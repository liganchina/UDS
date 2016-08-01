/******************************************************************************/
/** @file       HEATA_cfgIf.h                                                 */
/** @title      HEATA application interface                                   */
/** @brief      module for FAN management                                     */
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
#ifndef __HEATA_CFGIF_H__
#define __HEATA_CFGIF_H__

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/* minimum and maximum values for constant parameters (used in UDSA_RdiConfig.c) */
#define HEATA_TEMP_LIM_0          0U
#define HEATA_TEMP_LIM_1        700U
#define HEATA_TEMP_RANGE_MIN_0  -400
#define HEATA_TEMP_RANGE_MIN_1  -100
#define HEATA_TEMP_RANGE_MAX_0  500U
#define HEATA_TEMP_RANGE_MAX_1 1000U

#define HEATA_TIME_T1            600U
#define HEATA_TIME_T_WAIT_1      600U
#define HEATA_TIME_T2           1800U
#define HEATA_TIME_T3SW         4800U
#define HEATA_TIME_T3HS         3600U
#define HEATA_TIME_T_WAIT_2     1200U
#define HEATA_TIME_T4           6600U
#define HEATA_TIME_T_LOW        3000U

/*_____ G L O B A L - T Y P E S ______________________________________________*/

typedef enum HEATA_handle_e
{
	HEATA_SEAT_DRV,
	HEATA_SEAT_PSG,
  HEATA_STW,
	HEATA_MAX_HDL
} HEATA_handle_t;


typedef enum HEATA_reqlevel_e
{
	HEATA_LEVEL_0 = 0,
	HEATA_LEVEL_1,
	HEATA_LEVEL_2,
  HEATA_LEVEL_3,
  HEATA_LEVEL_MAX = HEATA_LEVEL_3
} HEATA_reqlevel_t;

/*_____ G L O B A L - D A T A ________________________________________________*/
//extern u16 FANA_PowerFan; /* variable for shared supply management */

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (HEATA_cfgIf.h) _________________________________________*/
