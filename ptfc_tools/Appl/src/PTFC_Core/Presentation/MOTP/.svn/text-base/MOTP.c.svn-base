/**
 * @file   MOTP.c
 * @author mmastrodonato
 * @date   18/set/2014
 * @brief 
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 * MM             Matteo Mastrodonato       Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 18/set/2014    0.1  MM      First revision
 * 02/mar/2015    0.2  MM      - Cmd management modified, now is generalized for
 *                             various type of output drivers.
 *                             - Added CmdArray structures.
 *                             - Static configuration semplified.
 */

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MOTP.h"
#include "MOTP_config.h"

/* Module inhibition filter */
#ifdef __MOTP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef enum Motp_state_e
{
  MOTP_STATE_IDLE,
  MOTP_STATE_UP_FW,
  MOTP_STATE_DW_BW,
  MOTP_STATE_BRAKE,
  MOTP_STATE_REC_IDLE,
  MOTP_STATE_REC_BRAKE,
  MOTP_STATE_NUM
}Motp_state_t;

typedef enum Motp_event_e
{
  MOTP_EVT_IDLE,
  MOTP_EVT_START_UP_FW,
  MOTP_EVT_START_DW_BW,
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
  MOTP_EVT_STG,
  MOTP_EVT_STB,
#endif
  MOTP_EVT_NUM
}Motp_cmdEvent_t;

typedef enum Motp_trans_e
{
  MOTP_TRANSITION_ENTRY,
  MOTP_TRANSITION_DURING,
  MOTP_TRANSITION_EXIT,
  MOTP_TRANSITION_NUM
}Motp_transition_t;

typedef struct Motp_PrivateData_s
{
  MOTP_Command_t          command;
  Motp_state_t            machineState;
  uint8_t                 brakeTime;
  int16_t                 prevPosition;
  uint16_t                stallTime;
  MOTP_PosFkbDiag_t       posFbkFault;
  PRES_Fault_t            driverFault;
  MOTP_MotStatus_t        motorSts;
  bool_t                  checkPos;
//  MOTP_MotStatus_t        lastMovement; 
} Motp_PrivateData_t;

typedef struct Motp_CmdArrayPrivateData_s
{
  MOTP_Handle_t           motpHdl;
  PRES_Fault_t            lastFault;
  PRES_Fault_t            validatedFault;
}Motp_CmdArrayPrivateData_t;
  
typedef void (*Motp_MotMoveTransSM_t)(MOTP_Handle_t motor);

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static void Motp_NewMotorState    (Motp_cmdEvent_t event, MOTP_Handle_t motor);
static void Motp_SetCmdArrayState (MOTP_CmdArrayHdl_t cmdArray, Motp_intCommand_t intCmd);
static void Motp_PosFbkDiag       (MOTP_Handle_t motor);
static void Motp_PosFbkInvalidDiag(MOTP_Handle_t motor);

static void Motp_IdleEntry    (MOTP_Handle_t motor);
static void Motp_UpFwEntry    (MOTP_Handle_t motor);
static void Motp_DwBwEntry    (MOTP_Handle_t motor);
static void Motp_BrakeEntry   (MOTP_Handle_t motor);
static void Motp_RecIdleEntry (MOTP_Handle_t motor);
static void Motp_RecBrakeEntry(MOTP_Handle_t motor);

static void Motp_IdleDuring     (MOTP_Handle_t motor);
static void Motp_MovementDuring (MOTP_Handle_t motor);
static void Motp_BrakeDuring    (MOTP_Handle_t motor);
static void Motp_RecIdleDuring  (MOTP_Handle_t motor);
static void Motp_RecBrakeDuring (MOTP_Handle_t motor);

static void Motp_IdleExit     (MOTP_Handle_t motor);
static void Motp_RecoveryExit (MOTP_Handle_t motor);

static void Motp_PosFbkFaultRecovery(MOTP_Handle_t motor);
static void Motp_UpFwStrokeDetected (MOTP_Handle_t motor);
static void Motp_DwBwStrokeDetected (MOTP_Handle_t motor);

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/


