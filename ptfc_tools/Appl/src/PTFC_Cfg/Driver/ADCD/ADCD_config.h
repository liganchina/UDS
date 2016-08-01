/******************************************************************************/
/** @file       ADCD_config.h                                                 */
/** @title      Analog Digital Converter Driver                               */
/** @brief      This file contain all configuration parameters of ADCD module */
/**             for user settings. This file is developed for Renesas RL78    */
/**             family - micro R5F10AGFLFB/F13. The requirement used for this */
/**             driver is the chapter 12 of the relative hw datasheet(v2.0).  */
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

#ifndef __ADCD_CONFIG_H
#define __ADCD_CONFIG_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "DRVD_if.h"

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*____________________ CHANNELS AND INTERRUPT SECTION ___________________*/


/* TODO SGR_OK */
/**
 * Configuration define to disable/enable the INTAD interrupt generation.
 * 
 * This configuration can assume the following values:
 * - ADCD_DISABLE
 * - ADCD_ENABLE
 */
#define ADCD_INTAD                      ADCD_ENABLE

/* TODO SGR_OK */
/**
 * Configuration define to set the INTAD interrupt priority level. 
 * The priority level decrease from HIHG to LOW.
 * This configuration is present only if the configuration define
 * ADCD_INTAD = ADCD_ENABLE (INTAD interrupt enable).
 * 
 * This configuration can assume the following values:
 * - ADCD_INTAD_HIGH: is the highest priority
 * - ADCD_INTAD_LEV1: is a middle priority but greater than level2
 * - ADCD_INTAD_LEV2: is a middle priority but smaller than level1
 * - ADCD_INTAD_LOW:  is the lowest priority
 */
#if (ADCD_INTAD == ADCD_ENABLE)
  #define ADCD_INTAD_PRTY               ADCD_INTAD_LEV1      
#endif


#if (ADCD_INTAD == ADCD_ENABLE)
  #define ADCD_ENABLE_SW_BREAK          ADCD_ENABLE
#endif


/*____________________ CONVERSION OPERATION SECTION ____________________*/



/**
 * Configuration define to set the "trigger mode" of the conversion 
 * operative mode. The trigger mode allow the start conversion by a 
 * sw event, an hw event associated to a specific timer and an hw event 
 * with the system in sleep mode (wait mode). 
 * For further details see the reference requirement to par. 12.3.3.
 * 
 * This configuration can assume the following values:
 * @li ADCD_SW_TRIG_MODE: the start conversion is performed by a sw routine
 * @li ADCD_HW_TRIG_MODE: the start conversion is performed by a 
 *     timer. This hw mode run only with micro in run
 *
 * !!! WARNING !!!: in this release the value ADCD_HW_TRIG_MODE cannot be 
 * used because partially implemented.
 */
#define ADCD_TRIG_MODE                  ADCD_SW_TRIG_MODE



/* TODO SGR - da definire */
#if 0
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
#endif



/**
 * Configuration define to set the "trigger mode" of the conversion 
 * operative mode. The trigger mode allow the start conversion by a 
 * sw event, an hw event associated to a specific timer and an hw event 
 * with the system in sleep mode (wait mode). 
 * For further details see the reference requirement to par. 12.3.3.
 * 
 * This configuration can assume the following values:
 * @li ADCD_SW_TRIG_MODE: the start conversion is performed by a sw routine
 * @li ADCD_HW_TRIG_MODE: the start conversion is performed by a 
 *     timer. This hw mode run only with micro in run
 *
 * !!! WARNING !!!: in this release the value ADCD_HW_TRIG_MODE cannot be 
 * used because partially implemented.
 */
#if (ADCD_TRIG_MODE == ADCD_HW_TRIG_MODE)
  #define ADCD_HW_TRIGGER_SOURCE          ADCD_TRIGGER_INTTM12
#endif



#if 0

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

#endif





/**
 * Configuration define to set the "trigger mode" of the conversion 
 * operative mode. The trigger mode allow the start conversion by a 
 * sw event, an hw event associated to a specific timer and an hw event 
 * with the system in sleep mode (wait mode). 
 * For further details see the reference requirement to par. 12.3.3.
 * 
 * This configuration can assume the following values:
 * @li ADCD_SW_TRIG_MODE: the start conversion is performed by a sw routine
 * @li ADCD_HW_TRIG_MODE: the start conversion is performed by a 
 *     timer. This hw mode run only with micro in run
 *
 * !!! WARNING !!!: in this release the value ADCD_HW_TRIG_MODE cannot be 
 * used because partially implemented.
 */
