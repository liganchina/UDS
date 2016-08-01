/******************************************************************************/
/** @file       LPMS_config.c                                                 */
/** @title      Analog Digital Converter Driver                               */
/** @brief      This file contain all configuration routines of ADCD module   */
/**             for user settings. This file is developed for Renesas RL78    */
/**             family - micro R5F10AGFLFB/F13. The requirement used for this */
/**             driver is the chapter 12 of the relative hw datasheet(v2.0).  */
/** @date       21/07/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 21/07/2014 0.1  CC      First draft. For this first release will
|                         be not implmented:
|                         - the SNOOZE mode function management (TODO SGR)
|                         - the TEST mode (TODO SGR)
|                         - the HW trigger mode is partially implemented then
|                           for now isn't usable (TODO SGR)
|-----------------------------------------------------------------------------
| 12/02/2015 1.1  CC      Introduced the routine Lpms_CheckWakeupSource
|-----------------------------------------------------------------------------
*/

#define LPMS_CFGIF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LPMS.h"
#include "LPMS_config.h"
#include "TASK_if.h"

/*______ L O C A L - D E F I N E _____________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

#define Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY     (3400u)
#define Lpms_50MS_DELAY                       (50u)

/*______ L O C A L - D A T A _________________________________________________*/

static LPMS_MsmEcuType_t   Lpms_MsmEcuType;
static LPMS_MsmEquipment_t Lpms_MsmEquipment;

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static void Lpms_MsmEcuTypeCoding(void);
static void Lpms_CheckWakeupSource(void);
static void Lpms_MsmEquipmentCoding(void);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


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
 * @return None
 */
void LPMS_InitEvtCbk(void)
{
  /* Refresh all watchdog */
  LPMS_RefreshAllWatchDog()
    
  /* MSM Ecu type coding */
  Lpms_MsmEcuTypeCoding();

  /* System layer routines */
  SYSM_Init();

  /* Driver layer routines */
  DRVD_Init();
  
  /* Control layer routines */
  CTRL_Init();
  
  /* MSM Equipment coding */
  Lpms_MsmEquipmentCoding();

  /* Presentation layer routines */
  PRES_Init();
  
  /* Application layer routines */
  APPL_Init();
  
  /* Refresh all watchdog */
  LPMS_RefreshAllWatchDog()
}

#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
/**
 * @brief Sleep routine for PieZO presentation module used for transition
 *        run --> sleep (low power mode)
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_PseudoInitEvtCbk(void)
{
  uint16_t PwrDelay;
  
  /* Enable the power supply for uC */
  (void)DIOD_SetLevel(DIOD_5V_En, L_HIGH);

  /* Enable the power supply for hw keyboards */
  (void)DIOD_SetLevel(DIOD_KeyEN, L_HIGH);/*  TODO COBRA: verificare se è necessario attivarla in PR */


  /* Refresh all watchdog */
  LPMS_RefreshAllWatchDog()

  /* Delay 4ms @ 24MHz (OPTIMIZATION HIGH) */
  for(PwrDelay = 0U; PwrDelay < (4U*Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY); PwrDelay++)
  {
    NOP();
  }

  /* Refresh all watchdog */
  LPMS_RefreshAllWatchDog()

  /* MSM Ecu type coding */
  Lpms_MsmEcuTypeCoding();

  /* Check the wakeup source and request a state transition to network management */
  Lpms_CheckWakeupSource();

  /* System layer routines */
  SYSM_PseudoInit();

  /* Driver layer routines */
  DRVD_PseudoInit();
  
  /* Control layer routines */
  CTRL_PseudoInit();

  /* Presentation layer routines */
  PRES_PseudoInit();
  
  /* Application layer routines */
  APPL_PseudoInit();
  
  /* Refresh all watchdog */
  LPMS_RefreshAllWatchDog()
}
#endif

/**
 * @brief Routine called for the transition RUN --> POWER_OFF
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_RunPwrOffEvtCbk(void)
{
  uint16_t WdCnt;
  uint8_t  shutdownDelay = 0U;
  
  /* Suspend the system tasks */
#ifdef FOREGROUND_TASK_ENABLED
  SLRS_FrgrndSuspendTask();
