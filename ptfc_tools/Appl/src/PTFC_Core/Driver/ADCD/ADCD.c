/******************************************************************************/
/** @file       ADCD.c                                                        */
/** @title      Analog Digital Converter Driver                               */
/** @brief      Source code of ADC module for driver layer. This file is      */
/**             developed for Renesas 78K0R family - micro 78f1837.           */
/**             The requirement used for this driver is the chapter 10 of the */
/**             hw datasheet version 6.0 of 78K0R/Fx3 family. For details see */
/**             http://am.renesas.com/products/mpumcu/78k/78k0rfx/78k0rfx3/   */
/**             Documentation.jsp#typeVXNlcidzIE1hbnVhbDogSGFyZHdhcmU=        */
/** @date       10/09/2014                                                    */
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
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 10/09/2014 0.1  CC      First draft. This draft is the release 1.1 of ADCD
|                         module developed for Renesas RL78 family - micro 
|                         R5F10AGFLFB/F13. Will be done the porting to 
|                         78K0R/Fx3 family - micro 78f1837.
|-----------------------------------------------------------------------------
*/

/* !!! NOT MOVE !!! */
#define ADCD_IF_OWNER

/*_____ I N C L U D E - F I L E S ____________________________________________*/

#include "ADCD.h"
#include "ADCD_config.h"

/* Module inhibition filter */
#ifdef __ADCD_IS_PRESENT__

/*_____ L O C A L - D E F I N E ______________________________________________*/

/* TODO SGR_OK */
/* Clock time in ns according to setting ADCD_FCLOCK_MHZ */
#define Adcd_TCLOCK_ns                ((uint16_t)(1000u/ADCD_FCLOCK_MHZ))
/* TODO SGR_OK */
/* Stabilization wait time A */
#define Adcd_VREF_DELAY_A             ((uint8_t)3u) /* us */
/* TODO SGR_OK */
/* Stabilization wait time B - see the flowcharts in the par. 12.7 */
#define Adcd_VREF_DELAY_B             ((uint8_t)1u) /* us */

/* Start address of ADCRn FIFO buffer */
#define Adcd_ADCRn_START_ADDR         ((uint32_t)0xF0280u)


/*_____ L O C A L - T Y P E S ________________________________________________*/

/*_____ L O C A L - D A T A __________________________________________________*/

/* TODO SGR_OK */
/* Full Mask for a specific bit position */
static const uint8_t Adcd_FullMaskReg[8] = {0x01U, 0x03U, 0x07U, 0x0FU, 
                                     0x1FU, 0x3FU, 0x7FU, 0xFFU};



static const uint8_t Adcd_FclockIndexTable[5] = 
{
  ADCD_FCLOCK_2MHZ,
  ADCD_FCLOCK_8MHZ,
  ADCD_FCLOCK_16MHZ,
  ADCD_FCLOCK_20MHZ,
  ADCD_FCLOCK_24MHZ
};



#if 0

#define ADCD_FCLOCK_MAX_2MHZ            (0x00u) /**< Prescaler for fCLK <= 2 MHz */
#define ADCD_FCLOCK_MAX_4MHZ            (0x01u) /**< Prescaler for fCLK <= 4 MHz */
#define ADCD_FCLOCK_MAX_6MHZ            (0x02u) /**< Prescaler for fCLK <= 6 MHz */
#define ADCD_FCLOCK_MAX_8MHZ            (0x03u) /**< Prescaler for fCLK <= 8 MHz */
#define ADCD_FCLOCK_MAX_10MHZ           (0x04u) /**< Prescaler for fCLK <= 10 MHz */
#define ADCD_FCLOCK_MAX_12MHZ           (0x05u) /**< Prescaler for fCLK <= 12 MHz */
#define ADCD_FCLOCK_MAX_14MHZ           (0x06u) /**< Prescaler for fCLK <= 14 MHz */
#define ADCD_FCLOCK_MAX_16MHZ           (0x07u) /**< Prescaler for fCLK <= 16 MHz */
#define ADCD_FCLOCK_MAX_18MHZ           (0x08u) /**< Prescaler for fCLK <= 18 MHz */
#define ADCD_FCLOCK_MAX_20MHZ           (0x09u) /**< Prescaler for fCLK <= 20 MHz */
#define ADCD_FCLOCK_MAX_22MHZ           (0x0Au) /**< Prescaler for fCLK <= 22 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV1      (0x0Bu) /**< Prescaler 1 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV2      (0x0Cu) /**< Prescaler 2 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV3      (0x0Du) /**< Prescaler 3 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV4      (0x0Eu) /**< Prescaler 4 for fCLK <= 24 MHz */
#define ADCD_FCLOCK_MAX_24MHZ_DIV5      (0x0Fu) /**< Prescaler 5 for fCLK <= 24 MHz */

#endif


/* 
   This look-up table, according to:
    - trigger mode with configuration parameter ADCD_TRIG_MODE;
    - hw peripheral clock with configuration parameter ADCD_FCLOCK_MHZ;
    - Conversion time prescaler with configuration parameter ADCD_CONV_TIME;
   filter the possible time setting by values FALSE (not possible) or TRUE
   (possible).
   Its structure refers to Table 12-3 of the reference requirement.
   The subtable 1 and 2 are fused in a single table and they are available
   only with ADCD_TRIG_MODE = ADCD_HW_WAIT_TRIG_MODE.
   The same thing is valid for subtable 3 and 4. They are available
   with ADCD_TRIG_MODE = ADCD_SW_TRIG_MODE or ADCD_HW_NO_WAIT_TRIG_MODE.
                           !!!! WARNING !!!! 
   Some possible time settings aren't available because must cover the
   CPU micro by overload. For this reason MUST NOT CHANGE these settings.
*/


