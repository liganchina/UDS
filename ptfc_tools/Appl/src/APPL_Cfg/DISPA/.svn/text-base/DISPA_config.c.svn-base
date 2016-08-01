/**
 * @file DISPA_config.c
 * @brief DISPA Module: user table definition and callback implementation
 *
 * @version 0.1
 * @author Davide Fogliano (Polimatica S.r.l.)
 * @date 24 june 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano           Polimatica S.r.l
|-----------------------------------------------------------------------------
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
| GB           Giuseppe Barberio         Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
| 24/07/15   0.2  DC      Porting to 952 project
|-----------------------------------------------------------------------------
| 24/07/15   0.3  GB      Bug fix for test norm 7z0142/01 - 7_2_11: WAKE-UP
|                         SLEEP process. Redmine #1414.
|-------------------------------------------------------------------------------
 */

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "DISPA.h"
#include "DISPA_config.h"

/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__ 


/*_____ G L O B A L - D E F I N E ____________________________________________*/
#define DISPA_INVALID_POSITION    -32000
#define DISPA_MOTOR_CMD_MAX       MOTP_REQ_MOVE_DW_BW

/* (risoluzione: 0.0625 Km/h / lsb) -> (DISPA_MEM_RECALL_SPEED_TH*1024)/640 = STATUS_CCAN3.VehicleSpeed */
#define DISPA_MEM_RECALL_SPEED    (u16)(((u32)(DISPA_MEM_RECALL_SPEED_TH<<10U))/64U)

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/
DISPA_BackrAlignState_t Dispa_BackrAlignState;


/*Global data for the model, defined as extern in MOTA.h */
UInt8 EEG_Status;
UInt8 Init_Motor_Slide;

/* APSA dummy variables not used, only for F151M compatibility */
UInt8 EERAM_Threshold_Att_Forward;
Int16 EERAM_Current_Map_Forward[100];
UInt16 EERAM_CounterVectorUpFwd[13];
UInt16 EERAM_CounterVectorDownFwd[13];
UInt8 EERAM_Threshold_Antipinch_Forward;
UInt8 EERAM_Threshold_Att_Forward;

const DISPA_ModuleCfg_t DISPA_ModuleCfgTable[DISPA_MOD_MAX] =
{
    /*+---------------------------------+--------------------------------+*/
    /*|          SetCmd                 |        CheckIoCallback         |*/
    /*+---------------------------------+--------------------------------+*/
    /*|       StartIoCallback           |         StopIoCallback         |*/
    /*+---------------------------------+--------------------------------+*/
    /*|         IdleCommand             |           SuspCommand          |*/
    /*+---------------------------------+--------------------------------+*/

    /* DISPA_MOD_MOTP          */
    {  (DISPA_SetCmd_t)MOTP_SetMovement,         NULL,
        NULL,                                    NULL,
        0x00U,                                   0x00U,                   },

    /* DISPA_MOD_HTRA         */
    {  (DISPA_SetCmd_t)HEATA_SetLevel,           HEATA_CheckIoControl,
        HEATA_StartIoControl,                    HEATA_StopIoControl,
        0x00U,                                   0xE9U,                   },

};  

const DISPA_FunctionCfg_t DISPA_FunctionCfgTable[DISPA_HANDLE_MAX] =
{
    /*       HANDLE             |    FUNCTION_HANDLE          |       MODULE      | SELF_IOCONTROL |         GROUP             |      IOC_TIMER          */
    /* DISPA_TILT             */ { MOTP_TILT,                   DISPA_MOD_MOTP,     TRUE,            DISPA_GROUP_SLIDE_TILT,      DISPA_TIME_SECONDS(30u)  },
    /* DISPA_LIFT             */ { MOTP_LIFT,                   DISPA_MOD_MOTP,     TRUE,            DISPA_GROUP_BACKR_LIFT,      DISPA_TIME_SECONDS(30u)  },
    /* DISPA_BACKREST         */ { MOTP_BACK_R,                 DISPA_MOD_MOTP,     TRUE,            DISPA_GROUP_BACKR_LIFT,      DISPA_TIME_SECONDS(30u)  },
    /* DISPA_SLIDE            */ { MOTP_SLIDE,                  DISPA_MOD_MOTP,     TRUE,            DISPA_GROUP_SLIDE_TILT,      DISPA_TIME_SECONDS(30u)  },
    /* DISPA_SEAT_DRV,        */ { HEATA_SEAT_DRV,              DISPA_MOD_HTRA,     FALSE,           DISPA_GROUP_H_D,             DISPA_TIME_SECONDS(5u)   },
    /* DISPA_SEAT_PSG,        */ { HEATA_SEAT_PSG,              DISPA_MOD_HTRA,     FALSE,           DISPA_GROUP_H_P,             DISPA_TIME_SECONDS(5u)   },
    /* DISPA_STW,             */ { HEATA_STW,                   DISPA_MOD_HTRA,     FALSE,           DISPA_GROUP_H_S,             DISPA_TIME_SECONDS(5u)   },
};

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/
static bool Dispa_KB1Pressed;
static bool Dispa_KB2Pressed;
static bool Dispa_KB3Pressed;
static bool Dispa_batteria_staccata;
static HeatedLeft_t  Dispa_HeatLevelDrv, Dispa_HeatLevelPsg;
static HeatedSteeringSts_t  Dispa_HeatLevelStw;
static MSM_storageStatus_t      Dispa_StoreStatus;
static NWMA_NetStateReq_t Dispa_NM_request = NWMA_NONE_REQ;
static bool Dispa_InitSlideInProg;

static uint8_t Dispa_LastMemorySel;

/*_____ P R I V A T E - M A C R O S __________________________________________*/
#define HEATER_IOC_VAL_50X100      50u

#define VBAT_MEMO_POS       395u       // 8,5 V
#define VBAT_OK             468u       // 10 V
#define T_VBAT_STABILE      200u       // 1 secondo per delay

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

void Dispa_StoreCbk(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle);
void Dispa_StoreMemory(uint8_t memory);
uint8_t Dispa_CheckMemory(uint8_t memory);
void    Dispa_ClearMemory(uint8_t motor);

static void Dispa_CheckSetHall(DISPA_handle_t hdl, u08 set_hall_cmd);
static void Dispa_SetMirrorsMemoryToRecall(uint8_t mem);
static bool_t Dispa_CheckActiveTimers(void);
static bool_t Dispa_CheckCranking(void);
#if 0
static void DISPA_Doors_Timer_Expire(void);
#endif
static void   Dispa_SetTolerances(void);
static void Dispa_SetNM_REQ(NWMA_NetStateReq_t NM_request);
static NWMA_NetStateReq_t Dispa_GetNM_REQ(void);

//MSM_HeatingStatus_t  Dispa_GetHeatingStatus(void);