static const Motp_state_t MOTP_MotorMoveSM[MOTP_EVT_NUM][MOTP_STATE_NUM] = {
/* STATE/INP_EVENT               STATE_IDLE            STATE_UP_FW           STATE_DW_BW           STATE_BRAKE           STATE_REC_IDLE       STATE_REC_BRAKE  */
/* MOTP_EVT_IDLE           */  { MOTP_STATE_IDLE,      MOTP_STATE_BRAKE,     MOTP_STATE_BRAKE,     MOTP_STATE_IDLE,      MOTP_STATE_IDLE,     MOTP_STATE_IDLE       },
/* MOTP_EVT_START_UP_FW    */  { MOTP_STATE_UP_FW,     MOTP_STATE_UP_FW,     MOTP_STATE_BRAKE,     MOTP_STATE_BRAKE,     MOTP_STATE_IDLE,     MOTP_STATE_IDLE       },
/* MOTP_EVT_START_DW_BW    */  { MOTP_STATE_DW_BW,     MOTP_STATE_BRAKE,     MOTP_STATE_DW_BW,     MOTP_STATE_BRAKE,     MOTP_STATE_IDLE,     MOTP_STATE_IDLE       },
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
/* MOTP_EVT_STG            */  { MOTP_STATE_IDLE,      MOTP_STATE_REC_IDLE,  MOTP_STATE_REC_IDLE,  MOTP_STATE_REC_IDLE,  MOTP_STATE_REC_IDLE, MOTP_STATE_REC_BRAKE  },
/* MOTP_EVT_STB            */  { MOTP_STATE_REC_BRAKE, MOTP_STATE_REC_BRAKE, MOTP_STATE_REC_BRAKE, MOTP_STATE_REC_BRAKE, MOTP_STATE_REC_IDLE, MOTP_STATE_REC_BRAKE  },
#endif
};

static const Motp_MotMoveTransSM_t Motp_MotMoveTransSM[MOTP_TRANSITION_NUM][MOTP_STATE_NUM] = {
/* STATE/TRANSITION              STATE_IDLE            STATE_UP_FW           STATE_DW_BW           STATE_BRAKE           STATE_REC_IDLE       STATE_REC_BRAKE  */
/* ENTRY                   */  { Motp_IdleEntry,       Motp_UpFwEntry,       Motp_DwBwEntry,       Motp_BrakeEntry,      Motp_RecIdleEntry,   Motp_RecBrakeEntry    },
/* DURING                  */  { Motp_IdleDuring,      Motp_MovementDuring,  Motp_MovementDuring,  Motp_BrakeDuring,     Motp_RecIdleDuring,  Motp_RecBrakeDuring   },
/* EXIT                    */  { Motp_IdleExit,        NULL,                 NULL,                 NULL,                 Motp_RecoveryExit,   Motp_RecoveryExit     }
};

static Motp_PrivateData_t Motp_PrivateData[MOTP_MAX_HDL];
static Motp_CmdArrayPrivateData_t Motp_CmdArrayPrivateData[MOTP_MAX_CMDA_HDL];


static bool Motp_diagEnabled;
static bool Motp_FreezeSts;

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * API to initialize the MOTP module. Call one time at system power on.
 * MOTP_Init
 *
 */
void MOTP_Init(void)
{
  MOTP_Handle_t         motor;
  MOTP_CmdArrayHdl_t cmdArray;

  for(motor = (MOTP_Handle_t)0u; motor < MOTP_MAX_HDL; motor++)
  {
    Motp_PrivateData[motor].command        = MOTP_REQ_STOP;
    Motp_PrivateData[motor].machineState   = MOTP_STATE_IDLE;
    Motp_PrivateData[motor].brakeTime      = MOTP_BRAKE_TIME;
    Motp_PrivateData[motor].prevPosition   = 0;
    Motp_PrivateData[motor].stallTime      = 0u;
    Motp_PrivateData[motor].posFbkFault    = MOTP_FBK_NO_FAULT;
    Motp_PrivateData[motor].motorSts       = MOTP_STS_STOPPED;
    Motp_PrivateData[motor].checkPos       = TRUE;
//    Motp_PrivateData[motor].lastMovement   = MOTP_STS_STOPPED;
  }

  for(cmdArray = (MOTP_CmdArrayHdl_t)0u; cmdArray < MOTP_MAX_CMDA_HDL; cmdArray++)
  {
    Motp_CmdArrayPrivateData[cmdArray].motpHdl        = MOTP_MAX_HDL;
    Motp_CmdArrayPrivateData[cmdArray].lastFault      = PRES_NOT_TESTED;
    Motp_CmdArrayPrivateData[cmdArray].validatedFault = PRES_NOT_TESTED;
  }
  
  Motp_diagEnabled = TRUE;

  Motp_FreezeSts = FALSE;

  /* User defined init procedure */
  MOTP_CONFIG_INIT()
}

