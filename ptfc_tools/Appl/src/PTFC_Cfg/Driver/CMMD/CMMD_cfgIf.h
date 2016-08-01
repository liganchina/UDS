/**
 * @file CMMD_cfgIf.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:31:36
 * @brief File containing the user configuration of CMMD module.
 * 
 * @see www.Bitron.net
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
| MM           Matteo Mastrodonato       Bitron S.p.A.
| DF           Davide Fogliano           Polimatica S.r.l.
| DC           Daniele Cloralio          Ema S.r.l.
|-----------------------------------------------------------------------------
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 15/06/15   0.1  DC     952 message map:  P_952_E2A_R3_BHCAN_15_05_2015_CR8681
|-----------------------------------------------------------------------------
| 28/07/15   0.1  DC     952 message map:  P952_E3A_R1_BHCAN
|-----------------------------------------------------------------------------
 */

#ifndef __CMMD_CFGIF_H
#define __CMMD_CFGIF_H

#ifdef CMMD_CFG_IF_OWNER
  #define CMMD_CFG_IF_EXTERN
#else
  #define CMMD_CFG_IF_EXTERN   extern
#endif

/*______ G L O B A L - M A C R O S ___________________________________________*/

/* Uncomment if in the project there are a DBC number major or equal to 2 */
/* #define __CMMD_MULTI_DBC__ */

#ifdef __CMMD_MULTI_DBC__
  /* This value must be major or equal to 2.
     For one DBC comment the previous define __CMMD_MULTI_DBC__ */
  #define CMMD_DBC_NMB      (2u)
#endif

/******************************************************************************/
/************   D L C - C O N F I G U R A T I O N - S E C T I O N   ***********/
/******************************************************************************/
/* RX messages */
#define  CAND_DIAG_REQ_FUNC_BH_C2_DLC                 (0U)                          
#define  CAND_DIAG_REQ_PHYS_HMSM_DLC                  (0U)
#define  CAND_NWM_BCM_DLC                             (6U)                          
#define  CAND_BCM_IGNITION_ON_COUNTER_DLC             (2U)                          
#define  CAND_STATUS_BH_BCM2_DLC                      (8U)                          
#define  CAND_VIN_DLC                                 (8U)                          
#define  CAND_STATUS_CCAN3_DLC                        (8U)                          
#define  CAND_STATUS_CLIMATE2_DLC                     (8U)                          
#define  CAND_STATUS_LIN_DLC                          (8U)                          
#define  CAND_STATUS_MIRROR_DLC                       (8U)                          
#define  CAND_TRIP_A_B_DLC                            (6U)                          
#define  CAND_STATUS_BH_BCM1_DLC                      (8U)                          
#define  CAND_CFG_DATA_CODE_REQUEST_DLC               (6U)                          

/* TX messages */
#define  CAND_STATUS_HMSM_DLC                         (8U)                          
#define  CAND_NWM_HMSM_DLC                            (2U)                          
#define  CAND_CFG_DATA_CODE_RSP_HMSM_DLC              (6U)                          
#define  CAND_DIAGNOSTIC_RESPONSE_HMSM_DLC            (0U)

/******************************************************************************/
/********   M S G - I D - C O N F I G U R A T I O N - S E C T I O N   *********/
/******************************************************************************/

