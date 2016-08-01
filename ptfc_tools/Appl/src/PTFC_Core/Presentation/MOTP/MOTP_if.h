/*
 * MOTP_if.h
 *
 *  Created on: 22/set/2014
 *      Author: mmastrodonato
 */

#ifndef MOTP_IF_H_
#define MOTP_IF_H_


/* Dichiarazione dell'interfaccia del Layer */
#ifdef MOTP_IF_OWNER
  #define MOTP_EXTERN
#else
  #define MOTP_EXTERN   extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MOTP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Moved from private to public data to let applicative level set stall status after */
/* resetting the hall when reaching stroke                                           */
typedef enum MOTP_PosFkbDiag_e
{
  MOTP_FBK_NO_FAULT = 0,
  MOTP_UP_FW_STALL,
  MOTP_DW_BW_STALL,
  MOTP_FBK_FAULT,
} MOTP_PosFkbDiag_t;

typedef enum MOTP_Command_e
{
  MOTP_REQ_STOP = 0,
  MOTP_REQ_MOVE_UP_FW,
  MOTP_REQ_MOVE_DW_BW,
} MOTP_Command_t;

/* DF: spostato MOTP_STS_FAIL da posizione 5 a posiione 3 per allineamento con modello (vedi documento MOTA_ModelInterface_1.0.docx) */
typedef enum MOTP_MotStatus_e
{
  MOTP_STS_STOPPED = 0,
  MOTP_STS_MOVE_UP_FW,
  MOTP_STS_MOVE_DW_BW,
  MOTP_STS_FAIL,
  MOTP_STS_STROKE_UP_FW,
  MOTP_STS_STROKE_DW_BW
} MOTP_MotStatus_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/**
 * API to initialize the MOTP module. Call one time at system power on.
 * MOTP_Init
 *
 */
MOTP_EXTERN void             MOTP_Init(void);

/**
 * API to manage motor movements. Call periodically.
 * MOTP_Mgm
 *
 */
MOTP_EXTERN void             MOTP_Mgm(void);

/**
 * API to request a motor movement
 * MOTP_SetMovement
 *
 */
MOTP_EXTERN PRES_ResSts_t    MOTP_SetMovement(MOTP_Handle_t motor, MOTP_Command_t command);

/**
 * API to get the motor status
 * MOTP_GetMotorStatus
 *
 */
MOTP_EXTERN MOTP_MotStatus_t MOTP_GetMotorStatus(MOTP_Handle_t motor);

/**
 * API to get the position feedback status
 * MOTP_GetCmdArrayDiag
 *
 */
PRES_Fault_t                 MOTP_GetCmdArrayDiag(MOTP_CmdArrayHdl_t cmdArray);

/**
 * API to get the position feedback status
 * MOTP_GetCmdArrayDiagState
 *
 */
PRES_State_t                 MOTP_GetCmdArrayDiagState(MOTP_CmdArrayHdl_t cmdArray);

/**
 * API to get the position feedback diagnosis.
 * MOTP_GetPosFbkDiag
 *
 */
MOTP_EXTERN PRES_Fault_t     MOTP_GetPosFbkDiag(MOTP_Handle_t motor);

/**
 * API to get the position of Up/Fw stroke.
 * MOTP_GetUpFwStroke
 *
 */
//MOTP_EXTERN int16_t          MOTP_GetUpFwStroke(MOTP_Handle_t motor);

/**
 * API to get the position of Dw/Bw stroke.
 * MOTP_GetDwBwStroke
 *
 */
//MOTP_EXTERN int16_t          MOTP_GetDwBwStroke(MOTP_Handle_t motor);

/**
 * API to initialize the position of Up/Fw stroke.
 * MOTP_GetUpFwStroke
 *
 */
//MOTP_EXTERN void             MOTP_SetUpFwStroke(MOTP_Handle_t motor, int16_t strokeValue);

/**
 * API to initialize the position of Dw/Bw stroke.
 * MOTP_GetDwBwStroke
 *
 */
//MOTP_EXTERN void             MOTP_SetDwBwStroke(MOTP_Handle_t motor, int16_t strokeValue);

/**
 * API to initialize the fault state. Typically called after clear DTC.
 * MOTP_ClearFaults
 *
 */
MOTP_EXTERN void             MOTP_ClearFaults(void);

/**
 * API to manage the soft system shutdown.
 * MOTP_PwrOff
 *
 */
MOTP_EXTERN void             MOTP_PwrOff(void);

/**
 * @brief API to initialize MOTP hall position fail (ie: stored in EEPROM), 
 * called tipically at startup
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in] u08 the motor with position feedback in fail (ie: stored in EEPROM)
 * @param [out] none
 * @return None
 */
DRVD_RStatus_t MOTP_SetFault(u08 motor, PRES_Fault_t Fault);

/**
 * @brief API to initialize the fault state for a specific handle
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_ClearFault(MOTP_Handle_t hdl);

/**
 * @brief API to freeze MOTP state machine, the new commands received will be ignored until MOTP_Enable() is called
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_Disable(void);

/**
 * @brief API to enable MOTP to receive new commands
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_Enable(void);

MOTP_EXTERN void             MOTP_SetFaultEvent(MOTP_Handle_t motor, PRES_Fault_t Fault);
  
MOTP_EXTERN void             MOTP_SetCmdArrayFaultEvent(MOTP_CmdArrayHdl_t cmdArray, PRES_Fault_t Fault);

MOTP_EXTERN void             MOTP_StopRecovery(void);

/**
 * @brief API to initialize the fault state for a specific handle
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_ClearFault(MOTP_Handle_t hdl);

/**
 * @brief API to freeze MOTP state machine, the new commands received will be ignored until MOTP_Enable() is called
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_Disable(void);

/**
 * @brief API to enable MOTP to receive new commands
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_Enable(void);

/**
 * @brief API to enable or disable MOTP diagnosis on motors output.
 * The diagnosis on protection relays does not depend on this state
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
MOTP_EXTERN void MOTP_SetDiagState(bool state);

/**
 * @brief API to set the position feedback channel of a motor in stall, called for example when
 * setting a new position after reaching a stroke
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in] u08 the motor with position feedback in stall
 * @param [out] none
 * @return None
 */
MOTP_EXTERN DRVD_RStatus_t MOTP_SetStall(u08 motor, MOTP_PosFkbDiag_t stall);

/*______ E X T E R N A L - D A T A ___________________________________________*/

#endif /* MOTP_IF_H_ */
