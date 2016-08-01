/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              tp.c                                                    */
/* @F_PURPOSE:          transport protocol implementation                       */
/*                      tpTx()          Must be called in MainLoop @ 10ms       */
/*                      tpRx()          Must be called @ RX diag. msg. event    */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/04/2013                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| MAG          M.Greco                   Bitron S.p.A.
| MID          M. d'Ercole               Bitron S.p.A.
| DF           Davide Fogliano           Polimatica S.r.l.
| CC           Carmine Celozzi           Akhela S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 25/02/2006  00.00 MAG    Prima stesura
| 11/07/2011  01.00 MID    Modifiche per GHS
| 24/04/2013  0.1   GIL    Ported in ALM IVECO
| 02/05/2013  0.2   GIL    Created interface with low level (CAND driver)
|                          and high level (UDS)
|-----------------------------------------------------------------------------
| 10/02/2015  0.3   CC     UDS messages alignment to F151M project message map
|-----------------------------------------------------------------------------
| 10/02/2015  1.0   CC     Alignement to platform TP
|-----------------------------------------------------------------------------
| 13/10/2015  1.0  FRAT    Issues #1875, 1876 - Platform Alignment
|-----------------------------------------------------------------------------
|-----------------------------------------------------------------------------
| 13/11/2015  1.1   FRAT     BOOT - APPL  Platform Alignement
|-----------------------------------------------------------------------------
*/

#define TP_IF_OWNER

/* =========================       include           ======================= */
#include "Tp.h"
#include "TP_config.h"

/* Module inhibition filter */
#ifdef __TP_IS_PRESENT__

/* =========================       define            ======================= */
#define IDLE_RX             0U
#define RECEIVING_RX        1U


u08 timer_N_CR;            // Misuratore del timeout N_Cr.
u08 Timer_T_Diag;     // Timer per gestione blocco richieste diagnostiche.
u08 supervison_timer_tp_tx;  // Controlla interruzione TX. tm221
TP_Flag_t  Status_TP;          // Insieme di flag bit per funzioni TP. tm221
u08 TpRx_FlowControl[3U];
u08 TPE_TX_Status;
u08 TPERX_Status;
u08 TP_FlowStatus;
/* =========================    variabili locali     ======================= */
static u16  NrDataRx;   // Contatore dei dati ricevuti sul singolo segmento Tp /*FRAT - variabile diventata u16 per problemi di overflow*/
static u08  NextSNRx;   // Contatore dei segmenti di Tp da intervallare con FC
#if  BLOCK_SIZE != 0U
static u16 SegmCntRx;  // Contatore dei segmenti di Tp
#endif
static u08  TpRx_Length;
static u08  TpRx_Buffer[8];
static u16  SndNrOfData;   // Number of data on Frame /*FRAT - variabile diventata u16 per evitare problemi di overflow*/
static u08  NextSNTx;      // Next segmentation number
static u08  txbox[8];
TP_Diag_t TP_DiagSts;     // Insieme di flag bit per funzioni UDS




/* =========================    prototipi funzione   ======================= */
static u08 TPFirstFrameRx(void);
static void TPSingleFrameRx(void);
static u08 TPConsecutiveFrameRx(void);
static void TPFlowControlFrameRx(void);

static u08 TP_FlowControlTx(void);
static u08 TP_SingleFrameTx(void);
static u08 TP_FirstFrameTx(void);
static u08 TP_ConsecutiveFrameTx(void);
static u08 TP_LastConsecutiveFrameTx(void);
static u08 TP_SendMessage(u08 payload[], u08 length);


/*----------------------------------------------------------------------------*/
/*Name : TP_Init                                                              */
/*Role : Init Tp variable                                                     */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [...]                                                                   */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void TP_Init(void)
{
  TPERX_Status = IDLE_RX;
  TPE_TX_Status = IDLE_TX;
  Status_TP.FlowControlError = FALSE;
  Status_TP.FlowControlTx = FALSE;
  Status_TP.FlowControlRx = FALSE;
  Diag_Resp_MRDI = 0u;
  /* init diag type to default */
  CAND_InitDiagType();
}

