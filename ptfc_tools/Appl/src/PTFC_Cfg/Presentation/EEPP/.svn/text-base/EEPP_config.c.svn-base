/*==============================================================================
                           B I T R O N    S.p.A.
================================================================================

    Modulo:     EEPP_config.c
    Progetto:   generico
    Descrizione:
        File di configurazione: deve contenere la tabella di gestione strutture
        dati in eeprom e i relativi valori di default (flash).

    Specifica di riferimento:

    Requisiti implementati:

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [0]     [2012-03-05]  [M.Mastrodonato]          1^ implementazione
        [1]     [2013-07-22]  [C.D'Onofrio]             DID data fixed
==============================================================================*/

#define EEPP_CONFIG_IF_OWNER

#include "EEPP.h"

/* Module inhibition filter */
#ifdef __EEPP_IS_PRESENT__

/**********************************************************************/
/** For write all dtc management & write                             **/
/**********************************************************************/
PRES_WriteStatus_t    EEPP_WriteStatus;
EEPP_Handle_t         EEPP_WriteDtcHandle;

void                  Eepp_UpdateCrc(EEPP_Handle_t hdl);
static void Eepp_WriteEnd(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle);
static void Eepp_WriteDtcRuntimeEnd(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle);
extern DRVD_RStatus_t Eepp_ReadEepromNow(EEPP_Handle_t handle);

