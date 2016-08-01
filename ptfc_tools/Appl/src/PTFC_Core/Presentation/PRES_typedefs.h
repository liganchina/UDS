/*
 * PRES_typedefs.h
 *
 *  Created on: 27/mag/2013
 *      Author: Matteo MASTRODONATO
 */

#ifndef PRES_TYPEDEFS_H_
#define PRES_TYPEDEFS_H_


/**
 * Enumerative for routines status
 */
typedef enum PRES_ResSts_e
{
  PRES_NOT_OK = 0,
  PRES_OK,
  PRES_BUSY,
  PRES_PAR_NOT_OK
}PRES_ResSts_t;


typedef enum PRES_KeyStatus_e
{
  KEYA_OFF_STATUS = 0,
  KEYA_ON_STATUS,
  KEYA_CRANK_STATUS,
  /* KEYA_ON_ENGINE_ON, */
  ANY_KEY
}PRES_KeyStatus_t;

typedef enum
{
  PRES_NOT_TESTED            = CTRL_NOT_TESTED,
  PRES_NO_FAULT              = CTRL_NO_FAULT,
  PRES_SHORT_TO_BAT          = CTRL_SHORT_TO_BAT,
  PRES_SHORT_TO_GND          = CTRL_SHORT_TO_GND,
  PRES_OPEN_LOAD             = CTRL_OPEN_LOAD,
  PRES_OVER_VOLTAGE          = CTRL_OVER_VOLTAGE,
  PRES_UNDER_VOLTAGE         = CTRL_UNDER_VOLTAGE,
  PRES_MSG_NOT_RECEIVED      = CTRL_MSG_NOT_RECEIVED,
  PRES_MSG_FAULTY            = CTRL_MSG_FAULTY,
  PRES_GENERIC_FAULT         = CTRL_GENERIC_FAULT,
  PRES_PLAU_FAULT            = CTRL_PLAU_FAULT,
  PRES_SIGNAL_ERROR          = CTRL_SIGNAL_ERROR,
  PRES_SIGNAL_SIGNAL_INVALID = CTRL_SIGNAL_SIGNAL_INVALID,
  PRES_BUS_OFF_FAULT         = CTRL_BUS_OFF_FAULT,
  PRES_DEVICE_FAULT          = CTRL_DEVICE_FAULT,
  PRES_NOT_PROGRAMMED        = CTRL_NOT_PROGRAMMED,
  PRES_OC_OR_STG             = CTRL_OC_OR_STG,
  PRES_OC_OR_STB             = CTRL_OC_OR_STB,
  PRES_BUTTON_STUCKED        = CTRL_BUTTON_STUCKED,
  PRES_TOO_FEW_TRANS         = CTRL_TOO_FEW_TRANS,
  PRES_BAD_CONFIGURATION     = CTRL_BAD_CONFIGURATION,
  /* DO NOT REMOVE FOLLOWING LINE */
  PRES_MAX_FAULT,
} PRES_Fault_t;


typedef CTRL_State_t PRES_State_t;


/* TODO MAM: spostare i fault dal pres al control, o inventarsi un qualche re-map */

/******************************************************/

typedef enum
{
  PRES_WR_IDLE = 0,
  PRES_WR_TERMINATED,
  PRES_WR_NOT_TERMINATED
} PRES_WriteStatus_t;


typedef struct PRES_Stroke_s
{
  int16_t upFwVal;
  uint8_t upFwCnt;
  int16_t dwBwVal;
  uint8_t dwBwCnt;
} PRES_Stroke_t;

/**
 * Values for disable/enable of boolean signal
 */
typedef enum PRES_EnSts_e
{
  PRES_DISABLE = 0,
  PRES_ENABLE
} PRES_EnSts_t;

#endif /* PRES_TYPEDEFS_H_ */
