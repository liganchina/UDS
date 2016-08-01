/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              DOVFC_if                                                */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     21/giu/2013                                             */
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
| 21/giu/2013     0.1  Matteo MASTRODONATO
*/

#ifndef DOVFC_IF_H_
#define DOVFC_IF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DOVFC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#ifdef DOVFC_IF_OWNER
  #define DOVFC_EXTERN
#else
  #define DOVFC_EXTERN    extern
#endif

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
DOVFC_EXTERN  void            DOVFC_Init         (void);
DOVFC_EXTERN  DRVD_RStatus_t  DOVFC_SetState     (DOVFC_Handle_t hdl, CTRL_State_t state);
DOVFC_EXTERN  CTRL_State_t    DOVFC_GetState     (DOVFC_Handle_t hdl);
DOVFC_EXTERN  CTRL_Fault_t    DOVFC_GetDiag      (DOVFC_Handle_t hdl);
DOVFC_EXTERN  CTRL_State_t    DOVFC_GetDiagState (DOVFC_Handle_t hdl);
DOVFC_EXTERN  DRVD_RStatus_t  DOVFC_FreezeState  (DOVFC_Handle_t hdl, CTRL_State_t freezeEnable);

/* Diagnosis interface */
DOVFC_EXTERN  bool            DOVFC_PerformDiag (u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState);
DOVFC_EXTERN  void            DOVFC_DecodeDiag  (u08 hdl, CTRL_FaultState_t faultState);
DOVFC_EXTERN  DRVD_RStatus_t  DOVFC_SetFault    (DOVFC_Handle_t hdl, CTRL_Fault_t fault);

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
DOVFC_EXTERN  void            DOVFC_EnableDisable(DOVFC_Handle_t hdl, CTRL_EnSts_t state);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DOVFC_IF_H_ */
