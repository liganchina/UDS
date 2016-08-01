/******************************************************************************/
/** @file       HEATA.c                                                       */
/** @title      Heater presentation                                           */
/** @brief      module for Heater management                                  */
/** @date       08/05/2015                                                    */
/** @author     Livio Bastonero                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| LB           Livio Bastonero		     Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 19/06/2015 0.1  LB      First draft
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define HEATA_IF_OWNER

#include "HEATA.h"
#include "HEATA_config.h"

/* Module inhibition filter */
#ifdef __HEATA_IS_PRESENT__
/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/

/*_____ G L O B A L - T Y P E S ______________________________________________*/

/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/*_____ P R I V A T E - D E F I N E __________________________________________*/

/*_____ P R I V A T E - T Y P E S ____________________________________________*/
typedef struct HEATA_privateData_s
{
  uint8_t          current_request_level   :8;
  uint8_t          request_level           :8;
  uint8_t          output_duty_cycle       :8;
  PRES_Fault_t     local_fault     		   :8;
  bool_t           fault_present           :1;
  bool_t           running                 :1;
  bool_t           ioControlActive         :1;
}Heata_privateData_t;

/*_____ P R I V A T E - D A T A ______________________________________________*/
static Heata_privateData_t Heata_privateTable[HEATA_MAX_HDL];
static uint16_t Level_Transition_Timer[HEATA_MAX_HDL];
static uint16_t Activation_Timer[HEATA_MAX_HDL];

/**
 * @brief The function performs the initialization of the structure array
 *        Heata_privateTable[hdl]
 *
 * @param [in] none
 *
 * @param [out]none
 *
 * @return None
 *
 */
void HEATA_Init(void)
{
  HEATA_handle_t hdl;

  /* intialize private data */
  for( hdl = (HEATA_handle_t)0u; hdl < HEATA_MAX_HDL; hdl++)
  {
    Heata_privateTable[hdl].current_request_level   = 0U;
    Heata_privateTable[hdl].request_level           = 0U;
    Heata_privateTable[hdl].output_duty_cycle       = 0U;
    Heata_privateTable[hdl].local_fault             = PRES_NO_FAULT;
    Heata_privateTable[hdl].fault_present           = FALSE;
    Heata_privateTable[hdl].running                 = TRUE;
    Heata_privateTable[hdl].ioControlActive         = FALSE;

    // init of timers
    Level_Transition_Timer[hdl] = 0U;
    Activation_Timer[hdl] = 0U;
  }
}

/**
 * @brief The function manages the heating of the driver seat, of the passenger seat
 *        and of the steering wheel. It is called with a period of 100 ms.
 *
 * @param [in] none
 *
 * @param [out]none
 *
 * @return None
 *
 */
