/**
 * @file NETP.c
 * @brief NETwork Presentation: source code of network module for the presentation layer.
 * @n The main module features/services are:
 * @li Multi DBC management according to MSM ECU type
 * @li API to send the event CAN messages by applicative
 * @li API to send the event CAN messages by diagnosis applicative (UDS)
 * @li Configuration table to send the periodic CAN messages automatically
 * @li Configuration table to notify the sending message by confirmation callback
 * @li Configuration table to filter the event messages near periodic messages
 * sending. This strategy, call MTBE, can be enabled/disabled by the configuration
 * define NETP_MTBE_STRATEGY
 * @li Configuration table to manage the diagnosis recovery for absent/faulty state.
 * This service can be enabled/disabled by the configuration define NETP_TIMEOUT_SERVICE.
 * @li Electrical and network diagnosis with own recovery
 * </ul>
 *
 * @version 2.1
 * @author Gianpiero Lenta (Bitron S.p.A.) - Carmine Celozzi (Akhela S.r.l.)
 * @date 23 may 2012 / 20 october 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 05/06/13   0.1  GIL     First derivative from Tesla (125K)
|-----------------------------------------------------------------------------
| 07/11/13   0.2  GIL     - Node Mute and bus off management
|                         - Fixing some MISRA C rule
|                         - Timeout Inhibition changed
|-----------------------------------------------------------------------------
| 06/01/14   0.3  GIL     Bit6(Test Not Completed this Monitorung Cycle) 
|                         management
|-----------------------------------------------------------------------------
| 06/10/14   1.0  CC      Porting first release to new architecture for TESLA
|                         project
|-----------------------------------------------------------------------------
| 20/10/14   1.1  CC      Inserted some bug fixing and module optimization
|-----------------------------------------------------------------------------
| 04/11/14   1.2  CC      New design to align this module to new CAND module.
|                         The main features inserted are:
|                         - Multi DBC management according to MSM ECU type
|                         - Configuration table to send the periodic CAN  
|                           messages automatically
|                         - Configuration table to notify the sending message 
|                           by confirmation callback
|                         - Configuration table to filter the event messages 
|                           near periodic messages sending. This strategy, 
|                           call MTBE, can be enabled/disabled by the   
|                           configuration define NETP_MTBE_STRATEGY
|-----------------------------------------------------------------------------
| 20/11/14   2.0  CC      Platform official release (complete redesign)
|-----------------------------------------------------------------------------
| 17/02/15   2.1  CC      Inserted the filter in NET_ON to send the applicative
|                         periodic messages
|-----------------------------------------------------------------------------
| 03/06/15   2.2  CC      Improvment about call of indication callback
|-----------------------------------------------------------------------------
| 04/11/15   2.3  DC      Improvements of absent\faulty network fail management
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define NETP_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "NETP.h"
#include "NETP_config.h"

/* Module inhibition filter */
#ifdef __NETP_IS_PRESENT__

/*______ L O C A L - D E F I N E _____________________________________________*/

#define NETP_NONE_SENDING_MSG     ((uint8_t)0xFFu)
#define NETP_APPL_MSG_DLC         ((uint8_t)0u)

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct Netp_TxMsgHndl_s
{
  uint16_t SendReq      :1;
  uint16_t SendDenied   :1;
  uint16_t PeriodTimer  :14;
}Netp_TxMsgHndl_t;

#ifdef NETP_MTBE_STRATEGY
typedef struct Netp_MtbeHndl_s
{
  bool_t   SendingEnable;
  uint16_t Thl;
  uint16_t Thh;
  uint16_t Timer;
}Netp_MtbeHndl_t;
#endif
  
/* Struct used to manage absent\faulty diagnosis for every entry of enum NETP_Af_t (NETP_cfgIf.h) */
typedef struct Netp_NetDiagnose_s
{
  u16             Mask;
  u08             MsgCnt;
  PRES_Fault_t    AbsentFaultySts;
}Netp_NetDiagnose_t;

/*______ L O C A L - D A T A _________________________________________________*/

/* Indexes to scan the DBC messages */
static uint8_t Netp_StartScanTxMsg;
static uint8_t Netp_StopScanTxMsg;
static uint8_t Netp_StartScanRxMsg;
static uint8_t Netp_StopScanRxMsg;

/* RX MESSAGES SECTION */
static NETP_ComType_t        Netp_ComTypeRx;
static NETP_RxStatus_t       Netp_RxStatus[CAND_RX_MSG_NMB];
static NETP_EnRxMsgTOutMng_t Netp_EnRxMsgToutMng;

/* TX MESSAGES SECTION */
static Netp_TxMsgHndl_t      Netp_TxMsgHndl[CAND_TX_MSG_NMB];
#ifdef NETP_MTBE_STRATEGY
  static Netp_MtbeHndl_t     Netp_MtbeHndl[CAND_TX_MSG_NMB];
#endif
static CAND_TxMsgName_t      Netp_TxSending;
static NETP_ComType_t        Netp_ComTypeTx;

/* NET STATUS SECTION */
static NETP_NetStatus_t Netp_NetStatus;

/* DIAGNOSYS SECTION */
static uint16_t        Netp_NodeMuteErrCnt;
static bool_t          Netp_MuteDtcStatus;
static u16 MsgTimeOut;
static PRES_State_t    Netp_MonitorStatus;
static bool_t          Netp_EnableRxTimeout;
static Netp_NetDiagnose_t  Netp_NetDiagnose[NETP_ABS_FAULTY_DISABLE];

/*______ L O C A L - M A C R O S _____________________________________________*/

#define NETP_BSET(bit)      (0x0001u << (bit))
#define NETP_BCLR(bit)      (~(0x0001u << (bit)))

/*______ G L O B A L - D A T A _______________________________________________*/

const NETP_TxNetMonitor_t *NETP_TxNetMonitorPtr;
const NETP_RxNetMonitor_t *NETP_RxNetMonitorPtr;

#ifdef __CMMD_MULTI_DBC__ 
/* MSM model type */
uint8_t NETP_MsmEcuType;
#endif


/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static void   Netp_InitPtrToMsgFrame(void);
static void   Netp_SetLimitToScan(void);
static void   Netp_InitNabsFaultyMask(void);
static bool_t Netp_NodeAbsDiag(NETP_Af_t AbsFaulty);
static bool_t Netp_NodeFaultyDiag(NETP_Af_t AbsFaulty);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief Initialization routine of the network module for the presentation layer.
 * @author Gianpiero Lenta - Bitron S.p.A. / Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NETP_Init(void)
{
  /* Init the pointers to configuration look-up table of the DBC messages */
  Netp_InitPtrToMsgFrame();
  /* Set the indexes to scan the DBC messages */
  Netp_SetLimitToScan();

  /* Init messages handlers, timers and diagnostic data */
  NETP_Restore();

  /*** call user macro to set communication type *******/
  /*** (N.B. It is called at PSEUDO RUN init!) *********/
  NETP_SET_COMM_TYPE()
}

/**
 * @brief Initialization routine of the network module.
 * It initialize every resources except communication control type and DBC configurations.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NETP_Restore(void)
{
  uint8_t TxIdx;
    
  /* Init TX messages section */
  for(TxIdx = 0U; TxIdx < CAND_TX_MSG_NMB; TxIdx++)
  {
    /* Init the main message handler */
    Netp_TxMsgHndl[TxIdx].SendReq     = FALSE;
    Netp_TxMsgHndl[TxIdx].SendDenied  = FALSE;
    Netp_TxMsgHndl[TxIdx].PeriodTimer = (&NETP_TxNetMonitor[TxIdx])->Period;

#ifdef NETP_MTBE_STRATEGY
    /* Init the handler for Mtbe strategy */
    Netp_MtbeHndl[TxIdx].SendingEnable = TRUE;
    Netp_MtbeHndl[TxIdx].Thl   = ((&NETP_TxNetMonitor[TxIdx])->Period - 
                                  (&NETP_TxNetMonitor[TxIdx])->Mtbe);
    Netp_MtbeHndl[TxIdx].Thh   = (&NETP_TxNetMonitor[TxIdx])->Mtbe;
    Netp_MtbeHndl[TxIdx].Timer = (&NETP_TxNetMonitor[TxIdx])->Mtbe;
#endif
  }
  
  /* Set the default Tx message name */
  Netp_TxSending = (CAND_TxMsgName_t)NETP_NONE_SENDING_MSG;

  /* Init RX messages section */
#ifdef NETP_TIMEOUT_SERVICE
  NETP_InitTimeout(NETP_CCT_APPL_MSG);
  Netp_InitNabsFaultyMask();
#endif

  /* Init diagnosis variables */
  Netp_NodeMuteErrCnt  = NETP_MUTE_SILENCE_TIME;
  Netp_MuteDtcStatus   = FALSE;
  Netp_EnableRxTimeout = TRUE;
}

