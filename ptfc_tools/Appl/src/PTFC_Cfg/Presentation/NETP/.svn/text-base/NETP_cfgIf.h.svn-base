/**
 * @file NETP_cfgIf.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 26/03/2015 - 14:30:8
 * @brief File containing the user configuration of NETP module.
 * 
 * @see www.Bitron.net
 */
#ifndef __NETP_CFGIF_H
#define __NETP_CFGIF_H

#ifdef NETP_CFG_IF_OWNER
  #define NETP_CFG_IF_EXTERN
#else
  #define NETP_CFG_IF_EXTERN   extern
#endif

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define NETP_TIMEOUT_SERVICE

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum
{
  NETP_BUS_OFF_HND = 0,
  NETP_NODE_MUTE_HND,
  NETP_ELECTRIC_FAIL_HND,
}NETP_CanDTC_t;

/**
 * @brief The entries of this enum should be used in NETP_RxNetMonitor table (NETP_config.c)
 * @brief to configure Faulty/Absent diagnostic enable or disable. Use NETP_ABS_FAULTY_DISABLE
 * @brief if no diagnosis should be performed on some messages
 */
typedef enum NETP_Af_e
{
  /***************************/
  /* INSERT HERE ALL HANDLES */
  /***************************/

  NETP_BCM_ABS_FAULTY = 0,
  NETP_IPC_ABS_FAULTY,
  NETP_ACM_ABS_FAULTY,

  /*********************************/
  /* DO NOT REMOVE FOLLOWING LINES */
  /*********************************/
  NETP_ABS_FAULTY_DISABLE,
  NETP_ABS_FAULTY_MAX_HDL,
}NETP_Af_t;

#ifdef NETP_TIMEOUT_SERVICE

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_CFG_DATA_CODE_REQUEST_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_DIAGNOSTIC_REQ_FUNC_BH_C2_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_DIAGNOSTIC_REQUEST_HMSM_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_NWM_BCM_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_BCM_IGNITION_ON_COUNTER_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_BH_BCM2_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_VIN_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_CCAN3_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_CLIMATE2_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_LIN_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_MIRROR_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_TRIP_A_B_Rec(void);

  /**
   * @brief Message recovery function on message absent event
   */
void NETP_STATUS_BH_BCM1_Rec(void);


#endif /* NETP_TIMEOUT_SERVICE */ 

#endif /* __NETP_CFGIF_H */

/*______ E N D _____ (NETP_cfgIf.h) _________________________________________*/
