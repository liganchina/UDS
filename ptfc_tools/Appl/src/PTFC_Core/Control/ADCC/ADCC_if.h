/******************************************************************************/
/** @file       ADCC_if.h                                                     */
/** @title      Analog Digital Converter Control                              */
/** @brief      Public interface of ADC module for control layer. This file   */
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

#ifndef __ADCC_IF_H
#define __ADCC_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ADCC_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifdef ADCC_IF_OWNER
	#define ADCC_EXTERN
#else
	#define ADCC_EXTERN		extern
#endif

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/**
 * Type containing the struct for ADC datas buffer
 */
typedef struct ADCC_ChnBuffer_s
{
  /**@{*/
  uint8_t  Index;   /**< select in the SampleBuffer buffer last data stored */
  uint16_t SampleBuffer[ADCC_BUFFER_SAMPLE_NMB];
  /**< sample datas buffer. The buffer size ADCC_BUFFER_SAMPLE_NMB
    * can be configured
    */
  /**@}*/
}ADCC_ChnBuffer_t;


/*_____ G L O B A L - D A T A ________________________________________________*/

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
ADCC_EXTERN void ADCC_Init(void);


/**
 * @brief This routine, only for run state of low power management module,
 *        manages the conversion of all ADC channels present on board except
 *        the PIEZO channel. The main activities are: starts che conversion
 *        configured in the ADCC_StartConversionRun, stores and manipulates
 *        the ADC datas by Adcc_PrepareDataBuffer routine and scans the ADC
 *        channels to their conversion.
 *        WARNING: must be called by task only during the run state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
ADCC_EXTERN void ADCC_RunManager(void);

/**
 * @brief Return the buffer data values for a specific channel.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels
 * @param [out] None
 *
 * @return ADCC_ChnBuffer_t
 * @retval uint16_t Average: in this field there is the average value of all 
 *         sample datas stored in the SampleBuffer field
 * @retval uint8_t Index: index to select in the SampleBuffer buffer last 
 *         data stored
 * @retval uint16_t SampleBuffer[ADCC_BUFFER_SAMPLE_NMB]: sample datas buffer.
 *         The buffer size is ADCC_BUFFER_SAMPLE_NMB and it can be configured
 */
ADCC_EXTERN ADCC_ChnBuffer_t ADCC_GetChnData(ADCC_InputChn_t InputChn);


/**
 * @brief Return the buffer data values for a specific channel.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [out] None
 *
 * @return ADCC_ChnBuffer_t
 * @retval uint16_t Average: in this field there is the average value of all 
 *         sample datas stored in the SampleBuffer field.
 * @retval uint8_t Index: index to select in the SampleBuffer buffer last 
 *         data stored.
 * @retval uint16_t SampleBuffer[ADCC_BUFFER_SAMPLE_NMB]: sample datas buffer.
 *         The buffer size is ADCC_BUFFER_SAMPLE_NMB and it can be configured.
 */
ADCC_EXTERN uint16_t ADCC_GetLastChnData(ADCC_InputChn_t InputChn);


ADCC_EXTERN uint16_t ADCC_GetChnAvrgData(ADCC_InputChn_t InputChn);

/**
 * @brief Returns the diagnosis status of a specific ADC channel (InputChn).
 *        The diagnosis is performed on the average value of the input.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [out] None
 *
 * @return CTRL_Fault_t
 * @retval CTRL_OVER_VOLTAGE The ADC value is over the maximum acceptable value.
 * @retval CTRL_UNDER_VOLTAGE The ADC is under the minimum acceptable value.
 */
ADCC_EXTERN CTRL_Fault_t ADCC_GetDiag(ADCC_InputChn_t InputChn);


#endif /* end __ADCC_IF_H */

/*_____ E N D _____ (ADCC_if.h) ______________________________________________*/
