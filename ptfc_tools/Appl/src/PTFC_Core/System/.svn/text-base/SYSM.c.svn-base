/**
 * @file SYSM.c
 * @brief Core module for SYSMem layer.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @date 02 june 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
/*
|----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     ------------------------------------
| MM           Matteo MASTRODONATO       Bitron S.p.A.
|----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  --------------------------------------------------
| 02/giu/13   0.1  MM      First draft
|----------------------------------------------------------------------------
| 
*/

/*______ I N C L U D E - F I L E S __________________________________________*/

#define SYSM_IF_OWNER

#include "typedefs.h"
#include "SYSM_if.h"

/*______ L O C A L - T Y P E S ______________________________________________*/

/*______ G L O B A L - D A T A ______________________________________________*/

/*______ P R I V A T E - D A T A ____________________________________________*/

/*______ L O C A L - D A T A ________________________________________________*/

/*______ L O C A L - M A C R O S ____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S ______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*______ G L O B A L - F U N C T I O N S ____________________________________*/

/*---------------------------------------------------------------------------*/
/*Name :  SYSM_Init                                                          */
/*Role :  Inizializzazione del layer System                                  */
/*                                                                           */
/*Interface : -                                                              */
/*Pre-condition : -                                                          */
/*Constraints :                                                              */
/*Behavior :                                                                 */
/*  DO                                                                       */
/*    []                                                                     */
/*  OD                                                                       */
/*---------------------------------------------------------------------------*/
void SYSM_Init(void)
{
/*_____ Inizializzazione del layer SYSM ________________*/

/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  LTMS_Init();
#endif

}

/*---------------------------------------------------------------------------*/
/*Name :  SYSM_Init                                                          */
/*Role :  Inizializzazione del layer System                                  */
/*                                                                           */
/*Interface : -                                                              */
/*Pre-condition : -                                                          */
/*Constraints :                                                              */
/*Behavior :                                                                 */
/*  DO                                                                       */
/*    []                                                                     */
/*  OD                                                                       */
/*---------------------------------------------------------------------------*/
void SYSM_PseudoInit(void)
{
/*_____ Inizializzazione del layer System ________________*/

}

/*---------------------------------------------------------------------------*/
/*Name :  SYSM_Init                                                          */
/*Role :  Inizializzazione del layer System                                  */
/*                                                                           */
/*Interface : -                                                              */
/*Pre-condition : -                                                          */
/*Constraints :                                                              */
/*Behavior :                                                                 */
/*  DO                                                                       */
/*    []                                                                     */
/*  OD                                                                       */
/*---------------------------------------------------------------------------*/
void SYSM_PrPseudoWakeup(void)
{
/*_____ Inizializzazione del layer System ________________*/

/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  LTMS_Init();
#endif

}

/**
 * @brief Power off routine for SYSMem layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void SYSM_RunPwrOff(void)
{
/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  LTMS_PwrOff();
#endif
}

/**
 * @brief Power off routine for SYSMem layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void SYSM_PseudoRUNPwrOff(void)
{
/* LTMS module inhibition filter */
#ifdef __LTMS_IS_PRESENT__
  LTMS_PwrOff();
#endif
}

/*______ P R I V A T E - F U N C T I O N S __________________________________*/

/*______ L O C A L - F U N C T I O N S ______________________________________*/

/*______ E N D _____ (Template.c) ___________________________________________*/

