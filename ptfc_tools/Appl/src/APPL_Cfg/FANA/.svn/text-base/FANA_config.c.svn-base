/******************************************************************************/
/** @file       FANA_config.c                                                 */
/** @title      FAN application interface                                     */
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
| DF           Davide Fogliano		       Polimatica S.r.l.
|-----------------------------------------------------------------------------
| DC           Daniele Cloralio          Ema S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 12/02/2015 0.1  DF      First draft
|-----------------------------------------------------------------------------
| 02/05/15   0.2  DC      Porting to F151M project
|-----------------------------------------------------------------------------
*/

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "FANA.h"
#include "FANA_config.h"

/* Module inhibition filter */
#ifdef __FANA_IS_PRESENT__ 
/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

HeatCoolingLevel_t Fana_CoolLevelFront;

/* Each bit of this variable represent the supply ON/OFF, this variable is shared 
   by the two FAN.
   This variable was introduced because, if the FAN power supply is shared by two 
   or more FAN (max 16), we need to provide power supply if at least one FAN is
   requested ON. Ths beahiovur is necessary for the 3 wire FAN type */
u16 FANA_PowerFan; 

u08 FANA_Levels[4] = {   0U,
                        60U,
                        80U,
                        100U}; /* TODO MAM: da proxare? */

const FANA_CfgTable_t FANA_CfgTable[FANA_MAX_HDL] =
{
/*       HANDLE         |     TYPE       |     PWM_HANDLE     |     SUPPLY_HANDLE    |  NUM_LEVEL  |    LEVELS[]     |  PWM_FAULT_LINE   | SUPPLY_FAULT_LINE | SHARED_SUPPLY_VAR */
/* FANA_BACK_CUSH_FAN */ { FANA_TWO_WIRE,    PWMC_PowerFan,        DOIFC_PowerFan,       4u,          FANA_Levels,      FVMP_FAN_POWER,  FVMP_FAN_POWER,     &FANA_PowerFan   },
};

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

void FANA_CfgInit(void)
{
  /* initialization */
  /* value store in EEPROM will be set after key on */
  Fana_CoolLevelFront = LEVEL_OFF;
}

/* This function is called by FANA_Mgm */
void FANA_CommandUpdate(void)
{
  FANA_SetLevel(FANA_BACK_CUSH_FAN,  Fana_CoolLevelFront);
}

HeatCoolingLevel_t FANA_GetCoolLevel(void)
{
  return Fana_CoolLevelFront;
}

APPL_ResSts_t FANA_SetCoolLevel(FANA_handle_t hdl, HeatCoolingLevel_t level)
{
  APPL_ResSts_t ret_val;

  if ((hdl < FANA_MAX_HDL) && (level < FANA_CfgTable[hdl].NUM_LEVEL))
  {
    Fana_CoolLevelFront = level;
    ret_val = APPL_OK;
  }
  else
  {
    ret_val = APPL_PAR_NOT_OK;
  }

  return ret_val;
}

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
/*______ E N D _____ (FANA_config.c) _________________________________________*/
