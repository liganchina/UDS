/**
 * @file CAND.c
 * @brief CAN Driver: source code of CAN module for driver layer. 
 * @author Gianpiero Lenta - Bitron S.p.A. / Carmine Celozzi - Akhela S.r.l.
 * @date 23 may 2012 / 20 november 2014
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
| 18/02/15   2.1  CC      Inserted the routine CAND_GetBusWakeUp used, when the
|                         transceiver is in sleep, to check the wakeup CAN bus
|-----------------------------------------------------------------------------
| 01/04/15   2.2  DAF     Fix dlc bug: when received message with dlc greather
|                         than expected, only the dlc configured will be copied
|                         to can buffer
|-----------------------------------------------------------------------------
| 03/06/15   2.3  CC      Inserted new feature on CAN initialization procedure.
|                         The CAN init can be call during the application layer
|                         requests a send message. For this reason the init phase
|                         is protect by a CAN initialization status variable to
|                         avoid a send message with a controller in use.
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define CAND_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "CAND.h"

/* Module inhibition filter */
#ifdef __CAND_IS_PRESENT__

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/

/* CAN module information register */
typedef enum Cand_InfoStsReg_e
{
  CAND_INFO_NONE     = 0x00u, /* REC < 96 & TEC < 96   */
  CAND_INFO_REC_WARN = 0x01u, /* 96 >= REC <=127       */
  CAND_INFO_UNDEFREC = 0x02u, /* undefined             */
  CAND_INFO_EPBO_REC = 0x03u, /* REC >= 128            */
  CAND_INFO_TEC_WARN = 0x04u, /* 96 >= TEC <=127       */
  CAND_INFO_UNDEFTEC = 0x08u, /* undefined             */
  CAND_INFO_EPBO_TEC = 0x0cu, /* TEC >= 128            */
  CAND_INFO_BOFF     = 0x10u  /* Bus Off               */
}Cand_InfoStsReg_t;

/* structure definition for CAN Message Buffers registers */
typedef struct Cand_Mailbox_s
{
  volatile u08 mdata[8];  /* Addr. offset 00H-07H.   data field                                                                              */
  volatile u08 mdlc;      /* Addr. offset 08H.       data lenght control: used to set the number of bytes of the data field                  */
  volatile u08 mconf;     /* Addr. offset 09H.       used to specify the type (TX/RX) of the message buffer and to set a mask (msg ID filter)*/
  volatile u16 midl;      /* Addr. offset 0AH-0BH.   used to set a message identifier (ID) and standard/extended format mode                 */
  volatile u16 midh;      /* Addr. offset 0CH-0DH.                                                                                           */
  volatile u16 mctrl;     /* Addr. offset 0EH-0FH.   used to control the operation of the message buffer                                     */
}Cand_Mailbox_t;


/* TODO SGR - OK */
typedef struct Cand_TxNotifyFlag_s
{
  uint8_t Sending       :1;
  uint8_t Confirmation  :1;
  uint8_t Spare         :6;
}Cand_TxNotifyFlag_t;

/* TODO SGR - OK */
typedef struct Cand_RxNotifyFlag_s
{
  uint8_t Indication  :1;
  uint8_t Event       :1;
  uint8_t CorrectDlc  :1;
  uint8_t Spare       :5;
}Cand_RxNotifyFlag_t;


typedef union Cand_NetStatus_u
{
  struct Cand_NetStatus_s
  {
    u16 ErrorActive         :1;
    u16 Warning             :1;
    u16 ErrorPassive        :1;
    u16 BusOff              :1;
    u16 WireFailure         :1;
    u16 WakeUpState         :3;
    u16 Spare               :8;
  }bit;
  u16 word;
}Cand_NetStatus_t;



/*______ L O C A L - D A T A _________________________________________________*/

/* Mailbox buffer of the CAN controller */
#pragma dataseg = CAN_RAM
  static __no_init volatile Cand_Mailbox_t Cand_Mailbox[16];
#pragma dataseg = default

/* Indexes to scan the DBC messages */
static uint8_t Cand_StartScanTxMsg;
static uint8_t Cand_StopScanTxMsg;
static uint8_t Cand_StartScanRxMsg;
static uint8_t Cand_StopScanRxMsg;
static const CAND_MsgObject_t *CAND_TxMsgFramePtr;
static const CAND_MsgObject_t *CAND_RxMsgFramePtr;

/* Flags to manage the Rx and Tx message events */
static Cand_TxNotifyFlag_t Cand_TxNotifyFlag[CAND_TX_MSG_NMB];
static Cand_RxNotifyFlag_t Cand_RxNotifyFlag[CAND_RX_MSG_NMB];

/* Variables for CAN status */
static bool_t Cand_InitDone = FALSE;            /* CC - Not clear this init value */
static bool_t Cand_InitTransceiverDone = FALSE; /* CC - Not clear this init value */
static CAND_TransceiverOpState_t Cand_TransceiverOpState;

/* Variables for dignasosis management */
static uint8_t                   Cand_Cinfo;
static Cand_NetStatus_t          Cand_NetStatus;
static CAND_DiagType_t           Cand_DiagType;
static CAND_CanHwErrStatus_t     Cand_CanHwErrStatus;


/*______ P R I V A T E - D A T A _____________________________________________*/


#ifdef __CMMD_MULTI_DBC__
  static uint8_t CAND_MsmEcuType;
#endif


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

#define Cand_EnableModule()\
{\
  /* enable can driver module */\
  CGMCTRL = CAND_GCMCTRL_SET_GOM;\
}


#define Cand_DisableModule()\
{\
  /* Set GOM bit and ESFD bit always separately. */\
  CGMCTRL = CAND_GCMCTRL_SET_EFSD;\
  CGMCTRL = CAND_GCMCTRL_CLEAR_GOM;\
}



#define Cand_SetBaudRate(BaudRate)      (CBRP = (BaudRate))



/* CAN module Interrupt Enable: Rx, Tx, CAN module error state interrupt, Wakeup
     CIE0 enabled:   message frame successfully transmitted from message buffer m.
     CIE1 enabled:   valid message frame reception in message buffer m.
     CIE2 enabled:   CAN module error state interrupt:
                     generated when the transmission/reception error counter is at
                     the warning level, or in the error passive or bus-off state.
     CIE3 disabled:  CAN module protocol error interrupt:
                     generated when a stuff error, form error, ACK error, bit error, or CRC error occurs.
     CIE4 disabled:  CAN module arbitration loss interrupt.
     CIE5 enabled:   CAN module wakeup interrupt from CAN sleep mode:
                     generated when the CAN module is woken up from the CAN sleep mode because a falling edge is detected
                     at the CAN reception pin (CAN bus transition from recessive to dominant). */
