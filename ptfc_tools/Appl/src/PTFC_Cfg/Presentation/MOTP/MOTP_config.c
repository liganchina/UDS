/********************************************************************************/
/* @F_PROJECT:          MSM TESLA                                               */
/* F_NAME:              MOTP_cfgIf                                              */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FF3                                  */
/* F_CREATION_DATE:     21/oct/2014                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|------------------------------------------------------------------------------
|                A U T H O R   I D E N T I T Y
|------------------------------------------------------------------------------
| Initials      Name                      Company
| --------      ---------------------     -------------------------------------
| MM            Matteo MASTRODONATO       Bitron S.p.A.
|------------------------------------------------------------------------------
|                R E V I S I O N   H I S T O R Y
|------------------------------------------------------------------------------
| Date         Ver  Author  Description
| -----------  ---  ------  ----------------------------------------------------
| 21/oct/2014  0.1  MM      First draft
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MOTP.h"
#include "MOTP_config.h"

/* Module inhibition filter */
#ifdef __MOTP_IS_PRESENT__

#define MOTP_CFGIF_OWNER

/*______ L O C A L - T Y P E S _______________________________________________*/

#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE) // TODO TANK: verificare soglie!
  #define OVER_CURRENT_THRESOLD_LO  450U  /* 2.20V ~ 24A */
  #define OVER_CURRENT_THRESOLD_HI  471U  /* 2.30V ~ 25A */
  #define RELE_RECOVERY_LIMIT_CURR  563U  /* 2.75V ~ 30A */
#endif

#define MOTP_STROKE_DETECT_THRES   3U

/*______ G L O B A L - D A T A _______________________________________________*/


const MOTP_CmdArrayTable_t MOTP_CmdArrayTable[MOTP_MAX_CMDA_HDL] = {
  /* MOTP_CMDA_HDL           CMD_HDL[0]            CMD_HDL[1]            CMD_HDL[2]                STATE_FUN_PTR                    DIAG_FUN_PTR   */
  /* MOTP_ArraySlideTilt */ {{DOVFC_CmdSlideFd   , DOVFC_CmdTiltUp,      DOVFC_CmdTiltSlideCom  }, (MOTP_SetState_t)DOVFC_SetState, (MOTP_GetDiag_t)DOVFC_GetDiag },
  /* MOTP_ArrayLiftBack  */ {{DOVFC_CmdLiftUp    , DOVFC_CmdBackrFd,     DOVFC_CmdLiftBackrCom  }, (MOTP_SetState_t)DOVFC_SetState, (MOTP_GetDiag_t)DOVFC_GetDiag },
  /* MOTP_ArraySpare     */ {{DOVFC_CmdSpareMotDw, DOVFC_CmdSpareMotCom, MOTP_CMD_NOT_USED      }, (MOTP_SetState_t)DOVFC_SetState, (MOTP_GetDiag_t)DOVFC_GetDiag },
};


const MOTP_CfgTable_t MOTP_CfgTable[MOTP_MAX_HDL] = {
  /* MOTP_HDL              POS_FBK_HDL      CMD_ARRAY_HDL       FBK_POS_DIAG_TIME */
  /* MOTP_SLIDE     */   { IPOC_Slide    ,  MOTP_ArraySlideTilt ,    300U},
  /* MOTP_TILT      */   { IPOC_Tilt     ,  MOTP_ArraySlideTilt ,    300U},
  /* MOTP_LIFT      */   { IPOC_Lift     ,  MOTP_ArrayLiftBack  ,    300U},
  /* MOTP_BACK_R    */   { IPOC_Backres  ,  MOTP_ArrayLiftBack  ,    300U},
  /* MOTP_SPARE     */   { IPOC_Spare    ,  MOTP_ArraySpare     ,    300U}
};


