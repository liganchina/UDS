/**
 * @file CAND.h
 * @brief CAN Driver: private interface of CAN module for driver layer. 
 * @author Gianpiero Lenta - Bitron S.p.A. / Carmine Celozzi - Akhela S.r.l.
 * @date 28 august 2014 / 20 november 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 23/05/12   0.1  GIL     First derivative from Tesla (125K)
|-----------------------------------------------------------------------------
| 18/09/12   0.2  GIL     Second draft: UDS integration
|-----------------------------------------------------------------------------
| 28/09/12   0.3  GIL     Third draft: added confirmation function, indication
|                         function and timeout function
|-----------------------------------------------------------------------------
| 12/04/13   0.4  GIL     Completely driver rewrite
|-----------------------------------------------------------------------------
| 25/06/13   0.5  GIL     Creato layer NETP(timeout monitor)
|-----------------------------------------------------------------------------
| 01/11/13   0.6  GIL     Can Wire failure management (fixing transceiver driver)
|-----------------------------------------------------------------------------
| 08/11/13   0.7  GIL     Finish node Mute and Bus off
|-----------------------------------------------------------------------------
| 06/10/14   1.0  CC      Porting first release to new architecture for TESLA
|                         project
|-----------------------------------------------------------------------------
| 20/10/14   1.1  CC      Inserted some bug fixing and module optimization
|-----------------------------------------------------------------------------
| 20/11/14   2.0  CC      Platform official release (complete redesign)
|-----------------------------------------------------------------------------
*/

#ifndef __CAND_H
#define __CAND_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "DRVD_if.h"

/* Module inhibition filter */
#ifdef __CAND_IS_PRESENT__

#include "CAND_config.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define WAIT_RDY    30U   /* number of maximum clear RDY bit retry, before proceed with CAN msg. buffer write. tm340, tm500 */
#define WAIT_INIT   60U   /* number of maximum read OPMODE bits to verify INIT mode active, before proceed with CAN module initialization. tm340 */

/* mconf (message configuration register CMCONFn)*/
#define OWS     0x80U     /* OWS: Over Write Stored (RX type message buffer option) */
#define RTR     0x40U     /* RTR: Remote Transmit Request (TX message type modifier) */
/* MT0..2: Message buffer Type setting. Transmit/Receive with no mask/Receive with mask set */
#define MT_TX   0x00U     /* Message buffer Type is Transmit */
#define MT_RX   0x08U     /* Message buffer Type is Receive with no mask setting */
#define MA0     0x01U     /* Message buffer Assignment (used) */

/* CMCTRLm Can message control register */
#define CAND_READ_RDY    0x0001U
#define CAND_CLEAR_RDY   0x0001U
#define CAND_SET_RDY     0x0100U

#define CAND_READ_TRQ    0x0002U
#define CAND_CLEAR_TRQ   0x0002U
#define CAND_SET_TRQ     0x0200U

#define CAND_DN   0x0004U
#define CAND_IE   0x0008U
#define CAND_MOW  0x0010U

/* GCMCTRL Can global module control register */
#define CAND_GCMCTRL_SET_GOM    0x0100U
#define CAND_GCMCTRL_CLEAR_GOM  0x0001U
#define CAND_GCMCTRL_SET_EFSD   0x0200U


/*______ G L O B A L - T Y P E S _____________________________________________*/

/* TODO SGR - OK */
/* mailbox transmission/reception configuration */
typedef enum
{
  CAND_TX_CFG = 0,
  CAND_RX_CFG,
  CAND_RX_MASKED1_CFG,
  CAND_RX_MASKED2_CFG,
  CAND_RX_MASKED3_CFG,
  CAND_RX_MASKED4_CFG,
  CAND_DBG_CFG,
  CAND_UNUSED_CFG
}CAND_Dir_t;

/* TODO SGR - OK */
/* CAN module interrupt status register */
typedef enum
{
  CAND_INTS_NONE   = 0x00u,
  CAND_INTS_NORM1  = 0x01u, /* tx normal completion       */
  CAND_INTS_NORM2  = 0x02u, /* rx valid message           */
  CAND_INTS_ERSTS  = 0x04u, /* error status interrupt     */
  CAND_INTS_PRERR  = 0x08u, /* protocol error interrupt   */
  CAND_INTS_ARBLOS = 0x10u, /* arbitration lost interrupt */
  CAND_INTS_WAKEUP = 0x20u  /* wake up interrupt          */
}CAND_IntStsReg_t;


/* TODO SGR - OK */
/* CAN message channel descriptor */
typedef struct
{
  CAND_MailBoxHnd_t  MsgHandler;       /* specify message handler */
  u08                Dlc;
  u32                Id;
  CAND_Dir_t         Dir;
  u08*               FrameBuffer;
}CAND_MsgObject_t;


/*______ G L O B A L - D A T A _______________________________________________*/

extern const CAND_MsgObject_t CAND_TxMsgObject[CAND_TX_MSG_NMB];
extern const CAND_MsgObject_t CAND_RxMsgObject[CAND_RX_MSG_NMB];

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/


#ifndef __CMMD_MULTI_DBC__
void CAND_DbcMsgInit(void);
#else
/* TODO SGR - OK */
void CAND_FirstDbcMsgInit(void);
/* TODO SGR - OK */
void CAND_SecondDbcMsgInit(void);
#endif


#endif /* end __CAND_IS_PRESENT__ */

#endif /* end __CAND_H */

/*_____ E N D _____ (CAND.h) _________________________________________________*/