/* ========================================================================= **
**                                                                           **
**     Funzione chiamante:  canRxMessageHandler() su evento di ricezione     **
**                          msg. di diagnosi                                 **
**                                                                           **
**     Gestisce il TP in ricezione                                           **
**                                                                           **
** ========================================================================= **
**         MODIFICA                RELEASE          DATA           AUTORE    **
**       Prima stesura              00.00         25/02/06         M.Greco   **
** ========================================================================= */
void TpRx(u08 *diagbuf, u08 diaglen)
{
  u08 ReceivedFrameType;
  u08 Index;
  CAND_DiagType_t checkDiagType;

  // Copia i dati dal buffer riempito in RX driver CAN (oppure accedi in modo diretto al buffer del controllore se dedicato).
  for(Index=0u;Index<8U;Index++)
  {
    TpRx_Buffer[Index] = diagbuf[Index];
  }

  TpRx_Length = diaglen;

  ReceivedFrameType = TpRx_Buffer[0] & 0xF0U;

  switch (TPERX_Status)
  {
  /*-----------------------*/
  case IDLE_RX:
    /*-----------------------*/
    switch(ReceivedFrameType)
    {
    /*-----------------------*/
    case FLOW_CONTROL_FRAME:
      /*-----------------------*/
      Status_TP.FlowControlError = TRUE;  // tm077. 463.229-0300-01E.1
      if (TPE_TX_Status == WAIT_FLOWCONTROL_RX)
      {
        // La ricezione di un FlowControl può avvenire a seguito dell'azione di invio di un FF nella sezione TpTx()
        // Effettuato l'invio del FC non occorre cambiare stato: si resta in IDLE

        // E' importante evitare che vengano armati flag di ricezione di FC spuri se non lo stiamo aspettando ovvero non c'è trasmissione in corso.
        if (TP_DiagSts.DiagnosticResponse == TPX_MAKING)
        {
          checkDiagType = CAND_GetDiagType();
          if((TP_DiagSts.Type == CAND_GetDiagType()) ||      /*FRAT - inserito controllo per risolvere il TP30 di DiVa*/
             (checkDiagType == CAND_PHYSICAL_DIAG_REQ)) /*FRAT - se mi arriva un FlowControl con indirizzamento funzionale lo ignoro e abortisco la trasmissione*/
          {
            Status_TP.FlowControlError = FALSE; // tm077
            TPFlowControlFrameRx();
          }
          else
          {
            TP_DiagSts.DiagnosticResponse = TPTX_END;
            TPE_TX_Status = IDLE_TX;
          }
        }
      }
      break;

      /*-------------------*/
    case SINGLE_FRAME:
      /*-------------------*/
      // La ricezione di un SingleFrame non richiede di passare in RECEIVING
      // check Nack78_pending
      if(UDSA_Nak78Pending == NAK78_PENDING)
      {
      }
      else
      {
        if ((TP_DiagSts.DiagnosticResponse == TPTX_END)) /*FRAT - 08/01/2014 - accetto nuove richieste solo se ho terminato la precedente trasmissione*/
        {
          TPSingleFrameRx();
        }
      }
      
      break;

      /*-------------------*/
    case FIRST_FRAME:
      /*-------------------*/
      // La ricezione di un FirstFrame richiederebbe di passare in RECEIVING
      // a patto che tutto sia avvenuto correttamente, altrimenti si abortisce il TP e si resta in IDLE.
      if ((TP_DiagSts.DiagnosticResponse == TPTX_END)) /*FRAT - 08/01/2014 - accetto nuove richieste solo se ho terminato la precedente trasmissione*/
      {      
        if (TPFirstFrameRx() == RETURN_PASS)
        {
          TPERX_Status = RECEIVING_RX;
        }
      }
      break;

    default:
      // Se arriva un CONSECUTIVE_FRAME oppure ReceivedFrameType assume altri valori, allora si ignora il messaggio.
      break;
    }
    break;

    /*-----------------------*/
    case RECEIVING_RX:
      /*-----------------------*/
      switch(ReceivedFrameType)
      {
      /*-----------------------*/
      case CONSECUTIVE_FRAME:
        /*-----------------------*/
        // La ricezione di un ConsecutiveFrame richiede di restare in RECEIVING
        // a patto che tutto sia avvenuto correttamente, altrimenti si abortisce il tp e si passa in IDLE.
        if (TPConsecutiveFrameRx() == RETURN_FAIL)
        {
          TPERX_Status = IDLE_RX;
        }
        break;

        /*-----------------------*/
      case SINGLE_FRAME:
        /*-----------------------*/
        // La ricezione di un SingleFrame in RECEIVING non dovrebbe avvenire
        // se ciò accade il protocollo è interrotto e si processa il nuovo messaggio, a quel punto si torna in IDLE

        //TPSingleFrameRx();     /*FRAT - 09/10/2014 - spostata la funzione all'interno dell'if*/
        if(!TP_CHECK_FUNCTP)     /*FRAT - inserito controllo per risolvere il baco sul test 7.9.1.10 della norma 7-z0145*/
        {                        /*FRAT - se sono in receiving e mi arriva un TP funzionale resto in questo stato*/
          TPSingleFrameRx();
          TPERX_Status = IDLE_RX;
        }        
        break;

        /*-----------------------*/
      case FIRST_FRAME:
        /*-----------------------*/
        // La ricezione di un FirstFrame in RECEIVING non dovrebbe avvenire
        // se ciò accade il procollo è interrotto e si processa il nuovo messaggio, a quel punto si resta in RECEIVING
        // a meno che nella ricezione qualcosa non sia andato a buon fine
        if (TPFirstFrameRx() == RETURN_FAIL)
        {
          TPERX_Status = IDLE_RX;
        }
        break;

        /*-----------------------*/
      case FLOW_CONTROL_FRAME:
        /*-----------------------*/
        // La ricezione di un FlowControl in RECEIVING non ha significato. Si abortisce il tp e si torna in IDLE.
/*FRAT - un FC inaspettato dovrebbe essere ignorato - TP22 DiVa*/
        //TPERX_Status = IDLE_RX;
        break;

      default:
        // tm221. DAFARE: altri valori sono ammissibili ?
/*FRAT - un frame non conosciuto dovrebbe essere ignorato - TP23 DiVa*/
        //TPERX_Status = IDLE_RX;
        break;
      }
      break;

      default:
        break;
  }  /* end switch TPERX_Status */
}


