/**
 * @file UCASE(MOTP.h)
 * @author mmastrodonato
 * @date 18/set/2014
 * @brief 
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 *                mmastrodonato             Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 18/set/2014        0.1     First revision
 */


#ifndef MOTP_H_
#define MOTP_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "PRES_if.h"
#include "MOTP_cbk.h"

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define MOTP_CMD_NOT_USED     (DOVFC_Handle_t)0xFF
#define MOTP_NUM_CMD          3U

/*______ G L O B A L - T Y P E S _____________________________________________*/

/* Module inhibition filter */
#ifdef __MOTP_IS_PRESENT__

typedef CTRL_Fault_t (*MOTP_GetDiag_t)  (u08 channel);  /* Get Diagnosis Fault     */
typedef PRES_State_t (*MOTP_SetState_t) (u08 channel, CTRL_State_t state);  /* Get Command State       */

typedef enum Motp_intCommand_e
{
  MOTP_CMD_IDLE,
  MOTP_CMD_UP_FW,
  MOTP_CMD_DW_BW,
  MOTP_CMD_BRAKE,
  MOTP_INT_CMD_NUM
}Motp_intCommand_t;

/* Typedef struttura da allocare in flash contenente i dati di configurazione statica */
typedef struct MOTP_CmdArrayTable_s
{
  uint8_t            CMD_HDL[MOTP_NUM_CMD];
  MOTP_SetState_t    STATE_FUN_PTR;
  MOTP_GetDiag_t     DIAG_FUN_PTR;
} MOTP_CmdArrayTable_t;

typedef struct MOTP_CfgTable_s
{
  IPOC_Channel_t     POS_FBK_HDL;
  MOTP_CmdArrayHdl_t CMD_ARRAY_HDL;
  uint16_t           FBK_POS_DIAG_TIME;
#if 0
  ADCC_InputChn_t    CURR_FBK_HDL;
#endif
} MOTP_CfgTable_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const MOTP_CfgTable_t      MOTP_CfgTable[MOTP_MAX_HDL];             /*Defined in MOTP_config.c */
extern const MOTP_CmdArrayTable_t MOTP_CmdArrayTable[MOTP_MAX_CMDA_HDL];   /*Defined in MOTP_config.c */

#endif /* end __MOTP_IS_PRESENT__ */

#endif /* MOTP_H_ */