/**
 * API to manage motor movements. To call periodically.
 * MOTP_Mgm
 *
 */
void MOTP_Mgm(void)
{
  MOTP_Handle_t motor;

  for(motor = (MOTP_Handle_t)0u; motor < MOTP_MAX_HDL; motor++)
  {
    /* Execute state "during" transition for each motor */
    if (Motp_MotMoveTransSM[MOTP_TRANSITION_DURING][Motp_PrivateData[motor].machineState] != NULL)
    {
      Motp_MotMoveTransSM[MOTP_TRANSITION_DURING][Motp_PrivateData[motor].machineState](motor);
    }
    else {} 
    
  }
  
}

/**
 * API to request a motor movement
 * MOTP_SetMovement
 *
 */
PRES_ResSts_t MOTP_SetMovement(MOTP_Handle_t motor, MOTP_Command_t command)
{
  PRES_ResSts_t      valueReturn;
  MOTP_CmdArrayHdl_t cmdArrayHdl;

  if (Motp_PrivateData[motor].command != command)
  {
    cmdArrayHdl = MOTP_CfgTable[motor].CMD_ARRAY_HDL;

    /* Check if cmdArray resource is free or is already assigned to this "motor".  */
    if ((Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl == MOTP_MAX_HDL) ||
        (Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl == motor) ||
        (Motp_PrivateData[motor].motorSts == MOTP_STS_FAIL))
    {
      /* Assign/Lock the CmdArray resource */
      Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl = motor;  
      Motp_CmdArrayPrivateData[cmdArrayHdl].lastFault = PRES_NOT_TESTED;
      Motp_CmdArrayPrivateData[cmdArrayHdl].validatedFault = PRES_NOT_TESTED;
      
      /* Store inputs state */
      Motp_PrivateData[motor].command  = command;

      /* Trigger event transition */
      switch (command)
      {
        case MOTP_REQ_STOP:
          Motp_NewMotorState(MOTP_EVT_IDLE, motor);
          valueReturn = PRES_OK;
          break;

        case MOTP_REQ_MOVE_UP_FW:
          Motp_NewMotorState(MOTP_EVT_START_UP_FW, motor);
          valueReturn = PRES_OK;
          break;

        case MOTP_REQ_MOVE_DW_BW:
          Motp_NewMotorState(MOTP_EVT_START_DW_BW, motor);
          valueReturn = PRES_OK;
          break;

        default:
          valueReturn = PRES_PAR_NOT_OK;
          break;
      }
    }
    else
    {
      /* resource cmdArray is busy */
      valueReturn = PRES_BUSY;
    }
  }
  else
  {
    valueReturn = PRES_OK;
  }

  return valueReturn;
}

/**
 * API to get the motor status
 * MOTP_GetMotorStatus
 *
 */
MOTP_MotStatus_t MOTP_GetMotorStatus(MOTP_Handle_t motor)
{
  return (Motp_PrivateData[motor].motorSts);
}

/**
 * API to get the position feedback status
 * MOTP_GetCmdArrayDiag
 *
 */
PRES_Fault_t MOTP_GetCmdArrayDiag(MOTP_CmdArrayHdl_t cmdArray)
{
  CTRL_Fault_t faultCmd[MOTP_NUM_CMD];
  PRES_Fault_t valueReturn;
  uint8_t i;
  
  valueReturn = PRES_NO_FAULT;
  
  if (Motp_diagEnabled == TRUE)
  {
    /* Check all CMD Diagnosis */
    for (i = 0U; i < MOTP_NUM_CMD; i++)
    {
      if (MOTP_CmdArrayTable[cmdArray].CMD_HDL[i] != MOTP_CMD_NOT_USED)
      {
        faultCmd[i] = MOTP_CmdArrayTable[cmdArray].DIAG_FUN_PTR(MOTP_CmdArrayTable[cmdArray].CMD_HDL[i]);
        
        if(faultCmd[i] == CTRL_NOT_TESTED)
        {
          valueReturn = (PRES_Fault_t)faultCmd[i];
        }
        else if (faultCmd[i] != CTRL_NO_FAULT)
        {
          valueReturn = (PRES_Fault_t)faultCmd[i];
          Motp_CmdArrayPrivateData[cmdArray].lastFault = valueReturn;
          break; /* One fault found --> exit */
        }
        else
        {
        }
      }
      else
      {
      }
    }
  }
  else
  {
    /* this value is returned if the diagnosis was disabled by other modules
     * to not performe diagnosis on the motors relays (e.g. for example to diagnose
     * only the protecion relay) */
    valueReturn = PRES_NOT_TESTED;
  }
  
  /* if all the commands of the array are not in fault, the array state is NO_FAULT */
  if (valueReturn == PRES_NO_FAULT)
  {
    Motp_CmdArrayPrivateData[cmdArray].lastFault = PRES_NO_FAULT;
  }
  
  return valueReturn;
}

