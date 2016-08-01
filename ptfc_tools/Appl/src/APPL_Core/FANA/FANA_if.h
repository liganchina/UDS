/******************************************************************************/
/** @file       FANA_if.h                                                     */
/** @title      FAN application interface                                     */
/** @brief      module for FAN management                                     */
/** @date       12/02/2015                                                    */
/** @author     Davide Fogliano                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano		     Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 12/02/2015 0.1  DF      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __FANA_IF_H__
#define __FANA_IF_H__

/* Module inhibition filter */
#ifdef __FANA_IS_PRESENT__ 

/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "FANA_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/
/* Dichiarazione dell'interfaccia del Layer */
#ifdef FANA_IF_OWNER
	#define FANA_EXTERN
#else
	#define FANA_EXTERN		extern
#endif
/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

//TODO TANK: verificare tutte le interfacce e dopo approvazione/Debug commentare bene!

FANA_EXTERN void FANA_Init(void);

FANA_EXTERN void FANA_Mgm(void);

FANA_EXTERN APPL_ResSts_t FANA_SetLevel(FANA_handle_t hdl,u08 level);

FANA_EXTERN APPL_ResSts_t FANA_SetState(FANA_handle_t hdl, APPL_DispaState_t state);

CTRL_Fault_t FANA_GetDiag(FANA_handle_t hdl);

/* functions for IOContro management */
FANA_EXTERN u08  FANA_CheckIoControl(u08 hdl, u08 command);
FANA_EXTERN void FANA_StartIoControl(u08 hdl, u08 level);
FANA_EXTERN void FANA_StopIoControl(u08 hdl); 

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif 
#endif
/*______ E N D _____ (FANA_if.h) _________________________________________*/
