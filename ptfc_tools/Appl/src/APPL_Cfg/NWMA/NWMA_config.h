/**
 * @file NWMA_config.h
 * @brief Private configuration interface of NetWork Management module.
 * In this module is implemented the network management FCA for NextGen network. 
 * The reference standard is N07320_ed5.
 * The main contents of this file are the configuration macros for particular
 * actions to associate to event handler during state transitions.
 *
 * @version 0.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 2 february 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| GB           Giuseppe Barberio         Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  -----------------------------------------------
| 02 feb 15  0.1  CC      First official release (whithout DLL error FSM)
| 28 may 15  0.2  GB CC   DLL error FSM completed
|-----------------------------------------------------------------------------
*/

#ifndef __NWMA_CFG_H
#define __NWMA_CFG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "NWMA.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition to NET_OFF state
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_NetOffNotifyToAppl()\
{\
  TLRP_ResetSlow(TLRP_NwmaSaTimer);\
  TLRP_ResetFast(TLRP_NwmaSleepShortTimer);\
  TLRP_ResetSlow(TLRP_NwmaSleepLongTimer);\
  TLRP_ResetFast(TLRP_NwmaBusOffTimer);\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition to NET_STARTUP or NET_CHECK state
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_NetWakeupNotifyToAppl()\
{\
  NETP_NotifyNetSts(NETP_NET_ON);\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition to NET_ON state
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_NetOnNotifyToAppl()\
{\
  NETP_EnableRxMsgTOutMng();\
  FVMP_NetOnEvent();\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition to NET_SILENT state
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_NetSilentNotifyToAppl()\
{\
  NETP_NotifyNetSts(NETP_NET_OFF);\
  NETP_DisableRxMsgTOutMng();\
  FVMP_NetOffEvent();\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E1
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A1Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E2
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A2Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E3
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A3Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E4
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A4Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  (void)LPMS_SetEvent(LPMS_PR_PSEUDO_WAKEUP);\
  NWMA_NetOnNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E5
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A5Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetSilentNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E6
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A6Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_E6Occour = TRUE;\
  NWMA_NetOnNotifyToAppl()\
  NWMA_NetWakeupNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E7
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A7Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetWakeupNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E9
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A9Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetWakeupNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E10
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A10Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E11
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A11Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetOffNotifyToAppl()\
  (FUNP_IsShortComfortTimer()==TRUE ? (LPMS_SetEvent(LPMS_PWR_OFF)) : ((TLRP_GetSlow(TLRP_Comfort_Timer)==0U) ? (LPMS_SetEvent(LPMS_PWR_OFF)) : (NWMA_NmStateReq(NWMA_NET_CHECK_REQ))));\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E12
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A12Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetOffNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E13
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A13Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetWakeupNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E14
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A14Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
  NWMA_NetWakeupNotifyToAppl()\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E15
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A15Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E16
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @return None
 */
#define NWMA_A16Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}


/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E1 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A1Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E2 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A2Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E3 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A3Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E4 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A4Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E5 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A5Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E6 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A6Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E7 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A7Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/**
 * @brief In this macro must insert all actions to use for system/application
 * purpose during the transition of E8 of DLL FSM
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @return None
 */
#define NWMA_DLLERR_A8Cfg()\
{\
  /* For this event insert here all actions related to other sw module */\
}

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* end __NWMA_CFG_H */

/*______ E N D _____ (NWMA_config.h) _________________________________________*/
