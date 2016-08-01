/**
 * @file DRVD_typedefs.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the datatypes used by the Driver layer.
 *
 * @see www.Bitron.net
 */

#ifndef __CTRL_TYPEDEFS_H
#define __CTRL_TYPEDEFS_H


/**
 * Values for disable/enable of boolean signal
 */
typedef enum CTRL_EnSts_e
{
  CTRL_DISABLE = 0U,
  CTRL_ENABLE
} CTRL_EnSts_t;

/**
 * Enumerative for routines status
 */
typedef enum CTRL_ResSts_e
{
  CTRL_NOT_OK = 0U,
  CTRL_OK,
  CTRL_BUSY,
  CTRL_PAR_NOT_OK,
  CTRL_PAR_NOT_ENABLED
} CTRL_ResSts_t;


typedef enum CTRL_Fault_e
{
  CTRL_NOT_TESTED = 0U,
  CTRL_NO_FAULT,
  CTRL_SHORT_TO_BAT,
  CTRL_SHORT_TO_GND,
  CTRL_OPEN_LOAD,
  CTRL_OVER_VOLTAGE,
  CTRL_UNDER_VOLTAGE,
  CTRL_MSG_NOT_RECEIVED,
  CTRL_MSG_FAULTY,
  CTRL_GENERIC_FAULT,
  CTRL_PLAU_FAULT,
  CTRL_SIGNAL_ERROR,
  CTRL_SIGNAL_SIGNAL_INVALID,
  CTRL_BUS_OFF_FAULT,
  CTRL_DEVICE_FAULT,
  CTRL_NOT_PROGRAMMED,
  CTRL_OC_OR_STG,
  CTRL_OC_OR_STB,
  CTRL_BUTTON_STUCKED,
  CTRL_TOO_FEW_TRANS,
  CTRL_BAD_CONFIGURATION,
} CTRL_Fault_t;

typedef enum CTRL_State_e
{
  S_OFF = 0,
  S_ON,
  S_PREVIOUS,
  S_TOGGLE
} CTRL_State_t;

typedef enum
{
  HSD = 0,
  LSD,
} CTRL_DriverType_t;

typedef enum CTRL_FaultState_e
{
  CTRL_NOT_TESTED_NO_FAULT_STATE = 0,
  CTRL_NO_FAULT_STATE,
  CTRL_FAULT_CMD_ON_STATE,
  CTRL_FAULT_CMD_OFF_STATE,
  CTRL_FAULT_CMD_ALL_STATE,
  CTRL_NOT_TESTED_FAULT_CMD_OFF_STATE,
  CTRL_NOT_TESTED_FAULT_CMD_ON_STATE,
  CTRL_NOT_TESTED_FAULT_STATE,
  CTRL_NUM_FAULT_STATE
}CTRL_FaultState_t;


#endif /* end __CTRL_TYPEDEFS_H */
