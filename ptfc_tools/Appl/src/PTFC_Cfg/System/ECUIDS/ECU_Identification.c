/********************************************************************************/
/* @F_PROJECT:          HNSN 952                                                */
/* F_NAME:              ECU_Id_KIT1.c                                           */
/* @F_PURPOSE:          ECU Identification and varian coding.                   */
/* @F_CREATED_BY:       F. Zanchetta                                            */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/03/2015                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| FZA          Fabio Zanchetta           BITRON S.p.A.
| CC           Carmine Celozzi           A-Key Srl
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 24/03/2015  1.0  FZA     First release
|-----------------------------------------------------------------------------
| 03/06/2015  1.1  CC      Insert a dedicated area memory, KIT_FILE_CONST, for
|                          all services to change in the kit file. This new
|                          management is valid for new Bitron tool to use to
|                          generate the FCA kit files.
|-----------------------------------------------------------------------------
|
|
*/

#ifndef KIT_FILE

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "typedefs.h"
#include "ECU_Identification.h"

/*****************************************************************************************************************/
/*                                               EEPROM DATA                                                     */
/*****************************************************************************************************************/

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF180 */ /* 7-Z0071 - Tabella Descrizione centralina */
const u08 EEDEF_BootSwId[UDSA_LN_BOOT_SW_ID]                    = {0x01u,
                                                                   0x01u,
                                                                   0x31u,0x38u,0x30u,0x30u,0x30u,0x36u,0x34u,0x33u,0x30u,0x35u,
                                                                   0x35u,0x41u};                              /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF181 */ /* 7-Z0071 - Tabella Descrizione centralina */
const u08 EEDEF_ApplSwId[UDSA_LN_APPL_SW_ID]                    = {0x01u,
                                                                   0x01u,
                                                                   0x31u,0x38u,0x30u,0x30u,0x30u,0x36u,0x34u,0x33u,0x30u,0x35u,
                                                                   0x35u,0x41u};                              /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF182 */ /* 7-Z0071 - Tabella Descrizione centralina */
const u08 EEDEF_ApplDataId[UDSA_LN_APPL_DATA_ID]                = {0x01u,
                                                                   0x01u,
                                                                   0x31u,0x38u,0x30u,0x30u,0x30u,0x36u,0x34u,0x33u,0x30u,0x35u,
                                                                   0x35u,0x41u};                              /* 7-Z0071 - Tabella Descrizione centralina */

/* RDI: 0xF183 */
const u08 EEDEF_BootSwFinger[UDSA_LN_BOOT_FINGER]               = {0x01u,                                     /* moduleID */
                                                                   0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, /* tester code */
                                                                   0x16u, 0x07u, 0x22u};                      /* date */   /* 7-Z0071 - Tabella Descrizione centralina */

/* RDI: 0xF184 */
const u08 EEDEF_ApplSwFinger[UDSA_LN_APPL_FINGER]               = {0x01u,                                     /* moduleID */
                                                                   0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, /* tester code */
                                                                   0x16u, 0x07u, 0x22u};                      /* date */   /* 7-Z0071 - Tabella Descrizione centralina */

/* RDI: 0xF185 */
const u08 EEDEF_ApplDataFinger[UDSA_LN_DATA_FINGER]             = {0x01u,                                     /* moduleID */
                                                                   0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u, /* tester code */
                                                                   0x16u, 0x07u, 0x22u};                      /* date */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF187 */
const u08 EEDEF_VehManSparePartN[UDSA_LN_SPARE_PART_NUMBER]     = {"50537140   "}; /* Full version */         /* RDI: 0xF187 */   /* 7-Z0071 - Tabella Descrizione centralina */


/* RDI: 0xF188 */
const u08 EEDEF_VehManEcuSwN[UDSA_LN_VEH_MAN_ECU_SW_NUM]        = {"52064207   "};                            /* RDI: 0xF188 */

/* RDI: F18A */
const u08 EEDEF_VehManEcuSwCalN[UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM] = {"          "};                             /* RDI: 0xF18A */

/* RDI: F18B */
const u08 EEDEF_VehManEcuSwAppN[UDSA_LN_VEH_MAN_ECU_SW_APP_NUM] = {"          "};                             /* RDI: 0xF18B */

/* RDI: 0xF18C */
const u08 EEDEF_EcuSerialNum[UDSA_LN_SERIAL_NUMBER]             = {"               "};                        /* RDI: 0xF18C */   /* 7-Z0071 - Tabella Descrizione centralina */

/* RDI: 0xF191 */
const u08 EEDEF_VehManEcuHwN[UDSA_LN_ECU_HW_NUMBER]             = {"52059236   "}; /* Full version */         /* RDI: 0xF191 */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF192 */
const u08 EEDEF_SysSuppEcuHwN[UDSA_LN_SYS_SUP_ECU_HW_NUM]       = {"03.01      "};                            /* ECUSupplierHwNumber    - RDI: 0xF192 */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF193 */
const u08 EEDEF_SysSuppEcuHwVerN                                = {0x01u};                                    /* ECUSupplierHwVerNumber - RDI: 0xF193 */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF194 */
const u08 EEDEF_SysSuppEcuSwN[UDSA_LN_SYS_SUP_ECU_SW_NUM]       = {"06.00_RC1  "};                            /* ECUSupplierSwNumber    - RDI: 0xF194 */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF195 */
const u08 EEDEF_SysSuppEcuSwVerN[UDSA_LN_SYS_SUP_ECU_SW_VER_NUM]= {0x00u,0x01u};                              /* ECUSupplierSwVerNumber - RDI: 0xF195 */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF196 */
const u08 EEDEF_HomologationCode[UDSA_LN_HOMOLOG]               = "      ";                                   /* RDI: 0xF196 */   /* 7-Z0071 - Tabella Descrizione centralina */