#if (ADCD_CONV_TIME_MODE == ADCD_NORMAL_MODE)
  /* Table 10.8 and 10.9 */
static const bool_t Adcd_ConvTimeFilterTable[16][5] = 
  {
    /* Conversion Fclk / Peripheral hw Fclk:
      2MHz,  8MHz, 16MHz, 20MHz, 24MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 2 MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 4 MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 6 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 8 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 10 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 12 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 14 MHz */
    { TRUE,  TRUE,  TRUE, FALSE, FALSE},   /* Prescaler for fCLK <= 16 MHz */
    {FALSE,  TRUE,  TRUE, FALSE, FALSE},   /* Prescaler for fCLK <= 18 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE, FALSE},   /* Prescaler for fCLK <= 20 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE, FALSE},   /* Prescaler for fCLK <= 22 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 1 for fCLK <= 24 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 2 for fCLK <= 24 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 3 for fCLK <= 24 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 4 for fCLK <= 24 MHz */
    {FALSE,  TRUE,  TRUE,  TRUE,  TRUE}    /* Prescaler 5 for fCLK <= 24 MHz */
  };
#else /* (ADCD_CONV_TIME_MODE = ADCD_HIGH_SPEED_1_MODE) || 
         (ADCD_CONV_TIME_MODE = ADCD_HIGH_SPEED_2_MODE) */
   
  /* Table 10.4, 10.5, 1.6 and 10.7 */
static const bool_t Adcd_ConvTimeFilterTable[16][5] = 
  {
    /* Conversion Fclk / Peripheral hw Fclk:
      2MHz,  8MHz, 16MHz, 20MHz, 24MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 2 MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 4 MHz */
    { TRUE, FALSE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 6 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 8 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 10 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 12 MHz */
    { TRUE,  TRUE, FALSE, FALSE, FALSE},   /* Prescaler for fCLK <= 14 MHz */
    { TRUE,  TRUE,  TRUE, FALSE, FALSE},   /* Prescaler for fCLK <= 16 MHz */
    { TRUE,  TRUE,  TRUE, FALSE, FALSE},   /* Prescaler for fCLK <= 18 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE, FALSE},   /* Prescaler for fCLK <= 20 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE, FALSE},   /* Prescaler for fCLK <= 22 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 1 for fCLK <= 24 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 2 for fCLK <= 24 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 3 for fCLK <= 24 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE,  TRUE},   /* Prescaler 4 for fCLK <= 24 MHz */
    { TRUE,  TRUE,  TRUE,  TRUE,  TRUE}    /* Prescaler 5 for fCLK <= 24 MHz */
  };
#endif

/* TODO SGR_OK */
/* Data buffer of all ADC channels of micro */
static uint16_t Adcd_ChnData[ADCD_IN_CHN_TOT];
/* TODO SGR_OK */
/* Single channel state */
static ADCD_InputChn_t Adcd_CurrentInChn;
/* Buffer index for scan mode */\
static ADCD_InputChn_t Adcd_BufferIdxScan;

#if ((ADCD_SELECT_ONESHOT_BLOCK|ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK) == ADCD_ENABLE)
/* TODO SGR_OK */
/* ISR flag for blocking oneshot management */
static bool_t Adcd_IsrOneshotFlag;
#endif


/*_____ L O C A L - M A C R O S ______________________________________________*/

/*_____ CHANNELS AND INTERRUPT SECTION _______________________________*/

/* TODO SGR_OK */
/**
 * @brief Clear in the reset status the registers ADMx. 
 *        This macro can be used only in a init phase.
 *
 * @param [in] None
 *
 * @return None
 */
#define Adcd_ClearAllReg()\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Switch off the comparator */\
  Adcd_SetComparator(ADCD_DISABLE)\
  /* Clear the ADMx registers */\
  ADM0 = 0x00U;\
  ADM1 = 0x00U;\
}

/* TODO SGR_OK */
/**
 * @brief Switch on/off the peripheral ADC
 *
 * @param [in] PerSts: is the peripheral status to be set
 *             The possible values are:
 *             - ADCD_ENABLE: switch on the ADC peripheric
 *             - ADCD_DISABLE: switch off the ADC peripheric
 *
 * @return None
 */
#define Adcd_SwitchPeripheral(PerSts)\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Switch on/off the peripheral ADC - PER0 register, bit7 */\
  ADCEN = (PerSts);\
}

/* TODO SGR_OK */
/**
 * @brief Enable/disable the ADC comparator. If the comparator is on
 *        the analog input can be read else isn't possible. 
 *        More ADC controller setting can be done only with comparator
 *        in off, then for this reason this macro can be used in a init
 *        phase but in runtime too.
 *
 * @param [in] CompSts: is the comparator status to be set.
 *             The possible values are:
 *             - ADCD_ENABLE: enable the comporator
 *             - ADCD_DISABLE: disable the comparator
 *
 * @return None
 */
#define Adcd_SetComparator(CompSts)\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Enable/disable the ADC comparator - ADM0 register, bit0 */\
  ADCE = (CompSts);\
  /* Delay stabilization after switch on the comparator */\
  ((CompSts) == ADCD_ENABLE) ? Adcd_WaitDelayUs(Adcd_VREF_DELAY_B) :\
    __no_operation();\
}

/* TODO SGR_OK */
/**
 * @brief Disable the ADC interrupt (INTAD_vect) used for
 *        notify the end Conversion.
 *
 * @param [in] None
 *
 * @return None
 */
#define Adcd_DisableInterrupt()\
{\
  /* Disable INTAD interrupt - MK1H register, bit0 */\
  ADMK = 1U;\
  /* Clear INTAD interrupt flag - IF1H register, bit0 */\
  ADIF = 0U;\
}

/* TODO SGR_OK */
/**
 * @brief Enable the ADC interrupt (INTAD_vect) used for
 *        notify the end Conversion.
 *
 * @param [in] None
 *
 * @return None
 */
