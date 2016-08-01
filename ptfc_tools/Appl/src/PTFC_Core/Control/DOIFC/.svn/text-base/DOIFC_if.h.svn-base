/********************************************************************************/
/* @F_PROJECT:          ALM02                                                   */
/* F_NAME:              DOIFC_if                                                */
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
| ----------  ---  ------  ----------------------------------------------------
| 12/06/15    0.2   DAF     New Diagnostic management with severe short crcuit recovery
*/

#ifndef DOIFC_IF_H_
#define DOIFC_IF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DOIFC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#ifdef DOIFC_IF_OWNER
  #define DOIFC_EXTERN
#else
  #define DOIFC_EXTERN    extern
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
DOIFC_EXTERN  void            DOIFC_Init        (void);
DOIFC_EXTERN  DRVD_RStatus_t  DOIFC_SetState    (DOIFC_Handle_t hdl, CTRL_State_t state);
DOIFC_EXTERN  CTRL_State_t    DOIFC_GetState    (DOIFC_Handle_t hdl);
DOIFC_EXTERN  CTRL_Fault_t    DOIFC_GetDiag     (DOIFC_Handle_t hdl);
DOIFC_EXTERN  CTRL_State_t    DOIFC_GetDiagState(DOIFC_Handle_t hdl);
DOIFC_EXTERN  DRVD_RStatus_t  DOIFC_FreezeState (DOIFC_Handle_t hdl, CTRL_State_t enableFreeze);
DOIFC_EXTERN  void            DOIFC_Mgm         (void);

/* Diagnosis interface */
DOIFC_EXTERN  bool            DOIFC_PerformDiag (u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState);
DOIFC_EXTERN  void            DOIFC_DecodeDiag  (u08 hdl, CTRL_FaultState_t faultState);
DOIFC_EXTERN  DRVD_RStatus_t  DOIFC_SetFault    (DOIFC_Handle_t hdl, CTRL_Fault_t fault);
DOIFC_EXTERN  void            DOIFC_PerformAndDecodeDiag(DOIFC_Handle_t hdl);
DOIFC_EXTERN  void            DOIFC_DiagExtReset(DOIFC_Handle_t hdl);

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
DOIFC_EXTERN  void            DOIFC_EnableDisable(DOIFC_Handle_t hdl, CTRL_EnSts_t state);
/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DOIFC_IF_H_ */
