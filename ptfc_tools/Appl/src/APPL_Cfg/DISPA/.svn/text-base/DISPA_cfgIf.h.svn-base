/**
 * @file DISPA_cfgIf.h
 * @brief DISPA Module: user enum and define
 *
 * @version 0.1
 * @author Davide Fogliano (Polimatica S.r.l.)
 * @date 24 june 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano           Polimatica S.r.l
|-----------------------------------------------------------------------------
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
| 24/07/15   0.2  DC      Porting to 952 project
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __DISPA_CFGIF_H__
#define __DISPA_CFGIF_H__

/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__ 

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/
/* number of possible IOCOntrol at startup */
#define DISPA_INITIAL_MAX_IO_CONTROL           0u  

/* Calling period of DISPA_FastMgm() in milliseconds*/
#define DISPA_FAST_MGM_TICK_MS                 10U

/* Calling period of DISPA_SlowMgm() in milliseconds*/
#define DISPA_SLOW_MGM_TICK_MS                 100U

/*_____ G L O B A L - T Y P E S ______________________________________________*/

typedef enum DISPA_handle_e
{
    DISPA_TILT,
    DISPA_LIFT,
    DISPA_BACKREST,
    DISPA_SLIDE,
    DISPA_SEAT_DRV,
    DISPA_SEAT_PSG,
    DISPA_STW,
    /* do not remove following line */
    DISPA_HANDLE_MAX
} DISPA_handle_t;

typedef enum DISPA_IoGroup_e
{
    DISPA_GROUP_SLIDE_TILT,
    DISPA_GROUP_BACKR_LIFT,
    DISPA_GROUP_H_D,
    DISPA_GROUP_H_P,
    DISPA_GROUP_H_S,
    /* do not remove following lines */
    DISPA_GROUP_MAX
} DISPA_IoGroup_t;

typedef enum DISPA_Module_e
{
    DISPA_MOD_MOTP,
    DISPA_MOD_HTRA,
    /* do not remove following line */
    DISPA_MOD_MAX
} DISPA_Module_t;

typedef enum
{
  BACKRALIGN_OFF,
  BACKRALIGN_BACKWARD,
  BACKRALIGN_FOREWARD,
}DISPA_BackrAlignState_t;
/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/
extern void DISPA_cfgInit(void);
extern void DISPA_ModelInInit(void);
extern void DISPA_FastModelInUpdate(void);
extern void DISPA_SlowModelInUpdate(void);
extern void DISPA_UpdateStatus(void);
extern void DISPA_ComputeCommands(void);
extern void DISPA_PriorityManager(void);

extern void DISPA_BatteryUnplugMonitor(void);
extern void DISPA_PwrOff(void);
extern void DISPA_PseudoRUNPwrOff(void);

extern void DISPA_NwmNotification(void);

extern void  DISPA_StartInitialization(void);    //DF:
extern void  DISPA_StopInitialization(void);
extern u08   DISPA_GetInitializationStatus(void);
extern void  DISPA_KeyOffEvent(void);

extern void  DISPA_UpdateAntiPinchThresholds(void);
extern bool  DISPA_IsSeatMoving(void);
extern bool  DISPA_IsButtonPressed(void);

/* function for IOControl directly managed by DISPA */
u08  DISPA_SelfCheckIoControl(DISPA_handle_t hdl, u08 cmd);
void DISPA_SelfStartIoControl(DISPA_handle_t hdl, u08 cmd);
void DISPA_SelfStopIoControl(DISPA_handle_t hdl);

//APSA debug function
extern uint8_t DISPA_GetAntiPinchSegment(void);
extern uint16_t DISPA_GetAttentionThreshold(void);
extern uint16_t DISPA_GetAntiPinchThreshold(void);

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (DISPA_cfgIf.h) _________________________________________*/
