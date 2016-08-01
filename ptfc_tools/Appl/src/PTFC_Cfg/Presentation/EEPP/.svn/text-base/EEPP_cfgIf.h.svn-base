/********************************************************************************/
/* @F_PROJECT:          TTM 636                                                 */
/* F_NAME:              EEPP_cfgIf                                              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 12/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef EEPP_CFGIF_H_
#define EEPP_CFGIF_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "ECU_Identification.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum EEPP_Handle_e
{
/*______ 0000 Start BootLoader AREA __________________________________________*/

/*______ 0127 Stop  BootLoader AREA __________________________________________*/

/*______ 0128 Start Common AREA ______________________________________________*/
/* 00 */   EEPP_HDL_CommEepromMapSign   ,
/* 01 */   EEPP_HDL_BootSwId            ,
/* 02 */   EEPP_HDL_ApplSwId            ,
/* 03 */   EEPP_HDL_ApplDataId          ,
/* 04 */   EEPP_HDL_BootSwFinger        ,
/* 05 */   EEPP_HDL_ApplSwFinger        ,
/* 06 */   EEPP_HDL_ApplDataFinger      ,
/* 07 */   EEPP_HDL_VehManSparePartN    ,
/* 08 */   EEPP_HDL_VehManEcuSwN        ,
/* 09 */   EEPP_HDL_VehManEcuSwCalN     ,
/* 10 */   EEPP_HDL_VehManEcuSwAppN     ,
/* 11 */   EEPP_HDL_EcuSerialNum        ,
/* 12 */   EEPP_HDL_VehManEcuHwN        ,
/* 13 */   EEPP_HDL_SysSuppEcuHwN       ,
/* 14 */   EEPP_HDL_SysSuppEcuHwVerN    ,
/* 15 */   EEPP_HDL_SysSuppEcuSwN       ,
/* 16 */   EEPP_HDL_SysSuppEcuSwVerN    ,
/* 17 */   EEPP_HDL_HomologationCode    ,
/* 18 */   EEPP_HDL_SincomAndFactory    ,
/* 19 */   EEPP_HDL_ISOCode             ,
/* 20 */   EEPP_HDL_VINOriginal         ,
/* 21 */   EEPP_HDL_VINCurrent          ,
/* 22 */   EEPP_HDL_VINOdometer         ,
/* 23 */   EEPP_HDL_VINLockState        ,
/* 24 */   EEPP_HDL_VINOdoStart         ,
/* 25 */   EEPP_HDL_RandomSeed          ,
/* 26 */   EEPP_HDL_ProgStatus          ,
/* 27 */   EEPP_HDL_EcuStatusInfo       ,
/*______ 0575 Stop  Common AREA ______________________________________________*/