#define Adcd_EnableInterrupt()\
{\
  /* Clear INTAD interrupt flag - IF1H register, bit0 */\
  ADIF = 0U;\
  /* Enable INTAD interrupt - MK1H register, bit0 */\
  ADMK = 0U;\
}

/* TODO SGR_OK */
/**
 * @brief Only if ADC interrupt is configured as present. This
 *        macro set the priority level passed by input parameter.
 *
 * @param [in] IntPrty: the ADC interrupt priority follow the 
 *             standard setting.
 *             The possible values are:
 *             - ADCD_INTAD_HIGH: is the highest priority
 *             - ADCD_INTAD_LEV1: is a middle priority but greater
 *               than level2
 *             - ADCD_INTAD_LEV2: is a middle priority but smaller
 *               than level1
 *             - ADCD_INTAD_LOW: is the lowest priority
 *
 * @return None
 */
#if (ADCD_INTAD == ADCD_ENABLE)
  #define Adcd_SetInterruptPriority(IntPrty)\
  {\
    /* Write the interrupt priority */\
    /* PR01H register, bit0 */\
    ADPR0 = ((IntPrty)&0x01U);\
    /* PR11H register, bit0 */\
    ADPR1 = (((IntPrty)&0x02U)>>1U);\
  }
#endif

/*_____ CONVERSION OPERATION SECTION __________________________________*/

/* TODO SGR_OK */
/**
 * @brief Set the "trigger mode" used for a start conversion. There are two
 *        trigger groups. The sw one is managed by a sw event, the hw one
 *        can be performed by the timer interrupts INTTM12, INTTM22 and an
 *        external trigger signal by the pin ADTRG.
 * WARNING - for now the setting ADCD_HW_TRIG_MODE is not available because
 * is partially developed.
 *
 * @param [in] TrigMode: The possible values are:
 * @li ADCD_SW_TRIG_MODE: the start conversion is performed by a sw event
 * @li ADCD_HW_TRIG_MODE: the start conversion is performed by some hw events. 
 * These events are: the timer interrupts INTTM12, INTTM22 and an external
 * trigger signal by the pin ADTRG.
 *
 * @return None
 */
#define Adcd_SetTriggerMode(TrigMode)\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Set the trigger mode - ADM1 register, bit7 */\
  GBLS_ClearBitReg(ADM1,7U);\
  ADM1 |= (((TrigMode)&0x01U) << 7U);\
}

/* TODO SGR_OK */
/**
 * @brief Set the trigger source for hw trigger mode setting. The sources can
 *        be internal, by timer interrupts, and external by a dedicated pin.
 * WARNING - for now this setting hasn't effect because the ADCD_HW_TRIG_MODE 
 * is not available because is partially developed.
 *
 * @param [in] Source: The possible values are:
 * @li ADCD_TRIGGER_INTTM12: interrupt event of timer TM12
 * @li ADCD_TRIGGER_INTTM22: interrupt event of timer TM22
 * @li ADCD_TRIGGER_ADTRG: external event associated to a pin signal
 *
 * @return None
 */
#define Adcd_SetHwTriggerSource(Source)\
{\
  /* Stop Conversion */\
  Adcd_StopConv();\
  /* Set the hw trigger source - ADM1 register, bit2-3 */\
  GBLS_ClearBitReg(ADM1,2);\
  GBLS_ClearBitReg(ADM1,3);\
  ADM1 |= (((Source)&0x03) << 2);\
}

/* TODO SGR_OK */
/**
 * @brief Set the input edge of the external hw trigger source ADTRG.
 * This routine and its setting value are available only if the trigger
 * mode setting is ADCD_HW_TRIG_MODE and if the hw trigger source is
 * the external pin ADTRG (ADCD_HW_TRIGGER_SOURCE = ADCD_TRIGGER_ADTRG).
 * WARNING - for now this setting hasn't effect because the ADCD_HW_TRIG_MODE 
 * is not available because is partially developed.
 *
 * @param [in] Edge: The possible values are:
 * @li ADCD_NO_EDGE_ADTRG: none edge setting (trigger is not generated)
 * @li ADCD_FALLING_EDGE_ADTRG: falling edge detection
 * @li ADCD_RISING_EDGE_ADTRG: rising edge detection
 * @li ADCD_BOTH_EDGE_ADTRG: rising and falling edges detection
 *
 * @return None
 */
#define Adcd_SetEdgeExtHwTrigger(Edge)\
{\
  /* Stop Conversion */\
  Adcd_StopConv();\
  /* Set the input edge for hw trigger source ADTRG */\
  /* ADM1 register, bit0-1 */\
  GBLS_ClearBitReg(ADM1,0);\
  GBLS_ClearBitReg(ADM1,1);\
  ADM1 |= ((Edge)&0x03);\
}

/* TODO SGR_OK */
/**
 * @brief Set the "selection mode" used to perform a conversion
 * of a single channel or of all channels configured and selected.
 *
 * @param [in] SelMode: the possible values are:
 * @li ADCD_SELECT_MODE: set the conversion for a single channel
 * @li ADCD_SCAN_MODE_MULTI_INT: set the conversion for all channels
 * selected, generating an interrupt for each channel
 * @li ADCD_SCAN_MODE_SINGLE_INT: set the conversion for all channels
 * selected, generating an interrupt at end of the conversion
 *
 * @return None
 */
#define Adcd_SetSelectionMode(SelMode)\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Set the selection mode - ADM0 register, bit4-5 */\
  GBLS_ClearBitReg(ADM0,4U);\
  GBLS_ClearBitReg(ADM0,5U);\
  ADM0 |= (((SelMode)&0x03U) << 4U);\
}

