/**
 * @file SYSM_if.c
 * @brief Interface for SYSMem layer.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @date 02 june 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo MASTRODONATO       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 02/giu/13   0.1  MM      First draft
|-----------------------------------------------------------------------------
| 
*/

#ifndef SYSM_IF_H_
#define SYSM_IF_H_


/* Include for presentation modules configuration */
#include "SYSM_cfg.h"

/* Inclusione dei tipi proprietari del Layer */
#include "SYSM_typedefs.h"

/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  #include "LTMS_if.h"
#endif


/* Layer extern interface */
#ifdef SYSM_IF_OWNER
	#define SYSM_EXTERN
#else
	#define SYSM_EXTERN		extern
#endif

/**
 * @brief Initialization routine for system layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
SYSM_EXTERN	void SYSM_Init(void);

/**
 * @brief Initialization routine for system layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
SYSM_EXTERN void SYSM_PseudoInit(void);

/**
 * @brief Initialization routine for system layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
SYSM_EXTERN void SYSM_PrPseudoWakeup(void);

/**
 * @brief Power off routine for system layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
SYSM_EXTERN void SYSM_RunPwrOff(void);

/**
 * @brief Power off routine for system layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
SYSM_EXTERN void SYSM_PseudoRUNPwrOff(void);

#endif /* SYSM_IF_H_ */
