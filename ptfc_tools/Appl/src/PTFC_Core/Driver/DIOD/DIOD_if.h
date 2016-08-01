/**
 * @file DIOD_if.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing interface of DIOD Driver.
 *  DIOD: "Digital Input / Output"
 *
 * @see www.Bitron.net
 */

#ifndef DIOD_IF_H_
#define DIOD_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef DIOD_IF_OWNER
 #define DIOD_EXTERN
#else
 #define DIOD_EXTERN  extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIOD_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the DIOD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
DIOD_EXTERN void            DIOD_Init(void);

/**
 * @brief This function set the electrical level of requested channel.
 * @param chan the requested channel
 * @param level the requested electrical level
 * @return the result of the operation.
 */
DIOD_EXTERN DRVD_RStatus_t DIOD_SetLevel(DIOD_Channel_t chan, DRVD_Level_t level);

/**
 * @brief This function returns the level of requested input.
 * @param chan the requested channel
 * @return the level of input pin.
 */
DIOD_EXTERN DRVD_Level_t   	DIOD_GetLevel(DIOD_Channel_t chan);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DIOD_IF_H_ */
