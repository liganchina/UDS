/**
 * @file UARTD_config.c
 * @brief Source for user configuration of UART driver module. In this file,
 * lookup tables are defined to map the addresses of the uC register
 * on the software module.
 *
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

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UARTD.h"
#include "UARTD_config.h"

/* Module inhibition filter */
#ifdef __UARTD_IS_PRESENT__

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

#endif /* end __UARTD_IS_PRESENT__ */

/*______ E N D _____ (UARTD_config.c) _________________________________________*/

