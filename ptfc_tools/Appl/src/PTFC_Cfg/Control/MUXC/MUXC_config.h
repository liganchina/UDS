/**
 * @file MUXC_config.h
 * @author mmastrodonato
 * @date 10/set/2014
 * @brief Configuration of Multiplexer management module.
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
 * 10/set/2014    0.1  MM      First revision
 */


#ifndef MUXC_CONFIG_H_
#define MUXC_CONFIG_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/**
 * Define the number of channel of the largest multiplexed used.
 *
 * WARNING:
 *  Allowed values are: MUXC_2MUX, MUXC_4MUX, MUXC_8MUX.
 *
 */
#define MUXC_MAX_MUX_SIZE   MUXC_8MUX

/**
 * It enables/disables the ANALOG Mux acquisition module
 */
#define MUXC_ANALOG_EN      TRUE

/**
 * It enables/disables the DIGITAL Mux acquisition module
 */
#define MUXC_DIGITAL_EN     TRUE

/**
 * Define the DIOD driver channel identifier used by multiplexer selection bus
 * If selection line is not used (IE: in case of MUX with 4 or less channels)
 * set it equal to DIOD_HDL_MAX.
 */
#define MUXC_SEL_1          DIOD_MuxSa
#define MUXC_SEL_2          DIOD_MuxSb
#define MUXC_SEL_3          DIOD_MuxSc


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MUXC_CONFIG_H_ */
