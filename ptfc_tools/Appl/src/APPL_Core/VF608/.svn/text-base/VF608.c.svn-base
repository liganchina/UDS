/******************************************************************************/
/* @F_PROJECT:          HMSM 952                                              */
/* F_NAME:              VF608.c                                               */
/* @F_PURPOSE:                                                                */
/* @F_CREATED_BY:       S. Micari                                             */
/* @F_MPROC_TYPE:       Renesas 78kF0R1833-FC3                                */
/* F_CREATION_DATE:     06/11/2013                                            */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                  */
/***************************************** (C) Copyright 2013 Bitron S.p.A. ***/

/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| SM           Salvatore Micari          Bitron S.p.A.
| FRAT         Francesco Talarico        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 06/11/2013 0.1  SM      First draft
| 24/08/2015 1.0  FRAT    TTM 520 porting - bug fix - general tuning
|
 */
#define VF608_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "VF608.h"


#ifdef __VF608_IS_PRESENT__


/*______ L O C A L - D E F I N E S ___________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

u08 VF608_recovery1_performed = FALSE;

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

OperationalModeSts_t   VF608_OperationalModeSts;
OperationalModeSts_t   VF608_OperationalModeStsOld;
VF608_CmdIgnInfo_t     VF608_CmdIgnInfo;
VF608_CmdIgnInfo_t     VF608_CmdIgnInfoOld;
u08 VF608_FaultOpModePresent;
/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/


/**
 * @brief Initialization of variables
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_Init(void)
{
  VF608_OperationalModeSts           = CMMD_OP_MODE_INITIALIZATION;
  VF608_OperationalModeStsOld        = CMMD_OP_MODE_INITIALIZATION;
  VF608_CmdIgnInfo.CmdIgnSts         = CMMD_INITIALIZATION;
  VF608_CmdIgnInfoOld.CmdIgnSts      = CMMD_INITIALIZATION;
  VF608_CmdIgnInfo.CmdIgn_FailSts    = CMMD_IGN_FAIL_NOT_PRESENT;
  VF608_CmdIgnInfoOld.CmdIgn_FailSts = CMMD_IGN_FAIL_NOT_PRESENT;
  VF608_FaultOpModePresent           = FALSE;
}

/**
 * @brief Get the State of the Operational Mode Status
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - OperationalModeSts_t
 * @return      - Value of the Operational Mode Status
 */
OperationalModeSts_t VF608_GetOperationalModeSts(void)
{
  return(VF608_OperationalModeSts);
}

/*----------------------------------------------------------------------------*/
/*Name : VF608_GetCmdIgnSts                                                   */
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
void VF608_GetCmdIgnSts(VF608_CmdIgnInfo_t* HMSM_CmdIgnSts)
{
  HMSM_CmdIgnSts->CmdIgnSts = VF608_CmdIgnInfo.CmdIgnSts;
  HMSM_CmdIgnSts->CmdIgn_FailSts = VF608_CmdIgnInfo.CmdIgn_FailSts;
}