#define Cand_InterruptEnable()\
{\
  C0RECMK = OFF;  /* CAN RX interrupt enable             */\
  C0TRXMK = OFF;  /* abilitazione interrupt trasmissione */\
  C0ERRMK = OFF;  /* abilitazione interrupt errore       */\
  C0WUPMK = OFF;  /* abilitazione interrupt wakeup       */\
  CIE = 0x2718u;  /* Enabled interrupt: TX, RX, CAN module error, CAN module Wakeup. */\
  C0WUPIF = 0U;   /* Wake Up interrupt flag azzerato */\
}


#define Cand_InterruptDisable(void)\
{\
  C0ERRMK = ON;     /* set all aFCAN interrupt mask flags */\
  C0WUPMK = ON;\
  C0RECMK = ON;\
  C0TRXMK = ON;\
  /* After an interrupt source has occurred, the corresponding */\
  /* interrupt status bit must be cleared to 0 by software. */\
  /* Operation necessary only if CINTS register is checked */\
  /* by application (polling mode). */\
  C0ERRIF = OFF;     /* clear all aFCAN interrupt request flags */\
  C0WUPIF = OFF;\
  C0RECIF = OFF;\
  C0TRXIF = OFF;\
}


#define Cand_SetIntptPrty()\
{\
  /* Set the CAN error interrupt to high level */\
  C0ERRPR0 = 0U;\
  C0ERRPR1 = 0U;\
  /* Set CAN wakeup interrupt to high level */\
  C0WUPPR0 = 0U;\
  C0WUPPR1 = 0U;\
  /* Set CAN receive interrupt to high level */\
  C0RECPR0 = 0U;\
  C0RECPR1 = 0U;\
  /* Set CAN transmit interrupt to high level */\
  C0TRXPR0 = 0U;\
  C0TRXPR1 = 0U;\
}



#define CAND_SET_ERROR_WARNING()\
{\
  Cand_NetStatus.bit.ErrorPassive = FALSE;\
  Cand_NetStatus.bit.ErrorActive = FALSE;\
  Cand_NetStatus.bit.Warning = TRUE;\
}

#define CAND_SET_ERROR_PASSIVE()\
{\
  Cand_NetStatus.bit.ErrorPassive = TRUE;\
  Cand_NetStatus.bit.ErrorActive = FALSE;\
  Cand_NetStatus.bit.Warning = FALSE;\
}

#define CAND_SET_ERROR_ACTIVE()\
{\
  Cand_NetStatus.bit.ErrorPassive = FALSE;\
  Cand_NetStatus.bit.ErrorActive = TRUE;\
  Cand_NetStatus.bit.Warning = FALSE;\
}

#define CAND_SET_BUS_OFF()\
{\
  Cand_NetStatus.bit.BusOff = TRUE;\
  Cand_NetStatus.bit.ErrorActive = FALSE;\
  Cand_NetStatus.bit.ErrorPassive = FALSE;\
  Cand_NetStatus.bit.Warning = FALSE;\
}


/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/


static void Cand_InitPtrToMsgFrame(void);
static void Cand_SetLimitToScan(void);
static void Cand_InitController(void);
static bool_t Cand_SleepController(void);
static void Cand_TjaStateSet(CAND_TransceiverOpState_t state);
static CAND_EvTx_t Cand_SendMsg(CAND_MailBoxHnd_t MsgHandle, uint8_t *Payload, 
                                uint8_t Dlc, uint32_t Id);
static uint16_t Cand_INTC0TRX_IsrCbk(void);
static uint16_t Cand_INTC0REC_IsrCbk(void);
static uint16_t Cand_INTC0ERR_IsrCbk(void);
static uint16_t Cand_INTC0WUP_IsrCbk(void);
static uint16_t Cand_INTPLR1_IsrCbk(void);


/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief General Init of CAN module
 *
 */
void CAND_Init(void)
{
  /* Set the CAN initialization status */
  Cand_InitDone = FALSE;
  
  /* Disable CAN interrupts */
  Cand_InterruptDisable(void)
  
  /* Set CAN EN and CAN_STB port in output mode and the latches to 1 */
  Cand_InitTransceiverDone = FALSE;
  Cand_TjaStateSet(CAND_TS_NORMAL);
  Cand_InitTransceiverDone = TRUE;

  /* Init the pointer to TX/RX message frame structure according to DBC number */
  Cand_InitPtrToMsgFrame();
  /* Compute the index for scan according to DBC number */
  Cand_SetLimitToScan();

  /* Init notify flag */
  memset(Cand_TxNotifyFlag, (int)0U, (sizeof(Cand_TxNotifyFlag_t)*CAND_TX_MSG_NMB));
  memset(Cand_RxNotifyFlag, (int)0U, (sizeof(Cand_RxNotifyFlag_t)*CAND_RX_MSG_NMB));
  
  /* Reset the diagnostic variables */
  CAND_InitDiagType();
  Cand_CanHwErrStatus = CAND_HW_NO_ERR;
  Cand_NetStatus.word = 0u;
  Cand_Cinfo = 0u;
  
  /* Set the callback for interrupt vector INTC0TRX */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTC0TRX, (ISRD_EvtCbk_t)Cand_INTC0TRX_IsrCbk);
  /* Set the callback for interrupt vector INTC0REC */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTC0REC, (ISRD_EvtCbk_t)Cand_INTC0REC_IsrCbk);
  /* Set the callback for interrupt vector INTC0ERR */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTC0ERR, (ISRD_EvtCbk_t)Cand_INTC0ERR_IsrCbk);
  /* Set the callback for interrupt vector INTC0WUP */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTC0WUP, (ISRD_EvtCbk_t)Cand_INTC0WUP_IsrCbk);
  /* Set the callback for interrupt vector INTPLR1 */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTPLR1, (ISRD_EvtCbk_t)Cand_INTPLR1_IsrCbk);

  /* Send the controller in sleep if come from boot */
  Cand_SleepController();

  /* Init CAN controller */
  Cand_InitController();
  
  /* Enable interrupt and Set its priority */
  Cand_SetIntptPrty()
  Cand_InterruptEnable()
  
  /* Set the CAN initialization status */
  Cand_InitDone = TRUE;
}