/* ========================================================================= **
**                                                                           **
**     Gestisce la ricezione di un single frame                              **
**                                                                           **
** ========================================================================= */
static void TPSingleFrameRx(void)
{
  u08 Index;
  u08 Lenght;
  
  // Il single frame può essere accettato solo se distante adeguatamente dalla precedente richiesta ricevuta.
  /*FRAT - commentato l'if sottostante per risolvere il test di DiVa TP20 ed essere congruenti alla norma 15765-2 par. 6.7.3*/
  if (Timer_T_Diag == 0U)
  {
    // Si arma il timer di esclusione delle richieste che arrivino prima del dovuto.
    // In questo modo se arrivano due single frame consecutivi, solo il primo viene correttamente considerato.
    Timer_T_Diag = TIMEOUT_TDIAG_CAN;// tm048: istruzione non presente in versione PDPC

    Lenght = (TpRx_Buffer[0] & 0x0FU);  // Avoid  error #1867-D: MISRA 2004 Rule 10.1: implicit Conversion of complex expression from underlying type, "unsigned char", to underlying type, "u16", not allowed. tm221
   
#if (TP_ENABLE_PADDING == TRUE)
    if((TpRx_Length == 8U) && (Lenght < 8U)) //DF: il DLC è sempre 8 in caso di padding ma dobbiamo cntrollare NPCI_BYTE
#else
    /*FRAT - ripristinato l'if di sotto per risolvere i punti TP31 TP32 di DiVa ed essere conformi alla norma 7z-0145 par. 7.9.1.4/5/6*/
    if (TpRx_Length == (Lenght+1U)) // Controllo congruenza DLC con NPCI_BYTE (Test RC 1.5).
#endif
    {
      TP_DiagSts.Type = CAND_GetDiagType();

      if(TP_CHECK_FUNCTP) /*FRAT - la ricezione di un TesterPresent in funzionale non dovrebbe bloccare una successiva richiesta in fisico*/
      {
        Timer_T_Diag = 0U;
      }

      TP_DiagSts.DiagnosticRequest = TRUE;  // Si alza il Flag che indica la ricezione di una richiesta diagnostica.

      Diag_Requeste_Ln = Lenght;

      // Copia la richiesta nel buffer.
      // Si può copiare tutto il buffer anche se la richiesta ha meno di 7 byte (gli altri vengono ignorati): questo evita di usare il ciclo for.
      for(Index=0u;Index<7U;Index++)
      {
        Diag_Requeste[Index] = TpRx_Buffer[Index+1U];
      }
    }
  }
  else
  {
  }
}


/* ========================================================================= **
**                                                                           **
**     Gestisce la ricezione di un First Frame                               **
**                                                                           **
** ========================================================================= */
static u08 TPFirstFrameRx(void)
{
  u08 Result;
  u08   Index;
  u16 Lenght;
  
  Lenght = (((u16)TpRx_Buffer[0] & 0x0FU)<<8) | (u16)TpRx_Buffer[1]; /*FRAT - conformi alla norma 15765-2 par. 6.5.3.3*/
  
  if (CAND_GetDiagType() == CAND_PHYSICAL_DIAG_REQ) /*FRAT - norma 7-z0145, par 7.9.1.9 -  la ricezione di un FirstFrame in funzionale deve essere ignorata*/
  {
    if (Timer_T_Diag == 0U)
    {
      // Si arma il timer di esclusione delle richieste che arrivino prima del dovuto.
      // In questo modo se arrivano due first frame consecutivi, solo il primo viene correttamente considerato.
      Timer_T_Diag = TIMEOUT_TDIAG_CAN;// tm048: istruzione non presente in versione PDPC.
  
      // Controllo congruenza DLC con NPCI_BYTE (Test RC 1.5)
      if ((TpRx_Length == 8U) && (Lenght >= 8U))  /*FRAT: aggiunto controllo sul FF_DL per essere conformi alla norma 15765-2 par. 6.5.3.3 e norma 7z-0145 7.9.1.11*/
      {
        // Tra la ricezione del FF e l'invio del FC vi sono 200ms di tempo massimo.
        Status_TP.FlowControlTx = TRUE;// Si effettua la richiesta di invio di FC
  
        // Estrazione della lunghezza della richiesta.
  
        Diag_Requeste_Ln = Lenght;  /*(((u16)TpRx_Buffer[0] & 0x0FU)<<8) | (u16)TpRx_Buffer[1] */ /*FRAT - uso Lenght definito sopra*/
  
        if (Diag_Requeste_Ln > RXBUF_LENGTH)    // Gestione dell'indicazione di OverFlow.
        {
          TP_FlowStatus = OVERFLOW;
          Timer_T_Diag = 0U; /*FRAT - posso processare un altro messaggio una volta data la risposta di overflow */
          Result = RETURN_FAIL;
        }
        else
        {
          TP_FlowStatus = CLEAR_TO_SEND;
  
          // Copia nel Buffer della richiesta, evitando di usare il ciclo for
          for(Index=0u;Index<6U;Index++)
          {
              Diag_Requeste[Index] = TpRx_Buffer[Index+2U];
          }
          NrDataRx = 6U;
  #if  BLOCK_SIZE != 0U
          SegmCntRx = 1U;
  #endif
          NextSNRx = 1U;
          Result = RETURN_PASS;
        }
      }
      else
      {
        Result = RETURN_FAIL;
      }
    }
    else
    {
      Result = RETURN_FAIL;
    }
  }  
  else
  {
    Result = RETURN_FAIL;
  }    
  return Result;
}