/**
 * @brief Manage the send request of the periodic TX messages. The messages
 * of type periodic (P) must be configured in the look-up table NETP_TxNetMonitor.
 * This routine set the sending inhibition for the MTBE strategy.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NETP_PeriodicMsgMgmt(void)
{
  uint8_t TxIdx;
  NETP_TxType_t TxType;
  const NETP_TxNetMonitor_t *NetTxMonitorPtr = NETP_TxNetMonitorPtr;

  /* Scan all Tx messages for the correct DBC */
  for(TxIdx = Netp_StartScanTxMsg; TxIdx < Netp_StopScanTxMsg; TxIdx++)
  {
    /* Read the communication type of the message */
    TxType = NetTxMonitorPtr->TxType;

    /* Manage the send request only for periodic message type */
    if( ((TxType == NETP_TX_P) || (TxType == NETP_TX_PE)) &&
        (Netp_NetStatus == NETP_NET_ON) )
    {
      /* Check if the current communication type allows the sending management */
      if( (Netp_ComTypeTx & NetTxMonitorPtr->ComType) != 0u )
      {
        /* Wait the period time...*/
        if( Netp_TxMsgHndl[TxIdx].PeriodTimer > 0u )
        {
          Netp_TxMsgHndl[TxIdx].PeriodTimer--;
          
          if( Netp_TxMsgHndl[TxIdx].PeriodTimer == 0u )
          {
            /* Notify the transmission request */
            Netp_TxMsgHndl[TxIdx].SendReq = TRUE;
            /* Reload the period timer */
            Netp_TxMsgHndl[TxIdx].PeriodTimer = NetTxMonitorPtr->Period;
          }
        }
#ifdef NETP_MTBE_STRATEGY
        /* Update the timer for Mtbe time */
        if( Netp_MtbeHndl[TxIdx].Timer > 0 )
        {
          Netp_MtbeHndl[TxIdx].Timer--;
        }
        
        /* Check the Thl limit */
        if(Netp_TxMsgHndl[TxIdx].PeriodTimer > Netp_MtbeHndl[TxIdx].Thl)
        {
          /* Set sending inhibition */
          Netp_MtbeHndl[TxIdx].SendingEnable = FALSE;
        }
        else if(Netp_TxMsgHndl[TxIdx].PeriodTimer < Netp_MtbeHndl[TxIdx].Thh)
        {
          /* Set sending inhibition */
          Netp_MtbeHndl[TxIdx].SendingEnable = FALSE;
        }
        else if(Netp_TxMsgHndl[TxIdx].PeriodTimer == 0u)
        {
          /* Enable the sending */
          Netp_MtbeHndl[TxIdx].SendingEnable = TRUE;
        }
        else
        {
          /* Enable the sending */
          Netp_MtbeHndl[TxIdx].SendingEnable = TRUE;
        }  
#endif /* end NETP_MTBE_STRATEGY */
      }
      /* Resource busy by diagnosys */
      else
      {
        /* Clear the transmission request */
        Netp_TxMsgHndl[TxIdx].SendReq = FALSE;
        /* Reload the period timer */
        Netp_TxMsgHndl[TxIdx].PeriodTimer = NetTxMonitorPtr->Period;
      } 
    }
    else if( Netp_NetStatus != NETP_NET_ON )
    {
      /* Clear the transmission request */
      Netp_TxMsgHndl[TxIdx].SendReq = FALSE;
      /* Reload the period timer */
      Netp_TxMsgHndl[TxIdx].PeriodTimer = NetTxMonitorPtr->Period;
    }
    else
    {
      /* Do nothing because the message has a TxType = NETP_TX_E */
    }

    NetTxMonitorPtr++;
  }
}




void NETP_ApplMsgSendingMgmt(void)
{
  uint8_t TxIdx;
  
  for(TxIdx = Netp_StartScanTxMsg; TxIdx < Netp_StopScanTxMsg; TxIdx++)
  {
    if((Netp_TxMsgHndl[TxIdx].SendReq == TRUE) && 
       (Netp_TxSending == NETP_NONE_SENDING_MSG) &&
       (Netp_NetStatus == NETP_NET_ON))
    {
      if( CAND_SendMsg((CAND_TxMsgName_t)TxIdx, NETP_APPL_MSG_DLC) == CAND_EVT_TX_SUCCESS )
      {
        /* Update the message sending only if the send is correct */
        Netp_TxSending = ((CAND_TxMsgName_t)TxIdx);
      }
      break;
    }
  }
}




#ifdef NETP_TIMEOUT_SERVICE
/**
 * @brief  NETP_MonitorRxPeriod
 * @note   must be called @10ms (polling)
 */
