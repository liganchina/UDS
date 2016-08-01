/**
 * @file DISPA.c
 * @brief The DISPA module is responsible of:
 *    - Link between function request and function activation
 *    - Function priority and contemporary activation management
 *    - Command priority ( for different command source for the same function)
 *    - Proxi management (enable/disable function depending on EOL configuration)
 *    - UDS IOControl and Routine management (only some routine)
 *    - CAN/LIN functional output signal update ( only functional signal)
 *    - Manage IPOC-MOTP <-> Model Based SW interaction ( for stroke recognition) and initialization
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
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define DISPA_IF_OWNER

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "DISPA.h"
#include "DISPA_config.h"
/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__ 

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/


/*_____ P R I V A T E - T Y P E S ____________________________________________*/
typedef struct DISPA_privateFunctionData_s
{
  u08               current_cmd;   /**< current active command */
  u08               requested_cmd; /**< reuested  command */
  DISPA_State_t     state_wait;    /**< state indication (suspended, aborted, ...) */
  u08               wait_cycle;    /**< Wait cycles*/
  bool              ioc_active;    /**< Indicates if IOcontrol for that handle is active */
} DISPA_privateFunctionData_t;

typedef struct DISPA_privateIoGroupData_s
{
  DISPA_IoState_t  state;         /**< Group io control state */
  u16              timeout;       /**< iocontrol timeout */ 
  DISPA_handle_t   active_handle; /**< Active handle within group (valid only if the group IOControl is active */
}DISPA_privateIoGroupData_t;

/*_____ P R I V A T E - D A T A ______________________________________________*/
/* Private data for DISPA handler */
DISPA_privateFunctionData_t Dispa_privateData[DISPA_HANDLE_MAX];

/* Private data for IOControl group handler */
DISPA_privateIoGroupData_t  Dispa_privateIoGroupData[DISPA_GROUP_MAX];

/* Variable used to mane the contemporary activation of IOControl can be at most DISPA_GROUP_MAX */
static u08 Dispa_MaxContemporaryControl;

/* This variable maintain the current number of active IoControl */
static u08 Dispa_ContemporaryControlActive;

/* variable used for timeut management, see Dispa_XXXX_TIMEOUT macros */
static s16 Dispa_TimerValue;

/* variable that indicates at least one Iocontrol active */
static bool Dispa_IoControlActive;

/* Vriable used to indicated that a self managed IOControl is active, the self managed IOCOntrol means model related IOControl */
static u08  Dispa_ModelIoControlActive;

static const DISPA_State_t Dispa_StateMachine[DISPA_STS_NUM][DISPA_EVT_NUM] = {
/* STATE/INP_EVENT          DISPA_EVT_RUN       DISPA_EVT_SUSPEND   DISPA_EVT_ABORT     DISPA_EVT_DISABLE   DISPA_EVT_ENABLE    DISPA_EVT_WAIT  */
/* DISPA_STS_RUN      */  { DISPA_STS_RUN    ,  DISPA_STS_SUSPEND,  DISPA_STS_ABORT  ,  DISPA_STS_DISABLE,  DISPA_STS_RUN    ,  DISPA_STS_WAIT    },
/* DISPA_STS_SUSPEND  */  { DISPA_STS_RUN    ,  DISPA_STS_SUSPEND,  DISPA_STS_ABORT  ,  DISPA_STS_DISABLE,  DISPA_STS_SUSPEND,  DISPA_STS_SUSPEND },
/* DISPA_STS_ABORT    */  { DISPA_STS_RUN    ,  DISPA_STS_ABORT  ,  DISPA_STS_ABORT  ,  DISPA_STS_DISABLE,  DISPA_STS_ABORT  ,  DISPA_STS_ABORT   },
/* DISPA_STS_DISABLE  */  { DISPA_STS_DISABLE,  DISPA_STS_DISABLE,  DISPA_STS_DISABLE,  DISPA_STS_DISABLE,  DISPA_STS_RUN    ,  DISPA_STS_DISABLE },
/* DISPA_STS_WAIT     */  { DISPA_STS_RUN    ,  DISPA_STS_SUSPEND,  DISPA_STS_ABORT  ,  DISPA_STS_DISABLE,  DISPA_STS_WAIT   ,  DISPA_STS_WAIT    },
};


