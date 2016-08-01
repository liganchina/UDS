/********************************************************************************/
/* @F_PROJECT:          ALM02                                         */
/* F_NAME:              APPL_if                                            */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                                 */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     17/lug/2013                                                 */
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
| 17/lug/2013     0.1  Matteo MASTRODONATO
*/

#ifndef APPL_IF_H_
#define APPL_IF_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/

/* Inclusione interfaccia del Layer inferiore */
#include "PRES_if.h"

/* Include for application modules configuration */
#include "APPL_cfg.h"

/* Inclusione dei tipi proprietari del Layer */
#include "APPL_typedefs.h"

/* NWMA module inhibition filter */
#ifdef __NWMA_IS_PRESENT__
  #include "NWMA_if.h"
#endif
/* UDSA module inhibition filter */
#ifdef __UDSA_IS_PRESENT__
  #include "UDSA_if.h"
#endif
/* KEYA module inhibition filter */
#ifdef __KEYA_IS_PRESENT__
  #include "KEYA_if.h"
#endif
/* SSMA module inhibition filter */
#ifdef __SSMA_IS_PRESENT__
  #include "SSMA_if.h"
#endif
/* HEATA module inhibition filter L.B.*/
#ifdef __HEATA_IS_PRESENT__
  #include "HEATA_if.h"
#endif
/* FANA module inhibition filter */
#ifdef __FANA_IS_PRESENT__
  #include "FANA_if.h"
#endif
/* VF607 module inhibition filter */
#ifdef __VF607_IS_PRESENT__
  #include "VF607_if.h"
#endif
/* VF608 module inhibition filter */
#ifdef __VF608_IS_PRESENT__
  #include "VF608_if.h"
#endif
/* EXMMA module inhibition filter */
#ifdef __EXMMA_IS_PRESENT__
	#include "EXMMA_if.h"
#endif

/* DISPA module inhibition filter */
#ifdef __DISPA_IS_PRESENT__
  #include "DISPA_if.h"
#endif
/* Dichiarazione dell'interfaccia del Layer */
#ifdef APPL_IF_OWNER
	#define APPL_EXTERN
#else
	#define APPL_EXTERN		extern
#endif


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
APPL_EXTERN void APPL_Init(void);

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
APPL_EXTERN void APPL_PseudoInit(void);

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
APPL_EXTERN void APPL_PrPseudoWakeup(void);

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
APPL_EXTERN void APPL_RunPwrOff(void);

/**
 * @brief Power off routine for application layer. It must call all
 * power off routines of the module for power off transition of the
 * power management. for the transition PSEUDO_RUN --> POWER_OFF
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
APPL_EXTERN void APPL_PseudoRUNPwrOff(void);

#endif /* APPL_IF_H_ */
