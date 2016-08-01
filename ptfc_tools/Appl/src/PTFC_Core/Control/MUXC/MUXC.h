/**
 * @file  MUXC.h
 * @author mmastrodonato
 * @date 10/set/2014
 * @brief Multiplexer management module header.
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


#ifndef MUXC_H_
#define MUXC_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __MUXC_IS_PRESENT__

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Allowed values for macro MUXC_MAX_MUX_SIZE (MUXC_config.h) */
/* Size is indicated using log2(REAL SIZE)                    */
#define MUXC_2MUX   1U
#define MUXC_4MUX   2U
#define MUXC_8MUX   3U

/*______ G L O B A L - D A T A _______________________________________________*/

/* Configuration table structure for Analog Virtual Channels */
typedef struct MUXC_AnCfgTable_s
{
  MUXC_AnMux_t   MUX_HDL;
  u08            MUX_CHANNEL;
} MUXC_AnCfgTable_t;

/* Configuration table structure for Digital Virtual Channels */
typedef struct MUXC_DgtCfgTable_s
{
  MUXC_DgtMux_t  MUX_HDL;
  u08            MUX_CHANNEL;
} MUXC_DgtCfgTable_t;


/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* __MUXC_IS_PRESENT__ */

#endif /* MUXC_H_ */
