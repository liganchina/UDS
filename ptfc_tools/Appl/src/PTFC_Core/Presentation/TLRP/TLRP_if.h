/**
 * @file TLRP_if.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing interface of TLRP Driver.
 *  TLRP: "Timer Low Resolution"
 *
 * @see www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 15/06/2013 1.0  MM      First release
|-----------------------------------------------------------------------------
| 09/10/2014 1.1  CC      New management of the callback: deleted input parameter
|-----------------------------------------------------------------------------
*/

#ifndef __TLRP_IF_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __TLRP_IF_H

#include "TLRP_cfgIf.h"


#ifdef TLRP_IF_OWNER
	#define TLRP_EXTERN
#else
	#define TLRP_EXTERN		extern
#endif

/************************   Types definition   *****************************/

typedef void (*TLRP_CallbackFast_t)(void);
typedef void (*TLRP_CallbackSlow_t)(void);


/************************   Function prototype   ******************************/

/**
 * @brief This function set a fast timer.
 * @return the result of the operation
 * @note  The timer value is statically configured.
 */

TLRP_EXTERN DRVD_RStatus_t  TLRP_SetFast(TLRP_HandlerFast_t hdl);

/**
 * @brief This function reset a fast timer.
 * @return the result of the operation
 */
TLRP_EXTERN DRVD_RStatus_t  TLRP_ResetFast(TLRP_HandlerFast_t hdl);

/**
 * @brief This function check a fast timer.
 * @return the current value of the timer
 */
TLRP_EXTERN u16             TLRP_GetFast(TLRP_HandlerFast_t hdl);

/**
 * @brief This function set a slow timer.
 * @return the result of the operation
 * @note  The timer value is statically configured.
 */
TLRP_EXTERN DRVD_RStatus_t  TLRP_SetSlow(TLRP_HandlerSlow_t hdl);

/**
 * @brief This function reset a slow timer.
 * @return the result of the operation
 */
TLRP_EXTERN DRVD_RStatus_t  TLRP_ResetSlow(TLRP_HandlerSlow_t hdl);

/**
 * @brief This function check a slow timer.
 * @return the current value of the timer
 */
TLRP_EXTERN u32             TLRP_GetSlow(TLRP_HandlerSlow_t hdl);

/**
 * @brief This function initializes the TLRP driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
TLRP_EXTERN void        	TLRP_Init(void);

/**
 * @brief This function manages the internal counters of TLRP driver.
 * @return void
 * @note  It must be called periodically (Fast)
 */
TLRP_EXTERN void        	TLRP_MgmFast(void);

/**
 * @brief This function manages the internal counters of TLRP driver.
 * @return void
 * @note  It must be called periodically (Slow)
 */
TLRP_EXTERN void        	TLRP_MgmSlow(void);

#endif  /* end __TLRP_IF_H */
