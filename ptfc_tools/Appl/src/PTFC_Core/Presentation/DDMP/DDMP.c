/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              ddmp.c                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:                                                               */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     xxxxx                                                   */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|                                        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| xx/xx/xxxx  x.x          First derivative from Tesla (125K)
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DDMP.h"
#include "DDMP_config.h"

/* Module inhibition filter */
#ifdef __DDMP_IS_PRESENT__

/*______ L O C A L - D E F I N E S ___________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

#define DDMP_EVENT_COUNTER  40U    // 40 decimale - DTC Event Counter in presenza di nuovo guasto

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/


static PRES_KeyStatus_t Ddmp_KeyStatus;

/*______ L O C A L - D A T A _________________________________________________*/

/* To manage the status byte for all DTC the array Ddmp_StatusOfDtc has been created.
    Array's index is the DTC_ID. The value is the StatusByte corresponding to DTC_ID.
    At first power on the array is initialized to 0x40. The values saved in EEPROM
    are used to update the array's values.*/
static DDMP_DtcStatus_t Ddmp_StatusOfDtc[DDMP_ALL_DTC_ID];

static Ddmp_Operation_t Ddmp_Operation[DDMP_NUM_MAX_DTC_SAVED]; // Operazioni eseguite sui DTC

bool Ddmp_KeyOffAlarmActive;
static bool FunctionBusy; /* Flag di controllo per evitare chiamate concorrenti alle funzioni di accesso ai DTC */
static bool Ddmp_ControlDtcSetting; /* Flag che controlla l'abilitazione al setting dei Dtc */


/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* KeySts argument allows to implement different behavior according to
      monitoring cycle setting */
void Ddmp_UpdateDtcCounter(PRES_KeyStatus_t KeySts, DDMP_ID_t Dtc);
void Ddmp_UpdatePendingStatusBit(PRES_KeyStatus_t KeySts);
void Ddmp_InitOpDTC(PRES_KeyStatus_t KeySts);
u08 Ddmp_GetDTCPresent(u16 DTC_ID);
DDMP_Fault_Manager_t Ddmp_CheckFaultExistence(u08 idx, u08 Sympt);
void Ddmp_UpdateDTCPresent(u08 index);
void Ddmp_StoreNewDTC(DDMP_ID_t DTC_ID, u08 index);
void Ddmp_ResetMonitoringCycleStatusBit(PRES_KeyStatus_t KeySts);
DDMP_SetLessPriorityID_t Ddmp_SetLessPriorityID(DDMP_ID_t Test_ID, u08 *MinPriority);

void Ddmp_UpdateSnapshot(Ddmp_Block_t *DtcBlockPntr, u08 EventNum);

DDMP_Read_Result_t Ddmp_ReadDtcSnapshotRecord(Ddmp_Block_t             *DtcPntr,
                                              u08                       FaultSym,
                                              DDMP_Snapshot_Event_Num_t SnapNum,
                                              u08                      *BufferPntr,
                                              u08                      *AddLen);

void Ddmp_ReadSnapshot(u08 *DiagBufPtr, DDMP_Snapshot_Event_Num_t SnapNum, Ddmp_Block_t * DtcPntr);


/* Indica se è neccessario il salvataggio dei dati in EEPROM */
Ddmp_DtcSave_t Ddmp_Data_Status;
/* DDMP_StatusOfDtc init to 0x40*/
void Ddmp_InitStatusOfDtc(void);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/******************************************************************************/
/* Name :        DDMP_Init                                                    */
/* Role :        Inizializza la funzione                                      */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void DDMP_Init(void)
{

  Ddmp_InitOpDTC(ANY_KEY); /* lo stato ANY_KEY potrebbe essere sostituito dallo stato KEY_ON */
  Ddmp_Data_Status = DDMP_SAVING_NOT_NEEDED;
  Ddmp_ControlDtcSetting = DDMP_DTC_ENABLE;
  FunctionBusy = FALSE;
  Ddmp_InitStatusOfDtc();
  Ddmp_KeyStatus = KEYA_OFF_STATUS;
}

/******************************************************************************/
/* Name :        DDMP_KeyStsChanged                                           */
/* Role :        Ritorna lo stato del generic fail                            */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void DDMP_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
  static bool KeyOnTransitionFlag = TRUE;

  if((KeyStatus == KEYA_ON_STATUS) && (KeyOnTransitionFlag == TRUE))
  {
    /*------------------------------------------------------------------------*/
    /* Actions once KEY_ON is detected                                        */
    /*------------------------------------------------------------------------*/
    Ddmp_KeyStatus = KEYA_ON_STATUS;
    /* Se l'allarme per il salvataggio dei dati non era esaurito, blocco
    l'allarme in modo da non avere salvataggi multipli. key off/key on veloci */
    if(Ddmp_KeyOffAlarmActive)
    {
      TLRP_ResetSlow(DDMP_KEY_OFF_Timer);
      Ddmp_KeyOffAlarmActive = FALSE;
    }

    /* StatusByte BIT2 Update*/
    Ddmp_UpdatePendingStatusBit(KEYA_ON_STATUS);

    /* StatusByte BIT1 = 0 (testFailedThisMonitoringCycle = not failed) */
    Ddmp_ResetMonitoringCycleStatusBit(KEYA_ON_STATUS);
  
    /* StatusByte BIT6 = 1 (testNotCompletedThisMonitoringCycle = TRUE) */
    DDMP_SetTestNotCompletedStatusBit(KEYA_ON_STATUS);
    
    /* Inizializzazione delle operazioni sui DTC. */
    Ddmp_InitOpDTC(KEYA_ON_STATUS);
    /* Set dello Status bit "testFailedThisMonitoringCycle" a 1
      (failed) per un insieme di DTC che al Key ON risultano presenti */

    DDMP_KEY_ON_EVENT

    /* Current key staus */
    KeyOnTransitionFlag = FALSE;
  }

  else if(KeyStatus == KEYA_OFF_STATUS)
  {
    /*------------------------------------------------------------------------*/
    /* Actions once KEY_OFF is detected                                       */
    /*------------------------------------------------------------------------*/
    Ddmp_KeyStatus = KEYA_OFF_STATUS;
    /*Nel caso di transizione da key-on a key-off gestisco il salvataggio
      dei DTC in EEPROM.
      Per evitare continui salvataggi durante i giochi chiave, eseguo il
      salvataggio dopo un tempo di 5 secondi. */

    if(KeyOnTransitionFlag == FALSE)
    {
      /*Timer di 5s per evitare salvataggi multipli in caso di eventuali giochi chiave*/
      TLRP_SetSlow(DDMP_KEY_OFF_Timer);
      Ddmp_KeyOffAlarmActive = TRUE;
      /* Congelo in un buffer lo stato del bit "testNotCompletedThisMonitoringCycle per i soli DTC presenti in memoria
      questa informazione influisce sui setting dei bit "pendingDtc" e sull'Event-Counter */
 
      DDMP_KEY_OFF_EVENT
    }
    else
    {
    }

    /* StatusByte BIT2 Update */
    Ddmp_UpdatePendingStatusBit(KEYA_OFF_STATUS);
    
    /* StatusByte BIT1 = 0 (testFailedThisMonitoringCycle = not failed) */
    Ddmp_ResetMonitoringCycleStatusBit(KEYA_OFF_STATUS); /*resetto il bit testFailedThisMonitoringCycle solo se è stato memorizzato a 1*/

    /* StatusByte BIT6 = 1 (testNotCompletedThisMonitoringCycle = TRUE) */
    DDMP_SetTestNotCompletedStatusBit(KEYA_OFF_STATUS);
    
    /* Inizializzazione delle operazioni sui DTC. */
    Ddmp_InitOpDTC(KEYA_OFF_STATUS);

    /* Current key staus */
    KeyOnTransitionFlag = TRUE;

  }
  else
  {
  }
}


/******************************************************************************/
/* Name :        DDMP_DtcSaveNeeded                                           */
/* Role :        Gestione del salvataggio dei dati in EEPROM                  */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
Ddmp_DtcSave_t DDMP_GetDTCSaveStatus(void)
{
  /* Se ci sono delle operazioni, salvo i dati in EEPROM ritorno DDMP_SAVING_NEEDED */
  return Ddmp_Data_Status;
}

/******************************************************************************/
/* Name :        DDMP_KeyOffService                                           */
/* Role :        Gestione del salvataggio dei dati in EEPROM                  */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void DDMP_KeyOffService( void )
{
  /* Questa funzione è chiamata dopo 5 secondi dallo spegnimento della centralina.
    Se ci sono state delle variazione nella tabella dei DTC, richiedo
    un salvataggio dei dati in EEPROM.*/

  Ddmp_KeyOffAlarmActive = FALSE;

  /* Se ci sono delle operazioni, salvo i dati in EEPROM */
  if(Ddmp_Data_Status == DDMP_SAVING_NEEDED )
  {
    EEPP_WriteDtcRuntime();
  }

  /* A questo punto, suppongo che la EEPROM sia allineata alla RAM.
    Di fatto questo non è vero, poiché può succedere che la EEPROM
    venga scritta più tardi. Ma comunque sarà scritta per cui, prima
    o poi i dati saranno allineati. */

  Ddmp_Data_Status = DDMP_SAVING_NOT_NEEDED;

  /*Nel caso peggiore ho questa situazione:

  1) Richiesta di salvataggio
  2) Modifica di un DTC
  3) Salvataggio in EEPROM
  In questo caso, potrei richiedere un salvataggio dei dati non neccessario al successivo key-off */
}

/******************************************************************************/
/* Name :        DDMP_SetDtc                                                  */
/* Role :        Scrive un DTC generico                                       */
/* Interface :   DDMP_ID_t ID, DDMP_FaultSymptom_t Fault                      */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
DDMP_Write_Result_t DDMP_SetDtc( DDMP_ID_t ID, DDMP_FaultSymptom_t Fault )