#endif
  SLRS_BckgrndSuspendTask();

  /* Application layer routines */
  APPL_RunPwrOff();
  
  /* Presentation layer routines */
  PRES_RunPwrOff();
  
  /* Control layer routines */
  CTRL_RunPwrOff();

  /* Disable the +5s power supply */
  (void)DIOD_SetLevel(DIOD_KeyEN, L_LOW);
  /* Disable the 7.5V power supply */
  (void)DIOD_SetLevel(DIOD_7V5_En, L_LOW);

  /* WARNING: Before put the CAN transceiver in sleep mode it is necessary wait
   *  the stabilization of +Key voltage to avoid a spurious wake up pulse that
   *  causes a cyclic restart of ECU.
   */
  
  /* Wait the +KeyEN discharge */  
  while(shutdownDelay < Lpms_50MS_DELAY)
  {
    /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
    for(WdCnt = 0U; WdCnt < Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY; WdCnt++)
    {
      NOP();
    }
    shutdownDelay++;
    /* Refresh internal watchdog */
    LPMS_RefreshAllWatchDog()
  }

  /* Driver layer routines */
  DRVD_RunPwrOff();
  
  /* System layer routines */
  SYSM_RunPwrOff();

  /* Disable the power supply for uC */
  (void)DIOD_SetLevel(DIOD_5V_En, L_LOW);
  
  /* Wait the uC killing */
  while(1)
  {
    /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
    for(WdCnt = 0U; WdCnt < Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY; WdCnt++)
    {
      NOP();
    }
    /* Refresh internal watchdog */
    LPMS_RefreshInternalWatchDog();
  }
}

/**
 * @brief Routine called for the transition PSEUDO_RUN --> POWER_OFF
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_PseudoRunPwrOffEvtCbk(void)
{
  uint16_t WdCnt;
  uint8_t  shutdownDelay = 0U;

  /* Suspend the system tasks */
#ifdef FOREGROUND_TASK_ENABLED
  SLRS_FrgrndSuspendTask();
#endif
  SLRS_BckgrndSuspendTask();

  /* Application layer routines */
  APPL_PseudoRUNPwrOff();

  /* Presentation layer routines */
  PRES_PseudoRUNPwrOff();

  /* Control layer routines */
  CTRL_PseudoRUNPwrOff();

  /* Disable the +5s power supply */
  (void)DIOD_SetLevel(DIOD_KeyEN, L_LOW);
  /* Disable the 7.5V power supply */
  (void)DIOD_SetLevel(DIOD_7V5_En, L_LOW);

  /* WARNING: Before put the CAN transceiver in sleep mode it is necessary wait
   *  the stabilization of +Key voltage to avoid a spurious wake up pulse that
   *  causes a cyclic restart of ECU.
   */

  /* Wait the +KeyEN discharge */
  while(shutdownDelay < Lpms_50MS_DELAY)
  {
    /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
    for(WdCnt = 0U; WdCnt < Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY; WdCnt++)
    {
      NOP();
    }
    shutdownDelay++;
    /* Refresh internal watchdog */
    LPMS_RefreshAllWatchDog()
  }

  /* Driver layer routines */
  DRVD_PseudoRUNPwrOff();

  /* System layer routines */
  SYSM_PseudoRUNPwrOff();

  /* Disable the power supply for uC */
  (void)DIOD_SetLevel(DIOD_5V_En, L_LOW);

  /* Wait the uC killing */
  while(1)
  {
    /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
    for(WdCnt = 0U; WdCnt < Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY; WdCnt++)
    {
      NOP();
    }
    /* Refresh internal watchdog */
    LPMS_RefreshInternalWatchDog();
  }
}

#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
/**
 * @brief Wakeup routine for PieZO presentation module used for transition
 *        sleep (low power mode) --> run
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_WakeupEvtCbk(void)
{
  /* Driver layer routines */
  /* XYZD_WakeUp(); */
  /* Control layer routines */
  /* XYZC_WakeUp(); */
  /* Presentation layer routines */
  /* XYZP_WakeUp(); */
  /* Application layer routines */
  /* XYZA_WakeUp(); */
}
#endif

#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
/**
 * @brief Sleep routine for PieZO presentation module used for transition
 *        run --> sleep (low power mode)
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_SleepEvtCbk(void)
{
  /* Application layer routines */
  /* XYZA_Sleep(); */
  /* Presentation layer routines */
  /* XYZP_Sleep(); */
  /* Control layer routines */
  /* XYZC_Sleep(); */
  //ADCC_Sleep();
  /* Driver layer routines */
  /* XYZD_Sleep(); */
}
#endif

#if (LPMS_FSM_SUBSET == LPMS_FULL_FSM_SUBSET)
/**
 * @brief Sleep routine for PieZO presentation module used for transition
 *        run --> sleep (low power mode)
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_LpPseudoWakeupEvtCbk(void)
{
  /* Driver layer routines */
  /* XYZD_LpPseudoWakeUp(); */
  /* Control layer routines */
  ADCC_LpPseudoWakeUp();
  /* Presentation layer routines */
  /* XYZP_LpPseudoWakeUp(); */
  /* Application layer routines */
  /* XYZA_LpPseudoWakeUp(); */
}
#endif