/* RX messages */
#define CAND_DIAG_REQ_FUNC_BH_C2_ID          CAND_EXT_ID(0x18DBFEF1U)      
#define CAND_DIAG_REQ_PHYS_HMSM_ID           CAND_EXT_ID(0x18DAC2F1U)
#define CAND_NWM_BCM_ID                      CAND_EXT_ID(0x1E340000U)      
#define CAND_BCM_IGNITION_ON_COUNTER_ID      CAND_STD_ID(0x75CU)           
#define CAND_STATUS_BH_BCM2_ID               CAND_STD_ID(0x46CU)           
#define CAND_VIN_ID                          CAND_STD_ID(0x3E0U)           
#define CAND_STATUS_CCAN3_ID                 CAND_STD_ID(0x3E2U)           
#define CAND_STATUS_CLIMATE2_ID              CAND_STD_ID(0x5CAU)           
#define CAND_STATUS_LIN_ID                   CAND_STD_ID(0x5B6U)           
#define CAND_STATUS_MIRROR_ID                CAND_STD_ID(0x5A6U)           
#define CAND_TRIP_A_B_ID                     CAND_STD_ID(0x760U)           
#define CAND_STATUS_BH_BCM1_ID               CAND_STD_ID(0x356U)           
#define CAND_CFG_DATA_CODE_REQUEST_ID        CAND_EXT_ID(0x1E114000U)

/* TX messages */
#define CAND_STATUS_HMSM_ID                  CAND_STD_ID(0x5A8U)
#define CAND_NWM_HMSM_ID                     CAND_EXT_ID(0x1E340030U)      
#define CAND_CFG_DATA_CODE_RSP_HMSM_ID       CAND_EXT_ID(0x1E114030U)      
#define CAND_DIAGNOSTIC_RESPONSE_HMSM_ID     CAND_EXT_ID(0x18DAF1C2U)      


/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum
{
  CMMD_NO_ACTIVE_LOADS_IN_MASTER = 0U,
  CMMD_ACTIVE_LOADS_IN_MASTER = 1U,
} ActiveLoadMaster_t;

typedef enum
{
  CMMD_NO_ACTIVE_LOADS_IN_SLAVE = 0U,
  CMMD_ACTIVE_LOADS_IN_SLAVE = 1U,
} ActiveLoadSlave_t;

typedef enum
{
  CMMD_IGN_FAIL_NOT_PRESENT = 0U,
  CMMD_IGN_FAIL_PRESENT = 1U,
  CMMD_IGN_SNA = 3U,
} CmdIgn_FailSts_t;

typedef enum
{
  CMMD_INITIALIZATION = 0U,
  CMMD_IGN_LK = 1U,
  CMMD_ACC = 3U,
  CMMD_RUN = 4U,
  CMMD_START = 5U,
  CMMD_SNA = 7U,
} CmdIgnSts_t;

typedef enum
{
  CMMD_NO_FAIL_PRESENT = 0U,
  CMMD_FAIL_PRESENT = 1U,
} CurrentFailSts_HMSM_t;

typedef enum
{
  CMMD_ERROR_ACTIVE_STATE = 0U,
  CMMD_ERROR_PASSIVE_WARNING_STATE = 1U,
  CMMD_BUS_OFF_STATE = 2U,
  CMMD_NOT_USED = 3U,
} D_ES_t;

typedef enum
{
  CMMD_NOT_READY = 0U,
  CMMD_READY = 1U,
} DataCmdReady_t;

typedef enum
{
  CMMD_CLOSED = 0U,
  CMMD_OPEN = 1U,
} EngineBonnetSts2_t;

typedef enum
{
  CMMD_ENGINE_OFF = 0U,
  CMMD_ENGINE_CRANKING = 1U,
  CMMD_ENGINE_ON = 2U,
  CMMD_ENGINE_SNA = 3U,
} EngineSts_t;

typedef enum
{
  CMMD_NO_EOL_PROGRAMMING = 0U,
  CMMD_EOL_PROGRAMMING = 1U,
} EOL_BCM_t;

typedef enum
{
  CMMD_FUEL_SNA = 255U,
} FuelLevel_t;

typedef enum
{
  CMMD_NO_FUNCTIONALFAILPRESENT = 0U,
  CMMD_FUNCTIONALFAILPRESENT = 1U,
} GenericFailSts_BCM_t;

typedef enum
{
  CMMD_OFF = 0U,
  CMMD_ON = 1U,
} HeatedSteeringSts_t;

