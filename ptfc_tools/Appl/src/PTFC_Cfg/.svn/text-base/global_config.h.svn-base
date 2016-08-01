#ifndef __GLOBAL_CFG_H
#define __GLOBAL_CFG_H

/* ============================================================================ **
**                           B I T R O N    S p A                               **
** ============================================================================ **
**                      +++++++++++++++++++++++++++++                           **
**           Modulo:    +    global_config          +                           **
**                      +++++++++++++++++++++++++++++                           **
**                                                                              **
**                                                                              **
**                                                                              **
** ============================================================================ */

/**
 * Macro to set the debug pin
 */
#ifdef __PIN_DEBUG__
  #define GBLS_SetDebugPin(level)             (P1_bit.no0 = (level))
  #define GBLS_ToggleDebugPin()               (P1_bit.no0 ^= 1U)
#else
  #define GBLS_SetDebugPin(level)
#endif

/**
  * Generate a spike c.a. 80 us on debug pin
  */
#ifdef __PIN_DEBUG__
  #define GBLS_SpikeDebugPin()\
  {\
    uint8_t Delay;\
    GBLS_SetDebugPin(FALSE);\
    GBLS_SetDebugPin(FALSE);\
    for(Delay = 0; Delay < 100; Delay++)\
    {\
      GBLS_SetDebugPin(TRUE);\
    }\
    for(Delay = 0; Delay < 10; Delay++)\
    {\
      GBLS_SetDebugPin(FALSE);\
    }\
  }
#else
  #define GBLS_SpikeDebugPin()
#endif

#endif /* end __GLOBAL_CFG_H */
