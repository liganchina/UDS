/**
 * @file DRVD_if.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the interface of Driver layer
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
| MM           Matteo MASTRODONATO       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 12/giu/13   0.1  MM       First draft
|-----------------------------------------------------------------------------
| 26/09/14    1.0  CC       Insert the routines DRVD_PseudoInit and 
|                           DRVD_PrPseudoWakeup for new power management done by
|                           LPMS module
|-----------------------------------------------------------------------------
| 
*/

#ifndef DRVD_IF_H_
#define DRVD_IF_H_


/* Include for driver modules configuration */
#include "DRVD_cfg.h"

/* Inclusione dei tipi proprietari del Layer */
#include "DRVD_typedefs.h"

/* Include for MCAL interfaces */
#include "MCAL_if.h"

/* Inlcude for System Layer */
#include "LPMS_if.h"
#include "SYSM_if.h"

/* ISRD - Interrupt Service Routine module */
#include "ISRD_if.h"

/* ADCD module inhibition filter */
#ifdef __ADCD_IS_PRESENT__
  #include "ADCD_if.h"
#endif
/* DIOD module inhibition filter */
#ifdef __DIOD_IS_PRESENT__
  #include "DIOD_if.h"
#endif
/* CMMD module inhibition filter */
#ifdef __CMMD_IS_PRESENT__
  #include "CMMD_cfgIf.h"
#endif
/* CAND module inhibition filter */
#ifdef __CAND_IS_PRESENT__
  #include "CAND_if.h"
#endif
/* MEMD module inhibition filter */
#ifdef __MEMD_IS_PRESENT__
  #include "MEMD_if.h"
#endif
/* UARTD module inhibition filter */
#ifdef __UARTD_IS_PRESENT__
  #include "UARTD_if.h"
#endif
/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  #include "LTMS_if.h"
#endif

/* Dichiarazione dell'interfaccia del Layer */
#ifdef DRVD_IF_OWNER
	#define DRVD_EXTERN
#else
	#define DRVD_EXTERN		extern
#endif


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
DRVD_EXTERN	void DRVD_Init(void);

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
DRVD_EXTERN void DRVD_PseudoInit(void);

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
DRVD_EXTERN void DRVD_PrPseudoWakeup(void);

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
DRVD_EXTERN void DRVD_RunPwrOff(void);

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
DRVD_EXTERN void DRVD_PseudoRUNPwrOff(void);

#endif /* DRVD_IF_H_ */
