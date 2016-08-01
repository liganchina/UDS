/**
 * @file HBRGC.c
 * @brief Source for user configuration of Infineon BTM7752 module. In this file,
 * by configuration look-up tables, must configured the driver properties.
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

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "HBRGC.h"

/* Module inhibition filter */
#ifdef __HBRGC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

const HBRGC_CfgTable_t HBRGC_CfgTable[HBRGC_HDL_MAX] = {

    /* Handle                         INPUT_CHAN1       INPUT_CHAN2         INHIBIT_CHAN        ACTIVE_LEVEL       FBK_CHAN       SHORT_CIRCUIT_THRES     OPEN_CIRCUIT_THRES    REC_RETRY    REC_WAIT_CYCLES   DIAG_DEBOUNCE   ERROR_MODE_THRES*/

    /* HBRGC_BeltCarrier        */ {DIOD_CmdBeltFd,     DIOD_CmdBeltBk,     DIOD_BeltINH,         L_HIGH,       ADCC_BeltDiag,           600U,                   8U,               5U,             5U,             2U /*, 900U */  },
};


/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

void HBRGC_UserCfg(void)
{
}

DRVD_RStatus_t  HBRGC_BeltCarrierSetCmd    (uint8_t channel, CTRL_State_t state)
{
  DRVD_RStatus_t valueReturn;
  HBRGC_Handle_t hdl;

  /* select handle for the belt carrier to be moved */
  hdl = HBRGC_BeltCarrier;

  if (channel < HBRGC_INPUT_MAX)
  {
    valueReturn = HBRGC_SetState(hdl, (HBRGC_InputSelection_t) channel, state);
  }
  else 
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return valueReturn;
}

CTRL_Fault_t    HBRGC_GetBeltCarrierDiag   (HBRGC_Handle_t hdl)
{
  CTRL_Fault_t retval;

  retval = HBRGC_GetDiag(HBRGC_BeltCarrier);

  return retval;
}

/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __HBRGC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