typedef enum
{
  CMMD_OFF_ = 0U,
  CMMD_LOW = 1U,
  CMMD_MEDIUM = 2U,
  CMMD_HIGH = 3U,
} HeatedLeft_t;

typedef enum
{
  CMMD_NOT_ACTIVE = 0U,
  CMMD_ACTIVE = 1U,
} InternalLightSts_t;

typedef enum
{
  CMMD_STANDSTILL = 0U,
  CMMD_MOVING = 1U,
} MirrorDrvStandStillSts_t;

typedef enum
{
  CMMD_OP_MODE_INITIALIZATION  = 0U,
  CMMD_IGNITION_OFF_WITHOUTKEY = 1U,
  CMMD_IGNITION_OFF            = 2U,
  CMMD_IGNITION_ACC            = 3U,
  CMMD_IGNITION_ON             = 4U,
  CMMD_IGNITION_PRE_START      = 5U,
  CMMD_IGNITION_START          = 6U,
  CMMD_IGNITION_CRANKING       = 7U,
  CMMD_IGNITION_ON_ENGON       = 8U,
  CMMD_IGNITION_PRE_ACC        = 9U,
  CMMD_IGNITION_PRE_OFF        = 10U,
  CMMD_AUTOMATIC_CRANKING      = 11U,
  CMMD_AUTOMATIC_STOP          = 12U,
  CMMD_KEY_AUTHENTICATED       = 13U,
  CMMD_OP_MODE_NOT_USED        = 14U,
  CMMD_OP_MODE_SNA             = 15U,
} OperationalModeSts_t;

typedef enum
{
  CMMD_NORMALOPERATION_OK = 0U,
  CMMD_SWTEMP_SHRT = 1U,
  CMMD_SWTEMP_OPN = 2U,
  CMMD_SWTEMP_SNA = 3U,
} StW_TempSensSts_t;

typedef enum
{
  CMMD_CMD_WAKE_UP = 0U,
  CMMD_CMD_NOT_USED = 1U,
  CMMD_CMD_STAYACTIVE = 2U,
  CMMD_CMD_SLEEP = 3U,
} SystemCommand_t;

typedef enum
{
  CMMD_STS_WAKE_UP = 0U,
  CMMD_STS_NOT_USED = 1U,
  CMMD_STS_STAYACTIVE = 2U,
  CMMD_STS_NOT_USED_2 = 3U,
} SystemStatus_HMSM_t;

typedef enum
{
  CMMD_SPEED_FAIL_NOT_PRESENT = 0U,
  CMMD_SPEED_FAIL_PRESENT = 1U,
} VehicleSpeedFailSts_t;

typedef enum
{
  CMMD_SPEED_SNA = 8191U,
} VehicleSpeedVSOSig_t;

typedef enum
{
  CMMD_VIN_LO = 0U,
  CMMD_VIN_MID = 1U,
  CMMD_VIN_HI = 2U,
  CMMD_VIN_SNA = 3U,
} VIN_MSG_t;

typedef enum
{
  CMMD_FIXED = 0U,
} Zero_byte_t;

/*-------------------------------------------------------*/
/*            MESSAGE STRUCTURE DEFINITION               */
/*-------------------------------------------------------*/

/*-----------------------------------------*/
/* NWM_HMSM                                */
/*-----------------------------------------*/
typedef struct
{
  Zero_byte_t                           Zero_byte_HMSM                            ;
  SystemStatus_HMSM_t                   SystemStatus_HMSM                       :2;
  ActiveLoadSlave_t                     ActiveLoadSlave_HMSM                    :1;
  EOL_BCM_t                             EOL_HMSM                                :1;
  GenericFailSts_BCM_t                  GenericFailSts_HMSM                     :1;
  CurrentFailSts_HMSM_t                 CurrentFailSts_HMSM                     :1;
  D_ES_t                                D_ES_HMSM                               :2;

}MSG_TXMAILBOX_0_t;

