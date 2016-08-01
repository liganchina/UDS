/******************************************************************************/
/** @file       ADCC_cfgIf.h                                                  */
/** @title      Analog Digital Converter Control                              */
/** @brief      This file contain the public configuration macros and types   */
/**             of ADCC module for user settings. This file is developed for  */
/**             project MQB starting to QB35.                                 */
/** @date       27/08/2014                                                    */
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
| 27/08/2014 0.1  CC      First draft
|-----------------------------------------------------------------------------
| 05/09/2014 1.0  CC      First release
|-----------------------------------------------------------------------------
*/

#ifndef __ADCC_CFGIF_H
#define __ADCC_CFGIF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/**
  * Define the samples number to store in the datas buffer "SampleBuffer"
  * present in the struct ADCC_ChnBuffer_s. Greater is its value and more
  * accurate will be the average value computed.
  * WARNING: this value MSUT BE A POWER OF TWO and <= 128
  */
#define ADCC_BUFFER_SAMPLE_NMB    (8u)


/*______ G L O B A L - T Y P E S _____________________________________________*/

/**
 * Type to configure the ADC channels to use on the board.
 * At left must write the coding name to use in all project and
 * at right must insert the ADC physical channel.
 * The reference documentation to logical channels could be the
 * project schematic or hw/sw interface requirement.
 */
typedef enum ADCC_InputChn_e
{
  /**@{*/
  /* Direct Channels: */
  ADCC_MotorsSens      ,  /**< ANI0   */
  ADCC_HallLift        ,  /**< ANI1   */
  ADCC_HallSlide       ,  /**< ANI2   */
  ADCC_HallBackr       ,  /**< ANI3   */
  ADCC_HallTilt        ,  /**< ANI4   */
  ADCC_HallSpareMot    ,  /**< ANI5   */
  ADCC_Spare           ,  /**< ANI6   */
  ADCC_HeatPassFbk     ,  /**< ANI7   */
  ADCC_Ele_Fbk         ,  /**< ANI8   */
  ADCC_RelProtFbk      ,  /**< ANI9   */
  ADCC_FanDrvFbk       ,  /**< ANI12  */
  ADCC_FanPassFbk      ,  /**< ANI13  */
  /* Multiplexed Channels: */
  ADCC_KeyDiag         ,  /**< ANI11 - MUX ch. 0  */
  ADCC_SlideTiltKey    ,  /**< ANI11 - MUX ch. 1  */
  ADCC_BackrLiftKey    ,  /**< ANI11 - MUX ch. 2  */
  ADCC_MemKey          ,  /**< ANI11 - MUX ch. 3  */
  ADCC_7V5_Fbk         ,  /**< ANI11 - MUX ch. 5  */
  ADCC_MOT_Fbk         ,  /**< ANI11 - MUX ch. 6  */
  ADCC_HeatSteerFbk    ,  /**< ANI11 - MUX ch. 7  */
  ADCC_HeatSteerOutFbk ,  /**< ANI10 - MUX ch. 0  */
  ADCC_HeatDrvOutFbk   ,  /**< ANI10 - MUX ch. 1  */
  ADCC_HeatPassOutFbk  ,  /**< ANI10 - MUX ch. 2  */
  ADCC_NtcDrv          ,  /**< ANI10 - MUX ch. 3  */
  ADCC_NtcSteer        ,  /**< ANI10 - MUX ch. 4  */
  ADCC_NtcPass         ,  /**< ANI10 - MUX ch. 5  */
  ADCC_NtcVFbk         ,  /**< ANI10 - MUX ch. 6  */
  ADCC_HeatDrvFbk      ,  /**< ANI10 - MUX ch. 7  */
  ADCC_CHN_NMB
  /**@}*/
}ADCC_InputChn_t;


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

CTRL_Fault_t ADCC_GetSlideCurrentDiag(u08 hdl);

CTRL_Fault_t ADCC_GetRelProtDiag(u08 hdl);

#endif /* end __ADCC_CFGIF_H */

/*_____ E N D _____ (ADCC_cfgIf.h) ___________________________________________*/
