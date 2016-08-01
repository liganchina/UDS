/**
 * @file UARTD.h
 * @brief UARTD Driver: private interface of UART module for driver layer. 
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

#ifndef __UARTD_H
#define __UARTD_H

/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "DRVD_if.h"
#include "CTRL_if.h"
/* #include "UARTD_cbk.h" */

/* Module inhibition filter */
#ifdef __UARTD_IS_PRESENT__

#include "UARTD_config.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* Baud rate settings */
#define LIN_UART_BRS    ((uint16_t) (F_CLK_MHZ * 1000000U / ( 2U * UARTD_BR_HZ )))

#define LIN_UART_BR_ERROR_01PC   ((uint16_t) ((F_CLK_MHZ * 1000000U / ( 2U * LIN_UART_BRS )) * 1000U / UARTD_BR_HZ - 1000 ))

#define UARTD_CTL1_BR_HZ    ((uint16_t) (((uint16_t)(LIN_UART_PRESC) << 13U) | LIN_UART_BRS))


/* Setting break field length for registry UFnOPT0.BLS */
#define BF_LEN_13_BIT           ((uint8_t) 5)    /* BF 676us */
#define BF_LEN_14_BIT           ((uint8_t) 6)    /* BF 728us */
#define BF_LEN_15_BIT           ((uint8_t) 7)    /* BF 780us */
#define BF_LEN_16_BIT           ((uint8_t) 0)    /* BF 832us */
#define BF_LEN_17_BIT           ((uint8_t) 1)    /* BF 884us */
#define BF_LEN_18_BIT           ((uint8_t) 2)    /* BF 936us */
#define BF_LEN_19_BIT           ((uint8_t) 3)    /* BF 988us */
#define BF_LEN_20_BIT           ((uint8_t) 4)    /* BF 1040us */

/* Memory location of registers */
#define LIN_UART_CTL_MEM_0      ( &UF0CTL0 )
#define LIN_UART_CTL_MEM_1      ( &UF1CTL0 )
#define LIN_UART_TX_REG_MEM_0   ( &UF0TXB )
#define LIN_UART_RX_REG_MEM_0   ( &UF0RXB )
#define LIN_UART_TX_REG_MEM_1   ( &UF1TXB )
#define LIN_UART_RX_REG_MEM_1   ( &UF1RXB )

#define LIN_UART_TX_W_REG_MEM_0   ( &UF0WTXB )
#define LIN_UART_TX_W_REG_MEM_1   ( &UF1WTXB )

/* Status register bit masks (same for clear) */

/* Overrun error */
#define STATUS_OVERRUN_ERR_BIT_MASK   ((uint16_t)( 1 << 0 ))
/* Framing error (no stop bit detected) */
#define STATUS_FRAMING_ERR_BIT_MASK   ((uint16_t)( 1 << 1 ))
/* Parity error */
#define STATUS_PARITY_ERR_BIT_MASK    ((uint16_t)( 1 << 2 ))    
/* Data consistency check error */
#define STATUS_DATA_CONS_ERR_BIT_MASK ((uint16_t)( 1 << 3 ))    
/* Break field successful reception */
#define STATUS_BF_RX_BIT_MASK         ((uint16_t)( 1 << 4 ))    
/* Reception status */
#define STATUS_RX_STATUS_BIT_MASK     ((uint16_t)( 1 << 6 ))    
/* Transmission status */
#define STATUS_TX_STATUS_BIT_MASK     ((uint16_t)( 1 << 7 ))    
/* Extension bit detected */
#define STATUS_EXT_BIT_BIT_MASK       ((uint16_t)( 1 << 8 ))    
/* ID match, only when enabled */
#define STATUS_ID_MATCH_BIT_MASK      ((uint16_t)( 1 << 9 ))    
/* Buffer transmission/reception completion, normal UART mode only */
#define STATUS_BUFF_TX_RX_BIT_MASK    ((uint16_t)( 1 << 10 ))   
/* Header reception complete, ABR mode only, not set during PID */
#define STATUS_HEADER_RX_BIT_MASK     ((uint16_t)( 1 << 11 ))   
/* Response preparation error, ABR mode only */
#define STATUS_RESP_PREP_ERR_BIT_MASK ((uint16_t)( 1 << 12 ))   
/* Checksum error, ABR mode only */ 
#define STATUS_CHECKSUM_ERR_BIT_MASK  ((uint16_t)( 1 << 13 ))   
/* Id parity error, ABR mode only */
#define STATUS_ID_PAR_ERR_BIT_MASK    ((uint16_t)( 1 << 14))    
/* Mask of errors in status register */
#define STATUS_ALL_ERRORS_BIT_MASK    ((uint16_t)0x700F)  



