/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                         */
/* F_NAME:              AVGP_if                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     07/giu/2013                                                 */
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
| 07/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef AVGP_IF_H_
#define AVGP_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef AVGP_IF_OWNER
	#define AVGP_EXTERN
#else
	#define AVGP_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "AVGP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

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
AVGP_EXTERN	void 		 AVGP_Init(void);
AVGP_EXTERN	void		 AVGP_Mgm(void);
AVGP_EXTERN	u16 		 AVGP_GetFast(AVGP_Handle_t chan);
AVGP_EXTERN	u16 		 AVGP_GetSlow(AVGP_Handle_t chan);
AVGP_EXTERN PRES_Fault_t AVGP_GetDiagFast(AVGP_Handle_t  chan);
AVGP_EXTERN PRES_Fault_t AVGP_GetDiagSlow(AVGP_Handle_t  chan);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* AVGP_IF_H_ */
