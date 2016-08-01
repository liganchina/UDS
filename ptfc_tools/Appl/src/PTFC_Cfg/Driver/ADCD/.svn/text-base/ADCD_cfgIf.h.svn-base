/******************************************************************************/
/** @file       ADCD_cfgIf.h                                                  */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Public interface of configuration files of ADCD module for    */
/**             user settings. This file is developed for Renesas RL78 family */
/**             - micro R5F10AGFLFB/F13. The requirement used for this driver */
/**             is the chapter 12 of the relative hw datasheet(v2.0).         */
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

#ifndef __ADCD_CFGIF_H
#define __ADCD_CFGIF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* TODO SGR_OK */
/**
 * Configuration define to set the continuos ADC channels number. It
 * configure the ANI00/P80 to ANI15/P97 pins to analog input of A/D 
 * converter according to requirement described in the par.10.3 of the 
 * reference hw datasheet. The section 8 describe the ADPC setting and 
 * the section 11 describe the port mode (PM8 and PM9) setting.
 * This pins are configurable as continuous number.
 *
 * WARNING: The range values is [0-15].
 *
 * For example: with the value 6 will be configurate as ADC inputs the
 * channels ANI0, ANI1, ANI2, ANI3, ANI4 and ANI5. Being the a continuos
 * number, if are used only the ANI0, ANI1 and ANI5, also must configure
 * the channels ANI2, ANI3 and ANI4.
 */
#define ADCD_CONT_CHN_NMB               ((uint8_t)14u)


/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#endif /* __ADCD_CFGIF_H */

/*_____ E N D _____ (ADCD_cfgIf.h) ___________________________________________*/
