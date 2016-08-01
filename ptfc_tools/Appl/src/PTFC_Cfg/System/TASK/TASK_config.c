/* ============================================================================ **
**                           B I T R O N    S p A                               **
** ============================================================================ **
**                      +++++++++++++++++++++++++++++                           **
**           Modulo:    +    Task.c                 +                           **
**                      +++++++++++++++++++++++++++++                           **
**                                                                              **
**   Progetto :          SIRENA PQ35                                            **

**   Descrizione                                                                **
**     Il modulo contiene le chiamate di tutti i task del sistema.
** ============================================================================ */
/*
|-------------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-------------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ---------------------------------------
| GB           Giuseppe Barberio         Bitron S.p.A.
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Ver  Author  Description
| ------------  ---  ------  ---------------------------------------------------
| 24 july 2015  1.1  GB      Bug fix for test norm 7z0142/01 - 7_2_11: WAKE-UP 
|                            SLEEP process. Redmine #1414.
|                            Bug fix for OP_1 present in document 
|                            OIL_NAG_NAP_F151M_20150710_FE.xlsx. Redmine #848.
|-------------------------------------------------------------------------------
*/
#define GLOBAL_TASK

/* =======================      include         =============================*/

#include "TASK_if.h"

//#define OVERLOAD_CPU
#if defined OVERLOAD_CPU
  static void overloadCPU(void);
#endif
static void TaskBackgroundMult1ms_10t(void);
static void TaskBackgroundMult5ms_4t(void);
static void TaskBackgroundMult5ms_10t(void);
static void TaskBackgroundMult100ms_10t(void);


// ---------------------------------------------------------------------------

#ifdef FOREGROUND_TASK_ENABLED
// periodo di chiamata: 1ms
void TaskForegroundFast(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
#ifdef __NETP_IS_PRESENT__
    NETP_ApplMsgSendingMgmt();
#endif
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
#ifdef __NETP_IS_PRESENT__
    NETP_ApplMsgSendingMgmt();
#endif
  }
  else
  {
    /* None scheduling */
  }
}

// ---------------------------------------------------------------------------
// periodo di chiamata: 5 ms
void TaskForegroundMedium(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
  }
  else
  {
    /* None scheduling */
  }
}

