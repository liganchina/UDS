/**
 * @file HBRGC.c
 * @brief Public user configuration for Infineon BTM7752 module.
 * In this file must be configured the handles of all the chips used.
 * @author Daniele Cloralio
 * @date 08 apr 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
|              Daniele CLORALIO          Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 08/apr/2015     0.1  Daniele CLORALIO
 */

#ifndef HBRGC_CFGIF_H_
#define HBRGC_CFGIF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* enum for the chip selection */
typedef enum HBRGC_Handle_e
{
  HBRGC_BeltCarrier,
  HBRGC_HDL_MAX
} HBRGC_Handle_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

extern  DRVD_RStatus_t  HBRGC_BeltCarrierSetCmd    (uint8_t channel, CTRL_State_t state);
extern  CTRL_Fault_t    HBRGC_GetBeltCarrierDiag   (HBRGC_Handle_t hdl);

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* HBRGC_CFGIF_H_ */