/*_____ G L O B A L - F U N C T I O N S ______________________________________*/
void DISPA_cfgInit(void)
{
  Dispa_batteria_staccata  = TRUE; // per non memorizzare la pos. dopo il reset!

  Dispa_HeatLevelDrv = CMMD_OFF_;
  Dispa_HeatLevelPsg = CMMD_OFF_;
  Dispa_HeatLevelStw = CMMD_OFF;

  /* init keyboard buttons as not pressed */
  Dispa_KB1Pressed = FALSE;
  Dispa_KB2Pressed = FALSE;
  Dispa_KB3Pressed = FALSE;

  /* Update model input to enable only the available motors */
  /* MOTORS presence */
  MOTA_Input_Slide.Slide_Presence = MOTA_PRESENT;
  MOTA_Input_Tilt.Tilt_Presence = MOTA_PRESENT;
  MOTA_Input_Backrest.Backrest_Presence = MOTA_PRESENT;
  MOTA_Input_Lift.Lift_Presence = MOTA_PRESENT;

  MOTA_Input_Slide.In_SlideUp   = S_OFF;
  MOTA_Input_Slide.In_SlideDown = S_OFF;
  MOTA_Input_Tilt.In_TiltUp     = S_OFF;
  MOTA_Input_Tilt.In_TiltDown   = S_OFF;
  MOTA_Input_Backrest.In_BackrestUp   = S_OFF;
  MOTA_Input_Backrest.In_BackrestDown = S_OFF;
  MOTA_Input_Lift.In_LiftUp           = S_OFF;
  MOTA_Input_Lift.In_LiftDown         = S_OFF;

  /*Init hall slide, for actual pos loss recovery strategy */
  MOTA_Input_Slide.Hall_Slide = EERAM_ContatoreHall[IPOC_Slide];

  Dispa_StoreStatus = STORAGE_NOT_ACTIVE;

  if(EERAM_ConfigModel.Init_MotorSlide == 1u)
  {
    Init_Motor_Slide = MOTA_INIT;
  }
  else
  {
    Init_Motor_Slide = MOTA_NOT_INIT;
  }

  MOTA_Input_Common.Antipanic        = MOTA_ABSENT;
  MOTA_Input_Common.Init_From_Diag   = MOTA_FALSE;
  MOTA_Input_Common.EasyExit_Enable  = MOTA_ENABLE;
  MOTA_Input_Common.Welcome_Distance = (Int16)EERAM_ConfigModel.Welcome_Distance;
  MOTA_Input_Common.PillarPosition   = (Int16)EERAM_ConfigModel.PillarPosition;

  EEG_Status  = EERAM_ConfigModel.EEG_Status;

  Dispa_SetTolerances();

  // check if hall memory in EEPP is ok
  if((EEPP_GetDataStatus(EEPP_HDL_ContatoreHall)    == MS_NOT_OK) ||
     (EERAM_ConfigModel.MotorNewPositionsToBeStored == TRUE)      ||   
     (EERAM_ConfigModel.ActualPosLoss               == TRUE ))
  {
    MOTA_Input_Common.Actual_Pos_Loss = TRUE;
    EERAM_ConfigModel.ActualPosLoss   = TRUE;
    EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
  }
  else
  {
    MOTA_Input_Common.Actual_Pos_Loss = FALSE;
  }
  
  /* APSA Init */
  APSA_INPUT_Low_Level.Enable_APSA = (uint8_t)APSA_ACTIVE;
  APSA_INPUT_DELTA.DELTA_1 = 2U;
  APSA_INPUT_DELTA.DELTA_2 = 2U;
}

/* called @100 ms */
/* update slow parameters (e.g. parameters changed via UDS, etc) */
void DISPA_SlowModelInUpdate(void)
{
  MOTA_Input_Common.Welcome_Distance = (Int16)EERAM_ConfigModel.Welcome_Distance;
  MOTA_Input_Common.PillarPosition   = (Int16)EERAM_ConfigModel.PillarPosition;
  /* Manage the update of EEG and EEP status and their counters */
  /* they will be written on EEPROM at power off */
  if ((EEG_Status  != EERAM_ConfigModel.EEG_Status)          ||
      (Init_Motor_Slide != EERAM_ConfigModel.Init_MotorSlide))
  {
    EERAM_ConfigModel.EEG_Status      =  EEG_Status;
    EERAM_ConfigModel.Init_MotorSlide =  Init_Motor_Slide;
    //EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
  }

  /* APSA parameters */
  APSA_INPUT_Low_Level.Enable_Adaptation = EERAM_AntiPinchAdaptation;
}

/* called @10 ms */
void DISPA_FastModelInUpdate(void)
{
  bool dummy;
  PRES_Fault_t key_fault;
  u08 Dispa_SlideMoved = FALSE;

  /***************************************/
  /********* MOTA model input ************/
  /***************************************/

  /* if STATUS_BH_BCM1 is not yet received by BCM, set key status to key off */
  MOTA_Input_Common.KeyStatus  = (KEYA_GetKeyStatus() == ANY_KEY) ? (KEYA_OFF_STATUS):(KEYA_GetKeyStatus());
  MOTA_Input_Common.DoorStatus = CMMD_DrvDoorSts;

  /* Update motors positions */
  if(MOTA_Input_Slide.Hall_Slide != EERAM_ContatoreHall[IPOC_Slide])
  {
    MOTA_Input_Slide.Hall_Slide = EERAM_ContatoreHall[IPOC_Slide];
    Dispa_SlideMoved  = TRUE;
  }
  MOTA_Input_Tilt.Hall_Tilt =           EERAM_ContatoreHall[IPOC_Tilt   ];
  MOTA_Input_Backrest.Hall_Backrest =   EERAM_ContatoreHall[IPOC_Backres];
  MOTA_Input_Lift.Hall_Lift =           EERAM_ContatoreHall[IPOC_Lift   ];

  if(EERAM_ConfigModel.MotorNewPositionsToBeStored == FALSE)
  {
    if(Dispa_SlideMoved == TRUE)
    {
      EERAM_ConfigModel.MotorNewPositionsToBeStored = TRUE;
      EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
    }
  }

  if(DISPA_isModelIoControlActive() == TRUE) //DF: 30.01.2015, for UDS IOControl management
  {
    MOTA_Input_Common.MCU_PositionRecall = MOTA_NO_MEMORY;
  }

  if (MOTP_GetPosFbkDiag(MOTP_SLIDE) == PRES_NO_FAULT)
  {
    MOTA_Input_Slide.StatusMotor_Slide = MOTP_GetMotorStatus(MOTP_SLIDE);
  }
  else
  {
    MOTA_Input_Slide.StatusMotor_Slide = MOTA_STS_FAIL;
  }

  if (MOTP_GetPosFbkDiag(MOTP_LIFT) == PRES_NO_FAULT)
  {
    MOTA_Input_Lift.StatusMotor_Lift = MOTP_GetMotorStatus(MOTP_LIFT);
  }
  else
  {
    MOTA_Input_Lift.StatusMotor_Lift = MOTA_STS_FAIL;
  }

  if (MOTP_GetPosFbkDiag(MOTP_BACK_R) == PRES_NO_FAULT)
  {
    MOTA_Input_Backrest.StatusMotor_Backrest = MOTP_GetMotorStatus(MOTP_BACK_R);
  }
  else
  {
    MOTA_Input_Backrest.StatusMotor_Backrest = MOTA_STS_FAIL;
  }

  if (MOTP_GetPosFbkDiag(MOTP_TILT) == PRES_NO_FAULT)
  {
    MOTA_Input_Tilt.StatusMotor_Tilt = MOTP_GetMotorStatus(MOTP_TILT);
  }
  else
  {
    MOTA_Input_Tilt.StatusMotor_Tilt = MOTA_STS_FAIL;
  }

  /* manage button fail */
  FVMP_GetDiag(FVMP_TILT_SLIDE_KEY, &key_fault, &dummy);
  if(key_fault == PRES_BUTTON_STUCKED)
  {
    /* slide / Tilt keyboard button stucked */
    MOTA_Input_Slide.In_SlideUp   = S_OFF;
    MOTA_Input_Slide.In_SlideDown = S_OFF;
    MOTA_Input_Tilt.In_TiltUp     = S_OFF;
    MOTA_Input_Tilt.In_TiltDown   = S_OFF;
  }

  FVMP_GetDiag(FVMP_LIFT_BACKR_KEY, &key_fault, &dummy);
  if(key_fault == PRES_BUTTON_STUCKED)
  {
    /* backrest / Lift keyboard button stucked */
    MOTA_Input_Backrest.In_BackrestUp   = S_OFF;
    MOTA_Input_Backrest.In_BackrestDown = S_OFF;
    MOTA_Input_Lift.In_LiftUp           = S_OFF;
    MOTA_Input_Lift.In_LiftDown         = S_OFF;
  }

  MOTA_Input_Common.Antipinch_Active = APSA_OUTPUT.Antipinch_Active;

  /***************************************/
  /********* APSA model input ************/
  /***************************************/
  APSA_INPUT_Mota.Check_Antipinch     = MOTA_Output.Check_Antipinch;
  APSA_INPUT_Mota.Cmd_Motor           = MOTA_Output.CmdMotor_Slide;
  APSA_INPUT_Mota.Write_Map           = MOTA_Output.Write_Map;
  APSA_INPUT_Mota.Cmd_Motor_Lift      = MOTA_Output.CmdMotor_Lift;
  APSA_INPUT_Mota.Lenght_Motor_Stroke = EERAM_Measured_Motors_Stroke;

  APSA_INPUT_Low_Level.Hall_Counter  = EERAM_ContatoreHall[IPOC_Slide];
  APSA_INPUT_Low_Level.Current       = MOTP_GetMotorsCurrent();
  APSA_INPUT_Low_Level.Vbatt         = ADCC_GetChnAvrgData(ADCC_Ele_Fbk);

}

