/**
 * @file LPMS.c
 * @brief Low Power Management System: source code of LPM module for system layer. 
 * Its finite state machine (FSM) manages the following four states:
 * @li LPMS_POWER_OFF: power off state
 * @li LPMS_RUN: run state
 * @li LPMS_LOW_POWER: low power (sleep) state
 * @li LPMS_PSEUDO_RUN: pseudo run state
 * </ul>
 *
 * For more details about the state and its transition see the enum structures 
 * LPMS_FsmState_t and LPMS_Event_t.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @date 28 august 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 28/08/2014 0.1  CC      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define LPMS_IF_OWNER

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "LPMS.h"
#include "LPMS_config.h"
/* Exception for Low Power Module */
#include "TASK_if.h"

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

static LPMS_FsmState_t Lpms_FsmState;
static LPMS_FsmState_t Lpms_NewFsmState;
static LPMS_Event_t    Lpms_Event;

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/

/** Routine prototypes to manage the power management transition */
static void Lpms_PowerOffEvtMgr(void);
static void Lpms_RunEvtMgr(void);
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  static void Lpms_LowPowerEvtMgr(void);
#endif
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
  static void Lpms_PseudoRunEvtMgr(void);
#endif


/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/**
 * @brief Initialization routine for Power management system module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_Init(void)
{
  /* Set the INIT event for transition POWER_OFF --> RUN */
  Lpms_Event = LPMS_NO_EVENT;
  LPMS_EventStatus_t EvtSts = LPMS_SetEvent(LPMS_PSEUDO_INIT);
  
  if( EvtSts == LPMS_OK )
  {
    /* Init state variables */
    Lpms_FsmState    = LPMS_POWER_OFF;
    Lpms_NewFsmState = LPMS_POWER_OFF;
    
    /* First call for System initialization */
    LPMS_FsmManager();
    
    /* Refresh all watchdog */
    LPMS_RefreshAllWatchDog()
  }
  else
  {
    /* Generate un HW reset due to a power management state wrong setting */
    LPMS_HwReset();
  }
}

/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.1 of the relative hw datasheet version 2.0. The sw trigger is given
 * when the routine is called with the parameter Enable to TRUE and the ADC
 * conversion start. It is stopped only when the routine is called with the
 * parameter Enable to FALSE (sequenzial mode behaviour). The conversion is
 * done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_SEQUENTIAL_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] Enable: flag for start/stop conversion. With TRUE start the
 * sequenzial conversion and with FALSE the conversion is stopped
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return CTRL_ResSts_t
 * @retval CTRL_OK The ADC channel selected is correct
 * @retval CTRL_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval CTRL_NOT_OK The ADC channel selected cannot used with current configuration
 */
void LPMS_FsmManager(void)
{
  /* Update the current state with the new setted */
  if( Lpms_NewFsmState != Lpms_FsmState )
  {
    Lpms_FsmState = Lpms_NewFsmState;
  }
  
  switch(Lpms_FsmState)
  {
    case LPMS_POWER_OFF:
      /* Manage the transition events of Power Off state */
      Lpms_PowerOffEvtMgr();
      break;

    case LPMS_RUN:
      /* Manage the transition events of Run state */
      Lpms_RunEvtMgr();
      break;

#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
    case LPMS_LOW_POWER:
      /* Manage the Low Power strategy */
      LPMS_LowPowerManager();
      /* Manage the transition events of Low Power state */
      Lpms_LowPowerEvtMgr();
      break;
#endif /* end LPMS_LOW_POWER_STATE */

#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
    case LPMS_PSEUDO_RUN:
      /* Manage the transition events of Pseudo Run state */
      Lpms_PseudoRunEvtMgr();
      break;
#endif /* end LPMS_PSEUDO_RUN_STATE */
      
    default:
      break;
  }
}

/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.1 of the relative hw datasheet version 2.0. The sw trigger is given
 * when the routine is called with the parameter Enable to TRUE and the ADC
 * conversion start. It is stopped only when the routine is called with the
 * parameter Enable to FALSE (sequenzial mode behaviour). The conversion is
 * done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_SEQUENTIAL_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] Enable: flag for start/stop conversion. With TRUE start the
 * sequenzial conversion and with FALSE the conversion is stopped
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return CTRL_ResSts_t
 * @retval CTRL_OK The ADC channel selected is correct
 * @retval CTRL_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval CTRL_NOT_OK The ADC channel selected cannot used with current configuration
 */
