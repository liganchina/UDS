/********************************************************************************/
/* @F_PROJECT:          TTM_636                                                 */
/* F_NAME:              ECU_Identification.h                                    */
/* @F_PURPOSE:          ECU Identification data types & lenghts                 */
/* @F_CREATED_BY:       C. D'Onofrio                                            */
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
| CDO           Clementina D'Onofrio      Consultant
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 25/07/2013  0.1  CDO     First release
| 07/11/2013  0.2  CDO     TTM 636
*/

#ifndef __ECU_IDENT_H 
#define __ECU_IDENT_H


/*______ I N C L U D E - F I L E S ___________________________________________*/




/*______ D A T A - L E N G T H _______________________________________________*/
/* data in EEPROM */

#define DDMP_NUM_MAX_DTC_SAVED         10U  /* Massimo numero di DTC  salvati in memoria */

#define UDSA_LN_BOOT_SW_ID             14U   /* F180 LENGHT */
#define UDSA_LN_APPL_SW_ID             14U   /* F181 LENGHT */
#define UDSA_LN_APPL_DATA_ID           14U   /* F182 LENGHT */
#define UDSA_LN_BOOT_FINGER            13U   /* F183 LENGHT */
#define UDSA_LN_APPL_FINGER            13U   /* F184 LENGHT */
#define UDSA_LN_DATA_FINGER            13U   /* F185 LENGHT */
#define UDSA_LN_SPARE_PART_NUMBER      11U   /* F187 LENGHT */
#define UDSA_LN_VEH_MAN_ECU_SW_NUM     11U   /* F188 LENGHT */
#define UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM 10U   /* F18A LENGHT */
#define UDSA_LN_VEH_MAN_ECU_SW_APP_NUM 10U   /* F18B LENGHT */
#define UDSA_LN_SERIAL_NUMBER          15U   /* F18C LENGHT */
#define UDSA_LN_VIN                    17U   /* F190 LENGHT */
#define UDSA_LN_ECU_HW_NUMBER          11U   /* F191 LENGHT */
#define UDSA_LN_SYS_SUP_ECU_HW_NUM     11U   /* F192 LENGHT */
#define UDSA_LN_SYS_SUP_ECU_HW_VER_NUM  1U   /* F193 LENGHT */
#define UDSA_LN_SYS_SUP_ECU_SW_NUM     11U   /* F194 LENGHT */
#define UDSA_LN_SYS_SUP_ECU_SW_VER_NUM  2U   /* F195 LENGHT */
#define UDSA_LN_HOMOLOG                 6U   /* F196 LENGHT */
#define UDSA_LN_SIN_FACTORY             6U   /* F1A4 LENGHT */
#define UDSA_LN_ISO                     5U   /* F1A5 LENGHT */



#define UDSA_LN_DATE                    4u   /*  */
#define UDSA_LN_TRACEABILITY            1U   /*  */
#define UDSA_LN_CONF_CODE              11U   /*  */
#define UDSA_LN_PROG_STATUS             4U   /*  */
#define UDSA_LN_CONF_DATA               6U   /*  */
#define UDSA_LN_CRC_PROXI               5U   /*  */
#define UDSA_LN_EOL_CHECK               9U   /*  */
#define UDSA_EOL_N_START_CRC           26U   /*  */
#define UDSA_VCarMovingUpperLimit      0x0000001FU
#define UDSA_Veh_Speed_ThresholdUpLim  0x04U

/* _________ RDI $2010 (Programmig Status) masks ________________________ */

#define UDSA_BOOTBLOCK           0x01U  /* Application Status, bit 0 */
#define UDSA_APPLBLOCK           0x02U  /* Application Status, bit 1 */
#define UDSA_DATABLOCK           0x04U  /* Application Status, bit 2 */
#define UDSA_TRANSFDATASEQ       0x01U  /* Failure Programming 3, bit 0 */
#define UDSA_TRANSFDATABLOCKSIZE 0x02U  /* Failure Programming 3, bit 1 */
#define UDSA_ROUTINEERASEMEMSIZE 0x08U  /* Failure Programming 3, bit 3 */
#define UDSA_ROUTINEERASEMEMADDR 0x10U  /* Failure Programming 3, bit 4 */
#define UDSA_ROUTINECHECKSUMADDR 0x20U  /* Failure Programming 3, bit 5 */
#define UDSA_ROUTINECHECKSUMSIZE 0x40U  /* Failure Programming 3, bit 6 */
#define UDSA_ROUTINECHECKSUM     0x80U  /* Failure Programming 3, bit 7 */
#define UDSA_SEQUENCEWRITEDATA   0x01U  /* Failure Programming 2, bit 0 */
#define UDSA_SEQUENCEERASE       0x02U  /* Failure Programming 2, bit 1 */
#define UDSA_SEQUENCEBLOCKTRANSF 0x04U  /* Failure Programming 2, bit 2 */
#define UDSA_SEQUENCECHECKSUM    0x08U  /* Failure Programming 2, bit 3 */
#define UDSA_SECURITYACCESS      0x10U  /* Failure Programming 2, bit 4 */
#define UDSA_REQUESTDOWNLOADAREA 0x20U  /* Failure Programming 2, bit 5 */
#define UDSA_REQUESTDOWNLOADTYPE 0x40U  /* Failure Programming 2, bit 6 */
#define UDSA_REQUESTDOWNLOADSIZE 0x80U  /* Failure Programming 2, bit 7 */
#define UDSA_HW_APPLSW           0x01U  /* Faillure Programming 1, bit 0 */
#define UDSA_APPSW_DATA          0x02U  /* Failure Programming 1, bit 1 */




