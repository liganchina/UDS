/******************************************************************************/
/** @file       APPL.c                                                        */
/** @title      APPLication layer source code                                 */
/** @brief      File containing the routines for power management of the      */
/**             Application layer                                             */
/** @date       24/09/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/09/14   0.1  CC      First draft
|-----------------------------------------------------------------------------
| 26/09/14   1.0  CC      Insert the routine APPL_PwrOff
|-----------------------------------------------------------------------------
*/

#define APPL_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "APPL_if.h"

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name :  APPL_Init                                                           */
/*Role :  Inizializzazione del layer Application                              */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void APPL_Init(void)
{
/* NWMA module inhibition filter */
#ifdef __NWMA_IS_PRESENT__
  NWMA_Init();
#endif

/* UDSA module inhibition filter */
#ifdef __UDSA_IS_PRESENT__
  UDSA_Init();
#endif

/* KEYA module inhibition filter */
#ifdef __KEYA_IS_PRESENT__
  KEYA_InitKeyStatus();
#endif

/* DISPA inhibition filter */
#ifdef __DISPA_IS_PRESENT__
  DISPA_Init();
#endif

/* Smart switch management inhibition filter */
#ifdef __SSMA_IS_PRESENT__
  SSMA_Init();
#endif

#ifdef __HEATA_IS_PRESENT__
  HEATA_Init(); // L.B.
#endif

/* ventilation  management inhibition filter */
#ifdef  __FANA_IS_PRESENT__
  FANA_Init();
#endif

/* VF607 inhibition filter */
#ifdef  __VF607_IS_PRESENT__
  VF607_Init();
#endif

/* VF608 inhibition filter */
#ifdef  __VF608_IS_PRESENT__
  VF608_Init();
#endif

/* Mirrors management inhibition filter */
#ifdef __EXMMA_IS_PRESENT__
  EXMMA_Init();
#endif
}

/*----------------------------------------------------------------------------*/
/*Name :  APPL_PseudoInit                                                     */
/*Role :  Inizializzazione del layer Application                              */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void APPL_PseudoInit(void)
{
/* NWMA module inhibition filter */
#ifdef __NWMA_IS_PRESENT__
  NWMA_Init();
#endif
}

/*----------------------------------------------------------------------------*/
/*Name :  APPL_PrPseudoWakeup                                                 */
/*Role :  Inizializzazione del layer Application                              */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void APPL_PrPseudoWakeup(void)
{
/* UDSA module inhibition filter */
#ifdef __UDSA_IS_PRESENT__
  UDSA_Init();
#endif
/* KEYA module inhibition filter */
#ifdef __KEYA_IS_PRESENT__
  KEYA_InitKeyStatus();
#endif
/* Smart switch management inhibition filter */
#ifdef __SSMA_IS_PRESENT__
  SSMA_Init();
#endif
#ifdef __HEATA_IS_PRESENT__
  HEATA_Init(); // L.B.
#endif
  /* FANA model inhibition filter */
#ifdef  __FANA_IS_PRESENT__
  FANA_Init();
#endif
/* Mirrors management inhibition filter */
#ifdef __EXMMA_IS_PRESENT__
    EXMMA_Init();
#endif
/* DISPA model inhibition filter */
#ifdef __DISPA_IS_PRESENT__
  DISPA_Init();
#endif
}

/**
 * @brief Power off routine for application layer. It must call all
 * power off routines of the module for power off transition of the
 * power management. It is called for the transition RUN --> POWER_OFF
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void APPL_RunPwrOff(void)
{
/* DISPA module inhibition filter */
#ifdef __DISPA_IS_PRESENT__ 
  DISPA_PwrOff();
#endif
}

/**
 * @brief Power off routine for application layer. It must call all
 * power off routines of the module for power off transition of the
 * power management. It is called for the transition PSEUDO_RUN --> POWER_OFF
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void APPL_PseudoRUNPwrOff(void)
{
/* DISPA module inhibition filter */
#ifdef __DISPA_IS_PRESENT__
  DISPA_PseudoRUNPwrOff();
#endif
}

/*______ E N D _____ (APPL.c) ________________________________________________*/