/**
 * API to get the position feedback status
 * MOTP_GetCmdArrayDiagState
 *
 */
PRES_State_t MOTP_GetCmdArrayDiagState(MOTP_CmdArrayHdl_t cmdArray)
{
  PRES_State_t valueReturn;

  if (Motp_CmdArrayPrivateData[cmdArray].motpHdl == MOTP_MAX_HDL)
  {
    valueReturn = S_OFF;
  }
  else
  {
    valueReturn = S_ON;
  }

  return valueReturn;
}

/**
 * API to get the position feedback diagnosis.
 * MOTP_GetPosFbkDiag
 *
 */
PRES_Fault_t MOTP_GetPosFbkDiag(MOTP_Handle_t motor)
{
  PRES_Fault_t valueReturn;

  if (Motp_PrivateData[motor].posFbkFault == MOTP_FBK_FAULT)
  {
    valueReturn = PRES_TOO_FEW_TRANS;
  }
  else
  {
    valueReturn = PRES_NO_FAULT;
  }

  return valueReturn;
}

/**
 * @brief API to freeze MOTP state machine, the new commands received will be ignored until MOTP_Enable() is called
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void MOTP_Disable(void)
{
  Motp_FreezeSts = TRUE;
}

/**
 * @brief API to enable MOTP to receive new commands
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void MOTP_Enable(void)
{
  Motp_FreezeSts = FALSE;
}

/**
 * @brief API to enable or disable MOTP diagnosis on motors output.
 * The diagnosis on protection relays does not depend on this state
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void MOTP_SetDiagState(bool state)
{
  Motp_diagEnabled = state;
}

/**
 * API to initialize the fault state. Typically called after clear DTC.
 * MOTP_ClearFaults
 *
 */
void MOTP_ClearFaults(void)
{
  MOTP_Handle_t      motor;
  MOTP_CmdArrayHdl_t cmdArray;

  for(motor = (MOTP_Handle_t)0u; motor < MOTP_MAX_HDL; motor++)
  {
    if ((Motp_PrivateData[motor].motorSts == MOTP_STS_FAIL) ||
        (Motp_PrivateData[motor].posFbkFault == MOTP_FBK_FAULT))
    {
      Motp_PrivateData[motor].stallTime = 0U;
      Motp_PrivateData[motor].posFbkFault = MOTP_FBK_NO_FAULT;
      // clear motor status, otherwise following state transiction will not be performed
      Motp_PrivateData[motor].motorSts = MOTP_STS_STOPPED;
      Motp_NewMotorState(MOTP_EVT_IDLE, motor);
      // checkPos was set to FALSE when a fail is detected, reset it to TRUE
      Motp_PrivateData[motor].checkPos = TRUE;
      //Motp_PrivateData[motor].lastMovement   = MOTP_STS_STOPPED;
    }
  }

  for(cmdArray = (MOTP_CmdArrayHdl_t)0u; cmdArray < MOTP_MAX_CMDA_HDL; cmdArray++)
  {
    Motp_CmdArrayPrivateData[cmdArray].lastFault = PRES_NOT_TESTED;
  }
}

/**
 * @brief API to initialize the fault state for a specific handle
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void MOTP_ClearFault(MOTP_Handle_t hdl)
{
  /* clear motor status */
  Motp_PrivateData[hdl].stallTime = 0U;
  Motp_PrivateData[hdl].posFbkFault = MOTP_FBK_NO_FAULT;
  // clear motor status, otherwise idle state transiction will not be performed
  Motp_PrivateData[hdl].motorSts = MOTP_STS_STOPPED;
  Motp_NewMotorState(MOTP_EVT_IDLE, hdl);
  // checkPos was set to FALSE when a fail is detected, reset it to TRUE
  Motp_PrivateData[hdl].checkPos = TRUE;
  //Motp_PrivateData[hdl].lastMovement = MOTP_STS_STOPPED;

  /* clear command array motor status */
  Motp_CmdArrayPrivateData[MOTP_CfgTable[hdl].CMD_ARRAY_HDL].lastFault = PRES_NOT_TESTED;
}

/**
 * API to manage the soft system shutdown.
 * MOTP_PwrOff
 *
 */
