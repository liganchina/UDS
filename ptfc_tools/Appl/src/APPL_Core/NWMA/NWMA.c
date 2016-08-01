/**
 * @file NWMA.c
 * @brief NetWork Management - Application layer. In this source code is
 * implemented the network management FCA for NextGen network. The reference
 * standard is N07320_ed5.
 * @n The main module features are:
 * @li Main FSM present in paragraph 3.4.2
 * @li DLL error FSM present in paragraph 3.5.7
 * @li Power management FSM present in paragraph 4.2 is implemented in LPMS module
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

/* !!! NOT MOVE !!! */
#define NWMA_IF_OWNER

/* _____ I N C L U D E - F I L E S ___________________________________________*/
#include "NWMA.h"

/* Module inhibition filter */
#ifdef __NWMA_IS_PRESENT__

/* _____ L O C A L - D E F I N E _____________________________________________*/

/* _____ L O C A L - T Y P E S _______________________________________________*/

/**
 * Type of function-pointer for event callback for main FSM management
 */
typedef void (*NWMA_EvtFnc_t)(void);

/**
 * Struct type containing the pointer to event routines used in state/new_state matrix.
 * The event handlers are 3 because for each transition don't exist more than 3 events.
 */
typedef struct NWMA_StateEventMatrix_s
{
  /**@{*/
  NWMA_EvtFnc_t   EvtHndl1;   /**< Event handler 1 */
  NWMA_EvtFnc_t   EvtHndl2;   /**< Event handler 2 */
  NWMA_EvtFnc_t   EvtHndl3;   /**< Event handler 3 */
  /**@}*/
}NWMA_StateEventMatrix_t;


/* _____ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* Handler routines for events management of main FSM */
static void Nwma_E1Hndl(void);
static void Nwma_E2Hndl(void);
static void Nwma_E3Hndl(void);
static void Nwma_E4Hndl(void);
static void Nwma_E5Hndl(void);
static void Nwma_E6Hndl(void);
static void Nwma_E7Hndl(void);
static void Nwma_E9Hndl(void);
static void Nwma_E10Hndl(void);
static void Nwma_E11Hndl(void);
static void Nwma_E12Hndl(void);
static void Nwma_E13Hndl(void);
static void Nwma_E14Hndl(void);
static void Nwma_E15Hndl(void);
static void Nwma_E16Hndl(void);

/* Handler routines for events management of DLL error FSM */
static void Nwma_E1HndlDllErr(void);
static void Nwma_E2HndlDllErr(void);
static void Nwma_E3HndlDllErr(void);
static void Nwma_E4HndlDllErr(void);
static void Nwma_E5HndlDllErr(void);
static void Nwma_E6HndlDllErr(void);
static void Nwma_E7HndlDllErr(void);
static void Nwma_E8HndlDllErr(void);

/* _____ L O C A L - D A T A _________________________________________________*/

/**
  * State/new state matrix to develop the main FSM of N07320.
  * The matrix is managed as follow:
  * @li The rows feature the current state of network
  * @li The columns feature the new state of network
  * @li The fields feature the event handlers
  * @li The event handlers check the event occuring and actuate own actions
  * </ul>
  */
