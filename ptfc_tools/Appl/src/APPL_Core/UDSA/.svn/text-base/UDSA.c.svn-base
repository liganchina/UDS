/********************************************************************************/
/* @F_PROJECT:          TTM 636 FIAT                                            */
/* F_NAME:              UDSA.c                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/07/2012                                              */
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
| FRAT         Francesco TALARICO        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 23/12/2012  0.1  MAD     First release
| 09/05/2013  0.2  GIL     Iveco porting
| 15/10/2013  0.3  GIL     Manage differences between physic and functional diagnosis
| 13/03/2014  1.0  GIL     Finally remove UDS subfunction table, managed in UDSA_Subfunction_t
|                          table type adding field AdSch
| 13/10/2015  1.2  FRAT    Issues #1875, 1876 - Platform Alignment
*/

/* !!! NOT MOVE !!! */
#define UDSA_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

u08                             UDSA_ServiceWithSubFunction;
bool                            UDSA_SuppressPosRspMsgIndicationBit;
u08 const __far                 *ptrAddressBootVersion;
UDSA_CommunicationControlType_t UDSA_CommunicationControlType;
UDSA_AddressingScheme_t         UDSA_AddresScheme;
u08                             UDSA_FoundedSubf;


UDSA_SecurityAccess_t ECU_SecAccessSts;
u08 UDSA_FingerCount; /* 0u: enter Programming session;
                         1u: Write ApplSw fingerprint;
                         2u: Write Data fingerprint after ApplSw one has been written. */
UDSA_VINSecAccess_t VIN_SecAccessSts;


/*______ E X T E R N A L - D A T A ___________________________________________*/

extern u08 UDSA_SecAccInProgress;
extern __no_init u16 UDSA_ApplKey;


/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______   L O C A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

bool Udsa_CheckSPRMIbit(u08 *data);
u08 Udsa_CheckSubfunctionSupported(u16 ServIdx, u08 SubF);

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name : UDSA_Init                                                            */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void UDSA_Init(void)
{
  UDSA_SetSessionType(UDSA_DEFAULT_SESSION); //DF 30.01.2015

  UDSA_CommunicationControlType = UDSA_CCT_ENRX_ENTX;


  UDSA_AddresScheme = UDSA_ADS_NONE;
  UDSA_FoundedSubf = 0U;

  UDSA_POST_INIT()

  UDSA_RESTORE_COM_CTRL(NETP_CCT_ALL_MSG)
}