void MOTP_PwrOff(void)
{
  MOTP_CONFIG_PWR_OFF()
}


#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
void MOTP_SetFaultEvent(MOTP_Handle_t motor, PRES_Fault_t Fault)
{
  if( (Fault == PRES_SHORT_TO_BAT) ||
      (Fault == PRES_OC_OR_STB))
  {
    Motp_NewMotorState(MOTP_EVT_STB, motor);
  }
  else
  {
  }
}
#endif

/**
 * API to communicate the fault validation of a cmdArray
 * MOTP_CmdArrayFaultEvent
 *
 */
void MOTP_SetCmdArrayFaultEvent(MOTP_CmdArrayHdl_t cmdArray, PRES_Fault_t Fault)
{
  Motp_CmdArrayPrivateData[cmdArray].validatedFault = Fault;
}

/*************************************************
 *
 * ENTRY/EXIT TRANSITIONS
 *
 ************************************************/
static void Motp_IdleEntry(MOTP_Handle_t motor)
{
  /* Put motor in IDLE */
  //DF: modification for the new model based SW MOTA, the status is set to stopped only if was not in fail */
  if(Motp_PrivateData[motor].motorSts != MOTP_STS_FAIL)
  {
    Motp_PrivateData[motor].motorSts = MOTP_STS_STOPPED;
  }
  
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_IDLE);
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_IDLE);
  /* Free CMD ARRAY */
  Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].motpHdl = MOTP_MAX_HDL;
}

static void Motp_UpFwEntry(MOTP_Handle_t motor)
{
//  if(Motp_PrivateData[motor].lastMovement != MOTP_STS_MOVE_UP_FW)
//  {
  Motp_PrivateData[motor].stallTime = 0u;
//  }
  Motp_PrivateData[motor].motorSts = MOTP_STS_MOVE_UP_FW;
//  Motp_PrivateData[motor].lastMovement = MOTP_STS_MOVE_UP_FW;
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_UP_FW);
  IPOC_SetStallStatus(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_NO_STALL);
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_UP_FW);
}

static void Motp_DwBwEntry(MOTP_Handle_t motor)
{ 
//  if(Motp_PrivateData[motor].lastMovement != MOTP_STS_MOVE_DW_BW)
//  {
  Motp_PrivateData[motor].stallTime = 0u;
//  }
  Motp_PrivateData[motor].motorSts = MOTP_STS_MOVE_DW_BW;
//  Motp_PrivateData[motor].lastMovement = MOTP_STS_MOVE_DW_BW;
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_DW_BW);
  IPOC_SetStallStatus(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_NO_STALL);
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_DOWN_BW);
}

static void Motp_BrakeEntry(MOTP_Handle_t motor)
{
  Motp_PrivateData[motor].brakeTime = MOTP_BRAKE_TIME;
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_IDLE);
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_BRAKE);
}

#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
static void Motp_RecIdleEntry(MOTP_Handle_t motor)
{
  /* Put motor commands in IDLE */
  Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].motpHdl = motor;  
  Motp_PrivateData[motor].motorSts = MOTP_STS_FAIL;
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_IDLE);
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_IDLE);
}

static void Motp_RecBrakeEntry(MOTP_Handle_t motor)
{
  /* Put motor commands in BRAKE */
  Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].motpHdl = motor;
  Motp_PrivateData[motor].motorSts = MOTP_STS_FAIL;
  IPOC_SetDirection(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_CMD_IDLE);
  Motp_SetCmdArrayState(MOTP_CfgTable[motor].CMD_ARRAY_HDL, MOTP_CMD_BRAKE);
}
#endif

static void Motp_IdleExit(MOTP_Handle_t motor)
{
  MOTP_PRE_MOVE_EVT(motor)
}

static void Motp_RecoveryExit (MOTP_Handle_t motor)
{
  /* TODO COBRA: reset local fault */
  Motp_PrivateData[motor].motorSts = MOTP_STS_STOPPED;
  Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].lastFault = PRES_NOT_TESTED;

  /* call user macro to perform actions after recovery is stopped */
  MOTP_STOP_RECOVERY()
}

/*************************************************
 *
 * DURING ACTIONS
 *
 ************************************************/
static void Motp_IdleDuring(MOTP_Handle_t motor)
{
  MOTP_CmdArrayHdl_t cmdArrayHdl;

  /* Check exit condition */
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
  PRES_Fault_t fault;

  fault = Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].validatedFault;

  if((fault == PRES_SHORT_TO_BAT) ||
     (fault == PRES_OC_OR_STB))
  {
    Motp_NewMotorState(MOTP_EVT_STB, motor);
  }
  else
