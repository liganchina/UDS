/******************************************************************************/
/** @file       FANA.h                                                        */
/** @title      FAN presentation                                              */
/** @brief      module for FAN management                                     */
/** @date       12/02/2015                                                    */
/** @author     Davide Fogliano                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano		     Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 12/02/2015 0.1  DF      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __FANA_H__
#define __FANA_H__

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "global.h"
#include "APPL_if.h"

/* Module inhibition filter */
#ifdef __FANA_IS_PRESENT__ 

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/
typedef enum FANA_fanType_e
{
  FANA_TWO_WIRE,
  FANA_THREE_WIRE,
}FANA_fanType_t;

typedef struct FANA_CfgTable_s
{
  FANA_fanType_t   TYPE;
  PWMC_Handle_t    PWM_HANDLE;
  DOIFC_Handle_t   SUPPLY_HANDLE;
  u08              NUM_LEVEL; //0 means no level management, the parameter of FANA_SetLevel is used to set drectly the PWM duty cycle
  u08              *LEVELS;  // pointer to array for decoding of FAN level, if NUM_LEVEL s 0 this must be NULL
  FVMP_Handle_t    PWM_FAULT_LINE;
  FVMP_Handle_t    SUPPLY_FAULT_LINE;
  u16              *SHARED_SUPPLY_VAR;
}FANA_CfgTable_t;

/*_____ G L O B A L - D A T A ________________________________________________*/
extern const FANA_CfgTable_t FANA_CfgTable[FANA_MAX_HDL];

/*_____ G L O B A L - M A C R O S ____________________________________________*/
#define FANA_DUTY_0     0U
#define FANA_DUTY_50   50U

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/
extern void FANA_CommandUpdate(void);

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (FANA.h) _________________________________________*/