const s16 EEDEF_ContatoreHall[ IPOC_HDL_MAX ] =
{
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

const MIRR_Data_t EEDEF_MirrorMemory =
{
  0x7FU, 0x7FU, 0x7FU, 0x7FU, CMMD_STANDSTILL,  CMMD_STANDSTILL
};
const uint8_t EEDEF_MirrorMemInit[NUM_MEMORIE] =
{
  FALSE, FALSE, FALSE
};

const DTC_EEPROM_Data EEDEF_DTC =
{
  {0x00U,0x00U}, {0x00U,0x00U,0x00U,0x00U,0x00U,0x00U, 0x00U}
};

const Ddmp_BlockExt_t EEDEF_DTC_EXT =
{
    /*Event_Counter*/
    0x00U
};

/* Not used anymore, kept for EEPROM retrocompatibility */
const PRES_Stroke_t EEDEF_MotorStroke[MOTP_MAX_HDL] =
{
 /* upFwVal  upFwCnt  dwBwVal  dwBwCnt */
  {  32000,    0U,    -32000,    0U   },
  {  32000,    0U,    -32000,    0U   },
  {  32000,    0U,    -32000,    0U   },
  {  32000,    0U,    -32000,    0U   },
  {  32000,    0U,    -32000,    0U   },
};

const EEPP_HeatTempParam_t EEDEF_HeatTempParam =
{
  500U,  /*Temp_lim */  
 -300,   /*Temp_range_min*/
  700U,  /*Temp_range_max*/ 
  350U,  /*Max_Av_Surf_Temp*/ 
  350U   /*Max_Av_Surf_Temp_StW*/
};

const EEPP_HeatTimeParam_t EEDEF_HeatTimeParam =
{
 /* T1   T_wait_1    T2     T3SW    T3HS   T_wait_2   T4     T_low */
  600U,    120U,   1800U,  4800U,  3600U,   1080U,   6300U,  2700U
};

const EEPP_HeatDutyParam_t EEDEF_HeatDutyParam =
{
 /* D_3    D_2   DWL1   DHL1   DLL1 */
   100U,   50U,   35U,   25U,   10U
};

const int16_t EEDEF_MemoM[ NUM_MOTORI * NUM_MEMORIE ] =
{ -32000, -32000, -32000, -32000,
  -32000, -32000, -32000, -32000,
  -32000, -32000, -32000, -32000,
};

const int16_t EEDEF_MemoDrivePos = { 0U };

const int16_t EEDEF_Measured_Motors_Stroke = { 0U };

const int16_t EEDEF_Nominal_Motors_Stroke = { 1500U };

const Model_ConfigValue_t EEDEF_ConfigModel =
{
    0U,     /* EEG_Status       */
    0U,     /* Init_MotorSlide  */
    450U,   /* PillarPosition   */
    336U,   /* Welcome_Distance */
    0u,     /* MotorNewPositionsToBeStored */
    0u,     /* ActualPosLoss               */
    0u,     /* Sparebits                   */
};

const int16_t  EEDEF_Current_Map_Backward[100] =
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

const uint8_t  EEDEF_Threshold_Antipinch_Bw  =  15u;
const uint8_t  EEDEF_AntiPinchAdaptation     =  0u;
const uint8_t  EEDEF_AntiPinch_Att_Backward  =  2u;

const uint16_t EEDEF_CounterVectorDownBwd[13] =
{
  0u, 0u, 0u, 0u, 0u, 0u,
  0u, 0u, 0u, 0u, 0u, 0u, 0u
};

const uint16_t EEDEF_CounterVectorUpBwd[13] =
{
  0u, 0u, 0u, 0u, 0u, 0u,
  0u, 0u, 0u, 0u, 0u, 0u, 0u
};

const uint16_t EEDEF_dummy[3] =
{
    0u, 0u, 0u
};

const int16_t EEDEF_dummyByte = 0 ;

void EEPP_ScheduleOperation(void);

const u16               EEDEF_ClearDTCpending      = {0x0000U};
const u08               EEDEF_CommEepromMapSign[8] = {"Comm01.0"};
const u08               EEDEF_ApplEepromMapSign[8] = {"Apll01.0"};
const u16               EEDEF_DTC_CRC              = {0x0000U};
const u16               EEDEF_DTC_CRC_EXT          = {0x0000U};

const u32               EEDEF_RandomSeed       = {0x01010101U};

const FUNP_ProxiCountriCode_t EEDEF_Proxi_Country_Code = FUNP_COUNTRY_WORLD;
const CMMD_DoorSts_t          EEDEF_DriverDoorStsInKeyOff = CMMD_CLOSED;

/***************************************
* EEPROM ADDRESS MAP
****************************************/
#if (DDMP_NUM_MAX_DTC_SAVED != 10U)
  //#error "Aggiornare l'inizializzazione della struttura dei DTC"
#endif

/* Configurare qui i valori di default per ciascun HANDLE */

/*______ 0000 Start BootLoader AREA __________________________________________*/
                /*      */
                /*      */
/*______ 0127 Stop  BootLoader AREA __________________________________________*/

/*______ 0128 Start Common AREA ______________________________________________*/
#define HANDLE_C_00_ROM_DATA     EEDEF_CommEepromMapSign              /*      */
#define HANDLE_C_01_ROM_DATA     EEDEF_BootSwId                       /* F180 */
#define HANDLE_C_02_ROM_DATA     EEDEF_ApplSwId                       /* F181 */
#define HANDLE_C_03_ROM_DATA     EEDEF_ApplDataId                     /* F182 */
#define HANDLE_C_04_ROM_DATA     EEDEF_BootSwFinger                   /* F183 */
#define HANDLE_C_05_ROM_DATA     EEDEF_ApplSwFinger                   /* F184 */
#define HANDLE_C_06_ROM_DATA     EEDEF_ApplDataFinger                 /* F185 */
#define HANDLE_C_07_ROM_DATA     EEDEF_VehManSparePartN               /* F187 */
#define HANDLE_C_08_ROM_DATA     EEDEF_VehManEcuSwN                   /* F188 */
#define HANDLE_C_09_ROM_DATA     EEDEF_VehManEcuSwCalN                /* F18A */
#define HANDLE_C_10_ROM_DATA     EEDEF_VehManEcuSwAppN                /* F18B */
#define HANDLE_C_11_ROM_DATA     EEDEF_EcuSerialNum                   /* F18C */
#define HANDLE_C_12_ROM_DATA     EEDEF_VehManEcuHwN                   /* F191 */
#define HANDLE_C_13_ROM_DATA     EEDEF_SysSuppEcuHwN                  /* F192 */
#define HANDLE_C_14_ROM_DATA     EEDEF_SysSuppEcuHwVerN               /* F193 */
#define HANDLE_C_15_ROM_DATA     EEDEF_SysSuppEcuSwN                  /* F194 */
#define HANDLE_C_16_ROM_DATA     EEDEF_SysSuppEcuSwVerN               /* F195 */
#define HANDLE_C_17_ROM_DATA     EEDEF_HomologationCode               /* F196 */
#define HANDLE_C_18_ROM_DATA     EEDEF_SincomAndFactory               /* F1A4 */
#define HANDLE_C_19_ROM_DATA     EEDEF_ISOCode                        /* F1A5 */
#define HANDLE_C_20_ROM_DATA     EEDEF_VINOriginal                    /*      */
#define HANDLE_C_21_ROM_DATA     EEDEF_VINCurrent                     /*      */
#define HANDLE_C_22_ROM_DATA     EEDEF_VINOdometer                    /*      */
#define HANDLE_C_23_ROM_DATA     EEDEF_VINLockState                   /*      */
#define HANDLE_C_24_ROM_DATA     EEDEF_VINOdoStart                    /*      */
#define HANDLE_C_25_ROM_DATA     EEDEF_RandomSeed                     /*      */
#define HANDLE_C_26_ROM_DATA     EEDEF_ProgStatus                     /*      */
#define HANDLE_C_27_ROM_DATA     EEDEF_EcuStatusInfo                  /*      */
/*______ 0575 Stop  Common AREA ______________________________________________*/

/*______ 0576 Start Applicative AREA _________________________________________*/
#define HANDLE_A_00_ROM_DATA     EEDEF_ApplEepromMapSign              /*      */
#define HANDLE_A_01_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_02_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_03_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_04_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_05_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_06_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_07_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_08_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_09_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_10_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_11_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_12_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_13_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_14_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_15_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_16_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_17_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_18_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_19_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_20_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_21_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_22_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_23_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_24_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_25_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_26_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_27_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_28_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_29_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_30_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_31_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_32_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_33_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_34_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_35_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_36_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_37_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_38_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_39_ROM_DATA     EEDEF_DTC                            /*      */
#define HANDLE_A_40_ROM_DATA     EEDEF_DTC_EXT                        /*      */
#define HANDLE_A_41_ROM_DATA     EEDEF_DTC_CRC                        /*      */
#define HANDLE_A_42_ROM_DATA     EEDEF_DTC_CRC_EXT                    /*      */
#define HANDLE_A_43_ROM_DATA     EEDEF_DTC_CRC                        /*      */
#define HANDLE_A_44_ROM_DATA     EEDEF_DTC_CRC_EXT                    /*      */
#define HANDLE_A_45_ROM_DATA     EEDEF_ContatoreHall                  /*      */
#define HANDLE_A_46_ROM_DATA     EEDEF_MotorStroke                    /*      */
#define HANDLE_A_47_ROM_DATA     EEDEF_MirrorMemory                   /* MCorr containing mirrors data */
#define HANDLE_A_48_ROM_DATA     EEDEF_MirrorMemory                   /* Mirror memory M1 */
#define HANDLE_A_49_ROM_DATA     EEDEF_MirrorMemory                   /* Mirror memory M2 */
#define HANDLE_A_50_ROM_DATA     EEDEF_MirrorMemory                   /* Mirror memory M3 */
#define HANDLE_A_51_ROM_DATA     EEDEF_MirrorMemInit                  /* Memory slots saved flag */
#define HANDLE_A_52_ROM_DATA     EEDEF_HeatTempParam
#define HANDLE_A_53_ROM_DATA     EEDEF_HeatTimeParam
#define HANDLE_A_54_ROM_DATA     EEDEF_HeatDutyParam
#define HANDLE_A_55_ROM_DATA     EEDEF_dummy                          /*      */
#define HANDLE_A_56_ROM_DATA     EEDEF_MemoM                          /*      */
#define HANDLE_A_57_ROM_DATA     EEDEF_MemoDrivePos                   /*      */
#define HANDLE_A_58_ROM_DATA     EEDEF_Measured_Motors_Stroke         /*      */
#define HANDLE_A_59_ROM_DATA     EEDEF_dummyByte                      /*      */
#define HANDLE_A_60_ROM_DATA     EEDEF_SysConfigProxy                 /*      */
#define HANDLE_A_61_ROM_DATA     EEDEF_TripABMsg                      /*      */
#define HANDLE_A_62_ROM_DATA     EEDEF_CheckEOLConfData               /*      */
#define HANDLE_A_63_ROM_DATA     EEDEF_BproxiConfig                   /*      */
#define HANDLE_A_64_ROM_DATA     EEDEF_BproxiValue                    /*      */
#define HANDLE_A_65_ROM_DATA     EEDEF_Current_Map_Backward           /*      */
#define HANDLE_A_66_ROM_DATA     EEDEF_Threshold_Antipinch_Bw         /*      */
#define HANDLE_A_67_ROM_DATA     EEDEF_CounterVectorDownBwd           /*      */
#define HANDLE_A_68_ROM_DATA     EEDEF_CounterVectorUpBwd             /*      */
#define HANDLE_A_69_ROM_DATA     EEDEF_ConfigModel                    /*      */
#define HANDLE_A_70_ROM_DATA     EEDEF_Nominal_Motors_Stroke          /*      */
#define HANDLE_A_71_ROM_DATA     EEDEF_AntiPinchAdaptation            /*      */
#define HANDLE_A_72_ROM_DATA     EEDEF_AntiPinch_Att_Backward         /*      */
#define HANDLE_A_73_ROM_DATA     EEDEF_Proxi_Country_Code             /*      */
#define HANDLE_A_74_ROM_DATA     EEDEF_DriverDoorStsInKeyOff          /*      */

/*______ 2047 Stop  Applicative AREA _________________________________________*/

/*______ 0000 Start BootLoader AREA __________________________________________*/


/*______ 0127 Stop  BootLoader AREA __________________________________________*/

/*______ 0128 Start Common AREA ______________________________________________*/
#define HANDLE_C_00_EE_ADDR     0x100U
#define HANDLE_C_01_EE_ADDR     HANDLE_C_00_EE_ADDR + sizeof(HANDLE_C_00_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_02_EE_ADDR     HANDLE_C_01_EE_ADDR + sizeof(HANDLE_C_01_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_03_EE_ADDR     HANDLE_C_02_EE_ADDR + sizeof(HANDLE_C_02_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_04_EE_ADDR     HANDLE_C_03_EE_ADDR + sizeof(HANDLE_C_03_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_05_EE_ADDR     HANDLE_C_04_EE_ADDR + sizeof(HANDLE_C_04_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_06_EE_ADDR     HANDLE_C_05_EE_ADDR + sizeof(HANDLE_C_05_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_07_EE_ADDR     HANDLE_C_06_EE_ADDR + sizeof(HANDLE_C_06_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_08_EE_ADDR     HANDLE_C_07_EE_ADDR + sizeof(HANDLE_C_07_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_09_EE_ADDR     HANDLE_C_08_EE_ADDR + sizeof(HANDLE_C_08_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_10_EE_ADDR     HANDLE_C_09_EE_ADDR + sizeof(HANDLE_C_09_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_11_EE_ADDR     HANDLE_C_10_EE_ADDR + sizeof(HANDLE_C_10_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_12_EE_ADDR     HANDLE_C_11_EE_ADDR + sizeof(HANDLE_C_11_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_13_EE_ADDR     HANDLE_C_12_EE_ADDR + sizeof(HANDLE_C_12_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_14_EE_ADDR     HANDLE_C_13_EE_ADDR + sizeof(HANDLE_C_13_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_15_EE_ADDR     HANDLE_C_14_EE_ADDR + sizeof(HANDLE_C_14_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_16_EE_ADDR     HANDLE_C_15_EE_ADDR + sizeof(HANDLE_C_15_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_17_EE_ADDR     HANDLE_C_16_EE_ADDR + sizeof(HANDLE_C_16_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_18_EE_ADDR     HANDLE_C_17_EE_ADDR + sizeof(HANDLE_C_17_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_19_EE_ADDR     HANDLE_C_18_EE_ADDR + sizeof(HANDLE_C_18_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_20_EE_ADDR     HANDLE_C_19_EE_ADDR + sizeof(HANDLE_C_19_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_21_EE_ADDR     HANDLE_C_20_EE_ADDR + sizeof(HANDLE_C_20_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_22_EE_ADDR     HANDLE_C_21_EE_ADDR + sizeof(HANDLE_C_21_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_23_EE_ADDR     HANDLE_C_22_EE_ADDR + sizeof(HANDLE_C_22_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_24_EE_ADDR     HANDLE_C_23_EE_ADDR + sizeof(HANDLE_C_23_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_25_EE_ADDR     HANDLE_C_24_EE_ADDR + sizeof(HANDLE_C_24_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_26_EE_ADDR     HANDLE_C_25_EE_ADDR + sizeof(HANDLE_C_25_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_C_27_EE_ADDR     HANDLE_C_26_EE_ADDR + sizeof(HANDLE_C_26_ROM_DATA)  + EE_CRC_SIZE
/*______ 0575 Stop  Common AREA ______________________________________________*/

/*______ 0576 Start Applicative AREA _________________________________________*/
#define HANDLE_A_00_EE_ADDR     0x500U
#define HANDLE_A_01_EE_ADDR     HANDLE_A_00_EE_ADDR + sizeof(HANDLE_A_00_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_02_EE_ADDR     HANDLE_A_01_EE_ADDR + sizeof(HANDLE_A_01_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_03_EE_ADDR     HANDLE_A_02_EE_ADDR + sizeof(HANDLE_A_02_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_04_EE_ADDR     HANDLE_A_03_EE_ADDR + sizeof(HANDLE_A_03_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_05_EE_ADDR     HANDLE_A_04_EE_ADDR + sizeof(HANDLE_A_04_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_06_EE_ADDR     HANDLE_A_05_EE_ADDR + sizeof(HANDLE_A_05_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_07_EE_ADDR     HANDLE_A_06_EE_ADDR + sizeof(HANDLE_A_06_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_08_EE_ADDR     HANDLE_A_07_EE_ADDR + sizeof(HANDLE_A_07_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_09_EE_ADDR     HANDLE_A_08_EE_ADDR + sizeof(HANDLE_A_08_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_10_EE_ADDR     HANDLE_A_09_EE_ADDR + sizeof(HANDLE_A_09_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_11_EE_ADDR     HANDLE_A_10_EE_ADDR + sizeof(HANDLE_A_10_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_12_EE_ADDR     HANDLE_A_11_EE_ADDR + sizeof(HANDLE_A_11_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_13_EE_ADDR     HANDLE_A_12_EE_ADDR + sizeof(HANDLE_A_12_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_14_EE_ADDR     HANDLE_A_13_EE_ADDR + sizeof(HANDLE_A_13_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_15_EE_ADDR     HANDLE_A_14_EE_ADDR + sizeof(HANDLE_A_14_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_16_EE_ADDR     HANDLE_A_15_EE_ADDR + sizeof(HANDLE_A_15_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_17_EE_ADDR     HANDLE_A_16_EE_ADDR + sizeof(HANDLE_A_16_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_18_EE_ADDR     HANDLE_A_17_EE_ADDR + sizeof(HANDLE_A_17_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_19_EE_ADDR     HANDLE_A_18_EE_ADDR + sizeof(HANDLE_A_18_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_20_EE_ADDR     HANDLE_A_19_EE_ADDR + sizeof(HANDLE_A_19_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_21_EE_ADDR     HANDLE_A_20_EE_ADDR + sizeof(HANDLE_A_20_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_22_EE_ADDR     HANDLE_A_21_EE_ADDR + sizeof(HANDLE_A_21_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_23_EE_ADDR     HANDLE_A_22_EE_ADDR + sizeof(HANDLE_A_22_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_24_EE_ADDR     HANDLE_A_23_EE_ADDR + sizeof(HANDLE_A_23_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_25_EE_ADDR     HANDLE_A_24_EE_ADDR + sizeof(HANDLE_A_24_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_26_EE_ADDR     HANDLE_A_25_EE_ADDR + sizeof(HANDLE_A_25_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_27_EE_ADDR     HANDLE_A_26_EE_ADDR + sizeof(HANDLE_A_26_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_28_EE_ADDR     HANDLE_A_27_EE_ADDR + sizeof(HANDLE_A_27_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_29_EE_ADDR     HANDLE_A_28_EE_ADDR + sizeof(HANDLE_A_28_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_30_EE_ADDR     HANDLE_A_29_EE_ADDR + sizeof(HANDLE_A_29_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_31_EE_ADDR     HANDLE_A_30_EE_ADDR + sizeof(HANDLE_A_30_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_32_EE_ADDR     HANDLE_A_31_EE_ADDR + sizeof(HANDLE_A_31_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_33_EE_ADDR     HANDLE_A_32_EE_ADDR + sizeof(HANDLE_A_32_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_34_EE_ADDR     HANDLE_A_33_EE_ADDR + sizeof(HANDLE_A_33_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_35_EE_ADDR     HANDLE_A_34_EE_ADDR + sizeof(HANDLE_A_34_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_36_EE_ADDR     HANDLE_A_35_EE_ADDR + sizeof(HANDLE_A_35_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_37_EE_ADDR     HANDLE_A_36_EE_ADDR + sizeof(HANDLE_A_36_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_38_EE_ADDR     HANDLE_A_37_EE_ADDR + sizeof(HANDLE_A_37_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_39_EE_ADDR     HANDLE_A_38_EE_ADDR + sizeof(HANDLE_A_38_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_40_EE_ADDR     HANDLE_A_39_EE_ADDR + sizeof(HANDLE_A_39_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_41_EE_ADDR     HANDLE_A_40_EE_ADDR + sizeof(HANDLE_A_40_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_42_EE_ADDR     HANDLE_A_41_EE_ADDR + sizeof(HANDLE_A_41_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_43_EE_ADDR     HANDLE_A_42_EE_ADDR + sizeof(HANDLE_A_42_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_44_EE_ADDR     HANDLE_A_43_EE_ADDR + sizeof(HANDLE_A_43_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_45_EE_ADDR     HANDLE_A_44_EE_ADDR + sizeof(HANDLE_A_44_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_46_EE_ADDR     HANDLE_A_45_EE_ADDR + sizeof(HANDLE_A_45_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_47_EE_ADDR     HANDLE_A_46_EE_ADDR + sizeof(HANDLE_A_46_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_48_EE_ADDR     HANDLE_A_47_EE_ADDR + sizeof(HANDLE_A_47_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_49_EE_ADDR     HANDLE_A_48_EE_ADDR + sizeof(HANDLE_A_48_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_50_EE_ADDR     HANDLE_A_49_EE_ADDR + sizeof(HANDLE_A_49_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_51_EE_ADDR     HANDLE_A_50_EE_ADDR + sizeof(HANDLE_A_50_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_52_EE_ADDR     HANDLE_A_51_EE_ADDR + sizeof(HANDLE_A_51_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_53_EE_ADDR     HANDLE_A_52_EE_ADDR + sizeof(HANDLE_A_52_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_54_EE_ADDR     HANDLE_A_53_EE_ADDR + sizeof(HANDLE_A_53_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_55_EE_ADDR     HANDLE_A_54_EE_ADDR + sizeof(HANDLE_A_54_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_56_EE_ADDR     HANDLE_A_55_EE_ADDR + sizeof(HANDLE_A_55_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_57_EE_ADDR     HANDLE_A_56_EE_ADDR + sizeof(HANDLE_A_56_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_58_EE_ADDR     HANDLE_A_57_EE_ADDR + sizeof(HANDLE_A_57_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_59_EE_ADDR     HANDLE_A_58_EE_ADDR + sizeof(HANDLE_A_58_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_60_EE_ADDR     HANDLE_A_59_EE_ADDR + sizeof(HANDLE_A_59_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_61_EE_ADDR     HANDLE_A_60_EE_ADDR + sizeof(HANDLE_A_60_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_62_EE_ADDR     HANDLE_A_61_EE_ADDR + sizeof(HANDLE_A_61_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_63_EE_ADDR     HANDLE_A_62_EE_ADDR + sizeof(HANDLE_A_62_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_64_EE_ADDR     HANDLE_A_63_EE_ADDR + sizeof(HANDLE_A_63_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_65_EE_ADDR     HANDLE_A_64_EE_ADDR + sizeof(HANDLE_A_64_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_66_EE_ADDR     HANDLE_A_65_EE_ADDR + sizeof(HANDLE_A_65_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_67_EE_ADDR     HANDLE_A_66_EE_ADDR + sizeof(HANDLE_A_66_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_68_EE_ADDR     HANDLE_A_67_EE_ADDR + sizeof(HANDLE_A_67_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_69_EE_ADDR     HANDLE_A_68_EE_ADDR + sizeof(HANDLE_A_68_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_70_EE_ADDR     HANDLE_A_69_EE_ADDR + sizeof(HANDLE_A_69_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_71_EE_ADDR     HANDLE_A_70_EE_ADDR + sizeof(HANDLE_A_70_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_72_EE_ADDR     HANDLE_A_71_EE_ADDR + sizeof(HANDLE_A_71_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_73_EE_ADDR     HANDLE_A_72_EE_ADDR + sizeof(HANDLE_A_72_ROM_DATA)  + EE_CRC_SIZE
#define HANDLE_A_74_EE_ADDR     HANDLE_A_73_EE_ADDR + sizeof(HANDLE_A_73_ROM_DATA)  + EE_CRC_SIZE
/*______ 2047 Stop  Applicative AREA _________________________________________*/

/*********************************
*  EEPROM MANAGEMENT TABLE
*********************************/

/* Configurare per ciascun Handle: RAM_data, PwrOn_Load e Mirror_Handle */

/* NB!!  */
/* NB!! Settare in EEPROM.h il parametro EEPROM_BUFFER_SIZE con un valore >= dell'Handle di dimensione maggiore */
/* NB!!  */

const EEPP_CfgTable_t eepromTable[EEPP_HDL_MAX] =
{
/*______ 0000 Start BootLoader AREA __________________________________________*/
    /* Handle                              ram_data                       rom_data                    ee_Addr                   ee_size                            pwron_load            mirror_handle   */


/*______ 0127 Stop  BootLoader AREA __________________________________________*/

/*______ 0128 Start Common AREA ______________________________________________*/
    /* Handle                              ram_data                       rom_data                    ee_Addr                   ee_size                            pwron_load            mirror_handle   */
  { /* EEPP_HDL_CommEepromMapSign   , */   &EERAM_CommEepromMapSign   ,   &HANDLE_C_00_ROM_DATA   ,   HANDLE_C_00_EE_ADDR   ,   sizeof(HANDLE_C_00_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_BootSwId            , */   &EERAM_BootSwId            ,   &HANDLE_C_01_ROM_DATA   ,   HANDLE_C_01_EE_ADDR   ,   sizeof(HANDLE_C_01_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ApplSwId            , */   &EERAM_ApplSwId            ,   &HANDLE_C_02_ROM_DATA   ,   HANDLE_C_02_EE_ADDR   ,   sizeof(HANDLE_C_02_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ApplDataId          , */   &EERAM_ApplDataId          ,   &HANDLE_C_03_ROM_DATA   ,   HANDLE_C_03_EE_ADDR   ,   sizeof(HANDLE_C_03_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_BootSwFinger        , */   &EERAM_BootSwFinger        ,   &HANDLE_C_04_ROM_DATA   ,   HANDLE_C_04_EE_ADDR   ,   sizeof(HANDLE_C_04_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ApplSwFinger        , */   &EERAM_ApplSwFinger        ,   &HANDLE_C_05_ROM_DATA   ,   HANDLE_C_05_EE_ADDR   ,   sizeof(HANDLE_C_05_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ApplDataFinger      , */   &EERAM_ApplDataFinger      ,   &HANDLE_C_06_ROM_DATA   ,   HANDLE_C_06_EE_ADDR   ,   sizeof(HANDLE_C_06_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VehManSparePartN    , */   &EERAM_VehManSparePartN    ,   &HANDLE_C_07_ROM_DATA   ,   HANDLE_C_07_EE_ADDR   ,   sizeof(HANDLE_C_07_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VehManEcuSwN        , */   &EERAM_VehManEcuSwN        ,   &HANDLE_C_08_ROM_DATA   ,   HANDLE_C_08_EE_ADDR   ,   sizeof(HANDLE_C_08_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VehManEcuSwCalN     , */   &EERAM_VehManEcuSwCalN     ,   &HANDLE_C_09_ROM_DATA   ,   HANDLE_C_09_EE_ADDR   ,   sizeof(HANDLE_C_09_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VehManEcuSwAppN     , */   &EERAM_VehManEcuSwAppN     ,   &HANDLE_C_10_ROM_DATA   ,   HANDLE_C_10_EE_ADDR   ,   sizeof(HANDLE_C_10_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_EcuSerialNum        , */   &EERAM_EcuSerialNum        ,   &HANDLE_C_11_ROM_DATA   ,   HANDLE_C_11_EE_ADDR   ,   sizeof(HANDLE_C_11_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VehManEcuHwN        , */   &EERAM_VehManEcuHwN        ,   &HANDLE_C_12_ROM_DATA   ,   HANDLE_C_12_EE_ADDR   ,   sizeof(HANDLE_C_12_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysSuppEcuHwN       , */   &EERAM_SysSuppEcuHwN       ,   &HANDLE_C_13_ROM_DATA   ,   HANDLE_C_13_EE_ADDR   ,   sizeof(HANDLE_C_13_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysSuppEcuHwVerN    , */   &EERAM_SysSuppEcuHwVerN    ,   &HANDLE_C_14_ROM_DATA   ,   HANDLE_C_14_EE_ADDR   ,   sizeof(HANDLE_C_14_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysSuppEcuSwN       , */   &EERAM_SysSuppEcuSwN       ,   &HANDLE_C_15_ROM_DATA   ,   HANDLE_C_15_EE_ADDR   ,   sizeof(HANDLE_C_15_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysSuppEcuSwVerN    , */   &EERAM_SysSuppEcuSwVerN    ,   &HANDLE_C_16_ROM_DATA   ,   HANDLE_C_16_EE_ADDR   ,   sizeof(HANDLE_C_16_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_HomologationCode    , */   &EERAM_HomologationCode    ,   &HANDLE_C_17_ROM_DATA   ,   HANDLE_C_17_EE_ADDR   ,   sizeof(HANDLE_C_17_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SincomAndFactory    , */   &EERAM_SincomAndFactory    ,   &HANDLE_C_18_ROM_DATA   ,   HANDLE_C_18_EE_ADDR   ,   sizeof(HANDLE_C_18_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ISOCode             , */   &EERAM_ISOCode             ,   &HANDLE_C_19_ROM_DATA   ,   HANDLE_C_19_EE_ADDR   ,   sizeof(HANDLE_C_19_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VINOriginal         , */   &EERAM_VINOriginal         ,   &HANDLE_C_20_ROM_DATA   ,   HANDLE_C_20_EE_ADDR   ,   sizeof(HANDLE_C_20_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VINCurrent          , */   &EERAM_VINCurrent          ,   &HANDLE_C_21_ROM_DATA   ,   HANDLE_C_21_EE_ADDR   ,   sizeof(HANDLE_C_21_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VINOdometer         , */   &EERAM_VINOdometer         ,   &HANDLE_C_22_ROM_DATA   ,   HANDLE_C_22_EE_ADDR   ,   sizeof(HANDLE_C_22_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VINLockState        , */   &EERAM_VINLockState        ,   &HANDLE_C_23_ROM_DATA   ,   HANDLE_C_23_EE_ADDR   ,   sizeof(HANDLE_C_23_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_VINOdoStart         , */   &EERAM_VINOdoStart         ,   &HANDLE_C_24_ROM_DATA   ,   HANDLE_C_24_EE_ADDR   ,   sizeof(HANDLE_C_24_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_RandomSeed          , */   &EERAM_RandomSeed          ,   &HANDLE_C_25_ROM_DATA   ,   HANDLE_C_25_EE_ADDR   ,   sizeof(HANDLE_C_25_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ProgStatus          , */   &EERAM_ProgStatus          ,   &HANDLE_C_26_ROM_DATA   ,   HANDLE_C_26_EE_ADDR   ,   sizeof(HANDLE_C_26_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_EcuStatusInfo       , */   &EERAM_EcuStatusInfo       ,   &HANDLE_C_27_ROM_DATA   ,   HANDLE_C_27_EE_ADDR   ,   sizeof(HANDLE_C_27_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
/*______ 0575 Stop  Common AREA ______________________________________________*/

/*______ 0576 Start Applicative AREA _________________________________________*/

    /* Handle                              ram_data                            rom_data                    ee_Addr                   ee_size                            pwron_load            mirror_handle   */
  { /* EEPP_HDL_ApplEepromMapSign   , */   &EERAM_ApplEepromMapSign     ,      &HANDLE_A_00_ROM_DATA   ,   HANDLE_A_00_EE_ADDR   ,   sizeof(HANDLE_A_00_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_0               , */   &EERAM_DTC[0]                ,      &HANDLE_A_01_ROM_DATA   ,   HANDLE_A_01_EE_ADDR   ,   sizeof(HANDLE_A_01_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_0           , */   &EERAM_DTC_EXT[0]            ,      &HANDLE_A_02_ROM_DATA   ,   HANDLE_A_02_EE_ADDR   ,   sizeof(HANDLE_A_02_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_1               , */   &EERAM_DTC[1]                ,      &HANDLE_A_03_ROM_DATA   ,   HANDLE_A_03_EE_ADDR   ,   sizeof(HANDLE_A_03_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_1           , */   &EERAM_DTC_EXT[1]            ,      &HANDLE_A_04_ROM_DATA   ,   HANDLE_A_04_EE_ADDR   ,   sizeof(HANDLE_A_04_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_2               , */   &EERAM_DTC[2]                ,      &HANDLE_A_05_ROM_DATA   ,   HANDLE_A_05_EE_ADDR   ,   sizeof(HANDLE_A_05_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_2           , */   &EERAM_DTC_EXT[2]            ,      &HANDLE_A_06_ROM_DATA   ,   HANDLE_A_06_EE_ADDR   ,   sizeof(HANDLE_A_06_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_3               , */   &EERAM_DTC[3]                ,      &HANDLE_A_07_ROM_DATA   ,   HANDLE_A_07_EE_ADDR   ,   sizeof(HANDLE_A_07_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_3           , */   &EERAM_DTC_EXT[3]            ,      &HANDLE_A_08_ROM_DATA   ,   HANDLE_A_08_EE_ADDR   ,   sizeof(HANDLE_A_08_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_4               , */   &EERAM_DTC[4]                ,      &HANDLE_A_09_ROM_DATA   ,   HANDLE_A_09_EE_ADDR   ,   sizeof(HANDLE_A_09_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_4           , */   &EERAM_DTC_EXT[4]            ,      &HANDLE_A_10_ROM_DATA   ,   HANDLE_A_10_EE_ADDR   ,   sizeof(HANDLE_A_10_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_5               , */   &EERAM_DTC[5]                ,      &HANDLE_A_11_ROM_DATA   ,   HANDLE_A_11_EE_ADDR   ,   sizeof(HANDLE_A_11_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_5           , */   &EERAM_DTC_EXT[5]            ,      &HANDLE_A_12_ROM_DATA   ,   HANDLE_A_12_EE_ADDR   ,   sizeof(HANDLE_A_12_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_6               , */   &EERAM_DTC[6]                ,      &HANDLE_A_13_ROM_DATA   ,   HANDLE_A_13_EE_ADDR   ,   sizeof(HANDLE_A_13_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_6           , */   &EERAM_DTC_EXT[6]            ,      &HANDLE_A_14_ROM_DATA   ,   HANDLE_A_14_EE_ADDR   ,   sizeof(HANDLE_A_14_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_7               , */   &EERAM_DTC[7]                ,      &HANDLE_A_15_ROM_DATA   ,   HANDLE_A_15_EE_ADDR   ,   sizeof(HANDLE_A_15_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_7           , */   &EERAM_DTC_EXT[7]            ,      &HANDLE_A_16_ROM_DATA   ,   HANDLE_A_16_EE_ADDR   ,   sizeof(HANDLE_A_16_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_8               , */   &EERAM_DTC[8]                ,      &HANDLE_A_17_ROM_DATA   ,   HANDLE_A_17_EE_ADDR   ,   sizeof(HANDLE_A_17_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_8           , */   &EERAM_DTC_EXT[8]            ,      &HANDLE_A_18_ROM_DATA   ,   HANDLE_A_18_EE_ADDR   ,   sizeof(HANDLE_A_18_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_9               , */   &EERAM_DTC[9]                ,      &HANDLE_A_19_ROM_DATA   ,   HANDLE_A_19_EE_ADDR   ,   sizeof(HANDLE_A_19_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_9           , */   &EERAM_DTC_EXT[9]            ,      &HANDLE_A_20_ROM_DATA   ,   HANDLE_A_20_EE_ADDR   ,   sizeof(HANDLE_A_20_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_0_BIS           , */   &EERAM_DTC[0]                ,      &HANDLE_A_21_ROM_DATA   ,   HANDLE_A_21_EE_ADDR   ,   sizeof(HANDLE_A_21_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_0_BIS       , */   &EERAM_DTC_EXT[0]            ,      &HANDLE_A_22_ROM_DATA   ,   HANDLE_A_22_EE_ADDR   ,   sizeof(HANDLE_A_22_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_1_BIS           , */   &EERAM_DTC[1]                ,      &HANDLE_A_23_ROM_DATA   ,   HANDLE_A_23_EE_ADDR   ,   sizeof(HANDLE_A_23_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_1_BIS       , */   &EERAM_DTC_EXT[1]            ,      &HANDLE_A_24_ROM_DATA   ,   HANDLE_A_24_EE_ADDR   ,   sizeof(HANDLE_A_24_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_2_BIS           , */   &EERAM_DTC[2]                ,      &HANDLE_A_25_ROM_DATA   ,   HANDLE_A_25_EE_ADDR   ,   sizeof(HANDLE_A_25_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_2_BIS       , */   &EERAM_DTC_EXT[2]            ,      &HANDLE_A_26_ROM_DATA   ,   HANDLE_A_26_EE_ADDR   ,   sizeof(HANDLE_A_26_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_3_BIS           , */   &EERAM_DTC[3]                ,      &HANDLE_A_27_ROM_DATA   ,   HANDLE_A_27_EE_ADDR   ,   sizeof(HANDLE_A_27_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_3_BIS       , */   &EERAM_DTC_EXT[3]            ,      &HANDLE_A_28_ROM_DATA   ,   HANDLE_A_28_EE_ADDR   ,   sizeof(HANDLE_A_28_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_4_BIS           , */   &EERAM_DTC[4]                ,      &HANDLE_A_29_ROM_DATA   ,   HANDLE_A_29_EE_ADDR   ,   sizeof(HANDLE_A_29_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_4_BIS       , */   &EERAM_DTC_EXT[4]            ,      &HANDLE_A_30_ROM_DATA   ,   HANDLE_A_30_EE_ADDR   ,   sizeof(HANDLE_A_30_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_5_BIS           , */   &EERAM_DTC[5]                ,      &HANDLE_A_31_ROM_DATA   ,   HANDLE_A_31_EE_ADDR   ,   sizeof(HANDLE_A_31_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_5_BIS       , */   &EERAM_DTC_EXT[5]            ,      &HANDLE_A_32_ROM_DATA   ,   HANDLE_A_32_EE_ADDR   ,   sizeof(HANDLE_A_32_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_6_BIS           , */   &EERAM_DTC[6]                ,      &HANDLE_A_33_ROM_DATA   ,   HANDLE_A_33_EE_ADDR   ,   sizeof(HANDLE_A_33_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_6_BIS       , */   &EERAM_DTC_EXT[6]            ,      &HANDLE_A_34_ROM_DATA   ,   HANDLE_A_34_EE_ADDR   ,   sizeof(HANDLE_A_34_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_7_BIS           , */   &EERAM_DTC[7]                ,      &HANDLE_A_35_ROM_DATA   ,   HANDLE_A_35_EE_ADDR   ,   sizeof(HANDLE_A_35_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_7_BIS       , */   &EERAM_DTC_EXT[7]            ,      &HANDLE_A_36_ROM_DATA   ,   HANDLE_A_36_EE_ADDR   ,   sizeof(HANDLE_A_36_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_8_BIS           , */   &EERAM_DTC[8]                ,      &HANDLE_A_37_ROM_DATA   ,   HANDLE_A_37_EE_ADDR   ,   sizeof(HANDLE_A_37_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_8_BIS       , */   &EERAM_DTC_EXT[8]            ,      &HANDLE_A_38_ROM_DATA   ,   HANDLE_A_38_EE_ADDR   ,   sizeof(HANDLE_A_38_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_9_BIS           , */   &EERAM_DTC[9]                ,      &HANDLE_A_39_ROM_DATA   ,   HANDLE_A_39_EE_ADDR   ,   sizeof(HANDLE_A_39_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_EXT_9_BIS       , */   &EERAM_DTC_EXT[9]            ,      &HANDLE_A_40_ROM_DATA   ,   HANDLE_A_40_EE_ADDR   ,   sizeof(HANDLE_A_40_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_CRC             , */   &EERAM_DTC_CRC               ,      &HANDLE_A_41_ROM_DATA   ,   HANDLE_A_41_EE_ADDR   ,   sizeof(HANDLE_A_41_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_CRC_EXT         , */   &EERAM_DTC_CRC_EXT           ,      &HANDLE_A_42_ROM_DATA   ,   HANDLE_A_42_EE_ADDR   ,   sizeof(HANDLE_A_42_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_CRC_BIS         , */   &EERAM_DTC_CRC               ,      &HANDLE_A_43_ROM_DATA   ,   HANDLE_A_43_EE_ADDR   ,   sizeof(HANDLE_A_43_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DTC_CRC_EXT_BIS     , */   &EERAM_DTC_CRC_EXT           ,      &HANDLE_A_44_ROM_DATA   ,   HANDLE_A_44_EE_ADDR   ,   sizeof(HANDLE_A_44_ROM_DATA)   ,   EEPP_NO_INIT      ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ContatoreHall       , */   &EERAM_ContatoreHall         ,      &HANDLE_A_45_ROM_DATA   ,   HANDLE_A_45_EE_ADDR   ,   sizeof(HANDLE_A_45_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MotorStroke         , */   &EERAM_MotorStroke           ,      &HANDLE_A_46_ROM_DATA   ,   HANDLE_A_46_EE_ADDR   ,   sizeof(HANDLE_A_46_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorMCorr         , */   &EERAM_MirrorMCorr           ,      &HANDLE_A_47_ROM_DATA   ,   HANDLE_A_47_EE_ADDR   ,   sizeof(HANDLE_A_47_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorM1            , */   &EERAM_MirrorM1              ,      &HANDLE_A_48_ROM_DATA   ,   HANDLE_A_48_EE_ADDR   ,   sizeof(HANDLE_A_48_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorM2            , */   &EERAM_MirrorM2              ,      &HANDLE_A_49_ROM_DATA   ,   HANDLE_A_49_EE_ADDR   ,   sizeof(HANDLE_A_49_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorM3            , */   &EERAM_MirrorM3              ,      &HANDLE_A_50_ROM_DATA   ,   HANDLE_A_50_EE_ADDR   ,   sizeof(HANDLE_A_50_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorMemInit       , */   &EERAM_MirrorMemInit         ,      &HANDLE_A_51_ROM_DATA   ,   HANDLE_A_51_EE_ADDR   ,   sizeof(HANDLE_A_51_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_HeatTempParam       , */   &EERAM_HeatTempParam         ,      &HANDLE_A_52_ROM_DATA   ,   HANDLE_A_52_EE_ADDR   ,   sizeof(HANDLE_A_52_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_HeatTimeParam       , */   &EERAM_HeatTimeParam         ,      &HANDLE_A_53_ROM_DATA   ,   HANDLE_A_53_EE_ADDR   ,   sizeof(HANDLE_A_53_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_HeatDutyParam       , */   &EERAM_HeatDutyParam         ,      &HANDLE_A_54_ROM_DATA   ,   HANDLE_A_54_EE_ADDR   ,   sizeof(HANDLE_A_54_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_Dummy               , */   &EERAM_dummy                 ,      &HANDLE_A_55_ROM_DATA   ,   HANDLE_A_55_EE_ADDR   ,   sizeof(HANDLE_A_55_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MemoM               , */   &EERAM_MemoM                 ,      &HANDLE_A_56_ROM_DATA   ,   HANDLE_A_56_EE_ADDR   ,   sizeof(HANDLE_A_56_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MEMODRIVEPOS        , */   &EERAM_MemoDrivePos          ,      &HANDLE_A_57_ROM_DATA   ,   HANDLE_A_57_EE_ADDR   ,   sizeof(HANDLE_A_57_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MeasuredMotorStroke , */   &EERAM_Measured_Motors_Stroke,      &HANDLE_A_58_ROM_DATA   ,   HANDLE_A_58_EE_ADDR   ,   sizeof(HANDLE_A_58_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_NominalMotorStroke  , */   &EERAM_Nominal_Motors_Stroke ,      &HANDLE_A_59_ROM_DATA   ,   HANDLE_A_59_EE_ADDR   ,   sizeof(HANDLE_A_59_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysConfigProxy      , */   &EERAM_SysConfigProxy        ,      &HANDLE_A_60_ROM_DATA   ,   HANDLE_A_60_EE_ADDR   ,   sizeof(HANDLE_A_60_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_SysConfigProxy      , */   &EERAM_TripABMsg             ,      &HANDLE_A_61_ROM_DATA   ,   HANDLE_A_61_EE_ADDR   ,   sizeof(HANDLE_A_61_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_CheckEOLConfData    , */   &EERAM_CheckEOLConfData      ,      &HANDLE_A_62_ROM_DATA   ,   HANDLE_A_62_EE_ADDR   ,   sizeof(HANDLE_A_62_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_BproxiBitfield      , */   &EERAM_BproxiConfig          ,      &HANDLE_A_63_ROM_DATA   ,   HANDLE_A_63_EE_ADDR   ,   sizeof(HANDLE_A_63_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_BproxiValue         , */   &EERAM_BproxiValue           ,      &HANDLE_A_64_ROM_DATA   ,   HANDLE_A_64_EE_ADDR   ,   sizeof(HANDLE_A_64_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_CurrentMapBw        , */   &EERAM_Current_Map_Backward  ,      &HANDLE_A_65_ROM_DATA   ,   HANDLE_A_65_EE_ADDR   ,   sizeof(HANDLE_A_65_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_AntiPinch_Threshold_Bw,*/  &EERAM_Threshold_Antipinch_Backward,&HANDLE_A_66_ROM_DATA   ,   HANDLE_A_66_EE_ADDR   ,   sizeof(HANDLE_A_66_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorRecallRequest,  */   &EERAM_CounterVectorDownBwd,        &HANDLE_A_67_ROM_DATA   ,   HANDLE_A_67_EE_ADDR   ,   sizeof(HANDLE_A_67_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_MirrorRecallRequest,  */   &EERAM_CounterVectorUpBwd,          &HANDLE_A_68_ROM_DATA   ,   HANDLE_A_68_EE_ADDR   ,   sizeof(HANDLE_A_68_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_ConfigModel         , */   &EERAM_ConfigModel           ,      &HANDLE_A_69_ROM_DATA   ,   HANDLE_A_69_EE_ADDR   ,   sizeof(HANDLE_A_69_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_NominalMotorStroke  , */   &EERAM_Nominal_Motors_Stroke ,      &HANDLE_A_70_ROM_DATA   ,   HANDLE_A_70_EE_ADDR   ,   sizeof(HANDLE_A_70_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_AntiPinchAdaptation,  */   &EERAM_AntiPinchAdaptation,         &HANDLE_A_71_ROM_DATA   ,   HANDLE_A_71_EE_ADDR   ,   sizeof(HANDLE_A_71_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_AntiPinch_Att_Backward,*/  &EERAM_Threshold_Att_Backward,      &HANDLE_A_72_ROM_DATA   ,   HANDLE_A_72_EE_ADDR   ,   sizeof(HANDLE_A_72_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_Proxi_Country_Code    ,*/  &EERAM_Proxi_Country_Code,          &HANDLE_A_73_ROM_DATA   ,   HANDLE_A_73_EE_ADDR   ,   sizeof(HANDLE_A_73_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    },
  { /* EEPP_HDL_DriverDoorStsInKeyOff ,*/  &EERAM_DriverDoorStsInKeyOff,       &HANDLE_A_74_ROM_DATA   ,   HANDLE_A_74_EE_ADDR   ,   sizeof(HANDLE_A_74_ROM_DATA)   ,   EEPP_INIT_RUN     ,   /* EEPP_HDL_MAX */    }
  /*______ 2047 Stop  Applicative AREA _________________________________________*/
};


// *------------------------------------------------------------------------- *
// *       Global Variables                                                   *
// *------------------------------------------------------------------------- *


// *------------------------------------------------------------------------- *
// *       Callback Functions                                                 *
// *------------------------------------------------------------------------- *

void EEPP_UserInit(void)
{
  /* Dtc structure CRC check */

    EEPP_Handle_t hdl ;
    u16 EEPROM_CRC;
    u16 EEPROM_CRC_EXT;

    EEPROM_CRC        = EERAM_DTC_CRC;
    EEPROM_CRC_EXT    = EERAM_DTC_CRC_EXT;
    EERAM_DTC_CRC     = 0x0000U;
    EERAM_DTC_CRC_EXT = 0x0000U;

    /* Calculate CRC Standard and Extended */
    for ( hdl = (EEPP_Handle_t)EEPP_HDL_DTC_0; hdl < EEPP_HDL_DTC_0_BIS; hdl++)
    {
        Eepp_UpdateCrc(hdl);
    }

    EEPP_SAFETY_ACK()

    /* Check CRC Standard */
    if (EEPROM_CRC != EERAM_DTC_CRC)
    {
        /* Error! The 1st DTC copy is corrupted, load the 2nd copy */
        for ( hdl = (EEPP_Handle_t)EEPP_HDL_DTC_0_BIS; hdl < EEPP_HDL_DTC_CRC; hdl+=2)
        {
            Eepp_ReadEepromNow(hdl);

            EEPP_SAFETY_ACK()
        }
        /* Load the 2nd CRC copy */
        Eepp_ReadEepromNow(EEPP_HDL_DTC_CRC_BIS);
        /* Re-calculate the dtc CRC*/
        EEPROM_CRC = EERAM_DTC_CRC;

        EEPP_SAFETY_ACK()

        for ( hdl = (EEPP_Handle_t)EEPP_HDL_DTC_0; hdl < EEPP_HDL_DTC_EXT_9; hdl+=2)
        {
            Eepp_UpdateCrc(hdl);
        }

        EEPP_SAFETY_ACK()

        /* Check the 2nd CRC */
        if (EEPROM_CRC != EERAM_DTC_CRC)
        {
            /* Error! Load default parameters */
            for ( hdl = (EEPP_Handle_t)EEPP_HDL_DTC_0; hdl < EEPP_HDL_DTC_EXT_9; hdl+=2)
            {
                memcpy(eepromTable[hdl].ram_data, eepromTable[hdl].rom_data, eepromTable[hdl].data_size);
            }
        }
    }

    EEPP_SAFETY_ACK()

    /* Check CRC Extended */
    if (EEPROM_CRC_EXT != EERAM_DTC_CRC_EXT)
    {
        /* Error! The 1st DTC_EXT copy is corrupted, load the 2nd copy */
        for (hdl = (EEPP_Handle_t)EEPP_HDL_DTC_EXT_0_BIS; hdl < EEPP_HDL_DTC_CRC; hdl+=2)
        {
            Eepp_ReadEepromNow(hdl);

            EEPP_SAFETY_ACK()
        }

        /* Load the 2nd CRC copy */
        Eepp_ReadEepromNow(EEPP_HDL_DTC_CRC_EXT_BIS);
        /* Re-calculate the dtc CRC*/
        EEPROM_CRC_EXT = EERAM_DTC_CRC_EXT;

        EEPP_SAFETY_ACK()

        for (hdl = (EEPP_Handle_t)EEPP_HDL_DTC_EXT_0; hdl < EEPP_HDL_DTC_0_BIS; hdl+=2)
        {
            Eepp_UpdateCrc(hdl);
        }

        EEPP_SAFETY_ACK()

        /* Check the 2nd CRC */
        if (EEPROM_CRC_EXT != EERAM_DTC_CRC_EXT)
        {
            /* Error! Load default parameters */
            for (hdl = (EEPP_Handle_t)EEPP_HDL_DTC_EXT_0; hdl < EEPP_HDL_DTC_0_BIS; hdl+=2)
            {
                memcpy(eepromTable[hdl].ram_data, eepromTable[hdl].rom_data, eepromTable[hdl].data_size);
            }
        }
    }

    /* Init write dtc state machine */
    EEPP_WriteStatus = PRES_WR_IDLE;
}


PRES_WriteStatus_t EEPP_WriteDtcRuntime(void)
{
  EEPP_WriteDtcHandle = EEPP_HDL_DTC_0;
  EEPP_WriteStatus  = PRES_WR_NOT_TERMINATED;

  EEPP_WriteData(EEPP_WriteDtcHandle, Eepp_WriteDtcRuntimeEnd);

  return(EEPP_WriteStatus);
}

void EEPP_ShutdownSaveReq(void)
{

}

void EEPP_ScheduleOperation(void)
{
  /* PROBLEMA: quando la LPMS chiama le shutdown i task non girano, quindi la EEPP non viene schedulata!!!
   * SOLUZIONE ATTUALE: chiamare la EEPP_Mgm continuamente nella procedura di shutdown finchè non ha finito
   *                      di scrivere tutto. Vantaggio: non perdiamo eventuali richieste pendenti inserite
   *                      appena prima di aver chiamato lo shutdown.
   */

  uint16_t          delayCnt;

  while (EEPP_OCCUPIED == EEPP_Mgm())
  {
    /* EEPROM busy, delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
    for (delayCnt = 0U; delayCnt < 3400U; delayCnt++)
    {
      NOP();
    }

    EEPP_SAFETY_ACK()
  }
}

/*************************************************************************
          LOCAL FUNCTIONS
*************************************************************************/

void Eepp_UpdateCrc(EEPP_Handle_t hdl)
{
  u08 *DataPnt;
  u08 i;

  if(hdl & 0x01)
  {
    /* odd = DTC_EXT */
    DataPnt = (u08*) &EERAM_DTC_EXT[(hdl - EEPP_HDL_DTC_EXT_0)>>1];

    for ( i = 0U; i < sizeof(Ddmp_BlockExt_t); i++)
    {
      //CalculateCRC16(*DataPnt, &EERAM_DTC_CRC_EXT);
      EERAM_DTC_CRC_EXT = crcFast(DataPnt, 2U);
      DataPnt++;
    }
  }
  else
  {
    /* even  = DTC */
    DataPnt = (u08*) &EERAM_DTC[(hdl - EEPP_HDL_DTC_0)>>1];

    for ( i = 0U; i < sizeof(Ddmp_Block_t); i++)
    {
      //CalculateCRC16(*DataPnt, &EERAM_DTC_CRC);
      EERAM_DTC_CRC = crcFast(DataPnt, 2U);
      DataPnt++;
    }
  }
}

void EEPP_EcuPowerOff(void)
{
  /* Schedule pending write requests */
  EEPP_ScheduleOperation();

  //EEPP_WriteData(EEPP_HDL_EcuTime,       Eepp_WriteEnd);
  //EEPP_ScheduleOperation();

  if (DDMP_GetDTCSaveStatus() == DDMP_SAVING_NEEDED)
  {
    EEPP_WriteDtcHandle = EEPP_HDL_DTC_0;
    EERAM_DTC_CRC     = 0x0000U;
    EERAM_DTC_CRC_EXT = 0x0000U;
    while(EEPP_WriteDtcHandle <= EEPP_HDL_DTC_CRC_EXT_BIS)
    {
      if(EEPP_WriteDtcHandle < EEPP_HDL_DTC_CRC)
      {
        EEPP_WriteData(EEPP_WriteDtcHandle, Eepp_WriteEnd);

        if (EEPP_WriteDtcHandle < EEPP_HDL_DTC_0_BIS)
        {
            Eepp_UpdateCrc(EEPP_WriteDtcHandle);
        }
      }
      else if (EEPP_WriteDtcHandle > EEPP_HDL_DTC_CRC_EXT_BIS)
      {
        EEPP_WriteStatus = PRES_WR_TERMINATED;
      }
      else
      {
        /* write CRC */
        EEPP_WriteData(EEPP_WriteDtcHandle, Eepp_WriteEnd);
      }
      EEPP_WriteDtcHandle++;
      EEPP_ScheduleOperation();
    }
  }
  else
  {
  }
}

static void Eepp_WriteDtcRuntimeEnd(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle)
{
  EEPP_WriteDtcHandle++;
  
  if(EEPP_WriteDtcHandle < EEPP_HDL_DTC_CRC)
  {
    EEPP_WriteData(EEPP_WriteDtcHandle, Eepp_WriteDtcRuntimeEnd);

    if (EEPP_WriteDtcHandle < EEPP_HDL_DTC_0_BIS)
    {
        Eepp_UpdateCrc(EEPP_WriteDtcHandle);
    }
  }
  else if (EEPP_WriteDtcHandle > EEPP_HDL_DTC_CRC_EXT_BIS)
  {
    EEPP_WriteStatus = PRES_WR_TERMINATED;
  }
  else
  {
    /* write CRC */
    EEPP_WriteData(EEPP_WriteDtcHandle, Eepp_WriteDtcRuntimeEnd);
  }
}

static void Eepp_WriteEnd(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle)
{
  EEPP_WriteStatus = PRES_WR_TERMINATED;
}

void EEPP_EraseCompleted(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle)
{
  UDSA_EraseEepromCompleted(returnStatus);
}

/**
* @brief This function is used to update the status (present/absent) of the proxable functions.
* @author Francesco Talarico
* @param none
* @param none
* @return none
*/
void EEPP_UpdateFunctionByProxi(void)
{
  DOVFC_EnableDisable (DOVFC_CmdTiltUp,  (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn);
  DOVFC_EnableDisable (DOVFC_CmdSlideFd, (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn);
  DOVFC_EnableDisable (DOVFC_CmdLiftUp,  (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn);
  DOVFC_EnableDisable (DOVFC_CmdBackrFd, (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].BackEn);

  DIAC_EnableDisable  (DIAC_Tilt_UP,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn);
  DIAC_EnableDisable  (DIAC_Tilt_DW,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn);
  DIAC_EnableDisable  (DIAC_Slide_FW,    (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn);
  DIAC_EnableDisable  (DIAC_Slide_BW,    (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn);
  DIAC_EnableDisable  (DIAC_Lift_DW,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn);
  DIAC_EnableDisable  (DIAC_Lift_UP,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn);
  DIAC_EnableDisable  (DIAC_Back_BW,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].BackEn);
  DIAC_EnableDisable  (DIAC_Back_FW,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].BackEn);

  DOIFC_EnableDisable (DOIFC_CmdHeatDrv,   (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn);
  DOIFC_EnableDisable (DOIFC_CmdHeatPass,  (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn);
  DOIFC_EnableDisable (DOIFC_CmdHeatSteer, (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn);

  PWMC_EnableDisable  (PWMC_HeatDrv,       (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn);
  PWMC_EnableDisable  (PWMC_HeatPass,      (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn);
  PWMC_EnableDisable  (PWMC_HeatSteer,     (CTRL_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn);

  SNSP_EnableDisable  (SNSP_SEAT_DRV,      (PRES_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn);
  SNSP_EnableDisable  (SNSP_SEAT_PASS,     (PRES_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn);
  SNSP_EnableDisable  (SNSP_STEER_WHEEL,   (PRES_EnSts_t)EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn);
}
#endif /* end __EEPP_IS_PRESENT__ */