void HEATA_Mgm (void)
{
  HEATA_handle_t hdl;
  PRES_Fault_t driver_fault, ntc_fault, timeout_fault;
  bool_t driver_is_destructive, ntc_is_destructive, timeout_is_destructive;

  /* L.B. init debug : toggle of output DIOD_PneuSysEN (P71) */
//  if(DIOD_GetLevel(DIOD_SteerHeat)== L_LOW)
//  {
//    DIOD_SetLevel(DIOD_SteerHeat, L_HIGH);
//  }
//  else
//  {
//    DIOD_SetLevel(DIOD_SteerHeat, L_LOW);
//  }
  /* L.B. end debug : toggle of output DIOD_PneuSysEN (P71) */

  /* this function (implemented in HEATA_Config.c) update the heating commands by calling HEATA_SetLevel() */
//  HEATA_CommandUpdate();

  for( hdl = (HEATA_handle_t)0u; hdl < HEATA_MAX_HDL; hdl++)
  {
    if(Heata_privateTable[hdl].current_request_level != Heata_privateTable[hdl].request_level)
    {
      /* the command has changed,  reset the fault information */
      FVMP_ResetLine(HEATA_CfgTable[hdl].PWM_FAULT_LINE);
      //FVMP_ResetLine(HEATA_CfgTable[hdl].NTC_FAULT_LINE);
      HEATA_ResetLine(hdl);
    }

    if (Heata_privateTable[hdl].request_level == HEATA_CfgTable[hdl].SUSP_CMD)
    {
      /* suspend command received from other modules */
      Heata_privateTable[hdl].running = FALSE;
      PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, 0u);
    }
    else
    {
      /* Update current_level */
      Heata_privateTable[hdl].running = TRUE;
      Heata_privateTable[hdl].current_request_level = Heata_privateTable[hdl].request_level;
    }

    if(Heata_privateTable[hdl].running)
    {
      driver_fault = PRES_NO_FAULT;
      driver_is_destructive = FALSE;
      ntc_fault = PRES_NO_FAULT;
      ntc_is_destructive = FALSE;
      timeout_fault = PRES_NO_FAULT;
      timeout_is_destructive = FALSE;

      if(driver_fault == PRES_NO_FAULT)
      {
        /* Check if some fault on HEATER PWM is present and validated */
        FVMP_GetDiag(HEATA_CfgTable[hdl].PWM_FAULT_LINE, &driver_fault, &driver_is_destructive);
      }

      if(ntc_fault == PRES_NO_FAULT)
      {
        /* Check if some fault on NTC sensor is present and validated */
        FVMP_GetDiag(HEATA_CfgTable[hdl].NTC_FAULT_LINE, &ntc_fault, &ntc_is_destructive); // vedere con Cloralio per stato NTC steering wheel
      }

      if(timeout_fault == PRES_NO_FAULT)
      {
        /* Check if a TIMEOUT fault is present and validated */
        HEATA_GetDiag(hdl, &timeout_fault, &timeout_is_destructive);
      }

      if((driver_fault != PRES_NOT_TESTED) && (driver_fault != PRES_NO_FAULT))
      {
        if(driver_is_destructive)
        {
          //HEATA_SetLevel(hdl,0u);
          /* set the duty cycle to 0*/
          PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, 0u);
        }
        //         HEATA_TempReg(hdl,Heata_privateTable[hdl].request_level);
        Heata_privateTable[hdl].fault_present = TRUE;
        Heata_privateTable[hdl].output_duty_cycle = 0U;
      }
      else
      {
        if(((ntc_fault != PRES_NOT_TESTED) && (ntc_fault != PRES_NO_FAULT)) ||
            ((timeout_fault != PRES_NOT_TESTED) && (timeout_fault != PRES_NO_FAULT)))
        {
          //            HEATA_SetLevel(hdl,0u);
          //            HEATA_TempReg(hdl,Heata_privateTable[hdl].request_level);
          HEATA_SetLevel(hdl,0u);
          /* set the duty cycle to 0*/
          PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, 0u);

          Heata_privateTable[hdl].fault_present = TRUE;
          Heata_privateTable[hdl].output_duty_cycle = 0U;
        }
        else
        {
          Heata_privateTable[hdl].fault_present = FALSE;
          HEATA_TempReg(hdl,(uint8_t)Heata_privateTable[hdl].request_level);
        }
      }
      /* update the Duty Cycle only if IOControl for this handle is not active */
      if((Heata_privateTable[hdl].ioControlActive == FALSE) &&
          (Heata_privateTable[hdl].fault_present == FALSE))
      {
        /* set the right level duty cycle */
        PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, (uint8_t)Heata_privateTable[hdl].output_duty_cycle);
      }
    }//if Runnning - END
    //      /* Update current_level */
    //      Heata_privateTable[hdl].current_request_level = Heata_privateTable[hdl].request_level;
  }//for
}

/**
 * @brief The function allows to set the heating request level.
 *        It stores the requested heating level
 *        into variable Heata_privateTable[hdl].request_level
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [in] level: This input specifies the required heating level.
 *             For the driver and passenger seats the possible values are
 *             HEATA_LEVEL_0, HEATA_LEVEL_1, HEATA_LEVEL_2, HEATA_LEVEL_3
 *             For the steering wheel the possible values are HEATA_LEVEL_0, HEATA_LEVEL_1
 *
 * @param [out] None
 *
 * @return APPL_ResSts_t
 * @retval APPL_OK if the input parameters are correct
 *
 * @retval APPL_PAR_NOT_OK if the device does not exist or if the level value
 * is not correct
 */