#endif
  {
    /* Manage pending request */
    if (Motp_PrivateData[motor].command != MOTP_REQ_STOP)
    {
      switch (Motp_PrivateData[motor].command)
      {
        case MOTP_REQ_MOVE_UP_FW:
        case MOTP_REQ_MOVE_DW_BW:

          cmdArrayHdl = MOTP_CfgTable[motor].CMD_ARRAY_HDL;

          /* Check if cmdArray resource is free or is already assigned to this "motor".  */
          if ((Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl == MOTP_MAX_HDL) ||
              (Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl == motor))
          {
            /* Lock cmdArray Resource */
            Motp_CmdArrayPrivateData[cmdArrayHdl].motpHdl = motor;

            if (Motp_PrivateData[motor].command == MOTP_REQ_MOVE_UP_FW)
            {
              Motp_NewMotorState(MOTP_EVT_START_UP_FW, motor);
            }
            else
            {
              Motp_NewMotorState(MOTP_EVT_START_DW_BW, motor);
            }
          }
          break;

        default:
          /* NOP */
          break;
      }
    }
  }
}

static void Motp_MovementDuring(MOTP_Handle_t motor)
{  
  /* Check exit condition */
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
  switch (Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].validatedFault)
  {
    case PRES_SHORT_TO_BAT:
    case PRES_OC_OR_STB:
      Motp_NewMotorState(MOTP_EVT_STB, motor);
      break;
    case PRES_SHORT_TO_GND:
    case PRES_OC_OR_STG:
    case PRES_OVER_VOLTAGE:
      Motp_NewMotorState(MOTP_EVT_STG, motor);
      break;
    default:
#endif
      if(Motp_PrivateData[motor].checkPos == TRUE)
      {
        /* Eseguire la diagnosi sul fbk di posizione solo se non ci sono fault sui comandi.
         * In questo modo non è necessario avere una validazione del fault comandi
         * più rapida di quella del fault IPOC  */
        
        if ((MOTP_POS_DIAG_CONDITION) && ((Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].lastFault == PRES_NO_FAULT) ||
            (Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].lastFault == PRES_NOT_TESTED)))
        {
          /* Strokes monitoring */
          Motp_PosFbkDiag(motor);
        }
        else
        {}
      }
      else
      {
        /* Check for diagnosis invalidation */
        Motp_PosFbkInvalidDiag(motor);
      }
      
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
      break;
  }
#endif
  MOTP_MOVING_EVT(motor, Motp_PrivateData[motor].command)
    
}

static void Motp_BrakeDuring(MOTP_Handle_t motor)
{
  /* Manage brake strategy */
#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
  PRES_Fault_t fault;

  fault = Motp_CmdArrayPrivateData[MOTP_CfgTable[motor].CMD_ARRAY_HDL].validatedFault;

  if((fault == PRES_SHORT_TO_GND) ||
     (fault == PRES_OC_OR_STG))
  {
    Motp_NewMotorState(MOTP_EVT_STG, motor);
  }
  else
#endif
  {
    if(Motp_PrivateData[motor].brakeTime == 0U)
    {
      Motp_NewMotorState(MOTP_EVT_IDLE, motor);
    }
    else
    {
      Motp_PrivateData[motor].brakeTime -= MOTP_TICK_MS;
    }
  }
}

#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
static void Motp_RecIdleDuring(MOTP_Handle_t motor)
{
  /* Wait cmd transition */
}

static void Motp_RecBrakeDuring(MOTP_Handle_t motor)
{
  /* Wait cmd transition */
}
#endif

/*************************************************
 * Output driver management
 *
 * Motp_SetCmdArrayState
 *
 ************************************************/
static void Motp_SetCmdArrayState(MOTP_CmdArrayHdl_t cmdArray, Motp_intCommand_t intCmd)
{
  MOTP_Handle_t currentHdl;
  uint8_t i;

  currentHdl = Motp_CmdArrayPrivateData[cmdArray].motpHdl;

  for (i = 0U; i < MOTP_NUM_CMD; i++)
  {
    if((MOTP_MovTable[currentHdl][intCmd][i] != S_PREVIOUS) && (MOTP_CmdArrayTable[cmdArray].CMD_HDL[i] != MOTP_CMD_NOT_USED))
    {
      /* Call the SetState function for each cmd object */
      MOTP_CmdArrayTable[cmdArray].STATE_FUN_PTR(MOTP_CmdArrayTable[cmdArray].CMD_HDL[i],
                                                 MOTP_MovTable[currentHdl][intCmd][i]);
    }
    else
    {
    }
  }
}