// ---------------------------------------------------------------------------
// periodo di chiamata: 10ms
void TaskForegroundSlow(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
  }
  else
  {
    /* None scheduling */
  }
}
#endif /* end FOREGROUND_TASK_ENABLED */

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// periodo di chiamata: 1ms
void TaskBackgroundFast(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
#ifdef __APPL_IS_PRESENT__
    /* Insert here an applicative handler */
#endif
#ifdef __TLRP_IS_PRESENT__
    TLRP_MgmFast();
#endif
#ifdef __MUXC_IS_PRESENT__
    /* Recall AD State machine each 1ms */
    MUXC_Mgm();
#endif
#ifdef __ADCC_IS_PRESENT__
    /* Recall AD State machine each 1ms */
    ADCC_RunManager();
#endif
#ifdef __IPOC_IS_PRESENT__
    IPOC_CounterMgm();
#endif
#ifdef __PWMC_IS_PRESENT__
    /* PWM Sw manager */
    PWMC_Mgm();
#endif
#ifdef __AVGP_IS_PRESENT__
    /* Gestione Input analogici mediati */
    AVGP_Mgm();
#endif
#ifdef __DINP_IS_PRESENT__
    /* Gestione Input debounce */
    DINP_Mgm();
#endif
#ifdef __EEPP_IS_PRESENT__
    /* Gestione EEPROM */
    EEPP_Mgm();
#endif
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
#ifdef __EEPP_IS_PRESENT__
    /* Gestione EEPROM */
    EEPP_Mgm();
#endif
#ifdef __TLRP_IS_PRESENT__
    TLRP_MgmFast();
#endif
#ifdef __MUXC_IS_PRESENT__
    /* Recall AD State machine each 1ms */
    MUXC_Mgm();
#endif
#ifdef __ADCC_IS_PRESENT__
    /* Recall AD State machine each 1ms */
    ADCC_RunManager();
#endif
#ifdef __DINP_IS_PRESENT__
    /* Gestione Input debounce */
    DINP_Mgm();
#endif
  }
  else
  {
    /* None scheduling */
  }
  
  /* Spreading task - Call every 1ms a routines group with a 10 ms period */
  TaskBackgroundMult1ms_10t();
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// periodo di chiamata: 5ms
void TaskBackground5ms(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
#ifdef __APPL_IS_PRESENT__
    /* Insert here an applicative handler */
#endif
#ifdef __DIAC_IS_PRESENT__
    /* Gestione Input digitalizzati */
    DIAC_Mgm(); /* WARNING: enable if thresholds ratio are used */
#endif
#ifdef __DIAGC_IS_PRESENT__
    /* Electrical diagnosis scheduler */
    DIAGC_Mgm();
#endif
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
#ifdef __DIAC_IS_PRESENT__
    /* Gestione Input digitalizzati */
    DIAC_Mgm(); /* WARNING: enable if thresholds ratio are used */
#endif

#ifdef __NWMA_IS_PRESENT__
    NWMA_FsmMgmt();
#endif
  }
  else
  {
    /* None scheduling */
  }

  /* Spreading task - Call every 5ms a routines group with a 20 ms period */
  TaskBackgroundMult5ms_4t();
  /* Spreading task - Call every 5ms a routines group with a 50 ms period */
  TaskBackgroundMult5ms_10t();
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// periodo di chiamata: 100ms
void TaskBackground100ms(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
#ifdef __TLRP_IS_PRESENT__
    TLRP_MgmSlow();
#endif
#ifdef __SNSP_IS_PRESENT__
    SNSP_Mgm ();   //L.B.
#endif
#ifdef __CAND_IS_PRESENT__
    CAND_ManageCANError();
#endif
#ifdef __MEMD_IS_PRESENT__
    MEMD_StackCheck();
#endif
#ifdef __EXMMA_IS_PRESENT__
    EXMMA_Mgm();
#endif
#ifdef __HEATA_IS_PRESENT__
    HEATA_Mgm ();   //L.B.
#endif
#ifdef __FANA_IS_PRESENT__
    FANA_Mgm ();
#endif
#ifdef __UARTD_IS_PRESENT__
    /* LIN check for UARTD short circuit */
    UARTD_SetShortCircuitError(UARTD_CHN_HND);    
#endif
#ifdef __DISPA_IS_PRESENT__
  DISPA_SlowMgm();
#endif
#ifdef __DOIFC_IS_PRESENT__
  DOIFC_Mgm();
#endif
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
#ifdef __TLRP_IS_PRESENT__
    TLRP_MgmSlow();
#endif
#ifdef __CAND_IS_PRESENT__
    CAND_ManageCANError();
#endif
#ifdef __MEMD_IS_PRESENT__
    MEMD_StackCheck();
#endif
  }
  else
  {
    /* None scheduling */
  }

  /* Spreading task - Call every 100ms a routines group with a 1 second period */
  TaskBackgroundMult100ms_10t();
}
// -----------------------------------------------------------------------------

/* periodo di chiamata: ad evento */
void TaskEvent(void)
{
  /* Manage Rx message events */
  NETP_RxEvtMgmt();

  /* Manage Tx message events */
  NETP_TxEvtMgmt();

#ifdef __CAND_IS_PRESENT__
  #ifdef __TP_IS_PRESENT__
    #ifdef __UDSA_IS_PRESENT__
      /* Event Diagnostic message ready : UDS decoding */
      if (TP_CheckDiagnosticDataReady() == TRUE)
      {
        TP_ResetDiagnosticDataReady();
        UDSA_Decoding(&Diag_Requeste[0], Diag_Requeste_Ln);
      }
    #endif
  #endif
#endif
}


