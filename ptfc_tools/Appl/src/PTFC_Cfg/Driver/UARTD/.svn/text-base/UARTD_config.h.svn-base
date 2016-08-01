/**
 * @file UARTD_config.h
 * @brief UART Driver: private configuration file of the UART driver.
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

#ifndef UARTD_CONFIG_H_
#define UARTD_CONFIG_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "LINC_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Baud rate settings */
#define UARTD_BR_HZ     ((uint16_t) 19200U)  /* Frequency LIN comunication (kbps) */  
#define LIN_UART_PRESC  ((uint8_t) 0U)       /* Prescale LIN comunication */

/* Channel device used */
/* #define __UARTD_CHN_HND_0__ */
#define __UARTD_CHN_HND_1__ 

/* Factor for short circuit  detection sw timer (x100ms)*/
#define UARTD_TIME_SC_TICK      ((uint8_t) 10)

/* Standard length of break field */
#define UARTD_BF_LEN            BF_LEN_14_BIT
/* Standard length of wake up */
#define UARTD_WAKE_UP_LEN       BF_LEN_20_BIT

/* Define Interrupt Priority Specification Flag (0=high level, 3=low level)   */
#define UARTD_INT_PR_LEVEL_TX       ((uint8_t) 0)
#define UARTD_INT_PR_LEVEL_RX       ((uint8_t) 0)
#define UARTD_INT_PR_LEVEL_ST       ((uint8_t) 0)
#define UARTD_INT_PR_LEVEL_PR       ((uint8_t) 0)

/* Rx data callback (ISR) */
#define UARTD_RX_DATA_CBK           LINC_RxDataCbk


/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* UARTD_CONFIG_H_ */

