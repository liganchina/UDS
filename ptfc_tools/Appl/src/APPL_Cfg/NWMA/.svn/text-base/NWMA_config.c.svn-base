/**
 * @file NWMA_config.c
 * @brief NetWork Management - Application layer. In this configuration file 
 * there is the source code for network management FCA for NextGen network. 
 * The reference standard is N07320_ed5.
 * @n The main contents are:
 * @li ECU type coding to select the correct NWM message in case of multi DBC
 * @li Master and slave NWM message adaptment to generic signal used in NWMA core
 * </ul>
 *
 * @version 0.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 2 february 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| GB           Giuseppe Barberio         Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 02 feb 15  0.1  CC      First official release (whithout DLL error FSM)
| 28 may 15  0.2  GB CC   DLL error FSM completed
|-----------------------------------------------------------------------------
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "NWMA.h"
#include "NWMA_config.h"

/* Module inhibition filter */
#ifdef __NWMA_IS_PRESENT__

/*______ L O C A L - D E F I N E _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/** Info on slave NWM message to use according to multi DBC */
CAND_TxMsgName_t NWMA_MsmNwmType;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief Configuration routine to initialize the configurable info
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_InitCfg(void)
{
  /* Init NWM message of NAG/NAP ECUs for specific DBC generation */
  NWM_HMSM.bit.Zero_byte_HMSM       = CMMD_FIXED;                      /* 0 = FIXED, */
  NWM_HMSM.bit.SystemStatus_HMSM    = CMMD_STS_WAKE_UP;                /* 0 = WAKE_UP,1 = NOT_USED,2 = STAYACTIVE,3 = NOT_USED, */
  NWM_HMSM.bit.ActiveLoadSlave_HMSM = CMMD_NO_ACTIVE_LOADS_IN_SLAVE;   /* 0 = NO_ACTIVE_LOADS_IN_SLAVE,1 = ACTIVE_LOADS_IN_SLAVE, */
  NWM_HMSM.bit.EOL_HMSM             = CMMD_EOL_PROGRAMMING;            /* 0 = NO_EOL_PROGRAMMING,1 = EOL_PROGRAMMING, */
  NWM_HMSM.bit.GenericFailSts_HMSM  = CMMD_NO_FUNCTIONALFAILPRESENT;   /* 0 = CMMD_NO_FUNCTIONALFAILPRESENT,1 = CMMD_FUNCTIONALFAILPRESENT, */
  NWM_HMSM.bit.CurrentFailSts_HMSM  = CMMD_NO_FAIL_PRESENT;            /* 0 = NO_FAIL_PRESENT,1 = FAIL_PRESENT, */
  NWM_HMSM.bit.D_ES_HMSM            = CMMD_ERROR_ACTIVE_STATE;         /* 0 = ERROR_ACTIVE_STATE,1 = ERROR_PASSIVE_WARNING_STATE,2 = BUS_OFF_STATE,3 = NOT_USED, */
}

/**
 * @brief Check the SysSts signal receiving from master NWM message and
 * code specific value to generic value
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] NwmStsToCheck: SysSts signal of master NWM message to check.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: check if present a wakeup request
 * @li NWMA_NWM_SYS_STAY_ACTIVE: check if present a stay active request
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: check if present a go to sleep request
 * </ul>
 * @param [out] None
 * @return bool_t
 * @retval FALSE if the SysSts value to check isn't present
 * @retval TRUE if the SysSts valuen to check is present
 */
bool_t NWMA_CheckMasterNwmSysSts(NWMA_NwmSysSts_t NwmStsToCheck)
{
  bool_t CheckSts = FALSE;
  /* To configure according to DBC definition */
  SystemCommand_t MsgSts = (SystemCommand_t)NWM_BCM.bit.SystemCommand;

  /* Select the SysSts value to check */
  switch(NwmStsToCheck)
  {
    case NWMA_NWM_SYS_WAKEUP:
      if( (NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] == TRUE) &&
          /* To configure according to DBC definition */
          (MsgSts == CMMD_CMD_WAKE_UP) )
      {
        NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] = FALSE;
        CheckSts = TRUE;
      }
      break;
      
    case NWMA_NWM_SYS_STAY_ACTIVE:
      if( (NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] == TRUE) &&
          /* To configure according to DBC definition */
          (MsgSts == CMMD_CMD_STAYACTIVE) )
      {
        NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] = FALSE;
        CheckSts = TRUE;
      }
      break;
      
    case NWMA_NWM_SYS_GO_TO_SLEEP:
      if( (NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] == TRUE) &&
          /* To configure according to DBC definition */
          (MsgSts == CMMD_CMD_SLEEP) )
      {
        NWMA_NwmReceived[NWMA_FSM_MGMT_REQ] = FALSE;
        CheckSts = TRUE;
      }
      break;
      
    default:
      break;
  }

  return(CheckSts);
}

/**
 * @brief Check if master NWM message is received
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @li TRUE: NWM message received
 * @li FALSE: NWM message not received
 * </ul>
 * @param [out] None
 * @return bool_t
 * @retval TRUE if NWM message is received
 * @retval FALSE if NWM message is not received
 */
bool_t NWMA_CheckMasterNwmReceived(void)
{
  bool_t CheckSts = NWMA_NwmReceived[NWMA_DLL_ERROR_MGMT];
  
  return(CheckSts);
}