/**
 * @brief Callback routine generated by CAN message received for operational mode status management
 * @author Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_MngOperationalModeSts(void)
{
  TLRP_SetSlow(VF608_T_BCM1_Missing_Msg);

  /*VF608_V1_R5 par. 1.11 - ECUB Functional Requirements*/

  if( (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_OP_MODE_INITIALIZATION) ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_OFF)           ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_ON)            ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_PRE_START)     ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_START)         ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_CRANKING)      ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_ON_ENGON)      ||
      (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_IGNITION_PRE_OFF) )
  {
    VF608_OperationalModeSts = STATUS_BH_BCM1.bit.OperationalModeSts;

    if (NETP_GetRxStatus(CAND_STATUS_BH_BCM2_HND) == NETP_MSG_RECEIVED)
    {
      VF608_CmdIgnInfo.CmdIgnSts      = STATUS_BH_BCM2.bit.CmdIgnSts;
      VF608_CmdIgnInfo.CmdIgn_FailSts = STATUS_BH_BCM2.bit.CmdIgn_FailSts;
    }
  }
  
  if(STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_OP_MODE_SNA) /*VF608_V1_R5 ID 1.0 Description par. 1.13.2.1.1*/
  {
    if (!VF608_recovery1_performed) /*performo la recovery una volta sola fintantochè lo status del messaggio non cambia*/
    {
      VF608_recovery1_performed = TRUE;
      TLRP_SetFast(VF608_T_SNA_Timer);
      /*FRAT - allo scadere di questo timer (50ms) verrà effettuata la recovery1*/
    }
  }
  else
  {
    VF608_recovery1_performed = FALSE;
    VF608_FaultOpModePresent = FALSE;/*FRAT - resetto la flag per DTC 0xD93286*/
    /*resetto il timer solo se precedentemente settato*/
    if (TLRP_GetFast(VF608_T_SNA_Timer) != 0U)
    {
      TLRP_ResetFast(VF608_T_SNA_Timer);
    }
    else
    {}
  }

  /*per punto C Recovery 1*/
  if (VF608_OperationalModeStsOld != VF608_OperationalModeSts)
  {
    VF608_OperationalModeStsOld = VF608_OperationalModeSts;
    /* call user macro to notify OperationalMode status is changed */
    VF608_OPMODE_STS_CHANGED_EVENT(VF608_OperationalModeSts)
    if (VF608_OperationalModeSts == CMMD_IGNITION_ON_ENGON)
    {
      /* call user macro to notify IgnitionOnEngineOn event occurred */
      VF608_OPMODE_OFF_TO_ON_ENGON_EVENT()
    }
  }

  if (VF608_CmdIgnInfoOld.CmdIgnSts != VF608_CmdIgnInfo.CmdIgnSts)
  {
    VF608_CmdIgnInfoOld.CmdIgnSts = VF608_CmdIgnInfo.CmdIgnSts;
  }

  DDMP_ComponeOperationalModeStatus(); /*viene chiamata per comporre il campo OpModeSts dello snapshot*/
}

/**
 * @brief - Callback routine generated when STATUS_BH_BCM1.OperationalModeSts == SNA for a time greater than T_SNA_filtering (50ms)
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_OpModeStsRecovery(void)
{
  /*FRAT - segnalo al modulo FVMP la condizione di fail per il DTC 0xD93286*/
  VF608_FaultOpModePresent = TRUE;

  VF608_EcuRecovery1();
}

