/**
 * @file DIAC_if.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing interface of DIAC Driver.
 *  DIAC: "Digital Input on Analog pin"
 *
 * @see www.Bitron.net
 */

#ifndef DIAC_IF_H_
#define DIAC_IF_H_

/* Dichiarazione dell'interfaccia del Layer */
#ifdef DIAC_IF_OWNER
	#define DIAC_EXTERN
#else
	#define DIAC_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIAC_cfgIf.h"

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
DIAC_EXTERN	void DIAC_Init(void);

/**
 * @brief This function returns the level of requested input.
 * @param [in] chan the requested channel
 * @return electrical level.
 */
DIAC_EXTERN	DRVD_Level_t DIAC_GetLevel(DIAC_Channel_t chan);

/**
 * @brief This function computes the discrete thresholds.
 * @param  none
 * @return non
 */
DIAC_EXTERN void DIAC_Mgm(void);

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
DIAC_EXTERN void DIAC_EnableDisable (DIAC_Channel_t hdl, CTRL_EnSts_t state);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DIAC_IF_H_ */
