/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              Funp.h                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/07/2012                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| DF           Davide Fogliano           Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 22/05/2013  0.1  GIL     First DRAFT
*/
#ifndef FUNP_CFGIF_H
#define FUNP_CFGIF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef enum
{
  FUNP_COUNTRY_WORLD  = 0U,
  FUNP_COUNTRY_USA    = 2U,
  FUNP_COUNTRY_CANADA = 4U,
  FUNP_COUNTRY_MEXICO = 14U
} FUNP_ProxiCountriCode_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define POLY 0x8408u  /* CRC-CCITT - Polynomial: x^16 + x^12 + x^5 + 1 (0x8408) */

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

bool FUNP_IsSlideActive(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_IsVehicleSpeedEqZero                                            */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool FUNP_IsVehicleSpeedEqZero(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_IsEngineNotRunning                                              */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
bool FUNP_IsEngineNotRunning(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetBatteryVoltageDiag                                           */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
//L.B.PRES_Fault_t FUNP_GetBatteryVoltageDiag(u08 dummy);

/**
 * @brief Get status of IgnitionPreStartLogic
 *
 * @return PRES_State_t
 * @retval Status of IgnitionPreStartLogic
 */
PRES_State_t FUNP_GetIgnitionPreStartLogic(void);

/**
 * @brief Get status of Country Code
 * @param none
 * @return FUNP_ProxiCountriCode_t
 * @retval Status of EERAM_Proxi_Country_Code
 */
FUNP_ProxiCountriCode_t FUNP_GetCountryCode(void);

/**
 * @brief Set status of Country Code
 * @param none
 * @return FUNP_ProxiCountriCode_t
 * @retval Status of EERAM_Proxi_Country_Code
 */
void FUNP_SetCountryCode(FUNP_ProxiCountriCode_t PrivateCountryCode);

/**
 * @brief Test if Country Code different from USA OR CANADA OR MEXICO values
 * @param none
 * @return bool_t
 * @retval Status of test
 */
bool_t FUNP_IsShortComfortTimer(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetTotalOdometer                                                */
/*Role : used in VF 607 only for VIN odo                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u32 FUNP_GetTotalOdometer(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetVehicleSpeed                                                 */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u16 FUNP_GetVehicleSpeed(void);

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetBatteryVoltage                                               */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u16 FUNP_GetBatteryVoltage(void);

PRES_Fault_t FUNP_GetVehicleSpeedDiag(void);

/**
 * @brief Update IDs (RDI 0xF180, 0xF181, 0xF182, 0xF187, 0xF194, 0xF195, 0xF196)
 *       after a flash re-programming
 * @return void
 * @retval none
 */
void FUNP_WriteNewIDs(void);

/**
 * @brief Function used to activate hall. It saves how many modules are using hall
 * @param [in] None
 * @param [out] None
 * @return None
 */
void FUNP_HallActive(void);

/**
 * @brief Function used to disable hall, if no modules are using it
 * @param [in] None
 * @param [out] None
 * @return None
 */
void FUNP_HallInactive(void);

/**
 * @brief Function to retrieve if hall are currently active or not
 * @param [in] None
 * @param [out] None
 * @return None
 */
bool FUNP_IsHallActive(void);

/**
 * @brief This function checks if hall sensor is in fail. It does not perform eletrical diagnose
 * @param [in] None
 * @param [out] None
 * @return bool
 */
bool FUNP_IsHallFail(u08 motor);
/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif
