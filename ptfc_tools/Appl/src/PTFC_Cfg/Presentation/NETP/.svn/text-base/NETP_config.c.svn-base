/**
 * @file NETP_config.c
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:30:7
 * @brief File containing the user configuration of NETP module.
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
#define NETP_CONFIG_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "NETP.h"
#include "NETP_config.h"

/* Module inhibition filter */
#ifdef __NETP_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/
void Netp_StatusCcan3Cbk (void);
void Netp_MngKeyOnCnt (void);
void Netp_StatusBhBcm1Cbk (void);
void Netp_ConfigurationCodeMng (void);

/*______ L O C A L - D A T A _______________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/* Following structure configuration is able to enable/disable            *
 * the transmission of a message when UDS communication control is active */
const NETP_TxNetMonitor_t NETP_TxNetMonitor[CAND_TX_MSG_NMB]  = 
{
/*+-----------------------------+-------------+---------------------+---------------------+-----------------------------------+
  |    Enable communication     |   Tx Type   |    Transmission     |  Mtbe: minimum time |          Confirmation             |
  |   control by UDS service    |             |     period [ms]     |    between events   |            callback               |
  +-----------------------------+-------------+---------------------+---------------------+-----------------------------------+*/
    /* CAND_STATUS_HMSM_HND */
    { NETP_CCT_NORMAL_MSG,         NETP_TX_PE,   NETP_TICK_MS(1000),   NETP_TICK_MS(0),              EXMMA_SendCbk             },
    /* CAND_NWM_HMSM_HND */
    { NETP_CCT_NWM_MSG,            NETP_TX_E,    NETP_TICK_MS(0),      NETP_TICK_MS(0),              NWMA_SendNwmNaxCbk        },
    /* CAND_CFG_DATA_CODE_RSP_HMSM_HND */
    { NETP_CCT_NORMAL_MSG,         NETP_TX_E,    NETP_TICK_MS(0),      NETP_TICK_MS(0),              NULL                      },
    /* CAND_DIAGNOSTIC_RESPONSE_HMSM_HND */
    { NETP_CCT_DIAG_MSG,           NETP_TX_E,    NETP_TICK_MS(0),      NETP_TICK_MS(0),              NULL                      },
};

#ifdef NETP_TIMEOUT_SERVICE
/* Following structure configuration is able to monitor network message timeout, *
 * call recovery function when message is in timeout and enable/disable timeout  *
 * monitoring when UDS communication control is active                           */
