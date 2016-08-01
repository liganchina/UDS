/******************************************************************************/
/** @file       HEATA.h                                                      */
/** @title      Heater presentation                                           */
/** @brief      module for Heater management                                  */
/** @date       08/05/2015                                                    */
/** @author     Livio Bastonero                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| LB           Livio Bastonero         Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  LB      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __HEATER_H
#define __HEATER_H


/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "APPL_if.h"
#include "HEATA_if.h"

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

typedef struct HEATA_CfgTable_s
{
  PWMC_Handle_t    PWM_HANDLE;
  uint8_t          NUM_LEVEL;
  uint8_t          SUSP_CMD;
  FVMP_Handle_t    PWM_FAULT_LINE;
  FVMP_Handle_t    NTC_FAULT_LINE;
  SNSP_Handle_t    TEMP_HANDLE;
}HEATA_CfgTable_t;


/*_____ G L O B A L - D A T A ________________________________________________*/
extern const HEATA_CfgTable_t HEATA_CfgTable[HEATA_MAX_HDL];

/*_____ G L O B A L - M A C R O S ____________________________________________*/
#define HEATA_DUTY_OFF    0U
#define HEATA_DUTY_ON   100U

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/
extern void HEATA_CommandUpdate(void);

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

APPL_ResSts_t HEATA_TempReg(HEATA_handle_t hdl,uint8_t level);
APPL_ResSts_t HEATA_Cycle(HEATA_handle_t hdl,uint8_t level);
CTRL_Fault_t HEATA_ResetLine(HEATA_handle_t hdl);
CTRL_Fault_t HEATA_SetLine(HEATA_handle_t hdl);

#endif
#endif
/*______ E N D _____ (HEATA.h) _________________________________________*/
