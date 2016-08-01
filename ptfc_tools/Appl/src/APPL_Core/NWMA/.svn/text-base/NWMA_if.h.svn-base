/**
 * @file NWMA_if.h
 * @brief Public interface of NetWork Management module in the Application layer.
 * In this module is implemented the network management FCA for NextGen network. 
 * The reference standard is N07320_ed5.
 * @n The main module features are:
 * @li Main FSM present in paragraph 3.4.2
 * @li DLL error FSM present in paragraph 3.5.7
 * @li Power management FSM present in paragraph 4.2 is implemented in LPMS module
 * </ul>
 *
 * @version 0.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 2 february 2015
 * @note (C) Copyright 2015 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| GB           Giuseppe Barberio         Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  -----------------------------------------------
| 02 feb 15  0.1  CC      First official release (whithout DLL error FSM)
| 28 may 15  0.2  GB CC   DLL error FSM completed
|-----------------------------------------------------------------------------
*/

#ifndef __NWMA_IF_H
#define __NWMA_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "NWMA_cfgIf.h"

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifdef NWMA_IF_OWNER
	#define NWMA_EXTERN
#else
	#define NWMA_EXTERN		extern
#endif

/*______ G L O B A L - T Y P E S _____________________________________________*/

/**
 * Enumerative type containing the values of paramater NET_STAT used
 * by API NM_IND() according to paragraph 3.2.2
 */
typedef enum NWMA_NetState_e
{
  /**@{*/
  NWMA_NET_OFF = 0u,    /**< NET_OFF value                */
  NWMA_NET_CHECK,       /**< NET_CHECK value              */
  NWMA_NET_STARTUP,     /**< NET_STARTUP value            */
  NWMA_NET_ON,          /**< NET_ON value                 */
  NWMA_NET_SILENT,      /**< NET_SDN value                */
  NWMA_NET_STATE_NMB    /**< Number of NET_STAT parameter */
  /**@}*/
}NWMA_NetState_t;

/**
 * Enumerative type containing the DLL error FMS states according
 * to paragraph 3.5.7
 */
typedef enum NWMA_DllState_e
{
  /**@{*/
  NWMA_SET_ERROR_ACTIVE = 0u, /**< "Set ERROR ACTIVE" state   */
  NWMA_SET_ERROR_PASSIVE,     /**< "Set ERROR PASSIVE" state  */
  NWMA_SET_BUS_OFF,           /**< "Set BUS OFF" state        */
  NWMA_BUS_OFF_STATE          /**< "BUS OFF State" state      */
  /**@}*/
}NWMA_DllState_t;

/**
 * Enumerative type cointaining the values of paramater DLL_STATUS
 * used by API NM_IND() according to paragraph 3.2.2
 */
typedef enum NWMA_DllSts_e
{
  /**@{*/
  NWMA_ERROR_ACTIVE = 0u,   /**< ERROR ACTIVE value   */
  NWMA_ERROR_PASSIVE,       /**< ERROR PASSIVE value  */
  NWMA_BUS_OFF              /**< BUS OFF value        */
  /**@}*/
}NWMA_DllSts_t;

/**
 * Enumerative type containing the values of paramater CMD used
 * by API NM_REQ() according to paragraph 3.2.2
 */
typedef enum NWMA_NetStateReq_e
{
  /**@{*/
  NWMA_NONE_REQ = 0,    /**< Empty value      */
  NWMA_NET_OFF_REQ,     /**< NET_OFF value    */
  NWMA_NET_CHECK_REQ,   /**< NET_CHECK value  */
  NWMA_NET_ON_REQ       /**< NET_ON value     */
  /**@}*/
}NWMA_NetStateReq_t;

/**
 * Enumerative type containing the values of paramater EOL_STATUS used
 * by API NM_REQ() according to paragraph 3.2.2
 */
typedef enum NWMA_EolStatus_e
{
  /**@{*/
  NWMA_EOL_PROG = 0,    /**< EOL_PROG value     */
  NWMA_EOL_NOT_PROG     /**< EOL_NOT_PROG value */
  /**@}*/
}NWMA_EolStatus_t;

/**
 * Struct type cointaining the fields of API NM_IND()
 * paramaters according to paragraph 3.2.2
 */
typedef struct NWMA_Ind_s
{
  /**@{*/
  NWMA_DllSts_t   DllStatus;        /**< DLL_STATUS parameter */
  NWMA_NetState_t CurrentNetState;  /**< NET_STAT parameter   */
  /**@}*/
}NWMA_Ind_t;

/**
 * Struct type cointaining the fields of API NM_REQ()
 * paramaters according to paragraph 3.2.2
 */
typedef struct NWMA_Req_s
{
  /* N07320_ed5, par. 3.2.2 - CMD parameter */
  NWMA_NetStateReq_t  NetStateReq;
  /* N07320_ed5, par. 3.2.2 - FAIL_STATUS parameter */
  bool_t              FailStatus;
  /* N07320_ed5, par. 3.2.2 - EOL_STATUS parameter */
  NWMA_EolStatus_t    EolStatus;
  /* N07320_ed5, par. 3.2.2 - CURR_FAIL_STATUS parameter */
  bool_t              CurrFailStatus;
}NWMA_Req_t;


/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * @brief Initialization routine for NWMA module. In this routine,
 * according to N07320_ed5 - par. 3.4.2, must generate the event E12
 * for states transition POWER_OFF --> NET_OFF
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_Init(void);

/**
 * @brief This handler routine call, according to current state, all event handlers
 * present in FMS matrix for all possible new state.
 * WARNING: It must be call in wakeup transition as fast as possible and at 
 * max every 20 ms in NET_ON state.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_FsmMgmt(void);

/**
 * @brief This API represent the API NM_REQ() described in par. 3.2.2 but
 * only for parameter CMD. This API is the interface to request by applicative
 * a FSM transition. The CMD parameter, as developed in type NWMA_NetStateReq_t,
 * can assume the following values:
 * @li NET_OFF: used for E1, E15
 * @li NET_CHECK: used for E10
 * @li NET_ON: used for E2, E7, E9, E14
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] NetStateReq represent the parameter CMD and its value are present
 * in type NWMA_NetStateReq_t
 * @param [out] None
 * @return APPL_ResSts_t
 * @retval APPL_OK: the request was accepted
 * @retval APPL_BUSY: there is another pending request
 * @retval APPL_PAR_NOT_OK: the input parameter is wrong
 */
NWMA_EXTERN APPL_ResSts_t NWMA_NmStateReq(NWMA_NetStateReq_t  NetStateReq);

/**
 * @brief This routine return the current net state according to parameter NET_STAT
 * of API NM_IND() present in par. 3.2.2
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_NetState_t
 * @retval NWMA_NET_OFF is the NET_OFF value of NET_STAT parameter
 * @retval NWMA_NET_CHECK is the NET_CHECK value of NET_STAT parameter
 * @retval NWMA_NET_STARTUP is the NET_STARTUP value of NET_STAT parameter
 * @retval NWMA_NET_ON is the NET_ON value of NET_STAT parameter
 * @retval NWMA_NET_SILENT is the NET_SDN value of NET_STAT parameter
 */
NWMA_EXTERN NWMA_NetState_t NWMA_GetNetState(void);

/**
 * @brief This routine call manages all events about DLL error management.
 * WARNING: It must be called at max every 50 ms in NET_ON state.
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
NWMA_EXTERN void NWMA_DllErrorMgmt(void);


#endif /* end __NWMA_IF_H */

/*_____E N D _____ (NWMA_if.h) _______________________________________________*/
