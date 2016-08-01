/**
 * @file LTMS_if.h
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

#ifndef LTMS_IF_H_
#define LTMS_IF_H_

/* Layer interface declaration */
#ifdef LTMS_IF_OWNER
 #define LTMS_EXTERN
#else
 #define LTMS_EXTERN  extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LTMS_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/
/* Machine state of transceiver */
typedef enum
{
  LTMS_POWER_ON = 0,
  LTMS_NORMAL,                                
  LTMS_STANDBY,     /* Auto if local or remote WakeUp occurs during sleep */
  LTMS_SLEEP,       /* Sleep state */
  LTMS_TO_SLEEP,    /* Transition state from Normal mode into Sleep mode */
  LTMS_TO_NORMAL,   /* Transition state from Sleep mode into Normal mode */
  LTMS_MAX_STATUS
} LTMS_Status_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


/**
 * @brief Put LTMS in power off
 * @return None
 * @note
 */
LTMS_EXTERN void LTMS_PwrOff(void);


/**
 * @brief This function Initializes the LTMS driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
LTMS_EXTERN void LTMS_Init(void);

/**
 * @brief This function activates the LTMS driver.
 * @param LIN channel number
 * @return void
 */
LTMS_EXTERN void LTMS_WakeUp(uint8_t chn_hnd);

/**
 * @brief This function deactivates the LTMS driver.
 * @param LIN channel number
 * @return void
 */
LTMS_EXTERN void LTMS_GoToSleep(uint8_t chn_hnd);

/**
 * @brief This function returns the status of the module.
 * @param LIN channel number
 * @return LTMS_Status_t
 */
LTMS_EXTERN LTMS_Status_t LTMS_GetStatus(uint8_t chn_hnd);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* LTMS_IF_H_ */