/*_____ P R I V A T E - M A C R O S __________________________________________*/
/* Macros used to manage IOControl timeout */
#define Dispa_START_TIMEOUT(group,n)     (Dispa_privateIoGroupData[(group)].timeout = (u16)(Dispa_TimerValue + (s16)(n)))
#define Dispa_CLEAR_TIMEOUT(group)       (Dispa_privateIoGroupData[(group)].timeout = (u16)Dispa_TimerValue)
#define Dispa_TIMEOUT_ELAPSED(group)     (u16)(((s16)(Dispa_privateIoGroupData[(group)].timeout)-Dispa_TimerValue)<=0)
#define Dispa_TIMER_TICK()               (Dispa_TimerValue++)

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/
static void Dispa_IoControlInit(void); 
static void Dispa_IoControlMgm(void);
void Dispa_StateMgm(DISPA_handle_t hdl);
static void Dispa_StopGroupInternal(DISPA_IoGroup_t group);
static void Dispa_StartShortTermAdj(DISPA_handle_t hdl, u08 command);
/* Return TRUE if the io control was active, else return FALSE */ 
static bool Dispa_ReturnControl(DISPA_handle_t hdl); 
/* Return TRUE if the io control was active, else return FALSE */ 
static bool Dispa_StopGroupIoControl(DISPA_IoGroup_t group); 
/* Stop all active IOCOntrol */
static void Dispa_StopAllIoControl(void);

/* Following functions manage the internal and external IO control callback in a safe way by checking SELF_IOCONTROL */
static u08  Dispa_CheckIoControlInternal(DISPA_handle_t hdl, u08 cmd);
static void Dispa_StartIoControlInternal(DISPA_handle_t hdl, u08 cmd);
static void Dispa_StopIoControlInternal(DISPA_handle_t hdl);

/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/* Initialization function, fill private table and initialize all module internal variables */
void DISPA_Init(void)
{
  uint16_t i;
  
  for(i = 0u ; i < DISPA_HANDLE_MAX ; i++)
  {
    Dispa_privateData[i].current_cmd   = 0U;
    Dispa_privateData[i].requested_cmd = 0U;
    Dispa_privateData[i].state_wait    = DISPA_STS_RUN;
    Dispa_privateData[i].wait_cycle    = 0U;
    Dispa_privateData[i].ioc_active    = FALSE;
  }
  
  Dispa_IoControlInit();
  
  DISPA_USER_INIT();
}

/* Function to call periodically with fast period (typical 10 ms), call period in ms defined by DISPA_FAST_MGM_TICK_MS
 * This function manage: 
 *   - Update of fast changing model input
 *   - Call the model step function
 *   - Update low level SW according to model output and command requested (fast device)
*/
void DISPA_FastMgm(void)
{
  DISPA_handle_t hdl;
  
  /* Update fast changing model input data */
  DISPA_FAST_MODEL_IN_UPDATE();

  /* Step the model */
  DISPA_MODEL_STEP_CALL()

  /* Calculate commands*/
  DISPA_COMPUTE_COMMAND();
  
  /* Priority calculation, suspend/abort and delay settings */
  DISPA_PRIORITY_CALCULATION();
  
  /* Run the state manager for every DISPA handle */
  for(hdl = (DISPA_handle_t)0u; hdl < DISPA_HANDLE_MAX ; hdl++)
  {
    Dispa_StateMgm(hdl);
  }
}

