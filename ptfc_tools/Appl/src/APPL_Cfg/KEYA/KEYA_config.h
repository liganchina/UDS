/********************************************************************************/
/* @F_PROJECT:          MQB - Volkswagen - Anti Theft Sirene                    */
/* F_NAME:              KEYA_config.h                                           */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       C.Celozzi                                               */
/* @F_MPROC_TYPE:       Renesas RL78 family - micro R5F10AGFLFB/F13             */
/* F_CREATION_DATE:     08/07/2014                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2014 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| MD           Michele Di Gangi          Bitron S.p.A.
| MM           Massimo Miletto           Brain Technologies S.r.l.
| AF           Adriano Finotti           T&T S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/07/2014 0.1  CC      First draft used by TTM FCA project
|-----------------------------------------------------------------------------
*/

#ifndef KEYA_CONFIG_H
#define KEYA_CONFIG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/* Call the following routines every key transition */
#define KEYA_STS_CHANGED_EVENT(x)\
{\
  DDMP_KeyStsChanged(x);\
  NETP_KeyStsChanged(x);\
  FVMP_KeyStsChanged(x);\
  EXMMA_KeyStsChanged(x);\
  HEATA_KeyStsChanged(x);\
}

/* Call the following routines only for key transition OFF --> ON */
#define KEYA_STS_OFF_TO_ON_EVENT()\
{\
  FVMP_KeyOffOnTrans();\
  /* Reset KeyStatus timer */\
  TLRP_ResetSlow(TLRP_KeyOffStatus);\
  TLRP_ResetSlow(TLRP_Comfort_Timer);\
}

/* Call the following routines only for key transition ON --> OFF */
#define KEYA_STS_ON_TO_OFF_EVENT()\
{\
  DISPA_KeyOffEvent();\
}

/* Call the following routines every time there is a cranking event */
#define KEYA_CRANK_CHANGED_EVENT(x)\
{\
}

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#endif /* end KEYA_CONFIG_H */

/*_____ E N D _____ (KEYA_config.h) __________________________________________*/
