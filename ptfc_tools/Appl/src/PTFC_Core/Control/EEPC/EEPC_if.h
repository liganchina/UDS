/**
 * @file EEPC_if.h
 * @author Michele Tedeschi
 * @date 20??
 * @brief File containing the interface of EEPROM Driver.
 *
 * @see www.Bitron.net
 */

#ifndef __EEPC_IF_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __EEPC_IF_H

#ifndef EEPC_IF_OWNER
 #define EEPC_EXTERN extern
#else
 #define EEPC_EXTERN 
#endif

#include "EEPC_cfgIf.h"

/* Module inhibition filter */

// stati di esecuzione del driver seriale sincrona CSI
typedef enum
{
  CSI_IDLE,  // tm331. Il caso più frequente viene testato per prima.
  CSI_WAIT_EEPROM
}EEPC_StatiCSI;

// attenzione: se la EEPROM ha indirizzo a 8 bit bisogna mandare solo
//EEPROM_READ_ADDRESS_SEND_HIGH/EEPROM_WRITE_ADDRESS_SEND_HIGH
// stati di esecuzione del driver EEPROM SPI
typedef enum
{
  EEPROM_IDLE,

  EEPROM_READ_REQUEST,        // STATO ESTERNO: richiesta di accesso in lettura
  EEPROM_READ_ADDRESS_SEND_HIGH,
  EEPROM_READ_ADDRESS_SEND_LOW,
  EEPROM_READ_CLOCK_OUT,
  EEPROM_READ,
  EEPROM_READ_CRC,
  EEPROM_READ_END,

  EEPROM_WRITE_REQUEST,       // STATO ESTERNO: richiesta di accesso in scrittura
  EEPROM_WRITE_ENABLE,
  EEPROM_WRITE_ADDRESS_SEND_HIGH,
  EEPROM_WRITE_ADDRESS_SEND_LOW,
  EEPROM_WRITE,
  EEPROM_PROGRAM,
  EEPROM_STATUS_REQUEST,      // STATO INTERNO, attesa di fine programmazione
  EEPROM_RDSR_CLOCK_OUT,
  EEPROM_STATUS_CHECK,

  EEPROM_WRITE_SR,
  EEPROM_WRITE_PROTECTION,

  // valori possibili di StatoEEPROM a fine operazione di accesso in READ/WRITE: lasciare in fondo !
  // (testati con StatoEEPROM >= EEPROM_READ_GOOD)
  EEPROM_READ_GOOD,
  EEPROM_WRITE_GOOD,
  EEPROM_READ_FAIL,
  EEPROM_WRITE_FAIL,
  EEPROM_BAD_PARAMETERS
}EEPC_StatiEEPROM;


extern __saddr EEPC_StatiCSI      EEPC_StatoCSI;
extern __saddr EEPC_StatiEEPROM   EEPC_StatoEEPROM;

/**
 * @brief This function Initializes the EEPROM driver.
 * @note  It must be called only one time at the system init.
 * @see EEPROM()
 */
EEPC_EXTERN void EEPC_Init(void);

/**
 * @brief This function manages the SPI communication with the chip.
 * @note  It must be called to start SPI protocol and in the SPI end of transmission interrupt
 */
EEPC_EXTERN void EEPC_Mgm(void);

#if EEPROM_BUFFER_SIZE < 255U  // tm471
/**
 * @brief This function reads data from eeprom.
 * @param ramStartAddress The address of the destination of data (ram)
 * @param byteNumber data size to read
 * @param eepromStartAddress The address of source data (eeprom)
 */
EEPC_EXTERN EEPC_StatiEEPROM EEPC_Read(void *ramStartAddress, u08 byteNumber, u16 eepromStartAddress, bool readRaw);

/**
 * @brief This function writes data to eeprom.
 * @param ramStartAddress The address of the source of data (ram)
 * @param byteNumber data size to write
 * @param eepromStartAddress The address of destination data (eeprom)
 */
EEPC_EXTERN EEPC_StatiEEPROM EEPC_Write(void *ramStartAddress, u08 byteNumber, u16 eepromStartAddress, bool writeRaw);

#else
/**
 * @brief This function reads data from eeprom.
 * @param ramStartAddress The address of the destination of data (ram)
 * @param byteNumber data size to read
 * @param eepromStartAddress The address of source data (eeprom)
 */

EEPC_EXTERN EEPC_StatiEEPROM EEPC_Read(void *ramStartAddress, u16 byteNumber, u16 eepromStartAddress, bool readRaw);
/**
 * @brief This function writes data to eeprom.
 * @param ramStartAddress The address of the source of data (ram)
 * @param byteNumber data size to write
 * @param eepromStartAddress The address of destination data (eeprom)
 */
EEPC_EXTERN EEPC_StatiEEPROM EEPC_Write(void *ramStartAddress, u16 byteNumber, u16 eepromStartAddress, bool writeRaw);

#endif

#endif  // __EEPC_IF_H