void NETP_MonitorRxPeriod(void)
{
  u08 MsgIdx;
  bool_t muteStatus;
  const NETP_RxNetMonitor_t *NetMonitorPtr = NETP_RxNetMonitorPtr;
  PRES_KeyStatus_t KeySts = NETP_GetKeyStatus();
  muteStatus = NETP_GetMuteStatus();

  /* monitor timeout if :                                                    */
  if( (CAND_GetBusOffState() == FALSE)              && /* NOT in bus off     */
      (Netp_EnRxMsgToutMng == NETP_TOUT_MNG_ENABLE) && /* IS in NET ON       */
      (muteStatus == FALSE)                         && /* NOT in bus mute    */
      (KeySts != KEYA_CRANK_STATUS) )                  /* NOT in crank       */
  {
    Netp_MonitorStatus = S_ON;
    
    /* Scan all RX messages configured */
    for(MsgIdx = Netp_StartScanRxMsg; MsgIdx < Netp_StopScanRxMsg; MsgIdx++)
    {
      /* If the communication isn't disabled by UDS and it's a applicative message and...*/
      if( ((NetMonitorPtr->ComType & Netp_ComTypeRx) != 0U)  &&
          /* ...the key status match with configuration of diagnosis in key off */
          (((NetMonitorPtr->DiagKeyOffEnable == FALSE) && (KeySts == KEYA_ON_STATUS)) ||
           (NetMonitorPtr->DiagKeyOffEnable == TRUE)) )
      {
        if( Netp_EnableRxTimeout == TRUE )
        {
          if(Netp_RxStatus[MsgIdx].ElapsedTime > 0u)
          {
            Netp_RxStatus[MsgIdx].ElapsedTime--;

            if(Netp_RxStatus[MsgIdx].ElapsedTime == 0u)
            {
              /* set message absent */
              Netp_RxStatus[MsgIdx].MsgStatus = NETP_MSG_NOT_RECEIVED;
              /**/
              if(NetMonitorPtr->AbsentFaultyEnable != NETP_ABS_FAULTY_DISABLE)
              {
                MsgTimeOut |= (u16)NETP_BSET((u16)MsgIdx - (u16)Netp_StartScanRxMsg);
              }

              /* Call the callback configured */
              if( NetMonitorPtr->RecCbk != NULL )
              { 
                /* call recovery */
                NetMonitorPtr->RecCbk();
              }
            }
          }
        }
      }
      else
      {
        /* message timeout disable by UDS :com ctrl */
        Netp_RxStatus[MsgIdx].ElapsedTime = NetMonitorPtr->RxMsgTimeOut;
      }

      NetMonitorPtr++;
    }
  }
  else
  {
    Netp_MonitorStatus = S_OFF;

    if( CAND_GetBusOffState() == TRUE )
    {
      NETP_BUS_OFF_RECOVERY()
    }
    NETP_InitTimeout(NETP_CCT_APPL_MSG);
  }
#ifdef NETP_NODE_MUTE_DIAG
  NETP_ManageNodeMute();
#endif
}
#else
void NETP_MonitorRxPeriod(void)
{
}
#endif



void NETP_TxEvtMgmt(void)
{
  u08 MsgIdx;

  /* Scan all RX messages configured */
  for(MsgIdx = Netp_StartScanTxMsg; MsgIdx < Netp_StopScanTxMsg; MsgIdx++)
  {
    /* Check confirmation flag by CAND module */
    if( CAND_CheckTxMsgRdy((CAND_TxMsgName_t)MsgIdx) == TRUE )
    {
      /* Clear the send request */
      Netp_TxMsgHndl[MsgIdx].SendReq = FALSE;
      
      /* Call TX callback configured */
      if( NETP_TxNetMonitor[MsgIdx].ConfCbk != NULL )
      {
        NETP_TxNetMonitor[MsgIdx].ConfCbk();
      }
  
      /* Clear the sending notify */
      Netp_TxSending = ((CAND_TxMsgName_t)NETP_NONE_SENDING_MSG);
    }
  }
}



#ifdef NETP_TIMEOUT_SERVICE
/**
 * @brief  Monitor the received periodic messages and call applicative callback
 * @note   Must be called @ event
 */
void NETP_RxEvtMgmt(void)
{ 
  u08 MsgIdx;
  const NETP_RxNetMonitor_t *NetMonitorPtr = NETP_RxNetMonitorPtr;


  /* Scan all RX messages configured */
  for(MsgIdx = Netp_StartScanRxMsg; MsgIdx < Netp_StopScanRxMsg; MsgIdx++)
  {
    /* Check the Rx event occurence */
    if( CAND_CheckRxMsgEvt((CAND_RxMsgName_t)MsgIdx) == TRUE )
    {
      /* Only for applicative message */
      if( (NetMonitorPtr->ComType & NETP_CCT_APPL_MSG) != 0U )
      {
        /* Load the timeout timer */
        Netp_RxStatus[MsgIdx].ElapsedTime = NetMonitorPtr->RxMsgTimeOut;
  
        /* set message received */
        Netp_RxStatus[MsgIdx].MsgStatus = NETP_MSG_RECEIVED;
      
        /* Devalidate the fault noitify */
        if(NetMonitorPtr->AbsentFaultyEnable != NETP_ABS_FAULTY_DISABLE)
        {
          MsgTimeOut &= (u16)NETP_BCLR((u16)MsgIdx - (u16)Netp_StartScanRxMsg);
        }
      }
      
      /* The receipt of diagnostic message is enabled */
      if ((NetMonitorPtr->ComType & Netp_ComTypeRx) != 0U)
      {
        /* Check the indication flag and call, if configured, the indication callback */
        if( CAND_CheckRxMsgRdy((CAND_RxMsgName_t)MsgIdx) == TRUE )
        {
          if( NetMonitorPtr->IndCbk != NULL )
          {
            NetMonitorPtr->IndCbk();
          }
        }
      }
    }
    NetMonitorPtr++;
  }
}
#else
void NETP_RxEvtMgmt(void)
{
}
#endif

/**
 * @brief  Monitor the periodic messages to be sent
 * @note   Must be called @5ms (polling @ TIMER_BACKGROUND_MEDIUM)
 */
