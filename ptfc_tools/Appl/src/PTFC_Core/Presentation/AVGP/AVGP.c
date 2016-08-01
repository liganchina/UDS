/********************************************************************************/
/* @F_PROJECT:          ALM_Appl                                                */
/* F_NAME:              AVGP                                                    */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     07/giu/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO                   Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 07/giu/2013 0.1  Matteo MASTRODONATO
*/

#define AVGP_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "AVGP.h"

/* Module inhibition filter */
#ifdef __AVGP_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct{
	u08 		 FastAvgStart:1;
	u08 		 SlowAvgStart:1;
	u08 		 FastAvgIndex;
	u16 		 SlowAvgIndex;
	u16 		 FastBuff[AVGP_FAST_BUFF_SIZE];
	u16 		 SlowBuff[AVGP_SLOW_BUFF_SIZE];
	u16 		 FastAvgSum;
	u16 		 SlowAvgSum;
	PRES_Fault_t prevFaultFast;
	PRES_Fault_t prevFaultSlow;
} Avgp_PrivateData_t;

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

Avgp_PrivateData_t Avgp_PrivateData[AVGP_HDL_MAX];

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

void 		 Avgp_MgmSlow(u08 chan);
PRES_Fault_t Avgp_GetDiag(AVGP_Handle_t chan, u16 ChanAvg, PRES_Fault_t prevFault);

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : void AVGP_Init(void)                                            */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Initiates the module's private data                                     */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void AVGP_Init(void)
{
  u08	chan, i;

  /* Inizializzazione dati privati */
  for (chan = 0U; chan < AVGP_HDL_MAX; chan++)
  {
    Avgp_PrivateData[chan].FastAvgStart  = FALSE;
    Avgp_PrivateData[chan].SlowAvgStart  = FALSE;
    Avgp_PrivateData[chan].FastAvgIndex  = 0U;
    Avgp_PrivateData[chan].SlowAvgIndex  = 0U;
    Avgp_PrivateData[chan].FastAvgSum	 = 0U;
    Avgp_PrivateData[chan].SlowAvgSum	 = 0U;
    Avgp_PrivateData[chan].prevFaultFast = PRES_NOT_TESTED;
    Avgp_PrivateData[chan].prevFaultSlow = PRES_NOT_TESTED;

    for (i = 0U; i<AVGP_FAST_BUFF_SIZE; i++)
    {
      Avgp_PrivateData[chan].FastBuff[i] 	= 0U;
    }

    for (i = 0U; i<AVGP_SLOW_BUFF_SIZE; i++)
    {
      Avgp_PrivateData[chan].SlowBuff[i]	= 0U;
    }
  }
}

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void AVGP_Mgm(void)
{
  u08	chan;
  u16 tmpValue;

  for (chan = 0U; chan < AVGP_HDL_MAX; chan++)
  {
    /* Sottraggo dalla somma il valore uscente della media mobile */
    Avgp_PrivateData[chan].FastAvgSum -=
        Avgp_PrivateData[chan].FastBuff[Avgp_PrivateData[chan].FastAvgIndex];

    tmpValue = ADCD_GetValue(AVGP_CfgTable[chan].ADCD_CHAN);

    /* Inserisco il nuovo campione */
    Avgp_PrivateData[chan].FastBuff[Avgp_PrivateData[chan].FastAvgIndex] = tmpValue;

    /* Aggiorno la somma fast */
    Avgp_PrivateData[chan].FastAvgSum += tmpValue;

    if(++Avgp_PrivateData[chan].FastAvgIndex == AVGP_FAST_BUFF_SIZE)
    {
      /* Ho raggiunto il numero di sample, attivo la media mobile fast */
      Avgp_PrivateData[chan].FastAvgStart = TRUE;
      Avgp_PrivateData[chan].FastAvgIndex = 0U;
      /* Scarico il primo risultato della media fast nel buffer della media slow */
      Avgp_MgmSlow(chan);
    }
  }
}

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u16 AVGP_GetFast(AVGP_Handle_t chan)
{
  u16 returnValue;

  if (Avgp_PrivateData[chan].FastAvgStart == TRUE)
  {
    returnValue = Avgp_PrivateData[chan].FastAvgSum >> AVGP_FAST_SAMPLE;
  }
  else
  {
    returnValue = Avgp_PrivateData[chan].FastAvgSum / Avgp_PrivateData[chan].FastAvgIndex;
  }

  returnValue = (u16)(((u32)returnValue * (u32)AVGP_CfgTable[chan].SCALING_GAIN) >> AVGP_GAIN_DIV);

  return (returnValue + AVGP_CfgTable[chan].HW_CAL_OFFSET);
}


