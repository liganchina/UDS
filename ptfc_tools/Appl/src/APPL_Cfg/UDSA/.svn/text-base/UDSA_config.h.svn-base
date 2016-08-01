#ifndef UDS_CONFIG_H
#define UDS_CONFIG_H
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
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 23/12/2012  0.1  MAD     First release
| 09/05/2013  0.2  GIL     Iveco porting
| 13/03/2014  1.0  GIL     Finally remove UDS subfunction table, managed in UDSA_Subfunction_t
|                          table type adding field AdSch
*/


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

// #define VERSION_NUMBER                  0x0108U

#define MAX_NUM_DID_READ                62U
#define MAX_NUM_DID_WRITE               32U

#define MAX_NUM_ROUTINE_START           5U
#define MAX_NUM_ROUTINE_STOP            1U
#define MAX_NUM_ROUTINE_RESULT          1U

#define MAX_VAL_DID                     0xFFFFU
#define MAX_NUM_SERVICE                 16U
#define MIN_NUM_SERVICE                 0U


#define MAX_NUM_SESSION                 6U
#define MAX_NUM_SUBFUNCTION            10U
#define MAX_NUM_RESET_SERVICE           2U
#define MAX_NUM_COM_CTRL_SERVICE        3U
#define MAX_NUM_SEC_ACC_SERVICE         5U
#define MAX_NUM_TEST_PRES_SERVICE       2U
#define MAX_NUM_CTRL_DTC_SERVICE        3U
#define MAX_NUM_DTC_SERVICE            10U //DF: aggiunto NumOfDTCbyStatusMask
#define MAX_NUM_ROUTINE_CTRL_SERVICE    4U

#define MAX_NUM_PARAM_MAP               2U //DF: aggiunto 15/01/2015

#define MAX_NUM_SECURITY_ACCESS         2U
#define MAX_NUM_IOCTRL                  7U
#define NO_SERVICE                      0xFFFFU

#define ADDR_CHECKSUM_FLAG          0x4000U

/* TODO_COBRA - replace the KEYA routine when it will be aligned to 
   new architecture with only keystatus by CAN */
#define UDSA_IsKeyOnStatus()          TRUE /* KEYA_IsKeyOnStatus() */

/*FRAT - #1021: spostato in config.h*/
//DF: diagsession bitwise
#define DIAG_NO_SESSION            0x00u
#define DIAG_DEFAULT_SESSION       0x01u
#define DIAG_PROGRAMMING_SESSION   0x02u
#define DIAG_EXTENDED_SESSION      0x04u
#define DIAG_EOL_SESSION           0x08u
#define DIAG_SUPPL_SESSION         0x10u
#define DIAG_DEFAULT_BOOT_SESSION  0x20u

#define DIAG_ALL_SESSION           (DIAG_DEFAULT_SESSION | \
                                    DIAG_PROGRAMMING_SESSION| \
                                    DIAG_EXTENDED_SESSION | \
                                    DIAG_EOL_SESSION | \
                                    DIAG_SUPPL_SESSION) 

#define DIAG_ALL_NO_BOOT_SESSION  (DIAG_DEFAULT_SESSION | \
                                   DIAG_EXTENDED_SESSION | \
                                   DIAG_EOL_SESSION | \
                                   DIAG_SUPPL_SESSION) 


/*______ G L O B A L - T Y P E S _____________________________________________*/

/*FRAT - #1021: spostato in config.h*/
typedef enum
{
  UDSA_NO_SESSION            = 0x00U,
  UDSA_DEFAULT_SESSION       = 0x01U,
  UDSA_PROGRAMMING_SESSION   = 0x02U,
  UDSA_EXTENDED_SESSION      = 0x03U,
  UDSA_EOL_SESSION           = 0x40U, /* USED ONLY IN 520*/
  UDSA_SUPPL_SESSION         = 0x60U,
  UDSA_DEFAULT_BOOT_SESSION  = 0xFFU //TODO TANK: vaore reale per default boot
}UDSA_DiagSession_t;

typedef enum
{
  ACCES_MODE_PROG_REQSEED = 0x01U, /* NOT used in Appl. */
  ACCES_MODE_PROG_SENDKEY = 0x02U, /* NOT used in Appl. */
  ACCES_MODE_VIN_REQSEED  = 0x05U,
  ACCES_MODE_VIN_SENDKEY  = 0x06U,
}UDSA_SecAccType_t;



typedef enum
{
  NO_RESET = 0,
  HARD_RESET,
  RESET_NUM,
}UDSA_Diag_Reset_t;

typedef enum
{
  UDSA_DTC_ON  = 0x01U,
  UDSA_DTC_OFF = 0x02U,
}UDSA_CntrlDtcSetting_t;

