/********************************************************************************/
/* @F_PROJECT:          MSM952                                                  */
/* F_NAME:              SNSP_config.c                                           */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Livio Bastonero                                         */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FF3                                  */
/* F_CREATION_DATE:     26/06/2015                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|------------------------------------------------------------------------------
|                A U T H O R   I D E N T I T Y
|------------------------------------------------------------------------------
| Initials      Name                      Company
| --------      ---------------------     -------------------------------------
| LB            Livio Batonero       Bitron S.p.A.
|------------------------------------------------------------------------------
|                R E V I S I O N   H I S T O R Y
|------------------------------------------------------------------------------
| Date         Ver  Author  Description
| -----------  ---  ------  ----------------------------------------------------
| 26/06/2015  0.1  LB      First draft
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "SNSP.h"
#include "SNSP_config.h"

/* Module inhibition filter */
#ifdef __SNSP_IS_PRESENT__

#define MOTP_CFGIF_OWNER

/*____________________G L O B A L - DATA _____________________________________*/

const SNSP_CfgTable_t SNSP_CfgTable[SNSP_HDL_MAX] =
{
/*   SNSP_HANDLE      |          TEMPERATURE ERROR FUNCTION */
{/*    SNSP_SEAT_DRV,*/          SNSP_GetNTCTemperatureErrorDriver },
{/*    SNSP_SEAT_PASS,*/         SNSP_GetNTCTemperatureErrorPassenger },
{/*    SNSP_STEER_WHEEL,*/       SNSP_GetNTCTemperatureErrorSteer }
};

/*______ L O C A L - D A T A _________________________________________________*/

//Note: the abscissa values must be in increasing order, for the binary search and conversion alghoritm
const FUNP_Interp_curve_point_t Snsp_NTC_Table[Snsp_NTC_TABLE_NUM_POINT] =
{
/*
 +--------+-------------+----------------+
 | number |  ADC val(X) | temperature(Y) |
 |        |             |     [0.1°C]    |
 +--------+-------------+----------------+   */
  /* 01 */{     81      ,       850      },
  /* 02 */{     95      ,       800      },
  /* 03 */{    110      ,       750      },
  /* 04 */{    128      ,       700      },
  /* 05 */{    148      ,       650      },
  /* 06 */{    172      ,       600      },
  /* 07 */{    199      ,       550      },
  /* 08 */{    230      ,       500      },
  /* 09 */{    266      ,       450      },
  /* 10 */{    307      ,       400      },
  /* 11 */{    352      ,       350      },
  /* 12 */{    401      ,       300      },
  /* 13 */{    455      ,       250      },
  /* 14 */{    511      ,       200      },
  /* 15 */{    568      ,       150      },
  /* 16 */{    580      ,       140      },
  /* 17 */{    591      ,       130      },
  /* 18 */{    603      ,       120      },
  /* 19 */{    614      ,       110      },
  /* 20 */{    626      ,       100      },
  /* 21 */{    637      ,        90      },
  /* 22 */{    648      ,        80      },
  /* 23 */{    660      ,        70      },
  /* 24 */{    671      ,        60      },
  /* 25 */{    682      ,        50      },
  /* 26 */{    693      ,        40      },
  /* 27 */{    704      ,        30      },
  /* 28 */{    715      ,        20      },
  /* 29 */{    725      ,        10      },
  /* 30 */{    736      ,         0      },
  /* 31 */{    746      ,       -10      },
  /* 32 */{    756      ,       -20      },
  /* 33 */{    766      ,       -30      },
  /* 34 */{    775      ,       -40      },
  /* 35 */{    785      ,       -50      },
  /* 36 */{    794      ,       -60      },
  /* 37 */{    803      ,       -70      },
  /* 38 */{    812      ,       -80      },
  /* 39 */{    821      ,       -90      },
  /* 40 */{    829      ,      -100      },
  /* 41 */{    867      ,      -150      },
  /* 42 */{    900      ,      -200      },
  /* 43 */{    928      ,      -250      },
  /* 44 */{    950      ,      -300      },
  /* 45 */{    968      ,      -350      },
  /* 46 */{    982      ,      -400      }
};


/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/**
 * @brief This function returns the temperature and the fault of the driver seat sensor
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] none
 * @param [out] none
 *
 * @return SNSP_FunRet_t
 * @retval temperature and fault of the driver seat sensor
 */
SNSP_FunRet_t SNSP_GetNTCTemperatureErrorDriver(void)
{
  return Snsp_Temp_Error((int16_t)ADCC_GetChnAvrgData(ADCC_NtcDrv), (int16_t)ADCC_GetChnAvrgData(ADCC_NtcVFbk), Snsp_NTC_Table, Snsp_NTC_TABLE_NUM_POINT);
}


/**
 * @brief This function returns the temperature and the fault of the passenger seat sensor
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] none
 * @param [out] none
 *
 * @return SNSP_FunRet_t
 * @retval temperature and fault of the passenger seat sensor
 */
SNSP_FunRet_t SNSP_GetNTCTemperatureErrorPassenger(void)
{
  return Snsp_Temp_Error((int16_t)ADCC_GetChnAvrgData(ADCC_NtcPass), (int16_t)ADCC_GetChnAvrgData(ADCC_NtcVFbk), Snsp_NTC_Table, Snsp_NTC_TABLE_NUM_POINT);
}

/**
 * @brief This function returns the temperature and the fault of the steering wheel sensor
 * @author Bastonero Livio - Bitron S.p.A.
 * @param [in] none
 * @param [out] none
 *
 * @return SNSP_FunRet_t
 * @retval temperature and fault of the steering wheel sensor
 */
SNSP_FunRet_t SNSP_GetNTCTemperatureErrorSteer(void)
{
  SNSP_FunRet_t ret_val;
  StW_TempSensSts_t error;

  ret_val.temperature = (((int16_t)CMMD_StW_TempSts * 10U) >> 1U) - 400U;
  error = (StW_TempSensSts_t)CMMD_StW_TempSensSts;

  if (error == CMMD_NORMALOPERATION_OK)
  {
    ret_val.error = PRES_NO_FAULT;
  }
  else
  {
    ret_val.error = PRES_SIGNAL_SIGNAL_INVALID;
  }

  return ret_val;
}


#endif /* __SNSP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