/* TODO SGR_OK */
/**
 * @brief Set the "Conversion mode" used for the conversion repeatability.
 *        The Conversion can be performed in oneshot and it will be stopped
 *        in automatic way. In opposition can be performed in continous mode
 *        and it must be stopped by a specific sw event.
 *
 * @param [in] ConvMode: the possible values are:
 * @li ADCD_CONTINUOUS_CONV_MODE: continuous conversion. Must be stopped by sw
 * @li ADCD_ONE_SHOT_CONV_MODE: oneshot conversion. It's stopped automatic by 
 * ADC controller
 *
 * @return None
 */
#define Adcd_SetConvMode(ConvMode)\
{\
  /* Stop Conversion */\
  Adcd_StopConv()\
  /* Set the Conversion mode - ADM0 register, bit6 */\
  GBLS_ClearBitReg(ADM0,6U);\
  ADM0 |= (((ConvMode)&0x01U) << 6U);\
}

/* TODO SGR_OK */
/**
 * @brief Return the trigger mode setting. There are two trigger groups.
 *        The sw one is managed by a sw event, the hw one can be 
 *        performed by the timer interrupts INTTM12, INTTM22 and an
 *        external trigger signal by the pin ADTRG.
 *
 * @param [in] None
 *
 * @return volatile uint8_t
 * @retval ADCD_SW_TRIG_MODE: the start conversion is performed by a sw event
 * @retval ADCD_HW_TRIG_MODE: the start conversion is performed by some hw events. 
 * These events are: the timer interrupts INTTM12, INTTM22 and an external
 * trigger signal by the pin ADTRG
 */
#define Adcd_GetTriggerMode()             ((ADM1&0x80U)>>7U)

/* TODO SGR_OK */
/**
 * @brief Return the selection mode setting. It perform a conversion
 * of a single channel or of all channels configured and selected.
 *
 * @param [in] None
 *
 * @return volatile uint8_t
 * @retval ADCD_SELECT_MODE: set the conversion for a single channel
 * @retval ADCD_SCAN_MODE_MULTI_INT: set the conversion for all channels
 * selected, generating an interrupt for each channel
 * @retval ADCD_SCAN_MODE_SINGLE_INT: set the conversion for all channels
 * selected, generating an interrupt at end of the conversion
 */
#define Adcd_GetSelectionMode()           ((ADM0&0x30U)>>4U)

/* TODO SGR_OK */
/**
 * @brief Return the conversion mode setting. It perform the conversion 
 *        repeatability. The Conversion can be performed in oneshot and 
 *        it will be stopped in automatic way. In opposition can be performed
 *        in continous mode and it must be stopped by a specific sw event.
 *
 * @param [in] None
 *
 * @return volatile uint8_t
 * @retval ADCD_CONTINUOUS_CONV_MODE: continuous conversion. Must be stopped by sw
 * @retval ADCD_ONE_SHOT_CONV_MODE: oneshot conversion. It's stopped automatic by 
 * ADC controller
 */
#define Adcd_GetConversionMode()          ((ADM0&0x40U)>>6U)

/*_____ CONVERSION TIME SECTION ______________________________________________*/

/* TODO SGR_OK */
/**
 * @brief Enable/disable the discharge function. This setting is used 
 *        for improve the conversion speed performance. With equal 
 *        parameters setting the speed performance improve with discharge
 *        function disabled.
 *
 * @param [in] Enable - The possible values are:
 * @li ADCD_DISABLE: function disabled improve the conversion speed
 * @li ADCD_ENABLE: function enabled worsen the conversion speed
 *
 * @return None
 */
#define Adcd_SetDischargeFnc(Enable)\
{\
  /* Stop conversion */\
  Adcd_StopConv()\
  /* Set the conversion time mode - ADM0 register, bit3 */\
  GBLS_ClearBitReg(ADM0,3U);\
  ADM0 |= (((Enable)&0x01U) << 3U);\
}

/* TODO SGR_OK */
/**
 * @brief Set the conversion time mode. This setting is used for improve
 *        the conversion speed performance. With equal parameters
 *        setting the speed performance improve from ADCD_NORMAL_MODE 
 *        (lowest speed) to ADCD_HIGH_SPEED_1_MODE (highest speed).
 *
 * @param [in] ConvTimeMode - The possible values are:
 * @li ADCD_HIGH_SPEED_1_MODE: high conversion speed (highest improvment)
 * @li ADCD_HIGH_SPEED_2_MODE: midle conversion speed
 * @li ADCD_NORMAL_MODE: low conversion speed (lowest improvment)
 *
 * @return None
 */
#define Adcd_SetConvTimeMode(ConvTimeMode)\
{\
  /* Stop conversion */\
  Adcd_StopConv()\
  /* Set the conversion time mode - ADM0 register, bit1-2 */\
  GBLS_ClearBitReg(ADM0,1U);\
  GBLS_ClearBitReg(ADM0,2U);\
  ADM0 |= (uint8_t)(((ConvTimeMode)&0x03U) << 1U);\
}

/*_____ FUNCTIONAL MODALITY SECTION __________________________________*/

/* TODO SGR_OK */
/**
 * @brief Set the variables and the register necessary for to start the
 * ADC conversion. This macro depend by the Interrupt presence configuration.
 * According to it the ADC interrupt registers are used or unused.
 *
 * @param [in] None
 *
 * @return None
 */
#if (ADCD_INTAD == ADCD_ENABLE)
#define Adcd_StartConv()\
{\
  /* Enable interrupt INTAD */\
  Adcd_EnableInterrupt()\
  /* Enable AD Conversion */\
  ADCS = 1U;\
}
#else
#define Adcd_StartConv()\
{\
  /* Enable AD Conversion */\
  ADCS = 1U;\
}
#endif

