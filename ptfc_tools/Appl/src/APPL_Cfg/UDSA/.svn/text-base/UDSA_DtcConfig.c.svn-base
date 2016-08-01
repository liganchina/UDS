/********************************************************************************/
/* @F_PROJECT:          TTM636 FIAT                                             */
/* F_NAME:              UDSA_DtcConfig.c                                        */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     26/09/2013                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| MAD          Mario Dallera             Consultant
| DF           Davide Fogliano           Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 26/09/2013  0.1  GIL     First Implementation : split from UDSA_Config.c
| 13/03/2014  1.0  GIL     Finally remove UDS subfunction table, managed in UDSA_Subfunction_t
|                          table type adding field AdSch
| 14/01/2015  1.0  DF      All DTC related sub-services disabled except for 01 and 02 
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define UDSA_FIXED_LEN_PROTOCOL    2U

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Subfunctions */
static u08 Udsa_FuncNumberOfDTCByStatusMask(u08 *Data, u16 Length);
static u08 Udsa_FuncDTCByStatusMask(u08 *Data, u16 Length);
static u08 Udsa_FuncDTCSnapshotRecordByDTCNumber(u08 *Data, u16 Length);
static u08 Udsa_FuncDTCExtendedDataRecordByDTCNumber(u08 *Data, u16 Length);
static u08 Udsa_FuncNumberOfDTCBySeverityMaskRecord(u08 *Data, u16 Length);
static u08 Udsa_FuncDTCBySeverityMaskRecord(u08 *Data, u16 Length);
static u08 Udsa_FuncSeverityInformationOfDTC(u08 *Data, u16 Length);
static u08 Udsa_FuncFirstConfirmedDTC(u08 *Data, u16 Length);
static u08 Udsa_FuncMostRecentConfirmedDTC(u08 *Data, u16 Length);
static void Udsa_ExtractDtc(u08 *BufInPtr, u16 *Dtc, u08 *Fault);


/*______ G L O B A L - D A T A _______________________________________________*/

