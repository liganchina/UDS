/**
 * @file DINP_config.h
 * @brief Debounce INput Presentation: this file contain some configuration  
 * parameters of the DINP module for user settings.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @date 10 september 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo Mastrodonato       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 10/09/2014 1.0  MM      First release
|-----------------------------------------------------------------------------
| 16/10/2014 1.1  CC      Inserted the parameter routine DINP_CHN_SCAN_TIME_US
|                         used to set the time to scan all channels configured
|-----------------------------------------------------------------------------
*/

#ifndef __DINP_CONFIG_H
#define __DINP_CONFIG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MOTP_cbk.h"
#include "DISPA_cbk.h"
#include "FUNP_cbk.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/


/**
 * Tick time to use for compute the maximum ticks number. This time must be used
 * as reference for call the module management routine with the correct task time.
 */
#define DINP_TICK_TIME              ((uint16_t)1000u)

/**
 * Time to scan all channel configured. This time must be setted in microseconds.
 */
#define DINP_CHN_SCAN_TIME_US       ((uint16_t)5000u)


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

uint8_t DINP_GetSteerVUp(u08 dummy);
uint8_t DINP_GetSteerVDw(u08 dummy);
uint8_t DINP_GetSteerHFw(u08 dummy);
uint8_t DINP_GetSteerHBw(u08 dummy);

#endif /* end __DINP_CONFIG_H */

/*_____ E N D _____ (DINP_config.h) __________________________________________*/