/* TODO SGR_OK */
/**
 * @brief Set the variables and the register necessary for to stop the
 * ADC conversion. This macro depend by the Interrupt presence configuration.
 * According to it the ADC interrupt registers are used or unused.
 *
 * @param [in] None
 *
 * @return None
 */
#if (ADCD_INTAD == ADCD_ENABLE)
#define Adcd_StopConv()\
{\
  /* Disable AD Conversion */\
  ADCS = 0U;\
  /* Disable interrupt INTAD */\
  Adcd_DisableInterrupt()\
}
#else
#define Adcd_StopConv()\
{\
  /* Disable AD Conversion */\
  ADCS = 0U;\
}
#endif

/* TODO SGR_OK */
/**
 * @brief Set the applicative variables for manage the single channel 
 * setting used in "select mode"
 *
 * @param [in] None
 *
 * @return None
 */
#define Adcd_SetSingleChannel(Chn)\
{\
  /* Set the current single channel */\
  Adcd_CurrentInChn = (Chn);\
  /* Init the index for scan mode */\
  Adcd_BufferIdxScan = ADCD_IN_CHN_0;\
}


/*_____ L O C A L - F U N C T I O N S - P R O T O T Y P E S __________________*/

/* TODO SGR_OK */
#if (ADCD_INTAD == ADCD_ENABLE)
  static uint16_t Adcd_ISR_Cbk(void);
#endif
/* TODO SGR_OK */
static void Adcd_ConfigureAnalogIn(uint8_t ChnNmb);
/* TODO SGR_OK */
static DRVD_ResSts_t Adcd_SetAdcChn(ADCD_InputChn_t AdcChn);
/* TODO SGR_OK */
static void Adcd_SetConversionTime(uint8_t PrescIdx);
/* TODO SGR_OK */
static void Adcd_WaitDelayUs(uint8_t DelayUs);


/*_____ G L O B A L - F U N C T I O N S ______________________________________*/

/* TODO SGR_OK */
/**
 * @brief Initialization routine for ADC driver module. The commands
 * sequence follow the figure 10.15 of the reference requirement.
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCD_Init(void)
{
  /* Switch on/off the ADC peripheral */
  Adcd_SwitchPeripheral(ADCD_ENABLE)
  
  /* Clear all registers ADMx */
  Adcd_ClearAllReg()
  
  /* Interrupt section */
  Adcd_DisableInterrupt()
#if (ADCD_INTAD == ADCD_ENABLE)
  Adcd_SetInterruptPriority(ADCD_INTAD_PRTY)
#endif

  /* Port configuration */
  Adcd_ConfigureAnalogIn(ADCD_CONT_CHN_NMB);

  /* ADM0 register - set the conversion time mode and discharge function */
  Adcd_SetConvTimeMode(ADCD_CONV_TIME_MODE)
  Adcd_SetDischargeFnc(ADCD_DISCHARGE_FNC)
  
  /* Switch on comparator */
  Adcd_SetComparator(ADCD_ENABLE)
  /* Delay stabilization after switch on the comparator */
  Adcd_WaitDelayUs(Adcd_VREF_DELAY_A);
  
  /* ADM1 register - set the trigger mode */
  Adcd_SetTriggerMode(ADCD_TRIG_MODE)
#if (ADCD_TRIG_MODE == ADCD_HW_TRIG_MODE)
  Adcd_SetHwTriggerSource(ADCD_HW_TRIGGER_SOURCE);
  #if (ADCD_HW_TRIGGER_SOURCE == ADCD_TRIGGER_ADTRG)
    Adcd_SetEdgeExtHwTrigger(ADCD_EDGE_ADTRG_SOURCE);
  #endif
#endif

  /* Set physical channels */
  (void)Adcd_SetAdcChn(ADCD_IN_CHN_0);
  
  /* ADMPS register - set the conversion timing */
  Adcd_SetConversionTime(ADCD_CONV_TIME);

  /* ADM0 register - set selection and conversion mode */
  Adcd_SetSelectionMode(ADCD_SELECTION_MODE)
  Adcd_SetConvMode(ADCD_CONVERSION_MODE)

#if (ADCD_INTAD == ADCD_ENABLE)
  /* Set the callback for interrupt vector INTAD */
  (void)ISRD_SetEvtCbk(ISRD_VECTOR_INTAD, (ISRD_EvtCbk_t)Adcd_ISR_Cbk);
  
  #if (ADCD_ENABLE_SW_BREAK == ADCD_ENABLE)
  
  #endif
#endif

  /* Init for data management */
  memset(Adcd_ChnData, 0x00, ADCD_IN_CHN_TOT);
#if ((ADCD_SELECT_ONESHOT_BLOCK|ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK) == ADCD_ENABLE)
  Adcd_IsrOneshotFlag = FALSE;
#endif
}

/* TODO SGR_OK */
/**
 * @brief Power-off routine for ADC driver module used for transition
 *        RUN state --> POWER_OFF state
 *
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
void ADCD_PowerOff(void)
{
}


/* TODO SGR_OK */
/**
 * @brief This routine return the last ADC value read for a specific channel
 *
 * @param [in] Chn: ADC channel you want read its value. The possible
 * values are given by the type ADCD_InputChn_t
 * @param [out] None
 *
 * @return uint16_t
 * @retval The selected ADC channel data is in the range [0-1023] if the 
 * ADCD_CONV_RESOLUTION setting is to 10 bit else the range is [0-127]
 */
uint16_t ADCD_GetChannelData(ADCD_InputChn_t Chn)
{
  return (Adcd_ChnData[Chn]);
}



