/**
 * @file NETP_config.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:30:7
 * @brief File containing the user configuration of NETP module.
 * 
 * @see www.Bitron.net
 */
#ifndef __NETP_CONFIG_H
#define __NETP_CONFIG_H
#include "NWMA_cbk.h"
#include "KEYA_cbk.h"
#include "EXMMA_cbk.h"
#include "DISPA_cbk.h"
#include "VF607_cbk.h"
#include "VF608_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define NETP_TIMEOUT_SERVICE

#define NETP_NODE_MUTE_DIAG

/**
* @brief MTBE (Minimum Time Beetwen Events) strategy is applied only for
* PE type message.
* This strategy manage two actions:
* @li The event message sending is done with a time minimum interval Mtbe.
* If occur onother event in this time it's ignored.
* @li If occur a sending event around the message periodic time, if the request
* is near with a time below Mtbe, It will be ignored.
* \n
* \n
* \n    x                  *                               x
* \n    |                  |                               |
* \n    |      o           |                        o      |      o
* \n    |      |           |                        |      |      |
* \n    |      |           |                        |      |      |
* \n ___|______|___________|________________________|______|______|_____
* \n    P     Thl          E                       Thh     P     Thl
* \n
* \n           |                                    |
* \n           |                                    |
* \n           +------------------------------------+
* \n                Event Tx allowed band
* \n
* \n
* \n  P = periodical Can message transmission
* \n  E = Event Can message transmission
* \n
* \n  Thl = low threshold of the band where event transmission allowed = Tmbe
* \n  Thh = high threshold of the band where event transmission allowed = P - Tmbe
* \n
 *-\n
*/

/*_____ UNCOMMENT TO ENABLE the MTBE strategy ____*/
//#define NETP_MTBE_STRATEGY


/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

#define NETP_TICK_MS(ms)            CVT_MS_2_TICK10(ms)

#define NETP_GetKeyStatus()         KEYA_GetKeyStatus()

#define NETP_SET_COMM_TYPE()\
{\
  NETP_SetCommCtrlTypeRx(NETP_CCT_NWM_MSG);\
  NETP_SetCommCtrlTypeTx(NETP_CCT_NWM_MSG);\
}
 
/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* TODO COBRA: aggiungere le recovery dei vari messaggi */
#define NETP_BUS_OFF_RECOVERY()\
{\
  NETP_InitTimeout(NETP_CCT_ALL_MSG);\
}

/* TODO COBRA: aggiungere le recovery dei vari messaggi */
#define NETP_MUTE_RECOVERY()\
{\
  NETP_InitTimeout(NETP_CCT_ALL_MSG);\
}


#endif /* __NETP_CONFIG_H */

/*______ E N D _____ (NETP_config.h) _________________________________________*/
