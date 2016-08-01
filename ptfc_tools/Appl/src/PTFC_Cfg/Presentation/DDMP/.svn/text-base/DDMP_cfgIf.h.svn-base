/*
 * DDMP_cfgIf.h
 *
 *  Created on: 16/lug/2013
 *      Author: glenta
 */

#ifndef DDMP_CFGIF_H_
#define DDMP_CFGIF_H_

#ifdef DDMP_CONFIG_IF_OWNER
  #define DDMP_CONFIG_IF_EXTERN
#else
  #define DDMP_CONFIG_IF_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define DDMP_ECU_TIME_STAMP_EN    TRUE

#define DDMP_DTC_MAX_SIZE   34      /* Dimensione in byte di un DTC           */

/* This define is used to mask the bit of the DTC status mask that are not used , 
  Bit 0 (Test Failed) and bit 3 (Confirmed DTC) are always managed. 
        (minimal DDMP_STATUS_AVAILABILITY_MASK is 0x09)
  Bits 1,2 ad 6 are optional
  Bits 4,5 and 7 are not implmented
*/
#define DDMP_STATUS_AVAILABILITY_MASK         0x4FU

//#define DDMP_STATUS_AVAILABILITY_MASK_FIAT    0x4FU  //09009 par. 4.3.1.1 pag.18

#define DDMP_FORMAT_IDENTIFIER                0x00U
#define DDMP_SNAPSHOT_RECORD_NUMBER           0x01U

/* Valore presente in richiesta/risposta diagnostica es: */
/* TX) DIAGNOSTIC_RESPONSE_TTM (0x18DAF14A)              */
/* RX) DIAGNOSTIN_REQUEST_TTM (0x18DA4AF1)               */
#define DDMP_FUNCTIONAL_UNIT                  0x4AU

#define DDMP_INVALID_SEVERITY_MASK            0x1FU // Rappresenta la maschera dei bit non utilizzati per indicare la severità del DTC

#define DDMP_SNAPSHOT_RECORD_NUM_EVENT        2U

#define DDMP_SNAPSHOT_RECORD_NUM_DATA         7U   /* Numero di RDI che compongono i parametri ambientali */

/* enable the management of time-based priority during DTC set */
#define DDMP_DTC_TIME_PRI_EN      TRUE

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* ************************************************************************** */
/* DDMP_ID_t                                                                  */
/* Elenco di tutti i DTC memorizzabili                                        */
/* B = Body system Groupings                                                  */
/* P = Powertrain system Groupings                                            */
/* U = Network system Groupings                                               */
/* ************************************************************************** */

typedef enum DTC_ID_e
{
  DDMP_NO_DTC_ID        = 0,   /* (0)   -  0x0000 */
  DDMP_VEHICLE_SPEED       ,   /* (1)   -  0x     */
  DDMP_INTERNAL_FAIL       ,   /* (2)   -  0x     */
  DDMP_TILT_SLIDE_KEY      ,   /* (3)   -  0x     */
  DDMP_LIFT_BACKR_KEY      ,   /* (4)   -  0x     */
  DDMP_MEM_KEY             ,   /* (4)   -  0x     */
  DDMP_TILT_SLIDE_RL       ,   /* (5)   -  0x     */
  DDMP_LIFT_BACK_RL        ,   /* (6)   -  0x     */
  DDMP_PROT_RL             ,   /* (7)   -  0x     */
  DDMP_SLIDE_HALL_SENSOR   ,   /* (8)   -  0x     */
  DDMP_TILT_HALL_SENSOR    ,   /* (9)   -  0x     */
  DDMP_LIFT_HALL_SENSOR    ,   /* (10)  -  0x     */
  DDMP_BACKREST_HALL_SENSOR,   /* (11)  -  0x     */
  DDMP_DRIVER_SEAT_HEATER  ,   /* (12)  -  0x     */
  DDMP_PSNGR_SEAT_HEATER   ,   /* (13)  -  0x     */
  DDMP_STEERW_HEATER       ,   /* (14)  -  0x     */
  DDMP_NTC_STEERW          ,   /* (15)  -  0x     */
  DDMP_SLIDE_LOW_CURRENT   ,
  DDMP_VBATT_MOTORS        ,
  DDMP_NTC_DRV             ,   /* (16)  -  0x     */
  DDMP_NTC_PSG             ,   /* (17)  -  0x     */
  DDMP_BUS_OFF             ,   /* (18)  -  0x     */
  DDMP_BCM                 ,   /* (19)  -  0x     */
  DDMP_IPC                 ,   /* (20)  -  0x     */
  DDMP_ACM                 ,   /* (21)  -  0x     */
  DDMP_IWC_SIGNAL_FROM_BCM ,   /* (22)  -  0xD932 */
  DDMP_STATUS_BCM1         ,   /* (23)  -  0x     */
  DDMP_STATUS_CCAN3        ,   /* (24)  -  0x     */
  DDMP_ALL_DTC_ID              /*   -  UM_DTC + 1 */
} DDMP_ID_t;