const NETP_RxNetMonitor_t NETP_RxNetMonitor[CAND_RX_MSG_NMB] =
{
/*+-----------------------------+-----------------------------+-------------------+--------------------------------------+-------------------------+-------------------+
  |    Enable communication     |    Indication callback      |      Recovery     |        Recovery callback             |      Faulty/Absent      |    Enable Diag    |
  |   control by UDS service    |                             |    timeout [ms]   |                                      |    diagnostic Enable    |     in key off    |
  +-----------------------------+-----------------------------|-------------------+--------------------------------------+-------------------------+-------------------+
  RX messages */
    /* CAND_VIN_HND */
    { NETP_CCT_NORMAL_MSG,         VF607_MgmVINWorkigCondition,  NETP_TICK_MS(2500),    NETP_VIN_Rec,                           NETP_BCM_ABS_FAULTY,          FALSE  },
    /* CAND_STATUS_CCAN3_HND */
    { NETP_CCT_NORMAL_MSG,         Netp_StatusCcan3Cbk,          NETP_TICK_MS(2500),    NETP_STATUS_CCAN3_Rec,                  NETP_BCM_ABS_FAULTY,          FALSE  },
    /* CAND_STATUS_CLIMATE2_HND */
    { NETP_CCT_NORMAL_MSG,         DISPA_StatusClimateCbk,       NETP_TICK_MS(2500),    NETP_STATUS_CLIMATE2_Rec,               NETP_ACM_ABS_FAULTY,          FALSE  },
    /* CAND_STATUS_LIN_HND */
    { NETP_CCT_NORMAL_MSG,         DISPA_StatusLinCbk,           NETP_TICK_MS(2500),    NETP_STATUS_LIN_Rec,                    NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_STATUS_MIRROR_HND */
    { NETP_CCT_NORMAL_MSG,         NULL,                         NETP_TICK_MS(2500),    NETP_STATUS_MIRROR_Rec,                 NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_TRIP_A_B_HND */
    { NETP_CCT_NORMAL_MSG,         VF607_TRIP_AB_flagSet,        NETP_TICK_MS(2500),    NETP_TRIP_A_B_Rec,                      NETP_IPC_ABS_FAULTY,          FALSE  },
    /* CAND_STATUS_BH_BCM1_HND */
    { NETP_CCT_NORMAL_MSG,         Netp_StatusBhBcm1Cbk,         NETP_TICK_MS(2500),    NETP_STATUS_BH_BCM1_Rec,                NETP_BCM_ABS_FAULTY,          FALSE  },
    /* CAND_CFG_DATA_CODE_REQUEST_HND */
    { NETP_CCT_NORMAL_MSG,         Netp_ConfigurationCodeMng,    NETP_TICK_MS(2500),    NULL,                                   NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_DIAGNOSTIC_REQ_FUNC_BH_C2_HND */
    { NETP_CCT_DIAG_MSG,           TP_DiagFuncMsgReceived,       NETP_TICK_MS(2500),    NULL,                                   NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_DIAGNOSTIC_REQUEST_HMSM_HND */
    { NETP_CCT_DIAG_MSG,           TP_DiagPhysMsgReceived,       NETP_TICK_MS(0),       NULL,                                   NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_NWM_BCM_HND */
    { NETP_CCT_NWM_MSG,            NWMA_NwmReceivedCbk,          NETP_TICK_MS(2500),    NETP_NWM_BCM_Rec,                       NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_BCM_IGNITION_ON_COUNTER_HND */
    { NETP_CCT_NORMAL_MSG,         Netp_MngKeyOnCnt,             NETP_TICK_MS(2500),    NETP_BCM_IGNITION_ON_COUNTER_Rec,       NETP_ABS_FAULTY_DISABLE,      FALSE  },
    /* CAND_STATUS_BH_BCM2_HND */
    { NETP_CCT_NORMAL_MSG,         DISPA_GateWayRemoteCranking,  NETP_TICK_MS(2500),    NETP_STATUS_BH_BCM2_Rec,                NETP_BCM_ABS_FAULTY,          FALSE  },
};
#endif

#ifdef NETP_TIMEOUT_SERVICE

/**
 * @brief Message recovery function on message absent event
 */

void NETP_NWM_BCM_Rec(void)
{
  NWM_BCM.bit.ActiveLoadMaster   =   (ActiveLoadMaster_t)0;
  NWM_BCM.bit.D_ES_BCM           =               (D_ES_t)0;
  NWM_BCM.bit.EOL_BCM            =            (EOL_BCM_t)0;
  NWM_BCM.bit.GenericFailSts_BCM = (GenericFailSts_BCM_t)0;
  NWM_BCM.bit.Node0    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node1    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node10   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node11   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node12   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node13   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node14   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node15   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node16   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node17   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node18   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node19   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node2    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node20   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node21   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node22   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node23   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node24   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node25   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node26   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node27   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node28   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node29   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node3    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node30   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node31   =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node4    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node5    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node6    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node7    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node8    =             (InternalLightSts_t)0;
  NWM_BCM.bit.Node9    =             (InternalLightSts_t)0;
  NWM_BCM.bit.P_ES     =          (VehicleSpeedFailSts_t)0;
  NWM_BCM.bit.SystemCommand   =         (SystemCommand_t)0;
  NWM_BCM.bit.Zero_byte_BCM   =             (Zero_byte_t)0;
}

void NETP_BCM_IGNITION_ON_COUNTER_Rec(void)
{
  BCM_IGNITION_ON_COUNTER.bit.IgnitionOnCounter[0] = 0U;
  BCM_IGNITION_ON_COUNTER.bit.IgnitionOnCounter[1] = 0U;
}

void NETP_STATUS_BH_BCM2_Rec(void)
{
  STATUS_BH_BCM2.bit.CmdIgn_FailSts   = (CmdIgn_FailSts_t)0;
  STATUS_BH_BCM2.bit.CmdIgnSts        =      (CmdIgnSts_t)0;
  STATUS_BH_BCM2.bit.RemStActvSts     =   (RemStActvSts_t)0;

  /*VF608_V1_R5 ID 4.0 Description par. 1.13.2.1.4*/
  VF608_ID4Description();
  DISPA_GateWayRemoteCranking();
}

void NETP_STATUS_CCAN3_Rec(void)
{
  STATUS_CCAN3.bit.EngineSts                    =           (EngineSts_t)3;
  STATUS_CCAN3.bit.VehicleSpeedVSOSig_40to47    =                       0U;
  STATUS_CCAN3.bit.VehicleSpeedVSOSig_55to51    =                       0U;
  STATUS_CCAN3.bit.VehicleSpeedVSOSigFailSts    = (VehicleSpeedFailSts_t)0;
}

void NETP_STATUS_CLIMATE2_Rec(void)
{
  STATUS_CLIMATE2.bit.HeatedLeft        =         (HeatedLeft_t)0;
  STATUS_CLIMATE2.bit.HeatedRight       =         (HeatedLeft_t)0;
  STATUS_CLIMATE2.bit.SteeringHeatedCmd =  (HeatedSteeringSts_t)0;
  STATUS_CLIMATE2.bit.VentilatedLeft    =         (HeatedLeft_t)0;
  STATUS_CLIMATE2.bit.VentilatedRight   =         (HeatedLeft_t)0;
  DISPA_StatusClimateCbk();
}

void NETP_STATUS_LIN_Rec(void)
{
  STATUS_LIN.bit.StW_TempSensSts   =  (StW_TempSensSts_t)0;
  STATUS_LIN.bit.StW_TempSts       =                     0U;
}

void NETP_STATUS_MIRROR_Rec(void)
{
  STATUS_MIRROR.bit.MirrorDrvHorizzontalPosSts   =                            0U;
  STATUS_MIRROR.bit.MirrorDrvStandStillSts       =  (MirrorDrvStandStillSts_t)0;
  STATUS_MIRROR.bit.MirrorDrvVerticalPosSts      =                            0U;
  STATUS_MIRROR.bit.MirrorPsngrHorizzontalPosSts =                            0U;
  STATUS_MIRROR.bit.MirrorPsngrStandStillSts     =  (MirrorDrvStandStillSts_t)0;
  STATUS_MIRROR.bit.MirrorPsngrVerticalPosSts_24to27    =                     0U;
  STATUS_MIRROR.bit.MirrorPsngrVerticalPosSts_39to36    =                     0U;
}

void NETP_TRIP_A_B_Rec(void)
{
  TRIP_A_B.bit.TotalOdometer_8to11     = 0U;
  TRIP_A_B.bit.TotalOdometer_23to24[0] = 0U;
  TRIP_A_B.bit.TotalOdometer_23to24[1] = 0U;

  VF607_TripABRecoveryOdo();
}

void NETP_STATUS_BH_BCM1_Rec(void)
{
  STATUS_BH_BCM1.bit.OperationalModeSts   =  (OperationalModeSts_t)0;
  STATUS_BH_BCM1.bit.DriverDoorSts        =  (CMMD_DoorSts_t)0;
}

void NETP_VIN_Rec(void)
{
  uint8_t i;

  VIN.bit.VIN_MSG  = CMMD_VIN_SNA;
  for (i=0U;i<VIN_DATA_LEN;i++)
  {
    VIN.bit.VIN_DATA[i] = 0U;
  }
}

/**
 * @brief  Public function for ManageNetwork fault (e.g.) bud off, mute, electric fail,faulty
 * @return type of fault
 */
PRES_Fault_t NETP_GetCanDiag(NETP_CanDTC_t diagSym)
{
  PRES_Fault_t valueReturn;
  valueReturn = PRES_NOT_TESTED;

  switch (diagSym)
  {
    case NETP_ELECTRIC_FAIL_HND:
      //if ((CAND_GetTransceiverOpState() == CAND_TS_NORMAL) &&
      //    (DINP_GetState(DINP_CanNerr) == S_ON))   // CDD 1.4 DTC U001901
      //{
      //  CAND_SetWireFailureState(TRUE);
      //  valueReturn = PRES_NO_FAULT;  /* in 250 WIRE failure dtc is Disabled, anyway the status is logged */
      //}
      //else
      //{
      //  CAND_SetWireFailureState(FALSE);
      //  valueReturn = PRES_NO_FAULT;
      //}
      break;
  
    case NETP_NODE_MUTE_HND:
      if (NETP_GetMuteStatus() == TRUE)  // CDD 1.4 DTC U001987  /* TODO: inserire get missing ack /
      {
        valueReturn = PRES_MSG_NOT_RECEIVED;
      }
      else
      {
        valueReturn = PRES_NO_FAULT;
      }
      break;
  
    case NETP_BUS_OFF_HND:
      if (CAND_GetBusOffState() == TRUE)   // CDD 1.4 DTC U001988
      {
        valueReturn = PRES_BUS_OFF_FAULT;
      }
      else
      {
        valueReturn = PRES_NO_FAULT;
      }
      break;

    default:
      valueReturn = PRES_NOT_TESTED;
      break;
  }

  return (valueReturn);
}


/**
 * @brief  Public function returning if the condition fot timeout monitor are fulfilled
 * @return S_ON = fulfilled, S_OFF = not fulfilled
 */
PRES_State_t NETP_GetCanDiagState(NETP_CanDTC_t diagSym)
{
  return (NETP_GetMonitorStatus());
}
#endif /* end NETP_TIMEOUT_SERVICE */

/*----------------------------------------------------------------------------*/
/*Name : NETP_KeyStsChanged                                                   */
/*Role : Force re-testing of network message after KEY-ON Event               */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
#ifdef __KEYA_IS_PRESENT__
void NETP_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
  if(KeyStatus == KEYA_ON_STATUS)
  {
#ifdef NETP_TIMEOUT_SERVICE
    NETP_InitTimeout(NETP_CCT_APPL_MSG);
#endif
  }
}
#else
void NETP_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
}
#endif



void NETP_Service28OffsetCbk(void)
{
  NETP_EnableRxTimeout(TRUE);
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void Netp_StatusCcan3Cbk (void)
{
  TLRP_SetSlow(VF608_T_CCAN3_Missing_Msg);
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void Netp_MngKeyOnCnt (void)
{
  EERAM_EcuStatusInfo.KeyOnCnt = CMMD_KeyOnCounter;

  if( (NETP_GetRxStatus(CAND_TRIP_A_B_HND)) == NETP_MSG_NOT_RECEIVED)
  {
    VF607_TripABRecoveryOdo();
  }
  else
  {
  }
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void Netp_StatusBhBcm1Cbk (void)
{
  VF608_MngOperationalModeSts();
  KEYA_CheckKeyStatus();

  /* Test if CountryCode is EQUAL to USA OR CANADA OR MEXICO */
  if(FUNP_IsShortComfortTimer()==FALSE)
  {
    DISPA_DriverDoorStsChanged((CMMD_DoorSts_t) STATUS_BH_BCM1.bit.DriverDoorSts);
  }
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void Netp_ConfigurationCodeMng (void)
{                                                                                   /*esempio*/
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_11_HMSM    = EERAM_SysConfigProxy.ConfCode[0];   /*= 0x4u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_10_HMSM    = EERAM_SysConfigProxy.ConfCode[1];   /*= 0x2u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_09_HMSM    = EERAM_SysConfigProxy.ConfCode[2];   /*= 0x5u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_08_HMSM    = EERAM_SysConfigProxy.ConfCode[3];   /*= 0x3u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_07_HMSM    = EERAM_SysConfigProxy.ConfCode[4];   /*= 0x2u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_06_HMSM    = EERAM_SysConfigProxy.ConfCode[5];   /*= 0x1u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_05_HMSM    = EERAM_SysConfigProxy.ConfCode[6];   /*= 0x4u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_04_HMSM    = EERAM_SysConfigProxy.ConfCode[7];   /*= 0x0u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_03_HMSM    = EERAM_SysConfigProxy.ConfCode[8];   /*= 0x0u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_02_HMSM    = EERAM_SysConfigProxy.ConfCode[9];   /*= 0x0u */
  CFG_DATA_CODE_RSP_HMSM.bit.Digit_01_HMSM    = EERAM_SysConfigProxy.ConfCode[10];  /*= 0x0u */
  CFG_DATA_CODE_RSP_HMSM.bit.spareBits_40to43 = 0x0u;                               /*= 0x0u */

  NETP_SendMsgReq(CAND_CFG_DATA_CODE_RSP_HMSM_HND);
}

#endif /* end __NETP_IS_PRESENT__ */

/*______ E N D _____ (NETP_config.c) _________________________________________*/
