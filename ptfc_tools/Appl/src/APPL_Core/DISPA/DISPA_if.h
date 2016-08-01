/**
 * @file DISPA.c
 * @brief The DISPA module: public interface
 *
 * @version 0.1
 * @author Davide Fogliano (Polimatica S.r.l.)
 * @date 24 june 2015
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano           Polimatica S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 24/06/15   0.1  DF      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#ifndef __DISPA_IF_H__
#define __DISPA_IF_H__


/*_____ I N C L U D E - F I L E S ____________________________________________*/
#include "DISPA_cfgIf.h"

/* Module inhibition filter */
#ifdef __DISPA_IS_PRESENT__ 

/*_____ G L O B A L - D E F I N E ____________________________________________*/
#define DISPA_IDLE_CMD        0u

/* Dichiarazione dell'interfaccia del Layer */
#ifdef DISPA_IF_OWNER
	#define DISPA_EXTERN
#else
	#define DISPA_EXTERN		extern
#endif

/*_____ G L O B A L - T Y P E S ______________________________________________*/
typedef enum DISPA_IoState_e
{
    DISPA_IO_NOT_ACTIVE,
    DISPA_IO_SHORT_TERM_ADJ,
    //DISPA_IO_FREEZED //DF: future extension
} DISPA_IoState_t;

typedef enum DISPA_DispaState_e
{
  DISPA_STS_RUN,
  DISPA_STS_SUSPEND,
  DISPA_STS_ABORT,
  DISPA_STS_DISABLE,
  DISPA_STS_WAIT,
  DISPA_STS_NUM
}DISPA_State_t;

typedef enum DISPA_DispaEvent_e
{
  DISPA_EVT_RUN,
  DISPA_EVT_SUSPEND,
  DISPA_EVT_ABORT,
  DISPA_EVT_DISABLE,
  DISPA_EVT_ENABLE,
  DISPA_EVT_WAIT,
  DISPA_EVT_NUM
}DISPA_Event_t;

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/* Initialization function, fill private table and initialize all module internal variables */
DISPA_EXTERN void DISPA_Init(void);

/* Function to call periodically with fast period (typical 10 ms), call period in ms defined by DISPA_FAST_MGM_TICK_MS
 * This function manage: 
 *   - Update of fast changing model input
 *   - Call the model step function
 *   - Update low level SW according to model output and command requested (fast device)
*/
DISPA_EXTERN void DISPA_FastMgm(void);

/* Function to call periodically with slow period (typical 100 ms), call period in ms defined by DISPA_SLOW_MGM_TICK_MS
 * This function manages:
 *   - IO control timeout
 *   - Update of slow changing model input
 *   - Update output can/lin signal 
*    - TODO TANK: vedere cosa altro deve fare... */
DISPA_EXTERN void DISPA_SlowMgm(void);

/* Function used by a DISPA_Config.c routine to define the priority and order of activation*/ 
DISPA_EXTERN void DISPA_SetRequestedCmd(DISPA_handle_t hdl,u08 cmd);
DISPA_EXTERN void DISPA_SetExecutionBit(DISPA_handle_t hdl,bool exec);
DISPA_EXTERN u08  DISPA_GetState(DISPA_handle_t hdl);

/**
 * @brief This function is used to set DISPA state machine of the function according to the input event.
 * @author Francesco Talarico
 * @param [in] hdl is the function line, evt is the event transition of the state machine
 * @param [out] none
 * @return none
 */
DISPA_EXTERN void DISPA_SetEvent(DISPA_handle_t hdl, DISPA_Event_t evt);

DISPA_EXTERN void DISPA_SetWaitCycles(DISPA_handle_t hdl,u08 cycles);

/* Functions for IOControl management */

/* Set the max number of contemporary active IOControl, parameter max is checked versus DISPA_GROUP_MAX */
DISPA_EXTERN void DISPA_SetMaxContemporaryIoControl(u08 max);

/* Return 0 if OK else return the NACK to send to diagnstic client, see UDSA_if.h */
DISPA_EXTERN u08 DISPA_SetIoControl(DISPA_handle_t hdl, UDSA_IOControlSubf_t controlType, u08 command); 

DISPA_EXTERN bool DISPA_isIoControlActive(DISPA_handle_t hdl); 

DISPA_EXTERN bool DISPA_isModelIoControlActive(void); 

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/

/*_____ P R I V A T E - D A T A ______________________________________________*/

/*_____ P R I V A T E - M A C R O S __________________________________________*/

/*_____ P R I V A T E - F U N C T I O N S - P R O T O T Y P E S ______________*/

#endif
#endif
/*______ E N D _____ (DISPA_if.h) _____________________________________________*/