/* ************************************************************************** */
/* DDMP_FaultSymptom_t                                                        */
/* Elenco di tutti i possibili fault symptom.                                 */
/* ************************************************************************** */
typedef enum DDMP_FaultSymptom_e
{
  DDMP_NO_SYMPTOM                 = 0x00,  /* nessun errore diagnosticato       */
  DDMP_SYMPTOM_NA                 = 0x00,  /* errore non previsto               */
  DDMP_GENERAL_FAIL_SYS           = 0x01,  /* Genaral Electrical Failures       */
  DDMP_SCGND_SYM                  = 0x11,  /* Circuit short to ground           */
  DDMP_SCVBATT_SYM                = 0x12,  /* Circuit short to battery          */
  DDMP_OC_SYM                     = 0x13,  /* Circuit open                      */
  DDMP_OC_SCGND_SYM               = 0x14,  /* Circuit short to ground or open   */
  DDMP_OC_SCVBATT_SYM             = 0x15,  /* Circuit short to battery or open  */
  DDMP_LOW_VOLTAGE_SYM            = 0x16,  /* Circuit voltage below threshold */
  DDMP_HIGH_VOLTAGE_SYM           = 0x17,  /* Circuit voltage above threshold */
//  DDMP_LOW_CURRENT_SYM            = 0x18,  /* Circuit current below threshold */
//  DDMP_HIGH_CURRENT_SYM           = 0x19,  /* Circuit current above threshold */
//  DDMP_SIGNAL_STUCK_LOW_SYM       = 0x23,  /* Signal stuck low                */
  DDMP_SIGNAL_STUCK_HIGH_SYM      = 0x24,    /* Signal stuck high               */
  DDMP_SIGNAL_SIGNAL_INVALID_SYM  = 0x29,  /* Signal invalid                  */
//  DDMP_DATA_MEM_FAIL_SYM          = 0x44,  /* Data memory failure             */
//  DDMP_PROGRAM_MEM_FAIL_SYM       = 0x45,  /* Program memory failure          */
//  DDMP_CALIB_MEM_FAIL_SYM         = 0x46,  /* Calibr./param. memory failure   */
//  DDMP_WATCHDOG_FAIL_SYM          = 0x47,  /* Watchdog/safety µC failure      */
  DDMP_NOT_PROGRAMMED             = 0x51,    /* Not programmed                  */
//  DDMP_NOT_CONFIGURED_SYM         = 0x55,  /* Not configured                  */
  DDMP_BAD_CONFIGURATION_SYM      = 0x56,    /* Invalid/incompatible config.    */
  DDMP_SIGNAL_PAUSIB_FAIL_SYM     = 0x64,    /* Signal plausibility failure     */
  DDMP_SIGNAL_TOO_FEW_TRANS_SYM   = 0x65,    /* Signal has too few transitions  */
//  DDMP_SIGNAL_INCORRECT_SYM       = 0x67,  /* Signal incorrect after event    */
//  DDMP_ACTUATOR_STUCK_SYM         = 0x71,  /* Actuator stuck                  */
//  DDMP_ALIVE_NOT_UPD_SYM          = 0x82,  /* Alive/sequence counter incorrect/not updated */
  DDMP_SIGNAL_INVALID_SYM         = 0x86,  /* Signal invalid                    */
  DDMP_MISSING_MESSAGE_SYM        = 0x87,  /* Missing message                   */
  DDMP_BUS_OFF_SYM                = 0x88,  /* Bus off                           */
  DDMP_ERRATIC_SYM                = 0x8F,  /* Erratic                           */
  DDMP_COMP_INT_FAIL_SYS          = 0x96   /* Component Internal Failure        */
} DDMP_FaultSymptom_t ;


typedef enum DDMP_Sub_Func_e
{
  SUB_FUNC_02  = 0x02,
  SUB_FUNC_07  = 0x07,
  SUB_FUNC_08  = 0x08,
  SUB_FUNC_0C  = 0x0C,
  SUB_FUNC_0E  = 0x0E
} DDMP_Sub_Func_t;


typedef enum DDMP_Snapshot_Num_e
{
  DDMP_FIRST_EVENT =  0x00,
  DDMP_LAST_EVENT  =  0x01,
  DDMP_ALL_EVENT   =  0xFF
} DDMP_Snapshot_Event_Num_t;

typedef enum DDMP_Env_Cond_Num_e
{
#if (DDMP_DTC_TIME_PRI_EN == TRUE)
  DDMP_ENV_COND_LIFE_TIME,
  DDMP_ENV_COND_TIMESTAMP_IGN_ON,
#endif
  DDMP_ENV_COND_IGN_ON_CNT,
  DDMP_ENV_COND_DTC_FAIL_TYPE,
  DDMP_ENV_COND_OPERAT_MODE_STS,
  DDMP_ENV_COND_VEH_SPEED,
  DDMP_ENV_COND_BATT_VOLTAGE
} DDMP_Env_Cond_Num_t;


