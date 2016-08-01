#ifndef __GLOBAL_H
#define __GLOBAL_H

/* ============================================================================ **
**                           B I T R O N    S p A                               **
** ============================================================================ **
**                      +++++++++++++++++++++++++++++                           **
**           Modulo:    +    global.h               +                           **
**                      +++++++++++++++++++++++++++++                           **
**                                                                              **
**                                                                              **
**                                                                              **
** ============================================================================ */

/* #define IDLE_CPU */

#include <string.h>
#include "typedefs.h"
#include "scheduler.h"
#include "global_config.h"

/* =========================       define            ========================== */

#ifndef NULL
  #define NULL              (0x0000u)
#endif

/* Usare solo per test/set bit e non per il return value di funzioni. tm470, tm471 */
#define ON                  (1u)
#define OFF                 (0u)

#ifndef TRUE
  #define TRUE              (1u)
#endif

#ifndef FALSE
  #define FALSE             (0u)
#endif

#define ENABLE              (1u)
#define DISABLE             (0u)

#define MCAL_LAYER          (1u)
#define DRVD_LAYER          (2u)
#define CTRL_LAYER          (3u)
#define PRES_LAYER          (4u)
#define APPL_LAYER          (5u)
#define SYST_LAYER          (6u)


/* Valori di ritorno delle funzioni/procedure che hanno esito boolean. tm470 */
#define RETURN_PASS         (0x01u)
#define RETURN_FAIL         (0xffu)
/* Segnala operazioni completate */
#define RETURN_END          (0x01u)
/* Segnala operazioni in corso (frazionamento esecuzione a 
   passi/stati per gestire attese/tempo cpu) */
#define RETURN_CONTINUE     (0xffu)


/**
 * Bitfield mask
 */
#define GBLS_MASK_BTF_0     (0x01u)
#define GBLS_MASK_BTF_1     (0x02u)
#define GBLS_MASK_BTF_2     (0x04u)
#define GBLS_MASK_BTF_3     (0x08u)
#define GBLS_MASK_BTF_4     (0x10u)
#define GBLS_MASK_BTF_5     (0x20u)
#define GBLS_MASK_BTF_6     (0x40u)
#define GBLS_MASK_BTF_7     (0x80u)

/**
 * Macro to set to TRUE a specific bit in a specific buffer
 */
#define GBLS_SetBitReg(Reg, BitPos)           ((Reg) |= (1U<<(BitPos)))

/**
 * Macro to set to FALSE a specific bit in a specific buffer
 */
#define GBLS_ClearBitReg(Reg, BitPos)         ((Reg) &= (~(1U<<(BitPos))))


/**
 * Macro to compute the subchannels number to apply the spreading strategy
 */
#define GBLS_SUB_CHAN_NMB(ChnNmb, ScanTick)\
  ( ((ChnNmb) / (ScanTick)) > ((ChnNmb) % (ScanTick)) ) ?\
    ((ChnNmb) / (ScanTick)) : (((ChnNmb) / (ScanTick))+1U)



#endif /* end __GLOBAL_H */
