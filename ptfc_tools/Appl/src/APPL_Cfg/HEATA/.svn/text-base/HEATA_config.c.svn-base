/******************************************************************************/
/** @file       HEATA_config.c                                                */
/** @title      FAN application interface                                     */
/** @brief      module for FAN management                                     */
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
| LB           Livio Bastonero		     Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 19/06/2015 0.1  LB      First draft
|-----------------------------------------------------------------------------
*/

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "HEATA.h"
#include "HEATA_config.h"

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__
/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

const HEATA_CfgTable_t HEATA_CfgTable[HEATA_MAX_HDL] =
{
/*   PWM_HANDLE  |    NUM_LEVEL |   SUSP_CMD  |     PWM_FAULT_LINE        |   NTC_FAULT_LINE    |    TEMP_HANDLE     */
{    PWMC_HeatDrv,        3u,         0xE9U,      FVMP_DRIVER_SEAT_HEATER,      FVMP_NTC_DRV,        SNSP_SEAT_DRV    },
{    PWMC_HeatPass,       3u,         0xE9U,      FVMP_PSNGR_SEAT_HEATER,       FVMP_NTC_PSG,        SNSP_SEAT_PASS   },
{    PWMC_HeatSteer,      1u,         0xE9U,      FVMP_STEERW_HEATER,           FVMP_NTC_STEERW,     SNSP_STEER_WHEEL }
};
/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/* This function is called by FANA_Mgm */
void HEATA_CommandUpdate(void)
{
}

void HEATA_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
  if (CMMD_OperationalModeSts != CMMD_IGNITION_ON_ENGON)
  {
    HEATA_SetLevel(HEATA_STW, 0U);
    HEATA_SetLevel(HEATA_SEAT_DRV, 0U);
    HEATA_SetLevel(HEATA_SEAT_PSG, 0U);
  }
}
/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
/*______ E N D _____ (HEATA_config.c) _________________________________________*/