/* Function to call periodically with slow period (typical 100 ms), call period in ms defined by DISPA_SLOW_MGM_TICK_MS
 * This function manages:
 *   - IO control timeout
 *   - Update of slow changing model input
 *   - Update output can/lin signal 
 */
void DISPA_SlowMgm(void)
{
  /* Update ECU status, CAN signal, internal status */
  DISPA_STATUS_UPDATE();
  
  /* Update slow changing model input data */
  DISPA_SLOW_MODEL_IN_UPDATE();
  
  /* Call the IOControl manager function */
  Dispa_IoControlMgm();
}

/* Function used by a DISPA_Config.c routine to define the priority and order of activation*/ 
void DISPA_SetRequestedCmd(DISPA_handle_t hdl,u08 cmd)
{
    Dispa_privateData[hdl].requested_cmd = cmd;
}

/* Set the wait cycle for function activation delay, this function acts only if the current state is RUN */
void DISPA_SetWaitCycles(DISPA_handle_t hdl,u08 cycles)
{
  Dispa_privateData[hdl].wait_cycle = cycles;
}

u08 DISPA_GetState(DISPA_handle_t hdl)
{
  return Dispa_privateData[hdl].state_wait;
}

/**
 * @brief This function is used to set DISPA state machine of the functions according to the input event.
 * @author Francesco Talarico
 * @param [in] hdl is the function line, evt is the event transition of the state machine
 * @param [out] none
 * @return none
 */
void DISPA_SetEvent(DISPA_handle_t hdl, DISPA_Event_t evt)
{
  Dispa_privateData[hdl].state_wait = Dispa_StateMachine[Dispa_privateData[hdl].state_wait][evt];
}

bool DISPA_isIoControlActive(DISPA_handle_t hdl)
{
  return Dispa_privateData[hdl].ioc_active;
}

/* Return 0 if OK else return the NACK to send to diagnostic client, see UDSA_if.h */
u08 DISPA_SetIoControl(DISPA_handle_t hdl, UDSA_IOControlSubf_t controlType, u08 command)
{
  u08 ret_val; 

  if(Dispa_privateData[hdl].state_wait == DISPA_STS_DISABLE)
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    switch(controlType)
    {
      case RETURN_CONTROL_TO_ECU:
        /* return true only if the IOControl to stop is active */
        if(Dispa_ReturnControl(hdl))
        {
          ret_val = SERVICE_OK;
        }
        else
        {
          ret_val = CONDITIONS_NOT_CORRECT;
        }
        break;

      case SHORT_TERM_ADJUSTMENT:

        /* Primarly Check if the IOControl is allowed according to current number of active control */
        /* if Dispa_MaxContemporaryControl is 1, use FCA strategy ( norma FIAT 09009 par. 4.8):
            the last requested IOControl ovverride the current active IOControl */
        if(Dispa_MaxContemporaryControl == 1u)
        {
          /* chek if the IOControl can be started before stop other active control */
          ret_val = Dispa_CheckIoControlInternal(hdl, command);
          if(ret_val == SERVICE_OK)
          {
            /* stop all active control and try to start the new IOControl */
            Dispa_StopAllIoControl();
            Dispa_StartShortTermAdj(hdl,command);
          }
        }
        else if(Dispa_MaxContemporaryControl > Dispa_ContemporaryControlActive)
        {
          /* check the state of the group to wich the handle belongs:
              Try to start the control only if the group is not active
              or if the requested control is already active */
          if ((Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].state == DISPA_IO_NOT_ACTIVE) ||
              (Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].active_handle == hdl))
          {
            /* chek if the IOControl can be started before stop other active control */
            ret_val = Dispa_CheckIoControlInternal(hdl, command);
            if(ret_val == SERVICE_OK)
            {
              /* stop required io control (for corrrect management of Dispa_ContemporaryControlActive)
               and start the new IOControl */
              Dispa_ReturnControl(hdl); /* This function acts only in case the required IOCOntrol device is already active */
              Dispa_StartShortTermAdj(hdl,command);
            }
          }
          else
          {
            ret_val = CONDITIONS_NOT_CORRECT;
          }
        }
        else
        {
          ret_val = CONDITIONS_NOT_CORRECT;
        }
        break;

      case RESET_TO_DEFAULT: /* Future extension */
      case FREEZE_CURRENT_STATE: /* Future extension */
      default:
        ret_val = REQUEST_OUT_OF_RANGE;
        break;
    }
  }
  return ret_val;
}

