/**
 * @file TLRP_config.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the user configuration of TLRP Driver.
 *
 * @see www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Mastrodonato Matteo       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 15/06/2013 1.0  MM      First release
|-----------------------------------------------------------------------------
| 09/10/2014 1.1  CC      New management of the callback: deleted input parameter
|-----------------------------------------------------------------------------
*/

#ifndef __TLRP_CONFIG_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __TLRP_CONFIG_H

/*
============================================================================
                           B I T R O N    S.p.A.
============================================================================

    Modulo:     TLRP - Timer Low Resolution Driver
    Progetto:   -
    Descrizione:
        Gestione di N timer a bassa risoluzione (basato su task)
		File modificabile dall'utente.

    Specifica di riferimento:

    Requisiti implementati:
        - Configurazione del periodo di chiamata della funzione Tick del timer.

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [1]     [2012-11-21]  [M.Mastrodonato]          1ma implementazione

============================================================================*/

/* Inclusione delle interfacce per le Callback */
#include "NWMA_cbk.h"
#include "DDMP_cbk.h"
#include "UDSA_cbk.h"
#include "FVMP_cbk.h"
#include "KEYA_cbk.h"
#include "MOTP_cbk.h"
#include "NETP_cbk.h"
#include "DISPA_cbk.h"
#include "VF608_cbk.h"

/*********************************************
*   CONFIGURAZIONE STATICA TIMER LOW RES 
*********************************************/

#define TLRP_FAST_TICK  1U    // periodicità di chiamata della TLRP_FastMgm in [ms]
#define TLRP_SLOW_TICK  100U  // periodicità di chiamata della TLRP_SlowMgm in [ms]


#endif  /* end __TLRP_CONFIG_H */