PRES_ResSts_t NETP_SendMsgReq(CAND_TxMsgName_t MsgName)
{
  const NETP_TxNetMonitor_t *NetTxMonitorPtr = (&NETP_TxNetMonitor[MsgName]);
  NETP_TxType_t TxType = NetTxMonitorPtr->TxType;
  PRES_ResSts_t ResSts = PRES_OK;
  
  if( (MsgName >= Netp_StartScanTxMsg) && (MsgName < Netp_StopScanTxMsg) && 
      ((TxType == NETP_TX_E) || (TxType == NETP_TX_PE)) )
  {
    if( (Netp_ComTypeTx & NetTxMonitorPtr->ComType) != 0u )
    {
#ifdef NETP_MTBE_STRATEGY
      if( (TxType == NETP_TX_PE) && (Netp_MtbeHndl[MsgName].Timer == 0) && 
          (Netp_MtbeHndl[MsgName].SendingEnable == TRUE) )
      {
        /* Reload Mtbe time */
        Netp_MtbeHndl[MsgName].Timer = NetTxMonitorPtr->Mtbe;   
        /* Notify the transmission request */
        Netp_TxMsgHndl[MsgName].SendReq = TRUE;
      }
      else if( TxType == NETP_TX_E )
      {
        /* Notify the transmission request */
        Netp_TxMsgHndl[MsgName].SendReq = TRUE;
      }
      else
      {
        /* Notify the error */
        ResSts = PRES_NOT_OK;
      }
#else        
      /* Notify the transmission request */
      Netp_TxMsgHndl[MsgName].SendReq = TRUE;
#endif
    }
    else
    {
      ResSts = PRES_BUSY;
    }
  }
  else
  {
    ResSts = PRES_PAR_NOT_OK;
  }
 
  return(ResSts);
}


PRES_ResSts_t NETP_SendDiagMsg(CAND_TxMsgName_t MsgName, uint8_t Dlc)
{
  const NETP_TxNetMonitor_t *NetTxMonitorPtr = (&NETP_TxNetMonitor[MsgName]);
  NETP_TxType_t TxType = NetTxMonitorPtr->TxType;
  PRES_ResSts_t ResSts = PRES_OK;
  
  if( (MsgName >= Netp_StartScanTxMsg) && (MsgName < Netp_StopScanTxMsg) && (TxType == NETP_TX_E) )
  {
    if( (Netp_ComTypeTx & NetTxMonitorPtr->ComType) != 0u )
    {
      /* Direct transmission for diagnostic message */
      if( CAND_SendMsg(MsgName, Dlc) != CAND_EVT_TX_SUCCESS )
      {
        ResSts = PRES_NOT_OK;
      }
    }
    else
    {
      ResSts = PRES_BUSY;
    }
  }
  else
  {
    ResSts = PRES_PAR_NOT_OK;
  }

  return(ResSts);
}


/**
 * @brief  Manage node mute condition
 * @return void
 */
void NETP_ManageNodeMute(void)
{
  bool_t ErrorPassiveSts;
  bool_t ErrorWarningSts;
  PRES_KeyStatus_t checkKey;
  
  checkKey = NETP_GetKeyStatus();

  if( (CAND_GetBusOffState() == FALSE) && (checkKey == KEYA_ON_STATUS) )
  {
    /* if NOT in bus off or crank */  
    ErrorPassiveSts = CAND_GetErrorPassiveState();
    ErrorWarningSts = CAND_GetErrorWarningeState();

    if(CAND_NetworkGetHwErrStatus() == CAND_HW_ACK_ERR)
    {
      if(Netp_NodeMuteErrCnt > 0u)
      {
        Netp_NodeMuteErrCnt--;
        
        if(Netp_NodeMuteErrCnt == 0u)
        {
          /*  */
          if((ErrorPassiveSts == TRUE) || (ErrorWarningSts == TRUE))
          {
            Netp_MuteDtcStatus = TRUE;
            Netp_NodeMuteErrCnt = NETP_MUTE_SILENCE_TIME;
            /* TODO PTFC: viene chiamata ogni tempo di validazione, 
             * si potrebbe chiamare solo una volta */
            NETP_MUTE_RECOVERY()
          }
        }
      }
      else
      {
      }
    }
    else
    {
      Netp_NodeMuteErrCnt = NETP_MUTE_SILENCE_TIME;
      Netp_MuteDtcStatus = FALSE;
    }
  }
  else
  {
    /* if bus off occurred, init MUTE sts */
    Netp_NodeMuteErrCnt = NETP_MUTE_SILENCE_TIME;
    /* Reset Node Mute Dtc Code and Symptom for specified network */
    Netp_MuteDtcStatus = FALSE;
  }
}



/**
 * @brief  Public function for Manage message received status
 * @return message received status
 * @retval PRES_MSG_NOT_RECEIVED
 * @retval PRES_NO_FAULT
 */