/*----------------------------------------------------------------------------*/
/*Name : Xxxx_yyyyzzzz                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/

u16 AVGP_GetSlow(AVGP_Handle_t chan)
{
  u16 returnValue;

  if (Avgp_PrivateData[chan].SlowAvgStart == TRUE)
  {
    returnValue = Avgp_PrivateData[chan].SlowAvgSum >> AVGP_SLOW_SAMPLE;
  }
  else
  {
    returnValue = Avgp_PrivateData[chan].SlowAvgSum / Avgp_PrivateData[chan].SlowAvgIndex;
  }

  returnValue = (u16)(((u32)returnValue * (u32)AVGP_CfgTable[chan].SCALING_GAIN) >> AVGP_GAIN_DIV);

  return (returnValue + AVGP_CfgTable[chan].HW_CAL_OFFSET);
}


/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*Interface : PRES_Fault_t AVGP_GetDiagFast(AVGP_Channel_t chan)              */
/*Pre-condition : AvgFastSize samples has been reached                        */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Returns the diagnosis status of input channel                           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
PRES_Fault_t AVGP_GetDiagFast(AVGP_Handle_t chan)
{
  PRES_Fault_t valueReturn;

  if (Avgp_PrivateData[chan].FastAvgStart == TRUE)
  {
    valueReturn = Avgp_GetDiag(chan, AVGP_GetFast(chan), Avgp_PrivateData[chan].prevFaultFast);
  }
  else
  {
    valueReturn = PRES_NOT_TESTED;
  }
  Avgp_PrivateData[chan].prevFaultFast = valueReturn;

  return valueReturn;
}

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*Interface : PRES_Fault_t AVGP_GetDiagSlow(AVGP_Channel_t chan)              */
/*Pre-condition : AvgSlowSize samples has been reached                        */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Returns the diagnosis status of input channel                           */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/

PRES_Fault_t AVGP_GetDiagSlow(AVGP_Handle_t chan)
{
  PRES_Fault_t valueReturn;

  if (Avgp_PrivateData[chan].FastAvgStart == TRUE)
  {
    valueReturn = Avgp_GetDiag(chan, AVGP_GetSlow(chan), Avgp_PrivateData[chan].prevFaultSlow);
  }
  else
  {
    valueReturn = PRES_NOT_TESTED;
  }
  Avgp_PrivateData[chan].prevFaultSlow = valueReturn;

  return valueReturn;
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

void Avgp_MgmSlow(u08 chan)
{
  u16 tmpAvg;

  /* Calcolo la media Fast */
  tmpAvg = Avgp_PrivateData[chan].FastAvgSum >> AVGP_FAST_SAMPLE;

  /* Sottraggo dalla somma il valore uscente della media mobile */
  Avgp_PrivateData[chan].SlowAvgSum -= Avgp_PrivateData[chan].SlowBuff[Avgp_PrivateData[chan].SlowAvgIndex];

  /* Inserisco nel buffer il nuovo valore */
  Avgp_PrivateData[chan].SlowBuff[Avgp_PrivateData[chan].SlowAvgIndex] = tmpAvg;

  /* Aggiorno la somma della media mobile */
  Avgp_PrivateData[chan].SlowAvgSum += tmpAvg;

  if(++Avgp_PrivateData[chan].SlowAvgIndex == AVGP_SLOW_BUFF_SIZE)
  {
    /* Ho raggiunto il numero di sample, attivo la media mobile slow */
    Avgp_PrivateData[chan].SlowAvgStart = TRUE;
    Avgp_PrivateData[chan].SlowAvgIndex = 0U;
  }
}

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*Interface : PRES_Fault_t Avgp_GetDiag(AVGP_Channel_t chan, u16 chanAvg)     */
/*Pre-condition : Module Avg Enabled                                          */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Returns the diagnosis of channel passed as parameters in accord with    */
/*    the threshold defined in AVGP_CfgTable                                  */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
PRES_Fault_t Avgp_GetDiag(AVGP_Handle_t chan, u16 chanAvg, PRES_Fault_t prevFault)
{
  PRES_Fault_t valueReturn;

  if ((chanAvg > AVGP_CfgTable[chan].OVER_V_THRES_H) ||
     ((chanAvg > AVGP_CfgTable[chan].OVER_V_THRES_L) && (prevFault == PRES_OVER_VOLTAGE)))
  {
    valueReturn = PRES_OVER_VOLTAGE;
  }
  else if((chanAvg < AVGP_CfgTable[chan].UNDER_V_THRES_L) ||
         ((chanAvg < AVGP_CfgTable[chan].UNDER_V_THRES_H) && (prevFault == PRES_UNDER_VOLTAGE)))
  {
    valueReturn = PRES_UNDER_VOLTAGE;
  }
  else
  {
    valueReturn = PRES_NO_FAULT;
  }
  return valueReturn;
}


#endif /* end __AVGP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/