typedef enum
{
  NO_SUBFUNCTION = 0,
  NUM_DTC_BY_STS_MASK,
  DTC_BY_STS_MASK,
  DTC_SNAPSHOT_IDENT,
  DTC_SNAPSHOT_RECORD_BY_DTC_NUM,
  DTC_SNAPSHOT_RECORD_BY_RECORD_NUM,
  DTC_EXT_DATA_RECORD_BY_DTC_NUM,
  NUM_OF_DTC_BY_SEVERITY_MASK_RECORD,
  DTC_BY_SEVERITY_MASK_RECORD,
  SEVERITY_INFO_DTC,
  SUPPORTED_DTC,
  FIRST_TEST_FAILED_DTC,
  FIRST_CONFIRMED_DTC,
  MOST_RECENT_TEST_FAILED_DTC,
  MOST_RECENT_CONFIRMED_DTC,
  MIRROR_MEMORY_DTC_BY_STS_MASK,
  MIRROR_MEMORY_DTC_EXTDATA_RECORD_BY_DTC_NUMBER,
  DUMMY_11_REPORTDTC,
  DUMMY_12_REPORTDTC,
  DUMMY_13_REPORTDTC,
  DTCFAULTDETECTIONCOUNTER,
  DTC_NUM_SUB_FUNC,
}UDSA_ReadDTCInformation_t;   /*   Service 0x19  */


typedef enum
{
  IOC_NONE,
  IOC_FAN_BACKREST,
  IOC_FAN_CUSHION,
  IOC_BOLSTER_CUSHION,
  IOC_BOLSTER_BACKREST,
  IOC_HEATING_BACKREST,
  IOC_HEATING_CUSHION,
  IOC_LUMBAR_H,
  IOC_LUMBAR_V,
  IOC_HEADREST,
  IOC_TILT,
  IOC_LIFT,
  IOC_BACKREST,
  IOC_CUSHION,
  IOC_SLIDE,
  /* DF: non togliere il seguente: */
     IOC_STANDARD_MAX_NMB
} IoCtrlDevice_enum;

typedef enum
{
  START_ROUTINE = 0x01U,
  STOP_ROUTINE,
  REQUEST_ROUTINE
} UDSA_RoutineCtrl_t;

typedef enum
{
  ZERO_SUBF = 0x00U
} UDSA_TesterPres_t;

typedef enum
{
  SET_ON = 0x01U,
  SET_OFF = 0x02
} UDSA_CtrlDtcSetting_t;

/* service communication control : control type */
typedef enum
{
  UDSA_CCT_ENRX_ENTX           = 0x00U,
  UDSA_CCT_ENRX_DISTX          = 0x01U,
  UDSA_CCT_DISRX_ENTX          = 0x02U,
  UDSA_CCT_DISRX_DISTX         = 0x03U,
  UDSA_CCT_NOT_SET             = 0x04U,
}UDSA_CommunicationControlType_t;


/* service routine control : routine control type */
typedef enum
{
  UDSA_RC_RESERVED             = 0x00U,
  UDSA_RC_START_ROUTINE        = 0x01U,
  UDSA_RC_STOP_ROUTINE         = 0x02U,
  UDSA_RC_REQ_ROUTINE_RES      = 0X03U
}UDSA_RoutineControlType_t;

/* ================================================================================= */

/*______ P R I V A T E - M A C R O S _________________________________________*/


/*______ G L O B A L - M A C R O S ___________________________________________*/

#define UDSA_RESTORE_COM_CTRL(x)      NETP_SetCommCtrlTypeRx(x);\
                                      NETP_SetCommCtrlTypeTx(x);

#define UDSA_SESSION_TIMEOUT_ELAPSED  UDSA_IOControlDeactivation();\
                                      UDSA_BitronUnlockFingerInit();

#define UDSA_POST_INIT()              UDSA_BitronUnlockFingerInit();\
                                      UDSA_ServiceConfigInit();

/*Macro that manage the suppression of negative response with negative response
* codes below when functional addressing was used for request message*/
/*Alignment to new ISO 14229-1:2013*/
#define UDSA_SUPPRESS_NEG_RESP_MSG(x) (((x) == SERVICE_NOT_SUPPORTED                      ) ||\
                                       ((x) == SUBFUNCTION_NOT_SUPPORTED                  ) ||\
                                       ((x) == SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION    ) ||\
                                       ((x) == SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION) ||\
                                       ((x) == REQUEST_OUT_OF_RANGE                       ))

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

//extern void UDSA_IOControlDeactivation(void);
extern void UDSA_BitronUnlockFingerInit(void);
extern void UDSA_ServiceConfigInit(void);
extern void UDSA_SetSessionType(UDSA_DiagSession_t session_type); //DF: diagsession bitwise
#endif



