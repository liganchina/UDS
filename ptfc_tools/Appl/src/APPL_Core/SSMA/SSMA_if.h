/**
 * @file NETP_if.h
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
| 11/11/2014  0.1  GIL    First release
*/

#ifndef __SSMA_IF_H
#define __SSMA_IF_H

#ifdef SSMA_IF_OWNER
	#define SSMA_EXTERN
#else
	#define SSMA_EXTERN		extern
#endif

//#include "NETP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum SSMA_SmartSwitchPressReq_e
{
  SSMA_NOT_PRESS               = 0x00u,
  SSMA_BUTTON_UP               = 0x01u,
  SSMA_BUTTON_FWD              = 0x02u,
  SSMA_BUTTON_DOWN             = 0x03u,
  SSMA_BUTTON_BWD              = 0x04u,
  SSMA_BUTTON_CENTRAL          = 0x05u,
  SSMA_BUTTON_SNA              = 0x0Fu
}SSMA_SmartSwitchPressReq_t;

typedef void (*SSMA_ButtonChgCbk_t)(void);

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Initialization routine for network Smart Smitch management module of the application layer.
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_Init(void);


SSMA_EXTERN PRES_State_t SSMA_GetLumbarH(SSMA_SmartSwitchPressReq_t req);

SSMA_EXTERN PRES_State_t SSMA_GetLumbarV(SSMA_SmartSwitchPressReq_t req);

SSMA_EXTERN PRES_State_t SSMA_GetHeadrest(SSMA_SmartSwitchPressReq_t req);

SSMA_EXTERN PRES_State_t SSMA_GetCushion(SSMA_SmartSwitchPressReq_t req);

SSMA_EXTERN PRES_State_t SSMA_GetBolsterH(SSMA_SmartSwitchPressReq_t req);

SSMA_EXTERN PRES_State_t SSMA_GetBolsterL(SSMA_SmartSwitchPressReq_t req);
#endif /* end __SSMA_IF_H */