const CTRL_State_t MOTP_MovTable[MOTP_MAX_HDL][MOTP_INT_CMD_NUM][MOTP_NUM_CMD] = {
  /* Motor/Movement/Relay  */
  /*                   CMD_1      CMD_2      CMD_3       */
  /* SLIDE IDLE  */ {{ S_OFF,     S_OFF,     S_OFF,      },
  /* SLIDE FW    */  { S_OFF,     S_ON,      S_ON,       },
  /* SLIDE BW    */  { S_ON,      S_OFF,     S_OFF,      },
  /* SLIDE BRK   */  { S_ON,      S_ON,      S_ON,       }},
  
  /* TILT OFF    */ {{ S_OFF,     S_OFF,     S_OFF,      },
  /* TILT UP     */  { S_ON,      S_OFF,     S_ON,       },
  /* TILT DW     */  { S_OFF,     S_ON,      S_OFF,      },
  /* TILT BRK    */  { S_ON,      S_ON,      S_ON,       }},
  
  /* LIFT OFF    */ {{ S_OFF,     S_OFF,     S_OFF,      },
  /* LIFT UP     */  { S_OFF,     S_ON,      S_ON,       },
  /* LIFT DW     */  { S_ON,      S_OFF,     S_OFF,      },
  /* LIFT_BRK    */  { S_ON,      S_ON,      S_ON,       }},
  
  /* BACK OFF    */ {{ S_OFF,     S_OFF,     S_OFF,      },
  /* BACK FW     */  { S_ON,      S_OFF,     S_ON,       },
  /* BACK BW     */  { S_OFF,     S_ON,      S_OFF,      },
  /* BACK BRK    */  { S_ON,      S_ON,      S_ON,       }},
  
  /* SPARE IDLE  */ {{ S_OFF,     S_OFF,     S_PREVIOUS, },
  /* SPARE UP    */  { S_ON,      S_OFF,     S_PREVIOUS, },
  /* SPARE DW    */  { S_OFF,     S_ON,      S_PREVIOUS, },
  /* SPARE BRK   */  { S_ON,      S_ON,      S_PREVIOUS, }},
};


/*______ P R I V A T E - D A T A _____________________________________________*/
/* These variable holds current offset for slide an other motors current sensig,
   they are set by Motp_SetCurrentOffset() function */
static uint16_t   Motp_MotorsCurrOffset;
bool_t            Motp_CurrOffsetAcquired;

/*______ L O C A L - D A T A _________________________________________________*/

//int16_t     MOTP_targetPos[MOTP_MAX_HDL];
//bool_t      MOTP_goToPos[MOTP_MAX_HDL];
//StatiMotore MOTP_motorStatus[MOTP_MAX_HDL];
uint8_t     MOTP_lastCmdMotor[MOTP_MAX_HDL];


/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/
void Motp_SetCurrentOffset(void);
uint16_t Motp_GetCurrentWithOffset(ADCC_InputChn_t ADCC_hdl, uint16_t offset);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 *
 *  This function is called once at power on. It initializes the config
 *  module local paremeters.
 *
 */
void MOTP_CfgInit(void)
{
  MOTP_Handle_t motor;

  for(motor = (MOTP_Handle_t)0u; motor < MOTP_MAX_HDL; motor++)
  {
    MOTP_lastCmdMotor[motor] = CMD_FERMO;

    /* Init Hall counters */
    IPOC_SetCounter(MOTP_CfgTable[motor].POS_FBK_HDL, &EERAM_ContatoreHall[MOTP_CfgTable[motor].POS_FBK_HDL]);
  }
  
  /* Prepare the first acquisition of current offset (3 step): */
  /* 1) Set the Motp_CurrOffsetAcquired to indicates that 
     the first offset acquisition is not yet done */
  Motp_CurrOffsetAcquired = FALSE;
  /* 2) Enable Current sense  amplifier pwr supply */
  FUNP_HallActive();
  /* 3) Start the timer for triggering of OpenProtectionRel() */
  TLRP_SetSlow(TLRP_ProtRelTimeout);
}

/**
 *  Called by stroke reached event
 *  It writes the stroke values in eeprom.
 *
 */
void MOTP_StrokeEvtMgm(MOTP_Handle_t motor)
{

}

#if (MOTP_RECOVERY_IDLE_BRAKE_EN == TRUE)
  /**
  *
  * This function is the callback of FMVP monitor Currents Handle
  * Check if there are the condition for run the fault recovery strategy
  *
  * */
  void MOTP_OverCurrentEvent(FVMP_Handle_t currFbkHdl, PRES_Fault_t fault, bool FaultDestructive)
  {
    MOTP_CmdArrayHdl_t i;
    uint16_t actualCurrent;
    
    /* Actuate recovery only if the fault is present */
    if(fault != PRES_NO_FAULT)
    {
      actualCurrent = ADCC_GetChnAvrgData(ADCC_MotorsSens);
    
      if (actualCurrent < RELE_RECOVERY_LIMIT_CURR)
      {
        /* set fault for all the motor arrays*/
        for(i = (MOTP_CmdArrayHdl_t)0u; i < MOTP_MAX_CMDA_HDL ; i++)
        {
             MOTP_SetCmdArrayFaultEvent(i,fault);
        }
      }
      else
      {
        /*  Current too HIGH, arc generated on opening could cause damage to the contacts,
        wait fuse intervention. */
      }
    }
  }