const NWMA_StateEventMatrix_t Nwma_StateEventMatrix[NWMA_NET_STATE_NMB][NWMA_NET_STATE_NMB] = 
{
  /************************************************************/
  /*              Current state: NWMA_NET_OFF                 */
  /************************************************************/
  {
    /* NWMA_NET_OFF --> NWMA_NET_OFF transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_OFF --> NWMA_NET_CHECK transition */
    {    Nwma_E10Hndl,             NULL,             NULL },
    /* NWMA_NET_OFF --> NWMA_NET_STARTUP transition */
    {     Nwma_E9Hndl,             NULL,             NULL },
    /* NWMA_NET_OFF --> NWMA_NET_ON transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_OFF --> NWMA_NET_SILENT transition */
    {            NULL,             NULL,             NULL },
  },
  
  /************************************************************/
  /*              Current state: NWMA_NET_CHECK               */
  /************************************************************/
  {
    /* NWMA_NET_CHECK --> NWMA_NET_OFF transition */
    {    Nwma_E11Hndl,             NULL,             NULL },
    /* NWMA_NET_CHECK --> NWMA_NET_CHECK transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_CHECK --> NWMA_NET_STARTUP transition */
    {     Nwma_E7Hndl,             NULL,             NULL },
    /* NWMA_NET_CHECK --> NWMA_NET_ON transition */
    {     Nwma_E6Hndl,             NULL,             NULL },
    /* NWMA_NET_CHECK --> NWMA_NET_SILENT transition */
    {            NULL,             NULL,             NULL },
  },
  
  /************************************************************/
  /*            Current state: NWMA_NET_STARTUP               */
  /************************************************************/
  {
    /* NWMA_NET_STARTUP --> NWMA_NET_OFF transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_STARTUP --> NWMA_NET_CHECK transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_STARTUP --> NWMA_NET_STARTUP transition */
    {    Nwma_E15Hndl,     Nwma_E16Hndl,             NULL },
    /* NWMA_NET_STARTUP --> NWMA_NET_ON transition */
    {     Nwma_E4Hndl,             NULL,             NULL },
    /* NWMA_NET_STARTUP --> NWMA_NET_SILENT transition */
    {            NULL,             NULL,             NULL },
  },

  /************************************************************/
  /*              Current state: NWMA_NET_ON                  */
  /************************************************************/
  {
    /* NWMA_NET_ON --> NWMA_NET_OFF transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_ON --> NWMA_NET_CHECK transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_ON --> NWMA_NET_STARTUP transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_ON --> NWMA_NET_ON transition */
    {     Nwma_E1Hndl,      Nwma_E2Hndl,      Nwma_E3Hndl },
    /* NWMA_NET_ON --> NWMA_NET_SILENT transition */
    {     Nwma_E5Hndl,             NULL,             NULL },
  },
  
  /************************************************************/
  /*            Current state: NWMA_NET_SILENT                */
  /************************************************************/
  {
    /* NWMA_NET_SILENT --> NWMA_NET_OFF transition */
    {    Nwma_E11Hndl,             NULL,             NULL },
    /* NWMA_NET_SILENT --> NWMA_NET_CHECK transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_SILENT --> NWMA_NET_STARTUP transition */
    {    Nwma_E13Hndl,     Nwma_E14Hndl,             NULL },
    /* NWMA_NET_SILENT --> NWMA_NET_ON transition */
    {            NULL,             NULL,             NULL },
    /* NWMA_NET_SILENT --> NWMA_NET_SILENT transition */
    {            NULL,             NULL,             NULL },
  }
};

/* State variables to manage the APIs NM_REQ() and NM_IND() - par. 3.2.2 */
static NWMA_Req_t       Nwma_NmReq;
static NWMA_Ind_t       Nwma_NmInd;
/* State variables for DLL error FSM */
static NWMA_DllState_t  Nwma_DllNextState;

/* _____ P R I V A T E - D A T A _____________________________________________*/

NWMA_DllState_t  NWMA_DllState;

/* Notify the master NWM message receiving */
bool_t NWMA_NwmReceived[NWM_NOTIFY_NMB];
/* Notify the event6 occuring */
bool_t NWMA_E6Occour;

/* _____ L O C A L - M A C R O S _____________________________________________*/

#define Nwma_ClearNwmRecNotify(NotifyId)\
{\
  NWMA_NwmReceived[(NotifyId)] = FALSE;\
}


/* _____ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* _____ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief Initialization routine for NWMA module. In this routine,
 * according to N07320_ed5 - par. 3.4.2, must generate the event E12
 * for states transition POWER_OFF --> NET_OFF
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_Init(void)
{
  /* The transition POWER_OFF --> NET_OFF is done by E12 */
  /* and it isn't managed by State/Event Matrix */
  Nwma_E12Hndl();
  
  Nwma_E1HndlDllErr();
  
  /* Init local/private variables */
  memset(NWMA_NwmReceived, (int)FALSE, NWM_NOTIFY_NMB);
  
  NWMA_E6Occour      = FALSE;
  NWMA_DllState      = NWMA_SET_ERROR_ACTIVE;
  
  /* Configuration routine init */
  NWMA_InitCfg();
  
  /* First FSM transition */
  NWMA_FsmMgmt();
}

