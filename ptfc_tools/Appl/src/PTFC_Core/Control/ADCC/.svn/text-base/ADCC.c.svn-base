/******************************************************************************/
/** @file       ADCC.c                                                        */
/** @title      Analog Digital Converter Control                              */
/** @brief      Source code of ADC module for control layer. This file is     */
/**             developed for project MQB starting to QB35. It contain the    */
/**             ADC channels management used in this project, its conversion  */
/**             characteristics and its low power behaviour.                  */
/** @date       27/08/2014                                                    */
/** @author     Carmine Celozzi                                               */
/**                                                                           */
/** @see        www.Bitron.net                                                */
/*************************************** (C) Copyright 2014 Bitron S.p.A. *****/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 27/08/2014 0.1  CC      First draft
|-----------------------------------------------------------------------------
| 05/09/2014 1.0  CC      First release
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define ADCC_IF_OWNER

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ADCC.h"
#include "ADCC_config.h"
#include "LPMS_if.h"

/* Module inhibition filter */
#ifdef __ADCC_IS_PRESENT__

/*_____ L O C A L - D E F I N E ______________________________________________*/

/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/** 
  * State variable of current ADC channel used for scan of conversion
  */
static ADCC_InputChn_t Adcc_InputChn;

/** 
  * Index for read data by multiplexer with a period of ADCC_MUX_SIZE
  * conversion
  */
static uint8_t Adcc_MuxIdx;

/** 
  * Variable for conversion status
  */
static CTRL_ResSts_t Adcc_ResStsConv;

/** 
  * Module buffer for all configured channels. In this buffer is stored
  * the avarage value, the current index to write in the buffer and a samples
  * buffer with size ADCC_BUFFER_SAMPLE_NMB
  */
static ADCC_ChnBuffer_t Adcc_ChnBuffer[ADCC_CHN_NMB];

/**
  * Number of shift needed to perform the average division.
  */
static uint8_t Adcc_ShiftIndex;

/**
  * Previous fault status, used to manage the diagnosis threshold hysteresis.
  */
static CTRL_Fault_t Adcc_prevFault[ADCC_CHN_NMB];

/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/

/**
 * @brief Store in the channel buffer the new data passed (ChnData input) and
 *        compute the average value of a specific ADC channel (InputChn).
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [in] ChnData: ADC value converted. This value will be stored in the
 *             buffer and used for compute the new average value.
 * @param [out] None
 *
 * @return CTRL_ResSts_t
 * @retval CTRL_OK The ADC value is stored and its average value is computed
 *         correctly.
 * @retval CTRL_PAR_NOT_OK The ADC channel selected isn't exist
 */
static CTRL_ResSts_t Adcc_PrepareDataBuffer(ADCC_InputChn_t InputChn, 
                                            uint16_t ChnData);
                                            
                                            
static uint8_t Adcc_ComputeShiftIndex(uint8_t Divider);


/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/**
 * @brief Initialization routine for ADC control module. This routine must be
 *        called only during transition POWER_OFF --> RUN.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_Init(void)
{
  ADCD_SelectionMode_t selectMode;
  ADCD_ConversionMode_t convertMode;
  
  /* Load operation mode for run state by configuration look-up table */
  ADCD_TriggerMode_t    TriggerMode = 
    ADCC_PwrmOperationMode[ADCC_PWRM_RUN_STATE].TriggerMode;
  ADCD_SelectionMode_t  SelectionMode = 
    ADCC_PwrmOperationMode[ADCC_PWRM_RUN_STATE].SelectionMode;
  ADCD_ConversionMode_t ConversionMode = 
    ADCC_PwrmOperationMode[ADCC_PWRM_RUN_STATE].ConversionMode;
  
  selectMode = ADCD_GetSelectionMode();
  convertMode = ADCD_GetConversionMode();

  /* Set operation mode for run state only if is 
     different respect to current state */
  if( (ADCD_GetTriggerMode() != TriggerMode)    ||
      (selectMode            != SelectionMode)  ||
      (convertMode           != ConversionMode)  )
  {
    /* Change operation mode for system run state */
    ADCD_SetTriggerOperationConversionMode(TriggerMode, 
                                           SelectionMode,
                                           ConversionMode);
  }

  /* Init for state variables and buffer */
  Adcc_InputChn   = ((ADCC_InputChn_t)(ADCD_CONT_CHN_NMB-1U));
  Adcc_MuxIdx     = 0U;
  Adcc_ResStsConv = CTRL_OK;
  memset(Adcc_prevFault, (int)CTRL_NOT_TESTED, sizeof(CTRL_Fault_t)     * ADCC_CHN_NMB);
  memset(Adcc_ChnBuffer, 0x00,            sizeof(ADCC_ChnBuffer_t) * ADCC_CHN_NMB);
  
  Adcc_ShiftIndex = Adcc_ComputeShiftIndex(ADCC_BUFFER_SAMPLE_NMB);

  /* Call configuration Init */
  ADCC_InitCfg();
}