/**
 * @brief  Put can module in power off
 * @return None
 */
void CAND_PwrOff(void)
{
  /* Disable CAN interrupts */
  Cand_InterruptDisable(void)

  /* Switch off the controller. If this procedure fail,
     in any case must send in sleep the CAN transceiver */
  (void)Cand_SleepController();

  /* Send in sleep the transceiver TJA1055 */
  Cand_TjaStateSet(CAND_TS_GOTO_SL);
}

/**
 * @brief  Transmit a CAN message. 
 * If DLC passed is 0 the DLC is read by configuration table.
 * \n DO
 * \n [Check if bus off]
 * \n [Check if driver or passenger]
 * \n [Check if MsgHandle is coherent]
 * \n ...
 * \n OD
 * @param MsgHandle Handle of message to be transmitted
 * @return the result of transmission
 */
CAND_EvTx_t CAND_SendMsg(CAND_TxMsgName_t TxMsgName, uint8_t Dlc)
{
  uint8_t DlcVar;
  CAND_EvTx_t ret_val = CAND_EVT_TX_SUCCESS;
  const CAND_MsgObject_t *TxMsgFramePtr = &CAND_TxMsgObject[TxMsgName];

  /* Check on busoff state */
  if( Cand_NetStatus.bit.BusOff == FALSE )
  {
    if( (TxMsgName >= Cand_StartScanTxMsg) && (TxMsgName < Cand_StopScanTxMsg) )
    { 
      if( (TxMsgFramePtr->Dir == CAND_TX_CFG) || 
          (TxMsgFramePtr->Dir == CAND_DBG_CFG) )
      {
        /* Tipically used for applicative messages */
        if( Dlc == 0U )
        {
          DlcVar = TxMsgFramePtr->Dlc;
        }
        /* Tipically used for diagnostic messages */
        else
        {
          DlcVar = Dlc;
        }

        /* Call the Send Message routine of the Low Level Driver */
        ret_val = Cand_SendMsg(TxMsgFramePtr->MsgHandler, 
                               TxMsgFramePtr->FrameBuffer, 
                               DlcVar, TxMsgFramePtr->Id);
                               
        if( ret_val == CAND_EVT_TX_SUCCESS )
        {
          Cand_TxNotifyFlag[TxMsgName].Confirmation = FALSE;
          Cand_TxNotifyFlag[TxMsgName].Sending = TRUE;
        }
      }
      else
      {
        /* Notify the wrong direction */
        ret_val = CAND_EVT_WRONG_DIR;
      }
    }
    else
    {
      /* Notify the wrong paramater TxMsgName  */
      ret_val = CAND_EVT_WRONG_MSG;
    }
  }
  else
  {
    /* Notify the busoff error */
    ret_val = CAND_EVT_BUS_OFF;
  }

  return(ret_val);
}

/**
 * @brief  Public function for Manage CAN error (warning, active, passive)
 * @return no return value
 */
void CAND_ManageCANError(void)
{
  /* Read the Cinfo register */
  Cand_Cinfo = CINFO;
  
  /* resetto il flag che segnala lo stato di error passive */
  /* se il contatore di errori è andato a zero */
  if ((CERC == 0U))
  {
    CAND_SET_ERROR_ACTIVE()
  }
  else
  {
    Cand_Cinfo = CINFO;
    
    /* Test if CAN Controller is in Rx Error Passive OR in Tx Error Passive */
    if( ((Cand_Cinfo & CAND_INFO_EPBO_REC) == CAND_INFO_EPBO_REC) ||
        ((Cand_Cinfo & CAND_INFO_EPBO_TEC) == CAND_INFO_EPBO_TEC) )
    {
      CAND_SET_ERROR_PASSIVE()
    }
    /* Test if CAN Controller is in Rx Error Warning OR in Tx Error Warning */
    else if( ((Cand_Cinfo & CAND_INFO_REC_WARN) == CAND_INFO_REC_WARN) ||
             ((Cand_Cinfo & CAND_INFO_TEC_WARN) == CAND_INFO_TEC_WARN) )
    {
      CAND_SET_ERROR_WARNING()
    }
    else if (Cand_Cinfo == 0U)
    {
      CAND_SET_ERROR_ACTIVE()
    }
    else
    {
    }
  }
}




uint8_t CAND_GetStartScanTxMsg(void)
{
  return (Cand_StartScanTxMsg);
}

uint8_t CAND_GetStopScanTxMsg(void)
{
  return (Cand_StopScanTxMsg);
}

uint8_t CAND_GetStartScanRxMsg(void)
{
  return (Cand_StartScanRxMsg);
}

uint8_t CAND_GetStopScanRxMsg(void)
{
  return (Cand_StopScanRxMsg);
}


/**
 * @brief  Force the wire failure on CAN controller
 * @return void
 */
void CAND_SetWireFailureState(bool_t value)
{
  Cand_NetStatus.bit.WireFailure = value;
}

/**
 * @brief  Check the bus off state of CAN controller
 * @return TRUE if bus off occours.
 */
u08 CAND_GetBusOffState(void)
{
  return((u08)(Cand_NetStatus.bit.BusOff));
}

/**
 * @brief  Check the wire failure of CAN controller
 * @return TRUE if wire failure occours.
 */
u08 CAND_GetWireFailureState(void)
{
  return((u08)(Cand_NetStatus.bit.WireFailure));
}

/**
 * @brief  Check the Error Passive failure of CAN controller
 * @return TRUE if Error Passive failure occours.
 */
u08 CAND_GetErrorPassiveState(void)
{
  return((u08)(Cand_NetStatus.bit.ErrorPassive));
}

/**
 * @brief  Check the Error Active failure of CAN controller
 * @return TRUE if Error Active failure occours.
 */
u08 CAND_GetErrorActiveState(void)
{
  return((u08)(Cand_NetStatus.bit.ErrorActive));
}

/**
 * @brief  Check the Error Warning failure of CAN controller
 * @return TRUE if Error Warning failure occours.
 */
u08 CAND_GetErrorWarningeState(void)
{
  return((u08)(Cand_NetStatus.bit.Warning));
}

/**
 * @brief  Check the wake up condition of tranceiver
 * @return wake up condition of tranceiver
 */