/**
 * @brief This handler routine call, according to current state, all event handlers
 * present in FMS matrix for all possible new state.
 * WARNING: It must be call in wakeup transition as fast as possible and at 
 * max every 20 ms in NET_ON state.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_FsmMgmt(void)
{ 
  NWMA_NetState_t CurrentNetState = Nwma_NmInd.CurrentNetState;
  NWMA_NetState_t NewNetState = NWMA_NET_OFF;

  /* Scan all possible new states */
  for( NewNetState = NWMA_NET_OFF; NewNetState < NWMA_NET_STATE_NMB; NewNetState++ )
  {
    /* The scan run until the first right event occur */
    if( CurrentNetState == Nwma_NmInd.CurrentNetState )
    { 
      /* Select the fields to check the event handlers */
      NWMA_StateEventMatrix_t StateEventMatrix = 
        Nwma_StateEventMatrix[Nwma_NmInd.CurrentNetState][NewNetState];
  
      /* Check and call the first event handler */
      if( StateEventMatrix.EvtHndl1 != NULL )
      {
        StateEventMatrix.EvtHndl1();
      }
      
      /* Check and call the second event handler */
      if( StateEventMatrix.EvtHndl2 != NULL )
      {
        StateEventMatrix.EvtHndl2();
      }
      
      /* Check and call the third event handler */
      if( StateEventMatrix.EvtHndl3 != NULL )
      {
        StateEventMatrix.EvtHndl3();
      }
    }
    else
    {
      break;
    }
  }
}

/**
 * @brief This routine call manages all events about DLL error management as per
 * norm N07320_ed5 par. 3.5.7
 * WARNING: It must be called at max every 50 ms in NET_ON state.
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_DllErrorMgmt(void)
{
  /* The Data Link Layer State Transistion Diagramm (DLL STD) must be executed 
     when the network is in NET ON state, Norm N07320_ed5 par. 3.5.7.2        */
  if(NWMA_GetNetState() == NWMA_NET_ON)
  {
    /* For all the following state see Norm N07320_ed5: STD in figure 5       */
    switch(NWMA_DllState)
    {
      case NWMA_SET_ERROR_ACTIVE:
        Nwma_E1HndlDllErr();
        Nwma_E2HndlDllErr();
        Nwma_E4HndlDllErr();
        
        Nwma_ClearNwmRecNotify(NWMA_DLL_ERROR_MGMT)
        NWMA_DllState = Nwma_DllNextState;
        break;
    
      case NWMA_SET_ERROR_PASSIVE:
        Nwma_E3HndlDllErr();
        Nwma_E4HndlDllErr();
        Nwma_E7HndlDllErr();
        
        Nwma_ClearNwmRecNotify(NWMA_DLL_ERROR_MGMT)
        NWMA_DllState = Nwma_DllNextState;
        break;
        
      case NWMA_BUS_OFF_STATE:
        
        Nwma_E5HndlDllErr();
        
        Nwma_ClearNwmRecNotify(NWMA_DLL_ERROR_MGMT)
        NWMA_DllState = Nwma_DllNextState;
        break;
      
      case NWMA_SET_BUS_OFF:
        
        Nwma_E4HndlDllErr();
        Nwma_E6HndlDllErr();
        Nwma_E8HndlDllErr();
        
        Nwma_ClearNwmRecNotify(NWMA_DLL_ERROR_MGMT)
        NWMA_DllState = Nwma_DllNextState;
        break;
        
      default:
        /* Do nothing */
        break;
    }
  }
  /* Norm N07320_ed5 par. 3.5.7                                               */
  else if(NWMA_GetNetState() == NWMA_NET_OFF)
  {
    Nwma_NmInd.DllStatus = NWMA_ERROR_ACTIVE;
    NWMA_SetDllSts(NWMA_ERROR_ACTIVE);
  }
  else
  {
    /* Misra rule 14.10 */
  }
}

