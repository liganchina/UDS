/******************************************************************************/
/** @file       PWMC_if.h                                                     */
/** @title      Pulse Width Modulation Control                                */
/** @brief      Public interface of PWM module for control layer.             */
/** @date       02/12/2014                                                    */
/** @author     Mastrodonato Matteo                                           */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 02/12/2014 0.1  MM      First draft
|-----------------------------------------------------------------------------
|            1.0  MM      First release
|-----------------------------------------------------------------------------
*/

#ifndef __PWMC_IF_H
#define __PWMC_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "PWMC_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifdef PWMC_IF_OWNER
	#define PWMC_EXTERN
#else
	#define PWMC_EXTERN		extern
#endif

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief Initialization routine for PWMC control module. This routine must be
 *        called only during transition POWER_OFF --> RUN.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
PWMC_EXTERN void PWMC_Init(void);


/**
 * @brief Manage the PWM SW period and duty transitions.
          Call this function periodically, the tick time must be less equal
          than the minimun Ton of the configured PWM signals.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
PWMC_EXTERN void PWMC_Mgm(void);


/**
 * @brief Set the duty cycle of the signal passed as parameter.
          Duty has a resolution of 1%/Bit.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal to change the duty cycle.
 * @param [out] duty the new duty cycle.
 * @return CTRL_Fault_t
 * @retval CTRL_OK Request correclty applied
 * @retval CTRL_PAR_NOT_OK Request refused due to duty cycle ouf of bound.
 */
PWMC_EXTERN CTRL_ResSts_t PWMC_SetDuty(PWMC_Handle_t hdl, uint8_t duty);


/**
 * @brief This function returns the electrical diagnosis of the selected handle.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT
 * @retval CTRL_OC_OR_STB
 * @retval CTRL_OC_OR_STG
 * @retval CTRL_SHORT_TO_BAT
 * @retval CTRL_SHORT_TO_GND
 * @retval CTRL_NOT_TESTED
 */
PWMC_EXTERN CTRL_Fault_t PWMC_GetDiag(PWMC_Handle_t hdl);



/**
 * @brief This function returns the command state related to diag information
 * returned by PWMC_GetDiag().
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @return CTRL_State_t
 * @retval S_OFF
 * @retval S_ON
 * @retval S_TOGGLE
 */
PWMC_EXTERN CTRL_State_t PWMC_GetDiagState(PWMC_Handle_t hdl);

/**
 * @brief This function is called by DIAGC scheduler. Trigger che diagnosis and get
 *  from the hdl the information to evolve the fault state machine.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal
 * @param [out] cmdState the command state when the last fault has been seen.
 * @param [out] fault the last fault seen
 * @param [out] faultState is the old state of the fault state machine.
 * @return bool_t
 * @retval TRUE the diagnosis is performed
 * @retval FALSE the diagnosis need further call to end the procedure
 */
PWMC_EXTERN bool_t PWMC_PerformDiag(u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState);


/**
 * @brief This function is called by DIAGC scheduler. Decode the information coming
 * from the fault state machine and update the internal handle diagnosis.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] hdl handle of the signal
 * @param [in] faultState is the new state of the fault state machine.
 * @return none
 */
PWMC_EXTERN void PWMC_DecodeDiag(u08 hdl, CTRL_FaultState_t faultState);

/**
 * @brief Get the duty cycle of the signal passed as parameter.
          Duty has a resolution of 1%/Bit.
 * @author Davide Fogliano - Polimatica S.r.l.
 * @param [in] hdl handle of the signal to get the duty cycle.
 * @return Duty cycle
 * @retval 0xFF handler not valid
 */
PWMC_EXTERN u08 PWMC_GetDuty(PWMC_Handle_t hdl);

/* TODO COBRA */
//PWMC_EXTERN DRVD_RStatus_t PWMC_SetFault(PWMC_Handle_t hdl, CTRL_Fault_t fault);

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
PWMC_EXTERN  void  PWMC_EnableDisable (PWMC_Handle_t hdl, CTRL_EnSts_t state);


#endif /* end __PWMC_IF_H */

/*_____ E N D _____ (PWMC_if.h) ______________________________________________*/