/* ========================================================================= **
**                                                                           **
**     Gestisce la ricezione di un Consecutive Frame                         **
**                                                                           **
** ========================================================================= */
static u08 TPConsecutiveFrameRx(void)
{
  u08 Result;
  u08   Index;

  if ((TpRx_Buffer[0] & 0x0FU) != NextSNRx)
  {
      Result = RETURN_FAIL;// Ricezione Consecutive Frame errata
  }
  else
  {
    if (timer_N_CR == 0U)
    {
      Result = RETURN_FAIL;// Ricezione Consecutive Frame dopo TimeOut (Test RC 1.6): torno in IDLE
    }
    else
    {
      // Verifico che non si tratti dell'ultimo Consecutive Frame
      if ((Diag_Requeste_Ln - NrDataRx) > 7U)
      {
        // Controllo congruenza DLC con NPCI_BYTE (Test RC 1.5)
        // Non essendo l'ultimo CF la lunghezza deve essere di 8 byte
        if (TpRx_Length != 8U)
        {
            Result = RETURN_FAIL;
        }
        else
        {
            for(Index=0u;Index<7U;Index++)
            {
                Diag_Requeste[NrDataRx+Index] = TpRx_Buffer[Index+1U];
            }
          NrDataRx += 7U;

          // Calcoliamo il prossimo SN atteso
          NextSNRx = (NextSNRx + 1U) % 16U;
          // NB: Il protocollo TP prevede che se BLOCK_SIZE = 0 non si invi mai il FC durante la sequenza di CF.
          // Verifichiamo se occorre inviare il FlowControl.
#if  BLOCK_SIZE != 0U
          if (SegmCntRx == BLOCK_SIZE)
          {
            SegmCntRx = 1U;

            // Tra la ricezione del FF e l'invio del FC vi sono 200ms di tempo massimo
            TP_DiagSts.FlowControlTx = TRUE;// Si effettua la richiesta di invio di FC
          }
          else
#endif
          {
#if  BLOCK_SIZE != 0U
            ++SegmCntRx;
#endif
            timer_N_CR = N_CR;// Si arma il timer per analizzare il ritardo tra i vari CF.
          }
        Result = RETURN_PASS;
        }
      }
      else
      {
#if (TP_ENABLE_PADDING == TRUE)
        if (TpRx_Length == 8U)
#else
        // Controllo congruenza DLC con NPCI_BYTE (Test RC 1.5)
        if (TpRx_Length == ((Diag_Requeste_Ln - NrDataRx) +1U)) 
#endif
        {
          TP_DiagSts.Type = CAND_GetDiagType();
          TP_DiagSts.DiagnosticRequest = TRUE;  // Si alza il Flag che indica la ricezione di una richiesta diagnostica.
          Timer_T_Diag = TIMEOUT_TDIAG_CAN; // Arma il timer di esclusione delle richieste che arrivino prima del dovuto. tm221

          // In  questo caso il ciclo for può essere evitato solo perchè si è fissata la massima lunghezza di Diag_Requeste a 257. tm221
          // Nel FF abbiamo caricato 6 byte nel buffer
          // In ogni CF si caricano  7 byte nel buffer
          // Nell'ultimo caso posso caricare con sicurezza 7 byte senza avere il dubbio di sovrascrivere oltre Diag_Requeste[] solo se il buffer è pari a 7*NCF+6=34 con NCFmax=36. tm221
            for(Index=0u;Index<7U;Index++)
            {
                Diag_Requeste[NrDataRx+Index] = TpRx_Buffer[Index+1U];
            }
        }
        Result = RETURN_FAIL;// Ultima Consecutive Frame, il protocollo è terminato, torno in IDLE
      }
    }
  }
  return Result;
}


/* ========================================================================= **
**                                                                           **
**     Gestisce la ricezione di un FlowControl                               **
**                                                                           **
** ========================================================================= */
static void TPFlowControlFrameRx(void)
{
 
#if (TP_ENABLE_PADDING == TRUE)  //DF: se il padding è abilitato la TpRx_Length è sempre 8!
  if (TpRx_Length == 8U)
#else
  if (TpRx_Length == 3U)// Controllo congruenza DLC con NPCI_BYTE (Test RC 1.5)
#endif
  {
    Status_TP.FlowControlRx = TRUE; // Si alza il Flag che indica la ricezione di un FlowControl.

    // Copia nel Buffer per analisi del Flow control.
    TpRx_FlowControl[0] = TpRx_Buffer[0];
    TpRx_FlowControl[1] = TpRx_Buffer[1];
    TpRx_FlowControl[2] = TpRx_Buffer[2];
  }
}