/* Gestisce l'inserimento di un DTC nella tabella.
   Vedi SPECIFICA GENERALE DI DIAGNOSI - 09009_ed3 - par.4.3.2
 */
{
  u08 index;                                                 /* Indice generico */
  u08 NumEvent;
  u08 Ddmp_SelectedPos    = DDMP_NUM_MAX_DTC_SAVED;          /* Posizione prescelta per la memorizzazione del nuovo DTC nella tabella da 10 elementi   */
  Ddmp_Block_t * DtcPntr  = (Ddmp_Block_t *) &EERAM_DTC[0];  /* Struttura con la copia in RAM del DTC  */
  Ddmp_write_t        write_status = DDMP_WRITE_ST_START;    /* Stato della scrittura                  */

  DDMP_Write_Result_t write_result = DDMP_WRITE_FAIL;        /* Valore di ritorno della funzione       */
  DDMP_ID_t Ddmp_StatusPos;                                  /* Ddmp_StatusOfDtc index */


  u08   MinPriorNotPres      = 255U;                         /* Contiene la priorità minore tra i DTC NON presenti                         */
  u08   MinPriorPres         = 255U;                         /* Contiene la priorità minore tra i DTC presenti                             */
  
#if(DDMP_DTC_TIME_PRI_EN == TRUE)
  u32   ECUTimeMin           = 0xFFFFFFFFU;                  /* Contiene l'ECUTimeStamps del Dtc più vecchio tra i NON presenti            */
  u16   ECUTimeFromKeyOnMin  = 0xFFFFU;                      /* Contiene l'ECUTimeStampsFromKeyOn del Dtc con ECUTimeStamps più vecchio    */
  u08   OlderNotPresDtcPos   = DDMP_NUM_MAX_DTC_SAVED;       /* Contiene la posizione del Dtc più vecchio tra i NON presenti               */
#endif
  
  u08   MinPriorPresPos      = DDMP_NUM_MAX_DTC_SAVED;       /* Contiene la posizione del Dtc a priorità minore tra i presenti             */

  bool  DtcNotPresent        = FALSE;                        /* Si setta a TRUE se c'è almeno un Dtc in stato NON PRESENTE                 */

  bool  DtcNotPresNotSecur   = FALSE;                        /* Si setta a TRUE se tra i Dtc NON presenti ce nè almeno 1 NON di sicurezza  */
  u08   MinPriorDtcNotPres   = DDMP_NUM_MAX_DTC_SAVED;       /* Contiene la posizione del Dtc a priorità minore tra i NON presenti         */


  if(Ddmp_ControlDtcSetting == DDMP_DTC_ENABLE)
  {
    if(FunctionBusy)
    {
      write_result = DDMP_WRITE_BUSY;
    }
    else
    {
      
      FunctionBusy = TRUE;
      
      /* STEP 1
      Verifico se i dati inseriti nella funzione sono formalmente corretti:
      - ID deve avere un valore compreso tra DDMP_NO_DTC_ID e DDMP_ALL_DTC_ID
      - Se l'ID è valido, si verifica se il sintomo è tra quelli gestiti
      */
      
      if(Ddmp_CheckFaultExistence(ID, Fault) == FAULT_NOT_MANAGED)
      {
        write_status = DDMP_WRITE_ST_FAILED; /*0x01*/
      }
      
      /* STEP 2
      Se non ci sono errori di formato dei dati, verifico se il guasto segnalato è già presente in memoria oppure se ci sono delle celle libere.
      Alla fine di questo step, setto una serie di info che serviranno in caso di memoria errori piena (10 DTC memorizzati).
      In base a queste info, si calcola SE il DTC da memorizzare abbia diritto a sostituirne uno già memorizzato ed eventualmente QUALE.
      L'algoritmo di filtraggio è descritto nella norma 9009 ed.3.
      Da questo punto in avanti, blocco gli altri accessi ai dati dei DTC.
      */
      
      if( !(write_status & DDMP_WRITE_ST_COMPLETED /*0x7F*/) ) /*Se sono in WRITE_ST_START entro*/
      {
        for(index=0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
        {
          if(!(write_status & (u16)(DDMP_WRITE_ST_CELL_UPDATE/*0x04*/ | DDMP_WRITE_ST_CELL_READY/*0x08*/) ))
          {
            
            /**************************************************************************/
            /*                  SPIEGAZIONE BLOCCO DI CODICE SOTTO                    */
            /* Eseguo una delle condizioni sotto riportate ( 1), 2), 3), 4) ):        */
            /*  1) Controllo se il DTC è già presente in RAM.                         */
            /*    1.1) Controllo il numero di eventi errore.                          */
            /*    1.2) Verifico se il fault è lo stesso del ciclo precedente ed era   */
            /*         già presente o se l'errore al ciclo precedente è stato         */
            /*         memorizzato ma nell'ultimo test eseguito NON era presente o    */
            /*         oppure non coincide con quello cercato.                        */
            /*  2) Controllo se esiste una cella libera in memoria.                   */
            /*  3) Controllo se esiste un DTC con stato non presente.                 */
            /*    3.1) Verifica se il Dtc corrente è di sicurezza.                    */
            /*    3.2) Verifica che la priorità del Dtc corrente è inferiore a quella */
            /*         minima.                                                        */
            /*    3.3) Confronta i Time Stamps di un Dtc con quelli del Dtc           */
            /*         attualmente più vecchio e se inferiori,setta i nuovi           */
            /*         Time Stamps minimi.                                            */
            /*  4) Verifica che la priorità del Dtc corrente è inferiore a quella     */
            /*     minima.                                                            */
            /**************************************************************************/
            /* Controllo se il DTC è già presente in RAM */
            if(DtcPntr[index].Ddmp_ID == ID)
            {
              // memorizzo la posizione prescelta per la memorizzazione del nuovo DTC nella tabella da 10 elementi
              Ddmp_SelectedPos = index;
              
              /* Verifico se il DTC deve essere salvato o se è già presente in RAM con lo stesso sintomo. */
              if(DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] != 0U)  // Controlla se ci sono già stati almeno 2 eventi di errore per questo DTC
              {
                NumEvent = DDMP_LAST_EVENT;        /*  Il DTC ha avuto almeno 2 eventi di errore */
              }
              else
              {
                NumEvent = DDMP_FIRST_EVENT;       /*  Il DTC ha avuto solo un evento di errore */
              }
              
              // Se il fault ricercato è lo stesso di quello memorizzato nello snapshot ed il bit testFailed è 1
              // if( (DtcPntr[index].Ddmp_Symptom[NumEvent] == Fault) && ((DtcPntr[index].Ddmp_Status.Byte & 0x01) == 0x01) )
              if( (DtcPntr[index].Ddmp_Symptom[NumEvent] == Fault) && (DtcPntr[index].Ddmp_Status.Bit.testFailed == 0x01U) )
              {
                write_status = DDMP_WRITE_ST_CELL_READY;  /* Il fault-symptom coincide e nell'ultimo test eseguito era ancora presente  */
              }
              else
              {
                write_status = DDMP_WRITE_ST_CELL_UPDATE; /* Il fault-symptom NON coincide, oppure coincide ma nell'ultimo test eseguito NON era presente */
              }
              
            }
            /* Controllo se c'è una cella libera */
            else if((DtcPntr[index].Ddmp_ID == DDMP_NO_DTC_ID ) &&
                    (!(write_status & DDMP_WRITE_ST_IN_CLEAN_CELL /*0x10*/ ))) // DDMP_WRITE_ST_IN_CLEAN_CELL || DDMP_WRITE_ST_OK || DDMP_WRITE_ST_COMPLETED
            {
              // memorizzo la posizione prescelta per la memorizzazione del nuovo DTC nella tabella da 10 elementi
              Ddmp_SelectedPos = index;
              write_status = DDMP_WRITE_ST_IN_CLEAN_CELL /*0x10*/;
            }
            else if( DtcPntr[index].Ddmp_Status.Bit.testFailed == 0U)  /* Se il Dtc corrente è attualmente NON PRESENTE */
            {
              DtcNotPresent = TRUE;          /* Almeno 1 Dtc è in stato NON PRESENTE */
              
              /* Verifica se il Dtc corrente è di sicurezza  */
              if(Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].SecurityDTC == FALSE)
              {
                DtcNotPresNotSecur = TRUE;    /* Tra i DTC in stato non presente almeno uno NON è di sicurezza */
              }
              /* Verifica che la priorità del Dtc corrente è inferiore a quella minima */
              if(Ddmp_SetLessPriorityID((DDMP_ID_t)(DtcPntr[index].Ddmp_ID), &MinPriorNotPres) == LOWER_PRIORITY)
              {
                MinPriorDtcNotPres = index;
              }
#if(DDMP_DTC_TIME_PRI_EN == TRUE)
              /*Confronta i Time Stamps di un Dtc con quelli del Dtc attualmente più vecchio e se inferiori, setta i nuovi Time Stamps minimi*/
              if(DDMP_UserSetOlderDtc(index, &ECUTimeMin, &ECUTimeFromKeyOnMin) == OLDEST )
              {
                OlderNotPresDtcPos = index;
              }
#endif
            }
            else
            {
              if(Ddmp_SetLessPriorityID((DDMP_ID_t)(DtcPntr[index].Ddmp_ID), &MinPriorPres) == LOWER_PRIORITY)
              {
                MinPriorPresPos = index;
              }
            }
          }
        }     /* fine ciclo for */
      }
      
      /* STEP 3 Norma 09009 ed.3: Filtraggio del Dtc secondo Presenza, Sicurezza, Priorità, TimeStamps */
      
      if(!(write_status & DDMP_WRITE_ST_COMPLETED /*0x7F*/) )
      {/* La memoria errori è piena */
        
        if(DtcNotPresent == TRUE) /* La memoria è piena e c'è almeno un Dtc in stato NON presente */
        {
          if(Ddmp_DtcInformation[ID].SecurityDTC == TRUE)  /* Il Dtc da memorizzare è di un componente di sicurezza */
          {
            if( Ddmp_SetLessPriorityID(ID, &MinPriorNotPres) == 0U ) /* Se in memoria esiste un Dtc (non presente) con priorità minore di quello da memorizzare */
            {
              Ddmp_SelectedPos = MinPriorDtcNotPres;
              write_status = DDMP_WRITE_ST_SECURITY_CODE;
            }
#if(DDMP_DTC_TIME_PRI_EN == TRUE)
            else /* In memoria NON esiste un Dtc (non presente) con priorità minore di quello da memorizzare.Seleziono quello a TimeStamps + basso */
            {
              if(OlderNotPresDtcPos != DDMP_NUM_MAX_DTC_SAVED) /* La posizione selezionata è quella relativa al Dtc (NON presente) più vecchio */
              {
                Ddmp_SelectedPos = OlderNotPresDtcPos;
                write_status = DDMP_WRITE_ST_SUBSTITUTE_OLD_CODE;
              }
            }
#endif
          }
          else if(DtcNotPresNotSecur == TRUE)
            /* Il Dtc da memorizzare NON è di sicurezza e tra i Dtc NON presenti ci sono anche componenti NON di sicurezza.
            La posizione selezionata è quella relativa al Dtc (non presente) a priorità più bassa, indipendentemente dalla
            priorità del Dtc da memorizzare */
          {
            Ddmp_SelectedPos = MinPriorDtcNotPres;
            write_status = DDMP_WRITE_ST_SECURITY_CODE;
          }
          else
            /* Il Dtc da memorizzare NON è di sicurezza e tra i Dtc NON presenti ci sono SOLO componenti di sicurezza
            La scrittura del nuovo Dtc è negata! */
          {
            write_status = DDMP_WRITE_ST_DENIED;
          }
        }
        /* La memoria è piena e TUTTI i Dtc sono in stato PRESENTE */
        else if(Ddmp_SetLessPriorityID(ID, &MinPriorPres) == HIGHER_PRIORITY)
        {
          Ddmp_SelectedPos = MinPriorPresPos; /* Memorizzo il DTC al posto del DTC con priorità minore */
          write_status = DDMP_WRITE_ST_SECURITY_CODE;
        }
        else
        {
          write_status = DDMP_WRITE_ST_DENIED;
        }
      }
      
      /* Se non sono ancora riuscito a trovare una posizione utile per il salvataggio, allora significa che non esiste una cella utilizzabile. */
      if(write_status == DDMP_WRITE_ST_START)
      {
        write_status = DDMP_WRITE_ST_DENIED;
      }
      
      /* Find Ddmp_StatusOfDtc index */
      if (ID < DDMP_ALL_DTC_ID)
      {
        Ddmp_StatusPos = ID;
      }
      else
      {
        Ddmp_StatusPos = DDMP_NO_DTC_ID;
      }
      
      /* A questo punto, in base alle scelte effettuate prima (ho trovato una cella su cui memorizzare il DTC */
      /* o non sono riuscito a trovarla) memorizzo o non memorizzo l'errore.                                  */
      switch(write_status)
      {
        case DDMP_WRITE_ST_START:  /* Scrittura non iniziata */
        case DDMP_WRITE_ST_DENIED: /* Scrittura fallita in quanto non c'è nessuna cella sostituibile */
        write_result = DDMP_WRITE_NOT;
        break;
        
        case DDMP_WRITE_ST_CELL_READY: /* Il fault-symptom coincide e nell'ultimo test eseguito era ancora presente  */
        DtcPntr[Ddmp_SelectedPos].Ddmp_Status.Byte = DDMP_SS_FAIL_LAMP_OFF;
        Ddmp_StatusOfDtc[Ddmp_StatusPos].Byte = DDMP_SS_FAIL_LAMP_OFF;
        write_result = DDMP_WRITE_OK;
        break;
        
        case DDMP_WRITE_ST_IN_CLEAN_CELL:         /* E' stata trovata una cella libera    */
        case DDMP_WRITE_ST_SECURITY_CODE:         /* Gestione dei componenti di sicurezza */
        
        case DDMP_WRITE_ST_SUBSTITUTE_OLD_CODE:   /* Si sostituisce una cella di un Dtc vecchio secondo ECUTimeStamps */
        if (write_status != DDMP_WRITE_ST_IN_CLEAN_CELL)
        {
          Ddmp_StatusOfDtc[DtcPntr[Ddmp_SelectedPos].Ddmp_ID].Byte=0x40U; /*reimposto lo stato del vecchio DTC*/
        }
        DtcPntr[Ddmp_SelectedPos].Ddmp_Symptom[DDMP_FIRST_EVENT] = Fault;
        DtcPntr[Ddmp_SelectedPos].Ddmp_Status.Byte = DDMP_SS_FAIL_LAMP_OFF;
        Ddmp_StatusOfDtc[Ddmp_StatusPos].Byte = DDMP_SS_FAIL_LAMP_OFF;
        Ddmp_StoreNewDTC(ID, Ddmp_SelectedPos);
        Ddmp_Operation[Ddmp_SelectedPos].StoreDTC = TRUE;
        Ddmp_Data_Status = DDMP_SAVING_NEEDED;
        write_result = DDMP_WRITE_OK;
        break;
        
        case DDMP_WRITE_ST_CELL_UPDATE: /* Il fault-symptom NON coincide, oppure coincide ma nell'ultimo test eseguito NON era presente */
        DtcPntr[Ddmp_SelectedPos].Ddmp_Symptom[DDMP_LAST_EVENT] = Fault;
        DtcPntr[Ddmp_SelectedPos].Ddmp_Status.Byte = DDMP_SS_FAIL_LAMP_OFF;
        Ddmp_StatusOfDtc[Ddmp_StatusPos].Byte = DDMP_SS_FAIL_LAMP_OFF;     /*EZ: aggiorno lo stato del nuovo DTC*/
        Ddmp_UpdateDTCPresent(Ddmp_SelectedPos);
        Ddmp_Operation[Ddmp_SelectedPos].UpdateDTC = TRUE;
        Ddmp_Data_Status = DDMP_SAVING_NEEDED;
        write_result = DDMP_WRITE_OK;
        break;
        
        case DDMP_WRITE_ST_FAILED:  /* Scrittura fallita a causa di parametri errati */
        
        default:
        write_result = DDMP_WRITE_FAIL;
        break;
      }
      
      FunctionBusy = FALSE;
    }
  } /* Chiude l'IF del flag generale "ControlDtcsetting" */
  return write_result;
}