// -----------------------------------------------------------------------------
// periodo di chiamata: 10ms
static void TaskBackgroundMult1ms_10t(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();
  static u08 TaskBckgndMult1ms_10tCnt = 0u;

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
    switch (TaskBckgndMult1ms_10tCnt)
    {
      case 0u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __NWMA_IS_PRESENT__
        NWMA_FsmMgmt();
#endif
        break;

      case 1u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __NETP_IS_PRESENT__
        NETP_MonitorRxPeriod();
#endif
        break;

      case 2u:
#ifdef __TP_IS_PRESENT__
        TpTx();
#endif
        TaskBckgndMult1ms_10tCnt++;
        break;

      case 3u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __NETP_IS_PRESENT__
        NETP_PeriodicMsgMgmt();
#endif
        break;

      case 4u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __DISPA_IS_PRESENT__
        /* Battery disconnection check */
        DISPA_BatteryUnplugMonitor();
#endif
        break;

      case 5u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __DISPA_IS_PRESENT__
        DISPA_FastMgm();
#endif
        break;

      case 6u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __KEYA_IS_PRESENT__
        /* KEYA MngKeyStatus removed from scheduler since it is executed as a CAN message callback */
#endif
        break;

      case 7u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __MOTP_IS_PRESENT__
        MOTP_Mgm();
#endif
      break;

      case 8u:
        TaskBckgndMult1ms_10tCnt++;
#ifdef __FVMP_IS_PRESENT__
      /* Gestione validazione/svalidazione fault */
      FVMP_Mgm();
#endif
        break;

      case 9u:
#ifdef __LINP_IS_PRESENT__
      /* Dummy LIN transmission */
      LINP_SchedulerTick(UARTD_CHN_HND);      
#endif
        /* Reset switch case */
        TaskBckgndMult1ms_10tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult1ms_10tCnt > 9u)
        {
          TaskBckgndMult1ms_10tCnt = 0u;
        }
        break;
    }
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
    switch (TaskBckgndMult1ms_10tCnt)
    {
      case 0u:
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
      case 8u:
        TaskBckgndMult1ms_10tCnt++;
        break;

      case 9u:
        /* Reset switch case */
        TaskBckgndMult1ms_10tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult1ms_10tCnt > 9u)
        {
          TaskBckgndMult1ms_10tCnt = 0u;
        }
        break;
    }
  }
  else
  {
    /* None scheduling */
  }
}
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// periodo di chiamata: 5ms
static void TaskBackgroundMult5ms_4t(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();
  static u08 TaskBckgndMult5ms_4tCnt = 0u;

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
    switch(TaskBckgndMult5ms_4tCnt)
    {
      case 0u:
        TaskBckgndMult5ms_4tCnt++;
        /* Refresh internal and external watchdog */
        LPMS_RefreshAllWatchDog()
        break;

      case 1u:
        TaskBckgndMult5ms_4tCnt++;
        #ifdef __HBRGC_IS_PRESENT__
          HBRGC_Mgm();
        #endif
        break;

      case 2u:
        TaskBckgndMult5ms_4tCnt++;
        break;

      case 3u:
        /* Reset switch case */
        TaskBckgndMult5ms_4tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult5ms_4tCnt > 3u)
        {
          TaskBckgndMult5ms_4tCnt = 0u;
        }
        break;
    }
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
    switch(TaskBckgndMult5ms_4tCnt)
    {
      case 0u:
        /* Refresh internal and external watchdog */
        LPMS_RefreshAllWatchDog()
        TaskBckgndMult5ms_4tCnt++;
        break;

      case 1u:
      case 2u:
        TaskBckgndMult5ms_4tCnt++;
        break;

      case 3u:
        /* Reset switch case */
        TaskBckgndMult5ms_4tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult5ms_4tCnt > 3u)
        {
          TaskBckgndMult5ms_4tCnt = 0u;
        }
        break;
    }
  }
  else
  {
    /* None scheduling */
  }
}

