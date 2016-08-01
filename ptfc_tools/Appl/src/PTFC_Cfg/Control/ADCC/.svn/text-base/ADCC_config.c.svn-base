/******************************************************************************/
/** @file       ADCC_config.c                                                 */
/** @title      Analog Digital Converter Control                              */
/** @brief      This file contain all configuration routines of ADCC module   */
/**             for user settings. This file is developed for project MQB     */
/**             starting to QB35.                                             */
/** @date       27/08/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 27/08/2014 0.1  CC      First draft
|-----------------------------------------------------------------------------
| 05/09/2014 1.0  CC      First release
|-----------------------------------------------------------------------------
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "ADCC.h"
#include "ADCC_config.h"

/* Module inhibition filter */
#ifdef __ADCC_IS_PRESENT__

/*______ L O C A L - D E F I N E _____________________________________________*/

#define ADCC_RELPROT_OUT_RANGE 102U  /* 2.0 V  */

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/**
 * Const configuration look-up table to set the operation mode of the 
 * ADC conversion in the low power states run and pseudo run. In particular
 * can be configured the parameter "trigger mode", "selection mode" and
 * "conversion mode" (see type ADCC_PwrmOperationMode_t). These configurations 
 * are setted during the transitions that go to the states configured.
 *
 * WARNING: the settings for pseudo run state and for run state must match 
 * to relative routines configured in ADCC_config.h used to manage the
 * conversion: ADCC_StartStopConversionPseudoRun and ADCC_StartConversionRun
 *
 */
const ADCC_PwrmOperationMode_t ADCC_PwrmOperationMode[ADCC_PWRM_STATE_NBM] = 
{
  /**@{*/
  {ADC_SW_TRIG_MODE, 
   ADC_SELECT_MODE, 
   ADC_CONTINUOUS_CONV_MODE}, /**< Operation mode setting for pseudo run state */
  
  {ADC_SW_TRIG_MODE, 
   ADC_SCAN_MODE_SINGLE_INT, 
   ADC_ONE_SHOT_CONV_MODE} /**< Operation mode setting for run state */
   /**@}*/
};


/**
 * Type to configure the ADC channels to use on the board.
 * At left must write the coding name to use in all project and
 * at right must insert the ADC physical channel.
 * The reference documentation to logical channels could be the 
 * project schematic or hw/sw interface requirement.
 */

/* TODO COBRA: configurare le soglie di diagnosi */