/* WARNING: this function stop ALL the already active IOCOntrol only if parameter max 
            is less than current active IOControl number*/
DISPA_EXTERN void DISPA_SetMaxContemporaryIoControl(u08 max)
{
  /* The value to set must be less or equal than the number of group */
  if( max <= DISPA_GROUP_MAX)
  {
    /* if the maximum allowed contemporay control (max) is less than current active IOControl
       stop all active control */
    if(max < Dispa_ContemporaryControlActive)
    {
      Dispa_StopAllIoControl();
    }
    
    /* udpate internal variable */
    Dispa_MaxContemporaryControl = max;
  }
}

/*_____ P R I V A T E - F U N C T I O N S ____________________________________*/

/* Periodic routine that manage IO Control timer and consequential deactivation */
static void Dispa_IoControlMgm(void)
{
  u16 i;
  
  if(Dispa_IoControlActive)
  {
    /*increment counter for timeout management */
    Dispa_TIMER_TICK();
   
    for ( i = 0u ; i < DISPA_GROUP_MAX ; i++)
    {
      /* Check if the group is active */
      if(Dispa_privateIoGroupData[i].state != DISPA_IO_NOT_ACTIVE)
      {
        /* check if the timer is elapsed */
        if(Dispa_TIMEOUT_ELAPSED(i))
        {
          Dispa_StopGroupIoControl((DISPA_IoGroup_t)i);
        }
      }
    }
  }
}

/*Initialization of IOCOntrol related private data */
static void Dispa_IoControlInit(void)
{
  u16 i;
  
  /* Initialize timer value */
  Dispa_TimerValue = 0u;
  
  /* Initialize private tables */
  for(i = 0u; i < DISPA_GROUP_MAX; i++)
  {
    Dispa_privateIoGroupData[i].state = DISPA_IO_NOT_ACTIVE;
    Dispa_privateIoGroupData[i].active_handle = DISPA_HANDLE_MAX;
    Dispa_CLEAR_TIMEOUT(i);
  }
  
  /* set max contemporary control to DISPA_INITIAL_MAX_IO_CONTROL (default session) */
  Dispa_MaxContemporaryControl = DISPA_INITIAL_MAX_IO_CONTROL;
  
  /* no IOControl active */
  Dispa_ContemporaryControlActive = 0u;
  Dispa_IoControlActive = FALSE;
  
  Dispa_ModelIoControlActive = FALSE;
}

/*Start IOControl short term adjustment */
static void Dispa_StartShortTermAdj(DISPA_handle_t hdl, u08 command)
{
  /* call the right callback passing the function handler */
  Dispa_StartIoControlInternal(hdl,command);
  
  /* update group private table data */
  Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].state = DISPA_IO_SHORT_TERM_ADJ;
  Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].active_handle = hdl;
  
  /* start group timeout */
  Dispa_START_TIMEOUT(DISPA_FunctionCfgTable[hdl].GROUP, DISPA_FunctionCfgTable[hdl].IOC_TIMER);
  
  /* Increment the cpounter of current active IOControl */
  Dispa_ContemporaryControlActive++;
  
  Dispa_IoControlActive = TRUE; /* to activate DISPA_Mgm operation */
}