PRES_Fault_t NETP_GetMsgDiag(CAND_RxMsgName_t RxMsgName)
{
  PRES_Fault_t valueReturn;
  NETP_MsgStatus_t msgStatus;

  msgStatus = NETP_GetRxStatus(RxMsgName);

  if (msgStatus == NETP_MSG_RECEIVED)
  {
    valueReturn = PRES_NO_FAULT;
  }
  else if (msgStatus == NETP_MSG_NOT_RECEIVED)
  {
    valueReturn = PRES_MSG_NOT_RECEIVED;
  }
  else
  {
    valueReturn = PRES_NOT_TESTED;
  }

  return (valueReturn);
}


/**
 * @brief Align Diagnose network and DTC after a clear all DTC
 * @param none
 * @return void
 */
void NETP_ClearDtcEvent(void)
{
#ifdef NETP_TIMEOUT_SERVICE
  NETP_InitTimeout(NETP_CCT_APPL_MSG);
#endif

  /* MUTE management*/
  Netp_NodeMuteErrCnt = NETP_MUTE_SILENCE_TIME;
  Netp_MuteDtcStatus = FALSE;
  /* wire fail management */
  CAND_SetWireFailureState(FALSE);
}


/**
 * @brief Get rx status of a specific message id
 * @param RxMsgName
 * @return NETP_MsgStatus_t
 * @retval NETP_MSG_RECEIVED
 * @retval NETP_MSG_NOT_RECEIVED
 */
NETP_MsgStatus_t NETP_GetRxStatus(CAND_RxMsgName_t RxMsgName)
{
  return(Netp_RxStatus[RxMsgName].MsgStatus);
}

/**
 * @brief Enable rx message timeout when network management is ON
 * @param none
 * @return void
 */
void NETP_EnableRxMsgTOutMng(void)
{
  Netp_EnRxMsgToutMng = NETP_TOUT_MNG_ENABLE;
}


/**
 * @brief Disable rx message timeout when network management is OFF
 * @param none
 * @return void
 */
void NETP_DisableRxMsgTOutMng(void)
{
  Netp_EnRxMsgToutMng = NETP_TOUT_MNG_DISABLE;
}


/**
 * @brief To set communication control type rx (UDS service 28)
 * @param comt
 * @return void
 */
void NETP_SetCommCtrlTypeRx(NETP_ComType_t comt)
{
  Netp_ComTypeRx = comt;
}

/**
 * @brief To retrieve communication control type rx (UDS service 28)
 * @param none
 * @return NETP_ComType_t
 */
NETP_ComType_t NETP_GetCommCtrlTypeRx(void)
{
  return Netp_ComTypeRx;
}

/**
 * @brief To set communication control type tx (UDS service 28)
 * @param comt
 * @return void
 */
void NETP_SetCommCtrlTypeTx(NETP_ComType_t comt)
{
  Netp_ComTypeTx = comt;
}


/**
 * @brief To retrieve communication control type tx (UDS service 28)
 * @param none
 * @return NETP_ComType_t
 */
NETP_ComType_t NETP_GetCommCtrlTypeTx(void)
{
  return Netp_ComTypeTx;
}

/**
 * @brief To retrieve monitor status S_ON/S_OFF e.g. networg diag. inhibition
 * @param none
 * @return PRES_State_t
 */
PRES_State_t NETP_GetMonitorStatus(void)
{
  return (Netp_MonitorStatus);
}


void NETP_EnableRxTimeout(bool_t Enable)
{
  Netp_EnableRxTimeout = Enable;
}


void NETP_NotifyNetSts(NETP_NetStatus_t NetSts)
{
  Netp_NetStatus = NetSts;
}


/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

#ifdef NETP_TIMEOUT_SERVICE
/**
 * @brief Reset timeout struct
 * @param ComType message communication type of which timeout should be reset
 * @return void
 */
void NETP_InitTimeout(NETP_ComType_t ComType)
{
  u08 MsgIdx;
  const NETP_RxNetMonitor_t *NetMonitorPtr = NETP_RxNetMonitorPtr;

  /* Scan all RX messages configured */
  for(MsgIdx = Netp_StartScanRxMsg; MsgIdx < Netp_StopScanRxMsg; MsgIdx++)
  {
    if( ((ComType & NETP_CCT_APPL_MSG) & NetMonitorPtr->ComType) != 0U )
    {
      Netp_RxStatus[MsgIdx].ElapsedTime = NetMonitorPtr->RxMsgTimeOut;
      /* init message status */
      Netp_RxStatus[MsgIdx].MsgStatus = NETP_MSG_INIT_MONITOR;
    }
    NetMonitorPtr++;
  }
  
  TLRP_SetSlow(NETP_FirstTestTimer);
}
#endif

/**
 * @brief Get Mute status
 * @param none
 * @return bool_t
 * @retval TRUE if Mute DTC is present
 */
bool_t NETP_GetMuteStatus(void)
{
  return(Netp_MuteDtcStatus);
}


/**
 * @brief Get absent/faulty status for the specific node
 * @param NETP_Af_t the handle to be diagnosed (listed in NETP_cfgIf.h)
 * @return PRES_Fault_t
 * @retval PRES_MSG_NOT_RECEIVED if all monitored messages are not received
 * @retval PRES_MSG_FAULTY DLC error or missing at least one (but not at all) monitored message
 * @retval PRES_NO_FAULT no fault present
 */