/******************************************************************************/
/* Name :        DDMP_ResetDtc                                                */
/* Role :        Devalida un DTC generico                                     */
/* Interface :   DDMP_ID_t ID, DDMP_FaultSymptom_t Fault                      */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/

DDMP_Write_Result_t DDMP_ResetDtc( DDMP_ID_t ID)

/* Gestisce la devalidazione di un DTC.
   Vedi SPECIFICA GENERALE DI DIAGNOSI - 07234 - par.4.3.2 */
{
  u08 index;                                               /* Indice generico */
  u08 Ddmp_SelectedPos = DDMP_NUM_MAX_DTC_SAVED;           /* Posizione prescelta per il nuovo DTC */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0]; /* Struttura con la copia in RAM del DTC  */

  DDMP_Write_Result_t write_result = DDMP_WRITE_FAIL;      /* Valore di ritorno della funzione */

  if(Ddmp_ControlDtcSetting == DDMP_DTC_ENABLE)
  {
    if(FunctionBusy)
    {
      write_result = DDMP_WRITE_BUSY;
    }
    else
    {
      
      FunctionBusy = TRUE;
      
      /* STEP 1
      Verifico se i dati inseriti nella funzione sono formalmente corretti.
      STEP 1.1
      ID deve avere un valore valido compreso tra DDMP_NO_DTC_ID e DDMP_ALL_DTC_ID  */
      
      if(( ID <= DDMP_NO_DTC_ID) || ( ID >= DDMP_ALL_DTC_ID))
      {
        write_result = DDMP_WRITE_FAIL;
      }
      
      /*STEP 2
      Se non ci sono errori di formato dei dati, verifico se il guasto segnalato è già presenti in memoria oppure se ci sono delle celle libere.
      Da questo punto in avanti, blocco gli altri accessi ai dati dei DTC. */
      else
      {
        for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
        {
          /* Controllo se il DTC è già presente in RAM */
          if(DtcPntr[index].Ddmp_ID == ID)
          {
            Ddmp_SelectedPos = index;
          }
        }
        
        if( Ddmp_SelectedPos < DDMP_NUM_MAX_DTC_SAVED)
        {
          /* Aggiorno i dati solamente se il dtc è ancora presente */
          if(DtcPntr[Ddmp_SelectedPos].Ddmp_Status.Bit.testFailed == 1U)
          {
            DtcPntr[Ddmp_SelectedPos].Ddmp_Status.Bit.testFailed = 0U;
            Ddmp_StatusOfDtc[ID].Bit.testFailed = 0U;
            write_result = DDMP_WRITE_OK;
            Ddmp_Operation[Ddmp_SelectedPos].UpdateDTC = TRUE;
            Ddmp_Data_Status = DDMP_SAVING_NEEDED;
          }
          else
          {
            write_result = DDMP_WRITE_OK;
          }
        }
      }
      
      FunctionBusy = FALSE;
    }
  } /* Chiude il flag generale "ControlDtcsetting" */

  return write_result;
}



/******************************************************************************/
/* Name :        DDMP_GetGenericFailPresent                                   */
/* Role :        Ritorna lo stato del generic fail                            */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
bool DDMP_GetGenericFailPresent( void )
{
  u08 index;  /* Indice generico */
  bool GenericFail = FALSE;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if(DtcPntr[index].Ddmp_ID != DDMP_NO_DTC_ID)
    {
      GenericFail = TRUE;
    }
  }

  return GenericFail;
}

