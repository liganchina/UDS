/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              DDMP_cbk                                                */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Salvatore Micari                                        */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     11/11/2013                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Salvatore Micari          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 11/11/2013  0.1  SM
*/

#ifndef VF608_CBK_H_
#define VF608_CBK_H_

#ifdef VF608_IF_OWNER
  #define VF608_EXTERN
#else
  #define VF608_EXTERN    extern
#endif

/*----------------------------------------------------------------------------*/
/*Name : VF608_MngOperationalModeSts                                          */
/*Role : 1.11.2 Ignition Working Condition Identification                     */
/*              (ECUB Algorithm Requirments)                                  */
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
VF608_EXTERN void VF608_MngOperationalModeSts(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_EcuRecovery1_ID1                                               */
/*Role : Recovery                                                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : Callback for Ecu Recovery 1 ID1 in VF608.c function         */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_EcuRecovery1_ID1(TLRP_HandlerFast_t Handle);

/*----------------------------------------------------------------------------*/
/*Name : VF608_OpModeStsRecovery                                              */
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
VF608_EXTERN void VF608_OpModeStsRecovery(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_EcuRecovery1_PartC                                             */
/*Role : Recovery                                                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : Callback for Ecu Recovery 1 part C in VF608.c function      */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_EcuRecovery1_PartC(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_EcuRecovery1_PartG                                             */
/*Role : Recovery                                                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : Callback for Ecu Recovery 1 part G in VF608.c function      */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF608_EXTERN void VF608_EcuRecovery1_PartG(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_StatusBhBcm1Rec                                                */
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
VF608_EXTERN void VF608_StatusBhBcm1Rec(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_StatusCcan3Rec                                                 */
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
VF608_EXTERN void VF608_StatusCcan3Rec(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_ID4Description                                                 */
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
VF608_EXTERN void VF608_ID4Description(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_ID5Description                                                 */
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
VF608_EXTERN void VF608_ID5Description(void);

/*----------------------------------------------------------------------------*/
/*Name : VF608_GetOpModeDiag                                                  */
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
VF608_EXTERN PRES_Fault_t VF608_GetOpModeDiag(uint8_t dummy);

VF608_EXTERN OperationalModeSts_t VF608_GetOperationalModeSts(void);

#endif /* VF608_CBK_H_ */