/**
 * Periodic diagnosis of position feedback signal
 *
 */
static void Motp_PosFbkDiag(MOTP_Handle_t motor)
{
  int16_t newPosition;

  newPosition = IPOC_GetPosition(MOTP_CfgTable[motor].POS_FBK_HDL);

  /* Compare the current position with the previous one */
  if (newPosition == Motp_PrivateData[motor].prevPosition)
  {
    /* Stall detected */
    if (Motp_PrivateData[motor].stallTime < MOTP_CfgTable[motor].FBK_POS_DIAG_TIME)
    {
      /* Validating stall */
      Motp_PrivateData[motor].stallTime += MOTP_TICK_MS;
    }
    else
    {
      /* Stall validated */
      if (Motp_PrivateData[motor].stallTime == MOTP_CfgTable[motor].FBK_POS_DIAG_TIME)
      {
        Motp_PrivateData[motor].stallTime++;

        if (Motp_PrivateData[motor].posFbkFault != MOTP_FBK_FAULT)
        {
          if (Motp_PrivateData[motor].machineState == MOTP_STATE_UP_FW)
          {
            IPOC_SetStallStatus(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_STALL_UP_FW);

            if(Motp_PrivateData[motor].posFbkFault == MOTP_DW_BW_STALL)
            {
              Motp_PrivateData[motor].posFbkFault = MOTP_FBK_FAULT;
              Motp_PosFbkFaultRecovery(motor);
            }
            else
            {
              Motp_PrivateData[motor].posFbkFault = MOTP_UP_FW_STALL;
              Motp_UpFwStrokeDetected(motor);
            }
          }
          else /* machineState = MOTP_STATE_DW_BW */
          {
            IPOC_SetStallStatus(MOTP_CfgTable[motor].POS_FBK_HDL, IPOC_STALL_DOWN_BW);

            if(Motp_PrivateData[motor].posFbkFault == MOTP_UP_FW_STALL)
            {
              Motp_PrivateData[motor].posFbkFault = MOTP_FBK_FAULT;
              Motp_PosFbkFaultRecovery(motor);
            }
            else
            {
              Motp_PrivateData[motor].posFbkFault = MOTP_DW_BW_STALL;
              Motp_DwBwStrokeDetected(motor);
            }
          }
        }
        else
        {
          /* Stall already validated */
        }
      }
      else
      {
        /* Fault was already validated */
      }
    }
  }
  else
  {
    /* Update previous position */
    Motp_PrivateData[motor].stallTime = 0u;
    Motp_PrivateData[motor].prevPosition = newPosition;

    if (Motp_PrivateData[motor].posFbkFault != MOTP_FBK_NO_FAULT)
    {
      /* Invalidate position fail */
      Motp_PrivateData[motor].stallTime    = 0u;
      Motp_PrivateData[motor].posFbkFault = MOTP_FBK_NO_FAULT;
    }
    else
    {
    }
  }
}

/**
 * Strategy to recongnize the return of IPOC pulses.
 *
 * Motp_PosFbkInvalidDiag(MOTP_Handle_t motor)
 *
 */
static void Motp_PosFbkInvalidDiag(MOTP_Handle_t motor)
{
  int16_t newPosition;

  newPosition = IPOC_GetPosition(MOTP_CfgTable[motor].POS_FBK_HDL);

  /* Compare the current position with the previous one */
  if (Motp_PrivateData[motor].machineState == MOTP_STATE_UP_FW)
  {
    if (newPosition > (Motp_PrivateData[motor].prevPosition + MOTP_INVALID_POS_FBK_DIAG_STEP))
    {
      /* Invalidate position fail */
      Motp_PrivateData[motor].stallTime    = 0u;
      Motp_PrivateData[motor].posFbkFault  = MOTP_FBK_NO_FAULT;
      Motp_PrivateData[motor].checkPos     = TRUE;
    }
    else
    {}
  }
  else
  {
    if (newPosition < (Motp_PrivateData[motor].prevPosition - MOTP_INVALID_POS_FBK_DIAG_STEP))
    {
      /* Invalidate position fail */
      Motp_PrivateData[motor].stallTime    = 0u;
      Motp_PrivateData[motor].posFbkFault  = MOTP_FBK_NO_FAULT;
      Motp_PrivateData[motor].checkPos     = TRUE;
    }
    else
    {}
  }
}