/*______ 0576 Start Applicative AREA _________________________________________*/
/* 28 */   EEPP_HDL_ApplEepromMapSign   ,
/* 29 */   EEPP_HDL_DTC_0               ,
/* 30 */   EEPP_HDL_DTC_EXT_0           ,
/* 31 */   EEPP_HDL_DTC_1               ,
/* 32 */   EEPP_HDL_DTC_EXT_1           ,
/* 33 */   EEPP_HDL_DTC_2               ,
/* 34 */   EEPP_HDL_DTC_EXT_2           ,
/* 35 */   EEPP_HDL_DTC_3               ,
/* 36 */   EEPP_HDL_DTC_EXT_3           ,
/* 37 */   EEPP_HDL_DTC_4               ,
/* 38 */   EEPP_HDL_DTC_EXT_4           ,
/* 39 */   EEPP_HDL_DTC_5               ,
/* 40 */   EEPP_HDL_DTC_EXT_5           ,
/* 41 */   EEPP_HDL_DTC_6               ,
/* 42 */   EEPP_HDL_DTC_EXT_6           ,
/* 43 */   EEPP_HDL_DTC_7               ,
/* 44 */   EEPP_HDL_DTC_EXT_7           ,
/* 45 */   EEPP_HDL_DTC_8               ,
/* 46 */   EEPP_HDL_DTC_EXT_8           ,
/* 47 */   EEPP_HDL_DTC_9               ,
/* 48 */   EEPP_HDL_DTC_EXT_9           ,
/* 49 */   EEPP_HDL_DTC_0_BIS           ,
/* 50 */   EEPP_HDL_DTC_EXT_0_BIS       ,
/* 51 */   EEPP_HDL_DTC_1_BIS           ,
/* 52 */   EEPP_HDL_DTC_EXT_1_BIS       ,
/* 53 */   EEPP_HDL_DTC_2_BIS           ,
/* 54 */   EEPP_HDL_DTC_EXT_2_BIS       ,
/* 55 */   EEPP_HDL_DTC_3_BIS           ,
/* 56 */   EEPP_HDL_DTC_EXT_3_BIS       ,
/* 57 */   EEPP_HDL_DTC_4_BIS           ,
/* 58 */   EEPP_HDL_DTC_EXT_4_BIS       ,
/* 59 */   EEPP_HDL_DTC_5_BIS           ,
/* 60 */   EEPP_HDL_DTC_EXT_5_BIS       ,
/* 61 */   EEPP_HDL_DTC_6_BIS           ,
/* 62 */   EEPP_HDL_DTC_EXT_6_BIS       ,
/* 63 */   EEPP_HDL_DTC_7_BIS           ,
/* 64 */   EEPP_HDL_DTC_EXT_7_BIS       ,
/* 65 */   EEPP_HDL_DTC_8_BIS           ,
/* 66 */   EEPP_HDL_DTC_EXT_8_BIS       ,
/* 67 */   EEPP_HDL_DTC_9_BIS           ,
/* 68 */   EEPP_HDL_DTC_EXT_9_BIS       ,
/* 69 */   EEPP_HDL_DTC_CRC             ,
/* 70 */   EEPP_HDL_DTC_CRC_BIS         ,
/* 71 */   EEPP_HDL_DTC_CRC_EXT         ,
/* 72 */   EEPP_HDL_DTC_CRC_EXT_BIS     ,
/* 73 */   EEPP_HDL_ContatoreHall       ,
/* 74 */   EEPP_HDL_MotorStroke         ,  /* Not used anymore, kept for EEPROM retrocompatibility */
/* 75 */   EEPP_HDL_MirrorMCorr         ,
/* 76 */   EEPP_HDL_MirrorM1            ,
/* 77 */   EEPP_HDL_MirrorM2            ,
/* 78 */   EEPP_HDL_MirrorM3            ,
/* 79 */   EEPP_HDL_MirrorMemInit       ,
/* 80 */   EEPP_HDL_HeatTempParam       ,
/* 81 */   EEPP_HDL_HeatTimeParam       ,
/* 82 */   EEPP_HDL_HeatDutyParam       ,
/* 83 */   EEPP_HDL_Dummy               ,
/* 84 */   EEPP_HDL_MemoM               ,
/* 85 */   EEPP_HDL_MEMODRIVEPOS        ,
/* 86 */   EEPP_HDL_MeasuredMotorStroke ,
/* 87 */   EEPP_HDL_DummyByte           ,
/* 88 */   EEPP_HDL_SysConfigProxy      ,
/* 89 */   EEPP_HDL_TripABMsg           ,
/* 90 */   EEPP_HDL_CheckEOLConfData    ,
/* 91 */   EEPP_HDL_BproxiBitfield      ,
/* 92 */   EEPP_HDL_BproxiValue         ,
/* 93 */   EEPP_HDL_CurrentMapBw        ,
/* 94 */   EEPP_HDL_AntiPinch_Threshold_Bw,
/* 95 */   EEPP_HDL_CounterVectorDownBwd,
/* 96 */   EEPP_HDL_CounterVectorUpBwd  ,
/* 97 */   EEPP_HDL_ConfigModel         ,
/* 98 */   EEPP_HDL_NominalMotorStroke  ,
/* 99 */   EEPP_HDL_AntiPinchAdaptation ,
/* 100 */  EEPP_HDL_AntiPinch_Att_Backward,
/* 101 */  EEPP_HDL_Proxi_Country_Code,
/* 102 */  EEPP_HDL_DriverDoorStsInKeyOff,
/*______ 2047 Stop  Applicative AREA _________________________________________*/

/* LAST */   EEPP_HDL_MAX
}EEPP_Handle_t;


typedef struct MIRR_Data_s
{
  uint8_t                   DrvVertPos;
  uint8_t                   DrvHorizPos;
  uint8_t                   PsngrVertPos;
  uint8_t                   PsngrHorizPos;
  MirrorDrvStandStillSts_t  DrvStandStillSts;
  MirrorDrvStandStillSts_t  PsngrStandStillSts;
} MIRR_Data_t;


typedef struct EEPP_HeatTempParam_s
{
  int16_t    Temp_lim;             /* [0.1°C/bit] */
  int16_t    Temp_range_min;       /* [0.1°C/bit] */
  int16_t    Temp_range_max;       /* [0.1°C/bit] */
  int16_t    Max_Av_Surf_Temp;     /* [0.1°C/bit] */
  int16_t    Max_Av_Surf_Temp_StW; /* [0.1°C/bit] */
} EEPP_HeatTempParam_t;


typedef struct EEPP_HeatTimeParam_s
{
  uint16_t    T1;
  uint16_t    T_wait_1;
  uint16_t    T2;
  uint16_t    T3SW;
  uint16_t    T3HS;
  uint16_t    T_wait_2;
  uint16_t    T4;
  uint16_t    T_low;
} EEPP_HeatTimeParam_t;


