/******************************************************************************/
/* F_PROJECT:          TTM 520                                                */
/* F_NAME:             KEYA.c                                                 */
/* F_PURPOSE:                                                                 */
/* F_CREATED_BY:       S.Micari                                               */
/* F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                 */
/* F_CREATION_DATE:    30/10/2013                                             */
/* F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                   */
/******************************************* (C) Copyright 2012 Bitron S.p.A. */
/*
|------------------------------------------------------------------------------|
|               A U T H O R   I D E N T I T Y                                  |
|----------------------------------------------------------------------------- |
| Initials     Name                      Company                               |
| --------     ---------------------     ------------------------------------- |
| SM           Salvatore Micari          Bitron S.p.A.                         |
|                                                                              |
|----------------------------------------------------------------------------- |
|               R E V I S I O N   H I S T O R Y                                |
|----------------------------------------------------------------------------- |
| Date       Ver  Author  Description                                          |
| ---------  ---  ------  ---------------------------------------------------- |
| 30/10/2013  0.1   SM    First draft                                          |
|                                                                              |
 */

/* !!! NOT MOVE !!! */
#define KEYA_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "KEYA.h"

/* Module inhibition filter */
#ifdef __KEYA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - F U N C T I O N _______________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

static PRES_KeyStatus_t  Keya_KeyStatus;
static KEYA_KeyOffOnTran_t Keya_KeyOffOnTransition;

/*----------------------------------------------------------------------------*/
/*Name : KEYA_Init                                                            */
/*Role : init the state machine Key-On Management                             */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void KEYA_InitKeyStatus(void)
{
  Keya_KeyStatus          = ANY_KEY;
  Keya_KeyOffOnTransition = NO_TRANSITION;
}

/*----------------------------------------------------------------------------*/
/*Name : KEYA_SetKeyStatus                                                    */
/*Role : Set the Applicative Request State of the state machine Key-On        */
/*       Management                                                           */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void KEYA_SetKeyStatus(PRES_KeyStatus_t  Appl_KeyStatus_Req)
{
  Keya_KeyStatus = Appl_KeyStatus_Req;
}

/*----------------------------------------------------------------------------*/
/*Name : KEYA_GetKeyStatus                                                    */
/*Role : Get the State of the state machine Key-On Management                 */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
PRES_KeyStatus_t KEYA_GetKeyStatus(void)
{
  return(Keya_KeyStatus);
}

/**
 * @brief Routine callback generated by STATUS_BH_BCM1 message received
 * It checks the key status and update it if necessary
 * @author Daniele Cloralio - Ema S.r.l.
 * @param [in]
 * @param [out]
 * @return None
 */
void KEYA_CheckKeyStatus(void)
{
  OperationalModeSts_t OperatModeSts;

  /* The following routine retrieves key signal status from CAN bus */
  OperatModeSts = VF608_GetOperationalModeSts();

  switch (OperatModeSts)
  {
  case CMMD_KEY_AUTHENTICATED:
  case CMMD_IGNITION_ACC:  /* not used */
  case CMMD_IGNITION_PRE_OFF:
  case CMMD_IGNITION_OFF_WITHOUTKEY:
  case CMMD_IGNITION_OFF:
    if (Keya_KeyStatus != KEYA_OFF_STATUS)
    {
      /* if the key status is changed, update it */
      KEYA_SetKeyStatus(KEYA_OFF_STATUS);
      KEYA_MngKeyStatus();  /* removed from scheduler and executed via this callback*/
    }
    break;

  case CMMD_AUTOMATIC_STOP:
  case CMMD_IGNITION_ON_ENGON:
  case CMMD_IGNITION_PRE_ACC:  /* not used */
  case CMMD_IGNITION_ON:
    if (Keya_KeyStatus != KEYA_ON_STATUS)
    {
      /* if the key status is changed, update it */
      KEYA_SetKeyStatus(KEYA_ON_STATUS);
      KEYA_MngKeyStatus();  /* removed from scheduler and executed via this callback*/
    }
    break;

  case CMMD_AUTOMATIC_CRANKING:
  case CMMD_IGNITION_CRANKING:
  case CMMD_IGNITION_START:
  case CMMD_IGNITION_PRE_START:
    if (Keya_KeyStatus != KEYA_CRANK_STATUS)
    {
      /* if the key status is changed, update it */
      KEYA_SetKeyStatus(KEYA_CRANK_STATUS);
      KEYA_MngKeyStatus();  /* removed from scheduler and executed via this callback*/
    }
    break;

  default:
  #if 0
    KEYA_SetKeyStatus(ANY_KEY);
  #endif
    break;
  }
}


/*----------------------------------------------------------------------------*/
/*Name : KEYA_GetKeyOffOnTransition                                           */
/*Role : Get TRUE if a KeyOff -> KeyOn transition has been done               */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
KEYA_KeyOffOnTran_t KEYA_GetKeyOffOnTransition(void)
{
  return(Keya_KeyOffOnTransition);
}

/*----------------------------------------------------------------------------*/
/*Name : KEYA_IsKeyOnStatus                                                   */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 KEYA_IsKeyOnStatus(void)
{
  u08 ret_val = FALSE;

  if(Keya_KeyStatus == KEYA_ON_STATUS)
  {
    ret_val = TRUE;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : KEYA_MngKeyStatus                                                    */
/*Role : Manager of the state machine Key-On Management                       */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : use restriction                                             */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/

void KEYA_MngKeyStatus(void)
{
  static PRES_KeyStatus_t  KEYA_KeyStatusOld = ANY_KEY;

  /************************************************************************************/
  /* The following code performs a debounce on Key-On state.                          */
  /* It is necessary to invoke the function DDMP_OperationalModeStsChanged() avoiding */
  /* mutiple calls of the function itself.                                            */
  /************************************************************************************/

  if (KEYA_KeyStatusOld != Keya_KeyStatus)
  {
    KEYA_STS_CHANGED_EVENT(Keya_KeyStatus)

    /* the keyoff to keyon transition is performed also if the first Key signal value    */
    /* received on CAN bus is KEY_ON (KEYA_StatusOld has still the init value ANY_KEY)   */
    if (((KEYA_KeyStatusOld == KEYA_OFF_STATUS) || (KEYA_KeyStatusOld == ANY_KEY)) &&
         (Keya_KeyStatus == KEYA_ON_STATUS))
    {
      //incremento contatore del KeyOn e memorizzo in RAM
      EERAM_EcuStatusInfo.KeyOnCnt++;

      KEYA_STS_OFF_TO_ON_EVENT()
    }
    else if((KEYA_KeyStatusOld == KEYA_ON_STATUS) &&
            (Keya_KeyStatus == KEYA_OFF_STATUS))
    {
      KEYA_STS_ON_TO_OFF_EVENT()
    }
    else
    {
    }

    KEYA_KeyStatusOld = Keya_KeyStatus;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : KEYA_MngKeyOnCntAlignment                                      	  */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void KEYA_MngKeyOnCntAlignment(void)
{
//  if(EERAM_EcuStatusInfo.KeyOnCnt != CMMD_BCMKeyOnCounter)
//  {
//    EERAM_EcuStatusInfo.KeyOnCnt = CMMD_BCMKeyOnCounter;
//    EERAM_EcuStatusInfo.KeyOnCntSts.bit.KeyOnCntFirstAlignment = 1u;
//
//    if(EERAM_EcuStatusInfo.KeyOnCntSts.bit.KeyOnCntFirstAlignmentCnt < 0x7Fu)
//    {
//      EERAM_EcuStatusInfo.KeyOnCntSts.bit.KeyOnCntFirstAlignmentCnt++;
//    }
//    else
//    {
//      ;
//    }
//  }
//  else
//  {
//    ;
//  }
}

#endif /* end __KEYA_IS_PRESENT__ */

