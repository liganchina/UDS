/**
 * @file CAND_cfgIf.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:20:9
 * @brief File containing the user configuration of CAND module.
 * 
 * @see www.Bitron.net
 */
#ifndef __CAND_CFGIF_H
#define __CAND_CFGIF_H

#ifdef CAND_CFG_IF_OWNER
  #define CAND_CFG_IF_EXTERN
#else
  #define CAND_CFG_IF_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

/* Execption - not move */
#include "CMMD_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum CAND_TxMsgName_e
{
  CAND_STATUS_HMSM_HND = 0,
  CAND_NWM_HMSM_HND,
  CAND_CFG_DATA_CODE_RSP_HMSM_HND,
  CAND_DIAGNOSTIC_RESPONSE_HMSM_HND,
  CAND_TX_MSG_NMB
}CAND_TxMsgName_t;

typedef enum CAND_RxMsgName_e
{
  CAND_VIN_HND = 0,
  CAND_STATUS_CCAN3_HND,
  CAND_STATUS_CLIMATE2_HND,
  CAND_STATUS_LIN_HND,
  CAND_STATUS_MIRROR_HND,
  CAND_TRIP_A_B_HND,
  CAND_STATUS_BH_BCM1_HND,
  CAND_CFG_DATA_CODE_REQUEST_HND,
  CAND_DIAGNOSTIC_REQ_FUNC_BH_C2_HND,
  CAND_DIAGNOSTIC_REQUEST_HMSM_HND,
  CAND_NWM_BCM_HND,
  CAND_BCM_IGNITION_ON_COUNTER_HND,
  CAND_STATUS_BH_BCM2_HND,
  CAND_RX_MSG_NMB
}CAND_RxMsgName_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

#ifdef __CMMD_MULTI_DBC__
  #define CAND_DBC2_TX_MSG_NMB        (CAND_TX_MSG_NMB - CAND_DBC1_TX_MSG_NMB)
  #define CAND_DBC2_RX_MSG_NMB        (CAND_RX_MSG_NMB - CAND_DBC1_RX_MSG_NMB)
#endif

#endif /* __CAND_CFGIF_H */

/*______ E N D _____ (CAND_cfgIf.h) _________________________________________*/
