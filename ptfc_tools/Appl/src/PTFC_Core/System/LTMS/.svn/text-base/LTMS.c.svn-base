/**
 * @file LTMS.c
 * @brief Configuration of the LIN transceiver
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/


#define LTMS_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LTMS.h"
#include "LTMS_config.h"

/* Module inhibition filter */
#ifdef __LTMS_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

static LTMS_Status_t Ltms_Status;   /* Status of LTMS layer */

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/* Interrupt timer for state transitions */
static uint16_t Ltms_INTTM02_Isr(void);    

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief Put LTMS in power off
 * @return None
 * @note
 */
void LTMS_PwrOff(void)
{
  /* Deactivates the LTMS driver */
  LTMS_GoToSleep(UARTD_CHN_HND);
}

/**
 * @brief This function Initializes the LTMS driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void LTMS_Init(void)
{
  /* Set into POWER_ON status (pre start-up)*/
  Ltms_Status = LTMS_POWER_ON;
    
  /* Set interrupts */
  /* Set the callback for interrupt vector INTTM02 */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTTM02, (ISRD_EvtCbk_t)Ltms_INTTM02_Isr);
  
  /* Enable transceiver */
  LTMS_WakeUp(UARTD_CHN_HND);
}

/**
 * @brief This function activates the LTMS driver.
 * @param LIN channel number
 * @return void
 */
void LTMS_WakeUp(uint8_t chn_hnd)
{  
  /* Start up transceiver */
  DIOD_SetLevel(DIOD_LIN_SLP, L_HIGH);
  
  /* Change state */
  Ltms_Status = LTMS_TO_NORMAL;
  
  /* Set up timer timeout */
  TAU0_Channel2_ChangeTimerCondition(LTMS_TIMEOUT_GOTONORM_COUNT);
  
  /* Start count */
  TAU0_Channel2_Start();
}

/**
 * @brief This function deactivates the LTMS driver.
 * @param LIN channel number
 * @return void
 */
void LTMS_GoToSleep(uint8_t chn_hnd)
{
  /* Shut off transceiver */
  DIOD_SetLevel(DIOD_LIN_SLP, L_LOW);
  
  /* Change state */
  Ltms_Status = LTMS_TO_SLEEP;
  
  /* Set up timer timeout */
  TAU0_Channel2_ChangeTimerCondition(LTMS_TIMEOUT_GOTOSLEEP_COUNT);
  
  /* Start count */
  TAU0_Channel2_Start();  
}

/**
 * @brief This function returns the status of the module.
 * @param LIN channel number
 * @return LTMS_Status_t
 */
LTMS_Status_t LTMS_GetStatus(uint8_t chn_hnd)
{
  return Ltms_Status;  
}

/* ISR */
static uint16_t Ltms_INTTM02_Isr(void)
{
  /* Stop timer */
  TAU0_Channel2_Stop();
  
  /* Change status */
  switch (Ltms_Status)
  {
    case LTMS_TO_SLEEP:
      Ltms_Status = LTMS_SLEEP;
      break;
    case LTMS_TO_NORMAL:
      Ltms_Status = LTMS_NORMAL;
      break;
    default:
      /* Should not be here */
      break;
  }
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTTM02));
}

#endif /* end __LTMS_IS_PRESENT__ */

/*______ E N D _____ (LTMS.c) ________________________________________________*/