LPMS_EventStatus_t LPMS_SetEvent(LPMS_Event_t EventReq)
{
  LPMS_EventStatus_t EvtSts = LPMS_OK;
  
  if( EventReq >= LPMS_NO_EVENT )
  {
    EvtSts = LPMS_WRONG_PARAM;
  }
  else
  {
    if( Lpms_Event != LPMS_NO_EVENT )
    {
      EvtSts = LPMS_BUSY;
    }
    else
    {
      switch(EventReq)
      {
        case LPMS_INIT:
        case LPMS_PWR_OFF:
        case LPMS_NO_EVENT:
          Lpms_Event = EventReq;
          break;
 
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
        case LPMS_PSEUDO_INIT:
          if( Lpms_FsmState == LPMS_POWER_OFF )
          {
            Lpms_Event = EventReq;
          }
          else
          {
            EvtSts = LPMS_NOT_POSSIBLE;
          }
          break;
#endif
        
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
        case LPMS_PR_PSEUDO_WAKEUP:
          if( Lpms_FsmState == LPMS_PSEUDO_RUN )
          {
            Lpms_Event = EventReq;
          }
          else
          {
            EvtSts = LPMS_NOT_POSSIBLE;
          }
          break;
#endif
      
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
        case LPMS_SLEEP:
          if( (Lpms_FsmState == LPMS_PSEUDO_RUN) ||
              (Lpms_FsmState == LPMS_RUN)        )
          {
            Lpms_Event = EventReq;
          }
          else
          {
            EvtSts = LPMS_NOT_POSSIBLE;
          }
          break;
#endif

#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
        case LPMS_WAKEUP:
          if( Lpms_FsmState == LPMS_LOW_POWER )
          {
            Lpms_Event = EventReq;
          }
          else
          {
            EvtSts = LPMS_NOT_POSSIBLE;
          }
          break;
#endif

#if (LPMS_FSM_SUBSET == LPMS_FULL_FSM_SUBSET)
        case LPMS_LP_PSEUDO_WAKEUP:
          if( Lpms_FsmState == LPMS_LOW_POWER )
          {
            Lpms_Event = EventReq;
          }
          else
          {
            EvtSts = LPMS_NOT_POSSIBLE;
          }
          break;
#endif

        default:
          break;
      }
    }
  }

  return(EvtSts);
}


LPMS_FsmState_t LPMS_GetFsmState(void)
{
  return(Lpms_FsmState);
}

/**
  * Ruotine to actuate the HW reset
  */
void LPMS_HwReset(void)
{
  DI();
  while(1)
  {
    NOP();
  }
}


/*_____ L O C A L - F U N C T I O N S ________________________________________*/

static void Lpms_PowerOffEvtMgr(void)
{
  /* INIT event - transition POWER_OFF --> RUN */
  if( Lpms_Event == LPMS_INIT )
  {
    /* Call Configuration init routine */
    LPMS_InitEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_RUN;
  }
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
  /* LPMS_PSEUDO_INIT event - transition POWER_OFF --> PSEUDO_RUN */
  else if( Lpms_Event == LPMS_PSEUDO_INIT )
  {
    /* Call Sleep routines of configured modules */
    LPMS_PseudoInitEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_PSEUDO_RUN;
  }
#endif
  /* NO_EVENT - none transition */
  else
  {
    /* no transition */
  }
}

static void Lpms_RunEvtMgr(void)
{
  /* PWR_OFF event - transition RUN --> POWER_OFF */
  if( Lpms_Event == LPMS_PWR_OFF )
  {
    /* Call Power off routines of configured modules */
    LPMS_RunPwrOffEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT; 
    Lpms_NewFsmState = LPMS_POWER_OFF;
  }
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  /* SLEEP event - transition RUN --> LOW_POWER */
  else if( Lpms_Event == LPMS_SLEEP )
  {
    /* Call Sleep routines of configured modules */
    LPMS_SleepEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_LOW_POWER;
  }
#endif
  /* NO_EVENT - none transition */
  else
  {
    /* no transition */
  }
}


#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
static void Lpms_LowPowerEvtMgr(void)
{
  /* WAKEUP event - transition LOW_POWER --> RUN */
  if( Lpms_Event == LPMS_WAKEUP )
  {
    /* Call Wakeup routines of configured modules */
    LPMS_WakeupEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_RUN;
  }
#if (LPMS_FSM_SUBSET == LPMS_FULL_FSM_SUBSET)
  /* LP_PSEUDO_WAKEUP event - transition LOW_POWER --> PSEUDO_RUN */
  else if( Lpms_Event == LPMS_LP_PSEUDO_WAKEUP )
  {
    /* Call LowPower Pseudo Wakeup routines of configured modules */
    LPMS_LpPseudoWakeupEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT; 
    Lpms_NewFsmState = LPMS_PSEUDO_RUN;
  }
#endif
  /* NO_EVENT - none transition */
  else
  {
    /* no transition */
  }
}
#endif /* end LPMS_LOW_POWER_STATE */


#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
static void Lpms_PseudoRunEvtMgr(void)
{
  /* RUN_PSEUDO_WAKEUP event - transition PSEUDO_RUN --> RUN */
  if( Lpms_Event == LPMS_PR_PSEUDO_WAKEUP )
  {
    /* Call Pr Pseudo Wakeup routines of configured modules */
    LPMS_PrPseudoWakeupEvtCbk();

    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_RUN;
  }
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  /* SLEEP event - transition PSEUDO_RUN --> LOW_POWER */
  else if( Lpms_Event == LPMS_SLEEP )
  {
    /* Call Sleep routines of configured modules */
    LPMS_SleepEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_LOW_POWER;
  }
#endif
  /* PWR_OFF event - transition PSEUDO_RUN --> POWER_OFF */
  else if( Lpms_Event == LPMS_PWR_OFF )
  {
    /* Call Power off routines of configured modules */
    LPMS_PseudoRunPwrOffEvtCbk();
    
    /* Update the new state and clear the current event request */
    Lpms_Event = LPMS_NO_EVENT;
    Lpms_NewFsmState = LPMS_POWER_OFF;
  }
  /* NO_EVENT - none transition */
  else
  {
    /* no transition */
  }
}
#endif /* end LPMS_PSEUDO_RUN_STATE */


/*_____ E N D _____ (LPMS.c) _________________________________________________*/