/* Private function for stop IOControl and update private data values */
static void Dispa_StopGroupInternal(DISPA_IoGroup_t group)
{
  
  Dispa_StopIoControlInternal(Dispa_privateIoGroupData[group].active_handle);
  
  /* this function is called only if the IoControl to stop is active */
  Dispa_privateIoGroupData[group].state = DISPA_IO_NOT_ACTIVE;
  Dispa_privateIoGroupData[group].active_handle = DISPA_HANDLE_MAX;
  Dispa_CLEAR_TIMEOUT(group);
  
  /* decrement the counter of current active IOControl */
  Dispa_ContemporaryControlActive--;
  
  if(Dispa_ContemporaryControlActive == 0U)
  {
    /* all IO Control are stopped */
    Dispa_IoControlActive = FALSE; /* to inhibit DISPA_Mgm operation */
  }
}

/* Stop all active IOCOntrol */
static void Dispa_StopAllIoControl(void)
{
  u16 i;
   
  for ( i = 0u ; i < DISPA_GROUP_MAX ; i++)
  {
    Dispa_StopGroupIoControl((DISPA_IoGroup_t)i);
  }
}


/** Function called to return from active IOControl, check if the hdl IOCOntrol is active and stop it
 *  Return TRUE if the io control was active, else return FALSE
 */
static bool Dispa_ReturnControl(DISPA_handle_t hdl)
{
  bool ret_val;
  /* check if the related group is active and if the actve IO cotrol 
     within the group is the one that is requested to stop */
  if((Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].state != DISPA_IO_NOT_ACTIVE) &&
      (Dispa_privateIoGroupData[DISPA_FunctionCfgTable[hdl].GROUP].active_handle == hdl))
  {
    Dispa_StopGroupInternal(DISPA_FunctionCfgTable[hdl].GROUP);
    ret_val = TRUE;
  }
  else
  {
    ret_val = FALSE;
  }
  
  return ret_val;
}

/** Fucntion used to stop Group IOCOntrol despite current active control within the group,
 *  Check if the group IOControl is active and stop it 
 * Return TRUE if the group io control was active, else return FALSE
 */
static bool Dispa_StopGroupIoControl(DISPA_IoGroup_t group) 
{
  bool ret_val;
  
  if(Dispa_privateIoGroupData[group].state != DISPA_IO_NOT_ACTIVE)
  {
    Dispa_StopGroupInternal(group);
    ret_val = TRUE;
  }
  else
  {
    ret_val = FALSE;
  }
  
  return ret_val;
}

/* Private function for check IOControl and update private data values */
static u08 Dispa_CheckIoControlInternal(DISPA_handle_t hdl, u08 cmd)
{
  u08 ret_val;
  
  /* Check if the IOCOntrol required is managed directly by DISPA or by external module */
  if(DISPA_FunctionCfgTable[hdl].SELF_IOCONTROL == TRUE)
  {
    /* Call DISPA function for Check IoControl */
    ret_val = DISPA_SelfCheckIoControl(hdl, cmd);
  }
  else
  {
    /* IOControl manged by external module */
    if(DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].CheckIoCallback != NULL)
    {
      /* call the right callback passing the function handler */
      ret_val = DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].CheckIoCallback(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, cmd);
    }
    else
    {
      /* if the check callback is null means that the iocontrol is always available */
      ret_val = SERVICE_OK;
    }
  }
  
  return ret_val;
}

/** Private function for start IOControl and update private data values,
 * This function is called after Dispa_CheckIoControlInternal and is 
 * executed if the conditions to start IOCtntrol are met ( return from Dispa_CheckIoControlInternal == SERVICE_OK)
 */
