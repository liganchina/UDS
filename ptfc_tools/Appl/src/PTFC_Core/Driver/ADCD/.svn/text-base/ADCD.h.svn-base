/******************************************************************************/
/** @file       ADCD.h                                                        */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Private interface of ADC module for driver layer. This file   */
/**             is developed for Renesas RL78 family - micro R5F10AGFLFB/F13. */
/**             The requirement used for this driver is the chapter 12 of the */
/**             relative hw datasheet version 2.0.                            */
/** @date       21/07/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 21/07/2014 0.1  CC      First draft. For this first release will
|                         be not implmented:
|                         - the SNOOZE mode function management (TODO SGR)
|                         - the TEST mode (TODO SGR)
|                         - the HW trigger mode is partially implemented then
|                           for now isn't usable (TODO SGR)
|-----------------------------------------------------------------------------
| 28/07/2014 1.0  CC      First official release (without functionlity 
|                         described in the description release v0.1)
|-----------------------------------------------------------------------------
| 26/08/2014 1.1  CC      Module documentation terminated
|-----------------------------------------------------------------------------
*/

#ifndef __ADCD_H
#define __ADCD_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "DRVD_if.h"

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*____________________ CHANNELS AND INTERRUPT SECTION ___________________*/

/* TODO SGR_OK */
/**
 * General defines to disable/enable a generic hw peripheral
 */
#define ADCD_DISABLE                    (0x00u)
#define ADCD_ENABLE                     (0x01u)

/* TODO SGR_OK */
/**
 * Defines to set the INTAD interrupt priority level. The priority
 * level decrease from HIHG to LOW. This value are coded in 2 bits, 
 * bit0 e bit1 with a range [0-3]. The bit0 must be write in bit
 * register ADPR0 e the bit1 must be write in bit register ADPR1.
 */
#define ADCD_INTAD_HIGH                 (0x00u) /* high priority */
#define ADCD_INTAD_LEV1                 (0x01u) /* middle level 1 prty */
#define ADCD_INTAD_LEV2                 (0x02u) /* middle level 1 prty */
#define ADCD_INTAD_LOW                  (0x03u) /* low priority */

/*____________________ CONVERSION OPERATION SECTION ____________________*/

/**
 * Defines to set the "trigger mode" of the conversion operative mode.
 * The trigger mode allow the start conversion by a sw event, an hw
 * event associated to TM0 or RTC timer and an hw event with system
 * in sleep mode (wait mode).
 * According to the reference requirement, par. 12.3.3, the following
 * values must be write in the bit register ADTM0 and ADTM1,
 * respectively in the bit6 and bit7 of the ADM1 register.
 */
#define ADCD_SW_TRIG_MODE               (0x00u) /* Software trigger mode */
#define ADCD_HW_TRIG_MODE               (0x01u) /* Hardware trigger mode */



/**
 * Defines to set the hw trigger source. This setting is used only if
 * will be set the hw trigger mode. In this release the hw mode don't
 * use then now there will be not a detailed description.
 * According to the reference requirement, par. 12.3.3, the 
 * following values must be write in the bit register ADTRS0 and
 * ADTRS1, respectively in the bit0 and bit1 of the ADM1 register.
 */
#define ADCD_TRIGGER_INTTM12            (0x00u) /* TM12 timer interrupt signal */
#define ADCD_TRIGGER_INTTM22            (0x01u) /* TM22 timer interrupt signal */
#define ADCD_TRIGGER_ADTRG              (0x03u) /* External pin */



/**
 * Defines to set the hw trigger source. This setting is used only if
 * will be set the hw trigger mode. In this release the hw mode don't
 * use then now there will be not a detailed description.
 * According to the reference requirement, par. 12.3.3, the 
 * following values must be write in the bit register ADTRS0 and
 * ADTRS1, respectively in the bit0 and bit1 of the ADM1 register.
 */
#define ADCD_NO_EDGE_ADTRG              (0x00u)
#define ADCD_FALLING_EDGE_ADTRG         (0x01u)
#define ADCD_RISING_EDGE_ADTRG          (0x02u)
#define ADCD_BOTH_EDGE_ADTRG            (0x03u)



/**
 * Defines to set the "selection mode" of the conversion operative mode.
 * The selection mode manage the conversion of a single channel (select
 * mode) or the conversion of a group of 4 continuous channels (scan mode).
 * According to the reference requirement, par. 12.3.2, the following values
 * must be write in the bit register ADMD, the bit6 of the ADM0 register.
 */
