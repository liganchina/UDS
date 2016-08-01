/********************************************************************************/
/* @F_PROJECT:          TTM520                                                  */
/* F_NAME:              VF607_if.h                                              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Clementina D'ONOFRIO                                    */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     28/Ott/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Clementina D'ONOFRIO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date            Ver  Author               Description
| ----------      ---  ------               ----------------------------------
| 28/Ott/2013     0.1  Clementina D'ONOFRIO
*/

#ifndef VF607_IF_H_
#define VF607_IF_H_

#ifdef VF607_IF_OWNER
	#define VF607_EXTERN
#else
	#define VF607_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef enum
{
  VIN_ODOMETER_INIT = 0x00U,
  VIN_ODOMETER_PENDING,
  VIN_ODOMETER_DONE,
}VIN_OdometerInitSts_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/
VF607_EXTERN VIN_OdometerInitSts_t VIN_OdometerInitSts;

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name : VF607_Init                                                           */
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
VF607_EXTERN void VF607_Init(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_VINLock                                                        */
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
VF607_EXTERN VINLockStatus_t VF607_GetVINLock(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINCurrent                                                  */
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
VF607_EXTERN void VF607_MgmVINCurrent(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINOriginal                                                 */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*DO                                                                          */
/*  []                                                                        */
/*OD                                                                          */
/*----------------------------------------------------------------------------*/
VF607_EXTERN void VF607_MgmVINOriginal(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_VINOdometer                                                    */
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
VF607_EXTERN void VF607_VINOdometer(void);

/*----------------------------------------------------------------------------*/
/*Name : VF607_VINdelivery                                                    */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN u08 VF607_VINdelivery(VinData_t VINData);

/*----------------------------------------------------------------------------*/
/*Name : VF607_TRIP_AB_flagReset                                              */
/*Role : RESET flag when message present for VIN odometer                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN void VF607_TRIP_AB_flagReset(void);

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
/*Name : VF607_Seed2Key                                                    */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
VF607_EXTERN u32 VF607_Seed2Key(u32 seed);

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* VF607_IF_H_ */
