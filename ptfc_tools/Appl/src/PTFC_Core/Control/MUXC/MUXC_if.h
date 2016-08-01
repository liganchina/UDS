/**
 * @file MUXC_if.h
 * @author mmastrodonato
 * @date 11/set/2014
 * @brief Public interface of Multiplexer management module.
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 * MM             mmastrodonato             Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 11/set/2014    0.1  MM      First revision
 */


#ifndef MUXC_IF_H_
#define MUXC_IF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef MUXC_IF_OWNER
  #define MUXC_EXTERN
#else
  #define MUXC_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MUXC_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Initialization routine for MUXC module
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
MUXC_EXTERN void MUXC_Init(void);


/**
 * @brief Event call to acquire analog sample at ADC end of conversion.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
MUXC_EXTERN uint16_t MUXC_AdcEndOfConv(void);

/**
 * @brief Periodic call to manage the channel selection and digital acquisition.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
MUXC_EXTERN void MUXC_Mgm(void);


/**
 * @brief This routine returns the last ADC value read for a channel.
 *
 * @param [in] channel  Virtual channel handle.
 * @param [out] None
 *
 * @return u16 The conversion result of virtual requested channel.
 */
  MUXC_EXTERN u16 MUXC_GetChannelData(MUXC_AnChannel_t channel);

/**
 * @brief This routine returns the last read physical value for a channel.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return DRVD_Level_t the physical value of requested channel.
 * @retval L_LOW
 * @retval L_HIGH
 */
  MUXC_EXTERN DRVD_Level_t MUXC_GetLevel(MUXC_DgtChannel_t channel);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MUXC_IF_H_ */