#if (ADCD_TRIG_MODE == ADCD_HW_TRIG_MODE)
  #if (ADCD_HW_TRIGGER_SOURCE == ADCD_TRIGGER_ADTRG)
    #define ADCD_EDGE_ADTRG_SOURCE          ADCD_RISING_EDGE_ADTRG
  #endif
#endif



/**
 * Configuration define to set the "selection mode" of the conversion 
 * operative mode. The selection mode manage the conversion of a single 
 * channel (select mode) or the conversion of a group of 4 continuous 
 * channels (scan mode).
 * For further details see the reference requirement to par. 12.3.2.
 * 
 * This configuration can assume the following values:
 * @li ADCD_SELECT_MODE: single channel conversion
 * @li ADCD_SCAN_MODE_MULTI_INT: four continuous channels conversion
 * @li ADCD_SCAN_MODE_SINGLE_INT
 */
#define ADCD_SELECTION_MODE             ADCD_SCAN_MODE_SINGLE_INT




/* TODO SGR_OK */
/**
 * Configuration define to set the "conversion mode" of the conversion 
 * operative mode. The conversion mode manage the conversion repeatability
 * using: a one-shot scan (one-shot conversion mode) that start by a 
 * trigger but stop it automatically; or a continuous scan (continuous 
 * conversion mode) that periodically convert the selected channels and 
 * stop it only with a sw event.
 * For further details see the reference requirement to par. 10.4.4.
 * 
 * This configuration can assume the following values:
 * @li ADCD_CONTINUOUS_CONV_MODE: continuous conversion. Must be stopped by sw.
 * @li ADCD_ONE_SHOT_CONV_MODE: one-shot conversion. 
 *     It's stopped automatically by ADC controller.
 */
#define ADCD_CONVERSION_MODE            ADCD_ONE_SHOT_CONV_MODE



/**
 * Configuration define to disable/enable the blocker management to
 * conversion in one-shot mode and select mode. It by a ISR flag and
 * a blocker delay, waits the end conversion and in exit from routine
 * ADCD_SwTriggerOneShotManager, the ADC data read will be ready.
 * 
 * This configuration can assume the following values:
 * - ADCD_DISABLE
 * - ADCD_ENABLE
 */
#if (ADCD_CONVERSION_MODE == ADCD_ONE_SHOT_CONV_MODE)
  #if (ADCD_SELECTION_MODE == ADCD_SELECT_MODE)        
    #define ADCD_SELECT_ONESHOT_BLOCK     ADCD_ENABLE
  #else
    #define ADCD_SELECT_ONESHOT_BLOCK     ADCD_DISABLE
  #endif
#endif


/**
 * Configuration define to disable/enable the blocker management to
 * conversion in one-shot mode and select mode. It by a ISR flag and
 * a blocker delay, waits the end conversion and in exit from routine
 * ADCD_SwTriggerOneShotManager, the ADC data read will be ready.
 * 
 * This configuration can assume the following values:
 * - ADCD_DISABLE
 * - ADCD_ENABLE
 */
#if (ADCD_CONVERSION_MODE == ADCD_ONE_SHOT_CONV_MODE)
  #if (ADCD_SELECTION_MODE == ADCD_SCAN_MODE_SINGLE_INT)        
    #define ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK     ADCD_DISABLE
  #endif
#endif



/*____________________ CONVERSION TIME SECTION ____________________*/

