/**
 * @file PWMC_config.c
 * @author Mastrodonato Matteo
 * @date 11 dec 2014
 * @brief File containing the user configuration of PWMC Driver.
 *
 * @see www.Bitron.net
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "PWMC.h"
#include "PWMC_config.h"

#include "FE78K0R_CG_timer_user.h"
#include "FE78K0R_CG_int_user.h"

#ifdef __PWMC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/ 


/*______ G L O B A L - D A T A _______________________________________________*/
typedef enum PWMC_SwHandleType_e
{
  PWMC_VIA_DOIFC,
  PWMC_VIA_DOVFC,
  PWMC_HANDLE_TYPE_NMB
}PWMC_SwHandleType_t;


/* WARNING: For PWM SW configuration, the period must be multiple of MIN_CMD */

const PWMC_SwCfgTable_t PWMC_SwCfgTable[PWMC_SW_HDL_MAX] = {
/*  HANDLE                    CMD_CHAN        PERIOD[ms]    MIN_CMD[ms]    */
/*  PWMC_HeatDrv    */  { DOIFC_CmdHeatDrv,     1000U,       PWMC_16MS,      },
/*  PWMC_HeatPass   */  { DOIFC_CmdHeatPass,    1000U,       PWMC_16MS,      },
/*  PWMC_HeatSteer  */  { DOIFC_CmdHeatSteer,   1000U,       PWMC_16MS,      },
};

const PWMC_HwCfgTable_t PWMC_HwCfgTable[PWMC_HW_HDL_MAX - PWMC_SW_HDL_MAX] = {
/*  HANDLE                    CMD_HDL                  FBK_HDL         DRIVER_TYPE    MIN_DUTY[%]  */
/*  PWMC_HeatLed   */  { (uint8_t)PWMD_CHAN_0,    INTD_CHAN_0,        HSD,          5U,       },
};

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

#endif /* __PWMC_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

