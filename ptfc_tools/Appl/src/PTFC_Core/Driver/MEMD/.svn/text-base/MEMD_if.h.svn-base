/**
 * @file MEMD.c
 * @brief MEMory test Driver. This module performs ram test and stack overflow
 * underflow check.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @date 20 October  2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */

#ifndef MEMD_IF_H_
#define MEMD_IF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef MEMD_IF_OWNER
 #define MEMD_EXTERN
#else
 #define MEMD_EXTERN  extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief This function Initializes the MEMD driver.
 * @return void
 * @note It must be called only one time at the system init BUT AFTER MEMD_RamTest.
 */
MEMD_EXTERN void MEMD_Init(void);

/**
 * @brief This function performs data RAM test driver. The RAM area to test (segments) is
 * defined in module configuration (MEMD_config.h).
 * @return void
 * @note It must be called only one time at the system init.
 */
MEMD_EXTERN void MEMD_RamTest(void);

/**
 * @brief Runtime stack overflow/underflow check. If an overflow/underflow
 * is detected the module will force a reset.
 * @return void
 * @note It must be called periodically.
 */
MEMD_EXTERN void MEMD_StackCheck(void);

/**
 * @brief This function returns the Flash test result.
 * @return DRVD_RStatus_t
 * @retval MS_NOT_OK FLASH test failed
 * @retval MS_OK The FLASH test passed
 */
MEMD_EXTERN DRVD_RStatus_t MEMD_GetFlashTestResult(void);

/**
 * @brief This function returns the Ram test result.
 * @return DRVD_RStatus_t
 * @retval MS_NOT_OK RAM test failed
 * @retval MS_OK The RAM test passed
 */
MEMD_EXTERN DRVD_RStatus_t MEMD_GetRamTestResult(void);

/**
 * @brief This function returns the stack peak usage in percent
 * @return u16 stack peak load (0.1%/bit)
 */
MEMD_EXTERN u16 MEMD_GetStackPeakLoad(void);
#endif /* MEMD_IF_H_ */