CAND_WakeUpState_t CAND_GetWakeUpState(void)
{
  return((CAND_WakeUpState_t)Cand_NetStatus.bit.WakeUpState);
}

/**
 * @brief  Check the tranceiver operational state
 * @return tranceiver operational state
 */
CAND_TransceiverOpState_t CAND_GetTransceiverOpState(void)
{
  return(Cand_TransceiverOpState);
}

/**
 * @brief  Get the lenght of message received
 * @param  MsgHandle Handle of mailbox
 * @return the DLC of message received
 */
u08 CAND_GetMailBoxLen(CAND_RxMsgName_t TxMsgName)
{
  const CAND_MsgObject_t *RxMsgFramePtr = &CAND_RxMsgObject[TxMsgName];
  
  return(Cand_Mailbox[RxMsgFramePtr->MsgHandler].mdlc);
}

/**
 * @brief  Get the HW (network) status
 * @return HW status error type
 */
CAND_CanHwErrStatus_t CAND_NetworkGetHwErrStatus(void)
{
  return(Cand_CanHwErrStatus);
}

/**
 * @brief  Get Dlc Correct Flag
 * @
 */
bool_t CAND_GetDlcCorrectFlag(CAND_RxMsgName_t MsgIdx)
{ 
  return (Cand_RxNotifyFlag[MsgIdx].CorrectDlc);
}



bool_t CAND_CheckTxMsgRdy(CAND_TxMsgName_t MsgIdx)
{
  bool_t MsgSts = FALSE;
  
  if( Cand_TxNotifyFlag[MsgIdx].Confirmation == TRUE )
  {
    Cand_TxNotifyFlag[MsgIdx].Confirmation = FALSE;
    MsgSts = TRUE;
  }

  return (MsgSts);
}



bool_t CAND_CheckRxMsgRdy(CAND_RxMsgName_t MsgIdx)
{
  bool_t MsgSts = FALSE;
  
  if( Cand_RxNotifyFlag[MsgIdx].Indication == TRUE )
  {
    Cand_RxNotifyFlag[MsgIdx].Indication = FALSE;
    MsgSts = TRUE;
  }

  return (MsgSts);
}


bool_t CAND_CheckRxMsgEvt(CAND_RxMsgName_t MsgIdx)
{
  bool_t MsgSts = FALSE;
  
  if( Cand_RxNotifyFlag[MsgIdx].Event == TRUE )
  {
    Cand_RxNotifyFlag[MsgIdx].Event = FALSE;
    MsgSts = TRUE;
  }

  return (MsgSts);
}



void CAND_SetDiagType(CAND_DiagType_t DiagType)
{
  Cand_DiagType = DiagType;
}


/**
 * @brief  Public Get method returning diag type
 * @return diag type :phys or funct
 */
CAND_DiagType_t CAND_GetDiagType(void)
{
  return(Cand_DiagType);
}

/**
 * @brief  Public Set method initializing diag type
 */
void CAND_InitDiagType(void)
{
  Cand_DiagType = CAND_NO_DIAG_REQ;
}

#ifdef __CMMD_MULTI_DBC__
uint8_t CAND_GetMsmEcuType(void)
{
  return (CAND_MsmEcuType);
}
#endif

/**
 * @brief Read the level of CAN RxD pin to determine the bus status.
 * This check is possible only before of tranceiver initialization.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return uint8_t
 * @retval 0x00: bus is in sleep
 * @retval 0x01: bus is in wakeup
 * @retval 0x0FF: not possible check the bus
 */
uint8_t CAND_GetBusWakeUp(void)
{
  uint8_t CheckRes = 0xFFU;

  if( Cand_InitTransceiverDone == FALSE )
  {
    CAND_SetRxPortMode(CAND_DIR_INPUT);
    CheckRes = CAND_GetRxDataLevel();
  }
  
  return(CheckRes);
}


/*______ L O C A L - F U N C T I O N S _______________________________________*/


/* Init the pointer to TX/RX message frame structure according to DBC number */
static void Cand_InitPtrToMsgFrame(void)
{
#ifndef __CMMD_MULTI_DBC__
  /* Prepare the main pointers to Tx and Rx message structs */
  CAND_TxMsgFramePtr = &CAND_TxMsgObject[0];
  CAND_RxMsgFramePtr = &CAND_RxMsgObject[0];
#else
  /* Read the MSM Ecu type and coding it */ 
  /* Driver DBC = 1° DBC, Passenger DBC = 2° DBC */
  CAND_MsmEcuType = (uint8_t)LPMS_GetMsmEcuType();
  
  #if (CMMD_DBC_NMB == 2u)
    if( CAND_MsmEcuType == 0 )
    {
      CAND_TxMsgFramePtr = &CAND_TxMsgObject[0];
      CAND_RxMsgFramePtr = &CAND_RxMsgObject[0];
    }
    else if( CAND_MsmEcuType == 1 )
    {
      CAND_TxMsgFramePtr = &CAND_TxMsgObject[CAND_DBC1_TX_MSG_NMB];
      CAND_RxMsgFramePtr = &CAND_RxMsgObject[CAND_DBC1_RX_MSG_NMB];
    }
    else
    {
      /* ECU type don't exist */
    }
  #endif
  
  #if (CMMD_DBC_NMB == 3u)
    if( CAND_MsmEcuType == 0 )
    {
      CAND_TxMsgFramePtr = &CAND_TxMsgObject[0];
      CAND_RxMsgFramePtr = &CAND_RxMsgObject[0];
    }
    else if( CAND_MsmEcuType == 1 )
    {
      CAND_TxMsgFramePtr = &CAND_TxMsgObject[CAND_DBC1_TX_MSG_NMB];
      CAND_RxMsgFramePtr = &CAND_RxMsgObject[CAND_DBC1_RX_MSG_NMB];
    }
    else if( CAND_MsmEcuType == 2 )
    {
      CAND_TxMsgFramePtr = &CAND_TxMsgObject[CAND_DBC2_TX_MSG_NMB];
      CAND_RxMsgFramePtr = &CAND_RxMsgObject[CAND_DBC2_RX_MSG_NMB];
    }
    else
    {
      /* ECU type don't exist */
    }
  #endif
#endif
}



