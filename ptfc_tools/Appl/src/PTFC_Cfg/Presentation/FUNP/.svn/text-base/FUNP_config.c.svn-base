/********************************************************************************/
/* @F_PROJECT:          ALM Iveco                                               */
/* F_NAME:              Funp.c                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/07/2012                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| DF           Davide Fogliano           Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 22/05/2013  0.1  GIL     First DRAFT
*/


/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "FUNP.h"
#include "FUNP_config.h"
#include "VF608_cbk.h"

/* Module inhibition filter */
#ifdef __FUNP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D E F I N E _____________________________________________*/

#define HALL_NUM_MODULES 1u /* MOTP is the only module that switch on and off hall supply */

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

uint8_t  HallCounter;

/*______ L O C A L - D A T A _________________________________________________*/



#define FUNP_LOW_BAT_THRES  ((u08)210u)  /* 10.5V thresold */
#define FUNP_HIGH_BAT_THRES ((u08)330u)  /* 16.5V thresold */


/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

void FUNP_CfgInit(void)
{
  HallCounter = 0U;
}

/*----------------------------------------------------------------------------*/
/*Name : FUNP_IsVehicleSpeedEqZero                                            */
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
bool FUNP_IsVehicleSpeedEqZero(void)
{
  bool ret_val;

  ret_val = FALSE;

  /* If vehicle speed fail status was NOT fail and vehicle speed was equal to 0 Km/h ? */
  if((CMMD_VehicleFail == CMMD_SPEED_FAIL_NOT_PRESENT) && (CMMD_VehicleSpeed == 0U))
  {
    ret_val = TRUE;
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : FUNP_IsEngineNotRunning                                              */
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
bool FUNP_IsEngineNotRunning(void)
{
  /*HMSM does not receive the CAN signal STATUS_CCAN5.EngineSpeed*/
  return(TRUE);
}

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetVehicleSpeed                                                 */
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
u16 FUNP_GetVehicleSpeed(void)
{
  return(CMMD_VehicleSpeed);
}

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetTotalOdometer                                                */
/*Role : used in VF 607 only for VIN odo                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u32 FUNP_GetTotalOdometer(void)
{
  u32 ret_val = 0u;

  NETP_MsgStatus_t msgStatus = NETP_GetRxStatus(CAND_TRIP_A_B_HND);

  if (msgStatus == NETP_MSG_RECEIVED)
  {
    ret_val = (u32)(((u32)(TRIP_A_B.bit.TotalOdometer_8to11)     << 16U) |\
                    ((u32)(TRIP_A_B.bit.TotalOdometer_23to24[0]) <<  8U) |\
                    ((u32)(TRIP_A_B.bit.TotalOdometer_23to24[1])));
  }
  else
  {
    ret_val = 0xFFFFFFFFUL; /* save delta VINodo */
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : FUNP_GetBatteryVoltage                                               */
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
u16 FUNP_GetBatteryVoltage(void)
{
  u16 calc_vbat = 0U;
  u32 tmpVbat   = 0U;

  /* Risoluzione: 0.001V/bit */
  /* Vbatt ELE: resistors ratio compensation + Diode */
  calc_vbat = ((u16)(ADCC_GetChnAvrgData(ADCC_Ele_Fbk)) << FUNP_VBATT_ELE_RATIO)
                       + FUNP_VBATT_ELE_OFFSET;

  /* Scaling to right resolution (4,883mV/bit --> 0,001V/bit) */
  tmpVbat = ((u32)calc_vbat * (u32)5000U) >> 10U;

  calc_vbat = (u16)(tmpVbat & (u32)0x0000FFFFU);
  return(calc_vbat);
}

PRES_Fault_t FUNP_GetVehicleSpeedDiag(void)
{
  PRES_Fault_t ret_val;

  if (CMMD_VehicleFail == 1U)
  {
    ret_val = PRES_SIGNAL_ERROR;
  }
  else
  {
    ret_val = PRES_NO_FAULT;
  }
  
  return ret_val;
}

/**
 * @brief Update IDs (RDI 0xF180, 0xF181, 0xF182, 0xF187, 0xF188, 0xF194, 0xF195, 0xF196, 0xF1A5)
 *       after a flash re-programming
 * @return void
 * @retval none
 */
void FUNP_WriteNewIDs(void)
{

  u08 check_sw         = FALSE;
  u08 check_ManSwN     = FALSE;
  u08 check_OmologCode = FALSE;
  u08 check_BootSwV    = FALSE;
  u08 check_ApplSwV    = FALSE;
  u08 check_DataSwV    = FALSE;
  u08 check_ISOCode    = FALSE;
  u08 i = 0U;

  /* check $F187 */
  while (i < MSM952_MAX)
  {
    if (memcmp(&EEDEF_VehManSparePartN[0U], &FLASH_SupportedVehManSparePartN[i][0U], UDSA_LN_SPARE_PART_NUMBER) == 0U)
    {
      if (memcmp(&EERAM_VehManSparePartN[0U], &FLASH_SupportedVehManSparePartN[EERAM_BproxiValue][0U], UDSA_LN_SPARE_PART_NUMBER) != 0U)
      {
        memcpy(&EERAM_VehManSparePartN[0U], &FLASH_SupportedVehManSparePartN[EERAM_BproxiValue][0U], UDSA_LN_SPARE_PART_NUMBER);
        EEPP_WriteData(EEPP_HDL_VehManSparePartN, NULL);
      }
      break;
    }
    else
    {
      i++;
    }
  }

  if (i == MSM952_MAX)
  {
    memcpy(&EERAM_VehManSparePartN[0U], &EEDEF_VehManSparePartN[0U], UDSA_LN_SPARE_PART_NUMBER);
    EEPP_WriteData(EEPP_HDL_VehManSparePartN, NULL);
  }

  /* check $F188 */
  for (i=0U; i < UDSA_LN_VEH_MAN_ECU_SW_NUM; i++)
  {
    if (EERAM_VehManEcuSwN[i] != EEDEF_VehManEcuSwN[i])
    {
      check_ManSwN = TRUE;
      i = UDSA_LN_VEH_MAN_ECU_SW_NUM;
    }
  }

  if(check_ManSwN == TRUE)
  {
    for (i=0U; i < UDSA_LN_VEH_MAN_ECU_SW_NUM; i++)
    {
      EERAM_VehManEcuSwN[i] = EEDEF_VehManEcuSwN[i];
    }
    EEPP_WriteData(EEPP_HDL_VehManEcuSwN, NULL);
    check_ManSwN = FALSE;
  }

  /* check $F194 */
  for (i=0U; i < UDSA_LN_SYS_SUP_ECU_SW_NUM; i++)
  {
    if (EERAM_SysSuppEcuSwN[i] != EEDEF_SysSuppEcuSwN[i])
    {
      check_sw = TRUE;
      i = UDSA_LN_SYS_SUP_ECU_SW_NUM;
    }
  }

  if(check_sw == TRUE)
  {
    for (i=0U; i < UDSA_LN_SYS_SUP_ECU_SW_NUM; i++)
    {
      EERAM_SysSuppEcuSwN[i] = EEDEF_SysSuppEcuSwN[i];
    }
    EEPP_WriteData(EEPP_HDL_SysSuppEcuSwN, NULL);
    check_sw = FALSE;
  }

  /* check $F195 */
  if ((EERAM_SysSuppEcuSwVerN[0] != EEDEF_SysSuppEcuSwVerN[0]) ||
      (EERAM_SysSuppEcuSwVerN[1] != EEDEF_SysSuppEcuSwVerN[1]))
    {
      EERAM_SysSuppEcuSwVerN[0] = EEDEF_SysSuppEcuSwVerN[0];
      EERAM_SysSuppEcuSwVerN[1] = EEDEF_SysSuppEcuSwVerN[1];
      EEPP_WriteData(EEPP_HDL_SysSuppEcuSwVerN, NULL);
    }

  /* check $F196 */
  for (i=0U; i < UDSA_LN_HOMOLOG; i++)
  {
    if (EERAM_HomologationCode[i] != EEDEF_HomologationCode[i])
    {
      check_OmologCode = TRUE;
      i = UDSA_LN_HOMOLOG;
    }
  }

  if(check_OmologCode == TRUE)
  {
    for (i=0U; i < UDSA_LN_HOMOLOG; i++)
    {
      EERAM_HomologationCode[i] = EEDEF_HomologationCode[i];
    }
    EEPP_WriteData(EEPP_HDL_HomologationCode, NULL);
    check_OmologCode = FALSE;
  }

  /* check $F180 */
  for (i=0U; i < UDSA_LN_BOOT_SW_ID; i++)
  {
    if (EERAM_BootSwId[i] != EEDEF_BootSwId[i])
    {
      check_BootSwV = TRUE;
      i = UDSA_LN_BOOT_SW_ID;
    }
  }

  if(check_BootSwV == TRUE)
  {
    for (i=0U; i < UDSA_LN_BOOT_SW_ID; i++)
    {
      EERAM_BootSwId[i] = EEDEF_BootSwId[i];
    }
    EEPP_WriteData(EEPP_HDL_BootSwId, NULL);
    check_BootSwV = FALSE;
  }

  /* check $F181 */
  for (i=0U; i < UDSA_LN_APPL_SW_ID; i++)
  {
    if (EERAM_ApplSwId[i] != EEDEF_ApplSwId[i])
    {
      check_ApplSwV = TRUE;
      i = UDSA_LN_APPL_SW_ID;
    }
  }

  if(check_ApplSwV == TRUE)
  {
    for (i=0U; i < UDSA_LN_APPL_SW_ID; i++)
    {
      EERAM_ApplSwId[i] = EEDEF_ApplSwId[i];
    }
    EEPP_WriteData(EEPP_HDL_ApplSwId, NULL);
    check_ApplSwV = FALSE;
  }

  /* check $F182 */
  for (i=0U; i < UDSA_LN_APPL_DATA_ID; i++)
  {
    if (EERAM_ApplDataId[i] != EEDEF_ApplDataId[i])
    {
      check_DataSwV = TRUE;
      i = UDSA_LN_APPL_DATA_ID;
    }
  }

  if(check_DataSwV == TRUE)
  {
    for (i=0U; i < UDSA_LN_APPL_DATA_ID; i++)
    {
      EERAM_ApplDataId[i] = EEDEF_ApplDataId[i];
    }
    EEPP_WriteData(EEPP_HDL_ApplDataId, NULL);
    check_DataSwV = FALSE;
  }

  /* check $F1A5 */
  for (i=0U; i < UDSA_LN_ISO; i++)
  {
    if (EERAM_ISOCode[i] != EEDEF_ISOCode[i])
    {
      check_ISOCode = TRUE;
      i = UDSA_LN_ISO;
    }
  }

  if(check_ISOCode == TRUE)
  {
    for (i=0U; i < UDSA_LN_ISO; i++)
    {
      EERAM_ISOCode[i] = EEDEF_ISOCode[i];
    }
    EEPP_WriteData(EEPP_HDL_ISOCode, NULL);
    check_ISOCode = FALSE;
  }
}

/**
 * @brief Get status of IgnitionPreStartLogic
 * @param none
 * @return PRES_State_t
 * @retval Status of IgnitionPreStartLogic
 */
PRES_State_t FUNP_GetIgnitionPreStartLogic(void)
{
  PRES_State_t valueReturn;

  if ((EERAM_SysConfigProxy.IgnitionPreStartLogic & 0x80) == 0x80)
  {
    valueReturn = S_ON;
  }
  else
  {
    valueReturn = S_OFF;
  }

  return valueReturn;
}

/**
 * @brief Get status of Country Code
 * @param none
 * @return FUNP_ProxiCountriCode_t
 * @retval Status of EERAM_Proxi_Country_Code
 */
FUNP_ProxiCountriCode_t FUNP_GetCountryCode(void)
{
  return (EERAM_Proxi_Country_Code);
}

/**
 * @brief Set status of Country Code
 * @param none
 * @return FUNP_ProxiCountriCode_t
 * @retval Status of EERAM_Proxi_Country_Code
 */
void FUNP_SetCountryCode(FUNP_ProxiCountriCode_t PrivateCountryCode)
{
  EERAM_Proxi_Country_Code = PrivateCountryCode;
}

/**
 * @brief Test if Country Code different from USA OR CANADA OR MEXICO values
 * @param none
 * @return bool_t
 * @retval Status of test
 */
bool_t FUNP_IsShortComfortTimer(void)
{
  bool_t valueReturn;

  if ((EERAM_Proxi_Country_Code == FUNP_COUNTRY_USA)    ||
      (EERAM_Proxi_Country_Code == FUNP_COUNTRY_CANADA) ||
      (EERAM_Proxi_Country_Code == FUNP_COUNTRY_MEXICO))
  {
    valueReturn = FALSE;
  }
  else
  {
    valueReturn = TRUE;
  }

  return valueReturn;
}

bool FUNP_IsSlideActive(void)
{
  bool ret_val;

  ret_val = (IPOC_GetDirection(IPOC_Slide) == IPOC_CMD_IDLE) ? FALSE : TRUE;

  return ret_val;
}

/**
 * @brief This function checks if hall sensor is in fail. It does not perform eletrical diagnose
 * @param [in] None
 * @param [out] None
 * @return bool
 */
bool FUNP_IsHallFail(u08 motor)
{
  bool ret_val;

  if (MOTP_GetPosFbkDiag((MOTP_Handle_t)motor) == PRES_TOO_FEW_TRANS)
  {
    ret_val = TRUE;
  }
  else
  {
    ret_val = FALSE;
  }

  return ret_val;
}

/**
 * @brief Function used to activate hall. It saves how many modules are using hall, to know when
 * switching off
 * @param [in] None
 * @param [out] None
 * @return None
 */
void FUNP_HallActive(void)
{
  if (HallCounter == 0)
  {
    DOVFC_SetState(DOVFC_7V5Hall, S_ON);
    /* call macro to notify other modules that hall has been activated */
    FUNP_HALL_ON_EVENT()
  }
  /* increment modules counter that are using hall */
  // HallCounter = ( HallCounter < HALL_NUM_MODULES ) ? (++HallCounter) : (HallCounter);
  /* MISRA 12.13 */
  if ( HallCounter < HALL_NUM_MODULES )
  {
    HallCounter++;
  }
}

/**
 * @brief Function used to disable hall, if no modules are using it
 * @param [in] None
 * @param [out] None
 * @return None
 */
void FUNP_HallInactive(void)
{
  if (HallCounter > 0)
  {
    HallCounter--;
  }
  if (HallCounter == 0)
  {
    DOVFC_SetState(DOVFC_7V5Hall, S_OFF);
    /* call macro to notify other modules that hall has been deactivated */
    FUNP_HALL_OFF_EVENT()
  }
}

/**
 * @brief Function to retrieve if hall are currently active or not
 * @param [in] None
 * @param [out] None
 * @return bool
 */
bool FUNP_IsHallActive(void)
{
  bool ret_val;

  if (HallCounter == 0) 
  {
    ret_val = FALSE;
  }
  else
  {
    ret_val = TRUE;
  }

  return ret_val;
}
#endif /* end __FVMP_IS_PRESENT__ */

/*______ E N D _____ (funp.c) ________________________________________________*/