/**
 * @brief - Callback routine generated when STATUS_BH_BCM1.OperationalModeSts == SNA for a time greater than T_SNA_filtering (50ms)
 *          or when STATUS_BH_BCM1 is missing for a time greater than or equal to "T_STATUS_BH_BCM1_Missing_Msg" (1000ms)
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_EcuRecovery1(void)
{
  PRES_State_t IgnitionPreStartLogic;

  /* FRAT - segnalo al modulo FVMP la condizione di fail per il DTC 0xD93286*/
  /* VF608_FaultOpModePresent = TRUE; FRAT - removed */
    
  /* A) IF (STATUS_BH_BCM2.CmdIgnSts == RUN OR STATUS_BH_BCM2.CmdIgnSts == START) AND (STATUS_CCAN3.EngineSts == SNA)
   * THEN the ECU shall set the internal signal ECU_OperationalModeSts.Info = SNA */
  if (((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_RUN ) || (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START)) &&
       (STATUS_CCAN3.bit.EngineSts   == CMMD_ENGINE_SNA))
  {
    VF608_OperationalModeSts = CMMD_OP_MODE_SNA;
  }

  /*  C is first of B because:
   * IN CASE OF CONFLICT BETWEEN THE TWO REQUIREMENTS, B) AND C) (FOR EXAMPLE AFTER A TRANSITION
   * OF THE STATUS_BH_BCM2.CmdIgnSts), SHALL BE PERFORMED THE REQUIREMENT C).

   C) IF STATUS_BH_BCM2.CmdIgnSts switches from RUN to IGN_LK value OR
   *    IF STATUS_BH_BCM2.CmdIgnSts switches from START to IGN_LK value THEN the ECU shall:
   *------------------ DO IN: at the top of VF608_MngOperationalModeSts() -------------------------
   * 1) go into the Ignition Working Condition Ignition Pre Off, and set for a time equal to
   * T_PreIgnition the internal signals ECU_OperationalModeSts.Info = Ignition_Pre_Off, only
   * if the STATUS_BH_BCM2.CmdIgnSts == IGN_LK during this time. IF the value of
   * STATUS_BH_BCM2.CmdIgnSts changes THEN the ECU shall set the internal signal
   * ECU_OperationalModeSts.Info according to the new conditions of the STATUS_BH_BCM2.CmdIgnSts
   * and the STATUS_CCAN3.EngineSts.
   * ------------------ DO IN: VF608_EcuRecovery1_PartC()------------------------------
   * 2) WHEN T_PreIgnition is elapsed, IF the STATUS_BH_BCM2.CmdIgnSts == IGN_LK THEN the ECU shall:
   *   1) go into the Ignition Working Condition Ignition Off;
   *   2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Off. */
  if (((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_RUN  ) && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK)) ||
      ((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_START) && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK)))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_PRE_OFF;
    TLRP_SetFast(VF608_T_Preignition);/*150 ms*/
  }

  /*  B) IF (STATUS_BH_BCM2.CmdIgnSts == IGN_LK) AND (the internal signal
   * ECU_OperationalModeSts.Info != Ignition_Pre_Off) THEN the ECU shall:
   * 1) go into the Ignition Working Condition Ignition Off;
   * 2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Off */
  if ((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK) && (VF608_OperationalModeSts != CMMD_IGNITION_PRE_OFF))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_OFF;
  }

  /*   D) IF (STATUS_BH_BCM2.CmdIgnSts == RUN OR the signal STATUS_BH_BCM2.CmdIgn_FailSts == Fail_Present)
   * AND (STATUS_CCAN3.EngineSts == Engine_Off ) THEN the ECU shall:
   * 1) go into the Ignition Working Condition Ignition On;
   * 2) set the internal signal ECU_ OperationalModeSts.Info = Ignition_On. */