/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.2 of the relative hw datasheet version 2.0. The sw trigger is given
 * every time that the routine is called and the ADC conversion start. The end 
 * conversion is automatically done by ADC controller (one-shot behaviour).
 * If the parameter ADCD_SELECT_ONESHOT_BLOCK is configured to ADCD_ENABLE, 
 * at the end of the routine execution the new data is ready to be read.
 * For internal channel of temperature sensor (ADCD_IN_CHN_TEMP_SENS) the manage
 * is always blocker a cause of a S/H limit.
 * The conversion is done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_ONE_SHOT_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return DRVD_ResSts_t
 * @retval DRVD_OK The ADC channel selected is correct
 * @retval DRVD_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval DRVD_NOT_OK The ADC channel selected cannot used with current configuration
 */
DRVD_ResSts_t ADCD_SwTriggerOneShotManager(ADCD_InputChn_t AdcChn)
{
  /* Set the single channel selected... */
  DRVD_ResSts_t SetChnRes = Adcd_SetAdcChn(AdcChn);

  /* ... and start the conversion only in 
         case of channel right setting */
  if( SetChnRes == DRVD_OK )
  {
    /* Call start conversiont routine */
    Adcd_StartConv()
  }
  
  /* In case of blocking functionality enabled must wait
     the end conversion ISR */
#if (ADCD_SELECT_ONESHOT_BLOCK == ADCD_ENABLE)
  if( Adcd_GetSelectionMode() == ADCD_SELECT_MODE )
  {
    while( Adcd_IsrOneshotFlag != TRUE )
    {
      __no_operation();
    }
  }
#endif

  /* In case of blocking functionality enabled must wait
     the end conversion ISR */
#if (ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK == ADCD_ENABLE)
  if( Adcd_GetSelectionMode() == ADCD_SCAN_MODE_SINGLE_INT )
  {
    while( Adcd_IsrOneshotFlag != TRUE )
    {
      __no_operation();
    }
  }
#endif

#if ((ADCD_SELECT_ONESHOT_BLOCK|ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK) == ADCD_ENABLE)
  /* Clear notify flag for end conversion */
  Adcd_IsrOneshotFlag = FALSE;
#endif
  
  return (SetChnRes);
}





/**
 * @brief This routine manage the operation mode described in the par.
 * 12.6.1 of the relative hw datasheet version 2.0. The sw trigger is given
 * when the routine is called with the parameter Enable to TRUE and the ADC
 * conversion start. It is stopped only when the routine is called with the
 * parameter Enable to FALSE (sequenzial mode behaviour). The conversion is
 * done only for the single channel selected.
 * WARNING: this routine must be used only with the following settings:
 * - ADCD_TRIG_MODE       = ADCD_SW_TRIG_MODE
 * - ADCD_SELECTION_MODE  = ADCD_SELECT_MODE
 * - ADCD_CONVERSION_MODE = ADCD_SEQUENTIAL_CONV_MODE
 * If it's called with settings different, the value returned may be wrong.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] Enable: flag for start/stop conversion. With TRUE start the
 * sequenzial conversion and with FALSE the conversion is stopped
 * @param [in] AdcChn: ADC channel you want start the conversion. The possible
 * values are given by the type ADCD_InputChn_t. The internal ADC channels
 * (ADCD_IN_CHN_TEMP_SENS, ADCD_IN_CHN_INT_VREF) can not be used if the 
 * configuration parameter ADCD_VREF_POS = ADCD_VREF_POS_INT.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 * @param [out] None
 *
 * @return DRVD_ResSts_t
 * @retval DRVD_OK The ADC channel selected is correct
 * @retval DRVD_PAR_NOT_OK The ADC channel selected isn't exist
 * @retval DRVD_NOT_OK The ADC channel selected cannot used with current configuration
 */
DRVD_ResSts_t ADCD_SwTriggerContinuousManager(bool_t Enable, 
                                              ADCD_InputChn_t AdcChn)
{
  DRVD_ResSts_t SetChnRes = DRVD_OK;
 
  /* Start conversion procedure */
  if( Enable == TRUE )
  {
    /* Set the single channel selected... */
    SetChnRes = Adcd_SetAdcChn(AdcChn);
    
    /* ... and start the conversion only in 
       case of channel right setting */
    if( SetChnRes == DRVD_OK )
    {
      /* Call start conversiont routine */
      Adcd_StartConv()
    }
  }
  /* Stop conversion procedure */
  else
  {
    /* Call stop conversiont routine */
    Adcd_StopConv()
  }
  
  return (SetChnRes);
}





/* TODO SGR_OK */
/**
 * @brief This routine set the main submodes for the operation mode. The possible
 * settings are: the trigger mode (for now is available only the sw trigger), the
 * selection mode and conversion mode. Before of this setting mustn't block the
 * conversion because this operation is done yet by routine.
 * It's reccomended to use the relative Get routine for know the current state.
 *
 * @param [in] TriggerMode: parameter to set the trigger mode. For now is 
 * possible use only the value ADC_SW_TRIG_MODE
 * @param [in] SelectionMode: parameter to set the selection mode. The possible 
 * values are given by the type ADCD_SelectionMode_t
 * @param [in] ConversionMode: parameter to set the conversion mode. The possible
 * values are given by the type ADCD_ConversionMode_t
 * @param [out] None
 *
 * @return None
 */
void ADCD_SetTriggerOperationConversionMode(ADCD_TriggerMode_t    TriggerMode,
                                            ADCD_SelectionMode_t  SelectionMode,
                                            ADCD_ConversionMode_t ConversionMode)
{
  /* Stop the scan */
  Adcd_StopConv()
  /* Switch off comparator */
  Adcd_SetComparator(ADCD_DISABLE)

  /* Set new trigger mode */
  Adcd_SetTriggerMode(TriggerMode)
  /* Set new operation mode */
  Adcd_SetSelectionMode(SelectionMode)
  /* Set new Conversion mode */
  Adcd_SetConvMode(ConversionMode)
  /* Delay stabilization after register setting with comparator in off */
  Adcd_WaitDelayUs(Adcd_VREF_DELAY_A);
  
  /* Switch on comparator */
  Adcd_SetComparator(ADCD_ENABLE)
}

