/**
 * @file EXMMA_config.h
 * @brief EXternal Mirrors Management module
 * @li ...
 * </ul>
 *
 * @version 0.1
 * @author De Stephanis Alessio (Intecs S.p.A.)
 * @date 31/03/2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/************************** (C) Copyright 2014 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| ADS          De Stephanis Alessio       Intecs S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 31/03/2015 0.1  ADS     First release
|
*/

#ifndef __EXMMA_CONFIG_H
#define __EXMMA_CONFIG_H

#ifdef EXMMA_IF_OWNER
  #define EXMMA_EXTERN
#else
  #define EXMMA_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/* Call the following routines to update CAN messages */
#define EXMMA_UPDATE_PSNGR_VERT_POS(x)        (STATUS_HMSM.bit.MirrorPsngrVerticalPosCmd = (uint8_t)(x))
#define EXMMA_UPDATE_PSNGR_HORIZ_POS(x)       (STATUS_HMSM.bit.MirrorPsngrHorizzontalPosCmd = (uint8_t)(x))
#define EXMMA_UPDATE_DRIVER_VERT_POS(x)       (STATUS_HMSM.bit.MirrorDrvVerticalPosCmd = (uint8_t)(x))
#define EXMMA_UPDATE_DRIVER_HORIZ_POS(x)      (STATUS_HMSM.bit.MirrorDrvHorizzontalPosCmd = (uint8_t)(x))
#define EXMMA_SET_MIRROR_MOVEMENT_CMD(x)      (STATUS_HMSM.bit.DataCmdReady = (DataCmdReady_t)(x))
#define EXMMA_SET_BUZZER_NOTIFICATION(x)      (STATUS_HMSM.bit.Ack_beep = (uint8_t)(x))

/* Call the following routines to get CAN messages */
#define EXMMA_READ_PSNGR_VERT_POS             ((uint8_t)CMMD_MirrPsngVertPos)
#define EXMMA_READ_PSNGR_HORIZ_POS            ((uint8_t)STATUS_MIRROR.bit.MirrorPsngrHorizzontalPosSts)
#define EXMMA_READ_DRIVER_VERT_POS            ((uint8_t)STATUS_MIRROR.bit.MirrorDrvVerticalPosSts)
#define EXMMA_READ_DRIVER_HORIZ_POS           ((uint8_t)STATUS_MIRROR.bit.MirrorDrvHorizzontalPosSts)
#define EXMMA_READ_DRIVER_STILL               ((MirrorDrvStandStillSts_t)STATUS_MIRROR.bit.MirrorDrvStandStillSts)
#define EXMMA_READ_PSNGR_STILL                ((MirrorDrvStandStillSts_t)STATUS_MIRROR.bit.MirrorPsngrStandStillSts)
#define EXMMA_READ_DATA_READY                 ((DataCmdReady_t)STATUS_HMSM.bit.DataCmdReady)

/* Time definition for declaring stable CAN signal */
#define EXMMA_STABLE_CAN_SIGNAL_CHECK_TIME    20u     /* ///< x 100 ms (2000 ms) */
#define EXMMA_EEPROM_SIGNAL_SAVE_TIME         30u     /* ///< x 100 ms (3000 ms after data saving in RAM) */
#define EXMMA_REV_GEAR_DEACTIV_TIME           20u     /* ///< x 100 ms (2000 ms) */

/* Number of mirror signals to check */
#define EXMMA_MIRROR_SIGNALS                  6u      /* ///< number of signals to check and save in RAM or EEPROM */
#define EXMMA_MIN_STEP_DIFFERENCE_RAM         3u      /* ///< minimum number of steps for updating read signal in RAM */

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* end __EXMMA_CONFIG_H */