PRES_Fault_t NETP_GetAbsentFaultyStatus(NETP_Af_t AbsFaulty)
{
  PRES_Fault_t ret_val;

  if((TLRP_GetSlow(NETP_FirstTestTimer)!= 0x0000u) ||
     (AbsFaulty >= NETP_ABS_FAULTY_DISABLE))
  {
    ret_val = PRES_NOT_TESTED;
  }
  else
  {
    switch(Netp_NetDiagnose[AbsFaulty].AbsentFaultySts)
    {
      case PRES_NO_FAULT:
        if(Netp_NodeAbsDiag(AbsFaulty) == TRUE)
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_MSG_NOT_RECEIVED;
        }
        else if(Netp_NodeFaultyDiag(AbsFaulty) == TRUE)
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_MSG_FAULTY;
        }
        else
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_NO_FAULT;
        }
        break;

      case PRES_MSG_NOT_RECEIVED:  /* absent */
        if (Netp_NodeAbsDiag(AbsFaulty) == FALSE)
        {
          if (Netp_NodeFaultyDiag(AbsFaulty) == FALSE)
          {
            Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_NO_FAULT;
          }
          else
          {
            Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_MSG_NOT_RECEIVED;
          }
        }
        else
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_MSG_NOT_RECEIVED;
        }
        break;

      case PRES_MSG_FAULTY:  /* faulty */
        if(Netp_NodeAbsDiag(AbsFaulty) == TRUE)
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_MSG_NOT_RECEIVED;
        }
        else if(Netp_NodeFaultyDiag(AbsFaulty) == FALSE)
        {
          Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_NO_FAULT;
        }
        else
        {
        }
        break;

      default:
        break;
    }

    ret_val = Netp_NetDiagnose[AbsFaulty].AbsentFaultySts;
  }

  return(ret_val);
}
/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief Init the pointer to TX/RX message frame structure according to DBC number
 * @param none
 * @return void
 */
static void Netp_InitPtrToMsgFrame(void)
{
#ifndef __CMMD_MULTI_DBC__
  /* Prepare the main pointers to Tx and Rx message structs */
  NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[0];
  NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[0];
#else
  /* Read the MSM Ecu type and coding it */ 
  /* Driver DBC = 1° DBC, Passenger DBC = 2° DBC */ 
  NETP_MsmEcuType = CAND_GetMsmEcuType();
  
  #if (CMMD_DBC_NMB == 2u)
    if( NETP_MsmEcuType == 0 )
    {
      NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[0];
      NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[0];
    }
    else if( NETP_MsmEcuType == 1 )
    {
      NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[CAND_DBC1_TX_MSG_NMB];
      NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[CAND_DBC1_RX_MSG_NMB];
    }
    else
    {
      /* ECU type don't exist */
    }
  #endif
  
  #if (CMMD_DBC_NMB == 3u)
    if( NETP_MsmEcuType == 0 )
    {
      NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[0];
      NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[0];
    }
    else if( NETP_MsmEcuType == 1 )
    {
      NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[CAND_DBC1_TX_MSG_NMB];
      NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[CAND_DBC1_RX_MSG_NMB];
    }
    else if( NETP_MsmEcuType == 2 )
    {
      NETP_TxNetMonitorPtr = &NETP_TxNetMonitor[CAND_DBC2_TX_MSG_NMB];
      NETP_RxNetMonitorPtr = &NETP_RxNetMonitor[CAND_DBC2_RX_MSG_NMB];
    }
    else
    {
      /* ECU type don't exist */
    }
  #endif
#endif
}


static void Netp_SetLimitToScan(void)
{
  Netp_StartScanTxMsg = CAND_GetStartScanTxMsg();
  Netp_StopScanTxMsg  = CAND_GetStopScanTxMsg();
  Netp_StartScanRxMsg = CAND_GetStartScanRxMsg();
  Netp_StopScanRxMsg  = CAND_GetStopScanRxMsg();
}

#ifdef NETP_TIMEOUT_SERVICE
/**
 * @brief Function used to build message absent, message faulty mask
 * @param none
 * @return void
 */
static void Netp_InitNabsFaultyMask(void)
{
  u08 MsgIdx;
  u08 AbsFaulty;
  const NETP_RxNetMonitor_t *NetMonitorPtr = NETP_RxNetMonitorPtr;


  for (AbsFaulty = 0U; AbsFaulty < (u08)NETP_ABS_FAULTY_DISABLE; AbsFaulty++)
  {
    Netp_NetDiagnose[AbsFaulty].Mask = 0U;
    Netp_NetDiagnose[AbsFaulty].AbsentFaultySts = PRES_NO_FAULT;
    Netp_NetDiagnose[AbsFaulty].MsgCnt = 0U;
  }

  for(MsgIdx = Netp_StartScanRxMsg; MsgIdx < Netp_StopScanRxMsg; MsgIdx++)
  {
    for (AbsFaulty = 0U; AbsFaulty < (u08)NETP_ABS_FAULTY_DISABLE; AbsFaulty++)
    {
      /* create message absent/faulty mask */
      /* for every timeout handler NETP_TOUT_MSG_x_HND there's a place in the mask */
      if(NetMonitorPtr->AbsentFaultyEnable == AbsFaulty)
      {
        Netp_NetDiagnose[AbsFaulty].Mask |= (u16)NETP_BSET((u16)MsgIdx - (u16)Netp_StartScanRxMsg);
        Netp_NetDiagnose[AbsFaulty].MsgCnt++;
      }
    }
    NetMonitorPtr++;
  }
}
#endif /* end NETP_TIMEOUT_SERVICE */


