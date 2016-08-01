/**
 * @file NWMA.h
 * @brief Private interface of NetWork Management module in the Application layer.
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
| ---------  ---  ------  ----------------------------------------------------
| 02 feb 15  0.1  CC      First official release (whithout DLL error FSM)
| 28 may 15  0.2  GB CC   DLL error FSM completed
|-----------------------------------------------------------------------------
*/

#ifndef __NWMA_H
#define __NWMA_H

/* _____ I N C L U D E - F I L E S ___________________________________________*/

#include "APPL_if.h"

/* Module inhibition filter */
#ifdef __NWMA_IS_PRESENT__

#include "NWMA_config.h"
#include "NWMA_cbk.h"

/* _____ P R I V A T E - D E F I N E _________________________________________*/

/* _____ P R I V A T E - T Y P E S ___________________________________________*/

/**
 * Enumerative type containing the generic values for the signal
 * SysSts of a NWM generic message.
 */
typedef enum NWMA_NwmSysSts_e
{
  /**@{*/
  NWMA_NWM_SYS_WAKEUP       = 0x00u,  /**< Value for wakeup request       */
  NWMA_NWM_SYS_STAY_ACTIVE  = 0x01u,  /**< Value for stay active request  */
  NWMA_NWM_SYS_GO_TO_SLEEP  = 0x02u,  /**< Value for sleep request        */
  NWMA_NWM_SYS_NOT_DEFINED  = 0xFEu,  /**< Value a request not defined    */
  NWMA_NWM_SYS_NOT_RECEIVED = 0xFFu   /**< Value for none request         */
  /**@}*/
}NWMA_NwmSysSts_t;

/**
 * Enumerative type containing the generic values for the signal
 * ActiveLoad of a NWM generic message.
 */
typedef enum NWMA_ActiveLoadSlave_e
{
  /**@{*/
  NWMA_NO_ACTIVE_LOAD_IN_SLAVE = 0u,  /**< No active load for slave node  */
  NWMA_ACTIVE_LOAD_IN_SLAVE           /**< Active load for slave node     */
  /**@}*/
}NWMA_ActiveLoadSlave_t;

/* NWM flag callback notification array */
typedef enum
{
  NWMA_FSM_MGMT_REQ = 0u,
  NWMA_DLL_ERROR_MGMT,
  NWM_NOTIFY_NMB
}NWM_CbkNotificationSts_t;

/* _____ P R I V A T E - D A T A _____________________________________________*/

extern NWMA_DllState_t NWMA_DllState;
extern bool_t NWMA_NwmReceived[NWM_NOTIFY_NMB];
extern bool_t NWMA_E6Occour;
extern CAND_TxMsgName_t NWMA_MsmNwmType;

/* _____ P R I V A T E - M A C R O S _________________________________________*/

/* _____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S _____________*/

/**
 * @brief Configuration routine to initialize the configurable info
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void NWMA_InitCfg(void);

/**
 * @brief Check the SysSts signal receiving from master NWM message and
 * code specific value to generic value
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] NwmStsToCheck: SysSts signal of master NWM message to check.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: check if present a wakeup request
 * @li NWMA_NWM_SYS_STAY_ACTIVE: check if present a stay active request
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: check if present a go to sleep request
 * </ul>
 * @param [out] None
 * @return bool_t
 * @retval FALSE if the SysSts value to check isn't present
 * @retval TRUE if the SysSts valuen to check is present
 */
bool_t NWMA_CheckMasterNwmSysSts(NWMA_NwmSysSts_t NwmStsToCheck);

/**
 * @brief Check if master NWM message is received
 * @author Giuseppe Barberio - Bitron S.p.A.
 * @param [in] None
 * @li TRUE: NWM message received
 * @li FALSE: NWM message not received
 * </ul>
 * @param [out] None
 * @return bool_t
 * @retval TRUE if NWM message is received
 * @retval FALSE if NWM message is not received
 */
bool_t NWMA_CheckMasterNwmReceived(void);

/**
 * @brief Set the value for SysSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] SlaveNwmSts: SysSts signal of slave NWM message to set.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: set a wakeup status
 * @li NWMA_NWM_SYS_STAY_ACTIVE: set a stay active status
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: set a go to sleep status
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetSlaveNwmSysSts(NWMA_NwmSysSts_t SlaveNwmSts);

/**
 * @brief Get the value for SysSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_NwmSysSts_t
 * @retval NWMA_NWM_SYS_WAKEUP: return a wakeup status
 * @retval NWMA_NWM_SYS_STAY_ACTIVE: return a stay active status
 * @retval NWMA_NWM_SYS_GO_TO_SLEEP: return a go to sleep status
 */
NWMA_NwmSysSts_t NWMA_GetSlaveNwmSysSts(void);

/**
 * @brief Set the value for ActiveLoad signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] ActiveLoad: ActiveLoad signal of slave NWM message to set.
 * The possible value defined in type NWMA_ActiveLoadSlave_t are:
 * @li NWMA_NO_ACTIVE_LOAD_IN_SLAVE: set an active load not present
 * @li NWMA_ACTIVE_LOAD_IN_SLAVE: set an active load present
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetActiveLoadSlave(NWMA_ActiveLoadSlave_t ActiveLoad);

/**
 * @brief Get the value for ActiveLoad signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 * @return NWMA_ActiveLoadSlave_t
 * @retval NWMA_NO_ACTIVE_LOAD_IN_SLAVE: return an active load not present
 * @retval NWMA_ACTIVE_LOAD_IN_SLAVE: return an active load present
 */
NWMA_ActiveLoadSlave_t NWMA_GetActiveLoadSlave(void);

/**
 * @brief Set the value for DllSts signal of slave NWM message
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] DllSts: DllSts signal of slave NWM message to set.
 * The possible value defined in type NWMA_DllSts_t are:
 * @li NWMA_ERROR_ACTIVE: set DLL status in error active
 * @li NWMA_ERROR_PASSIVE: set DLL status in error passive
 * @li NWMA_BUS_OFF: set DLL status in busoff
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SetDllSts(NWMA_DllSts_t DllSts);

/**
 * @brief Send slave NWM message with a specific SysSts value passed
 * by input parameter
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] SlaveNwmSysSts: SysSts signal of slave NWM message to send.
 * The possible value defined in type NWMA_NwmSysSts_t are:
 * @li NWMA_NWM_SYS_WAKEUP: send a slave NWM message with SysSts in wakeup
 * @li NWMA_NWM_SYS_STAY_ACTIVE: send a slave NWM message with SysSts in stay active
 * @li NWMA_NWM_SYS_GO_TO_SLEEP: send a slave NWM message with SysSts in got to sleep
 * </ul>
 * @param [out] None
 * @return None
 */
void NWMA_SendNwmMsg(NWMA_NwmSysSts_t SlaveNwmSysSts);


#endif /* end __NWMA_IS_PRESENT__ */

#endif /* __NWMA_H */

/*_____E N D _____ (NWMA.h) __________________________________________________*/