/******************************************************************************/
/* Name :        DDMP_GetCurrentFailPresent                                   */
/* Role :        Ritorna lo stato del current fail                            */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
bool DDMP_GetCurrentFailPresent( void )
{
  u08 index;                                              /* Indice generico */
  bool CurrentFail = FALSE;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if(( DtcPntr[index].Ddmp_ID != DDMP_NO_DTC_ID ) &&( (DtcPntr[index].Ddmp_Status.Byte & 0x01U) != 0x00U /*DDMP_SS_NOFAIL*/ ) )
    {
      CurrentFail = TRUE;
    }
  }

  return CurrentFail;
}

/*****************************************************************************************************************/
/* Name :        DDMP_ReadDtcSnapshotRecord                                                                      */
/* Role :        Legge gli Snapshot di un DTC                     19 04                                          */
/* Author:                                                                                                       */
/* Interface :   None                                                                                            */
/* Constraints :                                                                                                 */
/* Behaviour :                                                                                                   */
/*---------------------------------------------------------------------------------------------------------------*/
DDMP_Read_Result_t DDMP_ReadDtcSnapshotRecord(u16 DtcCode, u08 FaultSym, DDMP_Snapshot_Event_Num_t SnapNum, u08 *BufferPntr, u08 *AddLen)
{
  u08 index;                                                   /* Indice generico,  */
  u08 DTC_Index;
  DDMP_Fault_Manager_t FaultCheckResult;                       /* Indice del DTC da cercare */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */
  
  DDMP_Read_Result_t read_result = DDMP_READ_OK;               /* Valore di ritorno */
  BufferPntr[1] = 0x00U; //status byte /*se non ci sono errori in memoria errori questo valore non verrà sovrascritto*/
  
  if(FunctionBusy)
  {
    read_result = DDMP_READ_BUSY;
  }
  else
  {
    FunctionBusy = TRUE;
    
    /* La prima operazione da fare è la verifica dell'esistenza del DTC richiesto tra quelli supportati dalla centralina */
    /* Questa operazione viene eseguita su Ddmp_DtcInformation[idx].SymptomsNum                                          */
    
    DTC_Index = Ddmp_GetDTCPresent(DtcCode);                          /* Converte il codice del DTC(su 2 byte) nel corrispondente ID (1 byte) della lista */
    FaultCheckResult = Ddmp_CheckFaultExistence(DTC_Index, FaultSym); /* Controlla se il Sintomo richiesto è uno di quelli possibili per lo specifico DTC */
    
    if( (DTC_Index == DDMP_ALL_DTC_ID) || (FaultCheckResult == FAULT_NOT_MANAGED) )
    {
      read_result = DDMP_READ_FAIL;
    }
    else
    {
      for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++) /* Si cerca il DTC nella memoria errori */
      {
        if( DtcPntr[index].Ddmp_ID == DTC_Index )
        {
          BufferPntr[0] = DtcPntr[index].Ddmp_Symptom[DDMP_FIRST_EVENT];
          BufferPntr[1] = DtcPntr[index].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK; /* Carico lo StatusByte */
          *AddLen = DDMP_NO_DATA_LENGTH; /* Non necessaria, per pulizia inizializzata a 0 */
          
          Ddmp_ReadDtcSnapshotRecord(&DtcPntr[index], FaultSym, SnapNum, BufferPntr, AddLen);
          
          //Ddmp_ComponeSnapshot(BufferPntr, SnapNum, index); la chiamo all'interno dello switch
          break; /*FRAT - una volta trovato il dtc esco dal ciclo for*/
        } /* Chiude l'if del DTC trovato in memoria */
      }  /* Chiude il for */
    }   /* Chiude l'else principale */
    
    FunctionBusy = FALSE;
  }
  
  return read_result;
}

/*****************************************************************************************************************/
/* Name :        DDMP_SearchSettedDtc                                                                            */
/* Role :        Legge gli Snapshot di un DTC                                                                    */
/* Author:                                                                                                       */
/* Interface :   None                                                                                            */
/* Constraints :                                                                                                 */
/* Behaviour :                                                                                                   */
/*---------------------------------------------------------------------------------------------------------------*/
#if 0
/*
DDMP_Read_Result_t DDMP_SearchSettedDtc(u16 DtcCode, u08 FaultSym, DDMP_Snapshot_Event_Num_t SnapNum)
{
  u08 index;                                                                Indice generico,
  u08 DTC_Index, FaultCheckResult;                                          Indice del DTC da cercare

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];      Struttura con la copia in RAM del DTC

  DDMP_Read_Result_t read_result = DDMP_READ_OK;                                     Valore di ritorno
  u08 ReadSnap = 0;

  if(FunctionBusy)
  {
    return DDMP_READ_BUSY;
  }

  FunctionBusy = TRUE;


  DDMP_CheckDtcPresence

  if ( ( idx > DDMP_NO_DTC_ID ) && ( idx < DDMP_ALL_DTC_ID) )
    {
      for(i=0; i<Ddmp_DtcInformation[idx].SymptomsNum; i++)
      {
        if(Ddmp_DtcInformation[idx].Symptoms[i] == Sympt)
        {
          Fault_Manager = FAULT_MANAGED;
        }
      }





   La prima operazione da fare è la verifica dell'esistenza del DTC richiesto tra quelli supportati dalla centralina
   Questa operazione viene eseguita su Ddmp_DtcInformation[idx].SymptomsNum

  DTC_Index = Ddmp_GetDTCPresent(DtcCode);                           Converte il codice del DTC(su 2 byte) nel corrispondente ID (1 byte) della lista
  FaultCheckResult = Ddmp_CheckFaultExistence(DTC_Index, FaultSym);  Controlla se il Sintomo richiesto è uno di quelli possibili per lo specifico DTC

  if( (DTC_Index == DDMP_ALL_DTC_ID) || (FaultCheckResult == 0) )
  {
    read_result = DDMP_READ_FAIL;
  }
  else
  {
     Pulisco i dati del buffer in ingresso
    for(index=0;index<DDMP_TWO_SNAP_LENGTH+1;index++)  +1 xchè devo considerare anche lo StatusByte che fa parte della risposta fissa
    {
      BufferPntr[index] = 0;
    }
    for(index=0;index<DDMP_NUM_MAX_DTC_SAVED;index++)  Si cerca il DTC nella memoria errori
    {
      if( DtcPntr[index].Ddmp_ID == DTC_Index )
      {
 *AddLen = DDMP_NO_DATA_LENGTH;  Non necessaria, per pulizia inizializzata a 0

        switch(SnapNum)
        {
          case DDMP_FIRST_EVENT:
            if(DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] != 0)  Ci sono stati almeno 2 eventi di Fault per questo DTC
            {
              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT])  I due eventi di Fault hanno avuto lo stesso sintomo
              {
                ReadSnap = 1;
 *AddLen = DDMP_ONE_SNAP_LENGTH;
              }
            }
            else
            {
              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_FIRST_EVENT])
              {
                ReadSnap = 1;
 *AddLen = DDMP_ONE_SNAP_LENGTH;
              }
            }
            break;

          case DDMP_LAST_EVENT:
            if(DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] != 0)  Ci sono stati almeno 2 eventi di Fault per questo DTC
            {
              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT])  I due eventi di Fault hanno avuto lo stesso sintomo
              {
                ReadSnap = 1;
 *AddLen = DDMP_ONE_SNAP_LENGTH;
              }
            }
            break;

          case DDMP_ALL_EVENT:
            if(DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] != 0)  Ci sono stati almeno 2 eventi di Fault per questo DTC
            {
              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT])  I due eventi di Fault hanno avuto lo stesso sintomo
              {
               ReadSnap = 1;
 *AddLen = DDMP_TWO_SNAP_LENGTH;
              }
            }
            else
            {
              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_FIRST_EVENT])
              {
                ReadSnap = 1;
 *AddLen = DDMP_ONE_SNAP_LENGTH;
              }
              else
              {
 *AddLen = DDMP_NO_DATA_LENGTH;
              }
            }
            break;

          default:
           read_result = DDMP_READ_FAIL;
          break;
        }  Chiude lo switch

        if(ReadSnap==1)
        {
          Ddmp_ComponeSnapshot(BufferPntr, SnapNum, index);
        }
        else
        {
          BufferPntr[0] = 0x00;
        }
      }  Chiude l'if del DTC trovato in memoria
    }   Chiude il for
  }    Chiude l'else principale

  FunctionBusy = FALSE;
  return read_result;
}
 */
#endif

