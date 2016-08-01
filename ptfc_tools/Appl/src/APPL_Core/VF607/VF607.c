/******************************************************************************/
/* F_PROJECT:          TTM 520 Fiat                                           */
/* F_NAME:             KEYA.c                                                 */
/* F_PURPOSE:                                                                 */
/* F_CREATED_BY:       C.D'Onofrio                                            */
/* F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                 */
/* F_CREATION_DATE:    28/Ott/2013                                            */
/* F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                   */
/******************************************* (C) Copyright 2012 Bitron S.p.A. */
/*
|------------------------------------------------------------------------------|
|               A U T H O R   I D E N T I T Y                                  |
|----------------------------------------------------------------------------- |
| Initials     Name                      Company                               |
| --------     ---------------------     ------------------------------------- |
| SM           Clementina D'ONOFRIO      Bitron S.p.A.                         |
|                                                                              |
|----------------------------------------------------------------------------- |
|               R E V I S I O N   H I S T O R Y                                |
|----------------------------------------------------------------------------- |
| Date         Ver  Author  Description                                        |
| ---------    ---  ------  -------------------------------------------------- |
| 28/Ott/2013  0.1   CDO    First draft                                        |
| 03/Lug/2015  1.0   FZ     Preso da TTM226, sistemato alcune MISRA            |
|                           inserito funzione di saturazione a 0xFF del        |
|                           VINOdometerCount                                   |
|                                                                              |
 */
#define VF607_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "VF607.h"

#ifdef __VF607_IS_PRESENT__

/*______ L O C A L - D E F I N E S ___________________________________________*/

/*______ L O C A L - T Y P E S _______________________________________________*/


/*______ L O C A L - D A T A _________________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ G L O B A L - F U N C T I O N _______________________________________*/
static u08 VF607_VINvalid(VinData_t VINData);