APPL_ResSts_t HEATA_SetLevel(HEATA_handle_t hdl,uint8_t level)
{
  APPL_ResSts_t ret_val = APPL_OK;

  if(hdl >= HEATA_MAX_HDL)
  {
    ret_val = APPL_PAR_NOT_OK;
  }
  else
  {
    /* update the required level only if IOControl for this hande is not active */
    if(Heata_privateTable[hdl].ioControlActive == FALSE)
    {
      /* Check if parameter are in range */
      if((level > HEATA_CfgTable[hdl].NUM_LEVEL) && 
         (level != HEATA_CfgTable[hdl].SUSP_CMD))
      {
        /* Check if parameter are in range */
        ret_val = APPL_PAR_NOT_OK;
        Heata_privateTable[hdl].request_level = 0u;
      }
      else
      {
        /* parameters OK, change the requested level */
        Heata_privateTable[hdl].request_level = level;
      }
    }

  }
  return ret_val;
}

/**
 * @brief The function implements the temperature regulation for the driver seat,
 *        the passenger seat and the steering wheel. It stores the computed duty cycle
 *        into variable Heata_privateTable[hdl].output_duty_cycle
 *
 * @param [in] hdl: This input specifies the device whose temperature is regulated.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [in] level: This input specifies the required heating level.
 *             For the driver and passenger seats the possible values are
 *             HEATA_LEVEL_0, HEATA_LEVEL_1, HEATA_LEVEL_2, HEATA_LEVEL_3
 *             For the steering wheel the possible values are HEATA_LEVEL_0, HEATA_LEVEL_1
 *
 * @param [out] None
 *
 * @return APPL_ResSts_t
 * @retval APPL_OK if the input parameters are correct
 *
 * @retval APPL_PAR_NOT_OK if the device does not exist or if the level value
 * is not correct
 */