//  if (((VF608_CmdIgnInfo.CmdIgnSts == CMMD_RUN) || (VF608_CmdIgnInfo.CmdIgn_FailSts == CMMD_IGN_FAIL_PRESENT))
//      && (STATUS_CCAN3.bit.EngineSts == CMMD_ENGINE_OFF))
  if (((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_RUN) || (STATUS_BH_BCM2.bit.CmdIgn_FailSts == CMMD_IGN_FAIL_PRESENT)) &&
       (STATUS_CCAN3.bit.EngineSts   == CMMD_ENGINE_OFF))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_ON;
  }

  /* G is first of B because:
   * IN CASE OF CONFLICT BETWEEN THE TWO REQUIREMENTS, E) AND G) (FOR EXAMPLE AFTER A TRANSITION
   * OF THE STATUS_BH_BCM2.CmdIgnSts), SHALL BE PERFORMED THE REQUIREMENT G).

   G) IF (STATUS_BH_BCM2.CmdIgnSts switches from IGN_LK to START value) AND
   * (STATUS_BH_BCM2.CmdIgn_FailSts != Fail_Present) AND (STATUS_CCAN3.EngineSts == Engine_Off)
   * AND (Ignition_Pre_Start_Logic == Enable) OR IF (STATUS_BH_BCM2.CmdIgnSts switches from RUN
   * to START value) AND (STATUS_BH_BCM2.CmdIgn_FailSts != Fail_Present) AND
   * (STATUS_CCAN3.EngineSts == Engine_Off) AND (Ignition_Pre_Start_Logic == Enable) THEN the ECU shall:
   *  1) go into the Ignition Working Condition Ignition Pre Start, and set for a time equal to
   *  T_PreIgnitionStart the internal signal ECU_OperationalModeSts.Info = Ignition_Pre_Start, only if
   *  the STATUS_BH_BCM2.CmdIgnSts == START during this time. IF the value of STATUS_BH_BCM2.CmdIgnSts
   *  changes THEN the ECU shall set the internal signal ECU_OperationalModeSts according to the new
   *  conditions of the STATUS_BH_BCM2.CmdIgnSts and the STATUS_CCAN3.EngineSts.
   *  2) WHEN T_PreIgnitionStart is elapsed, IF the STATUS_BH_BCM2.CmdIgnSts == START THEN the ECU shall:
   *    1) go into the Ignition Working Condition Ignition Start;
   *    2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Start. */

  IgnitionPreStartLogic = FUNP_GetIgnitionPreStartLogic();
  
  if((((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_IGN_LK) && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START))  ||
      ((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_RUN )   && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START))) &&
      (STATUS_BH_BCM2.bit.CmdIgn_FailSts != CMMD_IGN_FAIL_PRESENT)                                      &&
      (STATUS_CCAN3.bit.EngineSts == CMMD_ENGINE_OFF)                                                   &&
      (IgnitionPreStartLogic == S_ON))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_PRE_START;
    TLRP_SetFast(VF608_T_PreignitionStart);/*80 ms*/
  }

  /* E) IF (STATUS_BH_BCM2.CmdIgnSts == START AND STATUS_BH_BCM2.CmdIgn_FailSts != Fail_Present AND
   * STATUS_CCAN3.EngineSts == Engine_Off  AND the internal signal
   * ECU_OperationalModeSts.Info  != Ignition_Pre_Start AND Ignition_Pre_Start_Logic == Enable)
   * THEN the ECU shall:
   *  1) go into the Ignition Working Condition Ignition Start;
   *  2) set the internal signal ECU_ OperationalModeSts.Info = Ignition_Start.

   F) IF (STATUS_BH_BCM2.CmdIgnSts == START AND STATUS_BH_BCM2.CmdIgn_FailSts != Fail_Present AND
   * STATUS_CCAN3.EngineSts== Engine_Off AND the internal signal ECU_OperationalModeSts.Info != Ignition_Pre_Start
   * AND Ignition_Pre_Start_Logic == Disable) THEN the ECU shall:
   *  1) go into the Ignition Working Condition Ignition Start;
   *  2) set the internal signal ECU_ OperationalModeSts.Info = Ignition_Start.

  Le due condizioni sono state inglobate in 1 sola visto che dipendono da Ignition_Pre_Start_Logic
   * che assume solo 2 valori 0/1 */
  if ((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START)                 &&
      (STATUS_BH_BCM2.bit.CmdIgn_FailSts != CMMD_IGN_FAIL_PRESENT) &&
      (STATUS_CCAN3.bit.EngineSts == CMMD_ENGINE_OFF)              &&
      (VF608_OperationalModeSts != CMMD_IGNITION_PRE_START))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_START;
  }

  /*  H) IF (STATUS_BH_BCM2.CmdIgnSts == START OR STATUS_BH_BCM2.CmdIgnSts == RUN) AND
   * (STATUS_CCAN3.EngineSts == Engine_Cranking) THEN the ECU shall:
   * 1) go into the Ignition Working Condition Ignition Cranking;
   * 2) set the internal signal ECU_OperationalModeSts.Info =  Ignition_Cranking. */
  if (((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START) || (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_RUN)) &&
      (STATUS_CCAN3.bit.EngineSts == CMMD_ENGINE_CRANKING))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_CRANKING;
  }

  /*  I) IF (STATUS_BH_BCM2.CmdIgnSts == RUN OR STATUS_BH_BCM2.CmdIgnSts == START) AND
   * (STATUS_CCAN3.EngineSts == Engine_On) THEN the ECU shall:
   * 1) go into the Ignition Working Condition Ignition On Engine On;
   * 2) set the internal signal ECU_OperationalModeSts.Info = Ignition_On_EngOn. */
  if (((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START) || (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_RUN)) &&
      (STATUS_CCAN3.bit.EngineSts == CMMD_ENGINE_ON))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_ON;
  }

  /*   N)  IF (STATUS_BH_BCM2.CmdIgnSts == SNA) THEN the ECU shall set the internal signal
   * ECU_OperationalModeSts.Info = SNA. */
  if (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_SNA)
  {
    VF608_OperationalModeSts = CMMD_OP_MODE_SNA;
  }
}