//****************************************************************************
//***************************      BITRON     ********************************
//****************************************************************************
//
//    File :   identificativi.h
//    Titolo : File contenente la definizione delle costanti di identificazione
//
//    Versione : 2.0
//    Data redazione : 03/02/12
//
//****************************************************************************

#define DDMP_NUM_MAX_DTC_SAVED   10U

#define ECUID_DN_LENGTH           12u
#define ECUID_PN_LENGTH           10u
#define ECUID_EHN_LENGTH          12u
#define ECUID_ON_LENGTH           12u
#define ECUID_IC_LENGTH           5u
#define ECUID_EHV_LENGTH          2u
#define ECUID_ESN_LENGTH          12u
#define ECUID_ESV_LENGTH          2u
#define ECUID_BSV_LENGTH          2u
#define ECUID_EDV_LENGTH          2u
#define ECUID_ESVB_LENGTH         2u
#define ECUID_ESNB_LENGTH         12u
#define ECUID_EHVB_LENGTH         2u
#define ECUID_SPARE_LENGTH        29u

/*______ D A T A T Y P E S ___________________________________________*/
typedef struct{                                             /* RDI: 0xF190 */
  u08 VINX[UDSA_LN_VIN];
  u08 Padding;
}VinData_t;

typedef struct{                                             /* RDI: 0x2023 */
  u08 ConfCode[UDSA_LN_CONF_CODE];
  u08 IgnitionPreStartLogic; /* byte  94 - bit 7  */
  u08 WriteCounter;          /* RDI: 0x292E */
}SystemConfigProxy_t;

typedef struct
{          /* TODO MAM : vedere se mappare attualmente non mappate in E2 */
  u16 KeyOnCnt;
  u08 KeyOnCntSts;
  u08 OccurenceCnt;
  u08 SpnType;
  u08 ActDiagSessDataId;
  u08 NumFlashRewrite;
  u32 EcuTimeStamps;
  u16 EcuTimeStampsFromKeyOn;        /* Per la richiesta 0x22 0x2009 */
  u08 FirstConfirmedDtcID;           /* Per la richiesta 0x19 0x0C   */
  u08 SymptomFirstConfirmedDtc;
  u08 MostRecentConfirmedDtcID;      /* Per la richiesta 0x19 0x0E   */
  u08 SymptomMostRecentConfirmedDtc;
  u32 EcuTimeFirstDTCDetection;      /* Per la richiesta 0x22 0x200B */
  u16 EcuTimeFromKeyOn1DTCDetect;    /* Per la richiesta 0x22 0x200C */
}EcuStatusInfo_t;

typedef struct
{
  u08 VINOdometerCount;
  enum
  { /* RDI 0103 */
    VIN_ODO_NOT_LOCKED = 0x00U, /* VinLock = FALSE */
    VIN_ODO_LOCKED     = 0xFFU, /* VinLock = TRUE */
  } VINOdometerLockStatus;
  u32 MilageOffset;  /* Total odo - Mileage counter */
}OdometerVIN_t;

typedef enum
{
    VIN_NOT_LOCKED = 0U,
    VIN_LOCKED_BY_EXT_TOOL = 1u,
    VIN_LOCKED_BY_ODOMETER = 2u
}VINLockStatus_t; /* RDI 2013 */

typedef struct{
  u08 Status; /* Msg Present = 1u; Msg Absent = 0u */
  u16 KeyOnCounter; /* Num_Key_Cycle ignition-on/ignition-off cycles */
} TripABMsg_t;


typedef enum {
  MSM952_8WPH = 0x00U,
  MSM952_6WP  = 0x01U,
  MSM952_6WPH = 0x02U,
  MSM952_MAX  = 0x03U,
}ProductCode_t;