typedef union
{
  uint8_t                               byte[CAND_NWM_HMSM_DLC];
  MSG_TXMAILBOX_0_t                     bit;
} NwmHmsm_t;

/*-----------------------------------------*/
/* CFG_DATA_CODE_RSP_HMSM                  */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               Digit_10_HMSM                           :4;
  uint8_t                               Digit_11_HMSM                           :4;
  uint8_t                               Digit_08_HMSM                           :4;
  uint8_t                               Digit_09_HMSM                           :4;
  uint8_t                               Digit_06_HMSM                           :4;
  uint8_t                               Digit_07_HMSM                           :4;
  uint8_t                               Digit_04_HMSM                           :4;
  uint8_t                               Digit_05_HMSM                           :4;
  uint8_t                               Digit_02_HMSM                           :4;
  uint8_t                               Digit_03_HMSM                           :4;
  uint8_t                               spareBits_40to43                        :4;
  uint8_t                               Digit_01_HMSM                           :4;

}MSG_TXMAILBOX_0_1_t;

typedef union
{
  uint8_t                               byte[CAND_CFG_DATA_CODE_RSP_HMSM_DLC];
  MSG_TXMAILBOX_0_1_t                   bit;
} CfgDataCodeRspHmsm_t;

/*-----------------------------------------*/
/* STATUS_HMSM                             */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               MirrorDrvHorizzontalPosCmd                ;
  uint8_t                               MirrorDrvVerticalPosCmd                   ;
  uint8_t                               MirrorPsngrHorizzontalPosCmd              ;
  uint8_t                               MirrorPsngrVerticalPosCmd                 ;
  uint8_t                               spareBits_32to37                        :6;
  uint8_t                               Ack_beep                                :1;
  DataCmdReady_t                        DataCmdReady                            :1;
  uint8_t                               spareBits_47to56[3]                       ;

}MSG_TXMAILBOX_0_2_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_HMSM_DLC];
  MSG_TXMAILBOX_0_2_t                   bit;
} StatusHmsm_t;

#define CMMD_SetBuzzerNotification(x)      (STATUS_HMSM.bit.Ack_beep = (uint8_t)(x))

/*-----------------------------------------*/
/* DIAGNOSTIC_RESPONSE_HMSM                */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               N_PDU[8]                                  ;

}MSG_TXMAILBOX_1_t;

typedef union
{
  uint8_t                               Byte[8];
  MSG_TXMAILBOX_1_t                     bit;
} DiagnosticResponseHmsm_t;

/*-----------------------------------------*/
/* CFG_DATA_CODE_REQUEST                   */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               Digit_10                                :4;
  uint8_t                               Digit_11                                :4;
  uint8_t                               Digit_08                                :4;
  uint8_t                               Digit_09                                :4;
  uint8_t                               Digit_06                                :4;
  uint8_t                               Digit_07                                :4;
  uint8_t                               Digit_04                                :4;
  uint8_t                               Digit_05                                :4;
  uint8_t                               Digit_02                                :4;
  uint8_t                               Digit_03                                :4;
  uint8_t                               spareBits_40to43                        :4;
  uint8_t                               Digit_01                                :4;

}MSG_RXMAILBOX_9_t;

typedef union
{
  uint8_t                               byte[8];
  MSG_RXMAILBOX_9_t                    bit;
} CfgDataCodeRequest_t;