typedef struct EEPP_HeatDutyParam_s
{
  uint8_t    D_3;
  uint8_t    D_2;
  uint8_t    DWL1;
  uint8_t    DHL1;
  uint8_t    DLL1;
} EEPP_HeatDutyParam_t;

typedef struct MSM_InitValue_s
{
  u08     EEG_Status        :2;
  u08     Init_MotorSlide   :1;
  u16     PillarPosition    :16;
  u16     Welcome_Distance  :16;
  u08     MotorNewPositionsToBeStored :1;
  u08     ActualPosLoss               :1;
  u08     Sparebits                   :3;
}Model_ConfigValue_t;

/* TODO SGR - inserite momentaneamente qui per farle compilare - vedere se lasciare
   questa struttura o inserire quella nuova */
typedef struct
{
  u08 DTC_EventCounter;
  u08 DTC_FaultPresent;
} DTC_EvCnt;

typedef struct
{
//  u08 DTC_Value_High;
//  u08 DTC_Value_Low;
  DTC_EvCnt DTC_EvCntStatus;
  u08 DTC_EnvParameters[7];
} DTC_EEPROM_Data;

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define NUM_MOTORI                      (4u)
#define NUM_MEMORIE                     (3u)
#define NUM_MOTORS_INIT                 (1u)

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

#ifdef EEPP_CONFIG_IF_OWNER
  #define EEPP_CONFIG_IF_EXTERN
#else
  #define EEPP_CONFIG_IF_EXTERN   extern
#endif

EEPP_CONFIG_IF_EXTERN void               EEPP_EcuPowerOff(void);
EEPP_CONFIG_IF_EXTERN PRES_WriteStatus_t EEPP_WriteDtcRuntime(void);
EEPP_CONFIG_IF_EXTERN void               EEPP_EraseCompleted(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle);

