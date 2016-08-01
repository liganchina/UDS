/**
 * @file SSMA_config.c
 * @author Gianpiero Lenta
 * @date 17 nov 2014
 * @brief File containing the user configuration of SSMA Application.
 *
 * @see www.Bitron.net
 */



/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "SSMA.h"
#include "SSMA_config.h"

#ifdef __SSMA_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/


const SSMA_CfgTable_t SSMA_CfgTable[SSMA_COMFORT_MAX_STS] = {
/*                                 button1           button2             button3             button4            button5           Callback */
/*SSMA_COMFORT_IDLE           */ { SSMA_NOT_PRESS,   SSMA_NOT_PRESS,     SSMA_NOT_PRESS,     SSMA_NOT_PRESS,    SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_MENU_SELECTION */ { SSMA_NOT_PRESS,   SSMA_NOT_PRESS,     SSMA_NOT_PRESS,     SSMA_NOT_PRESS,    SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_BOLSTER_H      */ { SSMA_BUTTON_UP,   SSMA_NOT_PRESS,     SSMA_BUTTON_DOWN,   SSMA_NOT_PRESS,    SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_BOLSTER_L      */ { SSMA_NOT_PRESS,   SSMA_BUTTON_FWD,    SSMA_NOT_PRESS,     SSMA_BUTTON_BWD,   SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_LUMBAR_H       */ { SSMA_NOT_PRESS,   SSMA_BUTTON_FWD,    SSMA_NOT_PRESS,     SSMA_BUTTON_BWD,   SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_LUMBAR_V       */ { SSMA_BUTTON_UP,   SSMA_NOT_PRESS ,    SSMA_BUTTON_DOWN,   SSMA_NOT_PRESS,    SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_HEADREST       */ { SSMA_BUTTON_UP,   SSMA_NOT_PRESS,     SSMA_BUTTON_DOWN,   SSMA_NOT_PRESS,    SSMA_NOT_PRESS,  NULL                    },
/*SSMA_COMFORT_CUSHION        */ { SSMA_NOT_PRESS,   SSMA_BUTTON_FWD,    SSMA_NOT_PRESS,     SSMA_BUTTON_BWD,   SSMA_NOT_PRESS,  NULL                    },
};


/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

#endif /* __SSMA_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