typedef union
{
  u08 Byte;
  struct
  {
    u08 testFailed                           :1;  /* Bit0, Mandatory */
    u08 testFailedThisMonitoringCycle        :1;  /* Bit1, optional, see  DDMP_STATUS_AVAILABILITY_MASK*/
    u08 pendingDTC                           :1;  /* Bit2, optional, see  DDMP_STATUS_AVAILABILITY_MASK */
    u08 confirmedDTC                         :1;  /* Bit3, Mandatory */
    u08 testNotCompletedSinceLastClear       :1;  /* Bit4, not implemented */
    u08 testFailedSinceLastClear             :1;  /* Bit5, not implemented  */
    u08 testNotCompletedThisMonitoringCycle  :1;  /* Bit6, optional, see  DDMP_STATUS_AVAILABILITY_MASK*/
    u08 warningIndicatorRequest              :1;  /* Bit7, not implemented */
  }Bit;
}DDMP_DtcStatus_t;

typedef struct DDMP_Env_Cond_Byte_s
{
#if (DDMP_DTC_TIME_PRI_EN == TRUE) //Per ricordare che in caso di norma fiat queste condizioni ambientali sono obbligatorie! 
  u08               Life_Time[4];                             /* RDI 0x1008 */
  u08               Time_Stamps_Ign_On[2];                    /* RDI 0x1009 */
#endif
  u08               Ddmp_Env_Cond_Ign_On_Counter[2];          /* RDI 0x200A */
  u08               Ddmp_Env_Cond_DTC_Failure_Type[1];        /* RDI 0x6082 */
  u08               Ddmp_Env_Cond_Operational_Mode_Status[9]; /* RDI 0x1921 */
  u08               Ddmp_Env_Cond_Veh_Speed[2];               /* RDI 0x1002 */
  u08               Ddmp_Env_Cond_Batt_Voltage[2];            /* RDI 0x1004 */
} DDMP_Env_Cond_Byte_t;



typedef union DDMP_Env_Cond_u
{
  DDMP_Env_Cond_Byte_t  Cond;
  u08                   Bytes[sizeof(DDMP_Env_Cond_Byte_t)];
} DDMP_Env_Cond_t;


typedef struct Ddmp_Block_s
{
  u16               Ddmp_ID;                                     /* ID         */
  DDMP_DtcStatus_t  Ddmp_Status;                                 /* Stato Dtc  */
  u08               Ddmp_Symptom[DDMP_SNAPSHOT_RECORD_NUM_EVENT];/* RDI 0x6082, always present */
  DDMP_Env_Cond_t   Ddmp_Env[DDMP_SNAPSHOT_RECORD_NUM_EVENT];

} Ddmp_Block_t;

typedef struct Ddmp_BlockExt_s
{
  u08               Ddmp_Dinam_Cond_Event_Counter; /* Numero di eventi in cui l'errore si è presentato indipendentemente*/
} Ddmp_BlockExt_t;


#define DDMP_NO_DATA_LENGTH               0u
#define DDMP_SYMPTOM_AND_STATUS           2u//1u  //StatusOfDTC(1)
//#define DDMP_ONE_SNAP_LENGTH             27u  //FIAT SnapshotData(26)
#define DDMP_ONE_SNAP_LENGTH             (sizeof(DDMP_Env_Cond_Byte_t) /* Dimensione parametri */\
                                          + 2U /*DTCSnapshotRecordNumber e DTCSnapshotRecordNumberOfIdentifiers*/\
                                          +(DDMP_SNAPSHOT_RECORD_NUM_DATA*2U) /* occupazione RDI (2 byte per ogni dato)*/\
                                            )//29u  //FIAT SnapshotData(26)
//#define DDMP_TWO_SNAP_LENGTH             54u  //FIAT SnapshotData(52)
#define DDMP_TWO_SNAP_LENGTH             (DDMP_ONE_SNAP_LENGTH*2U) //52 //FIAT SnapshotData(52)
#define DDMP_ONE_EXT_DATA_LENGTH          4u  //FIAT ExtendedDataRecord(4)
#define DDMP_TWO_EXT_DATA_LENGTH          8u  //FIAT ExtendedDataRecord(8)

#define    DDMP_OP_MODE           9u  //FIAT Numero di Operational Mode

  /*______ G L O B A L - M A C R O S ___________________________________________*/

DDMP_CONFIG_IF_EXTERN void DDMP_UserClearDtcEvent(void);
DDMP_CONFIG_IF_EXTERN void DDMP_UserKeyOnEvent(void);
DDMP_CONFIG_IF_EXTERN void DDMP_UserKeyOffEvent(void);
DDMP_CONFIG_IF_EXTERN void DDMP_UserReportFirstLastConfirmedDtc (DDMP_Sub_Func_t SubFun, u08 *BufferPntr);

#if (DDMP_ECU_TIME_STAMP_EN == TRUE)
  DDMP_EXTERN u32 DDMP_GetEcuTimeStamps(void);
  DDMP_EXTERN u16 DDMP_GetEcuTimeStampsFromKeyOn(void);
#endif

#endif /* DDMP_CFGIF_H_ */
