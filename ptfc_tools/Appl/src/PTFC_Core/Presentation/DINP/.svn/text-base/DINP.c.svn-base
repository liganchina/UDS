/**
 * @file DINP.c
 * @brief Debounce INput Presentation: source code of DIN module for 
 * presentation layer. This module apply the debounce filter to any inputs, 
 * both analog and digital inputs.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @date 10 september 2014
 * @note (C) Copyright 2014 Bitron S.p.A.
 * [The link text](http://example.net/)
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo Mastrodonato       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 10/09/2014 1.0  MM      First release
|-----------------------------------------------------------------------------
| 16/10/2014 1.1  CC      Inserted in the routine DINP_Mgm a strategy to apply
|                         the spreading of the channels scan.
|-----------------------------------------------------------------------------
| 17/10/2014 1.2  CC      Move the subchannel computing from DINP_Mgm to
|                         DINP_Init due to a speed performance improvement.
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define DINP_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DINP.h"

/* Module inhibition filter */
#ifdef __DINP_IS_PRESENT__

/*_____ L O C A L - D E F I N E ______________________________________________*/

/* Tick number to scan all channels configured */
#define DINP_SCAN_TICK_NMB      ((uint8_t)(DINP_CHN_SCAN_TIME_US/DINP_TICK_TIME))


/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

static DINP_PrivateData_t Dinp_PrivateData[DINP_HDL_MAX];

/* Current channel buffer */
static DINP_Handle_t Dinp_CurrentChan;

/* Variables for spreading strategy */
static uint8_t Dinp_ScanTickNmb;
static uint8_t Dinp_ChanToScan;
static uint8_t Dinp_SubChanForTick[DINP_SCAN_TICK_NMB];


/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
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
void DINP_Init(void)
{
  uint8_t Idx;
  
  for (Idx = 0U; Idx < DINP_HDL_MAX; Idx++)
  {
    Dinp_PrivateData[Idx].CntTest  = 0U;
    Dinp_PrivateData[Idx].RetState = DINP_CfgTable[Idx].INITIAL_STATE;
  }
  
  /* Set the first channel as current */
  Dinp_CurrentChan = ((DINP_Handle_t)0u);
  
  /* Init of the spreading variables */
  Dinp_ChanToScan = DINP_HDL_MAX;
  Idx = 0U;
  for(Dinp_ScanTickNmb = DINP_SCAN_TICK_NMB; Dinp_ScanTickNmb > 0U; Dinp_ScanTickNmb--)
  {
    Dinp_SubChanForTick[Idx] = GBLS_SUB_CHAN_NMB(Dinp_ChanToScan, Dinp_ScanTickNmb);
    Dinp_ChanToScan -= Dinp_SubChanForTick[Idx];
    Idx++;
  }
  Dinp_ScanTickNmb = 0u;
}

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*       In worst case will dure 22 us                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void DINP_Mgm(void)
{
  u08 SubChan;
  PRES_State_t ActualState;
  uint8_t subChanCheck;
  
  subChanCheck = Dinp_SubChanForTick[Dinp_ScanTickNmb];

  /* Scan a subchannels number by the spreading strategy */
  for (SubChan = 0U; ((SubChan < subChanCheck) && 
                      (Dinp_CurrentChan < DINP_HDL_MAX)); SubChan++)
  {
    if (DINP_CfgTable[Dinp_CurrentChan].ACTIVE_LEVEL == 
        DINP_CfgTable[Dinp_CurrentChan].GET_VALUE_PTR(DINP_CfgTable[Dinp_CurrentChan].INP_CHAN))
    {
      ActualState = S_ON;
    }
    else
    {
      ActualState = S_OFF;
    }

    /* Debouncing */
    if (ActualState != Dinp_PrivateData[Dinp_CurrentChan].RetState)
    {
      Dinp_PrivateData[Dinp_CurrentChan].CntTest++;
      if (Dinp_PrivateData[Dinp_CurrentChan].CntTest >= DINP_CfgTable[Dinp_CurrentChan].N_TEST)
      {
        Dinp_PrivateData[Dinp_CurrentChan].CntTest  = 0U;
        Dinp_PrivateData[Dinp_CurrentChan].RetState = ActualState;

        if (DINP_CfgTable[Dinp_CurrentChan].STATE_CHANGED != NULL)
        {
          DINP_CfgTable[Dinp_CurrentChan].STATE_CHANGED();
        }
        else
        {
        }
      }
      else
      {
        /* NOP */
      }
    }
    else
    {
      Dinp_PrivateData[Dinp_CurrentChan].CntTest = 0U;
    }
  
    /* Update current channel */  
    Dinp_CurrentChan++;
  }

  /* Reinit current channel */
  if( Dinp_CurrentChan >= DINP_HDL_MAX )
  {
    Dinp_CurrentChan = ((DINP_Handle_t)0u);
  }
  
  /* Update spreading variables */
  if (Dinp_ScanTickNmb < (DINP_SCAN_TICK_NMB-1U))
  {
    Dinp_ScanTickNmb++;
  }
  else
  {
    Dinp_ScanTickNmb = 0u;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : DINP_GetState                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
PRES_State_t DINP_GetState(DINP_Handle_t chan)
{
  /* Valore debouce-ato */
  return (Dinp_PrivateData[chan].RetState);
}


/*______ L O C A L - F U N C T I O N S _______________________________________*/


#endif /* end __DINP_IS_PRESENT__ */

/*_____ E N D _____ (DINP.c) _________________________________________________*/