/**
 * @brief This API represent the API NM_REQ() described in par. 3.2.2 but
 * only for parameter CMD. This API is the interface to request by applicative
 * a FSM transition. The CMD parameter, as developed in type NWMA_NetStateReq_t,
 * can assume the following values:
 * @li NET_OFF: used for E1, E15
 * @li NET_CHECK: used for E10
 * @li NET_ON: used for E2, E7, E9, E14
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] NetStateReq represent the parameter CMD and its value are present
 * in type NWMA_NetStateReq_t
 * @param [out] None
 * @return APPL_ResSts_t
 * @retval APPL_OK: the request was accepted
 * @retval APPL_BUSY: there is another pending request
 * @retval APPL_PAR_NOT_OK: the input parameter is wrong
 */
APPL_ResSts_t NWMA_NmStateReq(NWMA_NetStateReq_t  NetStateReq)
{
  APPL_ResSts_t ResSts = APPL_PAR_NOT_OK;

  /* Check the right input parameter */
  if( NetStateReq <= NWMA_NET_ON_REQ )
  {
    /* Check another request presence */
    if( (Nwma_NmReq.NetStateReq != NWMA_NONE_REQ) &&
        (NetStateReq != NWMA_NONE_REQ) )
    {
      ResSts = APPL_BUSY;
    }
    else
    {
      /* Assign new request */
      Nwma_NmReq.NetStateReq = NetStateReq;
      ResSts = APPL_OK;
    }
  }
  
  return(ResSts);
}

/**
 * @brief This routine return the current net state according to parameter NET_STAT
 * of API NM_IND() present in par. 3.2.2
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_NetState_t
 * @retval NWMA_NET_OFF is the NET_OFF value of NET_STAT parameter
 * @retval NWMA_NET_CHECK is the NET_CHECK value of NET_STAT parameter
 * @retval NWMA_NET_STARTUP is the NET_STARTUP value of NET_STAT parameter
 * @retval NWMA_NET_ON is the NET_ON value of NET_STAT parameter
 * @retval NWMA_NET_SILENT is the NET_SDN value of NET_STAT parameter
 */
NWMA_NetState_t NWMA_GetNetState(void)
{
  return(Nwma_NmInd.CurrentNetState);
}

