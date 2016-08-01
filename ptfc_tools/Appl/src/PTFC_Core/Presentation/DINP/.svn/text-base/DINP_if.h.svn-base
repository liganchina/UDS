/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                         */
/* F_NAME:              DIAD_if                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     10/giu/2013                                                 */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 10/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DINP_IF_H_
#define DINP_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef DINP_IF_OWNER
	#define DINP_EXTERN
#else
	#define DINP_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DINP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef void (*DINP_Callback_t)(void);

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
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
DINP_EXTERN	void 	      DINP_Init(void);
DINP_EXTERN	PRES_State_t  DINP_GetState(DINP_Handle_t chan);
DINP_EXTERN	void 	      DINP_Mgm(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DINP_IF_H_ */
