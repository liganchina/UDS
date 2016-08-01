/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              FVMP_if                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     02/lug/2013                                                 */
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
| 02/lug/2013     0.1  Matteo MASTRODONATO
*/

#ifndef FVMP_IF_H_
#define FVMP_IF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef FVMP_IF_OWNER
	#define FVMP_EXTERN
#else
	#define FVMP_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "FVMP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef void (*FVMP_FaultValidCbk_t)(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive); /* Fault Validation Callback 	*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

FVMP_EXTERN void FVMP_PseudoInit(void);

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
FVMP_EXTERN void FVMP_Init(void);

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
/*Role :                                                                      */
/*                                                                            */
/*Interface : FVMP_Reset                                                      */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*   Dopo un reset del FVMP, verrà chiamata nuovamente la callback di fault   */
/*    sia in caso di conferma sia in caso di svalidazione del fault           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
FVMP_EXTERN void FVMP_Reset(void);

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
/*Role :                                                                      */
/*                                                                            */
/*Interface : FVMP_ResetLine                                                  */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*   Dopo un reset del FVMP, verrà chiamata nuovamente la callback di fault   */
/*    sia in caso di conferma sia in caso di svalidazione del fault           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
FVMP_EXTERN DRVD_RStatus_t FVMP_ResetLine(FVMP_Handle_t hdl);

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
FVMP_EXTERN void FVMP_Mgm(void);

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
FVMP_EXTERN DRVD_RStatus_t FVMP_GetDiag(FVMP_Handle_t hdl, PRES_Fault_t* fault, bool* destructive);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* FVMP_IF_H_ */
