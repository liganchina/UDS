/********************************************************************************/
/* @F_PROJECT:          TTM 636 FIAT                                            */
/* F_NAME:              UDSA_Config.c                                           */
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
| CDO          Clementina D'Onofrio      TTech
| DAF          Davide Fogliano           Polimatica
| FRAT         Francesco TALARICO        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 23/12/2012  0.1  MAD     First release
| 09/05/2013  0.2  GIL     Iveco porting
| 24/07/2013  0.3  CDO     Read/Write DID (Identification & Variant Coding)
| 15/10/2013  0.4  GIL     Manage differences between fhisical and functional diagnosis
| 13/03/2014  1.0  GIL     Finally remove UDS subfunction table, managed in UDSA_Subfunction_t
|                          table type adding field AdSch
| 26/03/2015  1.1  DAF     Change sessions information to bitwise byte from byte vector 
| 25/06/2015  1.2  FRAT    Ferrari F151M porting
*/

/* !!! NOT MOVE !!! */
#define UDSA_CONFIG_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ S H A R E D - D A T A _______________________________________________*/

#define START_FROM_DWNLOAD_APPL_REQ     ((u16)0x55AAU)
#define START_FROM_RESET                ((u16)0x0000U)

#pragma dataseg = SHARED_RAM
  __no_init u16 BOOT_StartMode;
  __no_init u08 SHREDRAM_SuppPosRspMsgIndBit; /* To use this variable set optimize = none */
#pragma dataseg = default

/*______ E X T E R N A L - D A T A ___________________________________________*/
extern UDSA_CommunicationControlType_t UDSA_CommunicationControlType;

extern const UDSA_Subfunction_t               UDSA_ReadDTCInformation[MAX_NUM_DTC_SERVICE];        /*Request message sub-function parameter */
extern const UDSA_CmdByIdentifier_Service_t   UDSA_ReadDataByIdentifier[MAX_NUM_DID_READ];         /* 40 (22 boot - 18 app) */
extern const UDSA_CmdByIdentifier_Service_t   UDSA_WriteDataByIdentifier[MAX_NUM_DID_WRITE];       /* 2E */
extern const UDSA_CmdByIdentifier_Service_t   UDSA_IOControlByIdentifier[MAX_NUM_IOCTRL];

extern const UDSA_CmdByIdentifier_Service_t UDSA_StartRoutineByIdentifier[MAX_NUM_ROUTINE_START];  /* 31 01 */
extern const UDSA_CmdByIdentifier_Service_t UDSA_StopRoutineByIdentifier[MAX_NUM_ROUTINE_STOP];    /* 31 02 */
extern const UDSA_CmdByIdentifier_Service_t UDSA_RoutineResultByIdentifier[MAX_NUM_ROUTINE_RESULT];/* 31 03 */

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define APPL_KEY_VAL                    0x55AAU
#define UDSA_IO_MIN_LEN_PROTOCOL             4U
#define UDSA_IO_LEN_SHORT_ADJUST             5U
#define UDSA_N_MRDI                         10U
#define VIN_RSA_REV_POLY                0x1929U

#define UDSA_PROGR_SES_LOW_BAT_THRES   ((u16) 9900u)  /*  9.9V thresold - Reali su connettore  9,8V Requisito della 07284-01 4.1.2.1 nota 17 10.0V */
#define UDSA_PROGR_SES_HIGH_BAT_THRES  ((u16)14900u)  /* 14.9V thresold - Reali su connettore 14,7V Requisito della 07284-01 4.1.2.1 nota 17 14.5V */

#define UDSA_ADDR_LEN_FORMAT_ID        0x13U  /* Servizio 23 (ReadMemoryByAddress) */

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

const UDSA_Subfunction_t               UDSA_Security_Access[MAX_NUM_SEC_ACC_SERVICE];
const UDSA_Subfunction_t               UDSA_Communication_Ctrl[MAX_NUM_COM_CTRL_SERVICE];
const UDSA_Subfunction_t               UDSA_TesterPresent[MAX_NUM_TEST_PRES_SERVICE];
const UDSA_Subfunction_t               UDSA_ControlDTcSetting[MAX_NUM_CTRL_DTC_SERVICE];
const UDSA_Subfunction_t               UDSA_RoutineCtrlResp[MAX_NUM_ROUTINE_CTRL_SERVICE];
const UDSA_Subfunction_t               UDSA_Diagnostic_Sessions[MAX_NUM_SESSION];
const UDSA_Subfunction_t               UDSA_Diagnostic_Reset[MAX_NUM_RESET_SERVICE];

u08 UDSA_SecAccInProgress;

//u08 UDSA_MirrorApplSwId[UDSA_LN_APP_SW_IDENTIFICATION]; /* used in Bitron session to unlock fingerprints */
static u32 UDSA_LocalKey;
static u08 Udsa_SecAccess_CounterOfAttempt = 0U;
DRVD_RStatus_t UDSA_EraseEpromResult;

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
void UDSA_ServiceConfigInit(void);

/* Session */
static u08 Udsa_DefaultSessionResponse(u08 *Data, u16 Length);
static u08 Udsa_ProgrammingSessionResponse(u08 *Data, u16 Length);
static u08 Udsa_ExtendedSessionResponse(u08 *Data, u16 Length);
static u08 Udsa_EOLSessionResponse(u08 *Data, u16 Length);
static u08 Udsa_SystemSupplierSessionResponse(u08 *Data, u16 Length);

/* Services */
static u08 Udsa_StartDiagnosticSessionResponse(u08 *Data, u16 Length);
static u08 Udsa_EcuResetResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplClearDiagnosticInformationResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplReadDtcResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplReadDataByIdentifierResponse(u08 *Data, u16 Length);
static u08 Udsa_ReadMemoryByAddressResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplSecurityAccessResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplCommunicationControl(u08 *Data, u16 Length);
static u08 Udsa_ApplWriteDataByIdentifierResponse(u08 *Data, u16 Length);
static u08 Udsa_IOControlByIdentifierResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplRoutineControlResponse(u08 *Data, u16 Length);
static u08 ApplRequestDownloadResponse(u08 *Data, u16 Length);
static u08 ApplRequestTransfertDataResponse(u08 *Data, u16 Length);
static u08 ApplRequestTransfertExitResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplTesterPresentResponse(u08 *Data, u16 Length);
static u08 Udsa_ApplControlDtcSettingResponse(u08 *Data, u16 Length);
static u08 UDSA_ApplHardResetResponse(u08 *Data, u16 Length);


static u08 Udsa_EnableRxAndEnableTx(u08 *Data, u16 Length);
static u08 Udsa_EnableRxAndDisableTx(u08 *Data, u16 Length);

#if 0
  static u08 Udsa_DisableRxAndEnableTx(u08 *Data, u16 Length);
  static u08 Udsa_DisableRxAndDisableTx(u08 *Data, u16 Length);
#endif

static u08 Udsa_VINRequestSeed(u08 *Data, u16 Length); 
static u08 Udsa_VINSendKey(u08 *Data, u16 Length);

static uint32_t SeedKeyVIN3 (uint32_t seed);


static void Udsa_SetCommCtrlTypeTx(NETP_ComType_t valnew);
static void Udsa_SetCommCtrlTypeRx(NETP_ComType_t valnew);
static void Udsa_ResetCommCtrlTypeTx(NETP_ComType_t valnew);

#if 0
  static void Udsa_ResetCommCtrlTypeRx(NETP_ComType_t valnew);
#endif

static u08 Udsa_ControlDTCSettingON(u08 *Data, u16 Length);
static u08 Udsa_ControlDTCSettingOFF(u08 *Data, u16 Length);