static void Dispa_StartIoControlInternal(DISPA_handle_t hdl, u08 cmd)
{
  Dispa_privateData[hdl].ioc_active = TRUE;
  
  if(DISPA_FunctionCfgTable[hdl].SELF_IOCONTROL == TRUE)
  {
    /* Call DISPA function for start IoControl */
    DISPA_SelfStartIoControl(hdl, cmd);
    Dispa_ModelIoControlActive++;
    
  }
  else
  {
    /* call the right callback passing the function handler */
    DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].StartIoCallback(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, cmd);
  }
  
  /* If the IOControl is not internally managed set the current command to IOControlled 
     command in order to re-execute requested command when the IOControl ends */
  if(DISPA_FunctionCfgTable[hdl].SELF_IOCONTROL == FALSE)
  {
    Dispa_privateData[hdl].current_cmd = cmd;
  }
  
}

/** Private function for stop IOControl and update private data values */
static void Dispa_StopIoControlInternal(DISPA_handle_t hdl)
{
  Dispa_privateData[hdl].ioc_active = FALSE;
  
  if(DISPA_FunctionCfgTable[hdl].SELF_IOCONTROL == TRUE)
  {
    /* Call DISPA function for stop IoControl */
    DISPA_SelfStopIoControl(hdl);
    Dispa_ModelIoControlActive--;
  }
  else
  {
    /* call the right callback passing the function handler */
    DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].StopIoCallback(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE);
  }
  
}

/* Return TRUE if at least one self managed IOCOntrol is active, else return FALSE */
DISPA_EXTERN bool DISPA_isModelIoControlActive(void)
{
  bool ret_val;
  
  if(Dispa_ModelIoControlActive > 0U)
  {
    ret_val = TRUE;
  }
  else
  {
    ret_val = FALSE;
  }
  return ret_val;
}

/* This function implements the DISPA handler state machine */
void Dispa_StateMgm(DISPA_handle_t hdl)
{
  
  switch(Dispa_privateData[hdl].state_wait)
  {
    case  DISPA_STS_DISABLE:
    case  DISPA_STS_SUSPEND:
      /* Set IDLE command and update current command consequentially (current command = IDLE)
         so when the handle turn back to RUN state again the requested command (if != IDLE) is executed */
      if(DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].SetCmd(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].SuspCommand) == (u08)PRES_OK)
      {
        Dispa_privateData[hdl].current_cmd = DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].SuspCommand;
      }
      break;
    case DISPA_STS_ABORT:
      /* set IDLE command and update current command to requested command so when 
         the handle turn back to RUN state again the requested command (if != IDLE) is not executed 
         until the requested command is different from the command present during aborted state */
      if(DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].SetCmd(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].IdleCommand) == (u08)PRES_OK)
      {
        Dispa_privateData[hdl].current_cmd =  Dispa_privateData[hdl].requested_cmd;
      }
      break;
    case DISPA_STS_RUN:
      /* Normal state, execute command if the requested command is different from current command and if the IOCOntrol is not active
         or if the IOControl is active but self managed */
      if((DISPA_FunctionCfgTable[hdl].SELF_IOCONTROL == TRUE) || (Dispa_privateData[hdl].ioc_active == FALSE))
      {
        if(Dispa_privateData[hdl].current_cmd !=  Dispa_privateData[hdl].requested_cmd)
        {
          if(DISPA_ModuleCfgTable[DISPA_FunctionCfgTable[hdl].MODULE].SetCmd(DISPA_FunctionCfgTable[hdl].FUNCTION_HANDLE, Dispa_privateData[hdl].requested_cmd) == (u08)PRES_OK)
          {
            /*Update current command if the set command call is ended successfully */
            Dispa_privateData[hdl].current_cmd =  Dispa_privateData[hdl].requested_cmd;
          }
        }
      }
      break;
    case DISPA_STS_WAIT:
      /* WAIT state, decrement state_wait private value */
      Dispa_privateData[hdl].wait_cycle--;
      if(Dispa_privateData[hdl].wait_cycle == 0U)
      {
        DISPA_SetEvent(hdl, DISPA_EVT_RUN);
      }
      break;
    default:
      break;
  }
}

#endif
/*______ E N D _____ (DISPA.c) ________________________________________________*/