/**
 * @brief This routine return the current value of the trigger mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_TriggerMode_t
 * @retval ADC_SW_TRIG_MODE Value for sw trigger mode setting
 * @retval ADC_HW_NO_WAIT_TRIG_MODE Value for hw trigger no-wait mode 
 * setting (for now it isn't available)
 * @retval ADC_HW_WAIT_TRIG_MODE Value for hw trigger wait mode 
 * setting (for now it isn't available)
 */
ADCD_TriggerMode_t ADCD_GetTriggerMode(void)
{
  /* Get trigger mode by local macro */
  return( (ADCD_TriggerMode_t)Adcd_GetTriggerMode() );
}

/**
 * @brief This routine return the current value of the selection mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_SelectionMode_t
 * @retval ADC_SELECT_MODE Value for select mode setting (single channel mode)
 * @retval ADC_SCAN_MODE Value for scan mode setting (channels group mode)
 */
ADCD_SelectionMode_t ADCD_GetSelectionMode(void)
{
  /* Get selection mode by local macro */
  return( (ADCD_SelectionMode_t)Adcd_GetSelectionMode() );
}

/**
 * @brief This routine return the current value of the conversion mode setting
 *
 * @param [in] None
 * @param [out] None
 *
 * @return ADCD_ConversionMode_t
 * @retval ADC_CONTINUOUS_CONV_MODE Value for continuous conversion mode setting
 * @retval ADC_ONE_SHOT_CONV_MODE Value for one-shot conversion mode setting
 */
ADCD_ConversionMode_t ADCD_GetConversionMode(void)
{
  /* Get conversion mode by local macro */
  return( (ADCD_ConversionMode_t)Adcd_GetConversionMode() );
}


/*_____ L O C A L - F U N C T I O N S ________________________________________*/

#if (ADCD_INTAD == ADCD_ENABLE)
/**
 * @brief ISR callback for ADC interrupt. This routine is present only if
 * the configuration parameter ADCD_INTAD is enabled. In this routine,
 * according to selection mode (dynamic configuration) and conversion
 * resolution (static configuration), is stored in the Adcd_ChnData buffer 
 * the ADC data value wrote in the ADCR register by ADC controller. The right
 * agreement beetwen ADC data and channel is managed by variables 
 * Adcd_CurrentInChn and Adcd_ScanChnGroup (only for scan mode).
 *
 * @param [in] None
 *
 * @return uint16_t
 * @retval ISR callback check value computed by ISRD_ComputeCbkCheck with by
 * parameter ISRD_VECTOR_INTAD
 */
static uint16_t Adcd_ISR_Cbk(void)
{
  /* Pointer to register ADCRn initialized to ADCR0 */
  volatile uint16_t *ADCRnPtr = ((volatile uint16_t*)Adcd_ADCRn_START_ADDR);

#if ((ADCD_SELECT_ONESHOT_BLOCK|ADCD_SCAN_SINGLE_INT_ONESHOT_BLOCK) == ADCD_ENABLE)
  /* ISR flag for blocking oneshot setting */
  Adcd_IsrOneshotFlag = TRUE;
#endif

  /* Check the current selection mode */
  if( Adcd_GetSelectionMode() == ADCD_SCAN_MODE_SINGLE_INT )
  {
    for( Adcd_BufferIdxScan = ADCD_IN_CHN_0;
         Adcd_BufferIdxScan <= Adcd_CurrentInChn;
         Adcd_BufferIdxScan++ )
    {
      Adcd_ChnData[Adcd_BufferIdxScan] = ((uint16_t)((*ADCRnPtr) >> 6u));
      ADCRnPtr++;
    }
  }
  else if( Adcd_GetSelectionMode() == ADCD_SCAN_MODE_MULTI_INT )
  {
    Adcd_ChnData[Adcd_BufferIdxScan] = ((uint16_t)(ADCR >> 6u));
    Adcd_BufferIdxScan = (Adcd_BufferIdxScan <= Adcd_CurrentInChn) ? 
      (ADCD_InputChn_t)(Adcd_BufferIdxScan+1U) : ADCD_IN_CHN_0;
  }
  else /* (ADCD_SELECTION_MODE = ADCD_SELECT_MODE) */
  {
    Adcd_ChnData[Adcd_CurrentInChn] = ((uint16_t)(ADCR >> 6u));
  }
  
#if (ADCD_ENABLE_SW_BREAK == ADCD_ENABLE)
  /* Call the software break interrupt for MUXC syncronization */
  __break();
#endif
  
  return (ISRD_ComputeCbkCheck(ISRD_VECTOR_INTAD));
}
#endif /* end (ADCD_INTAD == ADCD_ENABLE) */

/* TODO SGR_OK */
/**
 * @brief This routine configure the ANI00/P80 to ANI15/P97 pins to analog 
 * input of A/D converter according to requirement described in the par.
 * 10.3 of the reference hw datasheet. The section 8 describe the ADPC
 * setting and the section 11 describe the port mode (PM8 and PM9) setting.
 * This pins are configurable as continuous number.
 *
 * @param [in] ChnNmb: continuous ADC channels number. The range values is
 * [0-15]. It the ChnNmb is greater the maximum number, ADCD_IN_CHN_TOT,
 * automatically will be configure all possible ADC channels.
 * For example: if ChnNmb = 5 will be configurate as ADC inputs the
 * channels ANI0, ANI1, ANI2, ANI3, ANI4
 *
 * @return None
 */