/*----------------------------------------------------------------------------*/
/*Name : VF607_Init                                                           */
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
void VF607_Init(void)
{
  VF607_VIN_DATA.VIN_HI_ready = FALSE;
  VF607_VIN_DATA.VIN_LO_ready = FALSE;
  VF607_VIN_DATA.VIN_MID_ready = FALSE;
  
  VIN_OdometerInitSts = VIN_ODOMETER_INIT;
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_GetVINLock                                                     */
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
VINLockStatus_t VF607_GetVINLock(void)
{
  VINLockStatus_t ret_val;

  ret_val = EERAM_VINLockState;

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINWorkigCondition                                          */
/*Role : VF607 - 1.10 Working Condition Table                                 */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void VF607_MgmVINWorkigCondition(void)
{
  OperationalModeSts_t HMSM_OperationalModeSts = VF608_GetOperationalModeSts();
  VF608_CmdIgnInfo_t HMSM_CmdIgnSts;
  VF608_GetCmdIgnSts(&HMSM_CmdIgnSts);

  if( (HMSM_OperationalModeSts == CMMD_IGNITION_OFF)       ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_ON)        ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_PRE_START) ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_START)     ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_CRANKING)  ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_ON_ENGON)  ||
      (HMSM_OperationalModeSts == CMMD_IGNITION_PRE_OFF)   ||
     ((HMSM_OperationalModeSts == CMMD_OP_MODE_SNA)        &&
     ((HMSM_CmdIgnSts.CmdIgnSts == CMMD_IGN_LK)            ||
      (HMSM_CmdIgnSts.CmdIgnSts == CMMD_RUN)               ||
      (HMSM_CmdIgnSts.CmdIgnSts == CMMD_START)) ) )
  {
    VF607_MgmVINCurrent();

    if(EERAM_TripABMsg.Status == TRUE)
    {
      VF607_VINOdometer();
    }
    else
    {
    }
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINCurrent                                                  */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  Example:                                                                  */
/*  1) VIN_LO  ->  31 43 33 43 44 46 41 ->  in ascii “1C3CDFA”                */
/*  2) VIN_MID ->  48 37 44 44 31 30 30 ->  in ascii “H7DD100”                */
/*  3) VIN_HI  ->  30 38 38 0 0 0 0 ->  in ascii “088”                        */
/*  VIN is “1C3 CDFAH7 DD100008”                                              */
/*  WMI = 1C3                                                                 */
/*  VDS = CDFAH7                                                              */
/*  VIS = DD100088                                                            */
/*DO                                                                          */
/*  []                                                                        */
/*OD                                                                          */
/*----------------------------------------------------------------------------*/
void VF607_MgmVINCurrent(void)
{
  u08 j, i;
  VinData_t VINData; /* temp VIN current */
  u08 VIN_check = TRUE; /* VIN valid: 0x30 - 0x39; 0x41 - 0x5A without 0x49, 0x4F, 0x51 */

  if( VIN.bit.VIN_MSG < CMMD_VIN_SNA )
  { /* IF VIN.bit.VIN_DATA == 0xFF...FF OR VIN.bit.VIN_MSG == 'SNA' THEN the ECUB shall use its stored VinCurr. */
    if( (VIN.bit.VIN_MSG == CMMD_VIN_LO) && (VF607_VIN_DATA.VIN_LO_ready == FALSE) &&
        (VF607_VIN_DATA.VIN_MID_ready == FALSE) && (VF607_VIN_DATA.VIN_HI_ready == FALSE)) /* R4 */
    {
      for(i=0u; i<VIN_DATA_LEN; i++)
      {
        VF607_VIN_DATA.VIN_LO[i] = VIN.bit.VIN_DATA[i];
      }

      VF607_VIN_DATA.VIN_LO_ready = TRUE;
    }
    else if( (VIN.bit.VIN_MSG == CMMD_VIN_MID) && (VF607_VIN_DATA.VIN_LO_ready == TRUE) &&
             (VF607_VIN_DATA.VIN_MID_ready == FALSE) && (VF607_VIN_DATA.VIN_HI_ready == FALSE))  /* R4 */
    {
      for(i=0u; i<VIN_DATA_LEN; i++)
      {
        VF607_VIN_DATA.VIN_MID[i] = VIN.bit.VIN_DATA[i];
      }

      VF607_VIN_DATA.VIN_MID_ready = TRUE;
    }
    else if( (VIN.bit.VIN_MSG == CMMD_VIN_HI) && (VF607_VIN_DATA.VIN_LO_ready == TRUE) &&
             (VF607_VIN_DATA.VIN_MID_ready == TRUE) && (VF607_VIN_DATA.VIN_HI_ready == FALSE) )  /* R4 */
    {
      for(i=0u; i<VIN_DATA_LEN; i++)
      {
        VF607_VIN_DATA.VIN_HI[i] = VIN.bit.VIN_DATA[i];
      }

      VF607_VIN_DATA.VIN_HI_ready = TRUE;
    }
    else /* R4 */
    {
      VF607_VIN_DATA.VIN_LO_ready  = FALSE;
      VF607_VIN_DATA.VIN_MID_ready = FALSE;
      VF607_VIN_DATA.VIN_HI_ready  = FALSE;
    }

    if( (VF607_VIN_DATA.VIN_LO_ready == TRUE) && (VF607_VIN_DATA.VIN_MID_ready == TRUE) && (VF607_VIN_DATA.VIN_HI_ready == TRUE) )
    {
      for(j=0u; j<VIN_DATA_LEN; j++)
      {
        VINData.VINX[j]              = VF607_VIN_DATA.VIN_LO[j];
        VINData.VINX[VIN_DATA_LEN+j] = VF607_VIN_DATA.VIN_MID[j];

        if(j<3)
        {
          VINData.VINX[14+j] = VF607_VIN_DATA.VIN_HI[j];
        }
        else
        {

        }
      }

      VF607_VIN_DATA.VIN_LO_ready  = FALSE;
      VF607_VIN_DATA.VIN_MID_ready = FALSE;
      VF607_VIN_DATA.VIN_HI_ready  = FALSE;

      VIN_check = VF607_VINvalid(VINData);

      if( (VF607_VINdelivery(VINData)) && VIN_check )
      { /* IF VIN.bit.VIN_DATA == 0xFF...FF OR VIN.bit.VIN_MSG == 'SNA' THEN the ECUB shall use its stored VinCurr. */
        if( (memcmp(&VINData.VINX[0u], &EERAM_VINCurrent.VINX[0u], UDSA_LN_VIN) != 0u) )
        {
          for (i=0U; i < UDSA_LN_VIN ; i++)
          {
            EERAM_VINCurrent.VINX[i] = VINData.VINX[i];
          }

          EEPP_WriteData(EEPP_HDL_VINCurrent, NULL);
        }
        else
        {

        }
      }
      else
      {
      }
    }
    else
    {
    }
  }
  else
  {
    /* ELSE use stored VIN current */
  }

  /* FZ 07.07.2015 - VIN Melfi Bug Fix - Allo sblocco del VIN, se non        *
   * c'è un messaggio VIN con un contenuto valido, ma nel VIN_Current        *
   * il contenuto è valido, non aggiornava il VIN_Original.                  *
   * Spostato dall' if qui sopra la VF607_MgmVINOriginal() che esegue solo   *
   * nel caso in cui il valore contenuto nel VIN_Current sia compatibile     *
   * con quello della specifica                                              */
  if(VF607_VINvalid(EERAM_VINCurrent))
  {
    VF607_MgmVINOriginal();
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_MgmVINOriginal                                                 */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  Example:                                                                  */
/*  1) VIN_LO   ->  31 43 33 43 44 46 41 ->  in ascii “1C3CDFA”               */
/*  2) VIN_MID->  48 37 44 44 31 30 30 ->  in ascii “H7DD100”                 */
/*  3) VIN_HI ->  30 38 38 0 0 0 0 ->  in ascii “088”                         */
/*  VIN is “1C3 CDFAH7 DD100008”                                              */
/*  WMI = 1C3                                                                 */
/*  VDS = CDFAH7                                                              */
/*  VIS = DD100088                                                            */
/*DO                                                                          */
/*  []                                                                        */
/*OD                                                                          */
/*----------------------------------------------------------------------------*/
void VF607_MgmVINOriginal(void)
{
  u08 i;

  if(EERAM_VINLockState == VIN_NOT_LOCKED)
  {
    if( memcmp(&EERAM_VINOriginal.VINX[0u], &EERAM_VINCurrent.VINX[0u], UDSA_LN_VIN) != 0u )
    {
      /* The ECUB, upon set of the VinOrig for the first time, shall set its Mileage Counter = '0',
       * it shall acquire CLUSTER1.TotalOdometer and it shall start the Mileage Counter. */
      if((VF607_VINdelivery(EERAM_VINOriginal)) == FALSE)
      {
        VIN_OdometerInitSts = VIN_ODOMETER_PENDING;
      }
      else
      {

      }

      /* The ECUB, upon set of the VinOrig for the first time, shall set its Mileage Counter = '0',
       * it shall acquire CLUSTER1.TotalOdometer and it shall start the Mileage Counter. */
//      if((VF607_VINdelivery(EERAM_VINOriginal)) == FALSE)
//      {
//        EERAM_VINOdometer.VINOdometerCount = 0u;
//        EERAM_VINOdometer.MilageOffset = FUNP_GetTotalOdometer(); /* acquire odometer */
//        EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);
//
//        EERAM_VINOdoStart = 1u; /* start the Mileage Counter */
//        EEPP_WriteData(EEPP_HDL_VINOdoStart, NULL);
//      }
//      else
//      {
//
//      }

      for (i=0U; i<UDSA_LN_VIN ; i++)
      {
        EERAM_VINOriginal.VINX[i] = EERAM_VINCurrent.VINX[i];
      }

      EEPP_WriteData(EEPP_HDL_VINOriginal, NULL);
    }
    else
    {
    }
  }
  else
  {
     /* don't update VIN original */
  }
}
/*----------------------------------------------------------------------------*/
/*Name : VF607_VINdelivery                                                    */
/*Role : Check if VIN = "0xFF..FF"                                            */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u08 VF607_VINdelivery(VinData_t VINData)
{
  u08 i=0u;
  u08 ret_val = FALSE; /* all "FF" */

  while(i < UDSA_LN_VIN)
  {
    if(VINData.VINX[i] == 0xFFu)
    {
      i++;
    }
    else
    {
      ret_val = TRUE;
      i = UDSA_LN_VIN;
    }
  }

  return(ret_val);
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_VINOdometer                                                    */
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
void VF607_VINOdometer(void)
{
  u32 incr;
  u32 GetOdometer;

  GetOdometer = FUNP_GetTotalOdometer();
  if(GetOdometer == 0xFFFFFFFFUL) /* Mileage not Ready */
  {

  }
  else
  {
    if(VIN_OdometerInitSts == VIN_ODOMETER_PENDING)
    {
      VIN_OdometerInitSts = VIN_ODOMETER_DONE;

      EERAM_VINOdometer.VINOdometerCount = 0u;
      EERAM_VINOdometer.MilageOffset = GetOdometer; /* acquire odometer */
      EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);

      EERAM_VINOdoStart = 1u; /* start the Mileage Counter */
      EEPP_WriteData(EEPP_HDL_VINOdoStart, NULL);
    }

    if(EERAM_VINOdoStart) /* VinOrig has been set for the first time */
    {
      if(GetOdometer >= EERAM_VINOdometer.MilageOffset) /* check for positive value of "incr" */
      {
        incr = GetOdometer - EERAM_VINOdometer.MilageOffset;

        /* FZ 07.07.2015 - VIN Melfi Bug Fix - VF_607 1.11.1.3 ECUB Algorithm*
         * Requirement Example 2 in Mileage Counter management picture       *
         * Non seguiva il Mileage counter come nell'esempio 2, ovvero anche  *
         * se l'odometro viene azzerato e successivamente incrementato,      *
         * il MileageCounter deve continuare ad incrementarsi                */
        if(incr > (u32)0u)
        {
          EERAM_VINOdometer.MilageOffset = GetOdometer;

          if(incr >= (u32)VF607_MILEAGE_SATURATION)
          {
            EERAM_VINOdometer.VINOdometerCount = (u32)VF607_MILEAGE_SATURATION;
          }
          else if((incr + EERAM_VINOdometer.VINOdometerCount) >= (u32)VF607_MILEAGE_SATURATION)
          {
            EERAM_VINOdometer.VINOdometerCount = (u32)VF607_MILEAGE_SATURATION;
          }
          else
          {
            EERAM_VINOdometer.VINOdometerCount = incr + EERAM_VINOdometer.VINOdometerCount;
          }
          EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);

          if(EERAM_VINOdometer.VINOdometerCount >= VF607_MILEAGE_LOCK)
          {
            EERAM_VINOdoStart = 0u; /* stop incrementing Mileage counter */
            EEPP_WriteData(EEPP_HDL_VINOdoStart, NULL);

            EERAM_VINOdometer.VINOdometerLockStatus = VIN_ODO_LOCKED;
            EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);

            EERAM_VINLockState = VIN_LOCKED_BY_ODOMETER;
            EEPP_WriteData(EEPP_HDL_VINLockState, NULL);
          }
          else
          {
          }
        }
        else
        {
        }
      }
      else
      {
        /* FZ 07.07.2015 - VIN Melfi Bug Fix - VF_607 1.11.1.3 ECUB Algorithm*
         * Requirement Example 2 in Mileage Counter management picture       *
         * Non seguiva il Mileage counter come nell'esempio 2, ovvero anche  *
         * se l'odometro viene azzerato e successivamente incrementato,      *
         * il MileageCounter deve continuare ad incrementarsi                */
        EERAM_VINOdometer.MilageOffset = GetOdometer; /*1.11.1.3 ECUB Algorithm Requirement Example 2 in Mileage Counter management picture */
        EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);
      }
    }
    else
    {
      if((EERAM_VINOdometer.VINOdometerCount < VF607_MILEAGE_SATURATION) && (EERAM_VINOdometer.VINOdometerLockStatus == VIN_ODO_LOCKED))
      {
        incr = GetOdometer - EERAM_VINOdometer.MilageOffset;

        if(incr > (u32)0u)
        {
          EERAM_VINOdometer.MilageOffset = GetOdometer;

          if(incr >= (u32)VF607_MILEAGE_SATURATION)
          {
            EERAM_VINOdometer.VINOdometerCount = (u32)VF607_MILEAGE_SATURATION;
          }
          else if((incr + EERAM_VINOdometer.VINOdometerCount) >= (u32)VF607_MILEAGE_SATURATION)
          {
            EERAM_VINOdometer.VINOdometerCount = (u32)VF607_MILEAGE_SATURATION;
          }
          else
          {
            EERAM_VINOdometer.VINOdometerCount = incr + EERAM_VINOdometer.VINOdometerCount;
          }
          EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);
        }
        else
        {
        }
      }
      else
      {

      }
    }
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_TRIP_AB_flag                                                   */
/*Role : RESET flag when message present for VIN odometer                     */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void VF607_TRIP_AB_flagReset(void)
{
  if(EERAM_TripABMsg.Status != FALSE)
  {
    EERAM_TripABMsg.Status = FALSE; /* msg absent */
    EERAM_TripABMsg.KeyOnCounter = EERAM_EcuStatusInfo.KeyOnCnt;
    EEPP_WriteData(EEPP_HDL_TripABMsg, NULL);
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_TRIP_AB_flagReset                                              */
/*Role : SET flag when message absent for VIN odometer                        */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void VF607_TRIP_AB_flagSet(void)
{
  if(EERAM_TripABMsg.Status != TRUE)
  {
    EERAM_TripABMsg.Status = TRUE; /* msg present */
    EERAM_TripABMsg.KeyOnCounter = EERAM_EcuStatusInfo.KeyOnCnt;
    EEPP_WriteData(EEPP_HDL_TripABMsg, NULL);
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_TripABRecoveryOdo                                              */
/*Role : Lock VIN Odometer when TRIP_AB msg missing                           */
/*Interface : Applicative                                                     */
/*  - IN  : input parameter                                                   */
/*  - OUT : output (return) parameter                                         */
/*Pre-condition : assumed operation                                           */
/*Constraints   : Callback for TRIP_AB Recovery                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [operation to carry out]                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void VF607_TripABRecoveryOdo(void)
{
  VF607_TRIP_AB_flagReset();

  if( ((EERAM_EcuStatusInfo.KeyOnCnt - EERAM_TripABMsg.KeyOnCounter) > VF607_Num_Key_Cycle) )
    // Daniele: Second condition of if sentence moved below for MISRA 12.4
  {
    if((VF607_VINdelivery(EERAM_VINOriginal)) && (EERAM_VINOdometer.VINOdometerLockStatus != VIN_ODO_LOCKED))
    {
      /* FZ 08.07.2015 - VIN Melfi Bug Fix - VF_607 Lock management          *
       * aggiunto EERAM_VINOdoStart management                               */
      EERAM_VINOdoStart = 0u; /* stop incrementing Mileage counter */
      EEPP_WriteData(EEPP_HDL_VINOdoStart, NULL);

      EERAM_VINOdometer.VINOdometerLockStatus = VIN_ODO_LOCKED;
      EEPP_WriteData(EEPP_HDL_VINOdometer, NULL);

      EERAM_VINLockState = VIN_LOCKED_BY_ODOMETER;
      EEPP_WriteData(EEPP_HDL_VINLockState, NULL);
    }
    else
    {

    }
  }
  else
  {
  }
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_VINvalid                                                       */
/*Role : Check if VIN has valid format according to 09009/02                  */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
static u08 VF607_VINvalid(VinData_t VINData)
{
  u08 checkVIN = TRUE; /* VIN valid */
  u08 i;

  for(i=0u; i<UDSA_LN_VIN; i++)
  {
    if( (((VINData.VINX[i] <= 0x39u) && (VINData.VINX[i] >= 0x30u)) ||
        ((VINData.VINX[i] <= 0x5Au) && (VINData.VINX[i] >= 0x41u) &&
         (VINData.VINX[i] != 0x49u) && (VINData.VINX[i] != 0x4Fu) &&
         (VINData.VINX[i] != 0x51u)) ) == FALSE )
    {
      checkVIN = FALSE;
      i = UDSA_LN_VIN;
    }
    else
    {
    }
  }

  return checkVIN;
}

/*----------------------------------------------------------------------------*/
/*Name : VF607_Seed2Key                                                       */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
// #pragma optimize=none
u32 VF607_Seed2Key(u32 seed)
{
  u32 key[4] = { 0x9b127d51u, 0x5ba41903u, 0x4fe87269u, 0x6bc361d8u }; //128 bits
  u32 y = ((seed<<24u)&0xff000000u) + ((seed<<8u)&0x00ff0000u) + ((seed>>8u)&0x0000ff00u) + ((seed>>24u)&0x000000ffu); //swap byte order
  u32 z = 0ul, sum = 0ul; //y = LOW_PART, z = HIGH_PART
  u08 n = 64u; //number of iterations

  while (n > 0u)
  { //encrypt
    y += (((z << 4u) ^ (z >> 5u)) + z) ^ (sum + key[(u08)(sum & 0x00000003u)]);
    sum += 0x8f750a1du;
    z += (((y << 4u) ^ (y >> 5u)) + y) ^ (sum + key[(u08)((sum >> 11u) & 0x00000003u)]);
    n--;
  }

  return ((z<<24u)&0xff000000u) + ((z<<8u)&0x00ff0000u) + ((z>>8u)&0x0000ff00u) + ((z>>24u)&0x000000ffu); //swap byte order
}


#endif /* end __VF607_IS_PRESENT__ */