// -----------------------------------------------------------------------------

// periodo di chiamata: 5ms
static void TaskBackgroundMult5ms_10t(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();
  static u08 TaskBckgndMult5ms_10tCnt = 0u;

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
    switch(TaskBckgndMult5ms_10tCnt)
    {
      case 0u:
        TaskBckgndMult5ms_10tCnt++;
        NWMA_DllErrorMgmt();
        break;
      case 1u:
        /* 24 july 2015 - Giuseppe Barberio
           bug fix for test norm 7z0142/01 - 7_2_11: WAKE-UP SLEEP process.
           Redmine #1414                                                      */
		TaskBckgndMult5ms_10tCnt++;
        #ifdef __DISPA_IS_PRESENT__
          DISPA_NwmNotification();
        #endif
        break;
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
      case 8u:
        TaskBckgndMult5ms_10tCnt++;
        break;

      case 9u:
        /* Reset switch case */
        TaskBckgndMult5ms_10tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult5ms_10tCnt > 9u)
        {
          TaskBckgndMult5ms_10tCnt = 0u;
        }
        break;
    }
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
    switch(TaskBckgndMult5ms_10tCnt)
    {
      case 0u:
        /* 24 july 2015 - Giuseppe Barberio
        bug fix for test norm 7z0142/01 - 7_2_11: WAKE-UP SLEEP process.
        Redmine #1414                                                      */
		TaskBckgndMult5ms_10tCnt++;
        #ifdef __DISPA_IS_PRESENT__
          DISPA_NwmNotification();
        #endif
        break;
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
      case 8u:
        TaskBckgndMult5ms_10tCnt++;
        break;

      case 9u:
        /* Reset switch case */
        TaskBckgndMult5ms_10tCnt = 0u;
        break;

      default:
        if (TaskBckgndMult5ms_10tCnt > 9u)
        {
          TaskBckgndMult5ms_10tCnt = 0u;
        }
        break;
    }
  }
  else
  {
    /* None scheduling */
  }
}

// periodo di chiamata: 100 ms
static void TaskBackgroundMult100ms_10t(void)
{
  /* Read the Low Power module state */
  LPMS_FsmState_t LpwState = LPMS_GetFsmState();
  static u08 TaskBckgndMult100ms_10tCnt = 0u;

  /* System in run */
  if( LpwState == LPMS_RUN )
  {
    switch(TaskBckgndMult100ms_10tCnt)
    {
      case 0u:
        TaskBckgndMult100ms_10tCnt++;
        HEATA_ManageTimer_1s();
        break;
      case 1u:
      case 2u:
      case 3u:
      case 4u:
      case 5u:
      case 6u:
      case 7u:
      case 8u:
        TaskBckgndMult100ms_10tCnt++;
        break;
      case 9u:
        /* Reset switch case */
        TaskBckgndMult100ms_10tCnt = 0u;
        break;
      default:
        if (TaskBckgndMult100ms_10tCnt > 9u)
        {
          TaskBckgndMult100ms_10tCnt = 0u;
        }
        break;
    }
  }
  /* System in pseudo-run */
  else if( LpwState == LPMS_PSEUDO_RUN )
  {
    switch(TaskBckgndMult100ms_10tCnt)
        {
          case 0u:
          case 1u:
          case 2u:
          case 3u:
          case 4u:
          case 5u:
          case 6u:
          case 7u:
          case 8u:
            TaskBckgndMult100ms_10tCnt++;
            break;
          case 9u:
            /* Reset switch case */
            TaskBckgndMult100ms_10tCnt = 0u;
            break;
          default:
            if (TaskBckgndMult100ms_10tCnt > 9u)
            {
              TaskBckgndMult100ms_10tCnt = 0u;
            }
            break;
        }
  }
  else
  {
    /* None scheduling */
  }
}
// -----------------------------------------------------------------------------