static u08 Udsa_ApplStartRoutineCtrlResp(u08 *Data, u16 Length);
static u08 Udsa_ApplStopRoutineCtrlResp(u08 *Data, u16 Length);
static u08 Udsa_ApplRequestRoutinResultCtrlResp(u08 *Data, u16 Length);

/* Utility Functions */
void UDSA_BitronUnlockFingerInit(void);

/********************************************************************************************************************************************/
/*                                               SERVICES                                                                                   */
/********************************************************************************************************************************************/
const UDSA_Diagnostic_Services_t UDSA_Diagnostic_Services[MAX_NUM_SERVICE] =
{
/* +----------+------+---------+------+------------------------------------------------------------------------------------------+-------------------------------------------------+---------------------------+
   |  Service |  En  |  SubF   | RxDL |                           Session                                                        |            Callback Function                    |    Subfunction pointer    |
   |          |      |         |      |                                                                                          |                                                 |                           |
   +----------+------+---------+------+------------------------------------------------------------------------------------------+-------------------------------------------------+---------------------------*/
  {     0x10U, ENABLE,  TRUE,     2U,  DIAG_ALL_SESSION                                                                            , Udsa_StartDiagnosticSessionResponse         , UDSA_Diagnostic_Sessions},
  {     0x11U, ENABLE,  TRUE,     2U,  DIAG_DEFAULT_SESSION | DIAG_PROGRAMMING_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION     , Udsa_EcuResetResponse                       , UDSA_Diagnostic_Reset   },
  {     0x14U, ENABLE,  FALSE,    4U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION    | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION     , Udsa_ApplClearDiagnosticInformationResponse , NULL                    },
  {     0x19U, ENABLE,  TRUE,     0U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION    | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION     , Udsa_ApplReadDtcResponse                    , UDSA_ReadDTCInformation },
  {     0x22U, ENABLE,  FALSE,    0U,  DIAG_ALL_SESSION                                                                            , Udsa_ApplReadDataByIdentifierResponse       , NULL                    },
  {     0x23U, ENABLE,  FALSE,    0U,  DIAG_SUPPL_SESSION                                                                          , Udsa_ReadMemoryByAddressResponse            , NULL                    },
  {     0x27U, ENABLE,  TRUE,     0U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                               , Udsa_ApplSecurityAccessResponse             , UDSA_Security_Access    },
  {     0x28U, ENABLE,  TRUE,     3U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                               , Udsa_ApplCommunicationControl               , UDSA_Communication_Ctrl },
  {     0x2EU, ENABLE,  FALSE,    0U,  DIAG_ALL_SESSION                                                                            , Udsa_ApplWriteDataByIdentifierResponse      , NULL                    },
  {     0x2FU, ENABLE,  FALSE,    0U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                               , Udsa_IOControlByIdentifierResponse          , NULL                    },
  {     0x31U, ENABLE,  TRUE,     0U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                               , Udsa_ApplRoutineControlResponse             , UDSA_RoutineCtrlResp    },
  {     0x34U, ENABLE,  FALSE,    9U,  DIAG_NO_SESSION                                                                             , ApplRequestDownloadResponse                 , NULL                    },
  {     0x36U, ENABLE,  FALSE,    0U,  DIAG_NO_SESSION                                                                             , ApplRequestTransfertDataResponse            , NULL                    },
  {     0x37U, ENABLE,  FALSE,    1U,  DIAG_NO_SESSION                                                                             , ApplRequestTransfertExitResponse            , NULL                    },
  {     0x3EU, ENABLE,  TRUE,     2U,  DIAG_ALL_SESSION                                                                            , Udsa_ApplTesterPresentResponse              , UDSA_TesterPresent      },
  {     0x85U, ENABLE,  TRUE,     2U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                               , Udsa_ApplControlDtcSettingResponse          , UDSA_ControlDTcSetting  }
};

/********************************************************************************************************************************************/
/*                                          DIAGNOSTIC SESSIONS CONTROLS                                                                    */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_Diagnostic_Sessions[MAX_NUM_SESSION] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                        |             Callback Function        | diag.scheme   |
   |    destinazione          |      |      |                      provenienza (dove sono ora)                             |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { UDSA_DEFAULT_SESSION,      ENABLE,  2U,  DIAG_ALL_SESSION                                                                , Udsa_DefaultSessionResponse        , UDSA_ADS_BOTH },
  { UDSA_PROGRAMMING_SESSION,  ENABLE,  2U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                 , Udsa_ProgrammingSessionResponse    , UDSA_ADS_PHYS },
  { UDSA_EXTENDED_SESSION,     ENABLE,  2U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                 , Udsa_ExtendedSessionResponse       , UDSA_ADS_BOTH },
  { UDSA_EOL_SESSION,          ENABLE,  2U,  DIAG_DEFAULT_SESSION | DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                 , Udsa_EOLSessionResponse            , UDSA_ADS_BOTH },
  { UDSA_SUPPL_SESSION,        ENABLE,  2U,  DIAG_DEFAULT_SESSION | DIAG_SUPPL_SESSION                                       , Udsa_SystemSupplierSessionResponse , UDSA_ADS_BOTH },
  { UDSA_SUBF_END_TABLEROW,    DISABLE, 0u,  DIAG_NO_SESSION                                                                 , NULL                               , UDSA_ADS_NONE }
};


/********************************************************************************************************************************************/
/*                                               ECU RESET                                                                                  */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_Diagnostic_Reset[MAX_NUM_RESET_SERVICE] =
{
/* +--------------------------+------+------+----------------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                                  |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                                        |                                      | (phys. funct  |
   +--------------------------+------+------+----------------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { HARD_RESET,                ENABLE,  2U,  DIAG_DEFAULT_SESSION | DIAG_PROGRAMMING_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION , UDSA_ApplHardResetResponse          , UDSA_ADS_BOTH },
  { UDSA_SUBF_END_TABLEROW,   DISABLE,  0u,  DIAG_NO_SESSION                                                                         , NULL                                , UDSA_ADS_NONE }
};

/********************************************************************************************************************************************/
/*                                               COMMUNICATION CONTROL                                                                      */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_Communication_Ctrl[MAX_NUM_COM_CTRL_SERVICE] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                        |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                              |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { UDSA_CCT_ENRX_ENTX,       ENABLE,   3U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                 , Udsa_EnableRxAndEnableTx            , UDSA_ADS_BOTH },
  { UDSA_CCT_ENRX_DISTX,      ENABLE,   3U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                 , Udsa_EnableRxAndDisableTx           , UDSA_ADS_BOTH },
/*{ UDSA_CCT_DISRX_ENTX,      DISABLE,  3U,  DIAG_NO_SESSION                                                               , Udsa_DisableRxAndEnableTx           , UDSA_ADS_PHYS },*/
/*{ UDSA_CCT_DISRX_DISTX,     DISABLE,  3U,  DIAG_NO_SESSION                                                               , Udsa_DisableRxAndDisableTx          , UDSA_ADS_PHYS },*/
  { UDSA_SUBF_END_TABLEROW,   DISABLE,  0u,  DIAG_NO_SESSION                                                               , NULL                                , UDSA_ADS_NONE }
};