void Dispa_StoreMemory(uint8_t memory)
{
  IPOC_Channel_t motor;

  /*Check memory number validity */
  if((memory != MOTA_NO_MEMORY) && (memory <= MOTA_NUM_MEMO))
  {
    /*Start storage procedure only f no other storage is in progress */
    if(Dispa_StoreStatus == STORAGE_NOT_ACTIVE)
    {
      Dispa_StoreStatus = STORAGE_ACTIVE;

      /* the mototr position are memorized at the same order as IPOC_Channel_t enum */
      for(motor = (IPOC_Channel_t)0u; motor < (IPOC_Channel_t)MOTA_NUM_MOTORS ; motor++)
      {
        EERAM_MemoM[(((memory-1U)*MOTA_NUM_MOTORS) + (uint8_t)motor)] =  EERAM_ContatoreHall[motor];
      }

      EEPP_WriteData(EEPP_HDL_MemoM, Dispa_StoreCbk);
    }
  }
  //  else
  //  {
  //    if(Dispa_StoreStatus == STORAGE_SUCCESS)
  //    {
  //      Dispa_StoreStatus = STORAGE_NOT_ACTIVE;
  //    }
  //  }

}

void Dispa_StoreCbk(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle)
{

  //  if(returnStatus == MS_OK)
  //  {
  //    Dispa_StoreStatus = STORAGE_SUCCESS;
  //  }
  //  else
  //  {
  Dispa_StoreStatus = STORAGE_NOT_ACTIVE;
  //  }
}

/*
Return the position to recall or MOTA_NO_MEMORY in case of invalid position
Check if the requested memory to recall contains valid motor position, if
at least one position is not valid then don't execute recall (return MOTA_NO_MEMORY)*/
uint8_t Dispa_CheckMemory(uint8_t memory)
{
  IPOC_Channel_t motor;  
  uint8_t ret_val = memory;

  if(DISPA_isModelIoControlActive() == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(memory != MOTA_NO_MEMORY)
    {
      /* the mototr position are memorized at the same order as IPOC_Channel_t enum */
      for(motor = (IPOC_Channel_t)0u; motor < (IPOC_Channel_t)MOTA_NUM_MOTORS ; motor++)
      {
        if(EERAM_MemoM[(((memory-1U)*MOTA_NUM_MOTORS) + (uint8_t)motor)] == DISPA_INVALID_POSITION)
        {
          /* Set the recall position to actual motor position so the motors don't move */
          EERAM_MemoM[(((memory-1U)*MOTA_NUM_MOTORS) + (uint8_t)motor)] = EERAM_ContatoreHall[motor];
        }
      }
    }
  }
  else
  {
    ret_val = MOTA_NO_MEMORY;
  }

  return ret_val;
}

void DISPA_ClrRecallReq(void)
{
  MOTA_Input_Common.MCU_PositionRecall = MOTA_NO_MEMORY;
}

void DISPA_UserSavePos(void)
{
  /* Save positions only in Key On status */
  if (KEYA_GetKeyStatus() == KEYA_ON_STATUS)
  {
    /* If memory save is activated, checking vehicle speed */
    if ((FUNP_GetVehicleSpeed() < DISPA_MEM_RECALL_SPEED)  &&
        (CMMD_VehicleFail == CMMD_SPEED_FAIL_NOT_PRESENT))
    {
      Dispa_StoreMemory(Dispa_LastMemorySel);
      
      if (DISPA_GetInitializationStatus() == MOTA_INIT)
      {
#ifdef __EXMMA_IS_PRESENT__
        switch (Dispa_LastMemorySel)
        {
          case 1:
            EXMMA_MemSave(MEM_1);
            break;
          case 2:
            EXMMA_MemSave(MEM_2);
            break;
          case 3:
            EXMMA_MemSave(MEM_3);
            break;
          default:
            break;
        }
#endif
      }
      else
      {
        EERAM_MemoM[(((Dispa_LastMemorySel-1U)*MOTA_NUM_MOTORS) + (uint8_t)IPOC_Slide)] = DISPA_INVALID_POSITION;
      }
    }

    /* send buzzer notification on CAN bus */
    CMMD_SetBuzzerNotification(CMMD_READY);
    NETP_SendMsgReq(CAND_STATUS_HMSM_HND);
  }
}

void DISPA_UpdateAntiPinchThresholds(void)
{
  //EERAM_Threshold_Att_Forward   =  EERAM_Threshold_Antipinch_Forward - (EERAM_Threshold_Antipinch_Forward >> 1);
  EERAM_Threshold_Att_Backward  =  EERAM_Threshold_Antipinch_Backward - (EERAM_Threshold_Antipinch_Backward >> 1);
}

/**
 * @brief Checks if cranking event occurs
 * @author De Stephanis Alessio
 * @param [in] none
 * @param [out] none
 * @return TRUE if cranking is active
 */
static bool_t Dispa_CheckCranking(void)
{
  bool_t Dispa_CrankOnGoing;

  /* Check for active timers */
  if (KEYA_GetKeyStatus() == KEYA_CRANK_STATUS)
  {
    /* At least one timer is still active */
    Dispa_CrankOnGoing = TRUE;
  }
  else
  {
    /* No timers active */
    Dispa_CrankOnGoing = FALSE;
  }

  return Dispa_CrankOnGoing;
}

#if 0
/**
 * @brief Callback routine generated timer expiring after "open doors" event
 * @author De Stephanis Alessio
 * @param [in] none
 * @param [out] none
 * @return None
 */
static void DISPA_Doors_Timer_Expire(void)
{
  /* Deactivation of ActiveLoad signal */
  (void)Dispa_SetNM_REQ(NWMA_NET_OFF_REQ);
}
#endif

#ifdef __EXMMA_IS_PRESENT__
/**
 * @brief Sets which memory of EXMMA module has to be recalled
 * @author De Stephanis Alessio
 * @param [in] memory identifier
 * @param [out] none
 * @return None
 */
static void Dispa_SetMirrorsMemoryToRecall(uint8_t mem)
{
  u32 checkTimer;
  
  checkTimer = TLRP_GetSlow(TLRP_KeyOffStatus);
  
  if ((KEYA_GetKeyStatus() == KEYA_ON_STATUS) || (checkTimer > 0u))
  {
    /* Recall selected memory for mirrors positioning */
    EXMMA_MemRecall(mem);
  }
}
#endif


/**
 * @brief Checks if some timer is active and permits motor movements
 * @author De Stephanis Alessio
 * @param [in] none
 * @param [out] none
 * @return TRUE if some timer is still active
 */
static bool_t Dispa_CheckActiveTimers(void)
{
  bool_t res;

  /* Check for active timers */
  if (TLRP_GetSlow(TLRP_KeyOffStatus) > 0u)
  {
    /* At least one timer is still active */
    res = TRUE;
  }
  else
  {
    /* Check for active timers */
    if (TLRP_GetSlow(TLRP_Comfort_Timer) > 0u)
    {
      /* At least one timer is still active */
      res = TRUE;
    }
    else
    {
      /* No timers active */
      res = FALSE;
    }
  }

  return (res);
}


/* Start initialization procedure from UDS */
extern void  DISPA_StartInitialization(void)
{
  MOTP_ClearFault(MOTP_SLIDE);
  MOTA_Input_Common.Init_From_Diag = MOTA_TRUE;
  //devalidate existing memory
  //Dispa_ClearMemory(IPOC_Slide);
}

/* get initialization status */
extern u08 DISPA_GetInitializationStatus(void)
{
  return Init_Motor_Slide;
}

/* Start initialization procedure from UDS */
extern void  DISPA_StopInitialization(void)
{
  //to stop init, set antipanic to true
  MOTA_Input_Common.Antipanic = MOTA_PRESENT;
}

