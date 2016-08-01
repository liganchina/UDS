/********************************************************************************/
/* @F_PROJECT:          Tesla MSM Model X                                       */
/* F_NAME:              UDSA_RtnConfig.c                                        */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       D. Fogliano                                             */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     19/01/2015                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| DF           Davide Fogliano           Polimatica S.r.l.
| FRAT         Francesco Talarico        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 19/01/2015  0.1  DF       First Implementation, 
| 16/07/2015  1.0  FRAT     Porting from Ferrari NAG/NAP F151M and alignment to Alfa Romeo CCD R5
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA.h"
#include "MOTA_Define.h" /* for slide routine status values */

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/* Start Routine */ 
static u08 Udsa_RtnStartSlideInitialization(u08 *Data, u16 Length);      /*0200*/
static u08 Udsa_RtnStartVINLock(u08 *Data, u16 Length);                  /*2000*/
static u08 Udsa_RtnStartVINUnlock(u08 *Data, u16 Length);                /*2001*/
static u08 Udsa_RtnStartStrokeReset(u08 *Data, u16 Length);              /*F009*/
static u08 Udsa_RtnStartPositionReset(u08 *Data, u16 Length);            /*F00A*/

/* Stop Routine */
static u08 Udsa_RtnStopSlideInitialization(u08 *Data, u16 Length);       /*0200*/
/* Request Routine Result */
static u08 Udsa_RtnResultSlideInitialization(u08 *Data, u16 Length);     /*0200*/


const UDSA_CmdByIdentifier_Service_t UDSA_StartRoutineByIdentifier[MAX_NUM_ROUTINE_START] =              /* Servizio 31 01 - 7 DID */
{
/* +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+
   |   DID     |  En   |RxDL |                           Session                                                                    | Diag type   |                      Callback Function                |
   |           |       |     |                                                                                                      |             |                                                       |
   +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+*/
   { 0x0200u,    ENABLE, 4u,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                                         , UDSA_ADS_PHYS, Udsa_RtnStartSlideInitialization                      },
   { 0x2000u,    ENABLE, 4u,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION                                                              , UDSA_ADS_PHYS, Udsa_RtnStartVINLock                                  },
   { 0x2001u,    ENABLE, 4u,  DIAG_EOL_SESSION                                                                                      , UDSA_ADS_PHYS, Udsa_RtnStartVINUnlock                                },
   { 0xF009u,    ENABLE, 4u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_PHYS, Udsa_RtnStartStrokeReset                              },
   { 0xF00Au,    ENABLE, 4u,  DIAG_SUPPL_SESSION                                                                                    , UDSA_ADS_BOTH, Udsa_RtnStartPositionReset                            },
};

const UDSA_CmdByIdentifier_Service_t UDSA_StopRoutineByIdentifier[MAX_NUM_ROUTINE_STOP] =              /* Servizio 31 02 - 1 DID */
{
/* +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+
   |   DID     |  En   |RxDL |                           Session                                                                    | Diag type   |                      Callback Function                |
   |           |       |     |                                                                                                      |             |                                                       |
   +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+*/
   { 0x0200u,    ENABLE, 4u,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                                         , UDSA_ADS_PHYS, Udsa_RtnStopSlideInitialization                       },
};

const UDSA_CmdByIdentifier_Service_t UDSA_RoutineResultByIdentifier[MAX_NUM_ROUTINE_RESULT] =              /* Servizio 31 03 - 4 DID */
{
/* +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+
   |   DID     |  En   |RxDL |                           Session                                                                    | Diag type   |                      Callback Function                |
   |           |       |     |                                                                                                      |             |                                                       |
   +-----------+-------+-----+------------------------------------------------------------------------------------------------------+-------------+-------------------------------------------------------+*/
   { 0x0200u,    ENABLE, 4u,  DIAG_EXTENDED_SESSION | DIAG_EOL_SESSION | DIAG_SUPPL_SESSION                                         , UDSA_ADS_PHYS, Udsa_RtnResultSlideInitialization                     },
};

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


