/**
 * @file UARTD.c
 * @brief UART Driver: source code of UART module for driver layer. 
 * @version 0.3
 * @author Giuseppe Colucci - EMA S.r.l.
 * @date 25 September 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GCO          Giuseppe Colucci          Ema S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 08/05/2015 0.1  GCO     First draft
|-----------------------------------------------------------------------------
| 05/06/2015 0.2  GCO     Complete driver for management of one channel at a 
|                         time
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
|-----------------------------------------------------------------------------
*/


#define UARTD_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UARTD.h"
#include "UARTD_if.h"
#include "UARTD_config.h"

/* Module inhibition filter */
#ifdef __UARTD_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/* Setting for Channel 0 functionality */
#ifdef  __UARTD_CHN_HND_0__

/* Enable register masks */
/* These are the bit-masks of the register used to supply the clock to the module */
const uint8_t per0UartEnMasks_au8 = 0x20;

/* Define LIN pin used */
#define UARTD_CHN_PIN           P1_bit.no4

/* Pointers to interrupt flag registers of lin-uart channels */
/* Register in which interrupt flags are stored */
uint8_t * const reg_if_apu8[INT_MAX_NUM] =
{
  (uint8_t *) &IF0H,
  (uint8_t *) &IF1L,
  (uint8_t *) &IF1L,
  (uint8_t *) &IF1L
};

/* Pointers to interrupt mask registers of lin-uart channels */
/* Register in which interrupt masks are stored */
uint8_t * const reg_mk_apu8[INT_MAX_NUM] =
{
  (uint8_t *) &MK0H,
  (uint8_t *) &MK1L,
  (uint8_t *) &MK1L,
  (uint8_t *) &MK1L
};

/* Bit mask for interrupt flag and mask registers */
const uint8_t int_bit_mask_au8[INT_MAX_NUM] =
{
  0x80,
  0x01,
  0x02,
  0x04
};

/* Pointers to external interrupt mask registers of lin-uart channels */
/* Register in which external interrupt edge detector are stored */
uint8_t * const reg_ed_apu8[INT_EXT_MAX_NUM] =
{
  (uint8_t *) &EGP0,
  (uint8_t *) &EGN0
};

/* Bit mask for external interrupt mask registers */
const uint8_t int_ext_bit_mask_au8[INT_EXT_MAX_NUM] =
{
  0x04,
  0x04
};

/* Pointers to priority interrupt flag registers of lin-uart channels */
/* Register in which priority interrupt flags are stored */
uint8_t * const reg_pr_apu8[INT_PRIORITY_MAX_NUM] =
{
  (uint8_t *) &PR10H,
  (uint8_t *) &PR00H,
  (uint8_t *) &PR11L,
  (uint8_t *) &PR01L,
  (uint8_t *) &PR11L,
  (uint8_t *) &PR01L,  
  (uint8_t *) &PR11L,
  (uint8_t *) &PR01L,
};

/* Bit mask for external interrupt mask registers */
const uint8_t int_pri_bit_mask_au8[INT_PRIORITY_MAX_NUM] =
{
  0x80,
  0x80,
  0x04,
  0x04,
  0x02,
  0x02,
  0x01,
  0x01,
};

/* Uart modules */
static Uartd_mod_t uart_mod =
{
  (Uartd_hw_reg_t *)(LIN_UART_CTL_MEM_0), 
  (uint8_t *)(LIN_UART_TX_W_REG_MEM_0),
  (uint8_t *)(LIN_UART_RX_REG_MEM_0),
  { 0 },
  { 0 },
  0,
  0,
  0,
  0,
  UARTD_SLEEP,
  UARTD_NO_ERROR,
  UARTD_RX_DATA_CBK
};

#endif

/* Setting for Channel 1 functionality */
#ifdef  __UARTD_CHN_HND_1__

/* Define LIN pin used */
#define UARTD_CHN_PIN           P1_bit.no1

/* Enable register masks */
/* These are the bit-masks of the register used to supply the clock to the module */
const uint8_t per0UartEnMasks_au8 = 0x40;

/* Pointers to interrupt flag registers of lin-uart channels */
/* Register in which interrupt flags are stored */
uint8_t * const reg_if_apu8[INT_MAX_NUM] =
{
  (uint8_t *) &IF1H,
  (uint8_t *) &IF1H,
  (uint8_t *) &IF1H,
  (uint8_t *) &IF1H
};

/* Pointers to interrupt mask registers of lin-uart channels */
/* Register in which interrupt masks are stored */
uint8_t * const reg_mk_apu8[INT_MAX_NUM] =
{
  (uint8_t *) &MK1H,
  (uint8_t *) &MK1H,
  (uint8_t *) &MK1H,
  (uint8_t *) &MK1H
};

/* Bit mask for interrupt flag and mask registers */
const uint8_t int_bit_mask_au8[INT_MAX_NUM] =
{
  0x02,
  0x04,
  0x08,
  0x10
};

/* Pointers to external interrupt mask registers of lin-uart channels */
/* Register in which external interrupt edge detector are stored */
uint8_t * const reg_ed_apu8[INT_EXT_MAX_NUM] =
{
  (uint8_t *) &EGP1,
  (uint8_t *) &EGN1
};

/* Bit mask for external interrupt mask registers */
const uint8_t int_ext_bit_mask_au8[INT_EXT_MAX_NUM] =
{
  0x08,
  0x08
};

/* Pointers to priority interrupt flag registers of lin-uart channels */
/* Register in which priority interrupt flags are stored */
uint8_t * const reg_pr_apu8[INT_PRIORITY_MAX_NUM] =
{
  (uint8_t *) &PR11H,
  (uint8_t *) &PR01H,
  (uint8_t *) &PR11H,
  (uint8_t *) &PR01H,
  (uint8_t *) &PR11H,
  (uint8_t *) &PR01H, 
  (uint8_t *) &PR11H,
  (uint8_t *) &PR01H,
};

