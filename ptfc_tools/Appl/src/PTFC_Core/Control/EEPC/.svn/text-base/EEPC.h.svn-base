/**
 * @file EEPC.h
 * @author Michele Tedeschi
 * @date 20??
 * @brief File containing the header prototypes of EEPROM Driver.
 *
 * @see www.Bitron.net
 */

#ifndef __EEPC_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __EEPC_H

#include "CTRL_if.h"

/* Module inhibition filter */

#include "EEPC_config.h"


// EEPROM Chip Select   is active low
// EEPROM Write Protect is active low

#if defined EEPROM_FAILURE

  #define EEPROM_CS_ON()      (EEPROM_CS=1U)// forzatura per provare errore EEPROM. tm317

#else

  #define EEPROM_CS_ON()      (EEPROM_CS=0U)
#endif

#define EEPROM_CS_OFF()     (EEPROM_CS=1U)

#define EEPROM_PAGE_MASK    (EEPROM_PAGE_SIZE-1u)

#endif  // __EEPC_H
