/********************************************************************************/
/* @F_PROJECT:          MQB - Volkswagen - Anti Theft Sirene                    */
/* F_NAME:              KEYA_cbk.h                                              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       C.Celozzi                                               */
/* @F_MPROC_TYPE:       Renesas RL78 family - micro R5F10AGFLFB/F13             */
/* F_CREATION_DATE:     08/07/2014                                              */
/* @F_CREATION_SITE:    Bitron S.p.A. - Grugliasco (TO)                         */
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

#ifndef KEYA_CBK_H
#define KEYA_CBK_H

#ifdef KEYA_IF_OWNER
  #define KEYA_EXTERN
#else
  #define KEYA_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#ifdef ACTIVE_IF
  KEYA_EXTERN void KEYA_MngKeyOnCntAlignment(void);
#else
/*----------------------------------------------------------------------------*/
/*Name : KEYA_GetKeyStatus                                                   */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
  KEYA_EXTERN PRES_KeyStatus_t KEYA_GetKeyStatus(void);

#endif

  KEYA_EXTERN void KEYA_CheckKeyStatus(void);

#endif /* end KEYA_CBK_H */

/*_____ E N D _____ (KEYA_cbk.h) _____________________________________________*/
