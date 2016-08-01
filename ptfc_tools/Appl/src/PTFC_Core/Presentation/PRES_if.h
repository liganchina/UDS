/*
 * PRES_if.h
 *
 *  Created on: 04/giu/2013
 *      Author: Matteo MASTRODONATO
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
| 26/09/14    1.0  CC       Insert the routines PRES_PseudoInit and
|                           PRES_PrPseudoWakeup for new power management done by
|                           LPMS module
|-----------------------------------------------------------------------------
*/

#ifndef PRES_IF_H_
#define PRES_IF_H_

/* Include lower layer interfaces */
#include "CTRL_if.h"

/* Include for presentation modules configuration */
#include "PRES_cfg.h"

/* Inclusione dei tipi proprietari del Layer */
#include "PRES_typedefs.h"
#include "ECU_Identification.h"

/* TLRP module inhibition filter */
#ifdef __TLRP_IS_PRESENT__
  #include "TLRP_if.h"
#endif
/* NETP module inhibition filter */
#ifdef __NETP_IS_PRESENT__
  #include "NETP_if.h"
#endif
/* DINP module inhibition filter */
#ifdef __DINP_IS_PRESENT__
  #include "DINP_if.h"
#endif
/* AVGP module inhibition filter */
#ifdef __AVGP_IS_PRESENT__
  #include "AVGP_if.h"
#endif
/* DIAGP module inhibition filter */
#ifdef __DIAGP_IS_PRESENT__
  #include "DIAGP_if.h"
#endif
/* FVMP module inhibition filter */
#ifdef __FVMP_IS_PRESENT__
  #include "FVMP_if.h"
#endif
/* TP module inhibition filter */
#ifdef __TP_IS_PRESENT__
  #include "TP_if.h"
#endif
/* DDMP module inhibition filter */
#ifdef __DDMP_IS_PRESENT__
  #include "DDMP_if.h"
#endif
/* FUNP module inhibition filter */
#ifdef __FUNP_IS_PRESENT__
  #include "FUNP_if.h"
#endif
/* MOTP module inhibition filter */
#ifdef __MOTP_IS_PRESENT__
  #include "MOTP_if.h"
#endif
/* LINP module inhibition filter */
#ifdef __LINP_IS_PRESENT__
  #include "LINP_if.h"
#endif
/* SNSP module inhibition filter */
#ifdef __SNSP_IS_PRESENT__
  #include "SNSP_if.h"
#endif
/* EEPP module inhibition filter */
#ifdef __EEPP_IS_PRESENT__
  #include "EEPP_if.h"
#endif

/* Layer extern interface */
#ifdef PRES_IF_OWNER
  #define PRES_EXTERN
#else
  #define PRES_EXTERN   extern
#endif

/**
 * @brief Initialization routine for presentation layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
PRES_EXTERN	void PRES_Init(void);

/**
 * @brief Initialization routine for presentation layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
PRES_EXTERN void PRES_PseudoInit(void);

/**
 * @brief Initialization routine for presentation layer. It must call
 *        all init routines present in this layer.
 *
 * @note  Must be called at power on with interrupt are not enabled
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
PRES_EXTERN void PRES_PrPseudoWakeup(void);

/**
 * @brief Power off routine for presentation layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
PRES_EXTERN void PRES_RunPwrOff(void);

/**
 * @brief Power off routine for presentation layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
PRES_EXTERN void PRES_PseudoRUNPwrOff(void);

/**
 * @brief This routine returns the layer Presentation fault from a DTC symptom
 * @param [in]  DDMP_FaultSymptom_t the DTC symptom
 * @param [out] None
 * @return PRES_Fault_t the presentation fault associated with the symptom code
 */
PRES_EXTERN PRES_Fault_t PRES_GetFaultBySymptom(DDMP_FaultSymptom_t Symptom);

/**
 * @brief This routine returns the DTC symptom code from a presentation fault
 * @param [in] PRES_Fault_t the presentation fault
 * @param [out] None
 * @return DDMP_FaultSymptom_t the DTC symptom associated with the fault
 */
PRES_EXTERN DDMP_FaultSymptom_t PRES_GetSymptomByFault(PRES_Fault_t Fault);

#endif /* PRES_IF_H_ */
