/**
 * @file EXMMA_config.h
 * @brief EXternal Mirrors Management module
 * @li ...
 * </ul>
 *
 * @version 0.1
 * @author De Stephanis Alessio (Intecs S.p.A.)
 * @date 31/03/2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/************************** (C) Copyright 2014 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| ADS          De Stephanis Alessio       Intecs S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 31/03/2015 0.1  ADS     First release
|
*/

#define EXMMA_CFG_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "EXMMA.h"
#include "EXMMA_config.h"

/* Module inhibition filter */
#ifdef __EXMMA_IS_PRESENT__

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function resets the signals for mirror movement request and buzzer activation request
 * @author De Stephanis Alessio
 * @param [in] None
 * @param [out] None
 * @return None
 */
void EXMMA_SendCbk(void)
{
  /* Reset mirror movement command */
  EXMMA_SET_MIRROR_MOVEMENT_CMD(CMMD_NOT_READY);
  
  /* Reset buzzer notification */
  EXMMA_SET_BUZZER_NOTIFICATION(0U);
}

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* end __EXMMA_CONFIG_H */