/*-----------------------------------------*/
/* NWM_BCM                                 */
/*-----------------------------------------*/
typedef struct
{
  Zero_byte_t                           Zero_byte_BCM                             ;
  SystemCommand_t                       SystemCommand                           :2;
  ActiveLoadMaster_t                    ActiveLoadMaster                        :1;
  EOL_BCM_t                             EOL_BCM                                 :1;
  GenericFailSts_BCM_t                  GenericFailSts_BCM                      :1;
  VehicleSpeedFailSts_t                 P_ES                                    :1;
  D_ES_t                                D_ES_BCM                                :2;
  InternalLightSts_t                    Node24                                  :1;
  InternalLightSts_t                    Node25                                  :1;
  InternalLightSts_t                    Node26                                  :1;
  InternalLightSts_t                    Node27                                  :1;
  InternalLightSts_t                    Node28                                  :1;
  InternalLightSts_t                    Node29                                  :1;
  InternalLightSts_t                    Node30                                  :1;
  InternalLightSts_t                    Node31                                  :1;
  InternalLightSts_t                    Node16                                  :1;
  InternalLightSts_t                    Node17                                  :1;
  InternalLightSts_t                    Node18                                  :1;
  InternalLightSts_t                    Node19                                  :1;
  InternalLightSts_t                    Node20                                  :1;
  InternalLightSts_t                    Node21                                  :1;
  InternalLightSts_t                    Node22                                  :1;
  InternalLightSts_t                    Node23                                  :1;
  InternalLightSts_t                    Node8                                   :1;
  InternalLightSts_t                    Node9                                   :1;
  InternalLightSts_t                    Node10                                  :1;
  InternalLightSts_t                    Node11                                  :1;
  InternalLightSts_t                    Node12                                  :1;
  InternalLightSts_t                    Node13                                  :1;
  InternalLightSts_t                    Node14                                  :1;
  InternalLightSts_t                    Node15                                  :1;
  InternalLightSts_t                    Node0                                   :1;
  InternalLightSts_t                    Node1                                   :1;
  InternalLightSts_t                    Node2                                   :1;
  InternalLightSts_t                    Node3                                   :1;
  InternalLightSts_t                    Node4                                   :1;
  InternalLightSts_t                    Node5                                   :1;
  InternalLightSts_t                    Node6                                   :1;
  InternalLightSts_t                    Node7                                   :1;

}MSG_RXMAILBOX_12_t;

typedef union
{
  uint8_t                               byte[CAND_NWM_BCM_DLC];
  MSG_RXMAILBOX_12_t                    bit;
} NwmBcm_t;

/*-----------------------------------------*/
/* BCM_IGNITION_ON_COUNTER                 */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               IgnitionOnCounter[2]                      ;

}MSG_RXMAILBOX_13_t;

typedef union
{
  uint8_t                               byte[CAND_BCM_IGNITION_ON_COUNTER_DLC];
  MSG_RXMAILBOX_13_t                    bit;
} BcmIgnitionOnCounter_t;

#define CMMD_KeyOnCounter     (u16)(((u16)(BCM_IGNITION_ON_COUNTER.bit.IgnitionOnCounter[0])<<8U) |\
                                    ((u16)(BCM_IGNITION_ON_COUNTER.bit.IgnitionOnCounter[1])))

/*-----------------------------------------*/
/* STATUS_BH_BCM2                          */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_0to5                          :6;
  CmdIgn_FailSts_t                      CmdIgn_FailSts                          :2;
  uint8_t                               spareBits_8to12                         :5;
  CmdIgnSts_t                           CmdIgnSts                               :3;
  uint8_t                               spareBits_23to56[6]                       ;

}MSG_RXMAILBOX_14_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_BH_BCM2_DLC];
  MSG_RXMAILBOX_14_t                    bit;
} StatusBhBcm2_t;

/*-----------------------------------------*/
/* VIN                                     */
/*-----------------------------------------*/
typedef struct
{
  VIN_MSG_t                             VIN_MSG                                 :2;
  uint8_t                               spareBits_2to7                          :6;
  uint8_t                               VIN_DATA[7]                               ;

}MSG_RXMAILBOX_2_t;

typedef union
{
  uint8_t                               byte[CAND_VIN_DLC];
  MSG_RXMAILBOX_2_t                     bit;
} Vin_t;