#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
/**
 * @brief Sleep routine for PieZO presentation module used for transition
 *        run --> sleep (low power mode)
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_PrPseudoWakeupEvtCbk(void)
{
  /* Disable all interrupts */  
  DI();
  LPMS_RefreshAllWatchDog()

  /* System layer routines */
  SYSM_PrPseudoWakeup();
      
  /* Driver layer routines */
  DRVD_PrPseudoWakeup();
  
  /* Control layer routines */
  CTRL_PrPseudoWakeup();
  
  /* MSM Equipment coding */
  Lpms_MsmEquipmentCoding();
  
  /* Presentation layer routines */
  PRES_PrPseudoWakeup();
  
  /* Application layer routines */
  APPL_PrPseudoWakeup();
  
  LPMS_RefreshAllWatchDog()
  /* Enable all interrupts */
  EI();
}
#endif

#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
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
void LPMS_LowPowerManager(void)
{
}
#endif

/**
 * @brief Return the ECU type refer to Memo Seat Module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return LPMS_MsmEcuType_t
 * @retval LPMS_MSM_ECU_DRIVER is the ECU of the driver seat
 * @retval LPMS_MSM_ECU_PASSENGER is the ECU of the passenger seat
 */
LPMS_MsmEcuType_t LPMS_GetMsmEcuType(void)
{
  return(Lpms_MsmEcuType);
}

/**
 * @brief Return the Memo Seat Module equipment
 *
 * @param [in] None
 * @param [out] None
 *
 * @return LPMS_MsmEquipment_t
 * @retval LPMS_MSM_LUXURY
 * @retval LPMS_MSM_PERFORMANCE
 * @retval LPMS_MSM_PREMIUM
 * @retval LPMS_MSM_BASE
 */
LPMS_MsmEquipment_t LPMS_GetMsmEquipment(void)
{
  return(Lpms_MsmEquipment);
}

/**
 * @brief Callback to notify the power supply +5s is stabilized
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void LPMS_PwSupply5sCbk(void)
{
  /* Not used for this project */
}


/*______ L O C A L - F U N C T I O N S _______________________________________*/

/**
 * @brief Read the ECU type pin to code the ECU driver or passenger
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
static void Lpms_MsmEcuTypeCoding(void)
{

}

/**
 * @brief Check the CAN RxD pin do select the wakeup source for F151M project.
 * By the wakeup source information it request to NWMA module a transition in
 * NET_CHECK for CAN source or a transition in NET_ON for EEP source.
 * The possible wakeup source are:
 * @li Network CAN
 * @li Easy Entry push button
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
static void Lpms_CheckWakeupSource(void)
{
/* TODO_CC - da controllare il livello di tensione che si legge sull'RxD
   del transceiver High Speed quando si chiama questa routine */
#if 0
  /* The CAN bus in sleep so the wakeup source is the EEP bush button */
  if( CAND_GetBusWakeUp() == 0x00 )
  {
    /* Wakeup source is the EEP bush button */
    (void)NWMA_NmStateReq(NWMA_NET_ON_REQ);
  }
  else
  {
    /* If the wakeup source is the network CAN or 
     isn't possible get the information, request a NET_CHECK transition */
    (void)NWMA_NmStateReq(NWMA_NET_CHECK_REQ);
  }
#else
  (void)NWMA_NmStateReq(NWMA_NET_CHECK_REQ);
#endif
}




static void Lpms_MsmEquipmentCoding(void)
{
  uint16_t WdCnt;

  /* Coding pins are ANALOG: */
  //ADCC_StartConversionRun(0U);

  /* Delay 1ms @ 24MHz (OPTIMIZATION HIGH) */
  for(WdCnt = 0U; WdCnt < Lpms_24MHZ_OPTIM_HIGH_1MS_DELAY; WdCnt++)
  {
    /* Refresh internal watchdog */
    LPMS_RefreshInternalWatchDog();
  }

  /* TODO COBRA: Codificare i livelli ...*/
#if 0
   if (ADCC_Get...(Chan...) == xxxx)
  {
    Lpms_MsmEquipment = LPMS_MSM_LUXURY;
  }
  else
  {
    Lpms_MsmEquipment = LPMS_MSM_PERFORMANCE;
  }
#endif

}

/*______ E N D _____ (LPMS_config.c) _________________________________________*/