/*----------------------------------------------------------------------------*/
/*Name : UDSA_Decoding                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void UDSA_Decoding(u08 *Data, u16 Length)
{
  u08 diagnosis_response = SERVICE_OK;
  u08 Service;

  TLRP_SetSlow(UDSA_S3ServerDiagAct_timer);


  Diag_Response[0] = Data[0] + 0x40U;         // Positive Response Service Id
  Service = Data[0];

  diagnosis_response = UDSA_DiagnosticServicesResponse(&Data[0], Length );

/*Check to suppress negative response in functional addressing*/
  if (((UDSA_AddresScheme == UDSA_ADS_FUNCT) && (UDSA_SUPPRESS_NEG_RESP_MSG(diagnosis_response))) || (diagnosis_response == NO_RESPONSE))
  {
    /* functional */
    /*negative response shall not be transmitted*/
    TP_ResetTimerDiag();
  }
  else
  {
    if((diagnosis_response == SERVICE_OK) && (UDSA_SuppressPosRspMsgIndicationBit))
    {
      /* If Suppress Positive Response Message Indication Bit set,
       * reset diagnose timeout (Timer_T_Diag)! This allow receive new
       * diagnose request */
      TP_ResetTimerDiag();
    }
    else
    {
      if  (diagnosis_response != SERVICE_OK)
      {
        Diag_Response[0] = 0x7FU;               /* negativeResponse Service ID */
        Diag_Response[1] = Service;             /* Request Service Id          */
        Diag_Response[2] = diagnosis_response;  /* Negative Response Code      */
        Diag_Response_Ln = 3U;
      }
      else
      {
        /* positiveResponse Service ID */
        ;
      }

      /* activate Transport Protocol to manage response*/
      TP_RunTpTx();
    }
  }
  return;
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_DiagnosticServicesResponse                                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 UDSA_DiagnosticServicesResponse(u08 *Data, u16 Length )
{
  u08 Service;
  u08 Subfunction;
  u16 ServIndex;

  u08 ret_val;

  ret_val = SERVICE_OK;

  Service = Data[0];

  ServIndex = UDSA_BinarySearch2((u16) Service, MAX_NUM_SERVICE, UDSA_Diagnostic_Services);

  UDSA_ServiceWithSubFunction = UDSA_Diagnostic_Services[ServIndex].SuppSubFunc;

  /* if service is with subfunction */
  if(UDSA_ServiceWithSubFunction)
  {
    /* check if subfunction positive message indication bit is set
       * and save value in UDSA_SuppressPosRspMsgIndicationBit. If positive clean it!!! */
    UDSA_SuppressPosRspMsgIndicationBit = Udsa_CheckSPRMIbit(&Data[1]);
    Subfunction = Data[1];
  }
  else
  {
    UDSA_SuppressPosRspMsgIndicationBit = FALSE;
  }

  /* get addressing scheme (functional, physical)*/
  UDSA_AddresScheme = (UDSA_AddressingScheme_t) TP_GetAddressingScheme();

  /* check if service ID supported : P1*/
  if ((ServIndex >= MAX_NUM_SERVICE) || (ServIndex == NO_SERVICE) || (UDSA_Diagnostic_Services[ServIndex].Enable != ENABLE))
  {
    ret_val = SERVICE_NOT_SUPPORTED;
  }
  else
  {
    /* now check if service supported in current session */
    if ((UDSA_Diagnostic_Services[ServIndex].Session & UDSA_DiagSession) != 0u)
    {
      if(((UDSA_Diagnostic_Services[ServIndex].RxDL != Length) && (UDSA_Diagnostic_Services[ServIndex].RxDL != 0U)) || (Length < 2U))
      {
              /*FRAT - NOTA: non inserire il controllo Length < 2U in boot altrimenti fallirebbe il servizio 37*/
        /* minimum number of byte not present in the request */
        ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
      }
      else
      {
        /* P3 -F3  */
        if(UDSA_ServiceWithSubFunction)
        {
          /* P4 - F4 */
          ret_val = Udsa_CheckSubfunctionSupported(ServIndex, Subfunction);
        }
        else
        {
          /* P5 - F5 */
          ret_val = SERVICE_OK;
        }

        if(ret_val == SERVICE_OK)
        {
          /* subfunction call */
          if (UDSA_Diagnostic_Services[ServIndex].Callback != NULL)
          {
            ret_val = (UDSA_Diagnostic_Services[ServIndex].Callback( Data, Length ));
          }
        }
      }
    }
    else
    {
      ret_val = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
    }
      
  }

  return ret_val;
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_CheckSubfunctionSupported                                       */
/*Role : Check i f a subfunction is supported in this address scheme          */
/*       input:                                                               */
/*       ServIdx = index of service in table (UDSA_Diagnostic_Services)       */
/*       SubF    = subfunction (received by UDS)                              */
/*       output:                                                              */
/*       ret_val = positive/negative or no response code for UDS management   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 Udsa_CheckSubfunctionSupported(u16 ServIdx, u08 SubF)
{
  u08 idx;
  u08 ret_val;
  const UDSA_Subfunction_t *SubFunctionTablePtr;
  u08 breakLoop;

  SubFunctionTablePtr = (const UDSA_Subfunction_t*) UDSA_Diagnostic_Services[ServIdx].PntSubF;
  
  breakLoop = FALSE;

  for(idx = 0U; idx < MAX_NUM_SUBFUNCTION; idx++)
  {

    /* check if subfunction is supported in this address scheme */
    if(SubFunctionTablePtr->SubFunction == SubF)
    {
      if((SubFunctionTablePtr->AdSch) & (UDSA_AddresScheme))
      {
        if(SubFunctionTablePtr->Enable == ENABLE)
        {
          ret_val = SERVICE_OK;
        }
        else
        {
          ret_val = SUBFUNCTION_NOT_SUPPORTED;
        }
      }
      else
      {
        ret_val = NO_RESPONSE;
      }

      UDSA_FoundedSubf = idx;
      breakLoop = TRUE;
    }
    else if(SubFunctionTablePtr->SubFunction == UDSA_SUBF_END_TABLEROW)
    {
      ret_val = SUBFUNCTION_NOT_SUPPORTED;
      UDSA_FoundedSubf = 0U;
      breakLoop = TRUE;
    }
    else
    {
      UDSA_FoundedSubf = 0U;
      ret_val = NO_RESPONSE;
    }

    SubFunctionTablePtr++;

    if (breakLoop)
    {
      break;
    }
  }
  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_CheckDiagSessionAct                                             */
