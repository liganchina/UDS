/**
 * @file HBRGC_if.c
 * @brief Public interfaces of driver for Infineon BTM7752 h-bridge chipset
 * @author Daniele Cloralio
 * @date 08 apr 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
|              Daniele CLORALIO          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 08/apr/2015     0.1  Daniele CLORALIO
 */

#ifndef HBRGC_IF_H_
#define HBRGC_IF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "HBRGC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

#ifdef HBRGC_IF_OWNER
  #define HBRGC_EXTERN
#else
  #define HBRGC_EXTERN    extern
#endif

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/* enum for the input of the chip that are visible to the upper layer */
typedef enum HBRGC_InputSelection_e
{
  HBRGC_INPUT_IN1,
  HBRGC_INPUT_IN2,
  HBRGC_INPUT_MAX
} HBRGC_InputSelection_t;

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
HBRGC_EXTERN  void            HBRGC_Init        (void);
HBRGC_EXTERN  DRVD_RStatus_t  HBRGC_SetState    (HBRGC_Handle_t hdl, HBRGC_InputSelection_t input, CTRL_State_t state);
HBRGC_EXTERN  CTRL_State_t    HBRGC_GetState    (HBRGC_Handle_t hdl, HBRGC_InputSelection_t input);
HBRGC_EXTERN  CTRL_Fault_t    HBRGC_GetDiag     (HBRGC_Handle_t hdl);
HBRGC_EXTERN  CTRL_State_t    HBRGC_GetDiagState(HBRGC_Handle_t hdl);
HBRGC_EXTERN  void            HBRGC_Mgm         (void);
HBRGC_EXTERN  void            HBRGC_PerformAndDecodeDiag(HBRGC_Handle_t hdl);

/* Diagnosis interface */
HBRGC_EXTERN  bool            HBRGC_PerformDiag (u08 hdl, CTRL_State_t *cmdState, CTRL_Fault_t *fault, CTRL_FaultState_t *faultState);
HBRGC_EXTERN  void            HBRGC_DecodeDiag  (u08 hdl, CTRL_FaultState_t faultState);
HBRGC_EXTERN  DRVD_RStatus_t  HBRGC_SetFault    (HBRGC_Handle_t hdl, CTRL_Fault_t fault);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* HBRGC_IF_H_ */
