/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              DIAGC_if                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/giu/2013                                                 */
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
| 24/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DIAGC_IF_H_
#define DIAGC_IF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIAGC_cfgIf.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

#ifdef DIAGC_IF_OWNER
  #define DIAGC_EXTERN
#else
  #define DIAGC_EXTERN    extern
#endif

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef void (*DIAGC_Callback_t)(u08 groupIdn);

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name :  DIAGC_Init                                                          */
/*Role :  Initialize the internal state machine                               */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DIAGC_EXTERN	void DIAGC_Init(void);

/*----------------------------------------------------------------------------*/
/*Name : DIAGC_Mgm                                                            */
/*Role : Schedule object diagnosis and manage the internal state machine      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints : Call periodically                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DIAGC_EXTERN	void DIAGC_Mgm(void);

/*----------------------------------------------------------------------------*/
/*Name : DIAGC_SetNextGroup                                                   */
/*Role : Select the next group to perform diagnosis                           */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DIAGC_EXTERN  DRVD_RStatus_t DIAGC_SetNextGroup(DIAGC_Group_t group);


/*----------------------------------------------------------------------------*/
/*Name : DIAGC_DiagFsmEvolve                                                  */
/*Role : evolve the diagnosis state machine, this function is used by handle  */
/*       that are not managed directly by DIAGC_Mgm, but the FSM is the same  */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DIAGC_EXTERN  CTRL_FaultState_t DIAGC_DiagFsmEvolve(CTRL_Fault_t newFault, CTRL_State_t cmdState,CTRL_FaultState_t currentState);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DIAGC_IF_H_ */