/**
 * @brief Clears the value stored in EEPP memories for a seat motor.
 * If the slide memory was cleared, remove also mirrors memories
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void Dispa_ClearMemory(uint8_t motor)
{
  u08 memory;

  for (memory = 1u; memory <= NUM_MEMORIE; memory++)
  {
    EERAM_MemoM[(((memory-1U)*MOTA_NUM_MOTORS) + (uint8_t)motor)] = DISPA_INVALID_POSITION;
  }
  EEPP_WriteData(EEPP_HDL_MemoM, NULL);

  if (motor == IPOC_Slide)
  {
    for (memory = 0u; memory < NUM_MEMORIE; memory++)
    {
      EERAM_MirrorMemInit[memory] = FALSE;
    }
  EEPP_WriteData(EEPP_HDL_MirrorMemInit, NULL);
  }
}

/* function for IOControl directly managed by DISPA */
u08  DISPA_SelfCheckIoControl(DISPA_handle_t hdl, u08 cmd)
{
  u08 ret_val;

  ret_val = SERVICE_OK;

  //TODO TANK Check fault presence!!!!

  if((MOTA_Output.AutomaticMov != MOTA_OFF)
      || (MOTA_Input_Common.Movement_Enable != MOTA_RUN))
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    if(cmd > DISPA_MOTOR_CMD_MAX)
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
  }
  return ret_val;
}

void DISPA_SelfStartIoControl(DISPA_handle_t hdl, u08 cmd)
{
  bool is_motor_control;
  u08 *in_par_up_fw_inf_ptr; 
  u08 *in_par_dw_bw_def_ptr;

  is_motor_control = TRUE;

  switch(hdl)
  {
  case DISPA_TILT:
    in_par_up_fw_inf_ptr = (u08*)&MOTA_Input_Tilt.In_TiltUp;
    in_par_dw_bw_def_ptr = (u08*)&MOTA_Input_Tilt.In_TiltDown;
    MOTA_Input_Slide.In_SlideUp   = S_OFF;
    MOTA_Input_Slide.In_SlideDown = S_OFF;
    break;

  case DISPA_LIFT:
    in_par_up_fw_inf_ptr = (u08*)&MOTA_Input_Lift.In_LiftUp;
    in_par_dw_bw_def_ptr = (u08*)&MOTA_Input_Lift.In_LiftDown;
    MOTA_Input_Backrest.In_BackrestUp   = S_OFF;
    MOTA_Input_Backrest.In_BackrestDown = S_OFF;
    break;

  case DISPA_BACKREST:
    in_par_up_fw_inf_ptr = (u08*)&MOTA_Input_Backrest.In_BackrestUp;
    in_par_dw_bw_def_ptr = (u08*)&MOTA_Input_Backrest.In_BackrestDown;
    MOTA_Input_Lift.In_LiftUp   = S_OFF;
    MOTA_Input_Lift.In_LiftDown = S_OFF;
    break;

  case DISPA_SLIDE:
    in_par_up_fw_inf_ptr = (u08*)&MOTA_Input_Slide.In_SlideUp;
    in_par_dw_bw_def_ptr = (u08*)&MOTA_Input_Slide.In_SlideDown;
    MOTA_Input_Tilt.In_TiltUp   = S_OFF;
    MOTA_Input_Tilt.In_TiltDown = S_OFF;
    break;

  default:
    is_motor_control = FALSE;
    break;
  }

  if(is_motor_control)
  {
    if(cmd == MOTP_REQ_MOVE_UP_FW)
    {
      *in_par_up_fw_inf_ptr = S_ON;
      *in_par_dw_bw_def_ptr = S_OFF;
    }
    else if(cmd == MOTP_REQ_MOVE_DW_BW)
    {
      *in_par_up_fw_inf_ptr = S_OFF;
      *in_par_dw_bw_def_ptr = S_ON;
    }
    else
    {
      *in_par_up_fw_inf_ptr = S_OFF;
      *in_par_dw_bw_def_ptr = S_OFF;
    }
  }
}

void DISPA_SelfStopIoControl(DISPA_handle_t hdl)
{
  /* Return control to ECU:
     Recall input callback in order to restore the user command*/

  switch(hdl)
  {
  case DISPA_TILT:
    Dispa_KB1Pressed = FALSE; /* for take into account an eventual key pressed */
    DISPA_TiltDwInput_Cbk();
    DISPA_TiltUpInput_Cbk();
    break;

  case DISPA_LIFT:
    Dispa_KB2Pressed = FALSE; /* for take into account an eventual key pressed */
    DISPA_LiftDwInput_Cbk();
    DISPA_LiftUpInput_Cbk();
    break;

  case DISPA_BACKREST:
    Dispa_KB2Pressed = FALSE; /* for take into account an eventual key pressed */
    DISPA_BackrestBwInput_Cbk();
    DISPA_BackrestFwInput_Cbk();
    break;

  case DISPA_SLIDE:
    Dispa_KB1Pressed = FALSE; /* for take into account an eventual key pressed */
    DISPA_SlideBwInput_Cbk();
    DISPA_SlideFwInput_Cbk();
    break;

  default:
    break;
  }
}

/**
 * @brief This function is called @10ms and checks if battery voltage drops under 8,5V.
 * When it happens, the most important data are saved.
 * @param none
 * @return void
 */
void DISPA_BatteryUnplugMonitor(void)
{
  static u16       Vbat_stabile_cnt = 0u;  // introduce un ritardo prima di tornare al normale fn
  u16              adVoltage_Battery;

  adVoltage_Battery = ADCC_GetLastChnData(ADCC_Ele_Fbk);

  /* GESTIONE BUCO/STACCO Batteria: memorizza posizione sedile */
  if (    ( Vbat_stabile_cnt  > T_VBAT_STABILE )  // filtraggio in tempo finito
      &&  ( adVoltage_Battery > VBAT_OK )         // tensione ok
  )
  {
    // Azzero i flag per la il prossimo calo di tensione
    Dispa_batteria_staccata = FALSE;
  }
  else
  {
    if ( adVoltage_Battery > VBAT_OK )   // Tensione OK
    {
      // La tensione è ok sopra 10 V
      Vbat_stabile_cnt++;
    }
    else
    {
      if (adVoltage_Battery < VBAT_MEMO_POS)
      {
        // Azzeramento del contatore della tensione stabile
        Vbat_stabile_cnt = 0u;

        // la richiesta di memorizzazione si fa solo una volta
        // quando scende la tensione.

        if (Dispa_batteria_staccata == FALSE)
        {
          // La variabile "batteria_staccata" viene inizializzata a true al reset.
          // Per questo dal reset non si farà la richiesta di memoriz.
          Dispa_batteria_staccata = TRUE;
          // richiedo la memorizzazione della posizione del sedile e di altri dati per il modello:
          EEPP_WriteData(EEPP_HDL_ContatoreHall, NULL);
          /* Motor new positions are stored so the variable
             MotorNewPositionsToBeStored can be set to FALSE */
          EERAM_ConfigModel.MotorNewPositionsToBeStored = FALSE;
          EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
          EEPP_WriteData(EEPP_HDL_MEMODRIVEPOS, NULL);
        }
        else
        {
          /* DISPA_batteria_staccata == TRUE */
        }
      }
      else
      {
        /* adVoltage_Battery > VBAT_MEMO_POS */
      }
    }
  }
}