/*****************************************************************************************************************/
/* Name :        DDMP_ReadDtcExtendedRecord                                                                      */
/* Role :        Legge gli Extended Snapshot di un DTC                                                           */
/* Author:                                                           19 06                                       */
/* Interface :   None                                                                                            */
/* Constraints :                                                                                                 */
/* Behaviour :                                                                                                   */
/*---------------------------------------------------------------------------------------------------------------*/
DDMP_Read_Result_t DDMP_ReadDtcExtendedRecord(u16 DtcCode, u08 FaultSym, DDMP_Snapshot_Ext_Num_t ExtDataNum, u08 *BufferPntr, u08 *AddLen)
{
  u08 index = 0U;                                           /* Indice generico */
  u08 DTC_Index;
  u08 flag_ext_data_rec = FALSE;
  DDMP_Fault_Manager_t FaultCheckResult;                   /* Indice del DTC da cercare */

  Ddmp_Block_t *DtcPntr       = (Ddmp_Block_t *) &EERAM_DTC[0];         /* Struttura snapshot con la copia in RAM del DTC  */
  Ddmp_BlockExt_t *DtcPntrExt = (Ddmp_BlockExt_t *) &EERAM_DTC_EXT[0];  /* Struttura extended snapshot con la copia in RAM del DTC  */

  DDMP_Read_Result_t read_result = DDMP_READ_OK;           /* Valore di ritorno */
  BufferPntr[1] = 0x00U; /*statusByte - se non ci sono errori in memoria errori questo valore non verrà sovrascritto*/

  if(FunctionBusy)
  {
    read_result = DDMP_READ_BUSY;
  }
  else
  {
    FunctionBusy = TRUE;
    
    DTC_Index = Ddmp_GetDTCPresent(DtcCode);                          /* Converte il codice del DTC(su 2 byte) nel corrispondente ID */
    FaultCheckResult = Ddmp_CheckFaultExistence(DTC_Index, FaultSym); /* Controlla se il Sintomo richiesto è uno di quelli possibili per lo specifico DTC */
    
    if( (DTC_Index == DDMP_ALL_DTC_ID) || (FaultCheckResult == FAULT_NOT_MANAGED) || ((ExtDataNum != DDMP_FIRST_EXT_EVENT) && (ExtDataNum != DDMP_LAST_EXT_EVENT) && (ExtDataNum != DDMP_ALL_EXT_EVENT)))
    {
      read_result = DDMP_READ_FAIL;
    }
    else
    {
      for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++) /* Si cerca il DTC nella memoria errori */
      {
        if( DtcPntr[index].Ddmp_ID == DTC_Index )
        {
          BufferPntr[0] = DtcPntr[index].Ddmp_Symptom[DDMP_FIRST_EVENT];
          BufferPntr[1] = DtcPntr[index].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK;
          
          // Su CANoe sembra che la richiesta da messaggio diagnostico supporti come DTCExtendedDataRecordNumber
          // i valori di 01(primo snapshot) e FF (Primo e secondo snapshot). E' stata implementata anche la
          // possibilità di richiedere il valore 02(secondo snapshot)
          switch(ExtDataNum)
          {
            case DDMP_FIRST_EXT_EVENT: // Invio il primo extended snapshot
              *AddLen = (DDMP_ONE_EXT_DATA_LENGTH);
              flag_ext_data_rec = TRUE;
              break;
/*FRAT - nel case sottostante non entrerà mai perchè filtrato a monte*/
            case DDMP_LAST_EXT_EVENT: // invio il secondo e ultimo snapshot

              if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT])
              {
                *AddLen = DDMP_ONE_EXT_DATA_LENGTH;
              }
              else
              {
                *AddLen = DDMP_NO_DATA_LENGTH;
              }
              break;

              case DDMP_ALL_EXT_EVENT: // Invio tutti gli snapshot disponibili
                *AddLen = DDMP_ONE_EXT_DATA_LENGTH;
                flag_ext_data_rec = TRUE;
                break;

              default:
                read_result = DDMP_READ_FAIL;
                break;
          } /* Chiude lo switch */

          if (flag_ext_data_rec)
          {
            BufferPntr[2]  = DDMP_FIRST_EXT_EVENT; // Per IVECO e FIAT il valore di ExtendedDataRecordNumber nella risposta è sempre 0x01. E' un valore differente da quello ricevuto nella richiesta.
            BufferPntr[3]  = 0x60u;
            BufferPntr[4]  = 0x80u;
            BufferPntr[5]  = DtcPntrExt[index].Ddmp_Dinam_Cond_Event_Counter;
          }
          else
          {
          }
          break; /*FRAT - una volta trovato il dtc esco dal ciclo for*/
        } /* Chiude l'if del DTC trovato in memoria */
      }  /* Chiude il for */
    }
    FunctionBusy = FALSE;
  }

  return read_result;
}

/*****************************************************************************************************************/
/* Name :        DDMP_ReportDTCSeverity                                                                          */
/* Role :        Riporta La severity di un DTC e il suo stato corrente di un DTC SubFunc 0x09                    */
/* Author:                                                                                                       */
/* Interface :   None                                                                                            */
/* Constraints :                                                                                                 */
/* Behaviour :                                                                                                   */
/*---------------------------------------------------------------------------------------------------------------*/
DDMP_Read_Result_t DDMP_ReportDTCSeverity(u16 DtcCode, u08 FaultSym, u08 *BufferPntr)
{
  u08 index = 0U;
  u08 DTC_Index, FaultCheckResult;                         /* Indice del DTC da cercare */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  DDMP_Read_Result_t read_result = DDMP_READ_OK;                        /* Valore di ritorno */
  
  if(FunctionBusy)
  {
    read_result = DDMP_READ_BUSY;
  }
  else
  {
    
    FunctionBusy = TRUE;
    
    /* Verifica dell'esistenza del DTC richiesto e del Sintomo. */
    
    DTC_Index = Ddmp_GetDTCPresent(DtcCode);  /* Converte il codice del DTC(su 2 byte) nel corrispondente ID */
    FaultCheckResult = Ddmp_CheckFaultExistence(DTC_Index, FaultSym); /* Controlla se il Sintomo richiesto è uno di quelli possibili per lo specifico DTC */
    
    if( (DTC_Index == DDMP_ALL_DTC_ID) || (FaultCheckResult == 0U) )
    {
      read_result = DDMP_READ_FAIL;
    }
    else
    {
      //    /* Pulisco i dati del buffer in ingresso */
      //    for(index=0; index<1; index++) //
      //    {
      //      BufferPntr[index] = 0x00;
      //    }
      
      BufferPntr[1] = (Ddmp_StatusOfDtc[DTC_Index].Byte & 0x40U); /*Initialization of StatusOfDTC if the DTC is not present in DTC error memory*/
      
      for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++) /* Si cerca il DTC nella memoria errori */
      {
        if( DtcPntr[index].Ddmp_ID == DTC_Index )
        {
          if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT])    /* Vuol dire che esiste un secondo Sintomo e coincide con quello richiesto */
          {
            BufferPntr[1] = DtcPntr[index].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK; /*Lo statusOfDTC è uguale per tutti gli snapshot*/
          }
          else if(FaultSym == DtcPntr[index].Ddmp_Symptom[DDMP_FIRST_EVENT])
          {
            BufferPntr[1] = DtcPntr[index].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK; /*Lo statusOfDTC è uguale per tutti gli snapshot*/
          }
          else
          {
          }
          break;  /*una volta trovato il dtc esco dal ciclo for*/
        }
        
        
      }  /* Chiude il for */
      
      BufferPntr[0] = Ddmp_DtcInformation[DTC_Index].Severity;
    }
    
    FunctionBusy = FALSE;
  }
  return read_result;
}

/******************************************************************************/
/* Name :        DDMP_CountAllDtcByMask                                       */
/* Role :                                                                     */
/*                                                                            */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
u16  DDMP_CountAllDtcByMask(u08 *Mask)
{
  u16 Counter = 0u;
  u08 index;

  for(index = 1U; index < DDMP_ALL_DTC_ID; index++)
  {
    if( Ddmp_StatusOfDtc[index].Byte & Mask[0] & DDMP_STATUS_AVAILABILITY_MASK)
    {
      Counter++;
    }
    else{}
  }
  return Counter;
}

/******************************************************************************/
/* Name :        DDMP_ReadAllDtcByMask                                        */
/* Role :        Riporta i DTC in memoria che soddisfano alla maschera di     */
/*               richiesta. Gestisce le Subfunction 0x02, 0x07, 0x08          */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
DDMP_Read_Result_t DDMP_ReadAllDtcByMask( u08 * BufferPntr, DDMP_Sub_Func_t SubFunc, u08 *Mask, u08 *NumOfDtc )
{
  DDMP_Read_Result_t read_result = DDMP_READ_FAIL;                      /* Valore di ritorno della funzione */

  if(FunctionBusy)
  {
    read_result = DDMP_READ_BUSY;
  }
  else
  {
    FunctionBusy = TRUE;

    read_result = DDMP_UserReadAllDtcByMask(BufferPntr, SubFunc, Mask, NumOfDtc);

    FunctionBusy = FALSE;

  }

  return read_result;
}

/* **********************************************************************************************/
/* Function name: DDMP_SetControlDtcSetting                                                     */
/* Author:                                                                                      */
/* Description:   set flag of control DTC (enable/disable DTC setting)                          */
/* Constraint:                                                                                  */
/* Returns:  nothing                                                                            */
/************************************************************************************************/
void DDMP_SetControlDtcSetting(bool EnDisDtc)
{
  bool tmp_ControlDtcSetting;

  tmp_ControlDtcSetting  = Ddmp_ControlDtcSetting;
  Ddmp_ControlDtcSetting = EnDisDtc;

  /* Chiamo l'evento in caso di fronte positivo */
  if ((tmp_ControlDtcSetting == FALSE) && (EnDisDtc == TRUE))
  {
    DDMP_ENABLE_DTC_EVENT
  }
}


