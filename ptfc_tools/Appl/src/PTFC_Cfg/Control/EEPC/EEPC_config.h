/**
 * @file EEPC.h
 * @author Michele Tedeschi, Matteo Mastrodonato
 * @date 10/03/2014
 * @brief File containing the configuration of EEPROM Driver.
 *
 * @see www.Bitron.net
 */

#ifndef __EEPC_CONFIG_H  /* MISRA C Rule 19.15: protect include file against repeated inclusion */
#define __EEPC_CONFIG_H


#define EEPROM_CLK_TICK         1U  /* periodo di chiamata EEPROM() */

/* TODO COBRA: da inserire il DIOD (setLevel) o SPID */
#define EEPROM_CS_PORT_OUT()    (PM6_bit.no3 = 0U)
#define EEPROM_CS               (P6_bit.no3)
/* l'ISRD per le callback multiple, tra cui il seriale dell'EE */
#define EEPROM_CS_INIT()		    CSI00_Start() /* Init SPI CSI00 */

#define CSI_TX_REGISTER         SDR00L
#define CSI_RX_REGISTER         SDR00L

#define EEPROM_SIZE             4096u /* EEPROM device: M95320 - 32K SPI Serial CMOS EEPROM (32 Kbit = 4 KB) */
#define EEPROM_PAGE_SIZE        32u


#endif  /* __EEPD_CONFIG_H */
