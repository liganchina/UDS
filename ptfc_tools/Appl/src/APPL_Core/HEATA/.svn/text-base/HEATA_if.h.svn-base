/******************************************************************************/
/** @file       HEATA_if.h                                                    */
/** @title      Heater application interface                                  */
/** @brief      module for Heater management                                  */
/** @date       08/05/2015                                                    */
/** @author     Livio Bastonero                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| LB           Livio Bastonero		     Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  LB      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __HEATER_IF_H__
#define __HEATER_IF_H__

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__

#define PROJECT_F952

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "HEATA_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/
/* Dichiarazione dell'interfaccia del Layer */
#ifdef HEATA_IF_OWNER
	#define HEATA_EXTERN
#else
	#define HEATA_EXTERN		extern
#endif

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief The function performs the initialization of the structure array
 *        Heata_privateTable[hdl]
 *
 * @param [in] none
 *
 * @param [out]none
 *
 * @return None
 *
 */
HEATA_EXTERN void HEATA_Init(void);

/**
 * @brief The function manages the heating of the driver seat, of the passenger seat
 *        and of the steering wheel. It is called with a period of 100 ms.
 *
 * @param [in] none
 *
 * @param [out]none
 *
 * @return None
 *
 */
HEATA_EXTERN void HEATA_Mgm(void);

/**
 * @brief The function allows to set the heating request level.
 *        It stores the requested heating level
 *        into variable Heata_privateTable[hdl].request_level
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [in] level: This input specifies the required heating level.
 *             For the driver and passenger seats the possible values are
 *             HEATA_LEVEL_0, HEATA_LEVEL_1, HEATA_LEVEL_2, HEATA_LEVEL_3
 *             For the steering wheel the possible values are HEATA_LEVEL_0, HEATA_LEVEL_1
 *
 * @param [out] None
 *
 * @return APPL_ResSts_t
 * @retval APPL_OK if the input parameters are correct
 *
 * @retval APPL_PAR_NOT_OK if the device does not exist or if the level value
 * is not correct
 */
HEATA_EXTERN APPL_ResSts_t HEATA_SetLevel(HEATA_handle_t hdl,uint8_t level);

/**
 * @brief The function allows to read the local fault
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]fault: This output returns the fault set by the application
 *             The possible values are PRES_GENERIC_FAULT, PRES_NO_FAULT, PRES_NOT_TESTED
 *
 * @param [out]destructive: This output returns the fault type set by the application
 *             The possible values are TRUE or FALSE
 *
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT if the input parameters are correct
 *
 * @retval CTRL_NOT_TESTED if the device does not exist
 *
 */
CTRL_Fault_t HEATA_GetDiag(HEATA_handle_t hdl, PRES_Fault_t* fault, bool_t* destructive);

HEATA_EXTERN void HEATA_KeyStsChanged(PRES_KeyStatus_t KeyStatus);

/* functions for IOContro management */
HEATA_EXTERN u08 HEATA_CheckIoControl(u08 hdl, u08 command);

/**
 * @brief The function allows to shift control from the application to the
 *        diagnostics service
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [in] level: This input specifies the required heating level.
 *             For the driver and passenger seats the possible values are
 *             HEATA_LEVEL_0, HEATA_LEVEL_1, HEATA_LEVEL_2, HEATA_LEVEL_3
 *             For the steering wheel the possible values are HEATA_LEVEL_0, HEATA_LEVEL_1
 *
 * @param [out]none
 *
 * @return None
 *
 */
HEATA_EXTERN void HEATA_StartIoControl(uint8_t hdl, uint8_t level);

/**
 * @brief The function allows the application to resume control (before was held by
 *        the diagnostics service)
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]none
 *
 * @return None
 *
 */
HEATA_EXTERN void HEATA_StopIoControl(uint8_t hdl);

HEATA_EXTERN u08 HEATA_GetLevel(HEATA_handle_t hdl);

HEATA_EXTERN void HEATA_ManageTimer_1s(void);

#endif
#endif
/*______ E N D _____ (HEATA_if.h) _________________________________________*/

