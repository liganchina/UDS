#ifndef __KEYA_H
#define __KEYA_H

/******************************************************************************/
/* @F_PROJECT:          ALM Iveco                                             */
/* F_NAME:              KEYA.h                                                */
/* @F_PURPOSE:                                                                */
/* @F_CREATED_BY:       S.Micari                                              */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                */
/* F_CREATION_DATE:     10/06/2013                                            */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                  */
/******************************************* (C) Copyright 2012 Bitron S.p.A. */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| SM           Salvatore Micari          Bitron S.p.A.
|
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 10/06/2013  0.1   SM    First draft
|
*/


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "APPL_if.h"

/* Module inhibition filter */
#ifdef __KEYA_IS_PRESENT__

#include "KEYA_config.h"
#include "KEYA_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/


/*______ G L O B A L - T Y P E S _____________________________________________*/


typedef enum
{
  NO_TRANSITION = 0,
  TRANSITION
} KEYA_KeyOffOnTran_t;


/*______ G L O B A L - D A T A _______________________________________________*/

/* _____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name : KEYA_GetKeyOffOnTransition                                           */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :  ECU's Life Counter                                              */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
KEYA_KeyOffOnTran_t KEYA_GetKeyOffOnTransition(void);


#endif /* end __KEYA_IS_PRESENT__ */

#endif /* end __KEYA_H */

/*_____E N D _______ (TRMA.h) ________________________________________________*/