/* Single channel conversion */
#define ADCD_SELECT_MODE                (0x00u)
/* Channels group conversion with an interrupt at end of the conversion */
#define ADCD_SCAN_MODE_MULTI_INT        (0x02u)
/* Channels group conversion with interrupt for each channel */
#define ADCD_SCAN_MODE_SINGLE_INT       (0x03u)





/**
 * Defines to set the "conversion mode" of the conversion operative mode.
 * The conversion mode manage the conversion repeatability using: a one-shot
 * scan (one-shot conversion mode) that start by a trigger but stop it 
 * automatically; or a continuous scan (sequential conversion mode) that
 * periodically convert the selected channels and stop it only with a sw event.
 * According to the reference requirement, par. 12.3.3, the following values
 * must be write in the bit register ADSCM in the bit5 of the ADM1 register.
 */
#define ADCD_CONTINUOUS_CONV_MODE       (0x00u)
#define ADCD_ONE_SHOT_CONV_MODE         (0x01u)


/*____________________ CONVERSION TIME SECTION ____________________*/

/* TODO SGR_OK */
/**
 * Defines to set the system clock frequency. This setting isn't used
 * to write in the ADC registers but It used to filter the possible
 * setting of the conversion time according to tables from 10.4 to
 * 10.8 of the reference requirement.
 */
#define ADCD_FCLOCK_2MHZ                (2u)
#define ADCD_FCLOCK_8MHZ                (8u)
#define ADCD_FCLOCK_16MHZ               (16u)
#define ADCD_FCLOCK_20MHZ               (20u)
#define ADCD_FCLOCK_24MHZ               (24u)



/**
 * Defines to set the "time mode" for the conversion time setting.
 * The normal mode 2 (see table 12.3 of the reference requirement),
 * respect to normal mode 1 and with the other parameters equal, 
 * improve the conversion speed performance.
 * According to the reference requirement, table 12.3, the 
 * following values must be write in the bit register LV0 and LV1,
 * respectively in the bit1 and bit2 of the ADM0 register.
 */
#define ADCD_HIGH_SPEED_1_MODE          (0x00u)
#define ADCD_HIGH_SPEED_2_MODE          (0x01u)
#define ADCD_NORMAL_MODE                (0x02u)





/**
 * Defines to set the prescaler for the conversion clock used for 
 * the conversion time setting. This setting is the largest
 * contribution to conversion time setting. The input clock 
 * frequency is given by the defines ADCD_FCLOCK_XMHZ previously 
 * described. 
 * According to the reference requirement, table 12.3, the 
 * following values must be write in the bit register FR0, FR1 and 
 * FR2,respectively in the bit3, bit4 and bit5 of the ADM0 register.
 */
#define ADCD_FCLOCK_MAX_2MHZ            (0x00u) /**< Prescaler for fCLK <= 2 MHz */
#define ADCD_FCLOCK_MAX_4MHZ            (0x01u) /**< Prescaler for fCLK <= 4 MHz */
#define ADCD_FCLOCK_MAX_6MHZ            (0x02u) /**< Prescaler for fCLK <= 6 MHz */
#define ADCD_FCLOCK_MAX_8MHZ            (0x03u) /**< Prescaler for fCLK <= 8 MHz */
#define ADCD_FCLOCK_MAX_10MHZ           (0x04u) /**< Prescaler for fCLK <= 10 MHz */
#define ADCD_FCLOCK_MAX_12MHZ           (0x05u) /**< Prescaler for fCLK <= 12 MHz */
#define ADCD_FCLOCK_MAX_14MHZ           (0x06u) /**< Prescaler for fCLK <= 14 MHz */
#define ADCD_FCLOCK_MAX_16MHZ           (0x07u) /**< Prescaler for fCLK <= 16 MHz */
#define ADCD_FCLOCK_MAX_18MHZ           (0x08u) /**< Prescaler for fCLK <= 18 MHz */
#define ADCD_FCLOCK_MAX_20MHZ           (0x09u) /**< Prescaler for fCLK <= 20 MHz */
#define ADCD_FCLOCK_MAX_22MHZ           (0x0Au) /**< Prescaler for fCLK <= 22 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV1      (0x0Bu) /**< Prescaler 1 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV2      (0x0Cu) /**< Prescaler 2 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV3      (0x0Du) /**< Prescaler 3 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV4      (0x0Eu) /**< Prescaler 4 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV5      (0x0Fu) /**< Prescaler 5 for fCLK <= 24 MHz */


/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/


#endif /* end __ADCD_H */

/*_____ E N D _____ (ADCD.h) _________________________________________________*/
