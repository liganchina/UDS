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
* Filename:	FE78K0R_CG_int_user.c
* Abstract:	This file implements device driver for INT module.
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
#include "FE78K0R_CG_int.h"
#include "FE78K0R_CG_int_user.h"

#include "PWMC_cbk.h"

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/

static uint16_t Intd_INTP0_Isr(void);

/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/**
 * @brief Initialization routine for the external interrupt driver module
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void INTD_Init(void)
{
  /* INTP0 - External interrupt 0 callback */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTP0, (ISRD_EvtCbk_t)Intd_INTP0_Isr);
 }


/*_____ L O C A L - F U N C T I O N S ________________________________________*/

/**
 * @brief ISR callback for INTP0_vect interrupt.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return uint16_t
 * @retval ISR callback check value computed by ISRD_ComputeCbkCheck with by
 * parameter ISRD_VECTOR_INTP0
 */
static uint16_t Intd_INTP0_Isr(void)
{
  /* Call external interrupt INTP0_vect callback */
  INTD_IsrCbkINTP0()

  /* Compute and return the key by interrupt vector index */
  return( ISRD_ComputeCbkCheck(ISRD_VECTOR_INTP0) );
}


/**
 * @brief This fuction enables the interrut request and the
 * related callback of the channel passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return None
 */
void INTD_EnableIsr(INTD_Channel_t chan)
{
  if (chan == INTD_CHAN_0)
  {
    INTP0_Enable();
  }
  else
  {
  }
}

/**
 * @brief This fuction disables the interrut request and the
 * related callback of the channel passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return None
 */
void INTD_DisableIsr(INTD_Channel_t chan)
{
  if (chan == INTD_CHAN_0)
  {
    INTP0_Disable();
  }
  else
  {
  }
}

/**
 * @brief This fuction return the electrical level of requested channel
 * passed as parameter.
 * @author Mastrodonato Matteo - Bitron S.p.A.
 * @param [in] chan The INTD channel
 * @param [out] None
 * @return electrical level
 * @retval 0
 * @retval 1
 */
u08 INTD_GetLevel(INTD_Channel_t chan)
{
  u08 valueReturn;

  if (chan == INTD_CHAN_0)
  {
    valueReturn = P12_bit.no0;
  }
  else
  {
  }

  return valueReturn;
}

/*_____ E N D _____ (FG78K0R_CG_int_user.c) __________________________________*/
