/**
 * @file NWMA_cbk.h
 * @brief Callback interface for NetWork Management - Application layer. 
 * In this file are present all callback prototypes to receive notify by
 * network service layer.
 * In this module is implemented the network management FCA for NextGen network. 
 * The reference standard is N07320_ed5.
 *
 * @version 0.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 2 february 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
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
| 02/02/15   0.1  CC      First official release
|-----------------------------------------------------------------------------
*/

#ifndef __NWMA_CBK_H
#define __NWMA_CBK_H

#ifdef NWMA_IF_OWNER
	#define NWMA_EXTERN
#else
	#define NWMA_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Routine callback to use to get notify of master NWM message receiving.
 * WARNING: this routine MUST BE LINKED to network service
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_NwmReceivedCbk(void);

/**
 * @brief Routine callback to use to get notify of slave NWM message sending.
 * WARNING: this routine MUST BE LINKED to network service
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_SendNwmNaxCbk(void);

/**
 * @brief This routine call manages all events about DLL error management.
 * WARNING: It must be called at max every 50 ms in NET_ON state.
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_DllErrorMgmt(void);

NWMA_EXTERN void NWMA_dummySA(void);


#endif /* end __NWMA_CBK_H */

/*_____E N D _____ (NWMA_cbk.h) ______________________________________________*/