/******************************************************************************/
/* Name :        DDMP_ClearAllDtc                                             */
/* Role :        Cancellazione di tutti i DTC                                 */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :  Richiamata tramite il servizio 19 14                          */
/*----------------------------------------------------------------------------*/
DDMP_Clear_Result_t DDMP_ClearAllDtc( void )
{
  u08 index;                                                            /* Indice generico */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];              /* Struttura con la copia in RAM del DTC  */
  Ddmp_BlockExt_t * DtcPntrExt = (Ddmp_BlockExt_t *) &EERAM_DTC_EXT[0]; /* Struttura con la copia in RAM del DTC  */

  DDMP_Clear_Result_t clear_result = DDMP_CLEAR_FAIL;                   /* Valore di ritorno della funzione */

  if(FunctionBusy)
  {
    clear_result = DDMP_CLEAR_BUSY;
  }
  else
  {
    
    FunctionBusy = TRUE;
    
    for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
    {
      if(DtcPntr[index].Ddmp_ID != DDMP_NO_DTC_ID)
      {
        memset(&DtcPntr[index], 0, sizeof(Ddmp_Block_t));
        memset(&DtcPntrExt[index], 0, sizeof(Ddmp_BlockExt_t));
        Ddmp_Operation[index].ClearDTC = TRUE;
      }
    }
    for(index = 1U; index < DDMP_ALL_DTC_ID; index++)
    {
      Ddmp_StatusOfDtc[index].Byte = 0x40U;
    }
    
    Ddmp_Data_Status = DDMP_SAVING_NEEDED;
    clear_result = DDMP_CLEAR_OK;
    
    /* A questo punto posso richiedere il salvataggio dei dati
    e attivare il timer di 5 secondi per l'aggiornamento
    dei DTC ancora attivi. */
    
    /* Notify the DTC clear event operation */
    DDMP_CLEAR_DTC_EVENT
      
    EEPP_WriteDtcRuntime();
    
    FunctionBusy = FALSE;
  }
  return clear_result;
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/******************************************************************************/
/* Name :        Ddmp_UpdateDtcCounter                                        */
/* Role :        Aggiornamento dei contatori                                  */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void Ddmp_UpdateDtcCounter(PRES_KeyStatus_t KeySts, DDMP_ID_t Dtc) /*FRAT - irrobustimento su event counter dei Dtc*/
/* Qui va messo l'aggiornamento di tutti i contatori.                         */
{
  u08 index;                                              /* Indice generico */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */
  Ddmp_BlockExt_t * DtcPntrExt = (Ddmp_BlockExt_t *) &EERAM_DTC_EXT[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U;index < DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if(DtcPntr[index].Ddmp_ID == Dtc)
    {
      /* Decremento i contatori se: - Non si deve ri-aggiornarne la presenza in memoria
                                  - Non si è appena validato come nuovo dtc
                                  - Provengo da uno stato del dtc pari a 0x08 (nel ciclo precedente non si è mai verificato)
                                  - L'eventcounter è maggiore di 0  */
      if(     (Ddmp_Operation[index].UpdateDTC == FALSE)                                     /*Non devo aggiornare il contatore dei DTC a 40         */
          &&  (Ddmp_Operation[index].StoreDTC  == FALSE)                                     /*Non è u nuovo DTC                                     */
          &&  ((DtcPntr[index].Ddmp_Status.Byte & 0x4FU) == DDMP_SS_FAIL_CONFIRMED)           /*DTC in memoria ma assente da almeno 2 Monitoring Cycle*/
          &&  (DtcPntrExt[index].Ddmp_Dinam_Cond_Event_Counter > 0x00U )                      /*I 40 cicli chiave con DTC assente non sono passati    */
          &&  (Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].KeyStatus == KeySts))    /*Sono allo stesso stato chiave della tabella DTC       */
      {
        DtcPntrExt[index].Ddmp_Dinam_Cond_Event_Counter--;
        Ddmp_Data_Status = DDMP_SAVING_NEEDED;
      }

      /* Elimino gli errori il cui event counter ha raggiunto la soglia minima. */
      if( (DtcPntr[index].Ddmp_ID != 0U) && (DtcPntrExt[index].Ddmp_Dinam_Cond_Event_Counter == 0x00U) )
      {
        Ddmp_StatusOfDtc[DtcPntr[index].Ddmp_ID].Byte = 0x00U;
        memset(&DtcPntr[index], 0, sizeof(Ddmp_Block_t));
      }

      break;
    }
    else
    {
    }
  }
}

/******************************************************************************/
/* Name :        void Ddmp_UpdatePendingStatusBit                             */
/* Role :        Aggiornamento degli StatusByte                               */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/* Description: Norma 14229-1.4- table D.17 pag.278 - Figure D.1- Pag.283     */
/* pendingDTC  == 0 settato dopo una richiesta di ClearDiagnosticInformation  */
/* o se nel monitoring cycle precedente se non si sono verificati fault       */
/* per quel determinato DTC.                                                  */
/* pendingDTC == 1 se il test è stato completato con risultato Failed         */
/* (riconoscimento avaria).                                                   */
/*----------------------------------------------------------------------------*/
void Ddmp_UpdatePendingStatusBit(PRES_KeyStatus_t KeySts)
{
  u08 index;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    /* Resetto il bit di stato "pendingDTC" se nel ciclo chiave appena concluso l'esito non è MAI stato negativo e ho completato il test*/
    /* Filtered by KeySts */

    if( ( (DtcPntr[index].Ddmp_Status.Byte & 0x4FU ) == DDMP_SS_FAIL_PENDING) && (Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].KeyStatus == KeySts) )

    {
      DtcPntr[index].Ddmp_Status.Bit.pendingDTC = 0U;
      Ddmp_StatusOfDtc[DtcPntr[index].Ddmp_ID].Bit.pendingDTC = 0U;
    }
  }
}

/******************************************************************************/
/* Name :        Ddmp_UpdateDTCPresent                                        */
/* Role :        Aggiornamento di un DTC già presente in memoria              */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void Ddmp_UpdateDTCPresent(u08 index)
/* Qui va messo l'aggiornamento di un DTC già presente in memoria */
{
  EERAM_DTC_EXT[index].Ddmp_Dinam_Cond_Event_Counter = DDMP_EVENT_COUNTER;

  Ddmp_Operation[index].UpdateDTC = TRUE;

  Ddmp_UpdateSnapshot(&EERAM_DTC[index], DDMP_LAST_EVENT);
}

/******************************************************************************/
/* Name :        Ddmp_StoreNewDTC                                             */
/* Role :        Inserimento di un nuovo DTC                                  */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void Ddmp_StoreNewDTC(DDMP_ID_t DTC_ID, u08 index)
{

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];                /* Struttura con la copia in RAM del DTC  */
  Ddmp_BlockExt_t * DtcPntrExt = (Ddmp_BlockExt_t *) &EERAM_DTC_EXT[0];   /* Struttura con la copia in RAM del DTC  */

  DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] = 0x00U;        /* Pulisco la cella del secondo sintomo. E' importante solo quando,
                                                                 a memoria piena, si sostituisce un dtc con un altro. Infatti il dtc sostituito
                                                                 può avere un secondo sintomo, che rimarrebbe erroneamente memorizzato     */
  DtcPntr[index].Ddmp_ID = DTC_ID;
  DtcPntrExt[index].Ddmp_Dinam_Cond_Event_Counter = DDMP_EVENT_COUNTER;
  Ddmp_Operation[index].StoreDTC = TRUE;

  /* Call user macro/routine */
  Ddmp_UpdateSnapshot(&DtcPntr[index], DDMP_FIRST_EVENT);
}

/******************************************************************************/
/* Name :        Ddmp_InitOpDTC                                               */
/* Role :        Inizializzazione delle operazioni sui DTC                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
void Ddmp_InitOpDTC(PRES_KeyStatus_t KeySts)

/* Cancellazione dell'elenco delle operazioni relative al
   ciclo di chiave precedente.
   L'elenco è utlizzato per la gestione dei contatori e per
   verificare se è necessario il salvataggio dei dati. */

{
  u08 index;
  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U;index < DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if ((Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].KeyStatus == KeySts) || (Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].KeyStatus == ANY_KEY))
    {
      Ddmp_Operation[index].UpdateDTC = FALSE;
      Ddmp_Operation[index].StoreDTC  = FALSE;
      Ddmp_Operation[index].ClearDTC  = FALSE;
    }
  }
}



/******************************************************************************/
/* Name :        Ddmp_GetDTCPresent                                           */
/* Role :        Ricerca dicotomica dell'id del DTC                           */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
u08 Ddmp_GetDTCPresent(u16 DTC_ID)
{
  u08 ListInf = 0U;
  u08 ListSup = DDMP_ALL_DTC_ID - 1U;
  u16 IndexList;
  u08 DTCtable_row_value;

  /* Ricerca del DTC richiesto tramite metodo dicotomico. */
  do
  {
    IndexList = ((u16)ListInf + (u16)ListSup) >> 1u;
    if (DTC_ID > Ddmp_DtcInformation[IndexList].Code)
    {
      ListInf = (u08)(IndexList + 1U);
    }
    else
    {
      ListSup = (u08)(IndexList - 1U);
    }
  } while ((ListInf <= ListSup) && (Ddmp_DtcInformation[IndexList].Code != DTC_ID));

  if (Ddmp_DtcInformation[IndexList].Code == DTC_ID)
  {
    DTCtable_row_value = (u08)IndexList;
  }
  else
  {
    DTCtable_row_value = DDMP_ALL_DTC_ID;
  }

  return DTCtable_row_value;
}


/******************************************************************************/
/* Name :        Ddmp_GetDTCPresent                                           */
/* Role :        Ricerca dicotomica dell'id del DTC                           */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
u08 DDMP_GetDTCStatus(DDMP_ID_t DTC_ID)
{
  return (Ddmp_StatusOfDtc[DTC_ID].Byte);
}

/******************************************************************************/
/* Name :        Ddmp_CheckFaultExistence                                     */
/* Role :                                                                     */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   Fault_Manager == 0 --> Fault is not managed                  */
/*               Fault_Manager == 1 --> Fault is managed                      */
/*----------------------------------------------------------------------------*/
DDMP_Fault_Manager_t Ddmp_CheckFaultExistence(u08 idx, u08 Sympt)
{
  u08 i;
  u08 numSymptoms;
  DDMP_Fault_Manager_t Fault_Manager;

  Fault_Manager = FAULT_NOT_MANAGED;
  numSymptoms = Ddmp_DtcInformation[idx].SymptomsNum;

  if ( ( idx > DDMP_NO_DTC_ID ) && ( idx < DDMP_ALL_DTC_ID) )
  {
    for(i = 0U; i < numSymptoms; i++)
    {
      if(Ddmp_DtcInformation[idx].Symptoms[i] == Sympt)
      {
        Fault_Manager = FAULT_MANAGED;
      }
    }
  }

  return Fault_Manager;
}