/* ========================================================================= **
**                         FUNZIONE :  TpTx()                                **
**                                                                           **
**     Funzione chiamante: main ogni 10ms.                                   **
**                                                                           **
**     Gestisce il TP in trasmissione.                                       **
**                                                                           **
** ========================================================================= */
void TpTx(void)
{
  // Durata misurata di circa 30us, massima 50us. tm048. Dati PDPC (CPU 78K0, 16 MHz). DAFARE: ripetere la misura.

  static u08 BlockSize;   // Block size counter
  static u08 FC_Timer;    // Tempo di attesa del FlowControl. 463.229-0112-01D.1: Délai jusqu’à transmission du prochain message Flow_Control (N_Br).
  static u08 ST_Timer;    // Separation Timer (timing N_Cs): misura il ritardo fra un Consecutive Frame e il successivo. 463.229-0112-01F.2. STmin spécifie le temps minimal qui doit séparer deux émissions consécutives de messages CONSECUTIVE_FRAME.
  static u08 ST_Timeout;  // Valore di timeout STmin, ricevuto sul primo FC. 463.229-0110-01D. Correzione soft_defect_47 e PSA_ACP_B0_FR_14: problema dovuto a timing di chiamata del task TICK_TPTX (vedi tm050).
  static u08 SegmCntTx;  // Segmentation Counter



  if (Timer_T_Diag != 0U)// 463.229-0300-01G.1
  {
    --Timer_T_Diag;// Le richieste possono essere accettate solo se distanti adeguatamente dalla precedente richiesta ricevuta.
  }

  if (timer_N_CR != 0U)
  {
    --timer_N_CR;
  }

  // --------------------------------  Sorveglianza in trasmissione / supervision timer  ---------------------------------
    // Se esiste un msg. pending nel TX buffer e scade il timeout, allora esegue un abort della richiesta di TX.
  if (Status_TP.TP_TX_running)// tm221
  {
    supervison_timer_tp_tx--;
    if (supervison_timer_tp_tx == 0U)
    {
      Status_TP.TP_TX_running = FALSE;
      Status_TP.DIAG_REP_Abort = TRUE;
      Status_TP.FlowControlTx = FALSE;// tm221. Nel caso di errore TX la richiesta FlowControlTx rimane appesa/pending: annulla.
//      CanOutSupervisionPdpc.Field.compteurNAs++; //@GM@ Modifica per Test RC 1.5 N_AS
      timer_N_CR = 0U;
    }
  }


  if (TP_DiagSts.DiagnosticResponse == TPX_MAKING)
  {
    // TPE_TX deve essere schedulato a tempo fisso:
    // ad ogni chiamata decrementa il timer di controllo del ritardo del FlowControl (N_Br) e del tempo di separazione dei Consecutive Frame (N_Cs).

    if (FC_Timer != 0U)// tm050. Soft_defect_40. The ECU should not emit anymore Consecutive Frames when it receives the Flow_Control after N_Br_max. Requirement 463.229-0112-01D.1.
    {
      --FC_Timer;
    }
    if (ST_Timer != 0U)
    {
      --ST_Timer;
    }

    switch (TPE_TX_Status)
    {
      /**************/
      case IDLE_TX:
      /**************/
        // Correzione fiche ALTIS_239269. Se dopo una risposta della ECU
        // single frame abortita si rientra per una nuova risposta SF, il bit di abort è ancora uno.
        // Occorre abbassarlo e ignorarlo

        Status_TP.DIAG_REP_Abort = FALSE;


        ///////////////////
        // Single Frame
        ///////////////////
        if (Diag_Response_Ln < 8U)
        {
          if (TP_SingleFrameTx() == RETURN_PASS)
          {
            TP_DiagSts.DiagnosticResponse = TPTX_END;
            Timer_T_Diag = 0U;// Risposta emessa, possiamo processare altre richieste anche se il timer non è scaduto, quindi lo azzeriamo.
            TPE_TX_Status = IDLE_TX;// Rimane in questo stato: istruzione utile a creare blocco comune di uscita.
          }
        }
        ///////////////////
        // First Frame
        ///////////////////
        else
        {
          if (TP_FirstFrameTx() == RETURN_PASS)
          {
            SndNrOfData = 6U;
            FC_Timer = N_AS + N_BS;// Si arma il timer di controllo di ricezione del FlowControl
            NextSNTx = 1U;
            TPE_TX_Status = WAIT_FLOWCONTROL_RX;
          }
          else
          {
            // La funzione TP_FirstFrameTx non è andata a buon fine e si ritenta la trasmissione
          }
        }
        break;

      /***************************/
      case WAIT_FLOWCONTROL_RX:
      /***************************/

        if (Status_TP.DIAG_REP_Abort)// Gestione Abort del First Frame.
        {
          Status_TP.DIAG_REP_Abort = FALSE;// E' passato il TimeOut quindi il FC non è arrivato per tempo.

          TP_DiagSts.DiagnosticResponse = TPTX_END;
          Timer_T_Diag = 0U;// Reset timer protezione a seguito TX abort per perturbazione.
          TPE_TX_Status = IDLE_TX;
        }
        else
        {
          if (Status_TP.FlowControlRx)  // Ho ricevuto un Flow Control a seguito del mio First Frame
          {
            Status_TP.FlowControlRx = FALSE;
            
            if (SndNrOfData == 6U)// Sto aspettando il primo FC dopo il FF.
            {
              BlockSize = TpRx_FlowControl[1];// acquisisco il valore BS

              // Definisco il tempo di Timeout per i prossimi CF: lo si accetta solo sul primo Flow Control.
              ST_Timeout = TpRx_FlowControl[2] + 10u;// Acquisisco il valore STmin, espresso in millisecondi. /*FRAT - aggiunto ritardo di un tick del tptx per problemi di tempistiche. Non rispettavamo l'STmin*/

              // Controllo che il valore sia congruente con la norma 15765-2: vedi documento [wprocan-a00-00-b_Eng.doc] § 2.3.4 FC (Flow Control).
              if (ST_Timeout < 0x80U)
              {
                ST_Timeout = (ST_Timeout / TICK_TPTX);
              }
              else if (ST_Timeout < 0xF1U)
              {
                TpRx_FlowControl[0] = 0xFFU;// Reserved is received, make FC invalid.
              }
              else if (ST_Timeout < 0xFAU)
              {
                // ST_min espresso in microsecondi in un range 100us - 900 us = ST_Timeout - 0xF0U. Poiche' il task gira ogni TICK_TPTX ms poniamo ST_min a zero.
                ST_Timeout = 0U;
              }
              else
              {
                TpRx_FlowControl[0] = 0xFFU;// Reserved is received, make FC invalid.
              }
            }

            switch (TpRx_FlowControl[0] & 0x0FU)// Verifica flow control status ricevuto.
            {
              case CLEAR_TO_SEND:
                SegmCntTx = 1U;
                ST_Timer = STMIN/TICK_TPTX;// Misuro il delay per inviare il primo CF: armo timer per il delay.
                TPE_TX_Status = SEND_CONSECUTIVE_FRAME_TX;
                break;
              case WAIT:    // Il tester richiede di attendere a trasmettere il prossimo CF e chiede di aspettare un nuovo FC
                FC_Timer = N_AS + N_BS;
                break;
              default:      // Arrivato un valore OVERFLOW o invalido: dobbiamo sospendere la comunicazione
                TP_DiagSts.DiagnosticResponse = TPTX_END;
                TPE_TX_Status = IDLE_TX;
                break;
            }
          }
          else
          {
            if (FC_Timer == 0U)// E' passato il TimeOut quindi il FC non è arrivato per tempo
            {
              TP_DiagSts.DiagnosticResponse = TPTX_END;
              TPE_TX_Status = IDLE_TX;
            }
          }
        }
        break;

      /***************************/
      case SEND_CONSECUTIVE_FRAME_TX :
      /***************************/

        if (Status_TP.DIAG_REP_Abort)// Non si è ricevuto ACK dopo timeout (TX supervision timer): forza reset del protocollo.
        {
          Status_TP.DIAG_REP_Abort = FALSE;

          TP_DiagSts.DiagnosticResponse = TPTX_END;
          Timer_T_Diag = 0U;// Reset timer protezione a seguito TX abort per perturbazione.
          TPE_TX_Status = IDLE_TX;
        }
        else
        {
          if (ST_Timer == 0U)// Possiamo inviare un CF, essendo trascorso il tempo STmin.
          {
          /*FRAT - commentata la parte sottostante per risolvere il test fail TP18 di DiVa*/
		  /*FRAT - se arriva un FlowControl inaspettato in questo stato lo ignoro*/	  
            /*if ((Status_TP.FlowControlRx) || (Status_TP.FlowControlError))  // tm050, tm077. Soft_defect_39. The ECU does not give up the emission of Consecutive Frames in case of unexpected frame. Req. 463.229-0300-01E.1.
            {
              Status_TP.FlowControlRx = FALSE;
              Status_TP.FlowControlError = FALSE;     // tm077. The ECU gives up the emission of Consecutive Frames in case of unexpected frame.

              TP_DiagSts.DiagnosticResponse = TPTX_END;
              Timer_T_Diag = 0U;
              TPE_TX_Status = IDLE_TX;
            }
            else
            {
*/            if ((Diag_Response_Ln - SndNrOfData) > 7U)// Verifico se si tratta dell'ultimo CF. tm471.
              {
                if (TP_ConsecutiveFrameTx() == RETURN_PASS)
                {
                  SndNrOfData += 7U;
                  NextSNTx = (NextSNTx + 1U) % 16U;
                  if (SegmCntTx == BlockSize) // Verifico se dopo questo CF devo attendere il FC
                  {
                    FC_Timer = N_AS + N_BS;
                    TPE_TX_Status = WAIT_FLOWCONTROL_RX;
                  }
                  else
                  {
                    ++SegmCntTx;            // Dopo questo CF ne trasmetterò un altro senza attendere FC
                    ST_Timer = ST_Timeout;
                  }
                }
              }
              else
              {
                if (TP_LastConsecutiveFrameTx() == RETURN_PASS)// Invio dell'ultimo CF.
                {
                  // Risposta emessa, possiamo processare altre richieste anche se il timer non è scaduto, quindi lo azzeriamo.
                  TP_DiagSts.DiagnosticResponse = TPTX_END;
                  Timer_T_Diag = 0U;
                  TPE_TX_Status = IDLE_TX;
                }
              }
          //}
          }
        }
        break;
      default:
        break;
    }
  }
  else
  {
    if (Status_TP.FlowControlTx)
    {
      if (TP_FlowControlTx() == RETURN_PASS)
      {
        Status_TP.FlowControlTx = FALSE;
      }
    }
  }
}

