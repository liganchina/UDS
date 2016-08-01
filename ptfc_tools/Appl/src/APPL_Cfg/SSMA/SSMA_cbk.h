/**
 * @file SSMA_cbk.h
 * @brief Smart Switch management: source code of ....
 * @n The main module features/services are:
 * @li ...
 * </ul>
 *
 * @version 0.1.
 * @author Gianpiero Lenta (Bitron S.p.A.)
 * @date 11 NOV 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/************************** (C) Copyright 2013 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero lenta           Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 05/12/2014  0.1  GIL    First release
|
*/

#ifndef __SSMA_CBK_H
#define __SSMA_CBK_H

#ifdef SSMA_IF_OWNER
	#define SSMA_EXTERN
#else
	#define SSMA_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Sleep routine for ADC control module used for transitions: 
 *        - RUN state        --> LOW_POWER state
 *        - PSEUDO_RUN state --> LOW_POWER state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */

/* Callback of the SMART SWITCH BUTTON  */

/**
 * @brief Callback routine generated on smart switch button 1 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortButton1Cbk(void);

/**
 * @brief Callback routine generated on smart switch button 2 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortButton2Cbk(void);

/**
 * @brief Callback routine generated on smart switch button 3 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortButton3Cbk(void);

/**
 * @brief Callback routine generated on smart switch button 4 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortButton4Cbk(void);

/**
 * @brief Callback routine generated on smart switch button 5 press event
 * send message CAN_MSG_1 (MSMx_status)
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortButton5Cbk(void);
/**
 * @brief Initialization routine for network Smart Smitch management module of the application layer.
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @param [in]
 * @param [out]
 * @return None
 */
SSMA_EXTERN void SSMA_ComfortNetCbk(void);





/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* end __SSMA_CBK_H */