#endif /* MOTP_RECOVERY_IDLE_BRAKE_EN = TRUE */

void MOTP_OpenProtRel(void)
{
  /* In this condition we can always acquie the cuurent offset */
  Motp_SetCurrentOffset();
    
  /* Timeout elapsed: open main relay */
  DOVFC_SetState(DOVFC_CmdRelProtEN, S_OFF);
  /* Disable Hall sensors pwr supply */
  FUNP_HallInactive();
  /* remove eventually present recovery */
  MOTP_StopRecovery();
  /* disable diagnosis on all motors' output since diagnosis should be performed only
   * on protection relay */
  MOTP_SetDiagState(FALSE);
}

void MOTP_SavePosition(void)
{
  /* Save current positions */
  EEPP_WriteData(EEPP_HDL_ContatoreHall, NULL);

  /* Motors positions correctly saved */
  EERAM_ConfigModel.MotorNewPositionsToBeStored = FALSE;
  EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);
}

void MOTP_MotorFailEvent(MOTP_Handle_t motor, PRES_Fault_t fault)
{
  /* Recovery */
  if (fault != PRES_NO_FAULT)
  {
    MOTP_OpenProtRel();
  }
  else
  {
  }
}

void MOTP_PosFailEvent(MOTP_Handle_t motor)
{

}

void MOTP_ResetAllStrokes(void)
{

}

void MOTP_CloseProtRel(MOTP_Handle_t motor)
{
  if(Motp_CurrOffsetAcquired == FALSE)
  {
    /* the current ense amplifier are enabled so we 
       can acquire current offset, see MOTP_CfgInit() */
    Motp_SetCurrentOffset();
  }
  /* Start Timeout */
  TLRP_SetSlow(TLRP_ProtRelTimeout);
  /* Enable Hall sensors pwr supply */
  /* If timer is running pwr supply was already switched on */
  if( 0U == TLRP_GetSlow(TLRP_SavePosition))
  {
    FUNP_HallActive();
  }
  /* Close protection relay */
  DOVFC_SetState(DOVFC_CmdRelProtEN, S_ON);
}

/**
 *  Called at ecu power off
 *  Checks if a current position store is needed.
 *
 */
void MOTP_CfgPwrOff(void)
{
  /* If timer is running a position store is pending */
  if( 0U != TLRP_GetSlow(TLRP_SavePosition))
  {
    /* Stop the timer ad store the current position */
    TLRP_ResetSlow(TLRP_SavePosition);
    MOTP_SavePosition();
  }
  else
  {
  }
}

/** 
 *  To have a correct current offset this function must 
 *  be called when the 7,5 V is enabled for more than 10 ms and 
 *  no movement has taken place in the last 10 ms 
 *
 */
void Motp_SetCurrentOffset(void)
{
  Motp_MotorsCurrOffset = ADCC_GetChnAvrgData(ADCC_MotorsSens);
  Motp_CurrOffsetAcquired = TRUE;
}



uint16_t MOTP_GetMotorsCurrent(void)
{
  return Motp_GetCurrentWithOffset(ADCC_MotorsSens, Motp_MotorsCurrOffset);
}

/* This function get the ADCC value of ADCC hdl and substract he given offset 
   if it's lower than current value, else it return 0 */
uint16_t Motp_GetCurrentWithOffset(ADCC_InputChn_t ADCC_hdl, uint16_t offset)
{
  uint16_t ret_val;

  ret_val = ADCC_GetChnAvrgData(ADCC_hdl);

  if(ret_val > offset)
  {
    ret_val = ret_val - offset;
  }
  else
  {
    ret_val = 0u;
  }
  
  return ret_val;
}

PRES_Fault_t MOTP_GetMotorsCurrentDiag(u08 dummy)
{
  static PRES_Fault_t motors_fault = PRES_NO_FAULT;
  uint16_t motors_current;
  
  motors_current = MOTP_GetMotorsCurrent();
    
  if (motors_current < OVER_CURRENT_THRESOLD_LO)
  {
    motors_fault = PRES_NO_FAULT;
  }
  else if(motors_current > OVER_CURRENT_THRESOLD_HI)
  {
    motors_fault = PRES_OVER_VOLTAGE;
  }
  else 
  {
    /* return the previous fault, already set */
  }
     
  return motors_fault;
}

void MOTP_SetPosition(MOTP_Handle_t motor, int16_t pos)
{
  IPOC_SetPosition(MOTP_CfgTable[motor].POS_FBK_HDL, pos);
}
                                                 
#endif /* end __MOTP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