/* ========================================================================= **
**                                                                           **
**     Gestisce la trasmissione di un FlowControl                            **
**                                                                           **
** ========================================================================= */
static u08 TP_FlowControlTx(void)
{
  u08 response;

  if (!Status_TP.TP_TX_running) // buffer di trasmissione libero
  {
    txbox[0] = FLOW_CONTROL_FRAME | TP_FlowStatus;
    txbox[1] = BLOCK_SIZE;
    txbox[2] = STMIN;

    response = TP_SendMessage(txbox, 3U);

    if (response == RETURN_PASS)  // tm048. Test valore di ritorno. tm221
    {
      timer_N_CR = N_CR;// carica timer su invio OK /ACK Messaggio TP. tm221. Nota: su PDPC (driver CAN non Vector, usavo il flag WaitAckFlowControl per caricare il timer su ACK = interrupt di trasmissione del msg. DIAG.)
    }
  }
  else
  {
    response = RETURN_FAIL; // buffer di trasmissione occupato
  }
  return response;
}


/* ========================================================================= **
**                                                                           **
**     Gestisce la trasmissione di un Single Frame                           **
**                                                                           **
** ========================================================================= */
static u08 TP_SingleFrameTx(void)
{
  u08 response;
  u08   Index;

  if (!Status_TP.TP_TX_running)// buffer di trasmissione libero
  {
    txbox[0] = SINGLE_FRAME | (u08)Diag_Response_Ln;// tm221. AVoid  error #1864-D: MISRA 2004 Rule 10.1: implicit Conversion from underlying type, "unsigned short", to narrower underlying type, "u08", not allowed.

    for(Index=0u;Index<7U;Index++)
    {
        txbox[Index+1U] = Diag_Response[Index];
    }

    response = TP_SendMessage(txbox, (u08)(Diag_Response_Ln+1U));
  }
  else
  {
    response = RETURN_FAIL; // buffer di trasmissione occupato
  }
  return response;
}