/* Bit mask for external interrupt mask registers */
const uint8_t int_pri_bit_mask_au8[INT_PRIORITY_MAX_NUM] =
{
  0x02,
  0x02,
  0x04,
  0x04,
  0x08,
  0x08,
  0x10,
  0x10,
};

/* Uart modules */
static Uartd_mod_t uart_mod =
{
  (Uartd_hw_reg_t *)(LIN_UART_CTL_MEM_1),
  (uint8_t *)(LIN_UART_TX_W_REG_MEM_1),
  (uint8_t *)(LIN_UART_RX_REG_MEM_1),
  { 0 },
  { 0 },
  0,
  0,
  0,
  0,
  UARTD_SLEEP,
  UARTD_NO_ERROR,
  UARTD_RX_DATA_CBK
};

#endif

/* Register configuration of uart for LIN operation */
const Uartd_hw_reg_t ST_LINUART_BASIC_LIN_CFG =
{
  {                   /* control0     */
    0,  /* 1-bit stop */    
    1,  /* 8-bit data */
    0,  /* No parity for tx, rx */
    1,  /* LSB first */
    0,  /* Rx disable */
    0,  /* Tx disable */
    0   /* RESERVED */   
  },
  {                   /* option0      */
    0,  /* Input level    */
    0,  /* Output level   */
    5,  /* BF length      */
    0,  /* BF Tx Trigger  */
    0,  /* BF Rx Trigger  */
    0   /* BF Flag        */
  },              
  0x0DAA, /* control1     */
  0x0D,               /* option1      */
  0x00,               /* option2      */
  0x0000,             /* status       */
  0x7F1F,             /* statusClear  */  /* Clear all flags */
  0x00,               /* txWaitRegB   */
  {0},                /* RESERVED[3]  */
  0x00,               /* idSetting    */
  {0},                /* bufferReg[9] */
  0x00                /* bufferCtl    */
};

/*______ L O C A L - D A T A _________________________________________________*/

/* Flag to determine whether there's data in tx buffer */
static bool_t Uartd_TxBuffNotEmpty;

/* Flag to determine whether there's data in rx buffer */
static bool_t Uartd_RxBuffNotEmpty;

/* Flag to determine if new signal on bus is received */
static bool_t Uartd_ReceivedBusActivity;
 
/* Flag to determine if external Wake is received */
static bool_t Uartd_ReceivedExternalWakeUp;

/* Flag to determine if external signal is received (not break field)*/
static bool_t Uartd_ReceivedExternalSignal;

/* Counter for short circuit time slot */
static uint8_t Uartd_TimerScDetectionCount;  

/* Counter for short circuit time slot */
static uint8_t Uartd_ReceivedWakeUpCounter;



/*______ L O C A L - M A C R O S _____________________________________________*/

/* Move required buffer pointer */
#define Uartd_MovePtrCirc(ptr)\
{\
  (ptr)++;\
  (ptr) %= TX_BUFFER_LEN;\
}

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/
static void Uartd_tx_isr(uint8_t chn_hnd);   /* Transmission interrupt       */
static void Uartd_rx_isr(uint8_t chn_hnd);   /* Reception interrupt          */
static void Uartd_st_isr(uint8_t chn_hnd);   /* Status interrupt             */
static void Uartd_pr_isr(uint8_t chn_hnd);   /* Pin input interrupt          */

/* Interrupt for channel 0 */
#ifdef  __UARTD_CHN_HND_0__
  static uint16_t Uartd_INTLT0_IsrCbk(void);
  static uint16_t Uartd_INTLR0_IsrCbk(void);
  static uint16_t Uartd_INTLS0_IsrCbk(void);
  static uint16_t Uartd_INTPLR0_IsrCbk(void);
#endif

/* Interrupt for channel 1 */
#ifdef  __UARTD_CHN_HND_1__
  static uint16_t Uartd_INTLT1_IsrCbk(void);
  static uint16_t Uartd_INTLR1_IsrCbk(void);
  static uint16_t Uartd_INTLS1_IsrCbk(void);
  static uint16_t Uartd_INTPLR1_IsrCbk(void);
#endif



/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function Initializes the UARTD driver.
 * @return void
 * @note  It must be called only one time at the system init.
 */
void UARTD_Init(void)
{
  /* Support variables */  
  /* Init device ports */
  Uartd_InitPorts();
  
  /* Interrupt functions */
  Uartd_SetPriorityInterrupt();
  
  /* Interrupt for channel 0 */
  #ifdef  __UARTD_CHN_HND_0__  
    /* Set the callback for interrupt vector INTLT0 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLT0,(ISRD_EvtCbk_t)Uartd_INTLT0_IsrCbk);
    /* Set the callback for interrupt vector INTLR0 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLR0,(ISRD_EvtCbk_t)Uartd_INTLR0_IsrCbk);
    /* Set the callback for interrupt vector INTLS0 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLS0,(ISRD_EvtCbk_t)Uartd_INTLS0_IsrCbk);
    /* Set the callback for interrupt vector INTPLR0 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTPLR0,(ISRD_EvtCbk_t)Uartd_INTPLR0_IsrCbk);  
  #endif

  /* Interrupt for channel 1 */
  #ifdef  __UARTD_CHN_HND_1__ 
    /* Set the callback for interrupt vector INTLT1 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLT1,(ISRD_EvtCbk_t)Uartd_INTLT1_IsrCbk);
    /* Set the callback for interrupt vector INTLR1 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLR1,(ISRD_EvtCbk_t)Uartd_INTLR1_IsrCbk);
    /* Set the callback for interrupt vector INTLS1 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTLS1,(ISRD_EvtCbk_t)Uartd_INTLS1_IsrCbk);
    /* Set the callback for interrupt vector INTPLR1 */
    (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTPLR1,(ISRD_EvtCbk_t)Uartd_INTPLR1_IsrCbk);
  #endif   

  /* Reset buffer pointers */
  uart_mod.txHead = 0;
  uart_mod.txTail = 0;
  uart_mod.rxHead = 0;
  uart_mod.rxTail = 0;
         
  /* No data in buffers */
  Uartd_TxBuffNotEmpty = FALSE;
  Uartd_RxBuffNotEmpty = FALSE;
  
  /* Reset flag for external signal request */
  Uartd_ReceivedExternalSignal = FALSE;
  
  /* Reset module status */
  uart_mod.modStatus = UARTD_SLEEP;

  /* Advanced setup */
  UARTD_WakeUp(UARTD_CHN_HND); 
}

