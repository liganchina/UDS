/**
 * @file IPOC.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the header and include chain of IPOC Driver.
 *
 * @see www.Bitron.net
 */

#ifndef IPOC_H_
#define IPOC_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __IPOC_IS_PRESENT__

/*______ G L O B A L - T Y P E S _____________________________________________*/


  /* Typedef struttura da allocare in flash contenente i dati di configurazione statica */

typedef struct
{
  ADCC_InputChn_t  AD_SENS_CHAN;       /* Sensor ADCD channel identifier                                         */
//  uint16_t         DECELERATION_TIME;  /* Deceleration tick [tick]                                               */
//  int16_t          MAX_PULSE_CNT;      /* Maximum position [pulses]                                              */
//  int16_t          MIN_PULSE_CNT;      /* Minimum position [pulses]                                              */
//  uint8_t          MAX_DIFF_PULSE;     /* Maximum HALL difference between two consecutive
//                                          samples, to recognize a DC change [4,883mV/bit]                        */
//  uint8_t          MIN_APPLITUDE;      /* Minimum HALL ac signal amplitude [4,883mV/bit]                         */
//  uint16_t         DIAG_THRES_UP;      /* Minimum acceptable input sensor value (ADC pin voltage) [4,883mV/bit]  */
//  uint16_t         DIAG_THRES_DOWN;    /* Maximum acceptable input sensor value (ADC pin voltage) [4,883mV/bit]  */
} IPOC_CfgTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const IPOC_CfgTable_t IPOC_CfgTable[IPOC_HDL_MAX];

#endif /* __IPOC_IS_PRESENT__ */

#endif /* IPOC_H_ */
