/**
 * @file LINP_if.h
 * @brief LIN presentation: source code of LIN module for presentation layer. 
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

#ifndef LINP_IF_H_
#define LINP_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef LINP_IF_OWNER
 #define LINP_EXTERN
#else
 #define LINP_EXTERN  extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "LINP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/
/* LINP module state */
typedef enum
{
  LINP_SLEEP = 0, /* Sleep state                          */
  LINP_IDLE,        /* Idle state (on, waiting to send)     */
  LINP_MAX_STATUS
} Linp_Status_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the LINP driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
LINP_EXTERN void LINP_Init(void);

/**
 * @brief Activates network transmitting a "wake up" command
 * @return void
 * @note 
 */
LINP_EXTERN void LINP_WakeUp(uint8_t chn_hnd);

/**
 * @brief Send network to sleep transmitting a "go to sleep" command
 * @return void
 * @note 
 */
LINP_EXTERN void LINP_GoToSleep(uint8_t chn_hnd);

/**
 * @brief Sends the message header and calculates for each frame the slot time
 * @return void
 * @note 
 */
LINP_EXTERN void LINP_SchedulerTick(uint8_t chn_hnd);

/**
 * @brief Change the schedule table index
 * @return void
 * @note 
 */
LINP_EXTERN void LINP_SetSchedulerTable(uint8_t scheduleTableNum);

/**
 * @brief Return index of schedule table
 * @return uint8_t
 * @note 
 */
LINP_EXTERN uint8_t LINP_GetSchedulerTable(void);

/**
 * @brief Return status of DTC setting
 * @return CTRL_Fault_t
 * @note 
 */
LINP_EXTERN PRES_Fault_t LINP_CheckSlaveOnline(void);
LINP_EXTERN PRES_Fault_t LINP_CheckCommunication(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* LINP_IF_H_ */
