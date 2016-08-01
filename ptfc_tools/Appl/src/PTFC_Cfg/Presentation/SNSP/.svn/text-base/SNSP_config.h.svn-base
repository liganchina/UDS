/**
 * @file SNSP_config.h
 * @brief
 * @author  - Livio Bastonero Bitron S.p.A.
 * @date 26/06/2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Livio Bastonero       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 26/06/2015 1.0  LB      First release
|-----------------------------------------------------------------------------
*/

#ifndef SNSP_CONFIG_H_
#define SNSP_CONFIG_H_

/* Module inhibition filter */
#ifdef __SNSP_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "SNSP_cbk.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define Snsp_NTC_TABLE_NUM_POINT                 46u
#define DELTA_HIST_SUP                            5u
#define DELTA_HIST_INF                           10u

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/
extern const FUNP_Interp_curve_point_t Snsp_NTC_Table[Snsp_NTC_TABLE_NUM_POINT];

SNSP_FunRet_t SNSP_GetNTCTemperatureErrorDriver(void);

SNSP_FunRet_t SNSP_GetNTCTemperatureErrorPassenger(void);

SNSP_FunRet_t SNSP_GetNTCTemperatureErrorSteer(void);

int16_t SNSP_GetTemperature(SNSP_Handle_t hdl);


#endif /* end __SNSP_IS_PRESENT__ */


#endif /* SNSP_CONFIG_H_ */
