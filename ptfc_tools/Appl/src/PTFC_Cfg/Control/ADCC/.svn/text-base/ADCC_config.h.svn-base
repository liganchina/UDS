/******************************************************************************/
/** @file       ADCC_config.h                                                 */
/** @title      Analog Digital Converter Control                              */
/** @brief      This file contain the private configuration macros and types  */ 
/**             of ADCC module for user settings. This file is developed for  */
/**             project MQB starting to QB35.                                 */
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

#ifndef __ADCC_CFG_H
#define __ADCC_CFG_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ADCC.h"

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/*_____ L O C A L - M A C R O S ______________________________________________*/


#define ADCC_ChannelIsMux(InputChn)\
  (ADCC_ChnMap[(InputChn)].GET_CHN_DATA == (ADCC_GetChnData_t)MUXC_GetChannelData)



/** 
  * Configuration macro to define the routine to use for manage the
  * conversion in pseudo run state. The routines that can be used are:
  *
  * @li ADCD_SwTriggerContinuousManager
  * @li ADCD_SwTriggerOneShotManager
  * @li ADCD_SwTriggerScanContinuousManager
  * @li ADCD_SwTriggerScanOneShotManager
  *
  * WARNING:
  * - the macro interface must be aligned to chosen routine interface
  * - the chosen routine must match to configuration look-up table
  *   ADCC_PwrmOperationMode for pseudo run state present in the file 
  *   ADCC_config.c
  *
  */
#define ADCC_StartStopConversionPseudoRun(StartStop, SingleChn)\
  (CTRL_ResSts_t)ADCD_SwTriggerContinuousManager((bool_t)(StartStop),\
                                                 (SingleChn))

/** 
  * Configuration macro to define the routine to use for manage the
  * conversion in run state. The routines that can be used are:
  *
  * @li ADCD_SwTriggerContinuousManager
  * @li ADCD_SwTriggerOneShotManager
  * @li ADCD_SwTriggerScanContinuousManager
  * @li ADCD_SwTriggerScanOneShotManager
  *
  * WARNING:
  * - the macro interface must be aligned to chosen routine interface
  * - the chosen routine must match to configuration look-up table
  *   ADCC_PwrmOperationMode for run state present in the file ADCC_config.c
  *
  */
#define ADCC_StartConversionRun(SingleChn)\
  (CTRL_ResSts_t)ADCD_SwTriggerOneShotManager(SingleChn)
  

/**
  * Configuration macro to define the syncronization between ADCC and MUXC
  * buffering. Indicates which MUX selection trigger the ADCC sampling of
  * all MUXC channels.
  *
  * Example:
  *
  * if ADCC_MUX_CHAN_SAMPLE_START is equal to 5 the ADCC will scan all
  * channels bufferized by MUXC when the MUXC selects the channel 5. So the
  * last sample acquired by phisical ADC will be the MUX channel 4
  * (ADCC_MUX_CHAN_SAMPLE_START - 1)
  *
  * This feature is useful when a fresh sample of a specific multiplexed
  * channel is required.
  *
  * Allowed values: 0 to ADCC_MUX_SIZE
  */
#define ADCC_MUX_CHAN_SAMPLE_START   3U


/**
  * Configuration macro to define the callback called when all multiplexed
  * channels have been updated.
  */
#define ADCC_MuxChanSampledCbk()\
{\
  /* Insert below the callback */\
}

/** Configuration macro to define the size of analog multiplexer in use.
 *  The 0 (zero) value disables the multiplexer management.
 */
#define ADCC_MUX_SIZE                8U

#endif /* end __ADCC_CFG_H */

/*______ E N D _____ (ADCC_config.h) _________________________________________*/