/*
 *
   According to table 12.3 of the reference requirement, for set the
   conversion time must set 3 configuration defines: ADCD_FCLOCK_MHZ, 
   ADCD_CONV_TIME_MODE and ADCD_CONV_TIME. 
   The following look-up table, according to:
    - trigger mode with configuration parameter ADCD_TRIG_MODE;
    - hw peripheral clock with configuration parameter ADCD_FCLOCK_MHZ;
    - Conversion time prescaler with configuration parameter ADCD_CONV_TIME;
   filter the possible conversion time settings. Some possible time settings 
   aren't available because must cover the CPU micro by overload.
   
   !!! WARNING !!! - if there will be some wrong settings, the set routine
   for conversion time will set automatically the lower speed changing only
   the ADCD_CONV_TIME value.
   
   For example:
   - #define ADCD_TRIG_MODE                  ADCD_SW_TRIG_MODE
   - #define ADCD_FCLOCK_MHZ                 ADCD_FCLOCK_8MHZ
   - #define ADCD_CONV_TIME_MODE             ADCD_NORMAL_MODE_2
   - #define ADCD_CONV_TIME                  ADCD_TIMING_FCLOCK_DIV_08
   
   The conversion time will be: 17us
*
*/
/* ------------------------------------------------------------------- */
/* |                TRIGGER MODE: Hardware trigger Wait              | */
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
/* |   Setting parameters: - Normal mode 1; - Peripheral hw Fclk     | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  1MHz  |  2MHz  |  4MHz  |  8MHz  | 16MHz  | 32MHz  |  Clk Div  | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/64  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  27us  |  Fclk/32  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  27us  | 13.5us |  Fclk/16  | */
/* |  N.A.  |  N.A.  |  N.A.  |  27us  | 13.5us |  N.A.  |  Fclk/8   | */
/* |  N.A.  |  N.A.  |  N.A.  | 20.3us | 10.1us |  N.A.  |  Fclk/6   | */
/* |  N.A.  |  N.A.  | 33.8us | 16.9us |  N.A.  |  N.A.  |  Fclk/5   | */
/* |  N.A.  |  N.A.  |  27us  |  N.A.  |  N.A.  |  N.A.  |  Fclk/4   | */
/* |  N.A.  |  27us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/2   | */
/* ------------------------------------------------------------------- */
/* |   Setting parameters: - Normal mode 2; - Peripheral hw Fclk     | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  1MHz  |  2MHz  |  4MHz  |  8MHz  | 16MHz  | 32MHz  |  Clk Div  | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/64  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  25us  |  Fclk/32  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  25us  | 12.5us |  Fclk/16  | */
/* |  N.A.  |  N.A.  |  N.A.  |  25us  | 12.5us |  N.A.  |  Fclk/8   | */
/* |  N.A.  |  N.A.  |  N.A.  | 18.8us |  9.4us |  N.A.  |  Fclk/6   | */
/* |  N.A.  |  N.A.  | 31.3us | 15.6us |  N.A.  |  N.A.  |  Fclk/5   | */
/* |  N.A.  |  N.A.  |  25us  |  N.A.  |  N.A.  |  N.A.  |  Fclk/4   | */
/* |  N.A.  |  25us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/2   | */
/* ------------------------------------------------------------------- */
/*                                                                     */
/* ------------------------------------------------------------------- */
/* |             TRIGGER MODE: - Hardware trigger No Wait            | */
/* |                           - Software trigger                    | */
/* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------- */
/* |   Setting parameters: - Normal mode 1; - Peripheral hw Fclk     | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  1MHz  |  2MHz  |  4MHz  |  8MHz  | 16MHz  | 32MHz  |  Clk Div  | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  38us  |  Fclk/64  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  38us  |  19us  |  Fclk/32  | */
/* |  N.A.  |  N.A.  |  N.A.  |  38us  |  19us  | 9.5us  |  Fclk/16  | */
/* |  N.A.  |  N.A.  |  38us  |  19us  | 9.5us  |  N.A.  |  Fclk/8   | */
/* |  N.A.  |  N.A.  | 28.5us | 14.3us |  N.A.  |  N.A.  |  Fclk/6   | */
/* |  N.A.  |  N.A.  | 23.8us |  N.A.  |  N.A.  |  N.A.  |  Fclk/5   | */
/* |  N.A.  |  38us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/4   | */
/* |  38us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/2   | */
/* ------------------------------------------------------------------- */
/* |   Setting parameters: - Normal mode 2; - Peripheral hw Fclk     | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  1MHz  |  2MHz  |  4MHz  |  8MHz  | 16MHz  | 32MHz  |  Clk Div  | */
/* |--------|--------|--------|--------|--------|--------|-----------| */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  34us  |  Fclk/64  | */
/* |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  34us  |  17us  |  Fclk/32  | */
/* |  N.A.  |  N.A.  |  N.A.  |  34us  |  17us  | 8.5us  |  Fclk/16  | */
/* |  N.A.  |  N.A.  |  34us  |  17us  | 8.5us  |  N.A.  |  Fclk/8   | */
/* |  N.A.  |  N.A.  | 25.5us |  13us  |  N.A.  |  N.A.  |  Fclk/6   | */
/* |  N.A.  |  N.A.  | 21.3us |  N.A.  |  N.A.  |  N.A.  |  Fclk/5   | */
/* |  N.A.  |  34us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/4   | */
/* |  34us  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  N.A.  |  Fclk/2   | */
/* ------------------------------------------------------------------- */


