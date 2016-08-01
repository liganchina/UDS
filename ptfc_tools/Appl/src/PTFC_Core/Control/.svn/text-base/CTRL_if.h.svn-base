/**
 * @file CTRL_if.h
 * @author Carmine Celozzi
 * @date 28 lug 2014
 * @brief File containing the interface of Control layer
 * @note  This file must be included by the upper layers (user).
 *
 * @see www.Bitron.net
 */
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
| 27/08/14   0.1  CC      First draft
|-----------------------------------------------------------------------------
| 26/09/14   1.0  CC       Insert the routines CTRL_PseudoInit and
|                          CTRL_PrPseudoWakeup for new power management done by
|                          LPMS module
|-----------------------------------------------------------------------------
*/

#ifndef __CTRL_IF_H
#define __CTRL_IF_H


/* Include for control modules configuration */
#include "CTRL_cfg.h"

/* Include lower layer interfaces */
#include "DRVD_if.h"

/* Inclusione dei tipi proprietari del Layer */
#include "CTRL_typedefs.h"

/* ADCC module inhibition filter */
#ifdef __ADCC_IS_PRESENT__
  /* ADCC - Analog Digital Converter module */
  #include "ADCC_if.h"
#endif

/* DOIFC module inhibition filter */
#ifdef __DOIFC_IS_PRESENT__
  /* Digital output with current fbk control module */
  #include "DOIFC_if.h"
#endif

/* HBRGC module inhibition filter */
#ifdef __HBRGC_IS_PRESENT__
  /* H-Bridge with current fbk control module */
  #include "HBRGC_if.h"
#endif

/* DOVFC module inhibition filter */
#ifdef __DOVFC_IS_PRESENT__
  /* Digital output with voltage fbk control module */
  #include "DOVFC_if.h"
#endif

/* MUXC module inhibition filter */
#ifdef __MUXC_IS_PRESENT__
  /* MUXC - Multiplexer controller module */
  #include "MUXC_if.h"
#endif

/* DIAC module inhibition filter */
#ifdef __DIAC_IS_PRESENT__
  /* Digital input on analog pin mgm */
  #include "DIAC_if.h"
#endif

/* DIAGC module inhibition filter */
#ifdef __DIAGC_IS_PRESENT__
  /* Electrical diagnosis scheduler control module */
  #include "DIAGC_if.h"
#endif

/* EEPC module inhibition filter */
#ifdef __EEPC_IS_PRESENT__
  /* EEPC - Eeprom protocol control module */
  #include "EEPC_if.h"
#endif

/* IPOC module inhibition filter */
#ifdef __IPOC_IS_PRESENT__
  /* IPOC - Input position control module */
  #include "IPOC_if.h"
#endif

/* PWMC module inhibition filter */
#ifdef __PWMC_IS_PRESENT__
  /* PWMC - PWM control module */
  #include "PWMC_if.h"
#endif

/* LINC module inhibition filter */
#ifdef __LINC_IS_PRESENT__
  #include "LINC_if.h"
#endif


/* Layer extern interface */
#ifdef CTRL_IF_OWNER
	#define CTRL_EXTERN
#else
	#define CTRL_EXTERN		extern
#endif

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
CTRL_EXTERN	void CTRL_Init(void);

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
CTRL_EXTERN void CTRL_PseudoInit(void);

/**
 * @brief Initialization routine for control layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
CTRL_EXTERN void CTRL_PrPseudoWakeup(void);

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
CTRL_EXTERN void CTRL_RunPwrOff(void);

/**
 * @brief Initialization routine for driver layer. It must call all init
 *        routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
CTRL_EXTERN void CTRL_PseudoRUNPwrOff(void);

#endif /* __CTRL_IF_H */