void DISPA_ComputeCommands(void)
{ 
  u32 checkTimer;
  CTRL_Fault_t VbattMot_diag;
  bool dummy, isProtReleOk = FALSE;
  PRES_Fault_t ProtRele;
  
  VbattMot_diag = ADCC_GetDiag(ADCC_MOT_Fbk);
  
  /* Call the function that set the positions if necessary */
  Dispa_CheckSetHall(DISPA_SLIDE,    MOTA_Output.Set_Hall_Slide);

  /* check fail on protection relay */
  FVMP_GetDiag(FVMP_PROT_RL, &ProtRele, &dummy);
  if ((ProtRele == PRES_NO_FAULT) ||
      (ProtRele == PRES_NOT_TESTED))
  {
    isProtReleOk = TRUE;
  }
  else
  {
    /* diagnosis on protection relay will be reset by MOTP_OpenProtRel */
    // FVMP_ResetLine(FVMP_PROT_RL);
  }
  
  /* motors command, check if VBATT MOTORS and prot rel are OK */
  //if (FVMP_isProtReleOk())
    if ((isProtReleOk) && 
      (CTRL_NO_FAULT == VbattMot_diag))
  {
    /* MOTP state transitions were disabled due to load dump protection */
    MOTP_Enable();
    /* seat motors command */
    DISPA_SetRequestedCmd(DISPA_SLIDE,    MOTA_Output.CmdMotor_Slide);
    DISPA_SetRequestedCmd(DISPA_LIFT,     MOTA_Output.CmdMotor_Lift);
    DISPA_SetRequestedCmd(DISPA_BACKREST, MOTA_Output.CmdMotor_Backrest);
    DISPA_SetRequestedCmd(DISPA_TILT,     MOTA_Output.CmdMotor_Tilt);
    TLRP_SetSlow(TLRP_LoadDumpTimeout);
  }
  else
  {
    checkTimer = TLRP_GetSlow(TLRP_LoadDumpTimeout);
    /* Request to stop the motors only if the battery voltage is undervoltage
    or if overvoltage condition persist for more than 1 second (load dump protection) */
    /* if there is a fail on protection relay, don't activate other relays */
    if((CTRL_UNDER_VOLTAGE == VbattMot_diag) || (checkTimer == 0UL))
    {
      /* MOTP state transitions could have been disabled due to load dump protection */
      MOTP_Enable();
      /* stop all motors */
      DISPA_SetRequestedCmd(DISPA_SLIDE ,   DISPA_IDLE_CMD);
      DISPA_SetRequestedCmd(DISPA_LIFT ,    DISPA_IDLE_CMD);
      DISPA_SetRequestedCmd(DISPA_BACKREST, DISPA_IDLE_CMD);
      DISPA_SetRequestedCmd(DISPA_TILT ,    DISPA_IDLE_CMD);
      /* stop ongoing automatic movements */
//      if (MOTA_Output.AutomaticMov == MOTA_ON)
//      {
//        MOTA_Input_Common.Antipanic = MOTA_PRESENT;
//      }
//      else
//      {
//        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
//      }
    }
    else
    {
      MOTP_Disable();
    }
  }

  /* heating command */
  DISPA_SetRequestedCmd(DISPA_SEAT_DRV, Dispa_HeatLevelDrv);
  DISPA_SetRequestedCmd(DISPA_SEAT_PSG, Dispa_HeatLevelPsg);
  DISPA_SetRequestedCmd(DISPA_STW,      Dispa_HeatLevelStw);
}

extern bool DISPA_IsSeatMoving(void)
{
  bool ret_val;
  
    if((MOTA_Output.CmdMotor_Backrest      != DISPA_IDLE_CMD)
      || (MOTA_Output.CmdMotor_Lift      != DISPA_IDLE_CMD)
      || (MOTA_Output.CmdMotor_Slide     != DISPA_IDLE_CMD)
      || (MOTA_Output.CmdMotor_Tilt      != DISPA_IDLE_CMD))
    {
      ret_val = TRUE;
    }
    else
    {
      ret_val = FALSE;
    }
    
  return ret_val;
}

void DISPA_PriorityManager(void)
{
  static bool motor_moving;
  bool_t checkTimer;
  CTRL_Fault_t batt_fail;

  motor_moving = DISPA_IsSeatMoving();
  checkTimer = Dispa_CheckActiveTimers();
  batt_fail = ADCC_GetDiag(ADCC_MOT_Fbk);

  /**** Seat Motors Management ***/

  /* key off timer management */
  if ((KEYA_GetKeyStatus() == KEYA_OFF_STATUS) && (checkTimer == FALSE) &&
      ((MOTA_Output.AutomaticMov) != MOTA_ON))
  {
    DISPA_SetEvent(DISPA_TILT,     DISPA_EVT_ABORT);
    DISPA_SetEvent(DISPA_LIFT,     DISPA_EVT_ABORT);
    DISPA_SetEvent(DISPA_BACKREST, DISPA_EVT_ABORT);
    DISPA_SetEvent(DISPA_SLIDE,    DISPA_EVT_ABORT);
    /* inform MOTA model that its movement are not executed */
   MOTA_Input_Common.Movement_Enable = MOTA_ABORT;
  }
  /* cranking management */
  else if (Dispa_CheckCranking() == TRUE)
  {
    DISPA_SetEvent(DISPA_TILT,     DISPA_EVT_SUSPEND);
    DISPA_SetEvent(DISPA_LIFT,     DISPA_EVT_SUSPEND);
    DISPA_SetEvent(DISPA_BACKREST, DISPA_EVT_SUSPEND);
    DISPA_SetEvent(DISPA_SLIDE,    DISPA_EVT_SUSPEND);
    /* inform MOTA model that its movement are not executed */
    MOTA_Input_Common.Movement_Enable = MOTA_SUSPEND;
  }
  else
  {
    /* seat motors can be moved */
    DISPA_SetEvent(DISPA_TILT,     DISPA_EVT_RUN);
    DISPA_SetEvent(DISPA_LIFT,     DISPA_EVT_RUN);
    DISPA_SetEvent(DISPA_BACKREST, DISPA_EVT_RUN);
    DISPA_SetEvent(DISPA_SLIDE,    DISPA_EVT_RUN);
    /* inform MOTA model that its movement are executed */
    MOTA_Input_Common.Movement_Enable = MOTA_RUN;
  }

  /**** Heaters Management ***/
  if (motor_moving == TRUE)
  {
    DISPA_SetEvent(DISPA_SEAT_DRV,     DISPA_EVT_SUSPEND);
    DISPA_SetEvent(DISPA_SEAT_PSG,     DISPA_EVT_SUSPEND);
    DISPA_SetEvent(DISPA_STW,          DISPA_EVT_SUSPEND);
  }
  else if ((VF608_GetOperationalModeSts() != CMMD_IGNITION_ON_ENGON) ||
           (CTRL_NO_FAULT !=  batt_fail))
  {
    DISPA_SetEvent(DISPA_SEAT_DRV,    DISPA_EVT_ABORT);
    DISPA_SetEvent(DISPA_SEAT_PSG,    DISPA_EVT_ABORT);
    DISPA_SetEvent(DISPA_STW,         DISPA_EVT_ABORT);
  }
  else
  {
    DISPA_SetEvent(DISPA_SEAT_DRV,    DISPA_EVT_RUN);
    DISPA_SetEvent(DISPA_SEAT_PSG,    DISPA_EVT_RUN);
    DISPA_SetEvent(DISPA_STW,         DISPA_EVT_RUN);
  }

}

