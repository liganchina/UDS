/******************************************************************************/
/** @file       LPMS.h                                                        */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Private interface of ADC module for driver layer. This file   */
/**             is developed for Renesas RL78 family - micro R5F10AGFLFB/F13. */
/**             The requirement used for this driver is the chapter 12 of the */
/**             relative hw datasheet version 2.0.                            */
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
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 21/07/2014 0.1  CC      First draft. 
|-----------------------------------------------------------------------------
*/

#ifndef __LPMS_H
#define __LPMS_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "LPMS_config.h"
#include "LPMS_if.h"

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

/** Routine prototypes to actuate the action during 
  * the power management transition 
  */
void LPMS_InitEvtCbk(void);
void LPMS_RunPwrOffEvtCbk(void);
void LPMS_PseudoRunPwrOffEvtCbk(void);
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  void LPMS_WakeupEvtCbk(void);
  void LPMS_SleepEvtCbk(void);
#endif
#if (LPMS_FSM_SUBSET == LPMS_FULL_FSM_SUBSET)
  void LPMS_LpPseudoWakeupEvtCbk(void);
#endif
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
  void LPMS_PrPseudoWakeupEvtCbk(void);
#endif
#if (LPMS_FSM_SUBSET & LPMS_PSEUDO_RUN_STATE)
void LPMS_PseudoInitEvtCbk(void);
#endif
#if (LPMS_FSM_SUBSET & LPMS_LOW_POWER_STATE)
  void LPMS_LowPowerManager(void);
#endif


#endif  /* end __LPMS_H */

/*_____ E N D _____ (LPMS.h) _________________________________________________*/
