/******************************************************************************/
/** @file       SNSP.c                                                        */
/** @title      SNSP sensor Control                                           */
/** @brief      Computes NTC sensor temperature and range                     */
/** @date       19/06/2015                                                    */
/** @author     Bastonero Livio                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2015 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Bastonero Livio
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 19/06/2015 0.1  MM      First draft
|-----------------------------------------------------------------------------
|            1.0  MM      First release
|-----------------------------------------------------------------------------
*/

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "SNSP.h"
#include "SNSP_config.h"


/* Module inhibition filter */
#ifdef __SNSP_IS_PRESENT__


/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct SNSP_PrivateData_s
{
  int16_t           temperature;
  PRES_Fault_t      diag;
  PRES_EnSts_t      functionState;   /*Function State, enabled/disabled by proxi*/
}Snsp_PrivateData_t;

/*______ P R I V A T E - D A T A _____________________________________________*/

static Snsp_PrivateData_t Snsp_PrivateData[SNSP_HDL_MAX];


/*______ L O C A L - M A C R O S _____________________________________________*/

/**
 * @brief Initialization routine for SNSP control module.
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 * @return None
 */
void SNSP_Init(void)
{
  SNSP_Handle_t hdl;

  for (hdl = (SNSP_Handle_t)0; hdl < SNSP_HDL_MAX; hdl++)
  {
    Snsp_PrivateData[hdl].temperature   = 850;
    Snsp_PrivateData[hdl].diag          = PRES_NOT_TESTED;
    Snsp_PrivateData[hdl].functionState = PRES_ENABLE;
  }
}

/**
 * @brief Computes the temperature and the diag state of the NTC sensor
          Stores the results into SNS_PrivateData
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */

void SNSP_Mgm(void)
{
  SNSP_Handle_t hdl;
  SNSP_FunRet_t temp;

    for (hdl = (SNSP_Handle_t)0; hdl < SNSP_HDL_MAX; hdl++)
    {
      if(Snsp_PrivateData[hdl].functionState == PRES_ENABLE)
      {
        temp  = SNSP_CfgTable[hdl].GetNTCTempError();

        Snsp_PrivateData[hdl].temperature = temp.temperature;

        if(temp.error != PRES_NOT_TESTED)
        {
          Snsp_PrivateData[hdl].diag = temp.error;
        }
      }
      else
      {}
    }
}



/**
 * @brief This function returns the electrical diagnosis of the selected handle.
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @return PRES_Fault_t
 * @retval PRES_NO_FAULT
 * @retval PRES_SHORT_TO_BAT
 * @retval PRES_SHORT_TO_GND
 * @retval PRES_NOT_TESTED
 */
PRES_Fault_t SNSP_GetDiag(SNSP_Handle_t hdl)
{
  PRES_Fault_t ret_val;

  if (hdl < SNSP_HDL_MAX)
  {
    ret_val = (Snsp_PrivateData[hdl].diag);
  }
  else
  {
  }

  return ret_val;
}

/**
 * @brief This function returns the temperature.
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] hdl signal handle
 * @param [out] none
 * @retval Snsp_PrivateData[hdl].temperatureData
 */
int16_t SNSP_GetTemperature(SNSP_Handle_t hdl)
{
  int16_t ret_val;

  if (hdl < SNSP_HDL_MAX)
  {
    ret_val = (Snsp_PrivateData[hdl].temperature);
  }
  else
  {
  }

  return ret_val;
}


/**
 * @brief This function returns the temperature and the sensor fault
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] X = NTC sensor voltage
 * @param [in] Z = NTC sensor power supply voltage
 * @param [in] TAB[] = Constant array: sensor voltage - temperature
 * @param [in] num_point = Number of points of TAB[] array
 * @param [out] none
 * @retval struct SNSP_FunRet_t containing temperature and sensor fault
 */

SNSP_FunRet_t  Snsp_Temp_Error(int16_t X, int16_t Z, const FUNP_Interp_curve_point_t TAB[], uint8_t num_point)
{
    SNSP_FunRet_t temp;
    int16_t  Xnorm;
    int32_t  comp;

/* Normalization of variable X */
    comp = X*1023L;
    if (Z != 0)
    {
        Xnorm = (int16_t)(comp/Z);
        if(Xnorm > 1023)
        {
            Xnorm = 1023;
        }
     }
     else
     {
        Xnorm = 0;
     }


/* Range determination */
  if ((Xnorm >= TAB[0].X) && (Xnorm <= TAB[num_point - 1U].X))
  {
    temp.error = PRES_NO_FAULT;
  }
  else if(Xnorm < (TAB[0].X - DELTA_HIST_INF))
  {
    temp.error = PRES_SIGNAL_SIGNAL_INVALID;
  }
  else if (Xnorm > (TAB[num_point - 1U].X + DELTA_HIST_SUP))
  {
    temp.error = PRES_SIGNAL_SIGNAL_INVALID;
  }
  else
  {
    temp.error = PRES_NOT_TESTED;
  }

  temp.temperature = FUNP_Curve(Xnorm, TAB, num_point);

  return temp;
}

/**
* @brief This function is used to enable/disable the functions according to the proxi configuration.
* @author Francesco Talarico
* @param hdl is the function line
* @param state is the state of the function (enabled/disabled by proxi)
* @return none
*/
void SNSP_EnableDisable (SNSP_Handle_t hdl, PRES_EnSts_t state)
{
  Snsp_PrivateData[hdl].functionState = state;
}

#endif /* SNSP_IS_PRESENT */

/*_____ E N D _____ (SNSP_if.h) ______________________________________________*/