static void Cand_SetLimitToScan(void)
{
#ifndef __CMMD_MULTI_DBC__
  /* Tx section */
  Cand_StartScanTxMsg = 0U;
  Cand_StopScanTxMsg = CAND_TX_MSG_NMB;
  /* Rx section */
  Cand_StartScanRxMsg = 0U;
  Cand_StopScanRxMsg = CAND_RX_MSG_NMB;
  CAND_DbcMsgInit();
#else
  #if (CMMD_DBC_NMB == 2U)
    /* LPMS_MSM_ECU_DRIVER */
    if( CAND_MsmEcuType == 0 )
    {
      /* Tx section */
      Cand_StartScanTxMsg = 0U;
      Cand_StopScanTxMsg = CAND_DBC1_TX_MSG_NMB;
      /* Rx section */
      Cand_StartScanRxMsg = 0U;
      Cand_StopScanRxMsg = CAND_DBC1_RX_MSG_NMB;
      
      CAND_FirstDbcMsgInit();
    }
    /* LPMS_MSM_ECU_PASSENGER */
    else if( CAND_MsmEcuType == 1 )
    {
      /* Tx section */
      Cand_StartScanTxMsg = CAND_DBC1_TX_MSG_NMB;
      Cand_StopScanTxMsg = CAND_TX_MSG_NMB;
      /* Rx section */
      Cand_StartScanRxMsg = CAND_DBC1_RX_MSG_NMB;
      Cand_StopScanRxMsg = CAND_RX_MSG_NMB;
      
      CAND_SecondDbcMsgInit();
    }
    /* Future set for 2° row */
    else
    {
      /* Do nothing because value not correct */
    }
  #endif
  
  #if (CMMD_DBC_NMB == 3U)
    /* LPMS_MSM_ECU_DRIVER */
    if( CAND_MsmEcuType == 0 )
    {
      /* Tx section */
      Cand_StartScanTxMsg = 0;
      Cand_StopScanTxMsg = CAND_DBC1_TX_MSG_NMB;
      /* Rx section */
      Cand_StartScanRxMsg = 0;
      Cand_StopScanRxMsg = CAND_DBC1_RX_MSG_NMB;
      
      CAND_FirstDbcMsgInit();
    }
    /* LPMS_MSM_ECU_PASSENGER */
    else if( CAND_MsmEcuType == 1 )
    {
      /* Tx section */
      Cand_StartScanTxMsg = CAND_DBC1_TX_MSG_NMB;
      Cand_StopScanTxMsg = (CAND_DBC1_TX_MSG_NMB+CAND_DBC2_TX_MSG_NMB);
      /* Rx section */
      Cand_StartScanRxMsg = CAND_DBC1_RX_MSG_NMB;
      Cand_StopScanRxMsg = (CAND_DBC1_RX_MSG_NMB+CAND_DBC2_RX_MSG_NMB);
      
      CAND_SecondDbcMsgInit();
    }
    /* Future set for 2° row */
    else if( CAND_MsmEcuType == 2 )
    {
      /* Tx section */
      Cand_StartScanTxMsg = CAND_DBC2_TX_MSG_NMB;
      Cand_StopScanTxMsg = CAND_TX_MSG_NMB;
      /* Rx section */
      Cand_StartScanRxMsg = CAND_DBC2_RX_MSG_NMB;
      Cand_StopScanRxMsg = CAND_RX_MSG_NMB;
      
      CAND_ThirdDbcMsgInit();
    }
    else
    {
      /* Do nothing because value not correct */
    }
  #endif
#endif /* end __CMMD_MULTI_DBC__ */
}




/**
 * @brief  CAN controller settings configuration
 */
