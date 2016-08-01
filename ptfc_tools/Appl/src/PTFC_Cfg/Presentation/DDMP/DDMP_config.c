/********************************************************************************/
/* @F_PROJECT:          TTM Fiat                                                */
/* F_NAME:              CMMD_config.c                                           */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       S. Micari                                               */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     23/07/2013                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| SM           Salvatore Micari          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 23/07/2013  0.1  SM     First  draft
| 03/09/2013  0.2  MDN    Second draft
| 04/10/2013  0.3  SM     Update functions
| 17/04/2015  0.4  DF     Update function, configurable snapshot added
 */

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DDMP.h"
#include "DDMP_config.h"

/* Module inhibition filter */
#ifdef __DDMP_IS_PRESENT__

/*______ L O C A L - D E F I N E S ___________________________________________*/

#define DDMP_RECORD_NUMBER_OF_IDENTIFIERS_FIAT    0x06U  /* Numero di RDI che compongono i parametri ambientali FIAT */

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ L O C A L - D A T A _________________________________________________*/
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
static u16 DDMP_EcuTimeStampsFromKeyOn;
static u32 DDMP_EcuTimeStamps;
u08 OperationalModeStatus[DDMP_OP_MODE];
#endif

/* Inserire i dati in ordine crescente di codice del DTC */
Ddmp_DtcInformation_t const Ddmp_DtcInformation[DDMP_ALL_DTC_ID] =
{
  /* DTC  ,   Possibili Simtomi         , Severity      ,   Prior,  N.Sint,    KeySts         , Sicur ,  SPN Type         spare                                      */
  {0x0000U, {0x00U, 0x00U, 0x00U, 0x00U}, DDMP_NO_INFO  ,      0U,      0U,    KEYA_OFF_STATUS, FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_NO_DTC_ID             (0)   */
  {0x505DU, {0x8FU, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     95U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_VEHICLE_SPEED         (1)   */
  {0x9000U, {0x96U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     20U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_INTERNAL_FAIL         (2)   */
  {0x9001U, {0x24U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     21U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_TILT_SLIDE_KEY        (3)   */
  {0x9002U, {0x24U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     22U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_LIFT_BACKR_KEY        (4)   */
  {0x9005U, {0x24U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     23U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_MEM_KEY               (4)   */
  {0x9012U, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     40U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_TILT_SLIDE_RL         (5)   */
  {0x9016u, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     41U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_LIFT_BACK_RL          (6)   */
  {0x901BU, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     53U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_WARN,    0U }, /* DDMP_PROT_RL               (7)   */
  {0x9050U, {0x65U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     60U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_SLIDE_HALL_SENSOR     (8)   */
  {0x9051U, {0x65U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     61U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_TILT_HALL_SENSOR      (9)   */
  {0x9052U, {0x65U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     62U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_LIFT_HALL_SENSOR      (10)  */
  {0x9053U, {0x65U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     63U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_BACKREST_HALL_SENSOR  (11)  */
  {0x9062U, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     64U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_DRIVER_SEAT_HEATER    (12)  */
  {0x9063U, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     65U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_PSNGR_SEAT_HEATER     (13)  */
  {0x9064U, {0x11U, 0x15U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     66U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_STEERW_HEATER         (14)  */
  {0x90C9U, {0x29U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     67U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_NTC_STEERW            (15)  */
  {0x9100U, {0x16U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     71U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_SLIDE_LOW_CURRENT     (22)  */
  {0x9102U, {0x16U, 0x17U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     70U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_VBATT_MOTORS          (23)  */
  {0x9EB1U, {0x29U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     68U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_NTC_DRV               (16)  */
  {0x9EB2U, {0x29U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     69U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_NTC_PSG               (17)  */
  {0xC010U, {0x87U, 0x88U, 0x00U, 0x00U}, DDMP_CK_IMM   ,     99U,      2U,    KEYA_ON_STATUS , TRUE  ,  DDMP_SPN_FAULT,   0U }, /* DDMP_BUS_OFF               (18)  */
  {0xD700U, {0x86U, 0x87U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     98U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_BCM                   (19)  */
  {0xD703U, {0x86U, 0x87U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     97U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_IPC                   (20)  */
  {0xD710U, {0x86U, 0x87U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     96U,      2U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_ACM                   (21)  */
  {0xD932U, {0x86U, 0x00U, 0x00U, 0x00U}, DDMP_CK_IMM   ,     97U,      1U,    KEYA_ON_STATUS , TRUE  ,  DDMP_SPN_WARN,    0U }, /* DDMP_IWC_SIGNAL_FROM_BCM   (22)  */
  {0xD933U, {0x87U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     94U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }, /* DDMP_STATUS_BCM1           (23)  */
  {0xD934U, {0x87U, 0x00U, 0x00U, 0x00U}, DDMP_CK_NEXT_H,     93U,      1U,    KEYA_ON_STATUS , FALSE ,  DDMP_SPN_FAULT,   0U }  /* DDMP_STATUS_CCAN3          (24)  */
};



/* Table for configuration of snapshot data, this table is striclty correlated with DDMP_Env_Cond_Byte_t typedef  and DDMP_Env_Cond_Num_t
   WARNING: This table must be ordered according to DDMP_Env_Cond_Byte_t typedef, this not apples to 
            Symptom code that can be placed in every position
 */
Ddmp_Env_Cond_Cfg_t const Ddmp_EnvCondInformation[DDMP_SNAPSHOT_RECORD_NUM_DATA] =
{
    /*-----------+---------------*
     |   RDI     |   Length      |
     |           |               |
     *-----------+---------------*/
    {  0x1008U,         4U        }, /* Life Time */
    {  0x1009U,         2U        }, /* Time stamps ignition on */
    {  0x200AU,         2U        }, /* Ignition_On_Counter */
    {  0x6082U,         1U        }, /* DTC_Failure_Type*/
    {  0x1921U,         9U        }, /* Operational_Mode_Sts */
    {  0x1002U,         2U        }, /* Vehicle_Speed */
    {  0x1004U,         2U        }, /* Battery_Voltage */

};

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/******************************************************************************/
/* Name :        DDMP_ReadAllDtcByMask                                        */
/* Role :        Riporta i DTC in memoria che soddisfano alla maschera di     */
/*               richiesta. Gestisce le Subfunction 0x02, 0x07, 0x08          */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :                                                                */
/*----------------------------------------------------------------------------*/
DDMP_Read_Result_t DDMP_UserReadAllDtcByMask(u08             *DiagBufPtr,
                                             DDMP_Sub_Func_t SubFunc,
                                             u08             *Mask,
                                             u08             *NumOfDtc )
{
  u08 TestStatusMsk, TestSevMsk, TestFilter;
  u08 i;
  u08 NumEvent = 0U;
  u16 BUF_index;                                           /* Indice generico */
  DDMP_ID_t DTC_Index;                                     /* Indice del DTC da cercare */

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0]; /* Struttura con la copia in RAM del DTC  */

  DDMP_Read_Result_t read_result = DDMP_READ_FAIL;         /* Valore di ritorno della funzione */

  BUF_index = 0U;

  read_result = DDMP_READ_OK;

  *NumOfDtc = 0u;

  /* Copio tutti i DTC sul buffer di copia */
  for(DTC_Index = (DDMP_ID_t)1U; DTC_Index < DDMP_ALL_DTC_ID; DTC_Index++)
  {
    if(SubFunc == SUB_FUNC_02)
    {
      /* Si testa la corrispondenza con lo StatusByte */
      TestStatusMsk = DDMP_GetDTCStatus(DTC_Index) & Mask[0] & DDMP_STATUS_AVAILABILITY_MASK;              /* Si testa la corrispondenza con lo StatusByte */
      TestFilter = TestStatusMsk;
    }
    else      /* Se SubFunc 0x07 o 0x08 si testa anche la SeverityMask */
    {
      TestSevMsk = (Ddmp_DtcInformation[DTC_Index].Severity & Mask[0] & DDMP_STATUS_AVAILABILITY_MASK);   /* Si testa la corrispondenza con la Severity Mask */
      TestStatusMsk = DDMP_GetDTCStatus(DTC_Index) & Mask[1] & DDMP_STATUS_AVAILABILITY_MASK;             /* Si testa la corrispondenza con lo StatusByte    */
      TestFilter = (TestSevMsk != 0U) && (TestStatusMsk != 0U);
    }

    /* Filtro con la maschera di stato del msg di richiesta */
    if((DTC_Index != DDMP_NO_DTC_ID)&&(TestFilter != 0U))
    {
      (*NumOfDtc)++;     /* Conta i DTC che soddisfano la "DTCSeverityMaskRecord" */
      if((SubFunc != SUB_FUNC_07) && (DiagBufPtr != NULL)) //DF: added (DiagBufPtr != NULL) condition
      {
        if(SubFunc == SUB_FUNC_08)
        {
          DiagBufPtr[BUF_index] = Ddmp_DtcInformation[DTC_Index].Severity;
          BUF_index++;
          DiagBufPtr[BUF_index] = DDMP_FUNCTIONAL_UNIT;
          BUF_index++;
        }
        /* High Byte Code */
        DiagBufPtr[BUF_index] = (u08)((Ddmp_DtcInformation[DTC_Index].Code & 0xFF00) >> 8);
        BUF_index++;
        /* Low Byte Code */
        DiagBufPtr[BUF_index] = (u08)(Ddmp_DtcInformation[DTC_Index].Code & 0x00FFU);
        BUF_index++;
        //Se il DTC è in memoria prendo il sintomo dalla memoria
        //altrimenti tengo il primo sintomo della DTCInformation
        //(NumEvent è inizializzato a 0).

        // Se il DTC è confermato (ConfirmedDTC == 1)
        if(((DDMP_GetDTCStatus(DTC_Index) & 0x08U) >> 3U) == 0x01U)
        {
          for (i = 0U; i < DDMP_NUM_MAX_DTC_SAVED; i++)
          {
            if (DtcPntr[i].Ddmp_ID == DTC_Index)
            {
              NumEvent = (DtcPntr[i].Ddmp_Symptom[DDMP_LAST_EVENT] == 0U) ? DDMP_FIRST_EVENT : DDMP_LAST_EVENT;
              DiagBufPtr[BUF_index] = DtcPntr[i].Ddmp_Symptom[NumEvent];
              BUF_index++;
              i = DDMP_NUM_MAX_DTC_SAVED;
            }
          }
        }
        else
        {
          DiagBufPtr[BUF_index] = Ddmp_DtcInformation[DTC_Index].Symptoms[NumEvent];
          BUF_index++;
        }
        /* DTC Status */
        DiagBufPtr[BUF_index] = DDMP_GetDTCStatus(DTC_Index) & DDMP_STATUS_AVAILABILITY_MASK;
        BUF_index++;
      }
    }
    else
    {
    }
  }

  return read_result;
}




void DDMP_UserKeyOnEvent(void)
{
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
  // Norma 9009 pag.39: Indica il tempo di alimentazione della centralina dal Key ON e viene progressivamente
  // aggiornato ad ogni Key ON viene inizializzato al valore 0.
  DDMP_EcuTimeStampsFromKeyOn = 0x0000u;
  // Norma 9009 pag.39: Ad ogni KEY ON, la ECU deve inizializzare il contenuto dell’RDI $1008 con
  // il corrispettivo valore in EEprom RDI $2008.
  DDMP_EcuTimeStamps = EERAM_EcuStatusInfo.EcuTimeStamps;
  TLRP_SetSlow(DDMP_EcuTimeStampsTimer);
  TLRP_SetSlow(DDMP_EcuTimeStampsFromKeyOnTimer);
#endif
}


void DDMP_UserKeyOffEvent(void)
{
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
  //Reset EcuTimeStampsFromKeyOnTimer
  TLRP_ResetSlow(DDMP_EcuTimeStampsFromKeyOnTimer);

  EERAM_EcuStatusInfo.EcuTimeStamps = DDMP_EcuTimeStamps;

  // Norma 9009 pag.40: ad ogni Key ON, il contenuto dell’RDI $2009 rappresenta il valore del ciclo precedente.
  // Quindi ad ogni Key OFF salvo il contenuto dell’RDI $1009 in EEPROM
  EERAM_EcuStatusInfo.EcuTimeStampsFromKeyOn = DDMP_EcuTimeStampsFromKeyOn;

  /*Salvataggio in memoria dati dopo transizione keyOn->KeyOff*/
  EEPP_WriteData(EEPP_HDL_EcuStatusInfo, NULL);
#endif
}


/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/* **********************************************************************************************/
/* Function name: DDMP_ReportFirstLastConfirmedDtc                                              */
/* Author:                                                                                      */
/* Description:   Riporta il primo e l'ultimo DTC registrato in memoria. Queste informazioni    */
/*                sono indipendenti dal valore dell'eventcounter. Ovvero non tengono conto di   */
/*                 un'eventuale svalidazione dalla memoria errori. Vengono resettate a fronte   */
/*  del comando "ClearDiagnosticInformation".                                                   */
/* Constraint:                                                                                  */
/* Returns:  nothing                                                                            */
/************************************************************************************************/
void DDMP_ReportFirstLastConfirmedDtc (DDMP_Sub_Func_t SubFun, u08 *DiagBufPtr)
{
  u08 ID;
  u08 idx;

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];  /* Struttura con la copia in RAM del DTC  */

  switch(SubFun)
  {
  case SUB_FUNC_0C:
    ID = EERAM_EcuStatusInfo.FirstConfirmedDtcID;
    DiagBufPtr[3] = EERAM_EcuStatusInfo.SymptomFirstConfirmedDtc;
    break;

  case SUB_FUNC_0E:
    ID = EERAM_EcuStatusInfo.MostRecentConfirmedDtcID;
    DiagBufPtr[3] = EERAM_EcuStatusInfo.SymptomMostRecentConfirmedDtc;
    break;

  default:
    break;
  }

  if(ID != DDMP_NO_DTC_ID)  /* C'è stato almeno un DTC dopo l'ultima cancellazione errori */
  {
    DiagBufPtr[0] = 4u;

    DiagBufPtr[1] = (u08)(Ddmp_DtcInformation[ID].Code >> 8u);
    DiagBufPtr[2] = (u08)(Ddmp_DtcInformation[ID].Code & 0x00FFu);

    idx=0x00u;
    while( (DtcPntr[idx].Ddmp_ID != ID) && (idx<DDMP_NUM_MAX_DTC_SAVED) )
    {
      idx++;
    }

    if( idx < DDMP_NUM_MAX_DTC_SAVED )  /* Il DTC è ancora nella memoria errori */
    {
      /* Set dello StatusByte */
      if(SubFun == SUB_FUNC_0C)
      {
        if(  ((DtcPntr[idx].Ddmp_Symptom[1U] != 0U) && (DiagBufPtr[3U] == DtcPntr[idx].Ddmp_Symptom[1U]))
            ||((DtcPntr[idx].Ddmp_Symptom[1U] == 0U) && (DiagBufPtr[3U] == DtcPntr[idx].Ddmp_Symptom[0U])) )
        {
          DiagBufPtr[4] = DtcPntr[idx].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK; /* Il sintomo registrato nella SubF 0C coincide con l'ultimo rilevato */
        }
        else
        {
          DiagBufPtr[4] = 0x00u;   /* Il sintomo registrato nella SubF 0C NON coincide con l'ultimo rilevato */
        }
      }
      else if(SubFun == SUB_FUNC_0E)
      {
        DiagBufPtr[4] = DtcPntr[idx].Ddmp_Status.Byte & DDMP_STATUS_AVAILABILITY_MASK;
      }
      else
      {
        /* TODO: se non è SUB_FUNC_0C e non è SUB_FUNC_0E ... */
      }
    }
    else   /* Il DTC non è più nella memoria errori */
    {
      DiagBufPtr[4] = 0x00u;
    }
  }
  else   /* Memoria errori vergine o dopo l'ultima cancellazione errori non si è settato nessun DTC */
  {
    DiagBufPtr[0] = 0x00u;
  }
}
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
/*----------------------------------------------------------------------------*/
/*Name : DDMP_MngEcuTimeStamps                                                */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DDMP_MngEcuTimeStamps(void)
{
  DDMP_EcuTimeStamps++;
  TLRP_SetSlow(DDMP_EcuTimeStampsTimer);
}
/*----------------------------------------------------------------------------*/
/*Name : DDMP_MngEcuTimeStampsFromKeyOn                                       */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DDMP_MngEcuTimeStampsFromKeyOn(void)
{
  DDMP_EcuTimeStampsFromKeyOn++;
  TLRP_SetSlow(DDMP_EcuTimeStampsFromKeyOnTimer);
}

/*----------------------------------------------------------------------------*/
/*Name : DDMP_GetEcuTimeStamps                                                */
/*Role :                                    */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u32 DDMP_GetEcuTimeStamps(void)
{
  return(DDMP_EcuTimeStamps);
}

/*----------------------------------------------------------------------------*/
/*Name : DDMP_GetEcuTimeStampsFromKeyOn                                       */
/*Role :                                    */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u16 DDMP_GetEcuTimeStampsFromKeyOn(void)
{
  return(DDMP_EcuTimeStampsFromKeyOn);
}
#endif

void DDMP_UserClearDtcEvent(void)
{
  EERAM_EcuStatusInfo.SymptomFirstConfirmedDtc      = 0x00u;
  EERAM_EcuStatusInfo.SymptomMostRecentConfirmedDtc = 0x00u;
  EERAM_EcuStatusInfo.FirstConfirmedDtcID           = 0x00u;  /* Clear $19 0C     */
  EERAM_EcuStatusInfo.MostRecentConfirmedDtcID      = 0x00u;  /* Clear $19 0E     */
  EERAM_EcuStatusInfo.EcuTimeFirstDTCDetection      = 0x00U;  /* Clear RDI 0x200B */
  EERAM_EcuStatusInfo.EcuTimeFromKeyOn1DTCDetect    = 0x00u;  /* Clear RDI 0x200C */
}


/*______ L O C A L - F U N C T I O N S _______________________________________*/


#if (DDMP_DTC_TIME_PRI_EN == TRUE)
/***********************************************************************************************************/
/* Name :        Ddmp_SetOlderDtc                                                                          */
/* Author:                                                                                                 */
/* Role :        Confronta i Time Stamps di un Dtc con quelli del Dtc attualmente più vecchio.             */
/*               Se inferiori,setta i nuovi Time Stamps minimi.                                            */
/* Constraints :                                                                                           */
/* Behaviour :   INPUT : Index, &TimeMin, &TimeFromKeyOnMin                                                */
/*               OUTPUT: retval    newest = 0 --> Dtc in test più recente di quello attualmente più vecchio*/
/*                                 oldest = 1 --> Dtc in test più vecchio di quello attualmente più vecchio*/
/*---------------------------------------------------------------------------------------------------------*/
DDMP_SetOlderDtc_t DDMP_UserSetOlderDtc(u08 index, u32 *TimeMin, u16 *TimeFromKeyOnMin)
{

  Ddmp_Block_t * DtcPntr = (Ddmp_Block_t *) &EERAM_DTC[0];     /* Struttura con la copia in RAM del DTC  */

  u32 DtcTimeStamps = 0U;
  u16 DtcTimeFromKeyOn = 0U;
  u08 NumEvent;
  DDMP_SetOlderDtc_t retval = NEWEST;

  if(DtcPntr[index].Ddmp_Symptom[DDMP_LAST_EVENT] != 0U)
  {
    NumEvent = 1U;  /* Ci sono stati almeno 2 eventi di Fault per questo DTC */
  }
  else
  {
    NumEvent = 0U;  /* C'è stato un solo evento di Fault per questo DTC      */
  }
  /* Leggo i Time Stamps relativi all'ultimo sintomo */
  DtcTimeStamps  = (u32) (DtcPntr[index].Ddmp_Env[NumEvent].Cond.Life_Time[3]);                    /* Parte bassa */
  DtcTimeStamps |= ((u32)(DtcPntr[index].Ddmp_Env[NumEvent].Cond.Life_Time[2])) <<  8U;
  DtcTimeStamps |= ((u32)(DtcPntr[index].Ddmp_Env[NumEvent].Cond.Life_Time[1])) << 16U;
  DtcTimeStamps |= ((u32)(DtcPntr[index].Ddmp_Env[NumEvent].Cond.Life_Time[0])) << 24U;

  DtcTimeFromKeyOn  =  (u16)(DtcPntr[index].Ddmp_Env[NumEvent].Cond.Time_Stamps_Ign_On[1]);          /* Parte bassa */
  DtcTimeFromKeyOn |= ((u16)(DtcPntr[index].Ddmp_Env[NumEvent].Cond.Time_Stamps_Ign_On[0])) << 8;

  /* Controllo 1: se il Time Stamps del Dtc in test è minore di quello minimo, vuol dire che è più vecchio e setto il nuovo minimo */

  if(DtcTimeStamps < *TimeMin)
  {
    *TimeMin = DtcTimeStamps;
    *TimeFromKeyOnMin = DtcTimeFromKeyOn;
    retval = OLDEST;
  }
  /* Controllo 2: Se i Time Stamps generali coincidono, controllo i Time Stamps dal Key ON. Se quello in test è minore lo setto come nuovo minimo */
  else if(DtcTimeStamps == *TimeMin)
  {
    if(DtcTimeFromKeyOn < *TimeFromKeyOnMin)
    {
      *TimeFromKeyOnMin = DtcTimeFromKeyOn;
      retval = OLDEST;
    }
  }
  else{}

  return retval;
}
#endif

/* TODO TANK: verificare con Gianpero/Matteo e commentare bene:

  This function is called by the Ddmp_UpdateSnapshot() function 
  in order to retrieving environment conditions.
  It fills the buffer with the environment parameter, the number of byte filled 
  is specified by Ddmp_EnvCondInformation table*/
void DDMP_UserGetEnvCond(DDMP_Env_Cond_Num_t EnvCondNum, u08 *buffer, u08 Sympt)
{
  u16 calc_vbat = 0U;
  u16 speed     = 0U;

  switch(EnvCondNum)
  {
  case DDMP_ENV_COND_IGN_ON_CNT:
    buffer[0] = (u08)(EERAM_EcuStatusInfo.KeyOnCnt >> 8);
    buffer[1] = (u08)(EERAM_EcuStatusInfo.KeyOnCnt & 0x00FFu);
    break;

  case DDMP_ENV_COND_OPERAT_MODE_STS:
    memcpy(buffer, OperationalModeStatus, DDMP_OP_MODE);
    break;

  case DDMP_ENV_COND_VEH_SPEED:
    speed = FUNP_GetVehicleSpeed();
    buffer[0] = (u08)(speed >> 8u); // High byte
    buffer[1] = (u08)(speed & 0x00FFu); // Low  byte
    break;

  case DDMP_ENV_COND_BATT_VOLTAGE:
    calc_vbat = FUNP_GetBatteryVoltage();
    buffer[0] = (u08)(calc_vbat >> 8u);
    buffer[1] = (u08)(calc_vbat & 0x00FFu);
    break;

#if (DDMP_DTC_TIME_PRI_EN == TRUE)
  case DDMP_ENV_COND_LIFE_TIME:
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
    buffer[0] = (u08)( DDMP_EcuTimeStamps >> 24U);
    buffer[1] = (u08)((DDMP_EcuTimeStamps & 0x00FF0000U) >> 16U);
    buffer[2] = (u08)((DDMP_EcuTimeStamps & 0x0000FF00U) >>  8U);
    buffer[3] = (u08)( DDMP_EcuTimeStamps & 0x000000FFU        );
#endif
    break;

  case DDMP_ENV_COND_TIMESTAMP_IGN_ON:
#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
    buffer[0] = (u08)(DDMP_EcuTimeStampsFromKeyOn   >>  8  );
    buffer[1] = (u08)(DDMP_EcuTimeStampsFromKeyOn & 0x00FFU);
#endif
    break;
#endif

  case DDMP_ENV_COND_DTC_FAIL_TYPE:
    buffer[0] = Sympt;
    break;

  default:
    /* do nothing */
    break;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : DDMP_ComponeOperationalModeStatus                                    */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DDMP_ComponeOperationalModeStatus(void)
{
  u08 i;

  for (i = 0U; i < DDMP_OP_MODE; i++)
  {
    OperationalModeStatus[i] = 0x00U;
  }

  switch (STATUS_BH_BCM1.bit.OperationalModeSts)
  {
    case CMMD_IGNITION_OFF:       OperationalModeStatus[0U] = 0x01U; break;
    case CMMD_IGNITION_ACC:       OperationalModeStatus[0U] = 0x02U; break;
    case CMMD_IGNITION_ON:        OperationalModeStatus[0U] = 0x04U; break;
    case CMMD_IGNITION_PRE_START: OperationalModeStatus[0U] = 0x08U; break;
    case CMMD_IGNITION_START:     OperationalModeStatus[0U] = 0x10U; break;
    case CMMD_IGNITION_CRANKING:  OperationalModeStatus[0U] = 0x20U; break;
    case CMMD_IGNITION_ON_ENGON:  OperationalModeStatus[0U] = 0x40U; break;
    case CMMD_IGNITION_PRE_OFF:   OperationalModeStatus[0U] = 0x80U; break;
    case CMMD_IGNITION_PRE_ACC:   OperationalModeStatus[1U] = 0x01U; break;
    case CMMD_OP_MODE_SNA:        OperationalModeStatus[1U] = 0x80U; break;
    default:                                                         break;
  }

  switch (STATUS_BH_BCM2.bit.CmdIgnSts)
  {
    case CMMD_IGN_LK: OperationalModeStatus[7U] = 0x01U; break;
    case CMMD_ACC:    OperationalModeStatus[7U] = 0x02U; break;
    case CMMD_RUN:    OperationalModeStatus[7U] = 0x04U; break;
    case CMMD_START:  OperationalModeStatus[7U] = 0x08U; break;
    default:                                             break;
  }

  if (STATUS_BH_BCM2.bit.CmdIgn_FailSts == CMMD_IGN_FAIL_PRESENT)
  {
    OperationalModeStatus[8U] = 0x80U;
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : DDMP_GetOperationalModeStatus                                        */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DDMP_GetOperationalModeStatus(u08 *DiagBufferPntr, u08 DataLen)
{
  u08 i;

  for (i=0U; i < DataLen; i++)
  {
    DiagBufferPntr[i] = OperationalModeStatus[i];
  }
}


#endif /* end __DDMP_IS_PRESENT__ */

/*______ E N D _____ (ddmp_config.c) _________________________________________*/