/*-----------------------------------------*/
/* STATUS_CCAN3                            */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_0to7[4]                         ;
  VehicleSpeedFailSts_t                 VehicleSpeedVSOSigFailSts               :1;
  uint8_t                               spareBits_39to33                        :7;
  uint8_t                               VehicleSpeedVSOSig_40to47                 ;
  EngineSts_t                           EngineSts                               :2;
  uint8_t                               spareBits_50to50                        :1;
  uint8_t                               VehicleSpeedVSOSig_55to51               :5;
  uint8_t                               spareBits_56to63                          ;

}MSG_RXMAILBOX_3_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_CCAN3_DLC];
  MSG_RXMAILBOX_3_t                     bit;
} StatusCcan3_t;

#define CMMD_VehicleSpeed     (u16)(((u16)(STATUS_CCAN3.bit.VehicleSpeedVSOSig_40to47) << 5U) |\
                                    ((u16)(STATUS_CCAN3.bit.VehicleSpeedVSOSig_55to51)))
#define CMMD_VehicleFail      (u08)(STATUS_CCAN3.bit.VehicleSpeedVSOSigFailSts)

/*-----------------------------------------*/
/* STATUS_CLIMATE2                         */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_0to7                            ;
  uint8_t                               spareBits_8to9                          :2;
  HeatedLeft_t                          VentilatedLeft                          :2;
  HeatedLeft_t                          HeatedRight                             :2;
  HeatedLeft_t                          HeatedLeft                              :2;
  uint8_t                               spareBits_23to16                          ;
  HeatedLeft_t                          VentilatedRight                         :2;
  uint8_t                               spareBits_31to26                        :6;
  uint8_t                               spareBits_32to39                          ;
  HeatedSteeringSts_t                   SteeringHeatedCmd                       :1;
  uint8_t                               spareBits_47to41                        :7;
  uint8_t                               spareBits_55to56[2]                       ;

}MSG_RXMAILBOX_4_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_CLIMATE2_DLC];
  MSG_RXMAILBOX_4_t                     bit;
} StatusClimate2_t;

#define CMMD_VentilatedLeft       (STATUS_CLIMATE2.bit.VentilatedLeft)
#define CMMD_VentilatedRight      (STATUS_CLIMATE2.bit.VentilatedRight)
#define CMMD_HeatedRight          (STATUS_CLIMATE2.bit.HeatedRight)
#define CMMD_HeatedLeft           (STATUS_CLIMATE2.bit.HeatedLeft)
#define CMMD_SteeringHeatedCmd    (STATUS_CLIMATE2.bit.SteeringHeatedCmd)

/*-----------------------------------------*/
/* STATUS_LIN                              */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_0to15[2];
  uint8_t                               spareBits_16to18                        :3;
  StW_TempSensSts_t                     StW_TempSensSts                         :2;
  uint8_t                               spareBits_23to21                        :3;
  uint8_t                               StW_TempSts                               ;
  uint8_t                               spareBits_39to56[4]                       ;

}MSG_RXMAILBOX_5_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_LIN_DLC];
  MSG_RXMAILBOX_5_t                     bit;
} StatusLin_t;

#define CMMD_StW_TempSensSts           (STATUS_LIN.bit.StW_TempSensSts)
#define CMMD_StW_TempSts               (STATUS_LIN.bit.StW_TempSts)

/*-----------------------------------------*/
/* STATUS_MIRROR                           */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               MirrorDrvHorizzontalPosSts                ;
  uint8_t                               MirrorDrvVerticalPosSts                   ;
  uint8_t                               MirrorPsngrHorizzontalPosSts              ;
  uint8_t                               MirrorPsngrVerticalPosSts_24to27        :4;
  MirrorDrvStandStillSts_t              MirrorPsngrStandStillSts                :1;
  uint8_t                               spareBits_29to29                        :1;
  MirrorDrvStandStillSts_t              MirrorDrvStandStillSts                  :1;
  uint8_t                               spareBits_31to31                        :1;
  uint8_t                               spareBits_32to35                        :4;
  uint8_t                               MirrorPsngrVerticalPosSts_39to36        :4;
  uint8_t                               spareBits_47to56[3]                       ;

}MSG_RXMAILBOX_6_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_MIRROR_DLC];
  MSG_RXMAILBOX_6_t                     bit;
} StatusMirror_t;