/********************************************************************************************************************************************/
/*                                                  SECURITY ACCESS                                                                         */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_Security_Access[MAX_NUM_SEC_ACC_SERVICE] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                        |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                              |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { ACCES_MODE_PROG_REQSEED,  ENABLE,  2U,  DIAG_NO_SESSION                                                                , NULL                                , UDSA_ADS_PHYS },
  { ACCES_MODE_PROG_SENDKEY,  ENABLE,  6U,  DIAG_NO_SESSION                                                                , NULL                                , UDSA_ADS_PHYS },
  { ACCES_MODE_VIN_REQSEED,   ENABLE,  2U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                  , Udsa_VINRequestSeed                 , UDSA_ADS_PHYS },
  { ACCES_MODE_VIN_SENDKEY,   ENABLE,  6U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                  , Udsa_VINSendKey                     , UDSA_ADS_PHYS },
  { UDSA_SUBF_END_TABLEROW,   DISABLE, 0u,  DIAG_NO_SESSION                                                                , NULL                                , UDSA_ADS_NONE }
};



/********************************************************************************************************************************************/
/*                                                  TESTER PRESENT                                                                          */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_TesterPresent[MAX_NUM_TEST_PRES_SERVICE] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                    Session                                                   |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                              |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { ZERO_SUBF,                 ENABLE,  2U,  DIAG_ALL_SESSION                                                                , NULL                                , UDSA_ADS_BOTH },
  { UDSA_SUBF_END_TABLEROW,   DISABLE,  0U,  DIAG_NO_SESSION                                                                 , NULL                                , UDSA_ADS_NONE }
};



/********************************************************************************************************************************************/
/*                                                  CONTROL DTC SETTING                                                                     */
/********************************************************************************************************************************************/
const UDSA_Subfunction_t UDSA_ControlDTcSetting[MAX_NUM_CTRL_DTC_SERVICE] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                        |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                              |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { SET_ON,                    ENABLE,  2U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                   , Udsa_ControlDTCSettingON            , UDSA_ADS_BOTH },
  { SET_OFF,                   ENABLE,  2U,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                   , Udsa_ControlDTCSettingOFF           , UDSA_ADS_BOTH },
  { UDSA_SUBF_END_TABLEROW,   DISABLE,  0U,  DIAG_NO_SESSION                                                                 , NULL                                , UDSA_ADS_NONE }
};


/********************************************************************************************************************************************/
/*                                               ROUTINE CONTROL                                                                            */
/********************************************************************************************************************************************/

const UDSA_Subfunction_t UDSA_RoutineCtrlResp[MAX_NUM_ROUTINE_CTRL_SERVICE] =
{
/* +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------+---------------+
   |       Subfunction        |  En  | RxDL |                               Session                                        |             Callback Function        | diag.scheme   |
   |                          |      |      |                                                                              |                                      | (phys. funct  |
   +--------------------------+------+------+------------------------------------------------------------------------------+--------------------------------------*---------------+*/
  { UDSA_RC_START_ROUTINE,      ENABLE, 4U, DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                  , Udsa_ApplStartRoutineCtrlResp       , UDSA_ADS_PHYS },
  { UDSA_RC_STOP_ROUTINE,       ENABLE, 4U, DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                  , Udsa_ApplStopRoutineCtrlResp        , UDSA_ADS_PHYS },
  { UDSA_RC_REQ_ROUTINE_RES,    ENABLE, 4U, DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                  , Udsa_ApplRequestRoutinResultCtrlResp, UDSA_ADS_PHYS },
  { UDSA_SUBF_END_TABLEROW,    DISABLE, 0U, DIAG_NO_SESSION                                                                , NULL                                , UDSA_ADS_NONE }
};