/**
 * Configuration define to set system clock frequency. This parameter
 * represent the "peripheral hw Fclk" of the previous tables. This setting 
 * isn't used to write in the ADC registers but It used to select and to 
 * filter the possible setting of the conversion time.
 * 
 * This configuration can assume the following values:
 * @li ADCD_FCLOCK_2MHZ
 * @li ADCD_FCLOCK_8MHZ
 * @li ADCD_FCLOCK_16MHZ
 * @li ADCD_FCLOCK_20MHZ
 * @li ADCD_FCLOCK_24MHZ
 */
#define ADCD_FCLOCK_MHZ                 ADCD_FCLOCK_24MHZ




#define ADCD_DISCHARGE_FNC              ADCD_ENABLE             


/* TODO SGR_OK */
/**
 * Configuration define to improve conversion time setting according to 
 * tables from 10.4 to 10.8 of the reference requirement. With equal 
 * parameters setting the speed performance improve from ADCD_NORMAL_MODE 
 * (lowest speed) to ADCD_HIGH_SPEED_1_MODE (highest speed).
 * 
 * This configuration can assume the following values:
 * @li ADCD_HIGH_SPEED_1_MODE: high conversion speed (highest improvment)
 * @li ADCD_HIGH_SPEED_2_MODE: midle conversion speed
 * @li ADCD_NORMAL_MODE: low conversion speed (lowest improvment)
 */
#define ADCD_CONV_TIME_MODE             ADCD_NORMAL_MODE

/**
 * Configuration define to set the prescaler for the conversion clock 
 * used for the conversion time setting according to table 12.3 of the 
 * reference requirement. This setting is the largest contribution to 
 * conversion time. This parameter represent the "Clk Div" of the 
 * previous tables and it's present in the right column.
 * 
 * This configuration can assume the following values:
 * @li ADCD_FCLOCK_MAX_2MHZ: prescaler for fCLK <= 2 MHz
 * @li ADCD_FCLOCK_MAX_4MHZ: prescaler for fCLK <= 4 MHz
 * @li ADCD_FCLOCK_MAX_6MHZ: prescaler for fCLK <= 6 MHz
 * @li ADCD_FCLOCK_MAX_8MHZ: prescaler for fCLK <= 8 MHz
 * @li ADCD_FCLOCK_MAX_10MHZ: prescaler for fCLK <= 10 MHz
 * @li ADCD_FCLOCK_MAX_12MHZ: prescaler for fCLK <= 12 MHz
 * @li ADCD_FCLOCK_MAX_14MHZ: prescaler for fCLK <= 14 MHz
 * @li ADCD_FCLOCK_MAX_16MHZ: prescaler for fCLK <= 16 MHz
 * @li ADCD_FCLOCK_MAX_18MHZ: prescaler for fCLK <= 18 MHz
 * @li ADCD_FCLOCK_MAX_20MHZ: prescaler for fCLK <= 20 MHz
 * @li ADCD_FCLOCK_MAX_22MHZ: prescaler for fCLK <= 22 MHz
 * @li ADCD_FCLOCK_MAX_24MHZ_DIV1: prescaler 1 for fCLK <= 24 MHz
 * @li ADCD_FCLOCK_MAX_24MHZ_DIV2: prescaler 2 for fCLK <= 24 MHz
 * @li ADCD_FCLOCK_MAX_24MHZ_DIV3: prescaler 3 for fCLK <= 24 MHz
 * @li ADCD_FCLOCK_MAX_24MHZ_DIV4: prescaler 4 for fCLK <= 24 MHz
 * @li ADCD_FCLOCK_MAX_24MHZ_DIV5: prescaler 5 for fCLK <= 24 MHz
 */
#define ADCD_CONV_TIME                  ADCD_FCLOCK_MAX_24MHZ_DIV5


/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/


#endif /* end __ADCD_CONFIG_H */

/*______ E N D _____ (ADCD_config.h) _________________________________________*/
