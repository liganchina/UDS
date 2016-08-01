/**
 * @file SSMA.c
 * @brief Smart Switch management: source code of ....
 * @n The main module features/services are:
 * @li ...
 * </ul>
 *
 * @version 0.1.
 * @author Gianpiero Lenta (Bitron S.p.A.)
 * @date 11 NOV 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/************************** (C) Copyright 2013 Bitron S.p.A. ***/

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero lenta           Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 11/11/2014  0.1  GIL    First release
|
*/

/* !!! NOT MOVE !!! */
#define SSMA_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "SSMA.h"

#ifdef __SSMA_IS_PRESENT__

/*______ E X T E R N A L - D A T A ___________________________________________*/


/*______ I N C L U D E - F I L E S ___________________________________________*/


/*______ L O C A L - D E F I N E _____________________________________________*/


/*______ L O C A L - T Y P E S _______________________________________________*/


/*______ L O C A L - D A T A _________________________________________________*/

CAND_TxMsgName_t           Ssma_MsmStatus;
SSMA_StateMachine_t        Ssma_StateMachine;

SSMA_SmartSwitchPressReq_t Ssma_ButtonSts[SSMA_COMFORT_MAX_STS];


/*______ L O C A L - M A C R O S _____________________________________________*/


/*______ G L O B A L - D A T A _______________________________________________*/


/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/


/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief Initialization routine of the SSMA module.
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void SSMA_Init(void)
{
  uint8_t i;

  Ssma_StateMachine = SSMA_COMFORT_IDLE;

  for (i = 0; i < SSMA_COMFORT_MAX_STS; i++)
  {
    Ssma_ButtonSts[i] = SSMA_NOT_PRESS;
  }

  if( LPMS_GetMsmEcuType() == LPMS_MSM_ECU_DRIVER )
  {
    Ssma_MsmStatus = CAND_MSMD_STATUS;
  }
  else if( LPMS_GetMsmEcuType() == LPMS_MSM_ECU_PASSENGER )
  {
    Ssma_MsmStatus = CAND_MSMP_STATUS;
  }
  else
  {

  }
}

/**
 * @brief Callback routine called from network rx event on message CAN_MSG_2 (MCU_msmCommands)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void SSMA_ComfortNetCbk(void)
{
  uint8_t i;
  SSMA_StateMachine_t Ssma_StateMachineOld;

  Ssma_StateMachineOld = Ssma_StateMachine;

  if(LPMS_GetMsmEcuType() == LPMS_MSM_ECU_DRIVER)
  {
    Ssma_StateMachine = (SSMA_StateMachine_t) MCU_msmCommands.bit.MCU_DriverComfortFunctionSel;
  }
  else
  {
    Ssma_StateMachine = (SSMA_StateMachine_t) MCU_msmCommands.bit.MCU_PassengerComfortFunctionSel;
  }

  if(Ssma_StateMachine >= SSMA_COMFORT_SNA)
  {
    Ssma_StateMachine = SSMA_COMFORT_IDLE;
  }

  /* If State machine is modified from central display */
  if (Ssma_StateMachineOld != Ssma_StateMachine)
  {
    for (i = 0; i < SSMA_COMFORT_MAX_STS; i++)
    {
      /* Clean all button pressed */
      if (Ssma_ButtonSts[i] != SSMA_NOT_PRESS)
      {
        Ssma_ButtonSts[i] = SSMA_NOT_PRESS;
        if (SSMA_CfgTable[i].Callback != NULL)
        {
          SSMA_CfgTable[i].Callback();
        }
      }
    }
  }
}


