/**
 * @file MOTP_config.h
 * @brief Motors with hall sensor position fbk management.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @date 21 October 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 10/09/2014 1.0  MM      First release
|-----------------------------------------------------------------------------
*/

#ifndef __MOTP_CONFIG_H
#define __MOTP_CONFIG_H


/* Module inhibition filter */
#ifdef __MOTP_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MOTP_cbk.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define MOTP_RECOVERY_IDLE_BRAKE_EN  TRUE

/**
 * Tick time to use for compute the maximum ticks number. This time must be used
 * as reference for call the module management routine with the correct task time.
 * Resolution: [1ms/bit]
 */
#define MOTP_TICK_MS                 10U

/**
 * Brake procedure duration. Warning: !!! It must be multiple of MOTP_TICK_TIME !!!
 * !!! Max Value = 255 !!!
 * Resolution: [1ms/bit]
 */
#define MOTP_BRAKE_TIME             100U

/**
 * Number max of delta step for position re-alignment when a stroke is recognized.
 */
#define MOTP_ALIGN_POS_STEP           10

/**
 * Gap of step between electrical and mechanical stroke.
 */
#define MOTP_ELT_STROKE_STEP          10  //SW_STROKE_OFFSET

/**
 * Diagnosis procedure duration. Warning: !!! It must be multiple of IPOC_TICK_TIME !!!
 * Resolution: [1ms/bit]
 */
//#define MOTP_FBK_POS_DIAG_TIME      300U

/**
 * Init values for forward/up and backward/down stroke
 */
#define MOTP_UP_FW_STROKE_INIT     32000
#define MOTP_DW_BW_STROKE_INIT    -32000

/**
 * Number of step needed to brake the motor before reaching the comfort position.
 */
#define MOTP_PRE_CONFORT_STEP            3  //HALLS_STOP_IN_ADVANCE  or  HALLS_STOP_IN_ADVANCE_HISPEED

/**
 * Minimum steps difference to start an automatic movement.
 */
#define MOTP_MIN_MOVE_STEP               8  // START_HALL_PULSES_TOL

/**
 * Minimum steps count to invalidate the position fbk diagnosis.
 */
#define MOTP_INVALID_POS_FBK_DIAG_STEP   5

/*______ G L O B A L - M A C R O S ___________________________________________*/

#define MOTP_CONFIG_INIT()                 MOTP_CfgInit();\
                                           MOTP_SetDiagState(FALSE);
#define MOTP_CONFIG_PWR_OFF()              MOTP_CfgPwrOff();
#define MOTP_PRE_MOVE_EVT(motor)           MOTP_CloseProtRel(motor);\
                                           MOTP_SetDiagState(TRUE);

#define MOTP_MOVING_EVT(motor, cmd)        TLRP_SetSlow(TLRP_ProtRelTimeout); \
                                           TLRP_SetSlow(TLRP_SavePosition);

#define MOTP_MOTOR_FAIL_EVT(motor, fail)   MOTP_MotorFailEvent((motor), (fail));
#define MOTP_POS_FAIL_EVT(motor)           MOTP_PosFailEvent(motor);

#define MOTP_STROKE_EVT(motor)             MOTP_StrokeEvtMgm(motor);

#define MOTP_STOP_RECOVERY()               FVMP_ResetLine(FVMP_TILT_SLIDE_RL);\
                                           FVMP_ResetLine(FVMP_LIFT_BACK_RL);\
                                           FVMP_ResetLine(FVMP_PROT_RL);\

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

extern const CTRL_State_t           MOTP_MovTable[MOTP_MAX_HDL][MOTP_INT_CMD_NUM][MOTP_NUM_CMD]; /*Defined in MOTP_config.c */

extern void MOTP_CfgInit(void);


#endif /* end __MOTP_IS_PRESENT__ */

#endif /* end __MOTP_CONFIG_H */

/*_____ E N D _____ (MOTP_config.h) __________________________________________*/