/**
 * @brief This function enables the UART module of uC.
 * @param Uart channel number
 * @return void
 */
void UARTD_WakeUp(uint8_t chn_hnd)
{  
  /* Enable UARTD channel */
  Uartd_LinEnableCh(chn_hnd, TRUE);
  
  /* Init registers */
  Uartd_InitAsLinMaster(uart_mod.Registers);
    
  /* Enable transmitter */
  uart_mod.Registers->control0.UFnTXE = 1;
  
  /* Enable receiver */
  uart_mod.Registers->control0.UFnRXE = 1;
  
  /* Clear flags */
  *(reg_if_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];
  *(reg_if_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
  *(reg_if_apu8[INT_ST]) &= ~int_bit_mask_au8[INT_ST];
  *(reg_if_apu8[INT_HW]) &= ~int_bit_mask_au8[INT_HW];
  
  /* Enable interrupts (unmask) */
  *(reg_mk_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];
  *(reg_mk_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
  *(reg_mk_apu8[INT_ST]) &= ~int_bit_mask_au8[INT_ST];
  
  /* Disable interrupts for WakeUp(mask) */  
  *(reg_mk_apu8[INT_HW]) |= int_bit_mask_au8[INT_HW];
  
  /* Disable external interrupts for WakeUp(mask) */ 
  *(reg_ed_apu8[INT_RE]) &= ~int_ext_bit_mask_au8[INT_RE];
  *(reg_ed_apu8[INT_FE]) &= ~int_ext_bit_mask_au8[INT_FE];  
  
  /* Reset flag for external WakeUp request */
  Uartd_ReceivedExternalWakeUp = FALSE;
  Uartd_ReceivedWakeUpCounter = 0;  
  
  /* Set idle state */
  uart_mod.modStatus = UARTD_IDLE;
}

/**
 * @brief This function disables the UART module of uC.
 * @param Uart channel number
 * @return void
 */
void UARTD_GoToSleep(uint8_t chn_hnd)
{
  /* Disable interrupts (mask) */
  *(reg_mk_apu8[INT_TX]) |= int_bit_mask_au8[INT_TX];
  *(reg_mk_apu8[INT_RX]) |= int_bit_mask_au8[INT_RX];
  *(reg_mk_apu8[INT_ST]) |= int_bit_mask_au8[INT_ST];
  
  /* Enable interrupts for WakeUp(mask) */  
  *(reg_mk_apu8[INT_HW]) &= ~int_bit_mask_au8[INT_HW];
  
  /* Enable external interrupts for WakeUp(mask) */ 
  *(reg_ed_apu8[INT_RE]) |= int_ext_bit_mask_au8[INT_RE];
  *(reg_ed_apu8[INT_FE]) |= int_ext_bit_mask_au8[INT_FE];  
  
  /* Clear flags */
  *(reg_if_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];
  *(reg_if_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
  *(reg_if_apu8[INT_ST]) &= ~int_bit_mask_au8[INT_ST];
  *(reg_if_apu8[INT_HW]) &= ~int_bit_mask_au8[INT_HW];  
  
  /* Disable transmitter */
  uart_mod.Registers->control0.UFnTXE = 0;
  
  /* Disable receiver */
  uart_mod.Registers->control0.UFnRXE = 0;
  
  /* Disable UARTD channel */
  Uartd_LinEnableCh(chn_hnd, FALSE);
  
  /* Reset flag for external WakeUp request */
  Uartd_ReceivedExternalSignal = FALSE;
  Uartd_ReceivedExternalWakeUp = FALSE;
  Uartd_ReceivedWakeUpCounter = 0;
  
  /* Set state to sleep */
  uart_mod.modStatus = UARTD_SLEEP;
}

/**
 * @brief This function reads n bytes from the reception buffer.
 * @param Uart channel number, pointer to data buffer, number of bytes to read
 * @return uint8_t, Number of read bytes
 * @note Head on first element to read; T over last element to read.
 */
uint8_t UARTD_ReadBuffer(uint8_t chn_hnd, uint8_t *rxBuffer, uint8_t len)
{
  /* Bytes are read from reception buffer and written into
      requested buffer until requested number or tail is reached */
      
  /* Support variables */
  uint8_t bytesRead_u8;
  uint8_t buffHead_u8;
  uint8_t buffTail_u8;
  
  /* Disable reception interrupts */
  *(reg_mk_apu8[INT_RX]) |= int_bit_mask_au8[INT_RX];
  
  /* Retrieve pointer values */
  bytesRead_u8 = 0;   /* Number of read bytes */
  buffHead_u8 = uart_mod.rxHead;
  buffTail_u8 = uart_mod.rxTail;
  
  /* Iterate until required */
  while ( (bytesRead_u8 < len) && (Uartd_RxBuffNotEmpty == TRUE) )
  {
    /* Write received data into requested buffer */
    rxBuffer[bytesRead_u8] = uart_mod.rxBuffer[buffHead_u8];
    
    /* Update head pointer */
    Uartd_MovePtrCirc(buffHead_u8);
    
    /* Increase number of bytes read */
    bytesRead_u8++;
    
    /* Check for end of buffer */
    if (buffHead_u8 == buffTail_u8)
    {
      Uartd_RxBuffNotEmpty = FALSE;
    }
    
  }
  
  /* Store new head value */
  uart_mod.rxHead = buffHead_u8;
  
  /* Enable reception interrupts */
  *(reg_mk_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
  
  /* Return number of bytes read */
  return bytesRead_u8;
}

/**
 * @brief This function sends n bytes from the transmission buffer.
 * @param Uart channel number, pointer to data buffer, number of bytes to send
 * @return Void
 * @note Head on first element to send; T over last element to send.
 */
void UARTD_SendBuffer(uint8_t chn_hnd, uint8_t *txBuffer, uint8_t len)
{
  /* Update transmission buffer with bytes which are specified by
     required buffer */
  
  /* Support variables */
  uint8_t index_u8;   
  uint8_t buffHead_u8;
  uint8_t buffTail_u8;
  
  /* Disable transmission interrupts */
  *(reg_mk_apu8[INT_TX]) |= int_bit_mask_au8[INT_TX];
  
  /* Retrieve pointer values */
  index_u8 = 0;   /* Iterator */
  buffHead_u8 = uart_mod.txHead;
  buffTail_u8 = uart_mod.txTail;
  
  /* Iterate until required */
  /* Exit when end is reached or overrun is detected */
  /* No overrun when buffer still empty */
  /* Overrun when tail reaches head with buffer full */
  while ( (index_u8 < len) &&
    ((Uartd_TxBuffNotEmpty == FALSE) || (buffTail_u8 != buffHead_u8)) )  
  {
      /* Write received data into requested buffer */
      uart_mod.txBuffer[buffTail_u8] = txBuffer[index_u8];
      
      /* Update tail pointer */
      Uartd_MovePtrCirc(buffTail_u8);
      
      /* Increase number of processed bytes */
      index_u8++;
      
      /* Now the buffer is not empty */
      Uartd_TxBuffNotEmpty = TRUE;
  }
  
  /* Store new tail value */
  uart_mod.txTail = buffTail_u8;
  
  /* Enable transmission interrupts */
  *(reg_mk_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];
  
  if (buffTail_u8 == buffHead_u8)
  {
      /* Overrun!! */
  }
  else
  {
    /* Start sending if not already on operation */
    if (uart_mod.modStatus == UARTD_IDLE)
    {
        /* Change status */
        uart_mod.modStatus = UARTD_TG_DATA;
        
        /* Start new transmission */
        /* Update head pointer */
        Uartd_MovePtrCirc(uart_mod.txHead);
        
        /* Put element in tx buffer pointer by head pointer into
            uart transmission register */
        *(uart_mod.txReg_p) = uart_mod.txBuffer[buffHead_u8];
        
        /* Check for other data to transfer */ 
        if(uart_mod.txHead == uart_mod.txTail)
        {
          /* Buffer is now empty */
          Uartd_TxBuffNotEmpty = FALSE;
        }
    }
  }
}

/**
 * @brief This function reads the first byte in the reception buffer.
 * @param Uart channel number
 * @return uint8_t, Byte read
 * @note If no byte is available in the reception buffer, 0 is returned.
 */
uint8_t UARTD_ReadByte(uint8_t chn_hnd)
{
  /* Support variables */
  uint8_t byteRead_u8 = 0;
  uint8_t buffHead_u8;
  uint8_t buffTail_u8;
  
  /* Disable reception interrupts */
  *(reg_mk_apu8[INT_RX]) |= int_bit_mask_au8[INT_RX];
  
  /* Retrieve pointer values */
  buffHead_u8 = uart_mod.rxHead;
  buffTail_u8 = uart_mod.rxTail;
  
  /* Retrieve first byte in buffer */
  if ( Uartd_RxBuffNotEmpty == TRUE )
  {
      /* Store data */
      byteRead_u8 = uart_mod.rxBuffer[buffHead_u8];
      
      /* Update head pointer */
      Uartd_MovePtrCirc(buffHead_u8);
      
      /* Check for empty buffer */
      if (buffHead_u8 == buffTail_u8)
      {
        Uartd_RxBuffNotEmpty = FALSE;
      }
  }
  
  /* Store new head value */
  uart_mod.rxHead = buffHead_u8;
  
  /* Enable reception interrupts */
  *(reg_mk_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
  
  /* Return byte */
  return byteRead_u8;
}

/**
 * @brief This function sends a byte.
 * @param Uart channel number, byte to send
 * @return Void
 */
void UARTD_SendByte(uint8_t chn_hnd, uint8_t byteToSend)
{
  /* Support variables */
  uint8_t buffHead_u8;
  uint8_t buffTail_u8;
  
  /* Disable transmission interrupts */
  *(reg_mk_apu8[INT_TX]) |= int_bit_mask_au8[INT_TX];
  
  /* Retrieve pointers */
  buffHead_u8 = uart_mod.txHead;
  buffTail_u8 = uart_mod.txTail;
  
  /* Check for overrun error */  
  if ((Uartd_TxBuffNotEmpty == FALSE) || (buffTail_u8 != buffHead_u8))
  {
      /* Write received data into requested buffer */
      uart_mod.txBuffer[buffTail_u8] = byteToSend;
      
      /* Update tail pointer */
      Uartd_MovePtrCirc(buffTail_u8);
      
      /* Now the buffer is not empty */
      Uartd_TxBuffNotEmpty = TRUE;
          
  }
    
  /* Store new tail value */
  uart_mod.txTail = buffTail_u8;
  
  /* Enable transmission interrupts */
  *(reg_mk_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];

  /* Start sending if not already on operation */
  if (uart_mod.modStatus == UARTD_IDLE)
  {
    /* Change status */
    uart_mod.modStatus = UARTD_TG_DATA;
    
    /* Start new transmission */
    /* Update head pointer */
    Uartd_MovePtrCirc(uart_mod.txHead);
    
    /* Put element in tx buffer pointer by head pointer into
      uart transmission register */
    *(uart_mod.txReg_p) = uart_mod.txBuffer[buffHead_u8]; 
  }  
}

/**
 * @brief This function returns whether there are non-read bytes in the reception buffer.
 * @param Uart channel number
 * @return Boolean
 */
bool_t UARTD_IsDataReceived(uint8_t chn_hnd)
{  
  return Uartd_RxBuffNotEmpty;
}

/**
 * @brief This function returns the number of non-read bytes in the reception buffer.
 * @param Uart channel number
 * @return uint8_t, Number of bytes in buffer
 */
uint8_t UARTD_GetNumberOfRxBytes(uint8_t chn_hnd)
{
  /* Support variables */
  /* Retrieve values of head and tail pointers */
  uint8_t buffHead_u8 = uart_mod.rxHead;
  uint8_t buffTail_u8 = uart_mod.rxTail;
  uint8_t receivedBytes_u8;
  
  if (Uartd_RxBuffNotEmpty == TRUE)
  {
    receivedBytes_u8 = (RX_BUFFER_LEN + buffTail_u8 - buffHead_u8) % RX_BUFFER_LEN;
  }
  else
  {
    receivedBytes_u8 = 0;
  }
  
  /* Return number of available bytes */
  return receivedBytes_u8;
}

/**
 * @brief This function is used to start sending a LIN break field (BF).
 * @param Uart channel number
 * @return Void
 */
void UARTD_SendBreak(uint8_t chn_hnd)
{
  /* Reset transmission buffer */
  uart_mod.txHead = 0;
  uart_mod.txTail = 0;
  Uartd_TxBuffNotEmpty = FALSE;
  
  /* Change status */
  uart_mod.modStatus = UARTD_TG_BF;
  
  /* Listen to break */
  uart_mod.Registers->option0.BRT = 1;
  
  /* Trigger break */
  uart_mod.Registers->option0.BTT = 1;

}

/**
 * @brief This function returns whether a break field has been received.
 * @param Uart channel number
 * @return Boolean
 * @note True is returned until the current frame ends.
 */
bool_t UARTD_IsBreakReceived(uint8_t chn_hnd)
{
  /* Support variables */
  bool_t rxBreak = FALSE;
  bool_t regStatus_b;
  regStatus_b = uart_mod.Registers->status & STATUS_BF_RX_BIT_MASK;
  
  if (regStatus_b != 0x0000)
  {
    /* Set output */
    rxBreak = TRUE;
    
    /* Clear flag */
    uart_mod.Registers->statusClear |= STATUS_BF_RX_BIT_MASK;
  }
  
  return rxBreak;
}

/**
 * @brief This function is used to start sending a LIN wakeup signal (WU).
 * @param Uart channel number
 * @return void
 */
void UARTD_SendWakeUp(uint8_t chn_hnd)
{
  /* Disable transmitter */
  uart_mod.Registers->control0.UFnTXE = 0;
 
  /* Set new value of BF */
  uart_mod.Registers->option0.BLS = UARTD_WAKE_UP_LEN; 
   
  /* Enable transmitter */
  uart_mod.Registers->control0.UFnTXE = 1; 
  
  /* Send new break used as WakeUp */
  UARTD_SendBreak(chn_hnd);  
}

/**
 * @brief This function is used to reset break field value.
 * @param Uart channel number
 * @return void
 */
void UARTD_ResetBreakFieldLen(uint8_t chn_hnd)
{
  /* Disable transmitter */
  uart_mod.Registers->control0.UFnTXE = 0;
 
  /* Set new value of BF */
  uart_mod.Registers->option0.BLS = UARTD_BF_LEN; 
   
  /* Enable transmitter */
  uart_mod.Registers->control0.UFnTXE = 1; 
  
}

/**
 * @brief This function informs on a bus signal reception.
 * @param Uart channel number
 * @return Boolean
 */
bool_t UARTD_GetBusSignalRequest(uint8_t chn_hnd)
{
  /* Return flag for external signal on bus*/
     
  /* Support variables */
  bool_t receivedExternalSignal = Uartd_ReceivedExternalSignal;
  
  /* If sleep mode is PowerOff, when IUT start, this function read 
  transceiver RX pin (if 1 there is activity on bus) */
  if (UARTD_GOTOSLEEP_MODE == UARTD_POWEROFF)
  {    
    /* Verify that UARTD both in Idle state */
    if((UARTD_CHN_PIN == 1U) && (UARTD_GetStatus(chn_hnd) == UARTD_IDLE))
    {
      receivedExternalSignal = TRUE;
    }                
  }    
  
  /* Reset flag */
  Uartd_ReceivedExternalSignal = FALSE;
  
  return receivedExternalSignal;
}

/**
 * @brief This function informs on a slave wakeup signal reception.
 * @param Uart channel number
 * @return Boolean
 */
bool_t UARTD_GetBusWakeUpRequest(uint8_t chn_hnd)
{
  /* Return flag for external WakeUp signal */
  
  /* Support variables */
  bool_t receivedExternalWakeUp = Uartd_ReceivedExternalWakeUp;
  
  /* Reset flag */
  Uartd_ReceivedExternalWakeUp = FALSE;
  
  return receivedExternalWakeUp;
}

/**
 * @brief Return if IUT has received a new signal on bus (for s.c. detection)
 * @param uint8_t, Uart channel number
 * @return boolean
 */
bool_t UARTD_GetBusActivity(uint8_t chn_hnd)
{
  /* If DUT has received a new signal this flag is set TRUE. Used for
    short circuit detection */
  
  /* Support variables */
  bool_t receivedBusActivity = Uartd_ReceivedBusActivity;
  
  /* Reset flag */
  Uartd_ReceivedBusActivity = FALSE;
  
  return receivedBusActivity;   
}

/**
 * @brief This function set a short circuit error.
 * @param uint8_t, Uart channel number
 * @return void
 */
void UARTD_SetShortCircuitError(uint8_t chn_hnd)
{
  /* Set short circuit error. This function is call into a period task 
  ( TaskBackground100ms). If the DUT does not receive a break field is set a 
    error */

  /* Checks whether the sw timer is over */
  if(Uartd_TimerScDetectionCount == UARTD_TIME_SC_TICK)
  {
    /* Checks current UARTD state */
    if(UARTD_GetStatus(chn_hnd) != UARTD_SLEEP)
    {
      /* Checks whether the break field is detected */
      if(UARTD_GetBusActivity(chn_hnd) == FALSE)
      {        
        /* Select a short circuit type */
        if(UARTD_CHN_PIN == 1)
        { 
          /* Set short circuit to Vbat */
          uart_mod.modError = UARTD_SHORT_CIRCUIT_HIGH;
        }
        else
        {
          /* Set short circuit to Ground */
          uart_mod.modError = UARTD_SHORT_CIRCUIT_LOW;
        }
      }
    }          
    /* Reset couter */
    Uartd_TimerScDetectionCount = 0;
  }
  else
  {
    /* Increase couter */
    Uartd_TimerScDetectionCount ++;
  }
}

/**
 * @brief This function returns the status of the module.
 * @param Uart channel number
 * @return UARTD_Status_t
 */
UARTD_Status_t UARTD_GetStatus(uint8_t chn_hnd)
{
  /* Support variables */
  UARTD_Status_t moduleState;
  
  moduleState = uart_mod.modStatus;
  
  return moduleState;
}

/**
 * @brief This function returns the last error status of the module.
 * @param Uart channel number
 * @return UART_HwErrorStatus_t
 */
UARTD_HwErrorStatus_t UARTD_GetDiag(uint8_t chn_hnd)
{
  /* Support variables */
  UARTD_HwErrorStatus_t moduleErrorState;
  
  moduleErrorState = uart_mod.modError;
  
  return moduleErrorState;
}

/* Local functions */

/**
 * @brief Initialize ports of the device
 * @return void
 */
void Uartd_InitPorts(void)
{
 #ifdef __UARTD_CHN_HND_0__
  /*  UART0 */
  STSEL |= 0x02; /* xxxxxx1x */
  
  P1  |= 0x18; /* xxx11xxx */
  PM1 |= 0x10; /* xxx1xxxx */
  PM1 &= 0xF7; /* xxxx0xxx */
#endif

#ifdef __UARTD_CHN_HND_1__  
  /*  UART1 */
  STSEL |= 0x04; /* xxxxx1xx */
  
  P1  |= 0x03; /* xxxxxx11 */
  PM1 |= 0x02; /* xxxxxx1x */
  PM1 &= 0xFE; /* xxxxxxx0 */
#endif  
}

/**
 * @brief Set priority for interrupt
 * @return void
 */
void Uartd_SetPriorityInterrupt(void)
{
  /* Support varaibles */
  uint8_t bit_H;      /* Value of high bit to set */
  uint8_t bit_L;      /* Value of low bit to set */
  
  /* Set TX interrupt priority */
  bit_H = (UARTD_INT_PR_LEVEL_TX & MASK_bit_1) >> 1;
  bit_L = (UARTD_INT_PR_LEVEL_TX & MASK_bit_0);  
  
  /* HIGH side */
  if(bit_H == 0)
  {
    *(reg_pr_apu8[INT_TX_H]) &= ~int_pri_bit_mask_au8[INT_TX_H];
  }
  else
  {
    *(reg_pr_apu8[INT_TX_H]) |= int_pri_bit_mask_au8[INT_TX_H];
  }
  /* LOW side */
  if(bit_L == 0)
  {
    *(reg_pr_apu8[INT_TX_L]) &= ~int_pri_bit_mask_au8[INT_TX_L];
  }
  else
  {
    *(reg_pr_apu8[INT_TX_L]) |= int_pri_bit_mask_au8[INT_TX_L];
  }  
  
  /* Set RX interrupt priority */
  bit_H = (UARTD_INT_PR_LEVEL_RX & MASK_bit_1) >> 1;
  bit_L = (UARTD_INT_PR_LEVEL_RX & MASK_bit_0);  
  
  /* HIGH side */
  if(bit_H == 0)
  {
    *(reg_pr_apu8[INT_RX_H]) &= ~int_pri_bit_mask_au8[INT_RX_H];
  }
  else
  {
    *(reg_pr_apu8[INT_RX_H]) |= int_pri_bit_mask_au8[INT_RX_H];
  }
  /* LOW side */
  if(bit_L == 0)
  {
    *(reg_pr_apu8[INT_RX_L]) &= ~int_pri_bit_mask_au8[INT_RX_L];
  }
  else
  {
    *(reg_pr_apu8[INT_RX_L]) |= int_pri_bit_mask_au8[INT_RX_L];
  }  
  
  /* Set ST (status) interrupt priority */
  bit_H = (UARTD_INT_PR_LEVEL_ST & MASK_bit_1) >> 1;
  bit_L = (UARTD_INT_PR_LEVEL_ST & MASK_bit_0);  
  
  /* HIGH side */
  if(bit_H == 0)
  {
    *(reg_pr_apu8[INT_ST_H]) &= ~int_pri_bit_mask_au8[INT_ST_H];
  }
  else
  {
    *(reg_pr_apu8[INT_ST_H]) |= int_pri_bit_mask_au8[INT_ST_H];
  }
  /* LOW side */
  if(bit_L == 0)
  {
    *(reg_pr_apu8[INT_ST_L]) &= ~int_pri_bit_mask_au8[INT_ST_L];
  }
  else
  {
    *(reg_pr_apu8[INT_ST_L]) |= int_pri_bit_mask_au8[INT_ST_L];
  } 
  
  /* Set PR (External signal is received) interrupt priority */
  bit_H = (UARTD_INT_PR_LEVEL_PR & MASK_bit_1) >> 1;
  bit_L = (UARTD_INT_PR_LEVEL_PR & MASK_bit_0);  
  
  /* HIGH side */
  if(bit_H == 0)
  {
    *(reg_pr_apu8[INT_PR_H]) &= ~int_pri_bit_mask_au8[INT_PR_H];
  }
  else
  {
    *(reg_pr_apu8[INT_PR_H]) |= int_pri_bit_mask_au8[INT_PR_H];
  }
  /* LOW side */
  if(bit_L == 0)
  {
    *(reg_pr_apu8[INT_PR_L]) &= ~int_pri_bit_mask_au8[INT_PR_L];
  }
  else
  {
    *(reg_pr_apu8[INT_PR_L]) |= int_pri_bit_mask_au8[INT_PR_L];
  }   
}


/**
 * @brief Initialize Uart HW registers.
 * @param Pointer to hw registers
 * @return void
 */
void Uartd_InitAsLinMaster(Uartd_hw_reg_t * reg)
{
  reg->control0.UFnSL  = 0; /* 1-bit stop */    
  reg->control0.UFnCL  = 1; /* 8-bit data */
  reg->control0.UFnPS  = 0; /* No parity for tx, rx */
  reg->control0.UFnDIR = 1; /* LSB first */
  reg->control0.UFnRXE = 0; /* Rx disable */
  reg->control0.UFnTXE = 0; /* Tx disable */
  
  reg->option0.RDL = 0;     /* Input level    */
  reg->option0.TDL = 0;     /* Output level   */
  reg->option0.BLS = UARTD_BF_LEN;     /* BF length      */
  
  reg->control1 = UARTD_CTL1_BR_HZ;
  
  reg->option1 = 0x0D;
  
  /* Other registers ok at reset */
}

/**
 * @brief Enable or disable supply to UART channel specified in parameter.
 * @param Channel number, enable value
 * @return void
 */
void Uartd_LinEnableCh(uint8_t chn_hnd, bool_t en)
{
  if (en == TRUE)
  {
    PER0 |= per0UartEnMasks_au8;
  }
  else
  {
    PER0 &= ~per0UartEnMasks_au8;
  }
}




/* ISR , interrupt management*/

/**
 * @brief Callback function for Tx Interrupt
 * @param Uart channel number
 * @return void
 */
static void Uartd_tx_isr(uint8_t chn_hnd)
{
  if(uart_mod.modStatus == UARTD_TG_DATA)
  {       
    if(uart_mod.txHead < uart_mod.txTail)
    {
      /* Send pointed byte */
      *(uart_mod.txReg_p) = uart_mod.txBuffer[uart_mod.txHead];
      
      /* Update pointer */
      Uartd_MovePtrCirc(uart_mod.txHead);    
    
    }
    else if(uart_mod.txHead == uart_mod.txTail)
    {
      /* Check for other data to transfer */
      /* If end of buffer has been reached */
      
      /* Go back to idle state */
      uart_mod.modStatus = UARTD_IDLE;
      
      /* Buffer is now empty */
      Uartd_TxBuffNotEmpty = FALSE; 
    }
    else
    {
      /* MISRA 14.10 */
    }
  }
}

/**
 * @brief Callback function for Rx Interrupt
 * @param Uart channel number
 * @return void
 */
static void Uartd_rx_isr(uint8_t chn_hnd)
{
  /* Store received byte */
  uart_mod.rxBuffer[uart_mod.rxTail] = *(uart_mod.rxReg_p);
  
  /* Set a flag for short circuit detection */
  Uartd_ReceivedBusActivity = TRUE;
  
  if(uart_mod.modError == UARTD_NO_ERROR)
  {  
    /* Update buffer pointer */
    Uartd_MovePtrCirc(uart_mod.rxTail);
    
    /* Buffer is now not empty */
    Uartd_RxBuffNotEmpty = TRUE;
    
    /* If head reaches tail, move tail */
    /* (Neglet overrun) */
    if (uart_mod.rxTail == uart_mod.rxHead)
    {
      Uartd_MovePtrCirc(uart_mod.rxHead);
    }
  }

  /* Call LINC callback for LIN reception (slave task) */
  if (uart_mod.RxDataCbk != NULL)
  {
    uart_mod.RxDataCbk();
  }   
}

/**
 * @brief Callback function for St Interrupt
 * @param Uart channel number
 * @return void
 */
static void Uartd_st_isr(uint8_t chn_hnd)
{
  /* Support varaibles */
  uint16_t  statusReg_u16;  /* Value of status reg */
  uint8_t buffHead_u8;      /* Buffer head ptr */
  uint8_t fakeReadByte;     /* Used if error is detected (clear HW RW Buffer)*/

  /* Flag used to enable Reception Task.Not enable when there's a 
    WakeUp signal on bus from another node*/
  bool_t enableReceptionTask;   
  enableReceptionTask = TRUE;
  
  /* Set a flag for short circuit detection. 
  If status of UARTD is UARTD_TG_BF not set a flag because if break field 
    is corrupted to Vbat interrupt decect the error. In this case isn't 
    activity*/
  if(uart_mod.modStatus != UARTD_TG_BF)
  {
    Uartd_ReceivedBusActivity = TRUE;  
  }
  
  /* Retrieve status flag */
  statusReg_u16 = uart_mod.Registers->status;
  
  /* Retrieve head and tail pointers */
  buffHead_u8 = uart_mod.txHead;

  /* Check for status errors */
  if ((statusReg_u16 & STATUS_ALL_ERRORS_BIT_MASK) != 0)
  {
    /* Clear error flags */
    uart_mod.Registers->statusClear |= STATUS_ALL_ERRORS_BIT_MASK;
    
    /* Clear HW buffer in RX for recovery from UARTD_ERR_HW_OVERRUN */
    fakeReadByte = *(uart_mod.rxReg_p);
    if(fakeReadByte == 0)
    {
      NOP();
    }
    
    /* Set a new error only if the bus is not in short circuit state and there is bus activity */
    if((UARTD_GetBusActivity(chn_hnd) != FALSE) && ((uart_mod.modError != UARTD_SHORT_CIRCUIT_LOW) ||
        (uart_mod.modError != UARTD_SHORT_CIRCUIT_HIGH)))
    {
      /* Data consistency check error */
      if ((statusReg_u16 & STATUS_DATA_CONS_ERR_BIT_MASK) != 0)
      {      
        uart_mod.modError = UARTD_ERR_DATA_CONS;      
      }
      /* Parity error */    
      if ((statusReg_u16 & STATUS_PARITY_ERR_BIT_MASK) != 0)
      {      
        uart_mod.modError = UARTD_ERR_PARITY;      
      }    
      /* Framing error (no stop bit detected) */    
      if ((statusReg_u16 & STATUS_FRAMING_ERR_BIT_MASK) != 0)
      {      
        uart_mod.modError = UARTD_ERR_FRAMING;       
      } 
      /* Overrun error */
      if ((statusReg_u16 & STATUS_OVERRUN_ERR_BIT_MASK) != 0)
      {      
        uart_mod.modError = UARTD_ERR_HW_OVERRUN;            
      }     
    }
        
    /* Management of transmission*/    
    /* Disable interrupts */
    *(reg_mk_apu8[INT_TX]) |= int_bit_mask_au8[INT_TX];
    /* Clear pointer */
    uart_mod.txTail = uart_mod.txHead;
    Uartd_TxBuffNotEmpty = FALSE;
    /* Enable interrupts */
    *(reg_mk_apu8[INT_TX]) &= ~int_bit_mask_au8[INT_TX];
    
    /* Management of reception*/
    /* Disable interrupts */
    *(reg_mk_apu8[INT_RX]) |= int_bit_mask_au8[INT_RX];           
   /* Clear pointer */
    uart_mod.rxHead = uart_mod.rxTail;
    Uartd_RxBuffNotEmpty = FALSE;    
    /* Enable interrupts */
    *(reg_mk_apu8[INT_RX]) &= ~int_bit_mask_au8[INT_RX];
            
  }
  else
  {  
    /* Check for effective break reception */
    if ((statusReg_u16 & STATUS_BF_RX_BIT_MASK) != 0)
    {         
      /* Set a flag for short circuit detection */
      Uartd_ReceivedBusActivity = TRUE;      
      
      /* Reset frame error */
      uart_mod.modError = UARTD_NO_ERROR;
      
      /* Select state */
      switch (uart_mod.modStatus)
      {       
        case UARTD_IDLE:
          /* If external break field is received */          
          /* Increase a couter of break field read for WakeUp */                           
          Uartd_ReceivedWakeUpCounter ++;
          /* Disable Reception Task until a WakeUp signal is confirmed */ 
          enableReceptionTask = FALSE;
          
          if(Uartd_ReceivedWakeUpCounter == UARTD_EXTERNAL_WAKE_UP_EXPECTED)
          {
            /* If DUT receives 2 break signal this is a WakeUp */
            Uartd_ReceivedExternalWakeUp = TRUE;
            Uartd_ReceivedWakeUpCounter = 0;
            
            /* Enable Reception Task because a WakeUp signal is confirmed */ 
            enableReceptionTask = TRUE;
          }          
          break;
        case UARTD_TG_BF:

          /* Reset poiter for new reception frame */
          uart_mod.rxHead = uart_mod.rxTail;
          Uartd_RxBuffNotEmpty = FALSE; 
 
          /* Check whether the data buffer is full */
          if (Uartd_TxBuffNotEmpty == TRUE)
          {
              /* Start new transmission */
              /* Change status */
              uart_mod.modStatus = UARTD_TG_DATA;
              
              /* Put element in tx buffer pointer by head pointer into
                  uart transmission register */
              *(uart_mod.txReg_p) = uart_mod.txBuffer[buffHead_u8];
              
              /* Update buffer pointer */
              Uartd_MovePtrCirc(buffHead_u8);
              
              /* Store new head pointer */
              uart_mod.txHead = buffHead_u8;
          }
          else
          {
            /* Nothing to send, go back to idle */
            uart_mod.modStatus = UARTD_IDLE;            
          }
          break;
        default:
          /* Should not arrive here */
          break;
          
       /* Close switch */               
      }
    /* Close confirm reception break field*/
    }
  /* Close reception break field or error mask*/
  }
  
  /* Call task for LIN reception (slave task) */
  if(enableReceptionTask == TRUE)
  { 
    /* Call LINC callback */
    if (uart_mod.RxDataCbk != NULL)
    {
      uart_mod.RxDataCbk();
    }     
  } 
}

/**
 * @brief Callback function for Pin input Interrupt
 * @param Uart channel number
 * @return void
 */
static void Uartd_pr_isr(uint8_t chn_hnd)
{   
  /* External signal is received: LINC checks whether is a WakeUp */
  Uartd_ReceivedExternalWakeUp = FALSE;
  Uartd_ReceivedExternalSignal = TRUE;
  Uartd_ReceivedWakeUpCounter = 0;

  /* Wake up transceiver */
  LTMS_WakeUp(chn_hnd);
  /* Wake up UART */
  UARTD_WakeUp(chn_hnd);
}

/* ISR */
/* Interrupt for channel 0 */
#ifdef  __UARTD_CHN_HND_0__
  static uint16_t Uartd_INTLT0_IsrCbk(void)
  {
    Uartd_tx_isr(0);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLT0));
  }

  static uint16_t Uartd_INTLR0_IsrCbk(void)
  {
    Uartd_rx_isr(0);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLR0));
  }

  static uint16_t Uartd_INTLS0_IsrCbk(void)
  {
    Uartd_st_isr(0);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLS0));
  }

  static uint16_t Uartd_INTPLR0_IsrCbk(void)
  {
    Uartd_pr_isr(0);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPLR0));
  }
#endif


/* Interrupt for channel 1 */
#ifdef  __UARTD_CHN_HND_1__
  static uint16_t Uartd_INTLT1_IsrCbk(void)
  {
    Uartd_tx_isr(1);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLT1));
  }

  static uint16_t Uartd_INTLR1_IsrCbk(void)
  {
    Uartd_rx_isr(1);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLR1));
  }

  static uint16_t Uartd_INTLS1_IsrCbk(void)
  {
    Uartd_st_isr(1);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTLS1));
  }

  static uint16_t Uartd_INTPLR1_IsrCbk(void)
  {
    Uartd_pr_isr(1);
    
    return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTPLR1));
  }
#endif


#endif /* end __UARTD_IS_PRESENT__ */

/*______ E N D _____ (UARTD.c) ________________________________________________*/