static void Adcd_ConfigureAnalogIn(uint8_t ChnNmb)
{
  /* Stop the scan */
  Adcd_StopConv()
  /* Switch off the comparator */
  Adcd_SetComparator(ADCD_DISABLE)

  if( ChnNmb <= ADCD_IN_CHN_TOT )
  {
#if ( (DRVD_UC_PACKAGE == DRVD_64_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_100_PIN) )
    /* Set port mode 8 as inputs */
    if( (ChnNmb > 0U) && (ChnNmb <= 8U) )
    {
      PM8 |= Adcd_FullMaskReg[(ChnNmb-1U)];
    }
    /* Set all port mode 8 and port mode 9 as inputs */
    else if( (ChnNmb > 8U) && (ChnNmb <= 16U) )
    {
      PM8 = 0xFFU;
      PM9 |= Adcd_FullMaskReg[(ChnNmb-9U)];
    }
#endif
#if ( DRVD_UC_PACKAGE == DRVD_100_PIN )
    /* Set all port mode 8, port mode 9 and port 10 as inputs */
    else if( (ChnNmb > 16) && (ChnNmb <= 24) )
    {
      PM8   = 0xFF;
      PM9   = 0xFF;
      PM10 |= Adcd_FullMaskReg[(ChnNmb-17)];
    }
#endif
    else
    {
      /* Setting not possible */
    }
    
    /* Set the inputs as ADC channels */
    ADPC = ChnNmb;
  }
  /* Configure all ADC channels */
  else
  {
    /* Set the port mode as inputs */
#if ( (DRVD_UC_PACKAGE == DRVD_64_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_80_PIN) || \
      (DRVD_UC_PACKAGE == DRVD_100_PIN) )
    PM8 = 0xFFU;
    PM9 = 0xFFU;
#endif
#if ( DRVD_UC_PACKAGE == DRVD_100_PIN )
    PM10 = 0xFF;
#endif
    /* Set the inputs as ADC channels */
    ADPC = ADCD_IN_CHN_TOT;
  }
}

/* TODO SGR_OK */
/**
 * @brief Set and prepare a single channel to conversion. All possible single
 * channels are present in the type ADCD_InputChn_t. If the selection mode is
 * "select mode" this routine set the single channel selected. If the selection
 * mode is "scan mode" this routine set the channels group from ANI0 to channel
 * number selected.
 * WARNING: Be careful that the channel to set was configured as ADC input !!!
 *
 * @param [in] AdcChn: channel to set. The possible values are present in the 
 * type ADCD_InputChn_t
 *
 * @return DRVD_ResSts_t
 * @retval DRVD_OK The ADC channel selected is correct
 * @retval DRVD_PAR_NOT_OK The ADC channel selected isn't exist
 */
static DRVD_ResSts_t Adcd_SetAdcChn(ADCD_InputChn_t AdcChn)
{
  DRVD_ResSts_t ResSts = DRVD_OK;
  
  if( (AdcChn >= ADCD_CONT_CHN_NMB) || (AdcChn >= ADCD_IN_CHN_TOT) )
  {
    /* Notify the wrong parameter */
    ResSts = DRVD_PAR_NOT_OK;
  }
  else
  {
    /* Clear INTAD interrupt */
    Adcd_DisableInterrupt()
    /* Set the correct channel in the relative register */
    ADS = (uint8_t)(AdcChn & 0x1FU);
    /* Update current channel */
    Adcd_SetSingleChannel(AdcChn)
  }
  
  return(ResSts);
}

/* TODO SGR_OK */
/**
 * @brief This routine set conversion time according to Adcd_ConvTimeFilterTable
 * and prescaler value passed by input parameter. In this table are present 
 * the possible setting according to conversion time mode, conversion Fclk and
 * discharge function. If the input parameter is associated to a valid time,
 * the routine will set it else will set he nearest possible setting.
 *
 * @param [in] PrescIdx: prescaler value used to set the conversion time
 *
 * @return None
 */
static void Adcd_SetConversionTime(uint8_t PrescIdx)
{
  uint8_t FclockIdx;
  uint8_t PrescIdxTemp  = PrescIdx;
  bool_t  SetFilterFlag = FALSE;

  /* Stop the conversion */
  Adcd_StopConv()

  /* Search Fclock index in the Adcd_FclockIndexTable */
  for(FclockIdx=0U; FclockIdx < 5U; FclockIdx++)
  {
    if( Adcd_FclockIndexTable[FclockIdx] == ADCD_FCLOCK_MHZ )
    {
      break;
    }
  }
  
  /* Read the filter flag by Conversion time table */
  SetFilterFlag = Adcd_ConvTimeFilterTable[PrescIdxTemp][FclockIdx];

  /* In case of setting prohibited, search the nearest possible setting */
  while( (SetFilterFlag == FALSE) && (PrescIdxTemp < 16U) )
  {
    PrescIdxTemp--;
    SetFilterFlag = Adcd_ConvTimeFilterTable[PrescIdxTemp][FclockIdx];
  }
  /* In case of search failed */
  if( SetFilterFlag == FALSE )
  {
    PrescIdxTemp = 0U;
  }

  /* Write the coding value in the register ADSMP */
  ADSMP = (PrescIdxTemp & 0x0FU);
}

/* TODO SGR_OK */
/**
 * @brief Perform a blocker delay in us according to configuration parameter
 * ADCD_FCLOCK_MHZ. The routine performance is much poor but for the specific
 * use of this module is acceptable.
 *
 * @param [in] DelayUs The range possible is [0-255] in us
 *
 * @return None
 */
static void Adcd_WaitDelayUs(uint8_t DelayUs)
{
  uint16_t TickIdx;
  uint16_t TickDelayNs = 
    (uint16_t)(((uint32_t)DelayUs*1000u)/Adcd_TCLOCK_ns);
  
  for(TickIdx = 0U; TickIdx < TickDelayNs; TickIdx++)
  {
    __no_operation();
  }
}


#endif /* end __ADCD_IS_PRESENT__ */

/*_____ E N D _____ (ADCD.c) _________________________________________________*/
