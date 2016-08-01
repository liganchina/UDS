/******************************************************************************/
/** @file       ADCC.h                                                        */
/** @title      Analog Digital Converter Control                              */
/** @brief      Private interface of ADC module for control layer. This file  */
/**             is developed for project MQB starting to QB35. It contain the */
/**             ADC channels management used in this project, its conversion  */
/**             characteristics and its low power behaviour.                  */
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

#ifndef __ADCC_H
#define __ADCC_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "CTRL_if.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/**
 * Define for power management states used in the configuration
 * look-up table ADCC_PwrmOperationMode
 */
#define ADCC_PWRM_PSEUDO_RUN_STATE      (0u)  /**< Pseudo run state position */
#define ADCC_PWRM_RUN_STATE             (1u)  /**< Run state position */
#define ADCC_PWRM_STATE_NBM             (2u)  /**< Low power states number */


/*_____ G L O B A L - T Y P E S ______________________________________________*/

/**
 * Type containing the struct to change the operation mode of ADC conversion
 */
typedef struct ADCC_PwrmOperationMode_s
{
  /**@{*/
  
  ADCD_TriggerMode_t    TriggerMode;
  /**< The trigger mode field, according to operation mode of ADC
   * driver module (ADCD) and according to type ADCD_TriggerMode_t,
   * can assume the following values:
   *
   * @li ADC_SW_TRIG_MODE: sw trigger mode
   * @li ADC_HW_NO_WAIT_TRIG_MODE: hw trigger mode in run mode
   * @li ADC_HW_WAIT_TRIG_MODE: hw trigger mode in snooze mode
   *
   * For now is acceptable only the value ADC_SW_TRIG_MODE
   * For more details see the ADCD interfaces
   */
   
  ADCD_SelectionMode_t  SelectionMode;
  /**< The selection mode field, according to operation mode of ADC
   * driver module (ADCD) and according to type ADCD_SelectionMode_t,
   * can assume the following values:
   *
   * @li ADC_SELECT_MODE: select mode is used to set a single channel
   * @li ADC_SCAN_MODE: scan mode is used to set a group of four channels
   *
   * For more details see the ADCD interfaces
   */
   
  ADCD_ConversionMode_t ConversionMode;  
  /**< The conversion mode field, according to operation mode of ADC
   * driver module (ADCD) and according to type ADCD_ConversionMode_t,
   * can assume the following values:
   *
   * @li ADC_CONTINUOUS_CONV_MODE: continuous conversion
   * @li ADC_ONE_SHOT_CONV_MODE: one shot conversion
   *
   * For more details see the ADCD interfaces
   */
   
   /**@}*/
}ADCC_PwrmOperationMode_t;


typedef uint16_t (*ADCC_GetChnData_t)(uint8_t data);

typedef struct ADCC_ChannelMap_s
{
  uint8_t           ANALOG_IN;
  ADCC_GetChnData_t GET_CHN_DATA;
  uint16_t          OVER_V_THRES_H;
  uint16_t          OVER_V_THRES_L;
  uint16_t          UNDER_V_THRES_H;
  uint16_t          UNDER_V_THRES_L;
}ADCC_ChannelMap_t;



/*_____ G L O B A L - D A T A ________________________________________________*/

/**
 * Interface for const configuration buffer to set the buffer position of 
 * ADCC module according to all possible ADC channels of driver module (ADCD).
 * For configure it go to ADCC_config.c.
 */
extern const ADCC_ChannelMap_t ADCC_ChnMap[ADCC_CHN_NMB];

/**
 * Const configuration look-up table to set the operation mode of the 
 * ADC conversion in the low power states run and pseudo run. 
 * For configure it go to ADCC_config.c.
 */
extern const ADCC_PwrmOperationMode_t ADCC_PwrmOperationMode[ADCC_PWRM_STATE_NBM];


/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief Initialization routine for ADC control module. This routine must be
 *        called only during transition POWER_OFF --> RUN.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_InitCfg(void);

/**
 * @brief Wakeup routine for ADC control module used for transition
 *        LOW_POWER state --> PSEUDO_RUN state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_LpPseudoWakeUpCfg(void);

/**
 * @brief Wakeup routine for ADC control module used for transition
 *        PSEUDO_RUN state --> RUN state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_PrPseudoWakeUpCfg(void);

/**
 * @brief Sleep routine for ADC control module used for transitions: 
 *        - RUN state        --> LOW_POWER state
 *        - PSEUDO_RUN state --> LOW_POWER state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_SleepCfg(void);


#endif  /* end __ADCC_H */

/*_____ E N D _____ (ADCC.h) _________________________________________________*/