/*----------------------------------------------------------------------------*/
/*Name : Udsa_StartDiagnosticSessionResponse     $10                          */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_StartDiagnosticSessionResponse(u08 *Data, u16 Length)
{
  u08 Subfunction;
  u08 ret_val = SERVICE_OK;

  Subfunction = Data[1];

  if ((UDSA_Diagnostic_Sessions[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if (UDSA_Diagnostic_Sessions[UDSA_FoundedSubf].Callback != NULL)
    {
      ret_val = (UDSA_Diagnostic_Sessions[UDSA_FoundedSubf].Callback(Data, Length));
    }

    UDSA_SecAccInProgress = FALSE;      // Reset Security Access sequence flag

    Diag_Response[1] = Subfunction;        // diagnosticMode
    Diag_Response[2] = 0x00U;               // P2Can (high byte)
    Diag_Response[3] = 0x32U;               // P2Can (low  byte)
    Diag_Response[4] = 0x01U;               // P2CanExtended (high byte)
    Diag_Response[5] = 0xf4U;               // P2CanExtended (low  byte)
    Diag_Response_Ln = 6U;
/*FRAT - The IO control deactivation is managed by DFCA or DISPA module*/

    if ((ret_val          == SERVICE_OK)            &&
        (UDSA_DiagSession != DIAG_SUPPL_SESSION))
    {
      UDSA_BitronUnlockFingerInit();
    }

    if ((ret_val          == SERVICE_OK)            &&
        (UDSA_DiagSession != DIAG_EOL_SESSION))
    {
      VIN_SecAccessSts = SEC_ACC_VIN_LOCKED;
    }

  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }
  

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_EcuResetResponse                   $11                          */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_EcuResetResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  
  if ((UDSA_Diagnostic_Reset[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if (UDSA_Diagnostic_Reset[UDSA_FoundedSubf].Callback != NULL)
    {
      ret_val = (UDSA_Diagnostic_Reset[UDSA_FoundedSubf].Callback(Data, Length));
    }
  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }


  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplClearDiagnosticInformationResponse $14                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplClearDiagnosticInformationResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u08 ClearStatus;

  if ((Data[1] == 0xFFU) && (Data[2] == 0xFFU) && (Data[3] == 0xFFU))
  {
    ClearStatus = DDMP_ClearAllDtc();

    if (ClearStatus == DDMP_CLEAR_OK)
    {
      Diag_Response_Ln = 1U;
      ret_val = SERVICE_OK;
    }
    else
    {
      ret_val = BUSY_REPEAT_REQUEST;
    }
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplReadDtcResponse               $19                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplReadDtcResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  
  if ((UDSA_ReadDTCInformation[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if (UDSA_ReadDTCInformation[UDSA_FoundedSubf].RxDL != Length)	/*FRAT - inserito controllo sulla lunghezza*/
    {
      ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT; /*nack 13*/
    }
    else
    {
      Diag_Response[1] = Data[1];
      if (UDSA_ReadDTCInformation[UDSA_FoundedSubf].Callback != NULL)
      {
        ret_val = (UDSA_ReadDTCInformation[UDSA_FoundedSubf].Callback(Data,Length));
      }
    }
  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }



  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplReadDataByIdentifierResponse       $22                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplReadDataByIdentifierResponse(u08 *Data, u16 Length)
{
  u16 dataID[UDSA_N_MRDI];
  u16 index;
  u08 ret_val = REQUEST_OUT_OF_RANGE;

  u08 num_RDI, j;

  if( (Length - 1U)%2U != 0U )
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    num_RDI = (u08)(Length - 1U)/2U;

    if(num_RDI <= UDSA_N_MRDI)
    {
      Diag_Resp_MRDI = 0x0000u;

      for(j=0u; (j<num_RDI); j++)
      {
        dataID[j] = ((u16)(Data[1U + 2U*j]))<< 8U | ((u16)(Data[2U + 2U*j]));

        index = UDSA_BinarySearch(dataID[j], MAX_NUM_DID_READ, UDSA_ReadDataByIdentifier);

        if (((index) == NO_SERVICE) || (UDSA_ReadDataByIdentifier[index].DID >= MAX_VAL_DID) || (UDSA_ReadDataByIdentifier[index].Enable != ENABLE))
        {
        }
        else
        {
          if (UDSA_ReadDataByIdentifier[index].AdSch & UDSA_AddresScheme)
          {
            /* DID supported in this address scheme */
            if (((UDSA_ReadDataByIdentifier[index].Session & UDSA_DiagSession) != 0u) && (Diag_Resp_MRDI < TXBUF_LENGTH - 2U))
            {
              Diag_Response[1U + Diag_Resp_MRDI] = Data[1U + 2U*j];
              Diag_Response[2U + Diag_Resp_MRDI] = Data[2U + 2U*j];
              ret_val = (UDSA_ReadDataByIdentifier[index].Callback(Data, Length));
              Diag_Resp_MRDI += (Diag_Response_Ln - 1U);
            }
            else if(Diag_Resp_MRDI >= TXBUF_LENGTH - 2U)
            {
              Diag_Resp_MRDI = 0U;
              ret_val = REQUEST_OUT_OF_RANGE;
              break;
            }
            else
            {
            }
          }
          else
          {
            /* DID NOT supported in this address scheme --> NO RESPONSE */
            ret_val = NO_RESPONSE;
          }
        }
      }

      if(Diag_Resp_MRDI < TXBUF_LENGTH - 2U)
      {
        Diag_Response_Ln = Diag_Resp_MRDI + 1u;
      }
      else
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }

      Diag_Resp_MRDI = 0u; /* reset multi rdi */

    }
    else
    {
    }
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : ApplReadMemoryByAddressResponse        $23                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ReadMemoryByAddressResponse(u08 *Data, u16 Length)
{
  u08 ret_val;
  DRVD_RStatus_t readEeResult;
  u32 memAddress;
  u08 dataSize;
  u16 eepromPageSize;
  
  ret_val = SERVICE_NOT_SUPPORTED;

  /* DATA [1]                   DATA[2]            DATA[3]      DATA[4]            DATA[5]   */
  /* ADDRESS_LENGTH_FORMAT_ID   ADDR_byte2 (MSB)   ADDR_byte1   ADDR_byte0 (LSB)   LEN       */

  /* Data[4] = Memory selection. 0x80 = EEPROM */
  /* Data[7] = Data size */
  /*TODO TIGRE*/
//  if (memcmp(&UDSA_MirrorApplSwId[0u], &EERAM_ApplSwId[0u], UDSA_LN_APP_SW_IDENTIFICATION) == 0u)
//  {
    
    eepromPageSize = EEPP_GetEepromPageSize();
  
    if ((Data[1] == UDSA_ADDR_LEN_FORMAT_ID) && (Data[2] == 0x80U) && (Data[5] <= (u08)eepromPageSize))
    {
      memAddress  = (u32)Data[3] << 8U;
      memAddress |= (u32)Data[4];
      dataSize    = Data[5];

      if((memAddress < EEPP_GetEepromSize()) && (dataSize > 0u))
      {
        DI();
        /* Bloccante, inoltre va chiamata a interrupt disabilitati */
        readEeResult = Eepp_ReadEepromRawNow(&Diag_Response[1], (u16)memAddress, dataSize);
        EI();

        if (readEeResult == MS_OK)
        {
          Diag_Response_Ln = (u16)(1U + dataSize);

          ret_val = SERVICE_OK;
        }
        else
        {
          ret_val = CONDITIONS_NOT_CORRECT; /* Errore in lettura della EEPROM */
        }
      }
      else
      {
        ret_val = REQUEST_OUT_OF_RANGE; /* Lettura oversize */
      }
    }
    else
    {
      ret_val = REQUEST_OUT_OF_RANGE; /* Formato della richiesta non corretto */
    }
//  }
//  else
//  {
//    /* ret_val = CONDITIONS_NOT_CORRECT;  Non è stato eseguito lo sblocco */
//    ret_val = SERVICE_NOT_SUPPORTED;  /* Rispondiamo 0x11 in quanto questo servizio non è supportato nel CDD */
//  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : ApplSecurityAccessResponse             $27                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplSecurityAccessResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

    if ((UDSA_Security_Access[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0U)
    {
      if (UDSA_Security_Access[UDSA_FoundedSubf].RxDL != Length)
      {
        ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT; /*nack 13*/
      }
      else
      {
        if((TLRP_GetSlow(UDSA_SEC_ACC_TOUT)==0x0000U))   /* Timer Unlocked ? */
        {
          Diag_Response[1] = Data[1];
          if ((UDSA_Security_Access[UDSA_FoundedSubf].Callback) != NULL)
          {
            ret_val = (UDSA_Security_Access[UDSA_FoundedSubf].Callback(Data, Length));
          }
        }
        else
        {
          ret_val = REQUIRED_TIME_DELAY_NOT_EXPIRED;
        }
      }
    }
    else
    {
      ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
    }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_VINRequestSeed               $27 05 [$27 0B]                    */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_VINRequestSeed(u08 *Data, u16 Length)
{
  UDSA_NecD Seed;
  u08 ret_val = SERVICE_OK;


  if(UDSA_SecAccInProgress == TRUE)
  {
    UDSA_SecAccInProgress = FALSE;
    Udsa_SecAccess_CounterOfAttempt = 1u;
    ret_val = REQUEST_SEQUENCE_ERROR;
  }
  else
  {

    if (VIN_SecAccessSts == SEC_ACC_VIN_UNLOCKED)
    {    // Se è già unlokata x questo SA, deve rispondere con un SEED = 0x00000000
      Diag_Response[2] = 0x00U;
      Diag_Response[3] = 0x00U;
      Diag_Response[4] = 0x00U;
      Diag_Response[5] = 0x00U;
    }
    else
    {
      UDSA_SecAccInProgress = TRUE;

      Seed.I[0]=TCR06;                                                  // Word meno significativa
      Seed.I[1]=TCR07;  // Word più  significativa /* Bug Fix 7-Z0071 - 7.15.1.9 */

      Seed.L = (u32)(Seed.L + EERAM_RandomSeed);
      EERAM_RandomSeed = Seed.L;

      Diag_Response[5] = Seed.B[0];    /* LSB */
      Diag_Response[4] = Seed.B[1];
      Diag_Response[3] = Seed.B[2];
      Diag_Response[2] = Seed.B[3];    /* MSB */

        Diag_Response_Ln = 6U;

        // Calcola la chiave
        UDSA_LocalKey = SeedKeyVIN3( Seed.L);

      EEPP_WriteData(EEPP_HDL_RandomSeed, NULL);
    }
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_VINSendKey                   $27 06 [$27 0C]                    */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_VINSendKey(u08 *Data, u16 Length)
{
  UDSA_NecD Testerkey;
  u08 ret_val = SERVICE_OK;

  Testerkey.L = 0U;


  if (UDSA_SecAccInProgress == FALSE)
  {
    Udsa_SecAccess_CounterOfAttempt = 1u;
    ret_val = REQUEST_SEQUENCE_ERROR;
  }
  else
  {
    // Acquisizione della chiave inviata dal tester

    Testerkey.B[0] = Data[5];     // LSB
    Testerkey.B[1] = Data[4];
    Testerkey.B[2] = Data[3];
    Testerkey.B[3] = Data[2];     // MSB

    UDSA_SecAccInProgress = FALSE;

    if (Testerkey.L != UDSA_LocalKey)
    {
      if(Udsa_SecAccess_CounterOfAttempt == 0U)
      {
        ret_val = INVALID_KEY;           // Key not valid
      }
      else
      {
        TLRP_SetSlow(UDSA_SEC_ACC_TOUT);
        ret_val = EXCEED_NUMBER_OF_ATTEMPTS;
      }

      Udsa_SecAccess_CounterOfAttempt = 1u;
    }
    else // Controllo chiave OK, VIN Locked / Unlocked
    {
      Udsa_SecAccess_CounterOfAttempt = 0U;

      Diag_Response_Ln = 2U;

      VIN_SecAccessSts = SEC_ACC_VIN_UNLOCKED;
    }
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplCommunicationControl               $28                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplCommunicationControl(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  if ((UDSA_Communication_Ctrl[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if (UDSA_Communication_Ctrl[UDSA_FoundedSubf].Callback != NULL)
    {
      ret_val = (UDSA_Communication_Ctrl[UDSA_FoundedSubf].Callback(Data, Length));
    }

    Diag_Response[1] = Data[1];
    Diag_Response_Ln = 2u;
  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_EnableRxAndEnableTx                            $28 00           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_EnableRxAndEnableTx(u08 *Data, u16 Length)
{
  u08 ret_val;
  u08 Subfunction;
  NETP_ComType_t CctNew;

  /* input parameter check */
  if (( Data[2] > NETP_CCT_NONE_MSG ) && ( Data[2] < NETP_CCT_DIAG_MSG ))
  {
    /* communication type */
    CctNew = (NETP_ComType_t) (Data[2]);
    Subfunction = Data[1];

    /* if previously disabled */
    if(!(UDSA_CommunicationControlType & UDSA_CCT_RXBIT))
    {
      /* Set 3sec. timeout */
      TLRP_SetSlow(UDSA_Timer_Service28);
      NETP_EnableRxTimeout(FALSE);
    }

    UDSA_CommunicationControlType = (UDSA_CommunicationControlType_t)Subfunction;

    Udsa_SetCommCtrlTypeTx(CctNew);
    Udsa_SetCommCtrlTypeRx(CctNew);

    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_EnableRxAndDisableTx                   $28 01                   */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_EnableRxAndDisableTx(u08 *Data, u16 Length)
{
  u08 ret_val;
  u08 Subfunction;
  NETP_ComType_t CctNew;

  /* input parameter check */
  if (( Data[2] > NETP_CCT_NONE_MSG ) && ( Data[2] < NETP_CCT_DIAG_MSG ))
  {
    /* communication type */
    CctNew = (NETP_ComType_t) (Data[2]);
    Subfunction = Data[1];

    /* if previously disabled */
    if(!(UDSA_CommunicationControlType & UDSA_CCT_RXBIT))
    {
      /* Set 3sec. timeout */
      TLRP_SetSlow(UDSA_Timer_Service28);
      NETP_EnableRxTimeout(FALSE);
    }

    UDSA_CommunicationControlType = (UDSA_CommunicationControlType_t)Subfunction;

    Udsa_ResetCommCtrlTypeTx(CctNew);
    Udsa_SetCommCtrlTypeRx(CctNew);

    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}


#if 0
/*----------------------------------------------------------------------------*/
/*Name : Udsa_DisableRxAndEnableTx                   $28 02                   */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_DisableRxAndEnableTx(u08 *Data, u16 Length)
{
  u08 ret_val;
  u08 Subfunction;
  NETP_ComType_t CctNew;

  /* input parameter check */
  if (( Data[2] > NETP_CCT_NONE_MSG ) && ( Data[2] < NETP_CCT_DIAG_MSG ))
  {
    /* communication type */
    CctNew = (NETP_ComType_t) (Data[2]);
    Subfunction = Data[1];

    /* if previously disabled */
    if(!(UDSA_CommunicationControlType & UDSA_CCT_RXBIT))
    {
      /* Set 3sec. timeout */
      TLRP_SetSlow(UDSA_Timer_Service28);
      NETP_EnableRxTimeout(FALSE);
    }

    UDSA_CommunicationControlType = (UDSA_CommunicationControlType_t)Subfunction;

    Udsa_SetCommCtrlTypeTx(CctNew);
    Udsa_ResetCommCtrlTypeRx(CctNew);

    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_DisableRxAndDisableTx                  $28 03                   */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_DisableRxAndDisableTx(u08 *Data, u16 Length)
{
  u08 ret_val;
  u08 Subfunction;
  NETP_ComType_t CctNew;

  /* input parameter check */
  if (( Data[2] > NETP_CCT_NONE_MSG ) && ( Data[2] < NETP_CCT_DIAG_MSG ))
  {
    /* communication type */
    CctNew = (NETP_ComType_t) (Data[2]);
    Subfunction = Data[1];

    /* if previously disabled */
    if(!(UDSA_CommunicationControlType & UDSA_CCT_RXBIT))
    {
      /* Set 3sec. timeout */
      TLRP_SetSlow(UDSA_Timer_Service28);
      NETP_EnableRxTimeout(FALSE);
    }

    UDSA_CommunicationControlType = (UDSA_CommunicationControlType_t)Subfunction;

    Udsa_ResetCommCtrlTypeTx(CctNew);
    Udsa_ResetCommCtrlTypeRx(CctNew);

    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }

  return(ret_val);
}
#endif

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplWriteDataByIdentifierResponse      $2E                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplWriteDataByIdentifierResponse(u08 *Data, u16 Length)
{
  u16 dataID = 0x0000U;
  u16 index;
  u08 ret_val = SERVICE_OK;

  if (Length < 4U)
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    dataID = ((u16)(Data[1]))<< 8U | ((u16)(Data[2]));

    index = UDSA_BinarySearch(dataID, MAX_NUM_DID_WRITE, UDSA_WriteDataByIdentifier);

    if (((index) == NO_SERVICE) || (UDSA_WriteDataByIdentifier[index].DID >= MAX_VAL_DID) || (UDSA_WriteDataByIdentifier[index].Enable != ENABLE))
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
    /* RDI $2023 has got variable length (RxDL = 0) */
    else if ((UDSA_WriteDataByIdentifier[index].RxDL != Length) && (UDSA_WriteDataByIdentifier[index].RxDL != 0U))
    {
      ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
    }
    else
    {
      if (UDSA_WriteDataByIdentifier[index].AdSch & UDSA_AddresScheme)
      {
        /* DID supported in this address scheme */
        
        if ((UDSA_WriteDataByIdentifier[index].Session & UDSA_DiagSession) != 0u)
        {
          Diag_Response[1] = Data[1];
          Diag_Response[2] = Data[2];
          Diag_Response_Ln = 3U ;

          if (UDSA_WriteDataByIdentifier[index].Callback != NULL)
          {
            ret_val = (UDSA_WriteDataByIdentifier[index].Callback(Data, Length));
          }
        }
        else
        {
          ret_val = REQUEST_OUT_OF_RANGE;
        }
        

      }
      else
      {
        /* DID NOT supported in this address scheme --> NO RESPONSE */
        ret_val = NO_RESPONSE;
      }
    }
  }

  return ret_val;
}
/*----------------------------------------------------------------------------*/
/*Name : Udsa_IOControlByIdentifierResponse     $2F                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_IOControlByIdentifierResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  u16 dataID;
  u16 index;
  bool b;

  b = FUNP_IsVehicleSpeedEqZero();

  if(b == TRUE)
  {
    if (Length < UDSA_IO_MIN_LEN_PROTOCOL)
    {
      ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;   /* 0x13 */
    }
    else
    {
      dataID = ((u16)(Data[1]))<< 8U | ((u16)(Data[2]));

      index = UDSA_BinarySearch(dataID, MAX_NUM_IOCTRL, UDSA_IOControlByIdentifier);

      if ( ((index) == NO_SERVICE) || (UDSA_IOControlByIdentifier[index].Enable != ENABLE) )
      {
        ret_val = REQUEST_OUT_OF_RANGE;

      }
      else if ((Data[3] == SHORT_TERM_ADJUSTMENT) && (Length != UDSA_IO_LEN_SHORT_ADJUST))
      {
        ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;   /* 0x13 */
      }
      else if ((Data[3] == RETURN_CONTROL_TO_ECU) && (Length != UDSA_IO_MIN_LEN_PROTOCOL))
      {
        ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;   /* 0x13 */
      }
      else
      {
        if (UDSA_IOControlByIdentifier[index].AdSch & UDSA_AddresScheme)
        {
          /* DID supported in this address scheme */
          if ((UDSA_IOControlByIdentifier[index].Session & UDSA_DiagSession)!= 0u)
          {
            Diag_Response_Ln = 4U ;
            Diag_Response[1] = Data[1];
            Diag_Response[2] = Data[2];
            Diag_Response[3] = Data[3];


            if (UDSA_IOControlByIdentifier[index].Callback != NULL)
            {
              ret_val = (UDSA_IOControlByIdentifier[index].Callback(Data, Length));
            }
          }
          else
          {
            ret_val = REQUEST_OUT_OF_RANGE;
          }
          
        }
        else
        {
          /* DID NOT supported in this address scheme --> NO RESPONSE */
          ret_val = NO_RESPONSE;
        }
      }
    }
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplRoutineControlResponse             $31                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplRoutineControlResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  if(Length < 4U)
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    
    if ((UDSA_RoutineCtrlResp[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
    {
      Diag_Response[1] = Data[1];
      Diag_Response[2] = Data[2];
      Diag_Response[3] = Data[3];
      Diag_Response_Ln = 4U;
      
      if (UDSA_RoutineCtrlResp[UDSA_FoundedSubf].Callback != NULL)
      {
        ret_val = (UDSA_RoutineCtrlResp[UDSA_FoundedSubf].Callback(Data, Length));
      }
    }
    else
    {
      ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
    }
     
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplStartRoutineCtrlResp             $31 01                     */
/*                                                                            */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplStartRoutineCtrlResp(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u16 routineID, index;

  routineID = ((u16)(Data[2]))<< 8U | ((u16)(Data[3]));

  index = UDSA_BinarySearch(routineID, MAX_NUM_ROUTINE_START, UDSA_StartRoutineByIdentifier);

  if (((index) == NO_SERVICE) || (UDSA_StartRoutineByIdentifier[index].DID >= MAX_VAL_DID) || (UDSA_StartRoutineByIdentifier[index].Enable != ENABLE))
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  else if ((UDSA_StartRoutineByIdentifier[index].RxDL != Length) && (UDSA_StartRoutineByIdentifier[index].RxDL != 0U))
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    if (UDSA_StartRoutineByIdentifier[index].AdSch & UDSA_AddresScheme)
    {
      /* DID supported in this address scheme */
      if ((UDSA_StartRoutineByIdentifier[index].Session & UDSA_DiagSession) != 0u)
      {
        if (UDSA_StartRoutineByIdentifier[index].Callback != NULL)
        {
          ret_val = (UDSA_StartRoutineByIdentifier[index].Callback(Data, Length));
        }
      }
      else
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }
      
    }
    else
    {
      /* DID NOT supported in this address scheme --> NO RESPONSE */
      ret_val = NO_RESPONSE;
    }
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplStopRoutineCtrlResp             $31 02                     */
/*                                                                            */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplStopRoutineCtrlResp(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u16 routineID, index;

  routineID = ((u16)(Data[2]))<< 8U | ((u16)(Data[3]));

  index = UDSA_BinarySearch(routineID, MAX_NUM_ROUTINE_STOP, UDSA_StopRoutineByIdentifier);

  if (((index) == NO_SERVICE) || (UDSA_StopRoutineByIdentifier[index].DID >= MAX_VAL_DID) || (UDSA_StopRoutineByIdentifier[index].Enable != ENABLE))
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  else if ((UDSA_StopRoutineByIdentifier[index].RxDL != Length) && (UDSA_StopRoutineByIdentifier[index].RxDL != 0U))
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    if (UDSA_StopRoutineByIdentifier[index].AdSch & UDSA_AddresScheme)
    {
      /* DID supported in this address scheme */
      if ((UDSA_StopRoutineByIdentifier[index].Session & UDSA_DiagSession) != 0u)
      {
        if (UDSA_StopRoutineByIdentifier[index].Callback != NULL)
        {
          ret_val = (UDSA_StopRoutineByIdentifier[index].Callback(Data, Length));
        }
      }
      else
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }
    }
    else
    {
      /* DID NOT supported in this address scheme --> NO RESPONSE */
      ret_val = NO_RESPONSE;
    }
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_RequestRoutinResultCtrlResp             $31 03                  */
/*                                                                            */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplRequestRoutinResultCtrlResp(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;
  u16 routineID, index;

  routineID = ((u16)(Data[2]))<< 8U | ((u16)(Data[3]));

  index = UDSA_BinarySearch(routineID, MAX_NUM_ROUTINE_RESULT, UDSA_RoutineResultByIdentifier);

  if (((index) == NO_SERVICE) || (UDSA_RoutineResultByIdentifier[index].DID >= MAX_VAL_DID) || (UDSA_RoutineResultByIdentifier[index].Enable != ENABLE))
  {
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  else if ((UDSA_RoutineResultByIdentifier[index].RxDL != Length) && (UDSA_RoutineResultByIdentifier[index].RxDL != 0U))
  {
    ret_val = INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT;
  }
  else
  {
    if (UDSA_RoutineResultByIdentifier[index].AdSch & UDSA_AddresScheme)
    {
      /* DID supported in this address scheme */
      if ((UDSA_RoutineResultByIdentifier[index].Session & UDSA_DiagSession) != 0u)
      {
        if (UDSA_RoutineResultByIdentifier[index].Callback != NULL)
        {
          ret_val = (UDSA_RoutineResultByIdentifier[index].Callback(Data, Length));
        }
      }
      else
      {
        ret_val = REQUEST_OUT_OF_RANGE;
      }
       
    }
    else
    {
      /* DID NOT supported in this address scheme --> NO RESPONSE */
      ret_val = NO_RESPONSE;
    }
  }

  return ret_val;
}


/*----------------------------------------------------------------------------*/
/*Name : ApplRequestDownloadResponse            $34                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 ApplRequestDownloadResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : ApplRequestTransfertDataResponse       $36                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 ApplRequestTransfertDataResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : ApplRequestTransfertExitResponse       $37                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 ApplRequestTransfertExitResponse(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplTesterPresentResponse              $3E                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplTesterPresentResponse(u08 *Data, u16 Length)
{
  u08 Subfunction;
  u08 ret_val = SERVICE_OK;

  Subfunction = Data[1];

  if ((UDSA_TesterPresent[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if((UDSA_TesterPresent[UDSA_FoundedSubf].Callback) != NULL)
    {
      ret_val = (UDSA_TesterPresent[UDSA_FoundedSubf].Callback(Data, Length));
    }

    Diag_Response[1] = Subfunction;
    Diag_Response_Ln = 2U;
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }
  

  return ret_val;
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_ApplControlDtcSettingResponse              $85                  */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ApplControlDtcSettingResponse(u08 *Data, u16 Length)
{
  u08 ret_val;
  u08 Subfunction;

  ret_val = SERVICE_OK;
  Subfunction = Data[1];

  if ((UDSA_ControlDTcSetting[UDSA_FoundedSubf].Session & UDSA_DiagSession) != 0u)
  {
    if((UDSA_ControlDTcSetting[UDSA_FoundedSubf].Callback) != NULL)
    {
      ret_val = (UDSA_ControlDTcSetting[UDSA_FoundedSubf].Callback(Data, Length));
    }

    Diag_Response[1] = Subfunction;
    Diag_Response_Ln = 2U;
  }
  else
  {
    ret_val = SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION;
  }
  
  
  return ret_val;
}




/*----------------------------------------------------------------------------*/
/*Name : Udsa_ControlDTCSettingON                    $85 01                   */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ControlDTCSettingON(u08 *Data, u16 Length)
{
  u08 ret_val;

  /* control DTC setting = ON (e.g. resume dtc setting) */
  DDMP_SetControlDtcSetting(DDMP_DTC_ENABLE);

  ret_val = SERVICE_OK;

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ControlDTCSettingOFF                   $85 02                   */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ControlDTCSettingOFF(u08 *Data, u16 Length)
{
  u08 ret_val;

  /* control DTC setting = OFF (e.g. stop dtc setting) */
  DDMP_SetControlDtcSetting(DDMP_DTC_DISABLE);
  ret_val = SERVICE_OK;

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_DefaultSessionResponse            0x01                          */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_DefaultSessionResponse(u08 *Data, u16 Length)
{
  u08 ret_val;

  if(KEYA_IsKeyOnStatus() == FALSE)
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    /* transition from ANY_NON_DEFAULT_SEESSION TO DEFAULT SESSION */

    /* restore communication contro type to default : pag. 27 19-2051 Iveco */
    UDSA_CommunicationControlType = UDSA_CCT_ENRX_ENTX;

    /* init IO control */
/*FRAT - The IO control deactivation is managed by DFCA or DISPA module*/

    /* Restore control DTC setting */
    DDMP_SetControlDtcSetting(DDMP_DTC_ENABLE);
    /* Restore communication control service */
    UDSA_RESTORE_COM_CTRL(NETP_CCT_ALL_MSG)

    UDSA_SetSessionType(UDSA_DEFAULT_SESSION); //DF 30.01.2015

    // Come Da CDD 1.4 - Dependencies - Alla richiesta di una sessione di diagnosi di DEFAULT
    // si deve LOCKARE la ECU
    ECU_SecAccessSts = SEC_ACC_ECU_LOCKED;
    VIN_SecAccessSts = SEC_ACC_VIN_LOCKED;
    ret_val = SERVICE_OK;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ProgrammingSessionResponse         0x02                         */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ProgrammingSessionResponse(u08 *Data, u16 Length)
{
  u08 ret_val;
  bool a,c;

  a = KEYA_IsKeyOnStatus();
  c = FUNP_IsVehicleSpeedEqZero();

  if(a && c)
  {
    if(FUNP_GetBatteryVoltage() < UDSA_PROGR_SES_LOW_BAT_THRES)
    {
      ret_val = UDSA_NRC_VOLTAGE_TOO_LOW;
    }
    else if(FUNP_GetBatteryVoltage() > UDSA_PROGR_SES_HIGH_BAT_THRES)
    {
      ret_val = UDSA_NRC_VOLTAGE_TOO_HIGH;
    }
    else
    {
      UDSA_SetSessionType(UDSA_PROGRAMMING_SESSION); //DF 30.01.2015
      UDSA_FingerCount = 0u; /* Enable fingerprint sequence writing to jump in boot mode */
      TLRP_SetFast(BOOT_Jump_Timer);   // jump to boot
      ret_val = SERVICE_OK;
    }
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ExtendedSessionResponse            0x03                         */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_ExtendedSessionResponse(u08 *Data, u16 Length)
{
  u08 ret_val;
  bool a;

  a = KEYA_IsKeyOnStatus();

  if(a == TRUE)
  {
    UDSA_SetSessionType(UDSA_EXTENDED_SESSION); //DF 30.01.2015
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_EOLSessionResponse                        0x40                  */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_EOLSessionResponse(u08 *Data, u16 Length)
{
  u08 ret_val;

  //TODO TANK, completare e verificare
  
  if(KEYA_IsKeyOnStatus() == FALSE)
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    UDSA_SetSessionType(UDSA_EOL_SESSION); //DF 30.01.2015
    ret_val = SERVICE_OK;
  }
  return ret_val;
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_SystemSupplierSessionResponse             0x60                  */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 Udsa_SystemSupplierSessionResponse(u08 *Data, u16 Length)
{
  u08 ret_val;

  if(KEYA_IsKeyOnStatus() == FALSE)
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    UDSA_SetSessionType(UDSA_SUPPL_SESSION); //DF 30.01.2015
    ret_val = SERVICE_OK;
  }
  return ret_val;
}

/******************************************************************************/
/*       EcuReset    $11                            ***   Callback  ***       */
/******************************************************************************/
/*----------------------------------------------------------------------------*/
/*Name : UDSA_ApplHardResetResponse                                           */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static u08 UDSA_ApplHardResetResponse(u08 *Data, u16 Length)     //Hard Reset $01
{
  u08 ret_val;

  Diag_Response[1] = HARD_RESET;
  Diag_Response_Ln = 2u;

  /* Timer set: when expiring hard reset is generated */
  TLRP_SetFast(TLRP_HardReset_Timer);
  /* allo scadere del quale verrà fatto scattare un reset!!!*/
  ret_val = SERVICE_OK;

  return ret_val;
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_Nak78Pending                                                    */
/*Role :    Routine called by the TaskBackgroundMedium() to manage the        */
/*          NACK 78 sending and the recall of the UDSA_Decoding()             */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/

/* MAM - al momento è utilizzata solo per la gestione della cancellazione eeprom.
 *       se si aggiungono altri "utenti" per il nak 78 è necessario ad es. uno switch case... 
 */
void UDSA_Nak78PendingDelay(void)
{
  /* Resetto il timeout (potrei essere stato chiamato dalla UDSA_EraseEepromCompleted) */
  TLRP_ResetSlow(UDSA_Nak78EepromEraseTimer);

  /* Risposta al servizio di reset eeprom (2E FDF1) */
  Diag_Response_Ln = 3U;

  if (UDSA_EraseEpromResult == MS_OK)
  {
    Diag_Response[0] = 0x6Eu;
    Diag_Response[1] = 0xFDu;
    Diag_Response[2] = 0xF1u;
  }
  else
  {
    Diag_Response[0] = 0x7Fu;
    Diag_Response[1] = 0x2Eu;
    Diag_Response[2] = GENERAL_PROGRAMMING_FAILURE;
  }

  TP_RunTpTx();

  UDSA_Nak78Pending = NAK78_NOT_PENDING;
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_EraseEepromCompleted                                            */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_EraseEepromCompleted(DRVD_RStatus_t ws)
{
  /* Erase completato, invio la risposta al servizio 2E */
  UDSA_EraseEpromResult = ws;
  UDSA_Nak78PendingDelay();
}

/******************************************************************************/
/*                                                                            */
/*                          ALFA ROMEO SEED & KEY                             */
/*                                                                            */
/******************************************************************************/
/**
 * @brief Get Key for FLASH programming
 * @author Seed & Key Alfa Algorithm
 * @param [in]  - seed u32
 * @param [out] - u32
 * @return      - calculated Key value
 */
static uint32_t SeedKeyVIN3 (uint32_t seed) {
  const uint32_t key[4U] = { 0x9b127d51U, 0x5ba41903U, 0x4fe87269U, 0x6bc361d8U }; //128 bits
  uint32_t y = ((seed<<24U)&0xff000000U) + ((seed<<8U)&0xff0000U) + ((seed>>8U)&0xff00U) + ((seed>>24U)&0xffU); //swap byte order
  uint32_t z = 0U, sum = 0U; //y = LOW_PART, z = HIGH_PART
  uint8_t n = 64U; //number of iterations
  while (n > 0U) { //encrypt
    y += (((z << 4U) ^ (z >> 5U)) + z) ^ (sum + key[sum & 3U]);
    sum += 0x8f750a1dU;
    z += (((y << 4U) ^ (y >> 5U)) + y) ^ (sum + key[(sum >> 11U) & 3U]);
    n--;
  }
  return ((z<<24U)&0xff000000U) + ((z<<8U)&0xff0000U) + ((z>>8U)&0xff00U) + ((z>>24U)&0xffU); //swap byte order
}
/******************************************************************************/
/*                                                                            */
/*                       END ALFA ROMEO SEED & KEY                            */
/*                                                                            */
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/*Name : Udsa_SetCommCtrlTypeTx                                               */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static void Udsa_SetCommCtrlTypeTx(NETP_ComType_t valnew)
{
  NETP_ComType_t CctOld;

  CctOld = NETP_GetCommCtrlTypeTx();
  CctOld |= valnew;
  NETP_SetCommCtrlTypeTx(CctOld);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_SetCommCtrlTypeRx                                               */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static void Udsa_SetCommCtrlTypeRx(NETP_ComType_t valnew)
{
  NETP_ComType_t CctOld;

  CctOld = NETP_GetCommCtrlTypeRx();
  CctOld |= valnew;
  NETP_SetCommCtrlTypeRx(CctOld);
}


/*----------------------------------------------------------------------------*/
/*Name : Udsa_ResetCommCtrlTypeTx                                             */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
static void Udsa_ResetCommCtrlTypeTx(NETP_ComType_t valnew)
{
  NETP_ComType_t CctOld;

  CctOld = NETP_GetCommCtrlTypeTx();
  CctOld &= (~valnew);
  NETP_SetCommCtrlTypeTx(CctOld);
}

/*----------------------------------------------------------------------------*/
/*Name : Udsa_ResetCommCtrlTypeRx                                             */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
#if 0
static void Udsa_ResetCommCtrlTypeRx(NETP_ComType_t valnew)
{
  NETP_ComType_t CctOld;

  CctOld = NETP_GetCommCtrlTypeRx();
  CctOld &= (~valnew);
  NETP_SetCommCtrlTypeRx(CctOld);
}
#endif
/*----------------------------------------------------------------------------*/
/*Name : UDSA_WriteProgrammingStatus                                          */
/*Role : RDI 0x2010 - check in Appl.                                          */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_WriteProgrammingStatus(void)
{
  u08 RDIFlag = 0u;

  if(EERAM_ProgStatus[0] != 0xFFu)
  {
    EERAM_ProgStatus[0] = 0xFFu;
    RDIFlag = 1u;
  }

  if((EERAM_ProgStatus[1U] & 0xE7u) != 0xE7u)
  {
    EERAM_ProgStatus[1] = EERAM_ProgStatus[1] | 0xE7u;
    RDIFlag = 1u;
  }

  if((EERAM_ProgStatus[2] & 0xECu) != 0xECu)
  {
    EERAM_ProgStatus[2] = EERAM_ProgStatus[2] | 0xECu;
    RDIFlag = 1u;
  }

  if(EERAM_ProgStatus[3] != 0xFFu)
  {
    EERAM_ProgStatus[3] = 0xFFu;
    RDIFlag = 1u;
  }

  if(RDIFlag)
  {
    EEPP_WriteData(EEPP_HDL_ProgStatus, NULL);
  }

}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_CallBoot                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
#pragma optimize=none //Aggiunto poichè con otpimize = MEDIUM la variabile UDSA_ApplKey non è gestita correttamente 
void UDSA_CallBoot(void)
{
  if(UDSA_DiagSession == DIAG_PROGRAMMING_SESSION)
  {
    DI();

    /* Notify the jump APPL --> BOOT */
    BOOT_StartMode = START_FROM_DWNLOAD_APPL_REQ;
    SHREDRAM_SuppPosRspMsgIndBit = (u08)UDSA_GetSuppPosRspMsgIndBit();

    /* Call __program_start of boot */
    asm("CALL 0x030F");
    
    /* In case of the direct boot call isn't performed */
    LPMS_HwReset();
  }
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_SecAccess_ClearCounterOfAttempt                                 */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_SecAccess_ClearCounterOfAttempt(void)
{
  //Udsa_SecAccess_CounterOfAttempt = 0U;
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_BitronUnlockFingerInit                                          */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_BitronUnlockFingerInit(void)
{
#if 0
  u08 i;

  for(i = 0U; i < UDSA_LN_APP_SW_IDENTIFICATION; i++)
  {
    UDSA_MirrorApplSwId[i] = 0u;
  }
#endif
}

/*----------------------------------------------------------------------------*/
/*Name : UDSA_ServiceConfigInit                                               */
/*Role : Init variable of config & module                                     */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_ServiceConfigInit(void)
{
  ECU_SecAccessSts = SEC_ACC_ECU_LOCKED;
  VIN_SecAccessSts = SEC_ACC_VIN_LOCKED;

  UDSA_Nak78Pending = NAK78_NOT_PENDING;
  UDSA_Nak78PendingResp[0] = 0x00U;
  UDSA_Nak78PendingResp[1] = 0x00U;
  UDSA_Nak78PendingResp[2] = 0x00U;
  UDSA_Nak78PendingResp[3] = 0x00U;
  UDSA_Nak78PendingResp_Ln = 0x00U;

  UDSA_SecAccInProgress = FALSE;
  UDSA_FingerCount = 0U; /* TODO CDO: Present in programming session, too (?) */

  /* If occour the jump boot --> appl, the UDSA_ApplKey is wrote to 0x0000, but
       in applicative is done the RAM test that change this value. For this reason
       is replaced the value wrote by boot during the jump. */
  BOOT_StartMode = START_FROM_RESET;
}


/*----------------------------------------------------------------------------*/
/*Name : UDSA_SetSessionType                                                  */
/*Role : set the session type and current session flag mask                   */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints : Must always call this function to change current diagnostic   */
/*              session ( not modify directly UDSA_DiagSession)               */
/*Behavior :                                                                  */
/*----------------------------------------------------------------------------*/
void UDSA_SetSessionType(UDSA_DiagSession_t session_type) //DF: diagsession bitwise
{
  switch(session_type)
  {   
    case UDSA_DEFAULT_SESSION:
      /* following function call stop the active IO Control 
      (0 is less than any numer of active io control, 
      see DISPA_SetMaxContemporaryIoControl function description)
      and inhibit further IoControl request */
      DISPA_SetMaxContemporaryIoControl(0u);
      UDSA_DiagSession = DIAG_DEFAULT_SESSION;
      break;
      
    case UDSA_PROGRAMMING_SESSION:
      UDSA_DiagSession = DIAG_PROGRAMMING_SESSION;
      break;
    
    case UDSA_EXTENDED_SESSION:
      /* if only 1 IOControl is active this function don't stop it, 
         else (if 2 or more IO control are active) it stop all the acttive control */
      DISPA_SetMaxContemporaryIoControl(1u); // only one IOControl available
      UDSA_DiagSession = DIAG_EXTENDED_SESSION;
      break;
      
    case UDSA_EOL_SESSION:
      /* if only 1 IOControl is active this function don't stop it, 
         else (if 2 or more IO control are active) it stop all the acttive control */
      DISPA_SetMaxContemporaryIoControl(1u); // only one IOControl available
      UDSA_DiagSession = DIAG_EOL_SESSION;
      break;
      
    case UDSA_SUPPL_SESSION:
      /* Enable multiple contemporary IOCOntrol */
      DISPA_SetMaxContemporaryIoControl(DISPA_GROUP_MAX);
      UDSA_DiagSession = DIAG_SUPPL_SESSION;
      break;
      
    case UDSA_NO_SESSION:
    default:
      break;
  }
}

#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDSA_Config.c) _________________________________________*/