/* ============================================================================ **
**                         FUNZIONE :  TP_FirstFrameTx()                         **
**                                                                              **
**     Funzione chiamante: TpTx()                                               **
**                                                                              **
**     Gestisce la trasmissione di un First Frame                               **
**                                                                              **
**                                                                              **
** ============================================================================ **
**         MODIFICA                   RELEASE          DATA           AUTORE    **
**       Prima stesura                 00.00         25/02/06         M.Greco   **
** ============================================================================ */

static u08 TP_FirstFrameTx(void)
{
  u08 response;
  u08 Index;
    
  if (!Status_TP.TP_TX_running)// buffer di trasmissione libero
  {
    txbox[0] = (FIRST_FRAME | (u08)(Diag_Response_Ln>>8));  // MISRA rule 12.7
    txbox[1] = (u08)(Diag_Response_Ln & 0x00FFU);     // Il TP gestisce fino a 4096 byte.

    for(Index=0u;Index<6U;Index++)
    {
        txbox[Index+2U] = Diag_Response[Index];
    }

    response = TP_SendMessage(txbox, 8U);
  }
  else
  {
    response = RETURN_FAIL; // buffer di trasmissione occupato
  }
  return response;
}

/* ========================================================================= **
**                                                                           **
**     Gestisce la trasmissione di un Consecutive Frame                      **
**                                                                           **
** ========================================================================= */
static u08 TP_ConsecutiveFrameTx(void)
{
  u08 response;
  u08   Index;

  if (!Status_TP.TP_TX_running)// buffer di trasmissione libero
  {
    txbox[0] = CONSECUTIVE_FRAME | NextSNTx;

    for(Index=0u;Index<7U;Index++)
    {
        txbox[Index+1U] = Diag_Response[SndNrOfData + Index];
    }

    response = TP_SendMessage(txbox, 8U);
  }
  else
  {
    response = RETURN_FAIL; // buffer di trasmissione occupato
  }
  return response;
}


/* ========================================================================= **
**                                                                           **
**     Gestisce la trasmissione di un Consecutive Frame (ultimo)             **
**                                                                           **
** ========================================================================= */
static u08 TP_LastConsecutiveFrameTx(void)
{
  u08 response;
  u08   Index;

  if (!Status_TP.TP_TX_running)// buffer di trasmissione libero
  {
    txbox[0] = CONSECUTIVE_FRAME | NextSNTx;

    for(Index=0u;Index<7u;Index++)
    {
        txbox[Index+1U] = Diag_Response[SndNrOfData + Index];
    }

    response = TP_SendMessage(txbox, (u08)((Diag_Response_Ln - SndNrOfData)+1U));
  }
  else
  {
    response = RETURN_FAIL; // buffer di trasmissione occupato
  }
  return response;
}