const ADCC_ChannelMap_t ADCC_ChnMap[ADCC_CHN_NMB] = 
{
 /**@{*/
 /*    ADCC HANDLE              ANALOG_IN                            GET_CHN_DATA               OVER_V_THRES_H     OVER_V_THRES_L   UNDER_V_THRES_H  UNDER_V_THRES_L */
 /*                          [ADCD  channel]                 [Pointer to get operation]         [4883uV/bit]       [4883uV/bit]      [4883uV/bit]     [4883uV/bit]  <- voltage at uC pin */
 /* ADCC_MotorsSens      */ { ADCD_IN_CHN_0         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,  1024U,             1024U,               15U, /*400 mA*/  10U /*300 mA*/ }, /**< ANI0   */
 /* ADCC_HallLift        */ { ADCD_IN_CHN_1         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI1   */
 /* ADCC_HallSlide       */ { ADCD_IN_CHN_2         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI2   */
 /* ADCC_HallBackr       */ { ADCD_IN_CHN_3         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI3   */
 /* ADCC_HallTilt        */ { ADCD_IN_CHN_4         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI4   */
 /* ADCC_HallSpareMot    */ { ADCD_IN_CHN_5         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI5   */
 /* ADCC_Spare           */ { ADCD_IN_CHN_6         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI6   */
 /* ADCC_HeatPassFbk     */ { ADCD_IN_CHN_7         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI7   */
 /* ADCC_Ele_Fbk         */ { ADCD_IN_CHN_8         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,    813U, /*16.9*/     790U, /*16.4*/    452U, /*9.7*/    417U /*9.0*/    }, /**< ANI8   */
 /* ADCC_RelProtFbk      */ { ADCD_IN_CHN_9         ,  (ADCC_GetChnData_t)ADCD_GetChannelData,   1024U,             1024U,              66U, /*1.3*/     50U /*1.0*/    }, /**< ANI9   */
 /* ADCC_FanDrvFbk       */ { ADCD_IN_CHN_12        ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI12  */
 /* ADCC_FanPassFbk      */ { ADCD_IN_CHN_13        ,  (ADCC_GetChnData_t)ADCD_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI13  */
 /* ADCC_KeyDiag         */ { MUXC_KeyDiag          ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 0  */
 /* ADCC_SlideTiltKey    */ { MUXC_SlideTiltKey     ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 1  */
 /* ADCC_BackrLiftKey    */ { MUXC_BackrLiftKey     ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 2  */
 /* ADCC_MemKey          */ { MUXC_MemKey           ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 3  */
 /* ADCC_7V5_Fbk         */ { MUXC_7V5_Fbk          ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 5  */
 /* ADCC_MOT_Fbk         */ { MUXC_MOT_Fbk          ,  (ADCC_GetChnData_t)MUXC_GetChannelData,    813U,/*16.9*/      790U,/*16.4*/     452U,/*9.7*/     417U/*9.0*/     }, /**< ANI11 - MUX ch. 6  */
 /* ADCC_HeatSteerFbk    */ { MUXC_HeatSteerFbk     ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI11 - MUX ch. 7  */
 /* ADCC_HeatSteerOutFbk */ { MUXC_HeatSteerOutFbk  ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 0  */
 /* ADCC_HeatDrvOutFbk   */ { MUXC_HeatDrvOutFbk    ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 1  */
 /* ADCC_HeatPassOutFbk  */ { MUXC_HeatPassOutFbk   ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 2  */
 /* ADCC_NtcDrv          */ { MUXC_NtcDrv           ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 3  */
 /* ADCC_NtcSteer        */ { MUXC_NtcSteer         ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 4  */
 /* ADCC_NtcPass         */ { MUXC_NtcPass          ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 5  */
 /* ADCC_NtcVFbk         */ { MUXC_NtcVFbk          ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 6  */
 /* ADCC_HeatDrvFbk      */ { MUXC_HeatDrvFbk       ,  (ADCC_GetChnData_t)MUXC_GetChannelData,      0U,                0U,               0U,              0U            }, /**< ANI10 - MUX ch. 7  */

 /**@}*/
};


/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

void ADCC_InitCfg(void)
{
}


CTRL_Fault_t ADCC_GetRelProtDiag(u08 hdl)
{
  CTRL_Fault_t ret_val;

  if (DOVFC_GetState((DOVFC_Handle_t)hdl) == S_ON)
  {
    ret_val = DOVFC_GetDiag((DOVFC_Handle_t)hdl);
  }
  else
  {
    if (ADCC_GetDiag(ADCC_RelProtFbk) == CTRL_UNDER_VOLTAGE)
    {
      ret_val = CTRL_SHORT_TO_GND;
    }
    else if (ADCC_GetChnAvrgData(ADCC_RelProtFbk) >
            (ADCC_GetChnAvrgData(ADCC_MOT_Fbk) - ADCC_RELPROT_OUT_RANGE))
    {
      ret_val = CTRL_OC_OR_STB;
    }
    else
    {
      ret_val = CTRL_NO_FAULT;
    }
  }

  return ret_val;
}

CTRL_Fault_t ADCC_GetSlideCurrentDiag(u08 hdl)
{
  CTRL_Fault_t ret_val;

  if (IPOC_GetDirection(IPOC_Slide) != IPOC_CMD_IDLE)
  {
    /* only under voltage is diagnosed */
    ret_val = ADCC_GetDiag(ADCC_MotorsSens);
  }
  else
  {
    ret_val = CTRL_NOT_TESTED;
  }

  return ret_val;
}
/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __ADCC_IS_PRESENT__ */

/*______ E N D _____ (ADCC_config.c) _________________________________________*/