/**
 * @brief Routine callback to use to get notify of master NWM message receiving.
 * WARNING: this routine MUST BE LINKED to network service
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_NwmReceivedCbk(void)
{
  memset(NWMA_NwmReceived, (int)TRUE, NWM_NOTIFY_NMB);
}

/**
 * @brief Routine callback to use to get notify of slave NWM message sending.
 * WARNING: this routine MUST BE LINKED to network service
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_SendNwmNaxCbk(void)
{
  if( NWMA_E6Occour == TRUE )
  {
    NWMA_E6Occour = FALSE;
    (void)LPMS_SetEvent(LPMS_PR_PSEUDO_WAKEUP);
  }
}


/* _____ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief Handler routine to manage the event E1 and to actuate the action A1
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E1:
 * @li NM_REQ(NET_OFF)
 * actuate A1:
 * @li AL = FALSE
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E1Hndl(void)
{
  /* Check on E1 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_OFF_REQ )
  {
    /* A1: AL = FALSE */
    NWMA_SetActiveLoadSlave(NWMA_NO_ACTIVE_LOAD_IN_SLAVE);
    
    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A1Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E2 and to actuate the action A2
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E2:
 * @li NM_REQ(NET_ON)
 * actuate A2:
 * @li AL = TRUE
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E2Hndl(void)
{
  /* Check on E2 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_ON_REQ )
  {
    /* A2: AL = TRUE */
    NWMA_SetActiveLoadSlave(NWMA_ACTIVE_LOAD_IN_SLAVE);
    
    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A2Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E3 and to actuate the action A3
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E3:
 * @li (NMmMaster(SA) received) OR
 * @li (SA Timer Timeout AND (AL == TRUE))
 * actuate A3:
 * @li Send NMmXXX(SA)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_ON)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E3Hndl(void)
{
  u32 checkTimer;
  NWMA_ActiveLoadSlave_t activeLoad;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  activeLoad = NWMA_GetActiveLoadSlave();
  
  /* Check on E3 event */
  if( (NWMA_CheckMasterNwmSysSts(NWMA_NWM_SYS_STAY_ACTIVE) == TRUE) ||
      ((checkTimer == 0U) && (activeLoad == NWMA_ACTIVE_LOAD_IN_SLAVE)) )
  {
    /* Send NMmXXX(SA) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_STAY_ACTIVE);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_ON) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_ON;
    
    /* Actuate actions related to other sw modules */
    NWMA_A3Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E4 and to actuate the action A4
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E4:
 * @li (NMmMaster(SA) received) OR
 * @li (SA Timer Timeout)
 * actuate A4:
 * @li Send NMmXXX(SA)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_ON)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E4Hndl(void)
{
  u32 checkTimer;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  
  /* Check on E4 event */
  if( (NWMA_CheckMasterNwmSysSts(NWMA_NWM_SYS_STAY_ACTIVE) == TRUE) ||
      (checkTimer == 0U) )
  {
    /* Send NMmXXX(SA) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_STAY_ACTIVE);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_ON) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_ON;
    
    /* Actuate actions related to other sw modules */
    NWMA_A4Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E5 and to actuate the action A5
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E5:
 * @li (NMmMaster(S) received) OR
 * @li (SA Timer Timeout AND (AL == FALSE))
 * actuate A5:
 * @li Start 100ms Sleep Timer
 * @li NM_IND(NET_SDN)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E5Hndl(void)
{
  u32 checkTimer;
  NWMA_ActiveLoadSlave_t activeLoad;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  activeLoad = NWMA_GetActiveLoadSlave();
  
  /* Check on E5 event */
  if( (NWMA_CheckMasterNwmSysSts(NWMA_NWM_SYS_GO_TO_SLEEP) == TRUE) ||
      ((checkTimer == 0U) && (activeLoad == NWMA_NO_ACTIVE_LOAD_IN_SLAVE)) )
  { 
    /* Start 100ms Sleep Timer */
    (void)TLRP_SetFast(TLRP_NwmaSleepShortTimer);
    (void)TLRP_ResetSlow(TLRP_NwmaSleepLongTimer);
    
    /* NM_IND(NET_SDN) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_SILENT;
    
    /* Actuate actions related to other sw modules */
    NWMA_A5Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E6 and to actuate the action A6
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E6:
 * @li NMmMaster(SA) received
 * actuate A6:
 * @li Send NMmXXX(SA)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_ON)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E6Hndl(void)
{
  /* Check on E6 event */
  if( NWMA_CheckMasterNwmSysSts(NWMA_NWM_SYS_STAY_ACTIVE) == TRUE )
  {
    /* Send NMmXXX(SA) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_STAY_ACTIVE);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_ON) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_ON;
    
    /* Actuate actions related to other sw modules */
    NWMA_A6Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E7 and to actuate the action A7
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E7:
 * @li NM_REQ(NET_ON)
 * actuate A7:
 * @li AL = TRUE
 * @li Send NMmXXX(WU)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_STARTUP)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E7Hndl(void)
{
  /* Check on E7 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_ON_REQ )
  {
    /* AL = TRUE */
    NWMA_SetActiveLoadSlave(NWMA_ACTIVE_LOAD_IN_SLAVE);
    /* Send NMmXXX(WU) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_WAKEUP);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_STARTUP) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_STARTUP;

    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A7Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E9 and to actuate the action A9
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E9:
 * @li NM_REQ(NET_ON)
 * actuate A9:
 * @li Init CAN
 * @li AL = TRUE
 * @li Send NMmXXX(WU)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_STARTUP)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E9Hndl(void)
{
  /* Check on E9 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_ON_REQ )
  {
    /* Init CAN - This subaction is done yet */

    /* AL = TRUE */
    NWMA_SetActiveLoadSlave(NWMA_ACTIVE_LOAD_IN_SLAVE);
    /* Send NMmXXX(WU) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_WAKEUP);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_STARTUP) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_STARTUP;

    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A9Cfg()
  } 
}

/**
 * @brief Handler routine to manage the event E10 and to actuate the action A10
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E10:
 * @li (Bus Wake Up) OR
 * @li (NM_REQ(NET_CHECK))
 * actuate A10:
 * @li Init CAN
 * @li Start 2s Sleep Timer
 * @li NM_IND(NET_CHECK)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E10Hndl(void)
{
  /* Check on E10 event: only NM_REQ(NET_CHECK) because the bus wakeup */
  /* is managed by Power Management module */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_CHECK_REQ )
  {
    /* Init CAN - This subaction is done yet */

    /* Start 2s Sleep Timer */
    (void)TLRP_SetSlow(TLRP_NwmaSleepLongTimer);
    (void)TLRP_ResetFast(TLRP_NwmaSleepShortTimer);
    
    /* NM_IND(NET_CHECK) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_CHECK;

    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A10Cfg()
  } 
}

/**
 * @brief Handler routine to manage the event E11 and to actuate the action A11
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E11:
 * @li Sleep Timer Timeout
 * actuate A11:
 * @li Shutdown CAN
 * @li NM_IND(NET_OFF)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E11Hndl(void)
{
  u32 checkTimerSlow;
  u16 checkTimerFast;
  
  checkTimerSlow = TLRP_GetSlow(TLRP_NwmaSleepLongTimer);
  checkTimerFast = TLRP_GetFast(TLRP_NwmaSleepShortTimer);
  
  /* Check on E11 event */
  if( (checkTimerSlow == 0U) && (checkTimerFast == 0U) )
  {
    /* Shutdown CAN - This subaction will be done by Power management module */

    /* NM_IND(NWMA_NET_OFF) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_OFF;
    
    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A11Cfg()
  } 
}

/**
 * @brief Handler routine to manage the event E12 and to actuate the action A12
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E12:
 * @li +30 ON
 * actuate A12:
 * @li NM_IND(NET_OFF)
 * @li AL = FALSE
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E12Hndl(void)
{
  /* The E12 is intrinsic to run code */
  Nwma_NmInd.CurrentNetState      = NWMA_NET_OFF;
  Nwma_NmInd.DllStatus            = NWMA_ERROR_ACTIVE;
  /* AL = FALSE */
  NWMA_SetActiveLoadSlave(NWMA_NO_ACTIVE_LOAD_IN_SLAVE);
  
  /* Actuate actions related to other sw modules */
  NWMA_A12Cfg()
}

/**
 * @brief Handler routine to manage the event E13 and to actuate the action A13
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E13:
 * @li NMmMaster(WU) received
 * actuate A13:
 * @li Start 2s SA Timer
 * @li NM_IND(NET_STARTUP)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E13Hndl(void)
{
  /* Check on E13 event */
  if( NWMA_CheckMasterNwmSysSts(NWMA_NWM_SYS_WAKEUP) == TRUE )
  {
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_STARTUP) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_STARTUP;
    
    /* Actuate actions related to other sw modules */
    NWMA_A13Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E14 and to actuate the action A14
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E14:
 * @li NM_REQ(NET_ON)
 * actuate A14:
 * @li AL = TRUE
 * @li Send NMmXXX(WU)
 * @li Start 2s SA Timer
 * @li NM_IND(NET_STARTUP)
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E14Hndl(void)
{
  /* Check on E9 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_ON_REQ )
  {
    /* AL = TRUE */
    NWMA_SetActiveLoadSlave(NWMA_ACTIVE_LOAD_IN_SLAVE);
    /* Send NMmXXX(WU) */
    NWMA_SendNwmMsg(NWMA_NWM_SYS_WAKEUP);
    
    /* Start 2s SA Timer */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* NM_IND(NET_STARTUP) */
    Nwma_NmInd.CurrentNetState = NWMA_NET_STARTUP;

    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A14Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E15 and to actuate the action A15
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E15:
 * @li NM_REQ(NET_OFF)
 * actuate A15:
 * @li AL = FALSE
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E15Hndl(void)
{
  /* Check on E15 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_OFF_REQ )
  {
    /* A15: AL = FALSE */
    NWMA_SetActiveLoadSlave(NWMA_NO_ACTIVE_LOAD_IN_SLAVE);
    
    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A15Cfg()
  }
}

/**
 * @brief Handler routine to manage the event E16 and to actuate the action A16
 * for main FSM.
 * According to requirements  N07320_ed5 - par. 3.4.2:
 * If occour E16:
 * @li NM_REQ(NET_ON)
 * actuate A16:
 * @li AL = TRUE
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E16Hndl(void)
{
  /* Check on E16 event */
  if( Nwma_NmReq.NetStateReq == NWMA_NET_ON_REQ )
  {
    /* A16: AL = TRUE */
    NWMA_SetActiveLoadSlave(NWMA_ACTIVE_LOAD_IN_SLAVE);
    
    /* Clear the applicative request */
    Nwma_NmReq.NetStateReq = NWMA_NONE_REQ;
    
    /* Actuate actions related to other sw modules */
    NWMA_A16Cfg()
  }
}

/**
 * @brief Transition Set ERROR ACTIVE --> Set ERROR ACTIVE 
 * Handler routine to manage the event E1 and to actuate the action A1
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E1:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)          ] AND
 * @li [(CAN controller is not in BUS OFF state)              ] AND
 * @li [(CAN controller is not in ERROR PASSIVE/WARNING state)]
 * actuate A1:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_ACTIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E1HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkBusOff, checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkBusOff = CAND_GetBusOffState();
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if(((NWMA_CheckMasterNwmReceived() == TRUE) ||
      (checkTimer == 0U))              &&
      (checkBusOff       == FALSE)     &&
      (checkErrorPassive == FALSE)     &&
      (checkErrorWarning == FALSE)
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_ACTIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_ACTIVE;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_ERROR_ACTIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A1Cfg()
  }
}

/**
 * @brief Transition Set ERROR ACTIVE --> Set ERROR PASSIVE 
 * Handler routine to manage the event E2 and to actuate the action A2
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E2:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)        ] AND
 * @li [(CAN controller is in ERROR PASSIVE/WARNING state) ]
 * actuate A2:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_PASSIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E2HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if( ((NWMA_CheckMasterNwmReceived() == TRUE) ||
       (checkTimer == 0U))           &&
      ((checkErrorPassive  == TRUE)  ||
       (checkErrorWarning  == TRUE))
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_PASSIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_PASSIVE;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_ERROR_PASSIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A2Cfg()
  }
}

/**
 * @brief Transition Set ERROR PASSIVE --> Set ERROR PASSIVE 
 * Handler routine to manage the event E3 and to actuate the action A3
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E3:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)      ] AND
 * @li [(CAN controller is in ERROR PASSIVE/WARNING state)]
 * actuate A3:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_PASSIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E3HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if(((NWMA_CheckMasterNwmReceived() == TRUE) ||
      (checkTimer   == 0U    ))     &&
     ((checkErrorPassive  == TRUE) ||
      (checkErrorWarning == TRUE))
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_PASSIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_PASSIVE;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_ERROR_PASSIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A3Cfg()
  }
}

/**
 * @brief Transition Set ERROR ACTIVE  --> Set BUS OFF 
 *    OR Transition  Set ERROR PASSIVE --> Set BUS OFF 
 *    OR Transition  Set BUS OFF       --> Set BUS OFF 
 * Handler routine to manage the event E4 and to actuate the action A4
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E4:
 * @li [(CAN controller is in BUS OFF  state)]
 * actuate A4:
 * @li [(CAN interface must be disabled) AND (1s Silence Timer must be started)]
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E4HndlDllErr(void)
{
  if(CAND_GetBusOffState() == TRUE)
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_BUS_OFF);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_BUS_OFF;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_BUS_OFF_STATE;
    
    /* CAN interface must be disabled                                         */
    CAND_PwrOff();
    
    /* 1s Silence Timer must be started                                       */
    TLRP_SetFast(TLRP_NwmaBusOffTimer);
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A4Cfg()
  }
}

/**
 * @brief Transition BUS OFF State  --> Set BUS OFF
 * Handler routine to manage the event E5 and to actuate the action A5
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E5:
 * @li [(Silence Timer Timeout)]
 * actuate A5:
 * @li [(2s SA Timer must be started)               AND
 * @li (NMmXXX() must be transmitted with D_ES = 2) AND
 * @li (CAN interface must be enabled)]
 * @li RECALL: If the node is in the BUS OFF state it is a slave node, its 
 * NMmXXX () must be transmitted, under Silence Timer 1 s, only in response 
 * to NMmMaster within 50 ms. it is not permitted the transmission of 
 * application messages before NMmMaster.
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E5HndlDllErr(void)
{
  if(TLRP_GetFast(TLRP_NwmaBusOffTimer) == 0U)
  {
    /* 2s SA Timer must be started                                            */
    TLRP_SetSlow(TLRP_NwmaSaTimer);
    
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_BUS_OFF);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_BUS_OFF;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_BUS_OFF;
    
    /* CAN interface must be enabled                                          */
    CAND_Init();
    NETP_Restore();
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A5Cfg()
  }
}

