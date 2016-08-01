/**
 * @file DIAC.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the header and include chain of DIAC Driver.
 *
 * @see www.Bitron.net
 */

#ifndef DIAC_H_
#define DIAC_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "global.h"
#include "CTRL_if.h"

/* Module inhibition filter */
#ifdef __DIAC_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define DIAC_NO_GAIN   1024U

/*______ G L O B A L - T Y P E S _____________________________________________*/


  /* Typedef struttura da allocare in flash contenente i dati di configurazione statica */

typedef struct
{
  ADCC_InputChn_t   ADCC_CHAN;         /* ADCC channel identifier                      */
  DIAC_Thresholds_t THRES_HIGH_HDL;    /* Discrete threshold high identifier           */
  DIAC_Thresholds_t THRES_LOW_HDL;     /* Discrete threshold low identifier            */
  DRVD_Level_t      INIT_VALUE;        /* Initialization value (pwr on)                */
  bool_t            MULTI_LEVEL_MODE;  /* GetValue returns high only if the analog
                                          value is between the two thresholds          */
} DIAC_CfgTable_t;


typedef struct
{
  uint16_t        RATIO;               /* Tens battery low level ratio (in case of ratiometric input)   [1/1024 lsb] */
  uint16_t        THRES;               /* Tens battery low level threshold (offset)  [4,883mv/lsb]                   */
  DIAC_Vref_t     DIAC_VREF_HDL;       /* Voltage reference, (DIAC_VREF_MAX if not used)                             */
  uint16_t        INIT_VALUE;          /* Initialization value (pwr on)                                              */
} DIAC_ThresTable_t;


typedef struct
{
  ADCC_InputChn_t ADCC_VREF_CHAN;      /* Reference voltage ADCD object (in case of ratiometric input)               */
  uint16_t        VREF_HW_GAIN;        /* Reference voltage partition gain [1/1024 lsb]                              */
  int16_t         VREF_HW_OFFSET;      /* Reference voltage offset [4,883mv/lsb]                                     */
}DIAC_VrefTable_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const DIAC_CfgTable_t   DIAC_CfgTable  [DIAC_HDL_MAX];
extern const DIAC_ThresTable_t DIAC_ThresTable[DIAC_THRES_MAX];
extern const DIAC_VrefTable_t  DIAC_VrefTable [DIAC_VREF_MAX];

#endif /* __DIAC_IS_PRESENT__ */

#endif /* DIAC_H_ */