/**
 * @brief Get message absent status for the specific input handle
 * @param AbsFaulty is the current handle
 * @return return TRUE if all monitored messages are absent
 */
static bool_t Netp_NodeAbsDiag(NETP_Af_t AbsFaulty)
{
  bool_t ret_val;
  u16 MsgToutFiltered;
  u08 MsgIdx;
  u08 DlcCorrect;
  u08 i;

  DlcCorrect = 1U;
   
  /* Diagnose messages for the given handle, filter other messages */
  MsgToutFiltered = MsgTimeOut;
  for (i = 0U; i < NETP_ABS_FAULTY_DISABLE; i++)
  {
    if (i != (u08)AbsFaulty)
    {
      MsgToutFiltered &= ~Netp_NetDiagnose[i].Mask;
    }
  }

    /* check if some received messsage has wrong DLC */
  for(MsgIdx = Netp_StartScanRxMsg; (MsgIdx < Netp_StopScanRxMsg) && (DlcCorrect == 1U); MsgIdx++)
  {
    if ((u16)(1U << (u16)MsgIdx) & (Netp_NetDiagnose[AbsFaulty].Mask))
    {
      DlcCorrect = CAND_GetDlcCorrectFlag((CAND_RxMsgName_t)MsgIdx);
    }
  }

  if (Netp_NetDiagnose[AbsFaulty].MsgCnt == 1U)
  {
    /* only one monitored message */
    if ((MsgToutFiltered == Netp_NetDiagnose[AbsFaulty].Mask) && (DlcCorrect == 1U))
    {
      ret_val = TRUE;
    }
    else
    {
      ret_val = FALSE;
    }
  } 
  else /* more than one monitored messages */
  {
    if(MsgToutFiltered == Netp_NetDiagnose[AbsFaulty].Mask)
    {
      /* return MSG_NOT_RECEIVED if all monitored messages are not received */
      ret_val = TRUE;
    }
    else
    {
      ret_val = FALSE;
    }
  }

  return(ret_val);
}

/**
 * @brief Get message faulty status for the specific input handle
 * @param AbsFaulty is the current handle
 * @return return TRUE if SOME monitored messages are absent (not all) or DLC is not correct
 */
static bool_t Netp_NodeFaultyDiag(NETP_Af_t AbsFaulty)
{
  bool_t ret_val;
  u08 DlcCorrect;
  u08 MsgIdx;
  u16 MsgToutFiltered;
  u08 i;

  DlcCorrect = 1U;
  
  /* Diagnose messages for the given handle, filter other messages */
  MsgToutFiltered = MsgTimeOut;
  for (i = 0U; i < NETP_ABS_FAULTY_DISABLE; i++)
  {
    if (i != (u08)AbsFaulty)
    {
      MsgToutFiltered &= ~Netp_NetDiagnose[i].Mask;
    }
  }

  /* check if some received messsage has wrong DLC */
  for(MsgIdx = Netp_StartScanRxMsg; (MsgIdx < Netp_StopScanRxMsg) && (DlcCorrect == 1U); MsgIdx++)
  {
    if ((u16)(1U << (u16)MsgIdx) & (Netp_NetDiagnose[AbsFaulty].Mask))
    {
      DlcCorrect = CAND_GetDlcCorrectFlag((CAND_RxMsgName_t)MsgIdx);
    }
  }

  if (Netp_NetDiagnose[AbsFaulty].MsgCnt == 1U)
  {
    /* only one monitored message */
    if ((MsgToutFiltered == Netp_NetDiagnose[AbsFaulty].Mask) && (DlcCorrect == 0U))
    {
      ret_val = TRUE;
    }
    else
    {
      ret_val = FALSE;
    }
  } 
  else /* more than one monitored messages */
  {
    if (((MsgToutFiltered & Netp_NetDiagnose[AbsFaulty].Mask) != 0U) &&
           (MsgToutFiltered != Netp_NetDiagnose[AbsFaulty].Mask))
    {
      /* return MSG_FAULTY if some messages are not received (not all) or DLC of one message is wrong */
      ret_val = TRUE;
    }
    else
    {
      ret_val = FALSE;
    }
  }
  
  return(ret_val);
}
#endif /* end __NETP_IS_PRESENT__ */

/*______ E N D _____ (NETP.c) ________________________________________________*/
