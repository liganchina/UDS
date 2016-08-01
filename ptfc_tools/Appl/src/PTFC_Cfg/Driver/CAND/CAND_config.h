/**
 * @file CAND_config.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:20:9
 * @brief File containing the user configuration of CAND module.
 * 
 * @see www.Bitron.net
 */
#ifndef __CAND_CONFIG_H
#define __CAND_CONFIG_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ P R I V A T E - D E F I N E S _______________________________________*/

/* Constant for direction value */
#define CAND_DIR_OUTPUT                 (0u)
#define CAND_DIR_INPUT                  (1u)

/* CAN Transmission port mode */
#define CAND_SetTxPortMode(Dir)         (PM7_bit.no2 = (Dir))
/* CAN Reception port mode */
#define CAND_SetRxPortMode(Dir)         (PM7_bit.no3 = (Dir))
/* CAN TX port status */
#define CAND_SetTxSts(Sts)              (P7_bit.no2 = (Sts))
/* CAN RX port status */
#define CAND_GetRxDataLevel()           (P7_bit.no3)
/** Get NERR control pin status */
#define CAND_GetNerrSts()               (bool_t)DIOD_GetLevel(DIOD_CAN_Ner)
/** Set STADBY control pin status */
#define CAND_SetStandbySts(Sts)         (void)DIOD_SetLevel(DIOD_CAN_Stb, (DRVD_Level_t)(Sts))
/** Set ENABLE control pin status */
#define CAND_SetEnableSts(Sts)          (void)DIOD_SetLevel(DIOD_CAN_En, (DRVD_Level_t)(Sts))
/* Register setting for Baud Rate */
#define CAND_BAUD_50K                   (9u)
#define CAND_BAUD_125K                  (3u)


/*______ P R I V A T E - T Y P E S ___________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/


#endif /* end __CAND_CONFIG_H */

/*______ E N D _____ (CAND_config.h) _________________________________________*/