/* called @100 ms */
void DISPA_UpdateStatus(void)
{
  static bool_t Dispa_Seat_E_SteeringColumnMoveSts;
  IPOC_DirectionCount_t dirSlide, dirBackr, dirLift, dirTilt;

  /*************************************/
  /******** update MOTA status *********/
  /*************************************/

  Dispa_Seat_E_SteeringColumnMoveSts = FALSE;
  
  dirSlide = IPOC_GetDirection(IPOC_Slide);
  dirBackr = IPOC_GetDirection(IPOC_Backres);
  dirLift = IPOC_GetDirection(IPOC_Lift);
  dirTilt = IPOC_GetDirection(IPOC_Tilt);

  /* Update seat and steering move status */
  Dispa_Seat_E_SteeringColumnMoveSts =
      (ActiveLoadSlave_t)
      (((dirSlide != IPOC_CMD_IDLE)?(TRUE):(FALSE)) ||
       ((dirBackr != IPOC_CMD_IDLE)?(TRUE):(FALSE)) ||
       ((dirLift != IPOC_CMD_IDLE)?(TRUE):(FALSE)) ||
       ((dirTilt != IPOC_CMD_IDLE)?(TRUE):(FALSE)));

  /* If the current seat and steering move status is different from respective status on CAN */
  if(FUNP_IsShortComfortTimer()==TRUE)
  {
    if( ((ActiveLoadSlave_t)Dispa_Seat_E_SteeringColumnMoveSts) != NWM_HMSM.bit.ActiveLoadSlave_HMSM)
    {
      /* seat is moving, set the slave active load and send a NET_ON req to NWMA */
      if( Dispa_Seat_E_SteeringColumnMoveSts  == CMMD_ACTIVE_LOADS_IN_MASTER )
      {
        (void)Dispa_SetNM_REQ(NWMA_NET_ON_REQ);
      }
      /* If the active load is released send a NET_OFF req to NWMA */
      else
      {
        (void)Dispa_SetNM_REQ(NWMA_NET_OFF_REQ);
      }
    }
    else
    {
    }
  }
  else
  {
    if(Dispa_Seat_E_SteeringColumnMoveSts == CMMD_ACTIVE_LOADS_IN_MASTER)
    {
      if(KEYA_GetKeyStatus() == KEYA_ON_STATUS)
      {
        (void)Dispa_SetNM_REQ(NWMA_NET_ON_REQ);
      }
      /* If the active load is released send a NET_OFF req to NWMA */
      else
      {
        (void)Dispa_SetNM_REQ(NWMA_NET_OFF_REQ);
      }
   }
    /* If the active load is released send a NET_OFF req to NWMA */
    else
    {
      (void)Dispa_SetNM_REQ(NWMA_NET_OFF_REQ);
    }
  }

  if (Init_Motor_Slide == MOTA_IN_PROGRESS)
  {
    Dispa_InitSlideInProg = TRUE;
  }

  /* check if init routine has ended */
  if((Init_Motor_Slide != MOTA_IN_PROGRESS) && (Dispa_InitSlideInProg == TRUE))
  {
    Dispa_InitSlideInProg = FALSE;
    MOTA_Input_Common.Init_From_Diag = MOTA_FALSE;
    /* save init state */
    //if routine was stopped, set antipanic to false
    MOTA_Input_Common.Antipanic = MOTA_ABSENT;
    EERAM_ConfigModel.Init_MotorSlide =  Init_Motor_Slide;
    EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
    if (Init_Motor_Slide == MOTA_INIT)
    {
      /* save strokes */
      EEPP_WriteData(EEPP_HDL_MeasuredMotorStroke, NULL);
      /* save current maps written by model */
      EEPP_WriteData(EEPP_HDL_CurrentMapBw, NULL);
    }
    else
    {
      /* Else condition added for Misra rule 14.10 */
    }
  }

}

/* This fucnction get the set_hall command from the model and update current motor position according to the command */
static void Dispa_CheckSetHall(DISPA_handle_t hdl, u08 set_hall_cmd)
{
  switch(set_hall_cmd)
  {
  case MOTA_SET_ZERO:
    /* a valid down/back stroke is recognized , set the position to 0 */
    MOTP_SetPosition((MOTP_Handle_t)DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE ,0U);
    if (MOTA_Input_Common.Actual_Pos_Loss == TRUE)
    {
      MOTA_Input_Common.Actual_Pos_Loss = FALSE;
      EERAM_ConfigModel.ActualPosLoss   = FALSE;
      EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
    }
    MOTP_SetStall((MOTP_Handle_t)DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, MOTP_DW_BW_STALL);
    break;

  case MOTA_SET_STROKE:
    /* a valid up/forward stroke is recognized , set the position to nominal stroke */
    MOTP_SetPosition((MOTP_Handle_t)DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE,
        EERAM_Measured_Motors_Stroke);
    MOTP_SetStall((MOTP_Handle_t)DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, MOTP_UP_FW_STALL);
    break;

  case MOTA_SET_NONE:
  default:
    /* nothing to do */
    break;
  }
}

/* This function calculate all the motor tolerance for init and for position verification
 * This function is called only at the startup or when the tolerance or nominla stroke of
 * at least one motor change value
 */
static void Dispa_SetTolerances(void)
{
  //MOTA_Input_Slide.Slide_Tolerance = (uint16_t)(((uint32_t)EERAM_Nominal_Motors_Stroke  * (uint32_t)DISPA_TOL_PERCENT)/100U);
  MOTA_Input_Slide.Slide_Tolerance = (Int16)DISPA_SLIDE_TOL;
}

/**
 * @brief Changes the "key" status following KEYA module notification
 * @author De Stephanis Alessio
 * @param [in] new KeyStatus
 * @param [out] None
 * @return None
 */
void DISPA_KeyOffEvent(void)
{
  /* Test if CountryCode is different from USA AND CANADA AND MEXICO */
  if(FUNP_IsShortComfortTimer()==TRUE)
  {/* Start 60" timer (active motors after key-off) */
    TLRP_SetSlow(TLRP_KeyOffStatus);
    TLRP_ResetSlow(TLRP_Comfort_Timer);
  }
  else
  {/* Start 20' timer (active motors after key-off) */
    TLRP_SetSlow(TLRP_Comfort_Timer);
    TLRP_ResetSlow(TLRP_KeyOffStatus);
  }
}

/**
 * @brief Changes the "Driver Door" status only in CountryCode equal to USA OR CANADA OR MEXICO
 * @author Fabio Zanchetta
 * @param [in] new Driver Door Status
 * @param [out] None
 * @return None
 */
void DISPA_DriverDoorStsChanged(CMMD_DoorSts_t DriverDoorStatus)
{
  /************************************************************************************/
  /* The following code performs a debounce on Driver Door Status.                     */
  /************************************************************************************/

  if (EERAM_DriverDoorStsInKeyOff != DriverDoorStatus)
  {
    EERAM_DriverDoorStsInKeyOff = DriverDoorStatus;
    EEPP_WriteData(EEPP_HDL_DriverDoorStsInKeyOff, NULL);

    /* Check if a Key-OFF status occurred */
    if(KEYA_GetKeyStatus() == KEYA_OFF_STATUS)
    {
      /* Start 20' timer (active motors after key-off) */
      TLRP_SetSlow(TLRP_Comfort_Timer);
    }
    else
    {
      /* Else condition added for Misra rule 14.10 */
    }
  }
  else
  {
    /* Else condition added for Misra rule 14.10 */
  }
}

/* Function called when the ECU is going to power off state from PSEUDO RUN state */
extern void DISPA_PseudoRUNPwrOff(void)
{
}

/* Function called when the ECU is going to power off state from RUN*/
extern void DISPA_PwrOff(void)
{
  /* save data for the model */
  EEPP_WriteData(EEPP_HDL_MEMODRIVEPOS, NULL);
  EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
  
  /* Save antipinch maps. It is not enough to save them after init routine,
   * since they are modified every EEP to be adapted to current trend    */
  EEPP_WriteData(EEPP_HDL_CurrentMapBw, NULL);
  EEPP_WriteData(EEPP_HDL_CounterVectorDownBwd, NULL);
  EEPP_WriteData(EEPP_HDL_CounterVectorUpBwd, NULL);
}

/********************************************************************/
/********************* CAN network callback *************************/
/********************************************************************/

/**
 * @brief Callback routine generated by CAN message received
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void DISPA_StatusClimateCbk(void)
{
  if (VF608_GetOperationalModeSts() == CMMD_IGNITION_ON_ENGON)
  {
    Dispa_HeatLevelDrv = (HeatedLeft_t)CMMD_HeatedLeft;
    Dispa_HeatLevelPsg = (HeatedLeft_t)CMMD_HeatedRight;
    Dispa_HeatLevelStw = (HeatedSteeringSts_t)CMMD_SteeringHeatedCmd;

    if (HEATA_GetLevel(HEATA_STW) != Dispa_HeatLevelStw)
    {
      HEATA_SetLevel(HEATA_STW, Dispa_HeatLevelStw);
    }
    if (HEATA_GetLevel(HEATA_SEAT_DRV) != Dispa_HeatLevelDrv)
    {
      HEATA_SetLevel(HEATA_SEAT_DRV, Dispa_HeatLevelDrv);
    }
    if (HEATA_GetLevel(HEATA_SEAT_PSG) != Dispa_HeatLevelPsg)
    {
      HEATA_SetLevel(HEATA_SEAT_PSG, Dispa_HeatLevelPsg);
    }
  }
  else
  {
    /* heating enabled only with engine on */
  }
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void DISPA_StatusLinCbk(void)
{
}