/*Role : Manage S3Server Timeout                                              */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void UDSA_CheckDiagSessionAct(void)
{
  UDSA_SetSessionType(UDSA_DEFAULT_SESSION); //DF 30.01.2015

  VIN_SecAccessSts = SEC_ACC_VIN_LOCKED;
  ECU_SecAccessSts = SEC_ACC_ECU_LOCKED;
  UDSA_SecAccInProgress = FALSE;
  /* Restore control DTC setting */
  DDMP_SetControlDtcSetting(DDMP_DTC_ENABLE);
  /* Restore communication control service */
  UDSA_RESTORE_COM_CTRL(NETP_CCT_ALL_MSG)

  //  UDSA_SESSION_TIMEOUT_ELAPSED TODO FRAT - da verificare
}


/*----------------------------------------------------------------------------*/
/*Name : UDSA_GetSecAccessState                                               */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_SecurityAccess_t UDSA_GetSecAccessState(void)
{
  return (ECU_SecAccessSts);
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_GetSuppPosRspMsgIndBit                                          */
/*Role : Get suppress positive message response indication bit                */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool UDSA_GetSuppPosRspMsgIndBit(void)
{
  return(UDSA_SuppressPosRspMsgIndicationBit);
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_BinarySearch                                                    */
/*Role :       binsearch: find word in tab[0]...tab[n-1]                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
u16 UDSA_BinarySearch(u16 pid, u08 num_elem, const UDSA_CmdByIdentifier_Service_t struct_pnt[])
{
  u08  loIdx;
  u08  hiIdx;
  u08  idx;
  u16  ret_val;
  u08 breakLoop;

  /* Init look-up */
  ret_val = 0xffff;
  loIdx = 0U;
  hiIdx = num_elem - 1U;
  
  breakLoop = FALSE;

  do
  {
    idx = (u08)(((u16)((u16)hiIdx + (u16)loIdx)) >> 1);

    /* Check for matching element */
    if(struct_pnt[idx].DID == pid)
    {
      /* Bingoooo :) */
      ret_val = idx;
      breakLoop = TRUE;
    }
    /* Determine which half shall be taken */
    if (pid < struct_pnt[idx].DID)
    {
      /* Avoid use of signed types */
      if(idx == 0U)
      {
        breakLoop = TRUE;
      }
      hiIdx = (u08)(idx - 1U);
    }
    else
    {
      /* Message 'greater' than service instance: Use upper half of interval... */
      loIdx = (u08)(idx + 1U);
    }
    
    if (breakLoop)
    {
      break;
    }
  }
  while (loIdx <= hiIdx);

  /* return the search result */
  return ret_val;
}


u16 UDSA_BinarySearch2(u16 pid, u08 num_elem, const UDSA_Diagnostic_Services_t struct_pnt[])
{
  u08  loIdx;
  u08  hiIdx;
  u08  idx;
  u16  ret_val;
  u08 breakLoop;

  /* Init look-up */
  ret_val = 0xffff;
  loIdx = 0U;
  hiIdx = num_elem - 1U;
  
  breakLoop = FALSE;

  do
  {
    idx = (u08)(((u16)((u16)hiIdx + (u16)loIdx)) >> 1U);

    /* Check for matching element */
    if(struct_pnt[idx].Service == pid)
    {
      /* Bingoooo :) */
      ret_val = idx;
      breakLoop = TRUE;
    }
    /* Determine which half shall be taken */
    if (pid < struct_pnt[idx].Service)
    {
      /* Avoid use of signed types */
      if(idx == 0U)
      {
        breakLoop = TRUE;
      }
      hiIdx = (u08)(idx - 1U);
    }
    else
    {
      /* Message 'greater' than service instance: Use upper half of interval... */
      loIdx = (u08)(idx + 1U);
    }
    
    if (breakLoop)
    {
      break;
    }
  }
  while (loIdx <= hiIdx);

  /* return the search result */
  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_CheckSPRMIbit                                                   */
/*Role : check if "suppress positive message indication bit" is set           */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool Udsa_CheckSPRMIbit(u08 *data)
{
  bool ret_val;

  if(*data & UDSA_SUP_POS_RSP_BIT)
  {
    /* check if "suppress positive message indication bit" is set */
    *data &= (~UDSA_SUP_POS_RSP_BIT);
    ret_val = TRUE;
  }
  else
  {
    ret_val = FALSE;
  }

  return(ret_val);
}

#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDS_Config.c) ________________________________________________*/

