/******************************************************************************/
/* @F_PROJECT:          TTM 520                                               */
/* F_NAME:              VF608_if.h                                            */
/* @F_PURPOSE:                                                                */
/* @F_CREATED_BY:       S. Micari                                             */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                */
/* F_CREATION_DATE:     06/11/2013                                            */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                  */
/***************************************** (C) Copyright 2013 Bitron S.p.A. ***/

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| SM           Salvatore Micari          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 06/11/2013 0.1  SM      First draft
|
 */

#ifndef VF608_IF_H_
#define VF608_IF_H_

#ifdef VF608_IF_OWNER
#define VF608_EXTERN
#else
#define VF608_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef struct
{
  CmdIgnSts_t       CmdIgnSts;
  CmdIgn_FailSts_t  CmdIgn_FailSts;
}VF608_CmdIgnInfo_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*----------------------------------------------------------------------------*/
/*Name : VF608_Init                                                           */
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
VF608_EXTERN void VF608_Init(void);



void VF608_RecoveryTimeoutMgmt(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_GetOperationalModeSts                                          */
/*Role : Get the State of the state machine Key-On Management                 */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN OperationalModeSts_t VF608_GetOperationalModeSts(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_GetCmdIgnSts                                                   */
/*Role : Get the State of the state machine Key-On Management                 */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_GetCmdIgnSts(VF608_CmdIgnInfo_t* HMSM_CmdIgnSts);

/*----------------------------------------------------------------------------*/
/*Name : VF608_EcuRecovery1                                                    */
/*Role : Recovery                                                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_EcuRecovery1(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_EcuRecovery2                                                    */
/*Role : Recovery                                                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_EcuRecovery2(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* VF608_IF_H_ */