/* RDI: 0xF1A4 */
const u08 EEDEF_SincomAndFactory[UDSA_LN_SIN_FACTORY]           = {0x20u, 0x20u, 0x20u, 0x20u, 0x20u, 0x20u}; /* RDI: 0xF1A4 */   /* 7-Z0071 - Tabella Descrizione centralina */

#pragma location = "KIT_FILE_CONST"
/* RDI: 0xF1A5 */
const u08 EEDEF_ISOCode[UDSA_LN_ISO]                            = {0x00u,0x30u,0x70u,0x10u,0x15u};            /* RDI: 0xF1A5 */   /* 7-Z0071 - Tabella Descrizione centralina */

/*****************************************************************************************************************/


/*****************************************************************************************************************/

const u08 EEDEF_ProgStatus[UDSA_LN_PROG_STATUS]          = {0xFFu, 0xFFu, 0xFFu, 0xFFu};   /* RDI: 0x2010 */

const SystemConfigProxy_t EEDEF_SysConfigProxy           = {{0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au, 0x0Au},  /* RDI: 0xF1A1, byte 1-11 PROXI*/
                                                            0u,                           /*IgnitionPreStartLogic, byte  94 - bit 7  PROXI*/
                                                            0u};                          /*RDI 0x292E*/

const EcuStatusInfo_t     EEDEF_EcuStatusInfo            = {0x0000u,         /* KeyOnCnt                      */
                                                            0x00u,           /* KeyOnCntSts                   */
                                                            0x00u,           /* OccurenceCnt                  */
                                                            0x00u,           /* SpnType                       */
                                                            0x00u,           /* ActDiagSessDataId             */
                                                            0x00u,           /* NumFlashRewrite               */
                                                            0x00000000u,     /* EcuTimeStamps                 */
                                                            0x0000u,         /* EcuTimeStampsFromKeyOn        */
                                                            0x00u,           /* FirstConfirmedDtcID           */
                                                            0x00u,           /* SymptomFirstConfirmedDtc      */
                                                            0x00u,           /* MostRecentConfirmedDtcID      */
                                                            0x00u,           /* SymptomMostRecentConfirmedDtc */
                                                            0x00000000u,     /* EcuTimeFirstDTCDetection      */
                                                            0x0000u};        /* EcuTimeFromKeyOn1DTCDetect    */


const TripABMsg_t EEDEF_TripABMsg                        = {0x01u, 0x0000u}; /* TRIP_AB present; KeyOnCounterCycle = 0 */


const VinData_t           EEDEF_VINOriginal                     = {{0xFFu,0xFFu,0xFFu,            /* RDI: 0xF190 */   /* 7-Z0071 - Tabella Descrizione centralina */
                                                                    0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,
                                                                    0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu},0U};

const VinData_t           EEDEF_VINCurrent               = {{0xFFu,0xFFu,0xFFu,            /* RDI: 0xF1B0 */
                                                             0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,
                                                             0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu},0U};

const OdometerVIN_t       EEDEF_VINOdometer              = {0u, VIN_ODO_NOT_LOCKED, 0x000000FFu};

const VINLockStatus_t         EEDEF_VINLockState         = VIN_NOT_LOCKED;

/* VF607: condition to start mileage counter */
const u08                     EEDEF_VINOdoStart          = 0u; /* 0: don't start mileage counter; 1: start mileage counter*/


/* RDI: 0x102A */
const u08 EEDEF_CheckEOLConfData[UDSA_LN_EOL_CHECK]      = {0x00u,0x00u,0x00u,0x00u,0x00u,0x00u,0x00u,0x00u,0x00u};


/*****************************************************************************************************************/
/*                                               FLASH DATA                                                      */
/*****************************************************************************************************************/

const ProductCode_t EEDEF_BproxiValue = {MSM952_8WPH}; /* Full version */

const uint8_t FLASH_SupportedVehManSparePartN[MSM952_MAX][UDSA_LN_SPARE_PART_NUMBER] =
{
  /* MSM952_8WPH */  {"50537140   "},
  /* MSM952_6WP  */  {"50537138   "},
  /* MSM952_6WPH */  {"50537139   "},
};

const BproxiBitfield_t EEDEF_BproxiConfig[MSM952_MAX] =
{
                   /*TiltEn,  SlideEn, LiftEn,  BackEn, HeatDvrEn, HeatPsgEn, HeatStrEn, AntiPinchEn, spareBit8, spareBit9, spareBit10, spareBit11, spareBit12, spareBit13, spareBit14, spareBit15*/
  /* MSM952_8WPH */{ ENABLE , ENABLE,  ENABLE,  ENABLE,  ENABLE ,   ENABLE ,   ENABLE ,    ENABLE,     DISABLE,   DISABLE,   DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE},
  /* MSM952_6WP  */{ DISABLE, ENABLE,  ENABLE,  ENABLE,  DISABLE,   DISABLE,   DISABLE,    ENABLE,     DISABLE,   DISABLE,   DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE},
  /* MSM952_6WPH */{ DISABLE, ENABLE,  ENABLE,  ENABLE,  ENABLE ,   ENABLE ,   ENABLE ,    ENABLE,     DISABLE,   DISABLE,   DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE,    DISABLE},
};


#endif
