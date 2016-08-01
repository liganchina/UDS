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
* Filename:	FE78K0R_CG_serial_user.c
* Abstract:	This file implements device driver for Serial module.
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
#include "FE78K0R_CG_serial.h"
/* Start user code for include. Do not edit comment generated here */
#include "global.h"
#include "EEPC.h"
#include "EEPC_if.h"
/* End user code. Do not edit comment generated here */

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
extern UCHAR  *gpCsi00RxAddress;	/* csi00 receive buffer address */
extern USHORT gCsi00RxLen;		/* csi00 receive data length */
extern USHORT gCsi00RxCnt;		/* csi00 receive data count */
extern UCHAR  *gpCsi00TxAddress;	/* csi00 send buffer address */
extern USHORT gCsi00TxLen;		/* csi00 send data length */
extern USHORT gCsi00TxCnt;		/* csi00 send data count */


/* Start user code for global. Do not edit comment generated here */
#define MD_CSI00_IF_CHECK	0x02U
#define MD_CSI00_IF_RST		0xFDU

extern __saddr EEPC_StatiCSI EEPC_StatoCSI;

static uint16_t Spid_INTCSI00_IsrCbk(void);

/* End user code. Do not edit comment generated here */


void SPID_Init(void)
{
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTCSI00, (ISRD_EvtCbk_t)Spid_INTCSI00_IsrCbk);
}

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is INTCSI00 interrupt service routine.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
static uint16_t Spid_INTCSI00_IsrCbk(void)
{
  /* Enable nested interrupt */
  EI();
  
  if (EEPC_StatoCSI == CSI_WAIT_EEPROM)
  {
    EEPC_Mgm();
  }
  else
  {
    // release SPI bus
    // disattiva i segnali di CS di tutti i componenti connessi al bus
    EEPROM_CS_OFF();
    EEPC_StatoCSI = CSI_IDLE;
  }
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTCSI00));
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of CSI00.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_ReceiveEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of CSI00.
**
**  Parameters:
**	err_type: error type value
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_ErrorCallback(UCHAR err_type)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function is a callback function of CSI00.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_SendEndCallback(void)
{
	/* Start user code. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract: Polling of CSI00 interrupt flag.
**	This function must be called only at interrupt disabled.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void SPID_INTCSI00_IsrPolling(void)
{
  /* Verifico se è scattato l'interrupt */
  if (IF0H & MD_CSI00_IF_CHECK)
  {
    /* Trasmissione/Ricezione terminata, chiamo l'eeprom */
    if (EEPC_StatoCSI == CSI_WAIT_EEPROM)
    {
      EEPC_Mgm();
    }
    /* Resetto il flag di interrupt */
    IF0H &= MD_CSI00_IF_RST;
  }
}

/* End user code. Do not edit comment generated here */
