/**
 * @file TP_config.c
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:30:7
 * @brief File containing the user configuration of TP module.
 * 
 * @see www.Bitron.net
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| FRAT         Francesco Talarico        Bitron S.p.A.
|-----------------------------------------------------------------------------
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 02/07/15   0.1  FRAT     first draft
|-----------------------------------------------------------------------------
*/
#define NETP_CONFIG_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "TP.h"
#include "TP_config.h"

/* Module inhibition filter */
#ifdef __TP_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/


/*----------------------------------------------------------------------------*/
/*Name : TP_GetMsgNameHnd                                                     */
/*Role : Get the message name of the diagnostic response (drv/psg for example)*/
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
CAND_TxMsgName_t TP_GetMsgNameHnd(void)
{
  return(CAND_DIAGNOSTIC_RESPONSE_HMSM_HND);
}

/*----------------------------------------------------------------------------*/
/*Name : TP_GetUdsPhysMsgRequest                                              */
/*Role : Get the message name of the diagnostic request (drv/psg for example) */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
CAND_RxMsgName_t TP_GetUdsPhysMsgRequestHnd(void)
{
  return(CAND_DIAGNOSTIC_REQUEST_HMSM_HND);
}

/*----------------------------------------------------------------------------*/
/*Name : TP_GetUdsFuncMsgRequest                                              */
/*Role : Get the message name of the diagnostic request (drv/psg for example) */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
CAND_RxMsgName_t TP_GetUdsFuncMsgRequestHnd(void)
{
  return(CAND_DIAGNOSTIC_REQ_FUNC_BH_C2_HND);
}



#endif /* end __TP_IS_PRESENT__ */

/*______ E N D _____ (TP_config.c) _________________________________________*/
