/**
 * @file EXMMA_cbk.h
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

#ifndef __EXMMA_CBK_H
#define __EXMMA_CBK_H

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

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* STATUS_NAG message Tx notification */
EXMMA_EXTERN void EXMMA_SendCbk(void);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* end __EXMMA_CBK_H */
