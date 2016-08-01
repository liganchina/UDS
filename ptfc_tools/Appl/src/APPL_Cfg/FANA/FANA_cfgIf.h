/******************************************************************************/
/** @file       FANA_cfgIf.h                                                  */
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
#ifndef __FANA_CFGIF_H__
#define __FANA_CFGIF_H__

/* Module inhibition filter */
#ifdef __FANA_IS_PRESENT__ 

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

typedef enum FANA_handle_e
{
	FANA_BACK_CUSH_FAN,
	FANA_MAX_HDL
} FANA_handle_t;


/*_____ G L O B A L - D A T A ________________________________________________*/
extern u16 FANA_PowerFan; /* variable for shared supply management */

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

HeatCoolingLevel_t FANA_GetCoolLevel(void);

APPL_ResSts_t FANA_SetCoolLevel(FANA_handle_t hdl, HeatCoolingLevel_t level);

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (FANA_cfgIf.h) _________________________________________*/