/**
 * Recovery strategy in case of position feedback fault
 *
 * Motp_PosFbkFaultRecovery(MOTP_Handle_t motor)
 *
 */
static void Motp_PosFbkFaultRecovery(MOTP_Handle_t motor)
{
  MOTP_POS_FAIL_EVT(motor)

  Motp_PrivateData[motor].motorSts = MOTP_STS_FAIL;
  Motp_PrivateData[motor].checkPos = FALSE;
}

/**
 * Stroke management
 *
 * Motp_UpFwStrokeDetected(MOTP_Handle_t motor)
 *
 */
static void Motp_UpFwStrokeDetected(MOTP_Handle_t motor)
{
  Motp_PrivateData[motor].motorSts = MOTP_STS_STROKE_UP_FW;
  MOTP_STROKE_EVT(motor)
}

/**
 * Stroke management
 *
 * Motp_DwBwStrokeDetected(MOTP_Handle_t motor)
 *
 */
static void Motp_DwBwStrokeDetected(MOTP_Handle_t motor)
{
  Motp_PrivateData[motor].motorSts = MOTP_STS_STROKE_DW_BW;
  MOTP_STROKE_EVT(motor)
}

/**
 * Motor movement state machine management
 *
 */
static void Motp_NewMotorState(Motp_cmdEvent_t event, MOTP_Handle_t motor)
{
  Motp_state_t tmp;

  tmp = MOTP_MotorMoveSM[event][Motp_PrivateData[motor].machineState];

  // check if there is a new state and the transition can be executed
  if ((Motp_PrivateData[motor].machineState != tmp) && (Motp_FreezeSts == FALSE))
  {
    /* Execute state "exit" transition */
    if (Motp_MotMoveTransSM[MOTP_TRANSITION_EXIT][Motp_PrivateData[motor].machineState] != NULL)
    {
      Motp_MotMoveTransSM[MOTP_TRANSITION_EXIT][Motp_PrivateData[motor].machineState](motor);
    }
    else
    {
    }

    /* Execute state "entry" transition */
    if (Motp_MotMoveTransSM[MOTP_TRANSITION_ENTRY][tmp] != NULL)
    {
      Motp_MotMoveTransSM[MOTP_TRANSITION_ENTRY][tmp](motor);
    }
    else
    {
    }

    Motp_PrivateData[motor].machineState = tmp;
  }
  else
  {
  }
}

void MOTP_StopRecovery(void)
{
  MOTP_Handle_t mot;

  /* remove eventually present recovery */
  for(mot = (MOTP_Handle_t)0u; mot < MOTP_MAX_HDL; mot++)
  {
    if((Motp_PrivateData[mot].machineState ==   MOTP_STATE_REC_IDLE) ||
        (Motp_PrivateData[mot].machineState ==   MOTP_STATE_REC_BRAKE))
    {
      Motp_CmdArrayPrivateData[MOTP_CfgTable[mot].CMD_ARRAY_HDL].validatedFault = PRES_NOT_TESTED;
      Motp_NewMotorState(MOTP_EVT_IDLE, mot);
    }
  }
}

/**
 * @brief API to initialize MOTP hall position fail (ie: stored in EEPROM), 
 * called tipically at startup
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in] u08 the motor with position feedback in fail (ie: stored in EEPROM)
 * @param [out] none
 * @return None
 */
DRVD_RStatus_t MOTP_SetFault(u08 motor, PRES_Fault_t Fault)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (motor < MOTP_MAX_HDL)
  {
    Motp_PrivateData[motor].posFbkFault = MOTP_FBK_FAULT;
    Motp_PrivateData[motor].stallTime   = MOTP_CfgTable[motor].FBK_POS_DIAG_TIME;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

/**
 * @brief API to set the position feedback channel of a motor in stall, called for example when
 * setting a new position after reaching a stroke
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in] u08 the motor with position feedback in stall
 * @param [out] none
 * @return None
 */
DRVD_RStatus_t MOTP_SetStall(u08 motor, MOTP_PosFkbDiag_t stall)
{
  DRVD_RStatus_t valueReturn = MS_OK;

  if (motor < MOTP_MAX_HDL)
  {
    Motp_PrivateData[motor].posFbkFault = stall;
    Motp_PrivateData[motor].stallTime   = MOTP_CfgTable[motor].FBK_POS_DIAG_TIME;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

#endif  /* __MOTP_IS_PRESENT__ */
