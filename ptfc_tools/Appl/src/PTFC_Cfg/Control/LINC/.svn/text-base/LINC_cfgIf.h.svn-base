/**
 * @file LINC_cfgIf.h
 * @brief LIN control: source code of LIN module for control layer. 
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
| MAM          Matteo Mastrodonato       Bitron S.p.A.
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
| 27/06/2015 1.0  MAM     Configuration of message map for NAG/NAP F151M.
|                         LDF v1.1.
|-----------------------------------------------------------------------------
| 25/09/2015 0.3  GCO     Moved LINC_ReceptionTask function to UARTD interrupt,
|                         modified frame timeout callback, added priority 
|                         management
*/

#ifndef LINC_CFGIF_H_
#define LINC_CFGIF_H_

#ifdef __LINC_IS_PRESENT__

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Type to configure the LINC message map */
typedef enum LINC_MessageMap_e
{
  /* Message map */
  LINC_CMD_AUTH = 0,   /**/
  LINC_CMD_MEMORY ,    /**/
  LINC_CommandGTS,     /* GoTo Sleep Cmd - !!! DO NOT REMOVE !!! */
  LINC_MESSAGE_MAP_LEN
}LINC_MessageMap_t;


/********************************************************/
/**            Message Map types definition             */
/********************************************************/

typedef enum LINC_PanelAuth_e
{
  LINC_PANEL_DISABLED = 0,
  LINC_PANEL_ENABLED
} LINC_PanelAuth_t;

typedef enum LINC_Memory_e
{
  LINC_NO_MEM = 0,
  LINC_MEM1,
  LINC_MEM2,
  LINC_MEM3,
}LINC_Memory_t;

typedef enum LINC_PanelFail_e
{
  LINC_PANEL_NO_DEFECT = 0,
  LINC_PANEL_DEFECT,
}LINC_PanelDefect_t;

typedef enum LINC_ErrorBit_e
{
  LINC_NO_ERROR_BIT = 0,
  LINC_ERROR_BIT,
}LINC_ErrorBit_t;


/********************************************************/
/**        Message Map Structures definition            */
/********************************************************/

/* Message CMD_Authorization */
typedef struct LINC_cmdAuth_s
{
  LINC_PanelAuth_t   authMemoryPanel       :1;
  uint8_t            spareBits             :7;
}LINC_cmdAuth_t;

/* Message CMD_Memory */
typedef struct LINC_cmdMemory_s
{
  LINC_Memory_t      selectedMemory        :2;
  LINC_PanelDefect_t memoryGenDefect       :1;
  LINC_ErrorBit_t    Error_Bit_Memory      :1;
  uint8_t            spareBits             :4;
}LINC_cmdMemory_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/* FRAME CMD_Authorizations */
#define LINC_CMD_AUTH_LEN     1U
/* FRAME CMD MEMORY */
#define LINC_CMD_MEMORY_LEN   1U
/* FRAME 3C (GoToSleep request) */
#define LINC_FRAME_3C_LEN     8U

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

CTRL_Fault_t LINC_GetEltDiag(uint8_t dummy);

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* __LINC_IS_PRESENT__ */

#endif /* LINC_CFGIF_H_ */