typedef struct BproxiBitfield_s {

  uint16_t TiltEn      :1;
  uint16_t SlideEn     :1;
  uint16_t LiftEn      :1;
  uint16_t BackEn      :1;
  uint16_t HeatDvrEn   :1;
  uint16_t HeatPsgEn   :1;
  uint16_t HeatStrEn   :1;
  uint16_t AntiPinchEn :1;
  uint16_t spareBit8   :1;
  uint16_t spareBit9   :1;
  uint16_t spareBit10  :1;
  uint16_t spareBit11  :1;
  uint16_t spareBit12  :1;
  uint16_t spareBit13  :1;
  uint16_t spareBit14  :1;
  uint16_t spareBit15  :1;

}BproxiBitfield_t;


/*______ E X T E R N A L - D A T A ___________________________________________*/
/* Data in EEPROM */

extern const u08                        EEDEF_BootSwId         [UDSA_LN_BOOT_SW_ID             ]; /* F180 */
extern const u08                        EEDEF_ApplSwId         [UDSA_LN_APPL_SW_ID             ]; /* F181 */
extern const u08                        EEDEF_ApplDataId       [UDSA_LN_APPL_DATA_ID           ]; /* F182 */
extern const u08                        EEDEF_BootSwFinger     [UDSA_LN_BOOT_FINGER            ]; /* F183 */
extern const u08                        EEDEF_ApplSwFinger     [UDSA_LN_APPL_FINGER            ]; /* F184 */
extern const u08                        EEDEF_ApplDataFinger   [UDSA_LN_DATA_FINGER            ]; /* F185 */
extern const u08                        EEDEF_VehManSparePartN [UDSA_LN_SPARE_PART_NUMBER      ]; /* F187 */
extern const u08                        EEDEF_VehManEcuSwN     [UDSA_LN_VEH_MAN_ECU_SW_NUM     ]; /* F188 */
extern const u08                        EEDEF_VehManEcuSwCalN  [UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM ]; /* F18A */
extern const u08                        EEDEF_VehManEcuSwAppN  [UDSA_LN_VEH_MAN_ECU_SW_APP_NUM ]; /* F18B */
extern const u08                        EEDEF_EcuSerialNum     [UDSA_LN_SERIAL_NUMBER          ]; /* F18C */
extern const u08                        EEDEF_VehManEcuHwN     [UDSA_LN_ECU_HW_NUMBER          ]; /* F191 */
extern const u08                        EEDEF_SysSuppEcuHwN    [UDSA_LN_SYS_SUP_ECU_HW_NUM     ]; /* F192 */
extern const u08                        EEDEF_SysSuppEcuHwVerN                                  ; /* F193 */
extern const u08                        EEDEF_SysSuppEcuSwN    [UDSA_LN_SYS_SUP_ECU_SW_NUM     ]; /* F194 */
extern const u08                        EEDEF_SysSuppEcuSwVerN [UDSA_LN_SYS_SUP_ECU_SW_VER_NUM ]; /* F195 */
extern const u08                        EEDEF_HomologationCode [UDSA_LN_HOMOLOG                ]; /* F196 */
extern const u08                        EEDEF_SincomAndFactory [UDSA_LN_SIN_FACTORY            ]; /* F1A4 */
extern const u08                        EEDEF_ISOCode          [UDSA_LN_ISO                    ]; /* F1A5 */

extern const VinData_t                  EEDEF_VINOriginal;                                        /* RDI: 0xF190 */
extern const VinData_t                  EEDEF_VINCurrent;                                         /* RDI: 0xF1B0 */
extern const OdometerVIN_t              EEDEF_VINOdometer;                                        /* RDI: 0x0103 */
extern const VINLockStatus_t            EEDEF_VINLockState;                                       /* RDI: 0x2013 */
extern const u08                        EEDEF_VINOdoStart;
extern const u08                        EEDEF_ProgStatus       [UDSA_LN_PROG_STATUS            ]; /*      */
extern const EcuStatusInfo_t            EEDEF_EcuStatusInfo;
extern const SystemConfigProxy_t        EEDEF_SysConfigProxy;                                     /* RDI: 0x2023 */
extern const TripABMsg_t                EEDEF_TripABMsg;
extern const u08                        EEDEF_CheckEOLConfData[UDSA_LN_EOL_CHECK];                /* RDI: 0x102A */
extern const BproxiBitfield_t           EEDEF_BproxiConfig[MSM952_MAX];
extern const ProductCode_t              EEDEF_BproxiValue;


/* Data in FLASH */
extern const uint8_t FLASH_SupportedVehManSparePartN[MSM952_MAX][UDSA_LN_SPARE_PART_NUMBER];


#endif /* end __ECU_IDENT_H */