static void Cand_InitController(void)
{
  uint8_t waitINIT, i, NumMsg;
  const CAND_MsgObject_t *TxMsgFramePtr = CAND_TxMsgFramePtr;
  const CAND_MsgObject_t *RxMsgFramePtr = CAND_RxMsgFramePtr;

  /* Set CAN Tx port latch to HIGH (recessive level) */
  CAND_SetTxSts(TRUE);
  /* Input mode*/
  CAND_SetTxPortMode(CAND_DIR_INPUT);           
  /* Control of CAN controller operating clock: Supplies operating clock. */
  CANMCKE = 1U;
  /* Clear OPMODE     p.921 CCERC  = 1: the CERC and CINFO registers are cleared in the initialization mode */
  CCTRL = 0x807FU;

  /*  wait transition to INIT mode.  tm340 */
  waitINIT = WAIT_INIT;
  waitINIT--;
  while (((CCTRL & 0x0007U) != 0U) && (waitINIT != 0U))
  {
    waitINIT--;
  }

  /* Determine the CAN module system clock: fCANMOD = fCAN = 8MHz. */
  CGMCS = 0x00U;
  /* Enable can driver module */
  CGMCTRL = CAND_GCMCTRL_SET_GOM;
  /* Set baud rate */
  Cand_SetBaudRate(CAND_BAUD_125K);

 /*
    Length of Prop Segment = 9TQ
    Length of Phase Segment 1 = 3TQ
    Length of time segment 1: Prop Segment + Phase Segment 1 = 12TQ

    Length of time segment 2: Phase Segment 2 = 3TQ
    Length of Synchronization jump width: SJW = 3TQ

    Sampling point: 81,25%
    num samples 1
 */
  CBTR = 0x220BU;

  /* Init mask */
  CMASK1L = 0x0000U;
  CMASK1H = 0x0000U;
  CMASK2L = 0x0000U;
  CMASK2H = 0x0000U;
  CMASK3L = 0x0000U;
  CMASK3H = 0x0000U;
  CMASK4L = 0x0000U;
  CMASK4H = 0x0000U;

  /* Clear all mailbox */
  for(i = 0U; i < 16U; i++)
  {
    /* set CMCONFn register: clear MA0 bit (Message buffer not Assigned)
        Cand_Mailbox[AFCAN_BUFFER_UNUSED_0].mconf = 0x00U */
    Cand_Mailbox[i].mconf = 0x00U;
    
    /*  set CMCTRLn register:
        clear MOW (clean Message buffer OverWrite status bit)                            0x0010U
        clear IE (message completion interrupt disabled)                                 0x0008U
        clear DN (clean Data New status bit)                                             0x0004U
        clear TRQ (abort TX)                                                             0x0002U
        clear RDY (the message buffer can be written by software.
                  The CAN module cannot write to the message buffer.)                   0x0001U  */
    Cand_Mailbox[i].mctrl = 0x001FU;
  }

  /*Initialization of message buffer:
  After the CAN module is enabled, the message buffers contain undefined values.
  A minimum initialization for all the message buffers, even for those not used in the application, is necessary
  before switching the CAN module from the initialization mode to one of the operation modes. */
  
  /* Init buffers for Tx Messages */
  for(NumMsg = Cand_StartScanTxMsg; NumMsg < Cand_StopScanTxMsg; NumMsg++)
  {
    i = TxMsgFramePtr->MsgHandler;
    
    switch(TxMsgFramePtr->Dir)
    {
      case CAND_TX_CFG:
        /* set CMCONFn register :   MT_TX: Msg buffer Type TX, MA0: Msg buffer Assigned */
        Cand_Mailbox[i].mconf = MT_TX|MA0;
        /* set CMIDLn register: Set IDE = 0 ed ID */
        Cand_Mailbox[i].midl = (u16)(TxMsgFramePtr->Id);
        /* set CMIDHn register: init msb ID and select 29 bits ID */
        Cand_Mailbox[i].midh = (u16)(TxMsgFramePtr->Id >> 16U);
        /* set CMxDLCn register */
        Cand_Mailbox[i].mdlc = TxMsgFramePtr->Dlc;
        /* set IE (normal message transmission completion interrupt enabled)                0x0800U
           clear MOW (clean Message buffer OverWrite status bit)                            0x0010U
           clear DN (clean Data New status bit)                                             0x0004U
           clear TRQ (abort TX)                                                             0x0002U
           clear RDY (Message Buffer Ready Bit)                                             0x0001U
           The message buffer can only be written by software: not ready for transmission. tm519
           The CAN module cannot access (nor write nor transmit) to the message buffer.           */
        Cand_Mailbox[i].mctrl = 0x0817U;
        break;

      case CAND_DBG_CFG:
        Cand_Mailbox[i].mconf = MA0;
        Cand_Mailbox[i].midl  = (u16)(TxMsgFramePtr->Id);
        Cand_Mailbox[i].midh  = (u16)(TxMsgFramePtr->Id >> 16U);
        Cand_Mailbox[i].mdlc  = TxMsgFramePtr->Dlc;
        Cand_Mailbox[i].mctrl = 0x0817U;
        break;

      case CAND_UNUSED_CFG:
      default:
        /* set CMCONFn register: clear MA0 bit (Message buffer not Assigned)
           Cand_Mailbox[AFCAN_BUFFER_UNUSED_0].mconf = 0x00U */
        Cand_Mailbox[i].mconf = 0x00U;

        /* set CMCTRLn register:
         clear MOW (clean Message buffer OverWrite status bit)                            0x0010U
         clear IE (message completion interrupt disabled)                                 0x0008U
         clear DN (clean Data New status bit)                                             0x0004U
         clear TRQ (abort TX)                                                             0x0002U
         clear RDY (the message buffer can be written by software.
                    The CAN module cannot write to the message buffer.)                   0x0001U  */
        Cand_Mailbox[i].mctrl = 0x001FU;
        break;
    }
    
    TxMsgFramePtr++;
  }
  
  /* Init buffers for Rx Messages */
  for(NumMsg = Cand_StartScanRxMsg; NumMsg < Cand_StopScanRxMsg; NumMsg++)
  {
    i = RxMsgFramePtr->MsgHandler;
    
    switch(RxMsgFramePtr->Dir)
    {
      case CAND_RX_CFG:
        /* set CMCONFn register : OWS: OverWrite Stored msg, MT_RX: Msg buffer Type RX, MA0: Msg buffer Assigned */

        Cand_Mailbox[i].mconf = OWS|MT_RX|MA0;
        /* set CMIDLn register: init lsb ID(29 bit) */
        Cand_Mailbox[i].midl  = (u16)(RxMsgFramePtr->Id);
        /* set CMIDHn register: init msb ID and select 29 bit ID */
        Cand_Mailbox[i].midh  =  (u16)(RxMsgFramePtr->Id >> 16U);
        /* set CMCTRLn register:
           set IE (valid message reception completion interrupt enabled)                                    0x0800U
           set RDY (Message Buffer Ready Bit)                                                               0x0100U
            (ready for reception: only
                  Writing the message buffer by SW is ignored except write to RDY, TRQ, DN and MOW bits).
                  Only the CAN module can write to the message buffer.
           clear MOW (clean Message buffer OverWrite status bit)                                            0x0010U
           clear DN (clean Data New status bit)                                                             0x0004U
           clear TRQ (abort TX)                                                                             0x0002U */
        Cand_Mailbox[i].mctrl        = 0x0916U;
      break;

      case CAND_DBG_CFG:
        Cand_Mailbox[i].mconf = MA0;
        Cand_Mailbox[i].midl  = (u16)(RxMsgFramePtr->Id);
        Cand_Mailbox[i].midh  = (u16)(RxMsgFramePtr->Id >> 16U);
        Cand_Mailbox[i].mdlc  = RxMsgFramePtr->Dlc;
        Cand_Mailbox[i].mctrl = 0x0817U;
        break;

      case CAND_UNUSED_CFG:
      default:
        /* set CMCONFn register: clear MA0 bit (Message buffer not Assigned)
           Cand_Mailbox[AFCAN_BUFFER_UNUSED_0].mconf = 0x00U */
        Cand_Mailbox[i].mconf = 0x00U;

        /* set CMCTRLn register:
         clear MOW (clean Message buffer OverWrite status bit)                            0x0010U
         clear IE (message completion interrupt disabled)                                 0x0008U
         clear DN (clean Data New status bit)                                             0x0004U
         clear TRQ (abort TX)                                                             0x0002U
         clear RDY (the message buffer can be written by software.
                    The CAN module cannot write to the message buffer.)                   0x0001U  */
        Cand_Mailbox[i].mctrl = 0x001FU;
        break;
    }
    
    RxMsgFramePtr++;
  }

  /* Set CTxD port mode to output */
  CAND_SetTxPortMode(CAND_DIR_OUTPUT);

  /* OPMODE = 1: switch the CAN module from initialization mode to normal operation mode. */
  /* CCERC  = 1: reset the CERC and CINFO registers. */
  /* AL = 0 : valid only in single-shot mode */
  CCTRL = 0x817EU;          /*  Set OPMODE */
}

