#ifndef __EEPP_CONFIG_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __EEPP_CONFIG_H


/*==============================================================================
                           B I T R O N    S.p.A.
================================================================================

    Modulo:     EEPP_config.h
    Progetto:   generico
    Descrizione:
        File di configurazione: deve contenere tutti e i soli parametri 
        configurabili del modulo

    Specifica di riferimento: 

    Requisiti implementati:

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [0]     [2012-03-05]  [M.Mastrodonato]          1^ implementazione

==============================================================================*/


/*******************************************************************************
*
*  EEPP Static Configuration
*
********************************************************************************/

/* Includere i file di interfaccia verso gli altri moduli */
#include "UDSA_cbk.h"


#define EEPP_TICK               1U      // Periodo di chiamata task EepromManager() [ms]
#define EEPP_TIMEOUT            200U    // timeout lettura/scrittura [ms]

#define EEPP_QUEUE_DIM          10U

#define EE_CRC_SIZE             1U      /* Dimensione del CRC calcolato dal driver eeprom di basso livello */

#define EE_PAD                  11U     /* Padding per terminare la riga di eeprom (32byte) */

#define ENABLE_MIRRORING        FALSE   /* Abilita la fuzionalità di mirroring dei dati EEPROM
                                           Da configurare nella tabella in EEPP_config.c
                                        */

/************************** EEPP Static Callback Mapping   *******************/

/* Driver Eeprom initialization (called before Eeprom loading in RAM) - PSEUDO_INITIALIZATION */
#define   EEPP_PRE_P_INIT()   EEPP_Default()        /* EEPP_Default() if not used */
#define   EEPP_POST_P_INIT()  EEPP_Default()        /* EEPP_Default() if not used */

/* Driver Eeprom initialization (called before Eeprom loading in RAM) - INITIALIZATION */
#define   EEPP_PRE_INIT()     EEPP_Default()        /* EEPP_Default() if not used */

#define   EEPP_POST_INIT()   EEPP_UserInit();\
                             UDSA_WriteProgrammingStatus();\
                             FUNP_WriteNewIDs()

/* Gestione handler eeprom (prima di gestire l'n-esimo elemento in coda) */
#define   EEPP_PREMGM()       EEPP_Default()    			 /* EEPP_Default() if not used */

/* Gestione evntuali driver di safety (WatchDog, ecc...) */
#define   EEPP_SAFETY_ACK()   LPMS_RefreshAllWatchDog()	 /* EEPP_Default() if not used */

/***********************   EEPP Config Prototypes  ********************/
extern void EEPP_UserInit(void);
void EEPP_ShutdownSaveReq(void);

#endif  /* __EEPROM_MANAGER_CONFIG_H */