/**
 * @brief This routine, only for run state of low power management module,
 *        manages the conversion of all ADC channels present on board except
 *        the PIEZO channel. The main activities are: starts che conversion
 *        configured in the ADCC_StartConversionRun, stores and manipulates
 *        the ADC datas by Adcc_PrepareDataBuffer routine and scans the ADC
 *        channels to their conversion.
 *        WARNING: must be called by task only during the run state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCC_RunManager(void)
{
  ADCC_InputChn_t InputChn;

  /* Check the conversion result */
  if( Adcc_ResStsConv == CTRL_OK )
  {
    for(InputChn = (ADCC_InputChn_t)0U; InputChn < ADCC_CHN_NMB; InputChn++)
    {

#if (ADCC_MUX_SIZE > 0U)

      if( (ADCC_ChannelIsMux(InputChn) == (s16)(FALSE)) ||
          ((ADCC_ChannelIsMux(InputChn) == (s16)(TRUE)) && (Adcc_MuxIdx == ADCC_MUX_CHAN_SAMPLE_START)) )
      {
        /* Store the new data converted and compute the new average value */
        (void)Adcc_PrepareDataBuffer(InputChn,
              ADCC_ChnMap[InputChn].GET_CHN_DATA((uint8_t)ADCC_ChnMap[InputChn].ANALOG_IN));
      }
#else
      /* Store the new data converted and compute the new average value */
      (void)Adcc_PrepareDataBuffer(InputChn,
          ADCC_ChnMap[InputChn].GET_CHN_DATA((uint8_t)ADCC_ChnMap[InputChn].ANALOG_IN));

#endif
    }
  }

#if (ADCC_MUX_SIZE > 0U)
  /* Call Multiplexed channels acquisition callback */
  if (Adcc_MuxIdx == ADCC_MUX_CHAN_SAMPLE_START)
  {
    ADCC_MuxChanSampledCbk()
  }
  else
  {
  }

  /* Update Index for sync with mux */
  Adcc_MuxIdx = (Adcc_MuxIdx + 1U) % ADCC_MUX_SIZE;
#endif

  /* Start conversion configured for run state */
  Adcc_ResStsConv = ADCC_StartConversionRun((ADCD_InputChn_t)Adcc_InputChn);
}

/**
 * @brief Return the buffer data values for a specific channel.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [out] None
 *
 * @return ADCC_ChnBuffer_t
 * @retval uint16_t Average: in this field there is the average value of all 
 *         sample datas stored in the SampleBuffer field.
 * @retval uint8_t Index: index to select in the SampleBuffer buffer last 
 *         data stored.
 * @retval uint16_t SampleBuffer[ADCC_BUFFER_SAMPLE_NMB]: sample datas buffer.
 *         The buffer size is ADCC_BUFFER_SAMPLE_NMB and it can be configured.
 */
ADCC_ChnBuffer_t ADCC_GetChnData(ADCC_InputChn_t InputChn)
{
  return (Adcc_ChnBuffer[InputChn]);
}



/**
 * @brief Return the buffer data values for a specific channel.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [out] None
 *
 * @return ADCC_ChnBuffer_t
 * @retval uint16_t Average: in this field there is the average value of all 
 *         sample datas stored in the SampleBuffer field.
 * @retval uint8_t Index: index to select in the SampleBuffer buffer last 
 *         data stored.
 * @retval uint16_t SampleBuffer[ADCC_BUFFER_SAMPLE_NMB]: sample datas buffer.
 *         The buffer size is ADCC_BUFFER_SAMPLE_NMB and it can be configured.
 */
uint16_t ADCC_GetLastChnData(ADCC_InputChn_t InputChn)
{
  return(Adcc_ChnBuffer[InputChn].SampleBuffer[Adcc_ChnBuffer[InputChn].Index]);
}