APPL_ResSts_t HEATA_TempReg(HEATA_handle_t hdl,uint8_t level)
{
  static uint8_t Level_State[HEATA_MAX_HDL] = {HL0,HL0,WL0};
  static uint8_t level_old[HEATA_MAX_HDL] = {HEATA_LEVEL_0, HEATA_LEVEL_0, HEATA_LEVEL_0};
//  static uint16_t safety_timer[HEATA_MAX_HDL]  = {0u,0u,0u};
//  static int16_t measured_temperature_old[HEATA_MAX_HDL];
  int16_t measured_temperature;
  APPL_ResSts_t ret_val = APPL_OK;

  if(hdl >= HEATA_MAX_HDL)
  {
    ret_val = APPL_PAR_NOT_OK;
  }
  else
  {
    /* update the required level only if IOControl for this handle is not active */
    if(Heata_privateTable[hdl].ioControlActive == FALSE)
    {
      if(level <= HEATA_CfgTable[hdl].NUM_LEVEL)
      {
        /* Compute the measured temperature for the device */
        measured_temperature  = SNSP_GetTemperature(HEATA_CfgTable[hdl].TEMP_HANDLE);
        switch(Level_State[hdl])
        {
          /* The states WL3 - WL0 are used for the steering wheel*/
          case WL3:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.D_3;
            if (level == HEATA_LEVEL_0)
            {
              Level_State[hdl] = WL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
//                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp_StW) || (Activation_Timer[hdl] == 0U))
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp_StW) ||
                    ((EERAM_HeatTimeParam.T3SW - Activation_Timer[hdl]) >= EERAM_HeatTimeParam.T1))
                {
                    Level_State[hdl] = WL2;
                    Level_Transition_Timer[hdl] = EERAM_HeatTimeParam.T_wait_1;
//                    Activation_Timer[hdl] = EERAM_HeatTimeParam.T2;
                }
            }
            else
            {
            }
          break;

          case WL2:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.D_2;
            if (level == HEATA_LEVEL_0)
            {
              Level_State[hdl] = WL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
//                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp_StW) || (Activation_Timer[hdl] == 0U))
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp_StW) ||
                    ((EERAM_HeatTimeParam.T3SW - Activation_Timer[hdl]) >= EERAM_HeatTimeParam.T2))
                {
                        Level_State[hdl] = WL1;
//                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T3SW;
                }
            }
            else
            {
            }
          break;

          case WL1:    /* This case is entered only for the steering wheel */
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.DWL1;
            if (level == HEATA_LEVEL_0)
            {
              Level_State[hdl] = WL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp_StW) || (Activation_Timer[hdl] == 0U))
                {
                      Level_State[hdl] = WL0;
                      Activation_Timer[hdl] = 0U;
                }
            }
            else
            {
            }
          break;

          case WL0:
            Heata_privateTable[hdl].output_duty_cycle = 0U;
            Level_Transition_Timer[hdl] = 0U;
            if(measured_temperature < EERAM_HeatTempParam.Temp_lim)
            {
                if(level > HEATA_LEVEL_0)
                {
                    Level_State[hdl] = WL3;
//                    Activation_Timer[hdl] = EERAM_HeatTimeParam.T1;
                    Activation_Timer[hdl] = EERAM_HeatTimeParam.T3SW;
                }
            }
          break;

          /* The states HL3 - HL0 are used for the driver and passenger seats */
          case HL3:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.D_3;
            if ((level != level_old[hdl]) || (measured_temperature <= EERAM_HeatTempParam.Temp_range_min) ||
                (measured_temperature >= EERAM_HeatTempParam.Temp_range_max))
            {
              Level_State[hdl] = HL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
//                if((measured_temperature >= EERAM_Max_Av_Surf_Temp) || (Activation_Timer[hdl] == 0U))
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp) || ((EERAM_HeatTimeParam.T4 - Activation_Timer[hdl]) >= EERAM_HeatTimeParam.T1))
                {
                    Level_State[hdl] = HL2;
                    Level_Transition_Timer[hdl] = EERAM_HeatTimeParam.T_wait_1;
//                    Activation_Timer[hdl] = EERAM_HeatTimeParam.T2;
                }
            }
            else
            {
            }
          break;

          case HL2:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.D_2;
            if ((level != level_old[hdl]) || (measured_temperature <= EERAM_HeatTempParam.Temp_range_min)
                || (measured_temperature >= EERAM_HeatTempParam.Temp_range_max))
            {
              Level_State[hdl] = HL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
//                if((measured_temperature >= EERAM_Max_Av_Surf_Temp) || (Activation_Timer[hdl] == 0U))
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp) || 
                   ((EERAM_HeatTimeParam.T4 - Activation_Timer[hdl]) >= EERAM_HeatTimeParam.T2))
                {
                        Level_State[hdl] = HL1;
                        Level_Transition_Timer[hdl] = EERAM_HeatTimeParam.T_wait_2;
//                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T3HS;
                }
            }
            else
            {
            }
          break;

          case HL1:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.DHL1;
            if ((level != level_old[hdl]) || (measured_temperature <= EERAM_HeatTempParam.Temp_range_min)
                || (measured_temperature >= EERAM_HeatTempParam.Temp_range_max))
            {
              Level_State[hdl] = HL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
//                if((measured_temperature >= EERAM_Max_Av_Surf_Temp) || (Activation_Timer[hdl] == 0U))
                if((measured_temperature >= EERAM_HeatTempParam.Max_Av_Surf_Temp) || 
                   ((EERAM_HeatTimeParam.T4 - Activation_Timer[hdl]) >= EERAM_HeatTimeParam.T3HS))
                {
                    Level_State[hdl] = LL1;
//                    Activation_Timer[hdl] = EERAM_HeatTimeParam.T4;
                }
            }
            else
            {
            }
          break;

          case LL1:
            Heata_privateTable[hdl].output_duty_cycle = EERAM_HeatDutyParam.DLL1;
            if ((level != level_old[hdl]) || (measured_temperature <= EERAM_HeatTempParam.Temp_range_min) ||
                (measured_temperature >= EERAM_HeatTempParam.Temp_range_max))
            {
              Level_State[hdl] = HL0;
              Activation_Timer[hdl] = 0U;
              Level_Transition_Timer[hdl] = 0U;
            }
            else if(Level_Transition_Timer[hdl] == 0U)
            {
                if(Activation_Timer[hdl] == 0U)
                {
                    Level_State[hdl] = HL0;
                }
            }
            else
            {
            }
          break;

          case HL0:
            Heata_privateTable[hdl].output_duty_cycle = 0U;
            Level_Transition_Timer[hdl] = 0U;
                if((measured_temperature > EERAM_HeatTempParam.Temp_range_min) && (measured_temperature < EERAM_HeatTempParam.Temp_range_max))
                {
                    if(level == HEATA_LEVEL_3)
                    {
                        Level_State[hdl] = HL3;
//                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T1;
                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T4;
                    }
                    if(level == HEATA_LEVEL_2)
                    {
                        Level_State[hdl] = HL1;
//                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T3HS;
                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T4;
                    }
                    if(level == HEATA_LEVEL_1)
                    {
                        Level_State[hdl] = LL1;
                        Activation_Timer[hdl] = EERAM_HeatTimeParam.T_low;
                    }
                }
          break;

          default:
          break;
        }       // End of switch

        level_old[hdl] = level;

