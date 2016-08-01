/**
 * @file DIAC_config.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of DIAC Driver.
 *
 * @see www.Bitron.net
 */

#ifndef DIAC_CONFIG_H_
#define DIAC_CONFIG_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/**
 * Tick time to use for compute the maximum ticks number. This time must be used
 * as reference for call the module management routine with the correct task time.
 */
#define DIAC_TICK_TIME              ((uint16_t)5000u)

/**
 * Time to scan all channel configured. This time must be setted in microseconds.
 */
#define DIAC_CHN_SCAN_TIME_US       ((uint16_t)20000u)


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DIAC_CONFIG_H_ */
