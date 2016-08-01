/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              Funp.h                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/07/2012                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| DF           Davide Fogliano           Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 22/05/2013  0.1  GIL     First DRAFT
*/
#ifndef FUNP_IF_H
#define FUNP_IF_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "FUNP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/
typedef struct
{
  s16 X;
  s16 Y;
}FUNP_Interp_curve_point_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/
#define POLY 0x8408u  /* CRC-CCITT - Polynomial: x^16 + x^12 + x^5 + 1 (0x8408) */

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function is called once at system boot to init module
 * @return none
 * @retval none
 */
void FUNP_Init(void);

/**
 * @brief This function Convert hex (2 byte) into BCD
 * @param num (u16 to convert)
 * @param *result (output string)
 * @return void (work directly on string pointed)
 * @retval none
 */
void FUNP_ConvertU16ToString(u16 num, u08 *result);


/**
 * @brief compute crc 16
 * @param *data (pointer to data vector from whom calculate crc)
 * @param len (data vector lenght)
 * @return u16
 * @retval crc calculated
 */
u16 FUNP_crc16_little(u08 *data, u16 len);

/**
 * @brief compute crcFast
 * @param message[] (pointer to data vector from whom calculate crc)
 * @param nBytes (data vector lenght)
 * @return u16
 * @retval crc calculated
 */
u16 crcFast(u08 const message[], u16 nBytes);

/**
 * @brief it convert given raw value (X) using given interpolation curve points array 
 * @param s16 X (Raw AD value)
 * @param Interp_curve_point_t TAB[] (interpolation curve array)
 * @param u08 num_point (number of point in TAB[])
 * @return u16
 * @retval Y value corresponding to X according to TAB[]
 */
s16 FUNP_Curve(s16 X, const FUNP_Interp_curve_point_t TAB[], u08 num_point);
//s16 FUNP_Curve(s16 X, s16 Z, const Interp_curve_point_t TAB[], u08 num_point);

/**
 * @brief Find the interval in TAB[] that contains X
 * @param s16 X (Raw AD value)
 * @param Interp_curve_point_t TAB[] (interpolation curve array)
 * @param u08 num_point (number of point in TAB[])
 * @return u08
 * @retval low index of interval in TAB[] that contains the value X
 */
u08 FUNP_Interval_Binary(s16 X, const FUNP_Interp_curve_point_t ITAB[], u08 num_point);

//FUNP_NTC_Range_t  FUNP_NTC_Range(s16 X, s16 Z, const Interp_curve_point_t TAB[], u08 num_point);    //L.B.

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif
