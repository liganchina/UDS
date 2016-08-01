/******************************************************************************/
/** @file       LPMS_cfgIf.h                                                  */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Public interface of configuration files of ADCD module for    */
/**             user settings. This file is developed for Renesas RL78 family */
/**             - micro R5F10AGFLFB/F13. The requirement used for this driver */
/**             is the chapter 12 of the relative hw datasheet(v2.0).         */
/** @date       21/07/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 21/07/2014 0.1  CC      First draft. For this first release will
|                         be not implmented:
|                         - the SNOOZE mode function management (TODO SGR)
|                         - the TEST mode (TODO SGR)
|                         - the HW trigger mode is partially implemented then
|                           for now isn't usable (TODO SGR)
|-----------------------------------------------------------------------------
*/

#ifndef __LPMS_CFGIF_H
#define __LPMS_CFGIF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/


#ifdef LPMS_CFGIF_OWNER
  #define LPMS_CFG_EXTERN
#else
  #define LPMS_CFG_EXTERN   extern
#endif

/**
  * Può assumere la combinazione dei valori:
  * - LPMS_POWER_OFF_STATE
  * - LPMS_LOW_POWER_STATE
  * - LPMS_PSEUDO_RUN_STATE
  */
#define LPMS_POWER_OFF_STATE          (0x01u)
#define LPMS_LOW_POWER_STATE          (0x02u)
#define LPMS_PSEUDO_RUN_STATE         (0x04u)


#define LPMS_FULL_FSM_SUBSET  (LPMS_POWER_OFF_STATE   |\
                               LPMS_LOW_POWER_STATE   |\
                               LPMS_PSEUDO_RUN_STATE  )


/**
  * Può assumere la combinazione dei valori:
  * - LPMS_POWER_OFF_STATE
  * - LPMS_LOW_POWER_STATE
  * - LPMS_PSEUDO_RUN_STATE
  */
#define LPMS_FSM_SUBSET       (LPMS_POWER_OFF_STATE   |\
                               LPMS_PSEUDO_RUN_STATE  )


/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum LPMS_MsmEcuType_e
{
  LPMS_MSM_ECU_DRIVER    = 0,
  LPMS_MSM_ECU_PASSENGER = 1,
}LPMS_MsmEcuType_t;


typedef enum LPMS_MsmEquipment_e
{
  LPMS_MSM_BASE = 0,
  LPMS_MSM_PREMIUM,
  LPMS_MSM_PERFORMANCE,
  LPMS_MSM_LUXURY
} LPMS_MsmEquipment_t;


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/**
  * Refresh the external watchdog 
  */
#define LPMS_RefreshExtWatchDog()\
{\
  (DIOD_GetLevel(DIOD_ExtWatchDog) == L_LOW) ?\
  (void)DIOD_SetLevel(DIOD_ExtWatchDog, L_HIGH) :\
  (void)DIOD_SetLevel(DIOD_ExtWatchDog, L_LOW);\
}

/** 
  * Refresh the internal watchdog 
  */
#define LPMS_RefreshInternalWatchDog()      WDT_Restart()

/** 
  * Refresh the external and internal watchdog 
  */
#define LPMS_RefreshAllWatchDog()\
{\
  LPMS_RefreshExtWatchDog()\
  LPMS_RefreshInternalWatchDog();\
}

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

LPMS_CFG_EXTERN LPMS_MsmEcuType_t   LPMS_GetMsmEcuType(void);

LPMS_CFG_EXTERN LPMS_MsmEquipment_t LPMS_GetMsmEquipment(void);

#endif /* end __LPMS_CFGIF_H */

/*_____ E N D _____ (LPMS_cfgIf.h) ___________________________________________*/