/*----------------------------------------------------------------------------*/
/*Name : TP_SendMessage                                                       */
/*Role : Send a transport protocol message                                    */
/*Interface : IN: payload msg to send, msg length to send                     */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [...]                                                                   */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static u08 TP_SendMessage(u08 payload[], u08 length)
{
  u08 i, ret_val = RETURN_FAIL;
  CAND_TxMsgName_t MsgNameHnd;

  if(length > 8U)
  {
    length = 8U;
  }

  /* fill diag. response buffer */
  for(i = 0U; i < length; i++)
  {
    DiagResponseBuf.Byte[i] = payload[i];
  }

#if(TP_ENABLE_PADDING == TRUE)
  /* clean buffer */
  for(i = length; i < 8; i++)
  {
    DiagResponseBuf.Byte[i] = TP_PADDING_BYTE;
  }
  length = 8U;
#endif


  MsgNameHnd = TP_GetMsgNameHnd();

  /* transmit diag. message */
  if(NETP_SendDiagMsg(MsgNameHnd, length) != PRES_OK)
  {
    /* to adjust can driver return value and Tp return value */
    ret_val = RETURN_FAIL;
  }
  else
  {
    /* to adjust can driver return value and Tp return value */
    ret_val = RETURN_PASS;
  }
  
  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : TP_CheckDiagnosticDataReady                                          */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 TP_CheckDiagnosticDataReady(void)
{
  return(TP_DiagSts.DiagnosticRequest);
}

/*----------------------------------------------------------------------------*/
/*Name : TP_ResetDiagnosticDataReady                                          */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void TP_ResetDiagnosticDataReady(void)
{
  TP_DiagSts.DiagnosticRequest = FALSE;
}

/*----------------------------------------------------------------------------*/
/*Name : TP_RunTpTx                                                           */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void TP_RunTpTx(void)
{
  TP_DiagSts.DiagnosticResponse = TPX_MAKING;
}

/*----------------------------------------------------------------------------*/
/*Name : TP_ResetTimerDiag                                                    */
/*Role : Reset timer diag.                                                    */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void TP_ResetTimerDiag(void)
{
  Timer_T_Diag = 0U;
}

/*----------------------------------------------------------------------------*/
/*Name : TP_GetAddressingScheme                                               */
/*Role : Get diagnose request message type (Physical, Functional)             */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 TP_GetAddressingScheme(void)
{
  return((u08) TP_DiagSts.Type );
}

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagPhysMsgReceived                                               */
/*Role : Physical diagnose message received (UDS)                             */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void TP_DiagPhysMsgReceived(void)
{
  CAND_RxMsgName_t UdsPhysMsgRequestHnd;
  /* Event Rx diagnose request message : check diagnose message received */
  CAND_SetDiagType(CAND_PHYSICAL_DIAG_REQ);

  UdsPhysMsgRequestHnd = TP_GetUdsPhysMsgRequestHnd();

  TpRx(&DiagRequestBuf[0], CAND_GetMailBoxLen(UdsPhysMsgRequestHnd));
  CAND_SetDiagType(CAND_NO_DIAG_REQ);
}

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagHiPrtyPhysMsgReceived                                         */
/*Role : Physical diagnose high priority message received (UDS)               */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
#if (TP_HIPRTY_PHYS_MSG_EN == TRUE)
void TP_DiagHiPrtyPhysMsgReceived(void)
{
  CAND_RxMsgName_t UdsHiPrtyPhysMsgReqHnd;

  /* Event Rx diagnose request message : check diagnose message received */
  CAND_SetDiagType(CAND_PHYSICAL_DIAG_REQ);

  UdsHiPrtyPhysMsgReqHnd = TP_GetUdsHiPrtyPhysMsgRequestHnd();

  TpRx(&DiagRequestBuf[0], CAND_GetMailBoxLen(UdsHiPrtyPhysMsgReqHnd));
  CAND_SetDiagType(CAND_NO_DIAG_REQ);
}
#endif

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagFuncMsgReceived                                               */
/*Role : Functional diagnose message received (UDS)                           */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
#if (TP_FUNC_MSG_EN == TRUE)
void TP_DiagFuncMsgReceived(void)
{
  CAND_RxMsgName_t UdsFuncMsgRequestHnd;
/* Event Rx diagnose request message : check diagnose message received */
  CAND_SetDiagType(CAND_FUNCTIONAL_DIAG_REQ);

  UdsFuncMsgRequestHnd = TP_GetUdsFuncMsgRequestHnd();

  TpRx(&DiagRequestBuf[0], CAND_GetMailBoxLen(UdsFuncMsgRequestHnd));
  CAND_SetDiagType(CAND_NO_DIAG_REQ);
}
#endif


#endif /* end __TP_IS_PRESENT__ */

/*______ E N D _____ (TP.c) __________________________________________________*/