/**
 * @brief Set the value for SysSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] SlaveNwmSts: SysSts signal of slave NWM message to set.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: set a wakeup status
 * @li NWMA_NWM_SYS_STAY_ACTIVE: set a stay active status
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: set a go to sleep status
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetSlaveNwmSysSts(NWMA_NwmSysSts_t SlaveNwmSts)
{
  /* Slave NWM message to configure according to specific DBC */
  switch(SlaveNwmSts)
  {
    case NWMA_NWM_SYS_WAKEUP:
      NWM_HMSM.bit.SystemStatus_HMSM = CMMD_STS_WAKE_UP;
      break;
      
    case NWMA_NWM_SYS_STAY_ACTIVE:
      NWM_HMSM.bit.SystemStatus_HMSM = CMMD_STS_STAYACTIVE;
      break;
      
    default:
      break;
  }
}

/**
 * @brief Get the value for SysSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_NwmSysSts_t
 * @retval NWMA_NWM_SYS_WAKEUP: return a wakeup status
 * @retval NWMA_NWM_SYS_STAY_ACTIVE: return a stay active status
 * @retval NWMA_NWM_SYS_GO_TO_SLEEP: return a go to sleep status
 */
NWMA_NwmSysSts_t NWMA_GetSlaveNwmSysSts(void)
{
  NWMA_NwmSysSts_t NwmSlaveSysSts;
  
  /* Slave NWM message to configure according to specific DBC */
  switch(NWM_HMSM.bit.SystemStatus_HMSM)
  {
  case CMMD_STS_WAKE_UP:
      NwmSlaveSysSts = NWMA_NWM_SYS_WAKEUP;
      break;
      
  case CMMD_STS_STAYACTIVE:
      NwmSlaveSysSts = NWMA_NWM_SYS_STAY_ACTIVE;
      break;

    default:
      NwmSlaveSysSts = NWMA_NWM_SYS_NOT_DEFINED;
      break;
  }
  
  return(NwmSlaveSysSts);
}

/**
 * @brief Set the value for ActiveLoad signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] ActiveLoad: ActiveLoad signal of slave NWM message to set.
 * The possible value defined in type NWMA_ActiveLoadSlave_t are:
 * @li NWMA_NO_ACTIVE_LOAD_IN_SLAVE: set an active load not present
 * @li NWMA_ACTIVE_LOAD_IN_SLAVE: set an active load present
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetActiveLoadSlave(NWMA_ActiveLoadSlave_t ActiveLoad)
{
  NWM_HMSM.bit.ActiveLoadSlave_HMSM = (ActiveLoadSlave_t)ActiveLoad;
}

/**
 * @brief Get the value for ActiveLoad signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_ActiveLoadSlave_t
 * @retval NWMA_NO_ACTIVE_LOAD_IN_SLAVE: return an active load not present
 * @retval NWMA_ACTIVE_LOAD_IN_SLAVE: return an active load present
 */
NWMA_ActiveLoadSlave_t NWMA_GetActiveLoadSlave(void)
{
  return((NWMA_ActiveLoadSlave_t)NWM_HMSM.bit.ActiveLoadSlave_HMSM);
}

/**
 * @brief Set the value for DllSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] DllSts: DllSts signal of slave NWM message to set.
 * The possible value defined in type NWMA_DllSts_t are:
 * @li NWMA_ERROR_ACTIVE: set DLL status in error active
 * @li NWMA_ERROR_PASSIVE: set DLL status in error passive
 * @li NWMA_BUS_OFF: set DLL status in busoff
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetDllSts(NWMA_DllSts_t DllSts)
{
  switch(DllSts)
  {
    case NWMA_ERROR_ACTIVE:
      /* Slave NWM message to configure according to specific DBC */
    NWM_HMSM.bit.D_ES_HMSM = CMMD_ERROR_ACTIVE_STATE;
      break;
      
    case NWMA_ERROR_PASSIVE:
      /* Slave NWM message to configure according to specific DBC */
    NWM_HMSM.bit.D_ES_HMSM = CMMD_ERROR_PASSIVE_WARNING_STATE;
      break;
      
    case NWMA_BUS_OFF:
      /* Slave NWM message to configure according to specific DBC */
    NWM_HMSM.bit.D_ES_HMSM = CMMD_BUS_OFF_STATE;
      break;
      
    default:
      break;
  }
}

/**
 * @brief Send slave NWM message with a specific SysSts value passed
 * by input parameter
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] SlaveNwmSysSts: SysSts signal of slave NWM message to send.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: send a slave NWM message with SysSts in wakeup
 * @li NWMA_NWM_SYS_STAY_ACTIVE: send a slave NWM message with SysSts in stay active
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: send a slave NWM message with SysSts in got to sleep
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SendNwmMsg(NWMA_NwmSysSts_t SlaveNwmSysSts)
{
  if( (NWMA_DllState == NWMA_SET_ERROR_ACTIVE) ||
      (NWMA_DllState == NWMA_SET_ERROR_PASSIVE) )
  {
    /* Set the SysSts of slave NWM message */
    NWMA_SetSlaveNwmSysSts(SlaveNwmSysSts);
    
    /* Update the signals not managed to event */
    NWM_HMSM.bit.GenericFailSts_HMSM  = (GenericFailSts_BCM_t)DDMP_GetGenericFailPresent();
    NWM_HMSM.bit.CurrentFailSts_HMSM  = (CurrentFailSts_HMSM_t)DDMP_GetCurrentFailPresent();
   
    /* Send request of NWM message */
    NETP_SendMsgReq(CAND_NWM_HMSM_HND);
  }
}


/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __NWMA_IS_PRESENT__ */

/*______ E N D _____ (NWMA_config.c) _________________________________________*/