/**
 * @brief  Put can module in sleep
 * @return FALSE if sleep ok, return TRUE if not
 */
static bool_t Cand_SleepController(void)
{
  bool_t retcod = TRUE;
  uint8_t i = 0u;

  while( ((CGMCTRL & 0x8000u) != 0x0000u) && (i < 200u) )
  {
    /* Periferica CAN in sleep mode: */
    CCTRL = 0x0810u;   /* PSMODE = 01b (b4..3) */
    i++;
  }

  if( (CGMCTRL & 0x8000u) == 0x0000u )
  {
    retcod = FALSE;
  }
  else
  {
    retcod = TRUE;
  }

  return(retcod);
}

/**
 * @brief CAN transceiver (TJA1055) state settings
 * @param state Tranceiver operational State
 *
 */
static void Cand_TjaStateSet(CAND_TransceiverOpState_t state)
{
  u08 wait50us;
  u08 rxDataLevel;

  Cand_NetStatus.bit.WakeUpState = CAND_WUP_NONE;
  Cand_TransceiverOpState = CAND_TS_PON;

  if (state == CAND_TS_NORMAL)
  {
    CAND_SetStandbySts(0u);
    CAND_SetEnableSts(0u);

    wait50us = 100u;

    while(wait50us > 0u)
    {
      NOP();
      wait50us--;
    }
    
    rxDataLevel = CAND_GetRxDataLevel();

    if((CAND_GetNerrSts() == 0U) && (rxDataLevel == 0U))
    {
      CAND_SetStandbySts(1u);

      wait50us = 100u;

      while(wait50us > 0u)
      {
        NOP();
        wait50us--;
      }

      if(CAND_GetNerrSts() == 0U)
      {
        Cand_NetStatus.bit.WakeUpState = CAND_WUP_1;
      }
      else
      {
        Cand_NetStatus.bit.WakeUpState = CAND_WUP_2;
      }
    }
    else
    {
      CAND_SetStandbySts(1u);

      wait50us = 100u;

      while(wait50us > 0u)
      {
        NOP();
        wait50us--;
      }

      if(CAND_GetNerrSts() == 0U)
      {
        Cand_NetStatus.bit.WakeUpState = CAND_WUP_3;
      }
      else
      {
        Cand_NetStatus.bit.WakeUpState = CAND_WUP_4;
      }
    }

    CAND_SetStandbySts(1u);
    CAND_SetEnableSts(1u);

    Cand_TransceiverOpState = state;
  }
  else if (state == CAND_TS_GOTO_SL)
  {
    CAND_SetStandbySts(0u);
    CAND_SetEnableSts(1u);

    wait50us = 100u;

    while(wait50us > 0u)
    {
      NOP();
      wait50us--;
    }

    CAND_SetStandbySts(0u);
    CAND_SetEnableSts(0u);

    Cand_TransceiverOpState = state;
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : Cand_SendMsg                                                         */
/*Role :                                                                      */
/*Interface : IN: MsgHandle = Handle of message to be transmitted             */
/*                data      = pointer to transmission  buffer                 */
/*                nb        = number of bytes to be transmitted               */
/*            OUT: tx success or not                                          */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    IF[frame buffer free]                                                   */
/*      [TX frame]                                                            */
/*    ELSE                                                                    */
/*       RETURN ERROR                                                         */
/*    FI                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static CAND_EvTx_t Cand_SendMsg(CAND_MailBoxHnd_t MsgHandle, uint8_t *Payload, 
                                uint8_t Dlc, uint32_t Id)
{
  uint8_t waitReady = WAIT_RDY;
  CAND_EvTx_t ret_val;

  
  if( Cand_InitDone == TRUE )
  {
    /* check frame buffer free: no message pending */
    if ((Cand_Mailbox[MsgHandle].mctrl & CAND_READ_TRQ) == 0U)
    {
      /* Wait RDY bit is cleared */
      do
      {
        /* Clear RDY bit */
        Cand_Mailbox[MsgHandle].mctrl = CAND_CLEAR_RDY;
        waitReady--;
      }while (((Cand_Mailbox[MsgHandle].mctrl & CAND_READ_RDY) != 0U) && (waitReady != 0U));

      /* CC - According to Hw datasheet v06.00 to pp. 950: */
      /* Cautions 1. Do not clear the RDY bit (0) during message transmission.
         Follow the transmission abort process about clearing the RDY bit (0) for
         redefinition of the message buffer.
         2. Clear again when RDY bit is not cleared even if this bit is cleared.
         3. Be sure that RDY is cleared before writing to the message buffer registers.
         Perform this confirmation by reading back the RDY bit. However, setting the
         TRQ bit, clearing the DN bit, setting the RDY bit or clearing the MOW bit of the
         CMCTRLm register need not be confirmed.
      */
      /* For this reason the manipulation of the mailbox must be done only if RDY bit is clear
         and then with protection timeout didn't elapse */
      if( waitReady > 0U )
      {
        /* Update the mailbox with data to transmit */
        /* set CMIDLn register: Set IDE = 0 ed ID */
        Cand_Mailbox[MsgHandle].midl = (u16)Id;
        /* set CMIDHn register: init msb ID and select 29 bits ID */
        Cand_Mailbox[MsgHandle].midh = (u16)(Id >> 16U);
        Cand_Mailbox[MsgHandle].mdlc = Dlc;
        memcpy((void *)Cand_Mailbox[MsgHandle].mdata, (void *)Payload, (u16)Dlc);
        Cand_Mailbox[MsgHandle].mctrl = CAND_SET_RDY;        /* Set RDY bit */
        Cand_Mailbox[MsgHandle].mctrl = CAND_SET_TRQ;        /* Set TRQ bit */
    
        /* Notify the correct sending */
        ret_val = CAND_EVT_TX_SUCCESS;
      }
      else
      {
        /* Notify the frame buffer holding transmission */
        ret_val = CAND_EVT_FRAMEBUS_BUSY;
      }
    }
    else
    {
      /*  Notify the frame buffer holding transmission */
      ret_val = CAND_EVT_FRAMEBUS_BUSY;
    }
  }
  
  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : isrCanTX                                                             */
/*Role : CAN transmission completion interrupt                                */
/*       Message frame successfully transmitted from message buffer m         */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static uint16_t Cand_INTC0TRX_IsrCbk(void)
{
  CAND_MailBoxHnd_t Index;
  uint8_t TxMsgName;

  /* CLOPT: CAN module Last Out-Pointer register
     The CLOPT register indicates the number of the message buffer
     to which a data frame or a remote frame was transmitted last. */
  Index = (CAND_MailBoxHnd_t)CLOPT;
  
  if(Index < CAND_MAILBOX_NMB)
  {
    /* Confirmation notify management */
    for(TxMsgName = Cand_StartScanTxMsg; TxMsgName < Cand_StopScanTxMsg; TxMsgName++)
    {
      if( Cand_TxNotifyFlag[TxMsgName].Sending == TRUE )
      {
        Cand_TxNotifyFlag[TxMsgName].Sending = FALSE;
        Cand_TxNotifyFlag[TxMsgName].Confirmation = TRUE;
        break;
      }
    }
  }

  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0TRX));
}

