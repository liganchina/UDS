/**
 * @file SSMA.c
 * @brief Smart Switch management: source code of ....
 * @n The main module features/services are:
 * @li ...
 * </ul>
 *
 * @version 0.1.
 * @author Gianpiero Lenta (Bitron S.p.A.)
 * @date 11 NOV 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/************************** (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
|11/11/2014  0.1  GIL    First release
|-----------------------------------------------------------------------------
*/

#ifndef __SSMA_H
#define __SSMA_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "APPL_if.h"

/* Module inhibition filter */
#ifdef __SSMA_IS_PRESENT__

//#include "NETP_config.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/


/*______ G L O B A L - T Y P E S _____________________________________________*/


typedef enum SSMA_StateMachine_e
{
  SSMA_COMFORT_IDLE            = 0x00u,
  SSMA_COMFORT_MENU_SELECTION  = 0x01u,
  SSMA_COMFORT_BOLSTER_H       = 0x02u,
  SSMA_COMFORT_BOLSTER_L       = 0x03u,
  SSMA_COMFORT_LUMBAR_H        = 0x04u,
  SSMA_COMFORT_LUMBAR_V        = 0x05u,
  SSMA_COMFORT_HEADREST        = 0x06u,
  SSMA_COMFORT_CUSHION         = 0x07u,
  SSMA_COMFORT_SNA             = 0x08u,
  SSMA_COMFORT_MAX_STS         = SSMA_COMFORT_SNA
}SSMA_StateMachine_t;

typedef enum SSMA_SmartSwitchConfig_e
{
  SSMA_BUTTON_1                = 0u,
  SSMA_BUTTON_2                = 1u,
  SSMA_BUTTON_3                = 2u,
  SSMA_BUTTON_4                = 3u,
  SSMA_BUTTON_5                = 4u,
  SSMA_MAX_BUTTON              = 5u
}SSMA_SmartSwitchConfig_t;


typedef struct SSMA_CfgTable_s
{
  SSMA_SmartSwitchPressReq_t  ButtonEnabled[SSMA_MAX_BUTTON];
  SSMA_ButtonChgCbk_t         Callback;
} SSMA_CfgTable_t;


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S _____________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const SSMA_CfgTable_t SSMA_CfgTable[SSMA_COMFORT_MAX_STS];

#endif /* end __SSMA_IS_PRESENT__ */

#endif /* end __SSMA_H */