/* Management of Activation_Timer[hdl] */
//        if(Activation_Timer[hdl] > 0U)
//        {
//            Activation_Timer[hdl]--;
//        }

/* Management of Level_Transition_Timer[hdl] */
//        if(Level_Transition_Timer[hdl] > 0U)
//        {
//            Level_Transition_Timer[hdl]--;
//        }

/* Management of Safety_Timer[hdl] */
//        if(((Level_State[hdl] != HL0) && (HEATA_CfgTable[hdl].NUM_LEVEL == 3u))/* ||
//           ((Level_State[hdl] != WL0) && (HEATA_CfgTable[hdl].NUM_LEVEL == 1u))*/)
//        {
//          if(safety_timer[hdl] < (uint16_t)T_15_MIN)
//          {
//            safety_timer[hdl]++;
//          }
//          else
//          {
//            safety_timer[hdl] = 0u;
//          }
//        }
//        else
//        {
//          safety_timer[hdl] = 0U;
//        }
//
//        if(safety_timer[hdl] == 1u)
//        {
//            measured_temperature_old[hdl] = measured_temperature;
//        }
//
//        if(safety_timer[hdl] == (uint16_t)(T_15_MIN - 1U))
//        {
//            if ((measured_temperature < (measured_temperature_old[hdl] + 10)) ||
//                (measured_temperature > (measured_temperature_old[hdl] - 10)))
//            {
//                HEATA_SetLine(hdl);
//            }
//        }

      }
      else
      {
          ret_val = APPL_PAR_NOT_OK;
      }
    }
  }
  return ret_val;
}

void HEATA_ManageTimer_1s(void)
{
  u08 hdl;

  for( hdl = (HEATA_handle_t)0u; hdl < HEATA_MAX_HDL; hdl++)
  {   
    /* decrease counter only if heater has not been suspended */
    if(Heata_privateTable[hdl].running)
    {
      /* Management of Activation_Timer[hdl] */
      if(Activation_Timer[hdl] > 0U)
      {
        Activation_Timer[hdl]--;
      }
      /* Management of Level_Transition_Timer[hdl] */
      if(Level_Transition_Timer[hdl] > 0U)
      {
        Level_Transition_Timer[hdl]--;
      }
    }
  }
}

/**
 * @brief The function allows to read the local fault
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]fault: This output returns the fault set by the application
 *             The possible values are PRES_GENERIC_FAULT, PRES_NO_FAULT, PRES_NOT_TESTED
 *
 * @param [out]destructive: This output returns the fault type set by the application
 *             The possible values are TRUE or FALSE
 *
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT if the input parameters are correct
 *
 * @retval CTRL_NOT_TESTED if the device does not exist
 *
 */
CTRL_Fault_t HEATA_GetDiag(HEATA_handle_t hdl, PRES_Fault_t* fault,
    bool_t* destructive)
{
  CTRL_Fault_t faultTmp;
  /* Update fault information */
  if (hdl < HEATA_MAX_HDL)
  {
    *fault        = (PRES_Fault_t)Heata_privateTable[hdl].local_fault;
    *destructive  = FALSE;
    faultTmp   = CTRL_NO_FAULT;
  }
  else
  {
    *fault        = PRES_NOT_TESTED;
    *destructive  = FALSE;
    faultTmp   = CTRL_NOT_TESTED;
  }
  return (faultTmp);
}

/**
 * @brief The function allows to reset the local fault by modifying the variable
 *        Heata_privateTable[hdl].local_fault.
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]none
 *
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT if the input parameters are correct
 *
 * @retval CTRL_NOT_TESTED if the device does not exist
 *
 */