/********************************************************************************************************************************************/
/*                                               SUBFUNCTIONS FOR $19 SERVICE                                                               */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_ReadDTCInformation[MAX_NUM_DTC_SERVICE] = /*Request message sub-function parameter  */
{
/* +------------------------------------+------+------+--------------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction                  |  En  | RxDL |                               Session                                                |             Callback Function        | diag.scheme   |
   |                                    |      |      |                                                                                      |                                      | (phys. funct  |
   +------------------------------------+------+------+--------------------------------------------------------------------------------------+--------------------------------------*---------------+*/
    {NUM_DTC_BY_STS_MASK,               DISABLE, 3U,  DIAG_NO_SESSION                                                                        , Udsa_FuncNumberOfDTCByStatusMask         , UDSA_ADS_BOTH },  /*$01*/
    {DTC_BY_STS_MASK,                    ENABLE, 3U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncDTCByStatusMask                 , UDSA_ADS_BOTH },  /*$02*/
    {DTC_SNAPSHOT_RECORD_BY_DTC_NUM,     ENABLE, 6U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncDTCSnapshotRecordByDTCNumber    , UDSA_ADS_BOTH },  /*$04*/
    {DTC_EXT_DATA_RECORD_BY_DTC_NUM,     ENABLE, 6U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncDTCExtendedDataRecordByDTCNumber, UDSA_ADS_BOTH },  /*$06*/
    {NUM_OF_DTC_BY_SEVERITY_MASK_RECORD, ENABLE, 4U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncNumberOfDTCBySeverityMaskRecord , UDSA_ADS_BOTH },  /*$07*/
    {DTC_BY_SEVERITY_MASK_RECORD,        ENABLE, 4U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncDTCBySeverityMaskRecord         , UDSA_ADS_BOTH },  /*$08*/
    {SEVERITY_INFO_DTC,                  ENABLE, 5u,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncSeverityInformationOfDTC        , UDSA_ADS_BOTH },  /*$09*/
    {FIRST_CONFIRMED_DTC,                ENABLE, 2u,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncFirstConfirmedDTC               , UDSA_ADS_BOTH },  /*$0C*/
    {MOST_RECENT_CONFIRMED_DTC,          ENABLE, 2u,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION   , Udsa_FuncMostRecentConfirmedDTC          , UDSA_ADS_BOTH },  /*$0E*/
    {UDSA_SUBF_END_TABLEROW,            DISABLE, 0u,  DIAG_NO_SESSION                                                                        , NULL                                     , UDSA_ADS_NONE }
};

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ExtractDtc                                                      */
/*Role : Extract Dtc Code and Symptom from Input Buffer                       */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static void Udsa_ExtractDtc(u08 *BufInPtr, u16 *Dtc, u08 *Fault)
{
  *Dtc     = ( (u16)BufInPtr[0] ) << 8;   /*DTC MSB*/
  *Dtc    |= (u16)BufInPtr[1];            /*DTC LSB*/
  *Fault   = BufInPtr[2];                  /* DTCFailureTypeByte*/
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncNumberOfDTCByStatusMask                  $1901              */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncNumberOfDTCByStatusMask(u08 *Data, u16 Length)
{
  u16 NumOfDtc;
  u08 ret_val = SERVICE_OK;

  Diag_Response[2u] = DDMP_STATUS_AVAILABILITY_MASK; 
  /*Norma 07209 ed07 20060601.pdf pag.69*/
  /*Nota: DTCFormatIdentifier sarà settato a ISO15031-6 DTCFormat, zero (0)*/
  /* 0x00 ISO15031-6  DTCFormat                                           */
  /* 0x01 ISO14229-1  DTCFormat                                           */
  /* 0x02 SAEJ1939-73 DTCFormat                                           */
  /* 0x03 ISO11992-4  DTCFormat                                           */
  Diag_Response[3u] = 0u;
  
  NumOfDtc = DDMP_CountAllDtcByMask(&Data[2u]);
  Diag_Response[4u] = (u08)(NumOfDtc >> 8u);
  Diag_Response[5u] = (u08)(NumOfDtc & 0x00FFu);
  
  Diag_Response_Ln = 6U;
    
  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncDTCByStatusMask               $1902                         */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncDTCByStatusMask(u08 *Data, u16 Length)
{
  u16 size;
  u08 ret_val;
  u08 StatusMask;
  u08 numDtc;
  DDMP_Read_Result_t temp_result;

  ret_val = SERVICE_OK;
  temp_result  = DDMP_READ_OK;

  StatusMask = Data[2u];
  size = 1u;

  Diag_Response[2u] = DDMP_STATUS_AVAILABILITY_MASK;

  temp_result = DDMP_ReadAllDtcByMask((u08*)&Diag_Response[3u], SUB_FUNC_02, &StatusMask, &numDtc);

  if(temp_result == DDMP_READ_BUSY)
  {
    ret_val = BUSY_REPEAT_REQUEST;
    Diag_Response_Ln = 3u;
  }
  else
  {
    size += ((u16)numDtc * 4u);
    Diag_Response_Ln = size + UDSA_FIXED_LEN_PROTOCOL;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncDTCSnapshotRecordByDTCNumber        $19 04                  */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncDTCSnapshotRecordByDTCNumber(u08 *Data, u16 Length)
{
  u16 Dtc = 0x0000u;
  u08 FaultSym;
  u08 ret_val;

  DDMP_Snapshot_Event_Num_t SnapNum;
  u08 AddLen = DDMP_NO_DATA_LENGTH;
  DDMP_Read_Result_t temp_result = DDMP_READ_OK;
  ret_val = SERVICE_OK;

  Diag_Response[2U] = Data[2U];      /* DTC MSB           */
  Diag_Response[3U] = Data[3U];      /* DTC LSB           */
  Diag_Response[4U] = Data[4U];      /* Symptom requested */

  Diag_Response_Ln = 6U; /*minimum response length without snapshot*/

  Udsa_ExtractDtc(&Data[2u], &Dtc, &FaultSym);
  
  /* extract snapshot record number */
  SnapNum   = (DDMP_Snapshot_Event_Num_t)Data[5u];

  /* Check se SnapshotNumber è uno tra i valori gestiti (0x00, 0x01, 0xFF) */
  if( (SnapNum == DDMP_FIRST_EVENT ) || (SnapNum == DDMP_LAST_EVENT) || (SnapNum == DDMP_ALL_EVENT) )
  {
    temp_result = DDMP_ReadDtcSnapshotRecord(Dtc, FaultSym, SnapNum, &Diag_Response[4u], &AddLen);

    if(temp_result == DDMP_READ_FAIL)
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
    else
    {
      if((u08)AddLen > 0u)
      {
        //memcpy(&Diag_Response[4u], &buffer_tmp[0u], (u08)AddLen);
        Diag_Response_Ln += (u08)AddLen;
      }
      else
      {
        /*Diag_Response_Ln = 6U*/
      }
    }
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  return (ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncDTCExtendedDataRecordByDTCNumber       $19 06               */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncDTCExtendedDataRecordByDTCNumber(u08 *Data, u16 Length)
{
  u16 Dtc = 0x0000u;
  u08 FaultSym;
  u08 ret_val;

  DDMP_Snapshot_Ext_Num_t ExtDataNum;

  u08 AddLen = DDMP_NO_DATA_LENGTH;
  DDMP_Read_Result_t temp_result = DDMP_READ_OK;
  ret_val = SERVICE_OK;

  Diag_Response[2U] = Data[2U];       /* DTC MSB           */
  Diag_Response[3U] = Data[3U];       /* DTC LSB           */
  Diag_Response[4U] = Data[4U];       /* Symptom requested */

  /* Da cdd FIAT la risposta deve prevedere 5 byte [59 04 DTCcode ] + 1 byte */
  /* [StatusOfDTC] inserito dalla funzione DDMP_ReadDtcExtendedRecord() */

  Diag_Response_Ln = 6U;  /*minimum response length without extended data*/

  Udsa_ExtractDtc(&Data[2u], &Dtc, &FaultSym);

  /* Extract DTCExtendedDataRecordNumber */
  ExtDataNum   = (DDMP_Snapshot_Ext_Num_t)Data[5u];

  if( (ExtDataNum == DDMP_FIRST_EXT_EVENT ) ||  (ExtDataNum == DDMP_ALL_EXT_EVENT) )
  {
    temp_result = DDMP_ReadDtcExtendedRecord(Dtc, FaultSym, ExtDataNum, &Diag_Response[4u], &AddLen);
    if(temp_result == DDMP_READ_FAIL)
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
    else
    {
      if((u08)AddLen > 0u)
      {
        Diag_Response_Ln += (u08)AddLen;
      }
      else
      {
        /*Diag_Response_Ln = 6U*/
      }
    }
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncNumberOfDTCBySeverityMaskRecord          $1907              */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncNumberOfDTCBySeverityMaskRecord(u08 *Data, u16 Length)
{
  u08 NumOfDtc;
  u08 ret_val;
  u08 DTCSeverityMaskRecord[2];
  ret_val = SERVICE_OK;

  DDMP_Read_Result_t temp_result = DDMP_READ_OK;

  Diag_Response_Ln = 4U;

  DTCSeverityMaskRecord[0] = Data[2];          /* Estraggo la SeverityMask */
  DTCSeverityMaskRecord[1] = Data[3];          /* Estraggo la StatusMask   */



  if( (DTCSeverityMaskRecord[0] & DDMP_INVALID_SEVERITY_MASK) == 0U)      /* Controllo se il valore di SeverityMask è tra quelli consentiti */
  {
    /* FIAT 250: Norma 07209 pag.69 */

    Diag_Response[2] = DDMP_STATUS_AVAILABILITY_MASK;

    /*Norma 07209 ed07 20060601.pdf pag.69*/
    /*Nota: DTCFormatIdentifier sarà settato a ISO15031-6 DTCFormat, zero (0)*/
    /* 0x00 ISO15031-6  DTCFormat                                           */
    /* 0x01 ISO14229-1  DTCFormat                                           */
    /* 0x02 SAEJ1939-73 DTCFormat                                           */
    /* 0x03 ISO11992-4  DTCFormat                                           */
    Diag_Response[3] = 0x00u;

	/* In "buffer_tmp" si copiano DTC in EEPROM  che soddisfano la StatusMask */
    temp_result = DDMP_ReadAllDtcByMask(NULL , SUB_FUNC_07, DTCSeverityMaskRecord, &NumOfDtc);

    if(temp_result == DDMP_READ_BUSY)
    {
      ret_val = BUSY_REPEAT_REQUEST;
    }
    else
    {
      /* read ok */
      Diag_Response[4] = 0x00u;                /* Numero di DTC che soddisfano la DTCSeverityMaskRecord MSB */
      Diag_Response[5] = NumOfDtc;            /* Numero di DTC che soddisfano la DTCSeverityMaskRecord LSB */
      Diag_Response_Ln = 6u;
    }
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncDTCBySeverityMaskRecord                $1908                */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncDTCBySeverityMaskRecord(u08 *Data, u16 Length)
{
  u16 size;
  u08 ret_val;
  u08 DTCSeverityMaskRecord[2];
  u08 numDtc;
  DDMP_Read_Result_t temp_result = DDMP_READ_OK;

  Diag_Response_Ln = 3U;
  ret_val = SERVICE_OK;

  DTCSeverityMaskRecord[0] = Data[2];          /* Estraggo la SeverityMask */
  DTCSeverityMaskRecord[1] = Data[3];          /* Estraggo la StatusMask   */


  /* Controllo se il valore di SeverityMask è tra quelli consentiti */
  if( (DTCSeverityMaskRecord[0] & DDMP_INVALID_SEVERITY_MASK) == 0U)
  {
    /* Norma 07209 pag.69 */
    Diag_Response[2] = DDMP_STATUS_AVAILABILITY_MASK;
    size = 3U;
    temp_result = DDMP_ReadAllDtcByMask(&Diag_Response[3], SUB_FUNC_08, DTCSeverityMaskRecord, &numDtc); /* In "buffer_tmp" si copiano DTC in EEPROM  che soddisfano la StatusMask */
    if(temp_result == DDMP_READ_BUSY)
    {
      ret_val = BUSY_REPEAT_REQUEST;
    }
    else
    {
      size += ((u16)numDtc * 6U);                       /* numDtc contiene il numero di DTC presenti in EEPROM, viene ricalcolata la size */
      Diag_Response_Ln = size;
    }
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncSeverityInformationOfDTC              $1909                 */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncSeverityInformationOfDTC(u08 *Data, u16 Length)
{
  u16 Dtc = 0x00U;
  u08 FaultSym;
  u08 ret_val;
  u08 buffer_tmp[2];


  DDMP_Read_Result_t temp_result = DDMP_READ_OK;

  Diag_Response_Ln = 3U;
  ret_val = SERVICE_OK;

  Udsa_ExtractDtc(&Data[2], &Dtc, &FaultSym);

  /* Norma 07209 pag.69 */
  Diag_Response[2] = DDMP_STATUS_AVAILABILITY_MASK;
 
  temp_result = DDMP_ReportDTCSeverity(Dtc, FaultSym, buffer_tmp);

  if(temp_result == DDMP_READ_FAIL)
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  else
  {
    Diag_Response[3] = buffer_tmp[0];          /* Severity      */
    Diag_Response[4] = DDMP_FUNCTIONAL_UNIT;
    Diag_Response[5] = Data[2];                /* DTC MSB       */
    Diag_Response[6] = Data[3];                /* DTC LSB       */
    Diag_Response[7] = FaultSym;               /* Fault Symptom */
    Diag_Response[8] = buffer_tmp[1];          /* StausByte     */
    Diag_Response_Ln = 9U;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncFirstConfirmedDTC                     $190C                 */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncFirstConfirmedDTC(u08 *Data, u16 Length)
{
  u16 size;
  u08 ret_val;
  u08 buffer_tmp[4u]; /*Length + DTC MSB + DTC LSB + Fault Symptom + StausByte*/

  size = 1u; /* 0x00u */   /*FRAT - ci perdevamo un byte*/
  ret_val = SERVICE_OK;

  /* Norma 07209 pag.69 */
  Diag_Response[2] = DDMP_STATUS_AVAILABILITY_MASK;

  DDMP_ReportFirstLastConfirmedDtc (SUB_FUNC_0C, buffer_tmp);

  size += (u16)buffer_tmp[0u];
  memcpy(&Diag_Response[3u], &buffer_tmp[1u], size);
  Diag_Response_Ln = size + UDSA_FIXED_LEN_PROTOCOL;

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_FuncMostRecentConfirmedDTC                $190E                 */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_FuncMostRecentConfirmedDTC(u08 *Data, u16 Length)
{
  u16 size;
  u08 ret_val;
  u08 buffer_tmp[4u]; /*Length + DTC MSB + DTC LSB + Fault Symptom + StausByte*/

  size = 1u;   /*FRAT - ci perdevamo un byte*/
  ret_val = SERVICE_OK;

  /* Norma 07209 pag.69 */
  Diag_Response[2] = DDMP_STATUS_AVAILABILITY_MASK;

  DDMP_ReportFirstLastConfirmedDtc (SUB_FUNC_0E, buffer_tmp);

  size += (u16)buffer_tmp[0u];
  memcpy(&Diag_Response[3u], &buffer_tmp[1u], size);
  Diag_Response_Ln = size + UDSA_FIXED_LEN_PROTOCOL;

  return(ret_val);
}


#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDSA_DtcConfig.c) ______________________________________*/