/**
 * @brief - Callback routine generated when STATUS_BH_BCM1 and STATUS_CCAN3 are missing
 *          or when STATUS_CCAN3 is missing for a time greater than or equal to "T_STATUS_CCAN3_Missing_Msg" (1000ms)
 *          and STATUS_BH_BCM1.OperationalModeSts == SNA
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_EcuRecovery2(void)
{
  /* 2) IF STATUS_BH_BCM2.CmdIgnSts switches from RUN to IGN_LK value OR IF STATUS_BH_BCM2.CmdIgnSts
   * switches from START to IGN_LK value THEN the ECU shall:
   *  1) go into the Ignition Working Condition Ignition Pre Off, and set for a time equal to
   *  T_PreIgnition the internal signal ECU_OperationalModeSts.Info = Ignition_Pre_Off only if the
   *  STATUS_BH_BCM2.CmdIgnSts == IGN_LK during this time.
   *  2) WHEN T_PreIgnition is elapsed, IF the STATUS_BH_BCM2.CmdIgnSts == IGN_LK THEN the ECU shall:
   *    1) go into the Ignition Working Condition Ignition Off;
   *    2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Off.
   *  IN CASE OF CONFLICT BETWEEN THE TWO REQUIREMENTS, 1) AND 2) (FOR EXAMPLE AFTER A TRANSITION OF
   *  THE STATUS_BH_BCM2.CmdIgnSts), SHALL BE PERFORMED THE REQUIREMENT 2).*/
 if (((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_RUN  ) && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK)) ||
     ((VF608_CmdIgnInfoOld.CmdIgnSts == CMMD_START) && (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK)))
  {
    TLRP_SetFast(VF608_T_Preignition);
   /* Setto VF608_PRE_OFF_STATUS per evitare che per un ciclo il valore VF608_OperationalModeSts == VF608_OFF_STATUS
     * a causa della condizione 1 */
    VF608_OperationalModeSts = CMMD_IGNITION_PRE_OFF;
  }

 /*  1) IF (STATUS_BH_BCM2.CmdIgnSts == IGN_LK) and (ECU_OperationalModeSts.Info != Ignition_Pre_Off)
   * the ECU shall go into the Ignition Working Condition Ignition Off, it shall set the internal signal
   * ECU_OperationalModeSts.Info = Ignition_Off. */
  if ((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK) && (VF608_OperationalModeSts != CMMD_IGNITION_PRE_OFF ))
  {
    VF608_OperationalModeSts = CMMD_IGNITION_OFF;
  }

 /*  3) IF (STATUS_BH_BCM2.CmdIgnSts == RUN OR START OR SNA) THEN the ECU shall set the internal signal
   * ECU_OperationalModeSts.Info = SNA */
  if ((STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_RUN)   ||
      (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START) ||
      (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_SNA))
  {
    VF608_OperationalModeSts = CMMD_OP_MODE_SNA;
  }
}