CTRL_Fault_t HEATA_ResetLine(HEATA_handle_t hdl)
{
  CTRL_Fault_t faultTmp;
  /* Update fault information */
  if (hdl < HEATA_MAX_HDL)
  {
     Heata_privateTable[hdl].local_fault = PRES_NO_FAULT;
     faultTmp   = CTRL_NO_FAULT;
  }
  else
  {
    Heata_privateTable[hdl].local_fault = PRES_NOT_TESTED;
    faultTmp   = CTRL_NOT_TESTED;
  }
  return (faultTmp);
}

/**
 * @brief The function allows to set the local fault by modifying the variable
 *        Heata_privateTable[hdl].local_fault.
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]none
 *
 * @return CTRL_Fault_t
 * @retval CTRL_NO_FAULT if the input parameters are correct
 *
 * @retval CTRL_NOT_TESTED if the device does not exist
 *
 */
CTRL_Fault_t HEATA_SetLine(HEATA_handle_t hdl)
{
  CTRL_Fault_t faultTmp;
  /* Update fault information */
  if (hdl < HEATA_MAX_HDL)
  {
     Heata_privateTable[hdl].local_fault = PRES_GENERIC_FAULT;
     faultTmp   = CTRL_NO_FAULT;
  }
  else
  {
    Heata_privateTable[hdl].local_fault = PRES_NOT_TESTED;
    faultTmp   = CTRL_NOT_TESTED;
  }
  return (faultTmp);
}


HEATA_EXTERN u08 HEATA_CheckIoControl(u08 hdl, u08 command)
{
  u08 ret_val;
  CTRL_Fault_t fbkMot;
  
  ret_val = SERVICE_OK;
  fbkMot = ADCC_GetDiag(ADCC_MOT_Fbk);

  /* NACK 31 should have higher priority than NACK 22*/
  
  // Daniele: IoControl set only ON\OFF level (50% or 0% duty cycle)
  /* check the required command according to levels type (level or direct duty cycle vale) */
  if(HEATA_CfgTable[hdl].NUM_LEVEL == 0U)
  {
    /* Check if parameter are in range */
    if (command > 100U)
    {
      ret_val = REQUEST_OUT_OF_RANGE;
    }
  }
  else if ((command != ON) && (command != OFF))
  {
    /* Check if parameter are in range */     
    ret_val = REQUEST_OUT_OF_RANGE;
  }
  /* check all conditions to start heating are satisfied */
  else if((VF608_GetOperationalModeSts() != CMMD_IGNITION_ON_ENGON)    ||
          (fbkMot != CTRL_NO_FAULT))
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }
  else
  {
    /* MISRA 14.10 */
  }

  return ret_val;
}

/**
 * @brief The function allows to shift control from the application to the
 *        diagnostics service
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [in] level: This input specifies the required heating level.
 *             For the driver and passenger seats the possible values are
 *             HEATA_LEVEL_0, HEATA_LEVEL_1, HEATA_LEVEL_2, HEATA_LEVEL_3
 *             For the steering wheel the possible values are HEATA_LEVEL_0, HEATA_LEVEL_1
 *
 * @param [out]none
 *
 * @return None
 *
 */
void HEATA_StartIoControl(uint8_t hdl, uint8_t level)
{
  Heata_privateTable[hdl].ioControlActive = TRUE;
  if (level == 0U)
  {
    PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, HEATA_DUTY_OFF);
  }
  else
  {
    PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, HEATA_DUTY_ON);
  }
}

/**
 * @brief The function allows the application to resume control (before was held by
 *        the diagnostics service)
 *
 * @param [in] hdl: This input specifies the device.
 *             It can assume the values HEATA_SEAT_DRV, HEATA_SEAT_PSG, HEATA_STW.
 *
 * @param [out]none
 *
 * @return None
 *
 */
void HEATA_StopIoControl(uint8_t hdl)
{
  PWMC_SetDuty(HEATA_CfgTable[hdl].PWM_HANDLE, HEATA_DUTY_OFF);
  Heata_privateTable[hdl].ioControlActive = FALSE;
}

u08 HEATA_GetLevel(HEATA_handle_t hdl)
{
  u08 ret_val = 0U;

  if (hdl < HEATA_MAX_HDL)
  {
     ret_val = (u08)Heata_privateTable[hdl].request_level;
  }

  return ret_val;
}

#endif
/*______ E N D _____ (FANA.c) _________________________________________*/
