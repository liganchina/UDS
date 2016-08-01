/********************************************************************************/
/* @F_PROJECT:          TTM 520                                                 */
/* F_NAME:              VF607_cbk                                               */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Clementina D'Onofrio                                    */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/02/2014                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Clementina D'Onofrio          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 11/11/2013  0.1  CDO
*/

#ifndef VF607_CBK_H_
#define VF607_CBK_H_

#ifdef VF607_IF_OWNER
  #define VF607_EXTERN
#else
  #define VF607_EXTERN    extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef struct
{
  u08  VIN_LO[7];
  u08  VIN_MID[7];
  u08  VIN_HI[7];
  u08  VIN_LO_ready :1;
  u08  VIN_MID_ready :1;
  u08  VIN_HI_ready :1;
  u08  VIN_dummy    :5;
}VINDataSig_rx_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define VIN_DATA_LEN     7U

/*______ G L O B A L - D A T A _______________________________________________*/
VF607_EXTERN VINDataSig_rx_t VF607_VIN_DATA;

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name : VF607_TripABRecoveryOdo                                              */
/*Role : Lock VIN Odometer when TRIP_AB msg missing                           */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : Callback for TRIP_AB Recovery                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN void VF607_TripABRecoveryOdo(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_TRIP_AB_flagSet                                                */
/*Role : SET flag when message absent for VIN odometer                       */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN void VF607_TRIP_AB_flagSet(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINWorkigCondition                                          */
/*Role : VF607 - 1.10 Working Condition Table                                 */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN void VF607_MgmVINWorkigCondition(void);


#endif /* VF607_CBK_H_ */