uint16_t ADCC_GetChnAvrgData(ADCC_InputChn_t InputChn)
{
  uint8_t  DataAvrgIdx = 0U;
  uint32_t DataAverage = 0U;


  /* Compute new data average */
  for(DataAvrgIdx = 0U; DataAvrgIdx < ADCC_BUFFER_SAMPLE_NMB; DataAvrgIdx++)
  {
    /* Accumulate all datas... */
    DataAverage += (uint32_t)(Adcc_ChnBuffer[InputChn].SampleBuffer[DataAvrgIdx]);
  }
  
  /* ...and divide for all samples. */
  DataAverage = (DataAverage >> Adcc_ShiftIndex);

  return((uint16_t)DataAverage);
}


/*_____ L O C A L - F U N C T I O N S ________________________________________*/

/**
 * @brief Store in the channel buffer the new data passed (ChnData input) and
 *        compute the average value of a specific ADC channel (InputChn).
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [in] ChnData: ADC value converted. This value will be stored in the
 *             buffer and used for compute the new average value.
 * @param [out] None
 *
 * @return CTRL_ResSts_t
 * @retval CTRL_OK The ADC value is stored and its average value is computed
 *         correctly.
 * @retval CTRL_PAR_NOT_OK The ADC channel selected isn't exist
 */
static CTRL_ResSts_t Adcc_PrepareDataBuffer(ADCC_InputChn_t InputChn, 
                                            uint16_t ChnData)
{
  CTRL_ResSts_t ResSts = CTRL_OK;

  /* Check the InputChn correctness */
  if( InputChn < ADCC_CHN_NMB )
  {
    /* Increase the data buffer index */
    Adcc_ChnBuffer[InputChn].Index = 
      (Adcc_ChnBuffer[InputChn].Index == (ADCC_BUFFER_SAMPLE_NMB-1U)) ?
      (Adcc_ChnBuffer[InputChn].Index = 0U) : (Adcc_ChnBuffer[InputChn].Index + 1U);
      
    /* Insert data passed by parameter in data buffer */
    Adcc_ChnBuffer[InputChn].SampleBuffer[Adcc_ChnBuffer[InputChn].Index] = ChnData;
  }
  else
  {
    /* Update the result status due to a wrong parameter */
    ResSts = CTRL_PAR_NOT_OK;
  }
  
  return (ResSts);
}



/* Descrivere che è una routine con la restizione che accetta solo divisori */
/* potenze di due */
static uint8_t Adcc_ComputeShiftIndex(uint8_t Divider)
{
  uint8_t ShiftIndex;
  uint8_t Mask = 0x01U;
  
  for(ShiftIndex = 0U; ShiftIndex < 8U; ShiftIndex++)
  {
    if( (Mask & Divider) != 0U )
    {
      break;
    }
    
    Mask = Mask << 1U;
  }
  
  return(ShiftIndex);
}

/**
 * @brief Returns the diagnosis status of a specific ADC channel (InputChn).
 *        The diagnosis is performed on the average value of the input.
 *
 * @param [in] InputChn: reference ADC channel. This input can assume the values
 *             configured in the type ADCC_InputChn_t. In this type are coded
 *             the ADC channels used in the project respect to micro ADC channels.
 * @param [out] None
 *
 * @return CTRL_Fault_t
 * @retval CTRL_OVER_VOLTAGE The ADC value is over the maximum acceptable value.
 * @retval CTRL_UNDER_VOLTAGE The ADC is under the minimum acceptable value.
 */
CTRL_Fault_t ADCC_GetDiag(ADCC_InputChn_t InputChn)
{
  CTRL_Fault_t valueReturn;
  uint16_t     chanAvg;

  chanAvg = ADCC_GetChnAvrgData(InputChn);

  if ((chanAvg > ADCC_ChnMap[InputChn].OVER_V_THRES_H) ||
     ((chanAvg > ADCC_ChnMap[InputChn].OVER_V_THRES_L) && (Adcc_prevFault[InputChn] == CTRL_OVER_VOLTAGE)))
  {
    valueReturn = CTRL_OVER_VOLTAGE;
  }
  else if((chanAvg < ADCC_ChnMap[InputChn].UNDER_V_THRES_L) ||
         ((chanAvg < ADCC_ChnMap[InputChn].UNDER_V_THRES_H) && (Adcc_prevFault[InputChn] == CTRL_UNDER_VOLTAGE)))
  {
    valueReturn = CTRL_UNDER_VOLTAGE;
  }
  else
  {
    valueReturn = CTRL_NO_FAULT;
  }

  Adcc_prevFault[InputChn] = valueReturn;

  return valueReturn;
}


#endif /* end __ADCC_IS_PRESENT__ */

/*_____ E N D _____ (ADCC.c) _________________________________________________*/
