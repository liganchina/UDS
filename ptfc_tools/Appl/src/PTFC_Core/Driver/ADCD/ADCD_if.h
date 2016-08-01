/******************************************************************************/
/** @file       ADCD_if.h                                                     */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Public interface of ADC module for driver layer. This file    */
/**             is developed for Renesas RL78 family - micro R5F10AGFLFB/F13. */
/**             The requirement used for this driver is the chapter 12 of the */
/**             relative hw datasheet version 2.0.                            */
/** @date       21/07/2014                                                    */
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
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 21/07/2014 0.1  CC      First draft. For this first release will
|                         be not implmented:
|                         - the SNOOZE mode function management (TODO SGR)
|                         - the TEST mode (TODO SGR)
|                         - the HW trigger mode is partially implemented then
|                           for now isn't usable (TODO SGR)
|-----------------------------------------------------------------------------
| 28/07/2014 1.0  CC      First official release (without functionlity 
|                         described in the description release v0.1)
|-----------------------------------------------------------------------------
| 26/08/2014 1.1  CC      Module documentation terminated
|-----------------------------------------------------------------------------
*/

#ifndef __ADCD_IF_H
#define __ADCD_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ADCD_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifdef ADCD_IF_OWNER
	#define ADCD_EXTERN
#else
	#define ADCD_EXTERN		extern
#endif


/*_____ G L O B A L - T Y P E S ______________________________________________*/

/* TODO SGR_OK */
/**
 * ADC controller input channels. Each channel used has a different
 * behaviour according to selection mode:
 * @li In select mode is used to select the channel specified
 * @li In scan mode is used to select the end of channels group to scan.
 */
typedef enum ADCD_InputChn_e
{
#if ( (DRVD_UC_PACKAGE == DRVD_64_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_100_PIN) )
  /**@{*/
  ADCD_IN_CHN_0 = 0u,   /**< ANI00 channel - P80 pin  */
  ADCD_IN_CHN_1,        /**< ANI01 channel - P81 pin  */
  ADCD_IN_CHN_2,        /**< ANI02 channel - P82 pin  */
  ADCD_IN_CHN_3,        /**< ANI03 channel - P83 pin  */
  ADCD_IN_CHN_4,        /**< ANI04 channel - P84 pin  */
  ADCD_IN_CHN_5,        /**< ANI05 channel - P85 pin  */
  ADCD_IN_CHN_6,        /**< ANI06 channel - P86 pin  */
  ADCD_IN_CHN_7,        /**< ANI07 channel - P87 pin  */
  ADCD_IN_CHN_8,        /**< ANI08 channel - P90 pin  */
  ADCD_IN_CHN_9,        /**< ANI09 channel - P91 pin  */
  ADCD_IN_CHN_10,       /**< ANI10 channel - P92 pin  */
  ADCD_IN_CHN_11,       /**< ANI11 channel - P93 pin  */
  ADCD_IN_CHN_12,       /**< ANI12 channel - P94 pin  */
  ADCD_IN_CHN_13,       /**< ANI13 channel - P95 pin  */
  ADCD_IN_CHN_14,       /**< ANI14 channel - P96 pin  */
#endif /* end ADC channels for 64 pins */
#if ((DRVD_UC_PACKAGE == DRVD_80_PIN) || \
     (DRVD_UC_PACKAGE == DRVD_100_PIN))
  ADCD_IN_CHN_15,       /**< ANI15 channel - P97 pin  */
#endif /* end ADC channels for 80 pins */
#if (DRVD_UC_PACKAGE == DRVD_100_PIN)
  ADCD_IN_CHN_16,       /**< ANI16 channel - P100 pin */
  ADCD_IN_CHN_17,       /**< ANI17 channel - P101 pin */
  ADCD_IN_CHN_18,       /**< ANI18 channel - P102 pin */
  ADCD_IN_CHN_19,       /**< ANI19 channel - P103 pin */
  ADCD_IN_CHN_20,       /**< ANI20 channel - P104 pin */
  ADCD_IN_CHN_21,       /**< ANI21 channel - P105 pin */
  ADCD_IN_CHN_22,       /**< ANI22 channel - P106 pin */
  ADCD_IN_CHN_23,       /**< ANI23 channel - P107 pin */
#endif /* end ADC channels for 100 pins */
  ADCD_IN_CHN_TOT       /**< Channels total number    */
  /**@}*/
}ADCD_InputChn_t;

/* TODO SGR_OK */
/**
 * Values for the trigger mode setting
 */
typedef enum ADCD_TriggerMode_e
{
  ADC_SW_TRIG_MODE  = 0x00u,
  ADC_HW_TRIG_MODE  = 0x01u
}ADCD_TriggerMode_t;

/* TODO SGR_OK */
/**
 * Values for the selection mode setting
 */
typedef enum ADCD_SelectionMode_e
{
  ADC_SELECT_MODE          = 0x00u,
  ADC_SCAN_MODE_MULTI_INT  = 0x02u,
  ADC_SCAN_MODE_SINGLE_INT = 0x03u
}ADCD_SelectionMode_t;

/* TODO SGR_OK */
/**
 * Values for the conversion mode setting
 */