/**
 * @brief - Callback routine generated when VF608_T_Preignition timeout (150ms) is elapsed
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_EcuRecovery1_PartC(void)
{
  /*Ecurecovery1 part C
  2) WHEN T_PreIgnition is elapsed, IF the STATUS_BH_BCM2.CmdIgnSts == IGN_LK THEN the ECU shall:
   *   1) go into the Ignition Working Condition Ignition Off;
   *   2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Off.*/
  if (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_IGN_LK)
  {
    VF608_OperationalModeSts = CMMD_IGNITION_OFF;
  }
}

/**
 * @brief - Callback routine generated when VF608_T_PreignitionStart timeout (80ms) is elapsed
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_EcuRecovery1_PartG(void)
{

/*  Ecurecovery1 part G
  2) WHEN T_PreIgnitionStart is elapsed, IF the STATUS_BH_BCM2.CmdIgnSts == START THEN the ECU shall:
   *    1) go into the Ignition Working Condition Ignition Start;
   *    2) set the internal signal ECU_OperationalModeSts.Info = Ignition_Start. */
  if (STATUS_BH_BCM2.bit.CmdIgnSts == CMMD_START)
  {
    VF608_OperationalModeSts = CMMD_IGNITION_START;
  }
}

/**
 * @brief - Callback routine generated when STATUS_BH_BCM1 is missing for a time greater than or equal to "T_STATUS_BH_BCM1_Missing_Msg" (1000ms)
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_StatusBhBcm1Rec (void)
{
  /*VF608_V1_R5 ID 2.0/3.0 Description*/

  VF608_EcuRecovery1();    /*VF608_V1_R5 ECU Recovery1 par. 1.13.2.1.22.8 */

  if (NETP_GetRxStatus(CAND_STATUS_BH_BCM2_HND) == NETP_MSG_NOT_RECEIVED)
  {
    VF608_OperationalModeSts = CMMD_OP_MODE_SNA;
  }

  if (TLRP_GetSlow(VF608_T_CCAN3_Missing_Msg) == 0U)
  {
    VF608_EcuRecovery2();    /*VF608_V1_R5 ECU Recovery2 par. 1.13.2.1.22.9 */
  }
}

/**
 * @brief - Callback routine generated when STATUS_CCAN3 is missing for a time greater than or equal to "T_STATUS_CCAN3_Missing_Msg" (1000ms)
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_StatusCcan3Rec (void)
{
  /*VF608_V1_R5 ID 5.0 Description par. 1.13.2.1.5*/
  if (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_OP_MODE_SNA)
  {
    VF608_EcuRecovery2();    /*VF608_V1_R5 ECU Recovery2 par. 1.13.2.1.22.9 */
  }
}

/**
 * @brief - Routine called when STATUS_BH_BCM2 is missing for a time greater than or equal to "T_STATUS_BH_BCM2_Missing_Msg" (2500ms)
 * @author - Francesco Talarico - Bitron S.p.A.
 * @param [in]  - None
 * @param [out] - None
 * @return      - None
 */
void VF608_ID4Description (void)
{
  VF608_CmdIgnInfo.CmdIgnSts      = CMMD_SNA;
  VF608_CmdIgnInfo.CmdIgn_FailSts = CMMD_IGN_FAIL_PRESENT;

  if (STATUS_BH_BCM1.bit.OperationalModeSts == CMMD_OP_MODE_SNA)
  {
    VF608_OperationalModeSts = CMMD_OP_MODE_SNA;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF608_GetOpModeDiag                                                  */
/*Role : Recovery                                                             */
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
PRES_Fault_t VF608_GetOpModeDiag(uint8_t dummy)
{
  PRES_Fault_t retValue;

  if(VF608_FaultOpModePresent == TRUE)
  {
    retValue = PRES_MSG_FAULTY;
  }
  else
  {
    retValue = PRES_NO_FAULT;
  }
  return(retValue);
}

#endif /* end __VF608_IS_PRESENT__ */