/* Module specifications */
#define TX_BUFFER_LEN   ((uint8_t) 16)
#define RX_BUFFER_LEN   ((uint8_t) 16)

/* Module specifications */
#define MASK_bit_0   ((uint8_t) 1)
#define MASK_bit_1   ((uint8_t) 2)


/*______ G L O B A L - T Y P E S _____________________________________________*/

/* List of interrupt types for lin-uart */
typedef enum
{
  INT_TX = 0,
  INT_RX,
  INT_ST,
  INT_HW,
  INT_MAX_NUM
} Uartd_int_type_t;

/* List of external interrupt types for lin-uart */
typedef enum
{
  INT_RE = 0,
  INT_FE,
  INT_EXT_MAX_NUM
} Uartd_int_ext_type_t;

/* List of priority interrupt types for lin-uart */
typedef enum
{
  INT_TX_H = 0,
  INT_TX_L,
  INT_RX_H,
  INT_RX_L,
  INT_ST_H,
  INT_ST_L,
  INT_PR_H,
  INT_PR_L,
  INT_PRIORITY_MAX_NUM
} Uartd_int_pr_type_t;

/* Struct reproducing control register 0 */
/* Single fields listed from lowest memory address */
typedef struct
{
  uint8_t UFnSL       : 1;
  uint8_t UFnCL       : 1;
  uint8_t UFnPS       : 2;
  uint8_t UFnDIR      : 1;
  uint8_t UFnRXE      : 1;
  uint8_t UFnTXE      : 1;
  uint8_t RESERVED    : 1;
} Uartd_c0_reg_t;

/* Struct reproducing option register 0 */
/* Single fields listed from lowest memory address */
typedef struct
{
  uint8_t RDL : 1;
  uint8_t TDL : 1;
  uint8_t BLS : 3;
  uint8_t BTT : 1;
  uint8_t BRT : 1;
  uint8_t BRF : 1;
} Uartd_op0_reg_t;

/* Control registers */
/* They must be mapped onto device memory registers */
typedef struct
{
  Uartd_c0_reg_t   control0;
  Uartd_op0_reg_t  option0;
  uint16_t         control1;
  uint8_t          option1;
  uint8_t          option2;
  uint16_t         status;
  uint16_t         statusClear;
  uint8_t          txWaitRegB;
  uint8_t          RESERVED[3];
  uint8_t          idSetting;
  uint8_t          bufferReg[9];
  uint16_t         bufferCtl;
} Uartd_hw_reg_t;

/* Structure defining all the variables required from a uart channel */
typedef struct
{
  Uartd_hw_reg_t    *Registers;        /* Structure to map device registers  */
  uint8_t      *txReg_p;               /* Pointer to device transmission reg */
  uint8_t      *rxReg_p;               /* Pointer to device reception reg    */
  uint8_t      txBuffer[TX_BUFFER_LEN];/* Transmission buffer                */
  uint8_t      rxBuffer[RX_BUFFER_LEN];/* reception buffer                   */
  uint8_t      txHead;                 /* Point to head of tx buffer         */
  uint8_t      txTail;                 /* Point to tail of tx buffer         */
  uint8_t      rxHead;                 /* Point to head of rx buffer         */
  uint8_t      rxTail;                 /* Point to tail of rx buffer         */
  UARTD_Status_t          modStatus;   /* Module status                      */
  UARTD_HwErrorStatus_t   modError;    /* Module last error                  */
  void         (*RxDataCbk)(void);     /* Receiving Data callback            */
} Uartd_mod_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/* Mask to enable /disable LIN channel */
extern const uint8_t per0UartEnMasks_au8;

/* Mask to set internal interrupt HW */
extern uint8_t * const reg_if_apu8[INT_MAX_NUM];
extern uint8_t * const reg_mk_apu8[INT_MAX_NUM];
extern const uint8_t int_bit_mask_au8[INT_MAX_NUM];

/* Mask to set external interrupt HW */
extern uint8_t * const reg_ed_apu8[INT_EXT_MAX_NUM];
extern const uint8_t int_ext_bit_mask_au8[INT_EXT_MAX_NUM];

/* Set registry to basic setting of LIN device */
extern const Uartd_hw_reg_t ST_LINUART_BASIC_LIN_CFG;


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Set I/O ports of device */
void Uartd_InitPorts(void);   

/* Set priority for interrupt */
void Uartd_SetPriorityInterrupt(void);

/* Set device as LIN Master */
void Uartd_InitAsLinMaster(Uartd_hw_reg_t * reg);   

/* Enable / Disable LIN channel */
void Uartd_LinEnableCh(uint8_t chn_hnd, bool_t en); 

#endif /* end __UARTD_IS_PRESENT__ */

#endif  // __UARTD_H