/******************************************************************************************/
/* Name :        Ddmp_ResetMonitoringCycleStatusBit                                       */
/* Author:                                                                                */
/* Role :        Dopo KeyOff-KeyOn, setta il bit testFailedThisMonitoringCycle a 0        */
/*               per ogni StatusByte di tutti i DTC presenti in memoria                   */
/* Interface :   None                                                                     */
/* Constraints :                                                                          */
/* Behaviour :                                                                            */
/*----------------------------------------------------------------------------------------*/
void Ddmp_ResetMonitoringCycleStatusBit(PRES_KeyStatus_t KeySts)
{
  u08 i;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(i = 0U; i < DDMP_NUM_MAX_DTC_SAVED; i++)
  {
    /*Se l'ID del DTC è diverso da 0 e il bit testFailedThisMonitoringCycle è presente in memoria (memorizzazione avvenuta con successo) */
    if( (DtcPntr[i].Ddmp_ID != DDMP_NO_DTC_ID) && ((DtcPntr[i].Ddmp_Status.Byte & 0x0EU) == DDMP_SS_FAIL_INTERMITTENT )
        && (Ddmp_DtcInformation[DtcPntr[i].Ddmp_ID].KeyStatus == KeySts) )
    {
      DtcPntr[i].Ddmp_Status.Bit.testFailedThisMonitoringCycle = 0U;       /* bit 1 StatusByte -> testFailedThisMonitoringCycle */
      Ddmp_StatusOfDtc[DtcPntr[i].Ddmp_ID].Bit.testFailedThisMonitoringCycle = 0U;
    }
  }
}

/********************************************************************************************/
/* Name :        DDMP_CheckDtcPresence                                                     */
/* Author:                                                                      */
/* Role :        Controlla se un Dtc è presente in memoria. Se si, restituisce il sintomo   */
/*               ed il suo stato.                                                           */
/* Interface :   None                                                                       */
/* Constraints :                                                                            */
/* Behaviour :                                                                              */
/*------------------------------------------------------------------------------------------*/
u08 DDMP_CheckDtcPresence(DDMP_ID_t Dtc, DDMP_FaultSymptom_t *Fault_symptom, u08 *StatusDtc)
{
  u08 ret_val = 0U;
  u08 i = 0U;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  if ( Ddmp_StatusOfDtc[Dtc].Bit.confirmedDTC == 1U)  /* Se il DTC è in memoria scorro la memoria */
  {
    /* Cerco il DTC */
    while( (i < DDMP_NUM_MAX_DTC_SAVED) && (ret_val == 0U) )
    {
      if(DtcPntr[i].Ddmp_ID == Dtc)
      {
        ret_val = 1U;
        i--;
      }
      i++;
    }

    /* Se ho trovato il DTC restituisco l'ultimo sintomo e lo stato */
    if(ret_val == 1U)
    {
      if(DtcPntr[i].Ddmp_Symptom[DDMP_LAST_EVENT] != 0U )
      {
        *Fault_symptom = (DDMP_FaultSymptom_t)(DtcPntr[i].Ddmp_Symptom[DDMP_LAST_EVENT]);
      }
      else
      {
        *Fault_symptom = (DDMP_FaultSymptom_t)(DtcPntr[i].Ddmp_Symptom[DDMP_FIRST_EVENT]);
      }
      *StatusDtc = DtcPntr[i].Ddmp_Status.Byte;
    }
    else{}
  }
  else
  {
    *StatusDtc = Ddmp_StatusOfDtc[Dtc].Byte;
  }
  return ret_val; /* 0 --> DTC non presente in memoria
                     1 --> DTC presente in memoria       */
}

/*********************************************************************************************************/
/* Name :        Ddmp_SetLessPriorityID                                                                  */
/* Author:                                                                                               */
/* Role :                                                                                                */
/* Constraints :                                                                                         */
/* Behaviour : Compara la priorità del DTC in esame con la priorità minore trovata                       */
/*             fino a quel momento e restituisce i seguenti valori:                                      */
/*             0 -> HIGHER_PRIORITY Il DTC in memoria ha una priorità maggiore                           */
/*             1 -> LOWER_PRIORITY  Il DTC in memoria ha una priorità minore                             */
/*-------------------------------------------------------------------------------------------------------*/
DDMP_SetLessPriorityID_t Ddmp_SetLessPriorityID(DDMP_ID_t Test_ID, u08 *MinPriority)
{
  u08 MinPr = *MinPriority;
  DDMP_SetLessPriorityID_t RetVal;

  if(Ddmp_DtcInformation[Test_ID].PriorityLevel < MinPr)
  {
    *MinPriority = Ddmp_DtcInformation[Test_ID].PriorityLevel;
    RetVal = LOWER_PRIORITY;  /* Il DTC in memoria ha una priorità minore (indice di priorità più piccolo) */
  }
  else
  {
    RetVal = HIGHER_PRIORITY; /* Il DTC in memoria ha una priorità maggiore (indice di priorità più grande)*/
  }

  return RetVal;
}


/******************************************************************************/
/* Name :        void DDMP_SetTestNotCompletedStatusBit                       */
/* Role :        Aggiornamento degli StatusByte                               */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   StatusByte BIT6 "testNotCompletedThisMonitoringCycle"        */
/*               is set to 1.                                                 */
/*----------------------------------------------------------------------------*/
void DDMP_SetTestNotCompletedStatusBit(PRES_KeyStatus_t KeySts)
{
  u08 index;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  /* aggiornamento testNotCompletedThisMonitoringCycle in memoria EEPROM */
  for(index = 0U; index< DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if (Ddmp_DtcInformation[DtcPntr[index].Ddmp_ID].KeyStatus == KeySts)
    {
      DtcPntr[index].Ddmp_Status.Bit.testNotCompletedThisMonitoringCycle = 1U;
    }
  }

  /* aggiornamento testNotCompletedThisMonitoringCycle in memoria RAM */
  for(index = 1U; index < DDMP_ALL_DTC_ID; index++)
  {
    if (Ddmp_DtcInformation[index].KeyStatus == KeySts)
    {
      Ddmp_StatusOfDtc[index].Bit.testNotCompletedThisMonitoringCycle = 1U;
    }
  }
}

/******************************************************************************/
/* Name :        void Ddmp_ResetTestNotCompletedStatusBit                     */
/* Role :                                                                     */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   StatusByte BIT6 "testNotCompletedThisMonitoringCycle"        */
/*               is set to 0.                                                 */
/*----------------------------------------------------------------------------*/
void DDMP_ResetTestNotCompletedStatusBit(DDMP_ID_t Dtc)
{
  u08  index;
  
  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  for(index = 0U; index<DDMP_NUM_MAX_DTC_SAVED; index++)
  {
    if(DtcPntr[index].Ddmp_ID == Dtc)
    {
      /*Decremento contatori DTC dopo aver effettuato un keyOff->KeyOn ed è stato terminato il primo test
       * che mette a 0 il bit 6 di Ddmp_Status relativo al DTC preso in considerazione*/
      if (DtcPntr[index].Ddmp_Status.Bit.testNotCompletedThisMonitoringCycle == 1U)
      {
        DtcPntr[index].Ddmp_Status.Bit.testNotCompletedThisMonitoringCycle = 0U;
        Ddmp_UpdateDtcCounter(Ddmp_KeyStatus, Dtc); /* Da chiamare dopo aver resettato il bit testNotCompletedThisMonitoringCycle */
      }
      else
      {
      }
    }
  }
  if (Dtc < DDMP_ALL_DTC_ID)
  {
    Ddmp_StatusOfDtc[Dtc].Bit.testNotCompletedThisMonitoringCycle = 0U;
  }
}

/******************************************************************************/
/* Name :        void Ddmp_InitStatusOfDtc                                    */
/* Role :        Ddmp_StatusOfDtc Init                                        */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   Initialize Ddmp_StatusOfDtc to 0x40. The values saved in     */
/*               EEPROM are used to update the array's values.                */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/* Ddmp_StatusOfDtc è una tabella utilizzata per contenere gli StatusOfDtc(16)*/
/* di tutti i possibili DTC gestiti dalla centralina.                         */
/* ogni StatusOfDtc ->     u08 testFailed                           :1; Bit0  */
/*                  ->     u08 testFailedThisMonitoringCycle        :1; Bit1  */
/*                  ->     u08 pendingDTC                           :1; Bit2  */
/*                  ->     u08 confirmedDTC                         :1; Bit3  */
/*                  ->     u08 testNotCompletedSinceLastClear       :1; Bit4  */
/*                  ->     u08 testFailedSinceLastClear             :1; Bit5  */
/*                  ->     u08 testNotCompletedThisMonitoringCycle  :1; Bit6  */
/*                  ->     u08 warningIndicatorRequest              :1; Bit7  */
/* La funzione inizializza la tabella in RAM mettendo tutti gli status bit a 0*/
/* e lo status bit 6 a 1. Se nella struttura memorizzata in RAM esiste un     */
/* ID != 0 e < 16. Inoltre copia lo stato dei DTC presenti in EEPROM          */
/* all'interno della tabella Ddmp_StatusOfDtc che contiene lo stato di tutti  */
/* i possibili DTC gestiti dalla centralina.                                  */
/*----------------------------------------------------------------------------*/
void Ddmp_InitStatusOfDtc(void)
{
  u08 index;

  /* Struttura contenente i 10 DTC memorizzati in RAM  */
  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];

  /*Inizializza la tabella in RAM dei DTC mettendo tutti gli status bit a 0 e lo status bit 6 a 1.*/
  for(index = 1U; index < DDMP_ALL_DTC_ID; index++)
  {
    Ddmp_StatusOfDtc[index].Byte = 0x40U;
  }

  /* Aggiorna all'interno della tabella in RAM le righe relative ai DTC presenti in EEPROM*/
  for(index = 0U; index < DDMP_NUM_MAX_DTC_SAVED; index++) // ciclo da 0 -> 10
  {
    if( (DtcPntr[index].Ddmp_ID != DDMP_NO_DTC_ID) &&  // se nella struttura memorizzata in RAM esiste un ID != 0 e ID < 16
        (DtcPntr[index].Ddmp_ID < DDMP_ALL_DTC_ID) )
    {    
      DtcPntr[index].Ddmp_Status.Bit.testNotCompletedThisMonitoringCycle = 1U;  //setta nella tabella dei 10DTC in RAM il bit6 (testNotCompletedThisMonitoringCycle) a 1
      Ddmp_StatusOfDtc[(DtcPntr[index].Ddmp_ID)].Byte = DtcPntr[index].Ddmp_Status.Byte;
      // Copia lo Stato dei DTC presenti in EEPROM all'interno della tabella Ddmp_StatusOfDtc che contiene
      // lo stato di tutti i possibili DTC gestiti dalla centralina.
    }
  }
}