#define CMMD_MirrPsngVertPos     (uint8_t)(((uint8_t)(STATUS_MIRROR.bit.MirrorPsngrVerticalPosSts_24to27) << 4U) |\
                                           ((uint8_t)(STATUS_MIRROR.bit.MirrorPsngrVerticalPosSts_39to36)))

/*-----------------------------------------*/
/* TRIP_A_B                                */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_0to7                            ;
  uint8_t                               TotalOdometer_8to11                     :4;
  uint8_t                               spareBits_15to12                        :4;
  uint8_t                               TotalOdometer_23to24[2]                   ;
  uint8_t                               spareBits_39to40[2]                       ;

}MSG_RXMAILBOX_7_t;

typedef union
{
  uint8_t                               byte[CAND_TRIP_A_B_DLC];
  MSG_RXMAILBOX_7_t                     bit;
} TripAB_t;

/*-----------------------------------------*/
/* STATUS_BH_BCM1                          */
/*-----------------------------------------*/
typedef struct
{
  uint8_t                               spareBits_7to8[2]                         ;
  uint8_t                               spareBits_16to19                        :4;
  OperationalModeSts_t                  OperationalModeSts                      :4;
  uint8_t                               spareBits_24to30                        :7;
  EngineBonnetSts2_t                    DriverDoorSts                           :1;
  uint8_t                               spareBits_39to56[4]                       ;

}MSG_RXMAILBOX_8_t;

typedef union
{
  uint8_t                               byte[CAND_STATUS_BH_BCM1_DLC];
  MSG_RXMAILBOX_8_t                     bit;
} StatusBhBcm1_t;

#define CMMD_DrvDoorSts         (STATUS_BH_BCM1.bit.DriverDoorSts)
#define CMMD_OperationalModeSts (STATUS_BH_BCM1.bit.OperationalModeSts)

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern __saddr StatusHmsm_t                          STATUS_HMSM                     ;
extern __saddr NwmHmsm_t                             NWM_HMSM                        ;
extern __saddr CfgDataCodeRspHmsm_t                  CFG_DATA_CODE_RSP_HMSM          ;
extern __saddr DiagnosticResponseHmsm_t              DiagResponseBuf                 ;

/******************************************************************************/
/***************   R X - M S G - B U F F E R - S E C T I O N   ****************/
/******************************************************************************/

extern __saddr CfgDataCodeRequest_t                  CFG_DATA_CODE_REQUEST           ;
extern __saddr uint8_t                               DiagRequestBuf[8]               ;
extern __saddr NwmBcm_t                              NWM_BCM                         ;
extern __saddr BcmIgnitionOnCounter_t                BCM_IGNITION_ON_COUNTER         ;
extern __saddr StatusBhBcm2_t                        STATUS_BH_BCM2                  ;
extern __saddr Vin_t                                 VIN                             ;
extern __saddr StatusCcan3_t                         STATUS_CCAN3                    ;
extern __saddr StatusClimate2_t                      STATUS_CLIMATE2                 ;
extern __saddr StatusLin_t                           STATUS_LIN                      ;
extern __saddr StatusMirror_t                        STATUS_MIRROR                   ;
extern __saddr TripAB_t                              TRIP_A_B                        ;
extern __saddr StatusBhBcm1_t                        STATUS_BH_BCM1                  ;

#endif /* __CMMD_CFGIF_H */

/*______ E N D _____ (CMMD_cfgIf.h) _________________________________________*/
