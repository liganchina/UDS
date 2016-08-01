/*
*******************************************************************************
* Copyright(C) 2008, 2014 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation. 
*
* This device driver was created by Applilet3 for 78K0R/Fx3
* 16-Bit Single-Chip Microcontrollers
* Filename:	FE78K0R_CG_system_user.c
* Abstract:	This file implements device driver for System module.
* APIlib:	Applilet3 for 78K0R/Fx3 V3.01.00.01 [17 Jul 2014]
* Device:	uPD78F1833_64
* Compiler:	IAR Systems icc78k0r
* Creation date:	06/03/2015
*******************************************************************************
*/

/*
*******************************************************************************
** Include files
*******************************************************************************
*/
#include "FE78K0R_CG_macrodriver.h"
#include "FE78K0R_CG_system.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

extern MD_STATUS gPllStatus1;
extern MD_STATUS gPllStatus2;

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function process of Reset.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CG_ReadResetSource(void)
{
	UCHAR resetflag = RESF;
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