/********************************************************************/
/********************* Button input callback ************************/
/********************************************************************/

/**
 * @brief This routine returns true if at least one button is actually pressed
 * @param [in]
 * @param [out]
 * @return None
 */
bool  DISPA_IsButtonPressed(void)
{
  bool_t ret_val;

  ret_val = (Dispa_KB1Pressed || Dispa_KB2Pressed || Dispa_KB3Pressed) ? TRUE : FALSE;

  return ret_val;
}

/**
 * @brief Callback routine generated by button press event
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void DISPA_SlideFwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_SLIDE) == FALSE)
  {
    if(Dispa_KB2Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Slide_FW);
      if(inp_state == S_ON)
      {
        Dispa_KB2Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Slide.In_SlideUp = S_ON;
        }
      }
      else
      {
        MOTA_Input_Slide.In_SlideUp = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Slide.In_SlideUp = S_OFF;
    }
  }

}

void DISPA_SlideBwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_SLIDE) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB2Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Slide_BW);
      if(inp_state == S_ON)
      {
        Dispa_KB2Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Slide.In_SlideDown = S_ON;
        }
      }
      else
      {
        MOTA_Input_Slide.In_SlideDown = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Slide.In_SlideDown = S_OFF;
    }
  }
}

void DISPA_BackrestFwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_BACKREST) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB1Pressed == FALSE)
     {
       inp_state = DINP_GetState(DINP_Back_FW);
       if(inp_state == S_ON)
       {
         Dispa_KB1Pressed = TRUE;
         if (MOTA_Output.AutomaticMov == MOTA_ON)
         {
           MOTA_Input_Common.Antipanic = MOTA_PRESENT;
         }
         else
         {
           MOTA_Input_Backrest.In_BackrestUp = S_ON;
         }
       }
       else
       {
         MOTA_Input_Backrest.In_BackrestUp = S_OFF;
         MOTA_Input_Common.Antipanic = MOTA_ABSENT;
       }
     }
     else
     {
       MOTA_Input_Backrest.In_BackrestUp = S_OFF;
     }
  }
}

void DISPA_BackrestBwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_BACKREST) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB1Pressed == FALSE)
     {
       inp_state = DINP_GetState(DINP_Back_BW);
       if(inp_state == S_ON)
       {
         Dispa_KB1Pressed = TRUE;
         if (MOTA_Output.AutomaticMov == MOTA_ON)
         {
           MOTA_Input_Common.Antipanic = MOTA_PRESENT;
         }
         else
         {
           MOTA_Input_Backrest.In_BackrestDown = S_ON;
         }
       }
       else
       {
         MOTA_Input_Backrest.In_BackrestDown = S_OFF;
         MOTA_Input_Common.Antipanic = MOTA_ABSENT;
       }
     }
     else
     {
       MOTA_Input_Backrest.In_BackrestDown = S_OFF;
     }
  }
}

void DISPA_TiltUpInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_TILT) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB2Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Tilt_UP);
      if(inp_state == S_ON)
      {
        Dispa_KB2Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Tilt.In_TiltUp = S_ON;
        }
      }
      else
      {
        MOTA_Input_Tilt.In_TiltUp = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Tilt.In_TiltUp = S_OFF;
    }
  }
}

void DISPA_TiltDwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_TILT) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB2Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Tilt_DW);
      if(inp_state == S_ON)
      {
        Dispa_KB2Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Tilt.In_TiltDown = S_ON;
        }
      }
      else
      {
        MOTA_Input_Tilt.In_TiltDown = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Tilt.In_TiltDown = S_OFF;
    }
  }
}

void DISPA_LiftUpInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_LIFT) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB1Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Lift_UP);
      if(inp_state == S_ON)
      {
        Dispa_KB1Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Lift.In_LiftUp = S_ON;
        }
      }
      else
      {
        MOTA_Input_Lift.In_LiftUp = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Lift.In_LiftUp = S_OFF;
    }
  }
}

void DISPA_LiftDwInput_Cbk(void)
{
  CTRL_State_t inp_state;

  if(DISPA_isIoControlActive(DISPA_LIFT) == FALSE) //DF: 30.01.2015, for UDS IOControl management
  {
    if(Dispa_KB1Pressed == FALSE)
    {
      inp_state = DINP_GetState(DINP_Lift_DW);
      if(inp_state == S_ON)
      {
        Dispa_KB1Pressed = TRUE;
        if (MOTA_Output.AutomaticMov == MOTA_ON)
        {
          MOTA_Input_Common.Antipanic = MOTA_PRESENT;
        }
        else
        {
          MOTA_Input_Lift.In_LiftDown = S_ON;
        }
      }
      else
      {
        MOTA_Input_Lift.In_LiftDown = S_OFF;
        MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      }
    }
    else
    {
      MOTA_Input_Lift.In_LiftDown = S_OFF;
    }
  }
}


/**
 * @brief Callback for Slide/Tilt open state (no button pressed)
 * @author Davide Fogliano - Polimatica S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void DISPA_SlideTiltOpen_Cbk(void)
{
  if(DINP_GetState(DINP_SlideTilt_OPEN) == S_ON)
  {
    Dispa_KB2Pressed = FALSE;
    MOTA_Input_Common.Antipanic = MOTA_ABSENT;
  }
}

/**
 * @brief Callback for Slide/Tilt open state (no button pressed)
 * @author Davide Fogliano - Polimatica S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void DISPA_BackrLiftOpen_Cbk(void)
{
  if(DINP_GetState(DINP_BackrLift_OPEN) == S_ON)
  {
    Dispa_KB1Pressed = FALSE;
    MOTA_Input_Common.Antipanic = MOTA_ABSENT;
  }
}

/**
 * @brief Callback for memory open state (no button pressed)
 * @author Davide Fogliano - Polimatica S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
DISPA_EXTERN void DISPA_MemOpen_Cbk(void)
{
  if(DINP_GetState(DINP_Mem_OPEN) == S_ON)
  {
    Dispa_KB3Pressed = FALSE;
    MOTA_Input_Common.Antipanic = MOTA_ABSENT;
  }
}


/**
 * @brief Routine callback for memory recall request
 * @param [in] None
 * @param [out] None
 * @return None
 */
void DISPA_Mem1Input_Cbk(void)
{
  CTRL_State_t inp_state;
  u32 checkTimer;
  u16 vehicle_speed;
  
  if(Dispa_KB3Pressed == FALSE)
  {
    inp_state = DINP_GetState(DINP_Mem1);
    if (MOTA_Output.AutomaticMov == MOTA_ON)
    {
      /* act as antipanic only on button pressed and not on button released */
      if (inp_state == S_ON)
      {
        MOTA_Input_Common.Antipanic = MOTA_PRESENT;
      }
    }
    else
    {
      MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      if (inp_state == S_ON)
      {
        //Dispa_KB3Pressed = TRUE;
        Dispa_LastMemorySel = 1U;
        TLRP_SetSlow(TLRP_UserSavePos);
      }
      else
      {
        if (Dispa_LastMemorySel == 1U)
        {
          Dispa_LastMemorySel = 0U;
          
          if (TLRP_GetSlow(TLRP_UserSavePos) > 0U)
          {
            checkTimer    = TLRP_GetSlow(TLRP_KeyOffStatus); /* FZ - CR10360 - In case that the CountryCode is equal to USA or CANADA or MEXICO */
                                                             /*                TLRP_KeyOffStatus timer is already set to 0 therefore the memory */
                                                             /*                recall is not executed                                           */
            vehicle_speed = FUNP_GetVehicleSpeed();
            /* check all conditions to recall a memory are satisfied */
            if (((KEYA_GetKeyStatus()  == KEYA_ON_STATUS) || (checkTimer > 0u)) &&
                 (vehicle_speed    <  DISPA_MEM_RECALL_SPEED)                   &&
                 (CMMD_VehicleFail == CMMD_SPEED_FAIL_NOT_PRESENT))
            {
              MOTA_Input_Common.MCU_PositionRecall = Dispa_CheckMemory(MOTA_MEMORY_1);
              TLRP_ResetSlow(TLRP_UserSavePos);
              TLRP_SetFast(TLRP_ClrRecallReq);
#ifdef __EXMMA_IS_PRESENT__
             // recall mirrors memory only if slide is initialized and it will recall its position
             if (DISPA_GetInitializationStatus() == MOTA_INIT)
             {
              Dispa_SetMirrorsMemoryToRecall(MEM_1);
             }
             else
             {
             }
#endif
            }
            else
            {
            }
          }
        }
      }
    }
  }
}

