/**
 * @file LTMS_config.h
 * @brief Configuration of the LIN transceiver
 * @version 0.2
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 5 June 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time 
|-----------------------------------------------------------------------------
|
|-----------------------------------------------------------------------------
*/

#ifndef LTMS_CONFIG_H_
#define LTMS_CONFIG_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/
/* Transition periods */

/* Time period for mode change from Sleep mode into Normal mode */
#define LTMS_GOTONORM_PER_US        ((uint8_t) 10)      /* uSec */

/* Time period for mode change from Normal mode into Sleep mode */
#define LTMS_GOTOSLEEP_PER_US      ((uint8_t) 10)      /* uSec */

/* Tick frequency settings */
#define TIM02_PRESC                 ((uint16_t) 16)     /* Prescale timer */ 

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* LTMS_CONFIG_H_ */