/**
 * @brief Transition Set BUS OFF --> Set ERROR ACTIVE
 * Handler routine to manage the event E6 and to actuate the action A6
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E6:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)          ] AND
 * @li [(CAN controller is not in BUS OFF state)              ] AND
 * @li [(CAN controller is not in ERROR PASSIVE/WARNING state)]
 * actuate A6:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_ACTIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E6HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkBusOff, checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkBusOff = CAND_GetBusOffState();
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if(((NWMA_CheckMasterNwmReceived() == TRUE) ||
      (checkTimer == 0U))               &&
      (checkBusOff        == FALSE)     &&
      (checkErrorPassive  == FALSE)     &&
      (checkErrorWarning  == FALSE)
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_BUS_OFF);

    /* Send request of NWM message */
    NETP_SendMsgReq(CAND_NWM_HMSM_HND);
    /* Force NETP to send immediatly the message, otherwise 2 messages        */
    /* with D_ES = BUS_OFF will be sent, one from this routine, the other one */
    /* from Nwma_E3Hndl                                                       */
    NETP_ApplMsgSendingMgmt();

    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_ACTIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_ACTIVE;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_ERROR_ACTIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A6Cfg()
  }
}

/**
 * @brief Transition Set BUS OFF --> Set ERROR ACTIVE
 * Handler routine to manage the event E7 and to actuate the action A7
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E7:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)          ] AND
 * @li [(CAN controller is not in BUS OFF state)              ] AND
 * @li [(CAN controller is not in ERROR PASSIVE/WARNING state)]
 * actuate A7:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_ACTIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E7HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkBusOff, checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkBusOff = CAND_GetBusOffState();
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if(((NWMA_CheckMasterNwmReceived() == TRUE) ||
      (checkTimer == 0U))               &&
      (checkBusOff        == FALSE)     &&
      (checkErrorPassive  == FALSE)     &&
      (checkErrorWarning  == FALSE)
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_ACTIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_ACTIVE;
    
    /* Set currente state for DLL FSM                                         */
    Nwma_DllNextState = NWMA_SET_ERROR_ACTIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A7Cfg()
  }
}

