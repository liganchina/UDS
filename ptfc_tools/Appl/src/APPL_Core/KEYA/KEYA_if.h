/********************************************************************************/
/* @F_PROJECT:          TTM 520                                                 */
/* F_NAME:              KEYA_if                                                 */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     22/lug/2013                                             */
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
| 22/lug/2013     0.1  Matteo MASTRODONATO
*/

#ifndef KEYA_IF_H_
#define KEYA_IF_H_

#ifdef KEYA_IF_OWNER
	#define KEYA_EXTERN
#else
	#define KEYA_EXTERN		extern
#endif


/*______ I N C L U D E - F I L E S ___________________________________________*/

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

KEYA_EXTERN void KEYA_InitKeyStatus(void);

/*----------------------------------------------------------------------------*/
/*Name : KEYA_IsKeyOnStatus                                                   */
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
KEYA_EXTERN void KEYA_MngKeyStatus(void);
/*----------------------------------------------------------------------------*/
/*Name : KEYA_IsKeyOnStatus                                                   */
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

/*----------------------------------------------------------------------------*/
/*Name : KEYA_IsKeyOnStatus                                                   */
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
KEYA_EXTERN void KEYA_SetKeyStatus(PRES_KeyStatus_t  Appl_KeyStatus_Req);

/*----------------------------------------------------------------------------*/
/*Name : KEYA_IsKeyOnStatus                                                   */
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
KEYA_EXTERN u08 KEYA_IsKeyOnStatus(void);

/*----------------------------------------------------------------------------*/
/*Name : KEYA_MngKeyOnCntAlignment                                            */
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
KEYA_EXTERN void KEYA_MngKeyOnCntAlignment(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* KEYA_IF_H_ */
