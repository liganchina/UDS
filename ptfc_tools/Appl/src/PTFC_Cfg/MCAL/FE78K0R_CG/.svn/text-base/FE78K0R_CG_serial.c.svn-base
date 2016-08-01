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
* Filename:	FE78K0R_CG_serial.c
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

/*
*******************************************************************************
**  Global define
*******************************************************************************
*/
UCHAR  *gpCsi00RxAddress;	/* csi00 receive buffer address */
USHORT gCsi00RxLen;		/* csi00 receive data length */
USHORT gCsi00RxCnt;		/* csi00 receive data count */
UCHAR  *gpCsi00TxAddress;	/* csi00 send buffer address */
USHORT gCsi00TxLen;		/* csi00 send data length */
USHORT gCsi00TxCnt;		/* csi00 send data count */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes SAU0.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void SAU0_Init(void)
{
	SAU0EN = 1U;	/* supply SAU0 clock */
	NOP();
	NOP();
	NOP();
	NOP();
	SPS0 = _0000_SAU_CK00_FCLK_0 | _0000_SAU_CK01_FCLK_0;
	CSI00_Init();
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function initializes CSI00.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_Init(void)
{
	ST0 |= _0001_SAU_CH0_STOP_TRG_ON;	/* disable CSI00 */
	CSIMK00 = 1U;	/* disable INTCSI00 interrupt */
	CSIIF00 = 0U;	/* clear INTCSI00 interrupt flag */
	/* Set INTCSI00 level1 priority */
	CSIPR100 = 0U;
	CSIPR000 = 1U;
	SIR00 = _0004_SAU_SIRMN_FECTMN | _0002_SAU_SIRMN_PECTMN | _0001_SAU_SIRMN_OVCTMN;	/* clear error flag */
	SMR00 = _0020_SAU_SMRMN_INITIALVALUE | _0000_SAU_CLOCK_SELECT_CK00 | _0000_SAU_CLOCK_MODE_CKS | _0000_SAU_TRIGGER_SOFTWARE | _0000_SAU_CSI | _0000_SAU_TRANSFER_END;
	SCR00 = _C000_SAU_RECEPTION_TRANSMISSION | _0000_SAU_TIMING_1 | _0000_SAU_MSB | _0007_SAU_LENGTH_8;
	SDR00 = _4A00_CSI00_DIVISOR;
	SO0 |= _0100_SAU_CH0_CLOCK_OUTPUT_1;	/* output CSI00 clock value 1 */
	SO0 &= ~_0001_SAU_CH0_DATA_OUTPUT_1;	/* output CSI00 data value 0 */
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;	/* enable CSI00 output */
	STSEL &= 0xEFU;	/* use P30, P17, P16, P15 as SSI00, SCK00, SI00, SO00 */
	/* Set SI00 pin */
	PM1 |= 0x40U;
	/* Set SO00 pin */
	P1 |= 0x20U;
	PM1 &= 0xDFU;
	/* Set SCK00 pin */
	P1 |= 0x80U;
	PM1 &= 0x7FU;
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function starts CSI00.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_Start(void)
{
	CSIIF00 = 0U;	/* clear INTCSI00 interrupt flag */
	CSIMK00 = 0U;	/* enable INTCSI00 */
	SOE0 |= _0001_SAU_CH0_OUTPUT_ENABLE;	/* enable CSI00 output */
	SS0 |= _0001_SAU_CH0_START_TRG_ON;	/* enable CSI00 */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function stops CSI00.
**
**  Parameters:
**	None
**
**  Returns:
**	None
**
**-----------------------------------------------------------------------------
*/
void CSI00_Stop(void)
{
	ST0 |= _0001_SAU_CH0_STOP_TRG_ON;	/* disable CSI00 */
	SOE0 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;	/* disable CSI00 output */
	CSIMK00 = 1U;	/* disable INTCSI00 interrupt */
	CSIIF00 = 0U;	/* clear INTCSI00 interrupt flag */
}
/*
**-----------------------------------------------------------------------------
**
**  Abstract:
**	This function sends and receives CSI00 data.
**
**  Parameters:
**	txbuf: transfer buffer pointer
**	txnum: buffer size
**	rxbuf: receive buffer pointer
**
**  Returns:
**	MD_OK
**	MD_ARGERROR
**
**-----------------------------------------------------------------------------
*/
MD_STATUS CSI00_SendReceiveData(UCHAR *txbuf, USHORT txnum, UCHAR *rxbuf)
{
	MD_STATUS status = MD_OK;

	if (txnum < 1U)
	{
		status = MD_ARGERROR;
	}
	else
	{
		gCsi00TxCnt = txnum;	/* send data count */
		gpCsi00TxAddress = txbuf;	/* send buffer pointer */
		gpCsi00RxAddress = rxbuf;	/* receive buffer pointer */
		if((SCR00 & 0x000FU) > _0007_SAU_LENGTH_8)
		{
			/* Transfer data length is more than 8 bit */
			/* The data number should be even */
			if ((txnum & 0x1U) == 1U)
			{
				status = MD_ARGERROR;
			}
			else
			{
				CSIMK00 = 1U;	/* disable INTCSI00 interrupt */
				SDR00 = *(USHORT*)gpCsi00TxAddress;	/* started by writing data to SDR[15:0] */
				gpCsi00TxAddress += 2U;
				gCsi00TxCnt -= 2U;
				CSIMK00 = 0U;	/* enable INTCSI00 interrupt */
			}
		}
		else
		{
			CSIMK00 = 1U;	/* disable INTCSI00 interrupt */
			SDR00L = *gpCsi00TxAddress;	/* started by writing data to SDR[7:0] */
			gpCsi00TxAddress++;
			gCsi00TxCnt--;
			CSIMK00 = 0U;	/* enable INTCSI00 interrupt */
		}
	}

	return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