/******************************************************************************/
/*                   Start Slide Initialization       (RID = 0x0200)          */
/******************************************************************************/
static u08 Udsa_RtnStartSlideInitialization(u08 *Data, u16 Length)
{
  u08  ret_val;
  bool button_pressed;
  
  button_pressed = DISPA_IsButtonPressed();
  
  if ((DISPA_IsSeatMoving()  == FALSE)  &&
      (button_pressed        == FALSE)  &&
      (EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn == ENABLE))
  {
    DISPA_StartInitialization();
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/******************************************************************************/
/*                       Start VIN Lock               (RID = 0x2000)          */
/******************************************************************************/
static u08 Udsa_RtnStartVINLock(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  if(VF607_VINdelivery(EERAM_VINOriginal))
  {
    EERAM_VINLockState = VIN_LOCKED_BY_EXT_TOOL;
    EEPP_WriteData(EEPP_HDL_VINLockState, NULL);
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/******************************************************************************/
/*                   Start VIN Unlock                 (RID = 0x2001)          */
/******************************************************************************/
static u08 Udsa_RtnStartVINUnlock(u08 *Data, u16 Length)
{
  u08 ret_val = SERVICE_OK;

  if ( VIN_SecAccessSts == SEC_ACC_VIN_UNLOCKED )
  {
    if( (VF607_GetVINLock()) != VIN_NOT_LOCKED )
    {
      EERAM_VINLockState = VIN_NOT_LOCKED;
      EEPP_WriteData(EEPP_HDL_VINLockState, NULL);

      /* VF607 ECU Diagnostic requirement */
      EERAM_VINOdometer.VINOdometerLockStatus = VIN_ODO_NOT_LOCKED;
      EERAM_VINOdometer.VINOdometerCount = 0u;
      if( (VF607_VINdelivery(EERAM_VINOriginal)) == FALSE)
      {
        EERAM_VINOdoStart = 0u; /* initial condition: don't start the Mileage Counter */
      }
      else
      {
        EERAM_VINOdometer.MilageOffset = FUNP_GetTotalOdometer(); /* start the Mileage Counter */
        EERAM_VINOdoStart = 1u;
      }

      EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);
      EEPP_WriteData(EEPP_HDL_VINOdoStart, NULL);
    }
  }
  else
  {
    ret_val = SECURITY_ACCESS_DENIED;
  }

  return ret_val;
}

/******************************************************************************/
/*                    Start Stroke reset rotuine      (RID = 0xF009)          */
/******************************************************************************/
static u08 Udsa_RtnStartStrokeReset(u08 *Data, u16 Length)
{
  EERAM_Measured_Motors_Stroke = 32000;
  EEPP_WriteData(EEPP_HDL_MeasuredMotorStroke, NULL);

  // if init was performed, removed it since electric strokes found are no longer available
  EERAM_ConfigModel.Init_MotorSlide = 0u;
  EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);

  return SERVICE_OK;
}

/******************************************************************************/
/*                   Start Position reset routine      (RID = 0xF00A)         */
/******************************************************************************/
static u08 Udsa_RtnStartPositionReset(u08 *Data, u16 Length)
{
  IPOC_Channel_t i;

  /* reset also strokes information */
  //MOTP_ResetAllStrokes();

  for ( i = (IPOC_Channel_t)0u; i < IPOC_HDL_MAX ; i++)
  {
    IPOC_SetPosition(i,0u);
  }

  /* tell to MOTP to save position since they are changed */
  MOTP_SavePosition();

  // if init was performed, removed it since electric strokes found are no longer available
  EERAM_ConfigModel.Init_MotorSlide = 0u;
  EEPP_WriteData(EEPP_HDL_ConfigModel, NULL);

  return SERVICE_OK;
}

/******************************************************************************/
/*                  Stop slide initialization     (RID = 0x0200)              */
/******************************************************************************/
static u08 Udsa_RtnStopSlideInitialization(u08 *Data, u16 Length)
{
  u08 ret_val;

  if ((DISPA_GetInitializationStatus() == MOTA_IN_PROGRESS) &&
      (EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn == ENABLE))
  {
    DISPA_StopInitialization();
    ret_val = SERVICE_OK;
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}

/******************************************************************************/
/*               Request Slide Initialization result    (RID = 0x0200)        */
/******************************************************************************/
static u08 Udsa_RtnResultSlideInitialization(u08 *Data, u16 Length)
{
  u08 ret_val;

  if(EERAM_BproxiConfig[EERAM_BproxiValue].SlideEn == ENABLE)
  {
    if (DISPA_GetInitializationStatus() == MOTA_IN_PROGRESS)
    {
      Diag_Response[4] = 0x01u; // routine ongoing
    }
    else if (DISPA_GetInitializationStatus() == MOTA_INIT)
    {
      Diag_Response[4] = 0x00u; // routine finished ok
    }
    else if (DISPA_GetInitializationStatus() == MOTA_NOT_INIT)
    {
      Diag_Response[4] = 0x02u; // routine not ok
    }
    else
    {
      /* MISRA 14.10 */
    }
    ret_val = SERVICE_OK;
    Diag_Response_Ln  = 5U;
  }
  else
  {
    ret_val = CONDITIONS_NOT_CORRECT;
  }

  return ret_val;
}


#endif /* end __UDSA_IS_PRESENT__ */

/*______ E N D _____ (UDSA_RtnConfig.c) ______________________________________*/