/**
* @brief This function is used to update the status (present/absent) of the proxable functions.
* @author Francesco Talarico
* @param none
* @param none
* @return none
*/
EEPP_CONFIG_IF_EXTERN void EEPP_UpdateFunctionByProxi(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/

#pragma data_alignment=2
/*______ 0000 Start BootLoader AREA __________________________________________*/
/*      */
/*      */
/*______ 0127 Stop  BootLoader AREA __________________________________________*/

/*______ 0128 Start Common AREA ______________________________________________*/
EEPP_CONFIG_IF_EXTERN u08                             EERAM_CommEepromMapSign[8]                              ; /*      */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_BootSwId         [UDSA_LN_BOOT_SW_ID             ]; /* F180 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ApplSwId         [UDSA_LN_APPL_SW_ID             ]; /* F181 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ApplDataId       [UDSA_LN_APPL_DATA_ID           ]; /* F182 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_BootSwFinger     [UDSA_LN_BOOT_FINGER            ]; /* F183 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ApplSwFinger     [UDSA_LN_APPL_FINGER            ]; /* F184 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ApplDataFinger   [UDSA_LN_DATA_FINGER            ]; /* F185 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VehManSparePartN [UDSA_LN_SPARE_PART_NUMBER      ]; /* F187 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VehManEcuSwN     [UDSA_LN_VEH_MAN_ECU_SW_NUM     ]; /* F188 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VehManEcuSwCalN  [UDSA_LN_VEH_MAN_ECU_SW_CAL_NUM ]; /* F18A */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VehManEcuSwAppN  [UDSA_LN_VEH_MAN_ECU_SW_APP_NUM ]; /* F18B */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_EcuSerialNum     [UDSA_LN_SERIAL_NUMBER          ]; /* F18C */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VehManEcuHwN     [UDSA_LN_ECU_HW_NUMBER          ]; /* F191 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_SysSuppEcuHwN    [UDSA_LN_SYS_SUP_ECU_HW_NUM     ]; /* F192 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_SysSuppEcuHwVerN                                  ; /* F193 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_SysSuppEcuSwN    [UDSA_LN_SYS_SUP_ECU_SW_NUM     ]; /* F194 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_SysSuppEcuSwVerN [UDSA_LN_SYS_SUP_ECU_SW_VER_NUM ]; /* F195 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_HomologationCode [UDSA_LN_HOMOLOG                ]; /* F196 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_SincomAndFactory [UDSA_LN_SIN_FACTORY            ]; /* F1A4 */
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ISOCode          [UDSA_LN_ISO                    ]; /* F1A5 */
EEPP_CONFIG_IF_EXTERN VinData_t                       EERAM_VINOriginal;                                        /* F190 */
EEPP_CONFIG_IF_EXTERN VinData_t                       EERAM_VINCurrent;
EEPP_CONFIG_IF_EXTERN OdometerVIN_t                   EERAM_VINOdometer;
EEPP_CONFIG_IF_EXTERN VINLockStatus_t                 EERAM_VINLockState;
EEPP_CONFIG_IF_EXTERN u08                             EERAM_VINOdoStart;
EEPP_CONFIG_IF_EXTERN u32                             EERAM_RandomSeed;
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ProgStatus       [UDSA_LN_PROG_STATUS            ]; /*      */
EEPP_CONFIG_IF_EXTERN EcuStatusInfo_t                 EERAM_EcuStatusInfo;
/*______ 0575 Stop  Common AREA ______________________________________________*/

/*______ 0576 Start Applicative AREA _________________________________________*/
EEPP_CONFIG_IF_EXTERN u08                             EERAM_ApplEepromMapSign[8]                              ; /*      */
EEPP_CONFIG_IF_EXTERN Ddmp_Block_t                    EERAM_DTC              [DDMP_NUM_MAX_DTC_SAVED         ];
EEPP_CONFIG_IF_EXTERN Ddmp_BlockExt_t                 EERAM_DTC_EXT          [DDMP_NUM_MAX_DTC_SAVED         ];
EEPP_CONFIG_IF_EXTERN u16                             EERAM_DTC_CRC                                           ;   /*      */
EEPP_CONFIG_IF_EXTERN u16                             EERAM_DTC_CRC_EXT                                       ;   /*      */
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_ContatoreHall    [IPOC_HDL_MAX                   ];
EEPP_CONFIG_IF_EXTERN PRES_Stroke_t                   EERAM_MotorStroke      [MOTP_MAX_HDL                   ];   /* Not used anymore, kept for EEPROM retrocompatibility */
EEPP_CONFIG_IF_EXTERN MIRR_Data_t                     EERAM_MirrorMCorr;
EEPP_CONFIG_IF_EXTERN MIRR_Data_t                     EERAM_MirrorM1;
EEPP_CONFIG_IF_EXTERN MIRR_Data_t                     EERAM_MirrorM2;
EEPP_CONFIG_IF_EXTERN MIRR_Data_t                     EERAM_MirrorM3;
EEPP_CONFIG_IF_EXTERN bool_t                          EERAM_MirrorMemInit[NUM_MEMORIE];
EEPP_CONFIG_IF_EXTERN EEPP_HeatTempParam_t            EERAM_HeatTempParam;
EEPP_CONFIG_IF_EXTERN EEPP_HeatTimeParam_t            EERAM_HeatTimeParam;
EEPP_CONFIG_IF_EXTERN EEPP_HeatDutyParam_t            EERAM_HeatDutyParam;
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_MemoM[NUM_MOTORI*NUM_MEMORIE];
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_MemoDrivePos;
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_Measured_Motors_Stroke;
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_Nominal_Motors_Stroke;
EEPP_CONFIG_IF_EXTERN SystemConfigProxy_t             EERAM_SysConfigProxy;
EEPP_CONFIG_IF_EXTERN TripABMsg_t                     EERAM_TripABMsg;          /* VF 607 */
EEPP_CONFIG_IF_EXTERN uint8_t                         EERAM_CheckEOLConfData[UDSA_LN_EOL_CHECK]; /* 9 byte */

EEPP_CONFIG_IF_EXTERN BproxiBitfield_t                EERAM_BproxiConfig[MSM952_MAX];
EEPP_CONFIG_IF_EXTERN ProductCode_t                   EERAM_BproxiValue;

EEPP_CONFIG_IF_EXTERN Model_ConfigValue_t             EERAM_ConfigModel;
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_Current_Map_Backward[100];
EEPP_CONFIG_IF_EXTERN uint8_t                         EERAM_Threshold_Antipinch_Backward;
EEPP_CONFIG_IF_EXTERN uint16_t                        EERAM_CounterVectorDownBwd[13];
EEPP_CONFIG_IF_EXTERN uint16_t                        EERAM_CounterVectorUpBwd[13];
EEPP_CONFIG_IF_EXTERN u08                             EERAM_AntiPinchAdaptation;
EEPP_CONFIG_IF_EXTERN u08                             EERAM_Threshold_Att_Backward;

EEPP_CONFIG_IF_EXTERN uint16_t                        EERAM_dummy[3];
EEPP_CONFIG_IF_EXTERN int16_t                         EERAM_dummyByte;

EEPP_CONFIG_IF_EXTERN FUNP_ProxiCountriCode_t         EERAM_Proxi_Country_Code;
EEPP_CONFIG_IF_EXTERN CMMD_DoorSts_t                  EERAM_DriverDoorStsInKeyOff;
/*______ 2047 Stop  Applicative AREA _________________________________________*/



#endif /* EEPP_CFGIF_H_ */
