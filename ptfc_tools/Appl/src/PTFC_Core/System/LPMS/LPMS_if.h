/******************************************************************************/
/** @file       LPMS_if.h                                                     */
/** @title      Analog Digital Converter Control                              */
/** @brief      Public interface of ADC module for control layer. This file   */
/**             is developed for project QB35 and MQB.                        */
/** @date       27/08/2014                                                    */
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
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 27/08/2014 0.1  CC      First draft
|-----------------------------------------------------------------------------
*/

#ifndef __LPMS_IF_H
#define __LPMS_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "global.h"
#include "LPMS_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifdef LPMS_IF_OWNER
	#define LPMS_EXTERN
#else
	#define LPMS_EXTERN		extern
#endif


/*_____ G L O B A L - T Y P E S ______________________________________________*/


typedef enum Lpms_FsmState_e
{
  LPMS_POWER_OFF = 0,
  LPMS_RUN,
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  LPMS_LOW_POWER,
#endif
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
  LPMS_PSEUDO_RUN
#endif
}LPMS_FsmState_t;


typedef enum LPMS_Event_e
{
  LPMS_INIT = 0,
  LPMS_PWR_OFF,
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  LPMS_SLEEP,
  LPMS_WAKEUP,
#endif
#if (LPMS_FSM_SUBSET == LPMS_FULL_FSM_SUBSET)
  LPMS_LP_PSEUDO_WAKEUP,
#endif
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
  LPMS_PSEUDO_INIT,
  LPMS_PR_PSEUDO_WAKEUP,
#endif
  LPMS_NO_EVENT
}LPMS_Event_t;



typedef enum LPMS_EventStatus_e
{
  LPMS_OK = 0,
  LPMS_WRONG_PARAM,
  LPMS_NOT_POSSIBLE,
  LPMS_BUSY
}LPMS_EventStatus_t;


/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief Initialization routine for Power management system module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
LPMS_EXTERN void LPMS_Init(void);

LPMS_EXTERN void LPMS_FsmManager(void);
LPMS_EXTERN LPMS_EventStatus_t LPMS_SetEvent(LPMS_Event_t EventReq);
LPMS_EXTERN LPMS_FsmState_t LPMS_GetFsmState(void);

/**
  * Ruotine to actuate the HW reset
  */
LPMS_EXTERN void LPMS_HwReset(void);


#endif /* end __LPMS_IF_H */

/*_____ E N D _____ (LPMS_if.h) ______________________________________________*/