/**
 * @brief Callback routine generated on smart switch button 1 press event
 * send message CAN_MSG_1 (MS \Mx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void SSMA_ComfortButton1Cbk(void)
{
  const SSMA_CfgTable_t *Ptr = &SSMA_CfgTable[Ssma_StateMachine];

  if(DINP_GetState(DINP_SS_1) == S_ON)
  {
    Ssma_ButtonSts[Ssma_StateMachine] = Ptr->ButtonEnabled[SSMA_BUTTON_1];

    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_BUTTON_UP;
  }
  else
  {
    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_NOT_PRESS;
    Ssma_ButtonSts[Ssma_StateMachine] = SSMA_NOT_PRESS;
  }

  NETP_SendMsgReq(Ssma_MsmStatus);

  if (SSMA_CfgTable[Ssma_StateMachine].Callback != NULL)
  {
    SSMA_CfgTable[Ssma_StateMachine].Callback();
  }
}

/**
 * @brief Callback routine generated on smart switch button 1 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void SSMA_ComfortButton2Cbk(void)
{
  const SSMA_CfgTable_t *Ptr = &SSMA_CfgTable[Ssma_StateMachine];

  if(DINP_GetState(DINP_SS_2) == S_ON)
  {
    Ssma_ButtonSts[Ssma_StateMachine]  = Ptr->ButtonEnabled[SSMA_BUTTON_2];

    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_BUTTON_FORW;
  }
  else
  {
    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_NOT_PRESS;
    Ssma_ButtonSts[Ssma_StateMachine]  = SSMA_NOT_PRESS;
  }

  NETP_SendMsgReq(Ssma_MsmStatus);

  if (SSMA_CfgTable[Ssma_StateMachine].Callback != NULL)
  {
    SSMA_CfgTable[Ssma_StateMachine].Callback();
  }
}

/**
 * @brief Callback routine generated on smart switch button 2 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void SSMA_ComfortButton3Cbk(void)
{
  const SSMA_CfgTable_t *Ptr = &SSMA_CfgTable[Ssma_StateMachine];

  if(DINP_GetState(DINP_SS_3) == S_ON)
  {
    Ssma_ButtonSts[Ssma_StateMachine]  = Ptr->ButtonEnabled[SSMA_BUTTON_3];


    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_BUTTON_DOWN;
  }
  else
  {
    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_NOT_PRESS;
    Ssma_ButtonSts[Ssma_StateMachine]  = SSMA_NOT_PRESS;
  }

  NETP_SendMsgReq(Ssma_MsmStatus);

  if (SSMA_CfgTable[Ssma_StateMachine].Callback != NULL)
  {
    SSMA_CfgTable[Ssma_StateMachine].Callback();
  }
}

/**
 * @brief Callback routine generated on smart switch button 4 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void SSMA_ComfortButton4Cbk(void)
{
  const SSMA_CfgTable_t *Ptr = &SSMA_CfgTable[Ssma_StateMachine];

  if(DINP_GetState(DINP_SS_4) == S_ON)
  {
    Ssma_ButtonSts[Ssma_StateMachine]  = Ptr->ButtonEnabled[SSMA_BUTTON_4];

    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_BUTTON_BACKW;
  }
  else
  {
    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_NOT_PRESS;
    Ssma_ButtonSts[Ssma_StateMachine]  = SSMA_NOT_PRESS;
  }

  NETP_SendMsgReq(Ssma_MsmStatus);

  if (SSMA_CfgTable[Ssma_StateMachine].Callback != NULL)
  {
    SSMA_CfgTable[Ssma_StateMachine].Callback();
  }
}

/**
 * @brief Callback routine generated on smart switch button 5 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
void SSMA_ComfortButton5Cbk(void)
{
  const SSMA_CfgTable_t *Ptr = &SSMA_CfgTable[Ssma_StateMachine];

  if(DINP_GetState(DINP_SS_5) == S_ON)
  {
    Ssma_ButtonSts[Ssma_StateMachine]  = Ptr->ButtonEnabled[SSMA_BUTTON_5];

    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_BUTTON_CENTRAL;
  }
  else
  {
    MSM_status.bit.MSM_SmartSwitchPressReq = SMS_NOT_PRESS;
    Ssma_ButtonSts[Ssma_StateMachine]  = SSMA_NOT_PRESS;
  }

  NETP_SendMsgReq(Ssma_MsmStatus);

  if (SSMA_CfgTable[Ssma_StateMachine].Callback != NULL)
  {
    SSMA_CfgTable[Ssma_StateMachine].Callback();
  }
}


/**
 * @brief
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
PRES_State_t SSMA_GetLumbarH(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_LUMBAR_H] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }

  return(ret_val);
}

PRES_State_t SSMA_GetLumbarV(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_LUMBAR_V] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }
  return(ret_val);
}

PRES_State_t SSMA_GetHeadrest(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_HEADREST] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }

  return(ret_val);
}

PRES_State_t SSMA_GetCushion(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_CUSHION] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }

  return(ret_val);
}

PRES_State_t SSMA_GetBolsterH(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_BOLSTER_H] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }
  return(ret_val);
}

PRES_State_t SSMA_GetBolsterL(SSMA_SmartSwitchPressReq_t req)
{
  PRES_State_t ret_val;

  if(Ssma_ButtonSts[SSMA_COMFORT_BOLSTER_L] == req)
  {
    ret_val = S_ON;
  }
  else
  {
    ret_val = S_OFF;
  }
  return(ret_val);
}

#endif /* end __SSMA_IS_PRESENT__ */

/*______ E N D _____ (SSMA.c) ________________________________________________*/