/*----------------------------------------------------------------------------*/
/*Name : isrCanReceive                                                        */
/*Role :CAN receipt completion interrupt                                      */
/*       Valid message frame reception in message buffer m.                   */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static uint16_t Cand_INTC0REC_IsrCbk(void)
{
  CAND_MailBoxHnd_t Index;
  uint8_t TableIdx;
  uint8_t TableOffsetIdx;
  const CAND_MsgObject_t *RxMsgFramePtr = CAND_RxMsgFramePtr;

  /* CLIPT: CAN module Last In-Pointer register */
  Index = (CAND_MailBoxHnd_t)CLIPT;
  if( Index < CAND_MAILBOX_NMB )
  {
    Cand_Mailbox[Index].mctrl = 0x0004u;   /* Clear DN */

    /* Compute the Table Index according to mailbox index */
    TableOffsetIdx = (Index - RxMsgFramePtr->MsgHandler);
    
    /* Pointer allignment to right position of the configuration table */
    RxMsgFramePtr += TableOffsetIdx;

    /* Allign the table index to use the notify flags */
    TableIdx = Cand_StartScanRxMsg + TableOffsetIdx;

    /* Set the event flag */
    Cand_RxNotifyFlag[TableIdx].Event = TRUE;
    
    if (Cand_Mailbox[Index].mdlc >= RxMsgFramePtr->Dlc)
    {
      if(RxMsgFramePtr->Dlc == 0U) //DF: 01/04/2015 dlc buffer overflow correction
      {
        /* variable lenght DLC */
        memcpy( RxMsgFramePtr->FrameBuffer, (void *)Cand_Mailbox[Index].mdata, (u16)(Cand_Mailbox[Index].mdlc));
      }
      else
      {
        /* fixed lenght DLC */
        memcpy( RxMsgFramePtr->FrameBuffer, (void *)Cand_Mailbox[Index].mdata, (u16)(RxMsgFramePtr->Dlc));
      }
      
      /* set indication flag */
      Cand_RxNotifyFlag[TableIdx].Indication = TRUE;
      Cand_RxNotifyFlag[TableIdx].CorrectDlc = TRUE;
    }
    else
    {
      /* Clear all notify flag */
      Cand_RxNotifyFlag[TableIdx].Event = FALSE;
      Cand_RxNotifyFlag[TableIdx].Indication = FALSE;
      Cand_RxNotifyFlag[TableIdx].CorrectDlc = FALSE;
    }
  }
  else
  {
  }

  /* If interrupt INTC0REC occour the CAN controller isin't in error */
  if(Cand_CanHwErrStatus != CAND_HW_NO_ERR)
  {
    CLEC = 0x00U;
    Cand_CanHwErrStatus = CAND_HW_NO_ERR;
  }
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0REC));
}

/*----------------------------------------------------------------------------*/
/*Name : isrCanError                                                          */
/*Role : CAN error interrupt                                                  */
/*      This interrupt is generated when the transmission/reception error     */
/*      counter is at the warning level, or in the error passive or           */
/*      bus-off state.                                                        */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static uint16_t Cand_INTC0ERR_IsrCbk(void)
{
  if((CINTS & CAND_INTS_ERSTS) == CAND_INTS_ERSTS)    // CAN error status interrupt pending?
  {
    Cand_CanHwErrStatus = (CAND_CanHwErrStatus_t)CLEC;
    if((CINFO & CAND_INFO_BOFF) == CAND_INFO_BOFF)    // Test if CAN Controller is in BusOff
    {
      if(Cand_NetStatus.bit.BusOff == FALSE)
      {
        CAND_SET_BUS_OFF()
      }
      else
      {
      }
    }
    else
    {
      Cand_NetStatus.bit.BusOff = FALSE;
    }
    Cand_CanHwErrStatus = (CAND_CanHwErrStatus_t)CLEC;
    CINTS |= CAND_INTS_ERSTS;           // RESET CAN error status interrupt pending
  }

  if((CINTS & CAND_INTS_PRERR) == CAND_INTS_PRERR)    // CAN protocol error interrupt pending?
  {
    Cand_CanHwErrStatus = (CAND_CanHwErrStatus_t)CLEC;
    CINTS |= CAND_INTS_PRERR;           // RESET CAN protocol error interrupt pending
  }

  if((CINTS & CAND_INTS_ARBLOS) == CAND_INTS_ARBLOS)    // Arbitration loss interrupt pending?
  {
    Cand_CanHwErrStatus = (CAND_CanHwErrStatus_t)CLEC;
    CINTS |= CAND_INTS_ARBLOS;           // RESET Arbitration loss interrupt pending
  }
  else
  {
  }

  CLEC = 0x00u;
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0ERR));
}

/*----------------------------------------------------------------------------*/
/*Name : isrCanWakeUp                                                         */
/*Role :CAN error interrupt                                                   */
/*      This interrupt is generated when the CAN module is woken up from      */
/*      the CAN sleep mode because a falling edge is detected at the CAN      */
/*      reception pin (CAN bus transition from recessive to dominant).        */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static uint16_t Cand_INTC0WUP_IsrCbk(void)
{
  NOP();
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTC0WUP));
}

/*----------------------------------------------------------------------------*/
/*Name : isrCan_RxPin                                                         */
/*Role : da rivedere !!!!!!                                                   */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static uint16_t Cand_INTPLR1_IsrCbk(void)
{  
  NOP();
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPLR1));
}


#endif /* end __CAND_IS_PRESENT__ */

/*______ E N D _____ (CAND.c) ________________________________________________*/