/**
 * @brief Transition Set BUS OFF --> Set ERROR PASSIVE
 * Handler routine to manage the event E8 and to actuate the action A8
 * for DLL FSM.
 * According to requirements  N07320_ed5 - par. 3.5.7.2:
 * If occour E8:
 * @li [(NMmMaster() received) OR (SA Timer Timeout)      ] AND
 * @li [(CAN controller is in ERROR PASSIVE/WARNING state)]
 * actuate A8:
 * @li NMmXXX() must be trasmitted with D_ES = ERROR_PASSIVE
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
static void Nwma_E8HndlDllErr(void)
{
  u32 checkTimer;
  u08 checkErrorPassive, checkErrorWarning;
  
  checkTimer = TLRP_GetSlow(TLRP_NwmaSaTimer);
  checkErrorPassive = CAND_GetErrorPassiveState();
  checkErrorWarning = CAND_GetErrorWarningeState();
  
  if(((NWMA_CheckMasterNwmReceived() == TRUE) ||
      (checkTimer == 0U))           &&
     ((checkErrorPassive  == TRUE)  || 
      (checkErrorWarning  == TRUE))
    )
  {
    /* Set D_ES value                                                         */
    NWMA_SetDllSts(NWMA_ERROR_PASSIVE);
    
    /* Set current state for DLL FSM                                          */
    Nwma_NmInd.DllStatus = NWMA_ERROR_PASSIVE;
    
    /* Set next state for DLL FSM                                             */
    Nwma_DllNextState = NWMA_SET_ERROR_PASSIVE;
    
    /* Actuate actions related to other sw modules                            */
    NWMA_DLLERR_A8Cfg()
  }
}


#endif /* end __NWMA_IS_PRESENT__ */

/*_____E N D _____ (NWMA.c) __________________________________________________*/