typedef enum ADCD_ConversionMode_e
{
  ADC_CONTINUOUS_CONV_MODE = 0x00u,
  ADC_ONE_SHOT_CONV_MODE   = 0x01u
}ADCD_ConversionMode_t;


/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/* TODO SGR_OK */
/**
 * @brief Initialization routine for ADC driver module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
ADCD_EXTERN void ADCD_Init(void);

/* TODO SGR_OK */
/**
 * @brief Power-off routine for ADC driver module used for transition
 *        RUN state --> POWER_OFF state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
ADCD_EXTERN void ADCD_PowerOff(void);

/* TODO SGR_OK */
/**
 * @brief This routine return the last ADC value read for a specific channel
 *
 * @param [in] Chn: ADC channel you want read its value. The possible
 * values are given by the type ADCD_InputChn_t
 * @param [out] None
 *
 * @return uint16_t
 * @retval The selected ADC channel data is in the range [0-1023] if the 
 * ADCD_CONV_RESOLUTION setting is to 10 bit else the range is [0-127]
 */
ADCD_EXTERN uint16_t ADCD_GetChannelData(ADCD_InputChn_t Chn);



/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.2 of the relative hw datasheet version 2.0. The sw trigger is given
 * every time that the routine is called and the ADC conversion start. The end 
 * conversion is automatically done by ADC controller (one-shot behaviour).
 * If the parameter ADCD_SELECT_ONESHOT_BLOCK is configured to ADCD_ENABLE, 
 * at the end of the routine execution the new data is ready to be read.
 * For internal channel of temperature sensor (ADCD_IN_CHN_TEMP_SENS) the manage
 * is always blocker a cause of a S/H limit.
 * The conversion is done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_ONE_SHOT_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return DRVD_ResSts_t
 * @retval DRVD_OK The ADC channel selected is correct
 * @retval DRVD_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval DRVD_NOT_OK The ADC channel selected cannot used with current configuration
 */
ADCD_EXTERN DRVD_ResSts_t ADCD_SwTriggerOneShotManager(ADCD_InputChn_t AdcChn);



/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.1 of the relative hw datasheet version 2.0. The sw trigger is given
 * when the routine is called with the parameter Enable to TRUE and the ADC
 * conversion start. It is stopped only when the routine is called with the
 * parameter Enable to FALSE (sequenzial mode behaviour). The conversion is
 * done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_SEQUENTIAL_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] Enable: flag for start/stop conversion. With TRUE start the
 * sequenzial conversion and with FALSE the conversion is stopped
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return DRVD_ResSts_t
 * @retval DRVD_OK The ADC channel selected is correct
 * @retval DRVD_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval DRVD_NOT_OK The ADC channel selected cannot used with current configuration
 */
ADCD_EXTERN DRVD_ResSts_t ADCD_SwTriggerContinuousManager(bool_t Enable, 
                                                          ADCD_InputChn_t AdcChn);
                                                          
                                                          

/* TODO SGR_OK */
/**
 * @brief This routine set the main submodes for the operation mode. The possible
 * settings are: the trigger mode (for now is available only the sw trigger), the
 * selection mode and conversion mode. Before of this setting mustn't block the
 * conversion because this operation is done yet by routine.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] TriggerMode: parameter to set the trigger mode. For now is 
 * possible use only the value ADC_SW_TRIG_MODE
 * @param [in] SelectionMode: parameter to set the selection mode. The possible 
 * values are given by the type ADCD_SelectionMode_t
 * @param [in] ConversionMode: parameter to set the conversion mode. The possible
 * values are given by the type ADCD_ConversionMode_t
 * @param [out] None
 *
 * @return None
 */
ADCD_EXTERN void ADCD_SetTriggerOperationConversionMode(ADCD_TriggerMode_t    TriggerMode,
                                                        ADCD_SelectionMode_t  SelectionMode,
                                                        ADCD_ConversionMode_t ConversionMode);

/**
 * @brief This routine return the current value of the trigger mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_TriggerMode_t
 * @retval ADC_SW_TRIG_MODE Value for sw trigger mode setting
 * @retval ADC_HW_NO_WAIT_TRIG_MODE Value for hw trigger no-wait mode 
 * setting (for now it isn't available)
 * @retval ADC_HW_WAIT_TRIG_MODE Value for hw trigger wait mode 
 * setting (for now it isn't available)
 */
ADCD_EXTERN ADCD_TriggerMode_t ADCD_GetTriggerMode(void);

/**
 * @brief This routine return the current value of the selection mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_SelectionMode_t
 * @retval ADC_SELECT_MODE Value for select mode setting (single channel mode)
 * @retval ADC_SCAN_MODE Value for scan mode setting (channels group mode)
 */
ADCD_EXTERN ADCD_SelectionMode_t ADCD_GetSelectionMode(void);

/**
 * @brief This routine return the current value of the conversion mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_ConversionMode_t
 * @retval ADC_CONTINUOUS_CONV_MODE Value for continuous conversion mode setting
 * @retval ADC_ONE_SHOT_CONV_MODE Value for one-shot conversion mode setting
 */
ADCD_EXTERN ADCD_ConversionMode_t ADCD_GetConversionMode(void);


#endif /* __ADCD_IF_H */

/*_____ E N D _____ (ADCD_if.h) ______________________________________________*/
