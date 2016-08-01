/**
 * @file LTMS.h
 * @brief Configuration of the LIN transceiver
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
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
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/

#ifndef __LTMS_H
#define __LTMS_H

#include "DRVD_if.h"
/* #include "LTMS_cbk.h" */

/* Module inhibition filter */
#ifdef __LTMS_IS_PRESENT__


/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Timer timeout counts */
#define LTMS_TIMEOUT_GOTONORM_COUNT     ((F_CLK_MHZ*LTMS_GOTONORM_PER_US)/TIM02_PRESC) 
#define LTMS_TIMEOUT_GOTOSLEEP_COUNT    ((F_CLK_MHZ*LTMS_GOTOSLEEP_PER_US)/TIM02_PRESC)

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#endif /* end __LTMS_IS_PRESENT__ */

#endif  // __LTMS_H
