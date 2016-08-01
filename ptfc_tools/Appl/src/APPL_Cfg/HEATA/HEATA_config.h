/******************************************************************************/
/** @file       HEATA_config.h                                                 */
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
| LB           Livio Bastonero         Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  LB      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __HEATA_CONFIG_H__
#define __HEATA_CONFIG_H__

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "DISPA_cbk.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

// Definition of task call period
#define TASK_PERIOD 100U                        // 100ms
//#define CONV_T      (60000U/TASK_PERIOD)        // Time conversion constant
//#define CONV_TEMP   10                          // Temperature conversion constant

// Definition of temperature values
#define DELTA_T                  15             //  1.5 °C
#define TOL_T                    10             //  1.0 °C

// Definition of temperature values
#define TEMP_LIM                500             // 50 °C
#define MAX_AV_SURF_TEMPERATURE 350             // 35 °C ??

#define SEAT_TEMP_RANGE_MIN     -300            // -30 °C
#define SEAT_TEMP_RANGE_MAX      700            //  70 °C

//// Definition of timer thresholds
//#define T1          (600000U/TASK_PERIOD)        // 10 min
//#define T2          (1800000U/TASK_PERIOD)       // 30 min
//#define T_LOW       (2700000U/TASK_PERIOD)       // 45 min
//#define T3HS        (3600000U/TASK_PERIOD)       // 60 min
//#define T3SW        (4800000U/TASK_PERIOD)       // 80 min
//#define T4          (6300000U/TASK_PERIOD)       // 105 min
//#define T_WAIT_1    (120000U/TASK_PERIOD)        //  2 min
//#define T_WAIT_2    (1080000U/TASK_PERIOD)       // 18 min
//
//// Definition of heating duty cycle levels
//#define DLL1    10U                             // Duty Cycle = 10%
//#define DHL1    25U                             // Duty Cycle = 25%
//#define DWL1    35U                             // Duty Cycle = 35%
//#define D_2     50U                             // Duty Cycle = 50%
//#define D_3    100U                             // Duty Cycle = 100%

// Definition of temperature control finite machine states
#define HL0 0U
#define LL1 1U
#define HL1 2U
#define HL2 3U
#define HL3 4U
#define WL0 5U
#define WL1 6U
#define WL2 7U
#define WL3 8U

#define T_15_MIN            (900000U/TASK_PERIOD)      // 15 min

#endif
#endif
/*______ E N D _____ (HEATA_cfgIf.h) _________________________________________*/