/**
 * @brief Routine callback for memory recall request
 * @param [in] None
 * @param [out] None
 * @return None
 */
void DISPA_Mem2Input_Cbk(void)
{
  CTRL_State_t inp_state;
  u32 checkTimer;
  u16 vehicle_speed;
  
  if(Dispa_KB3Pressed == FALSE)
  {
    inp_state = DINP_GetState(DINP_Mem2);
    if (MOTA_Output.AutomaticMov == MOTA_ON)
    {
      /* act as antipanic only on button pressed and not on button released */
      if (inp_state == S_ON)
      {
        MOTA_Input_Common.Antipanic = MOTA_PRESENT;
      }
    }
    else
    {
      MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      if (inp_state == S_ON)
      {
        //Dispa_KB3Pressed = TRUE;
        Dispa_LastMemorySel = 2U;
        TLRP_SetSlow(TLRP_UserSavePos);
      }
      else
      {
        if (Dispa_LastMemorySel == 2U)
        {
          Dispa_LastMemorySel = 0U;

          if (TLRP_GetSlow(TLRP_UserSavePos) > 0U)
          {
            checkTimer    = TLRP_GetSlow(TLRP_KeyOffStatus); /* FZ - CR10360 - In case that the CountryCode is equal to USA or CANADA or MEXICO */
                                                             /*                TLRP_KeyOffStatus timer is already set to 0 therefore the memory */
                                                             /*                recall is not executed                                           */
            vehicle_speed = FUNP_GetVehicleSpeed();
            /* check all conditions to recall a memory are satisfied */
            if (((KEYA_GetKeyStatus()  == KEYA_ON_STATUS) || (checkTimer > 0u)) &&
                 (vehicle_speed    <  DISPA_MEM_RECALL_SPEED)                   &&
                 (CMMD_VehicleFail == CMMD_SPEED_FAIL_NOT_PRESENT))
            {
              MOTA_Input_Common.MCU_PositionRecall = Dispa_CheckMemory(MOTA_MEMORY_2);
              TLRP_ResetSlow(TLRP_UserSavePos);
              TLRP_SetFast(TLRP_ClrRecallReq);
#ifdef __EXMMA_IS_PRESENT__
             // recall mirrors memory only if slide is initialized and it will recall its position
             if (DISPA_GetInitializationStatus() == MOTA_INIT)
             {
               Dispa_SetMirrorsMemoryToRecall(MEM_2);
             }
             else
             {
             }
#endif
            }
            else
            {
            }
          }
        }
      }
    }
  }
}

/**
 * @brief Routine callback for memory recall request
 * @param [in] None
 * @param [out] None
 * @return None
 */
void DISPA_Mem3Input_Cbk(void)
{
  CTRL_State_t inp_state;
  u32 checkTimer;
  u16 vehicle_speed;
  
  if(Dispa_KB3Pressed == FALSE)
  {
    inp_state = DINP_GetState(DINP_Mem3);
    if (MOTA_Output.AutomaticMov == MOTA_ON)
    {
      /* act as antipanic only on button pressed and not on button released */
      if (inp_state == S_ON)
      {
        MOTA_Input_Common.Antipanic = MOTA_PRESENT;
      }
    }
    else
    {
      MOTA_Input_Common.Antipanic = MOTA_ABSENT;
      if (inp_state == S_ON)
      {
        //Dispa_KB3Pressed = TRUE;
        Dispa_LastMemorySel = 3U;
        TLRP_SetSlow(TLRP_UserSavePos);
      }
      else
      {
        if (Dispa_LastMemorySel == 3U)
        {
          Dispa_LastMemorySel = 0U;

          if (TLRP_GetSlow(TLRP_UserSavePos) > 0U)
          {
            checkTimer    = TLRP_GetSlow(TLRP_KeyOffStatus); /* FZ - CR10360 - In case that the CountryCode is equal to USA or CANADA or MEXICO */
                                                             /*                TLRP_KeyOffStatus timer is already set to 0 therefore the memory */
                                                             /*                recall is not executed                                           */
            vehicle_speed = FUNP_GetVehicleSpeed();
            /* check all conditions to recall a memory are satisfied */
            if (((KEYA_GetKeyStatus()  == KEYA_ON_STATUS) || (checkTimer > 0u)) &&
                 (vehicle_speed    <  DISPA_MEM_RECALL_SPEED)                   &&
                 (CMMD_VehicleFail == CMMD_SPEED_FAIL_NOT_PRESENT))
            {
              MOTA_Input_Common.MCU_PositionRecall = Dispa_CheckMemory(MOTA_MEMORY_3);
              TLRP_ResetSlow(TLRP_UserSavePos);
              TLRP_SetFast(TLRP_ClrRecallReq);
#ifdef __EXMMA_IS_PRESENT__
             // recall mirrors memory only if slide is initialized and it will recall its position
             if (DISPA_GetInitializationStatus() == MOTA_INIT)
             {
               Dispa_SetMirrorsMemoryToRecall(MEM_3);
             }
             else
             {
             }
#endif
            }
            else
            {
            }
          }
        }
      }
    }
  }
}

/**
 * @brief This function requestes NET_ON or NET_OFF to network management
 * @return void
 * @note  It must be called periodically at 50 ms or lower time
 */
void DISPA_NwmNotification(void)
{
  NWMA_NetStateReq_t NM_REQ;

  NM_REQ = Dispa_GetNM_REQ();
  
  /* if the request was correctly set to NWMA module, remove it */
  if (NWMA_NmStateReq(NM_REQ) == APPL_OK)
  {
    Dispa_SetNM_REQ(NWMA_NONE_REQ);
  }
}

/**
 * @brief Get the network management requested in DISPA SwC
 * @author Giuseppe Barberio
 * @param [in] none
 * @param [out] none
 * @return network management request as per NWMA_NetStateReq_t
 */
static NWMA_NetStateReq_t Dispa_GetNM_REQ(void)
{
  return Dispa_NM_request;
}


/**
 * @brief Set the network management requested in DISPA SwC
 * @author Giuseppe Barberio
 * @param [in] none
 * @param [out] none
 * @return none
 */
static void Dispa_SetNM_REQ(NWMA_NetStateReq_t NM_request)
{
  Dispa_NM_request = NM_request;
}

//APSA debug functions
uint8_t DISPA_GetAntiPinchSegment(void)
{
  return APSA_OUTPUT.Index_vector;
}

uint16_t DISPA_GetAttentionThreshold(void)
{
  return APSA_OUTPUT.Threshold_Attention_Update;
}

uint16_t DISPA_GetAntiPinchThreshold(void)
{
  return APSA_OUTPUT.Threshold_AntiPinch_Update;
}

/**
 * @brief This function is used to set DISPA state machine of the functions according to the proxi configuration.
 * @author Francesco Talarico
 * @param [in] none
 * @param [out] none
 * @return none
 */
void DISPA_UpdateFunctionByProxi(void)
{
  if(EERAM_BproxiConfig[EERAM_BproxiValue].TiltEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_TILT, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_SLIDE, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].LiftEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_LIFT, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].BackEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_BACKREST, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].HeatDvrEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_SEAT_DRV, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].HeatPsgEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_SEAT_PSG, DISPA_EVT_DISABLE);
  }
  if(EERAM_BproxiConfig[EERAM_BproxiValue].HeatStrEn == DISABLE)
  {
    DISPA_SetEvent(DISPA_STW, DISPA_EVT_DISABLE);
  }
}

/**
 * @brief Callback routine generated by CAN message received
 * @author Fabio Zanchetta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
DISPA_EXTERN void DISPA_GateWayRemoteCranking(void)
{
  MOTA_Input_Common.RemoteCranking = STATUS_BH_BCM2.bit.RemStActvSts;
}


#endif
/*______ E N D _____ (DISPA_config.c) _________________________________________*/