/***************************************************************************************************/
/* Name :        DDMP_ReadSnapshot                                                                 */
/* Role :        Compose Snapshot buffer for UDS service 19 04                                     */
/* Author:                                                                                         */
/* Interface :   None                                                                              */
/* Constraints :                                                                                   */
/* Behaviour :                                                                                     */
/*-------------------------------------------------------------------------------------------------*/
void Ddmp_ReadSnapshot(u08 *DiagBufPtr, DDMP_Snapshot_Event_Num_t SnapNum, Ddmp_Block_t * DtcPntr)
{
  u08 i;             /* Indice ciclo for Evento*/
  u08 j;             /* Punta allo snapshot da riportare (o da "cominciare" a riportare nel caso siano richiesti entrambi)*/
  u08 k;             /* Indice ciclo for dato snapshot*/
  u08 BufIndex ;         /* Indice buffer da riempire */
  u08 SnapshotDataIndex; /* indice del'array che contiene i dati da riportare nello snapshot */
  u08 NumEvent;          /* Contiene QUANTI eventi sono da riportare (uno o due) */

   //buf[0] = DtcPntr[DtcIdx].Ddmp_Status.Byte; /* Carico lo StatusByte */

  // ALM_IVECO v1.4.1.71.cdd -> Data Types -> DTCSnapshotRecordNumber
  // For servers that do support multiple DTCSnapshot data records for a single DTC, the tester shall set this to a value
  // ranging from 0 to the maximum number supported by the ECU (which may range up to FE hex, depending on the server).
  // A value of FF hex requests the ECU to report all stored DTCSnapshot data records at once.

  // richiesto solo il 1° snapshot
  if(SnapNum == DDMP_ALL_EVENT)
  {
    j = 0U;
    NumEvent = 2U;
  }
  // richiesto solo il 2° snapshot
  else if (SnapNum == DDMP_LAST_EVENT)
  {
    j = 1U;
    NumEvent = 1U;
  }
  // richiesti tutti gli snapshot
  else if(SnapNum == DDMP_FIRST_EVENT)
  {
    j = 0U;
    NumEvent = 1U;
  }
  else
  {
  }

  BufIndex = 2u; // Parte dal byte 2 
  for(i = 0U; i < NumEvent; i++)
  {
    DiagBufPtr[BufIndex] = i ; //inserisco il DTCSnapshotRecordNumber relativo allo snapshot trasmesso
    BufIndex++;
    DiagBufPtr[BufIndex] = DDMP_SNAPSHOT_RECORD_NUM_DATA;
    BufIndex++;
    
    SnapshotDataIndex = 0U;
    
    /* scorre i dati snapshot e li inserisce nel buffer con il relativo RDI */
    for(k = 0U ; k < DDMP_SNAPSHOT_RECORD_NUM_DATA ; k++)
    {
      /* Scrive l'RDI (2 byte) */
      DiagBufPtr[BufIndex] = (u08)(Ddmp_EnvCondInformation[k].RDI >> 8u);
      BufIndex++;
      DiagBufPtr[BufIndex] = (u08)(Ddmp_EnvCondInformation[k].RDI);
      BufIndex++;
      
      /* Scrive il dato */
        memcpy(&DiagBufPtr[BufIndex],(void *)&(DtcPntr->Ddmp_Env[j+i].Bytes[SnapshotDataIndex]),(u16)Ddmp_EnvCondInformation[k].Length);
        SnapshotDataIndex += Ddmp_EnvCondInformation[k].Length;
        BufIndex += Ddmp_EnvCondInformation[k].Length ;
    }
  }
}

DDMP_Read_Result_t Ddmp_ReadDtcSnapshotRecord(Ddmp_Block_t             *DtcPntr,
                                              u08                       FaultSym,
                                              DDMP_Snapshot_Event_Num_t SnapNum,
                                              u08                      *BufferPntr,
                                              u08                      *AddLen)
{
  DDMP_Read_Result_t read_result;  /* Valore di ritorno */

  read_result = DDMP_READ_OK;

  switch(SnapNum)
  {
    /* WARNING: Visto che il 6° byte della risposta deve contenere lo StatusOfDTC */
    /* che viene calcolato nella funzione Ddmp_ComponeSnapshot(), è stato         */
    /* necessario incrementare il valore Diag_Response_Ln = 6 e ridotta la        */
    /* lunghezza di AddLen di 1                                                   */
    case DDMP_FIRST_EVENT:

      // E' stato richiesto solo il primo snapshot
      // Restituisco lo snapshot indipendentemente dal sintomo chiesto (come da scambio mail)
      *AddLen = DDMP_ONE_SNAP_LENGTH;// Inserire solo il primo snapshot
      Ddmp_ReadSnapshot(BufferPntr, SnapNum, DtcPntr);

      break;

      /* WARNING: Visto che il 6° byte della risposta deve contenere lo StatusOfDTC */
      /* che viene calcolato nella funzione Ddmp_ComponeSnapshot(), è stato         */
      /* necessario incrementare il valore Diag_Response_Ln = 6 e ridotta la        */
      /* lunghezza di AddLen di 1                                                   */
    case DDMP_LAST_EVENT:
      // E' stato richiesto solo l'ultimo snapshot
      // Verifico se è presente il secondo snapshot indipendentemente dal sintomo chiesto
      if(DtcPntr->Ddmp_Symptom[DDMP_LAST_EVENT] != DDMP_NO_SYMPTOM)
      {
        *AddLen = DDMP_ONE_SNAP_LENGTH; // Inserire solo il secondo snapshot
        Ddmp_ReadSnapshot(BufferPntr, SnapNum, DtcPntr);
      }
      else
      {
        *AddLen = DDMP_NO_DATA_LENGTH;
      }
      break;

      /* WARNING: Visto che il 6° byte della risposta deve contenere lo StatusOfDTC */
      /* che viene calcolato nella funzione Ddmp_ComponeSnapshot(), è stato         */
      /* necessario incrementare il valore Diag_Response_Ln = 6 e ridotta la        */
      /* lunghezza di AddLen di 1                                                   */
    case DDMP_ALL_EVENT:
      // Sono stati richiesti tutti gli snapshot
      // Verifico se è presente il secondo snapshot
      if(DtcPntr->Ddmp_Symptom[DDMP_LAST_EVENT] != DDMP_NO_SYMPTOM)
      {
        // Restituisco gli snapshot indipendentemente dal sintomo chiesto
        SnapNum = DDMP_ALL_EVENT;
        *AddLen = DDMP_TWO_SNAP_LENGTH; // invierò entrambi gli snapshot
      }
      else
      { // Restituisco il primo snapshot indipendentemente dal sintomo chiesto
        SnapNum = DDMP_FIRST_EVENT;
        *AddLen = DDMP_ONE_SNAP_LENGTH;// Inserire solo il primo snapshot
      }

      Ddmp_ReadSnapshot(BufferPntr, SnapNum, DtcPntr);

      break;

    default:
      read_result = DDMP_READ_FAIL;
      break;
  } /* Chiude lo switch */

  return read_result;
}

void Ddmp_UpdateSnapshot(Ddmp_Block_t *DtcBlockPntr, u08 EventNum)
{
  u08 i;
  u08 snapshotDataIndex;
  
  if(EventNum != DDMP_FIRST_EVENT)
  {
    EventNum = 1u;
  }

  snapshotDataIndex = 0U;
  /* scorre i dati snapshot e li legge per inserirli nei dati DTC */
  for(i = 0U ; i < DDMP_SNAPSHOT_RECORD_NUM_DATA ; i++)
  {
      DDMP_UserGetEnvCond((DDMP_Env_Cond_Num_t)i, &(DtcBlockPntr->Ddmp_Env[EventNum].Bytes[snapshotDataIndex]), DtcBlockPntr->Ddmp_Symptom[EventNum]);
      snapshotDataIndex += Ddmp_EnvCondInformation[i].Length;
  }

  if(EERAM_EcuStatusInfo.FirstConfirmedDtcID == 0x00u )
  {
    EERAM_EcuStatusInfo.FirstConfirmedDtcID        = (u08)DtcBlockPntr->Ddmp_ID;                  /* Per la richiesta 0x19 0x0C */
    EERAM_EcuStatusInfo.SymptomFirstConfirmedDtc   = DtcBlockPntr->Ddmp_Symptom[EventNum];
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
    EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection   = DDMP_GetEcuTimeStamps();            /* Copia RDI 0x200B */
    EERAM_EcuStatusInfo.EcuTimeFromKeyOn1DTCDetect = DDMP_GetEcuTimeStampsFromKeyOn();   /* Copia RDI 0x200C */
#endif
  }
  
  EERAM_EcuStatusInfo.MostRecentConfirmedDtcID = (u08)DtcBlockPntr->Ddmp_ID;                      /* Per la richiesta 0x19 0x0E */
  EERAM_EcuStatusInfo.SymptomMostRecentConfirmedDtc = DtcBlockPntr->Ddmp_Symptom[EventNum];
}

#endif /* end __DDMP_IS_PRESENT__ */

/*______ E N D _____ (ddmp.c) ________________________________________________*/
