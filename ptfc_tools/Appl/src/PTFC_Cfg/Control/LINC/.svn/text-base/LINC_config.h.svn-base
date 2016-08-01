/**
 * @file LINC_config.h
 * @brief LIN control: source code of LIN module for control layer. 
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
| MAM          Matteo Mastrodonato       Bitron S.p.A.
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
| 27/06/2015 1.0  MAM     Configuration of message map for NAG/NAP F151M.
|                         LDF v1.1.
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
*/

#ifndef LINC_CONFIG_H_
#define LINC_CONFIG_H_

#ifdef __LINC_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINP_cbk.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Transition periods */
#define LINC_INTERBYTE_PER_US   ((uint32_t) 1000)   /* Interbyte space(usec)*/
#define LINC_RESPONSE_PER_US    ((uint32_t) 7000)   /* Responce space (usec)*/
#define LINC_WAKEUP_LEN_PER_US  ((uint32_t) 200000) /* InterWakeUp space (usec)*/
/* Timeout for confirm WakeUp extern (usec) */
#define LINC_WAKEUP_EXT_PER_US  ((uint32_t) 275000 * UARTD_EXTERNAL_WAKE_UP_EXPECTED) 

/* Tick frequency settings */
#define TIM03_PRESC             ((uint16_t) 256)    /* Prescale timer */ 

/* Number of low signal used as WakeUp signal on bus */
#define LINC_WAKEUP_SIGNAL_COUNT    ((uint8_t) 3)

/* Maximum number of errors that can be set for a frame */
#define LINC_FRAME_MAX_ERROR_COUNT  ((uint8_t) 0xFF)

/*______ G L O B A L - D A T A _______________________________________________*/

/* Message map */
extern const Linc_lin_frame_st_t *Linc_MessageMap[LINC_MESSAGE_MAP_LEN];

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* __LINC_IS_PRESENT__ */

#endif /* LINC_CONFIG_H_ */
