/******************************************************************************/
/* @F_PROJECT:          ALM                                                   */
/* F_NAME:              PRES                                                  */
/* @F_PURPOSE:                                                                */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                   */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                */
/* F_CREATION_DATE:     12/giu/2013                                           */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                  */
/****************************************** (C) Copyright 2012 Bitron S.p.A. **/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MM           Matteo MASTRODONATO       Bitron S.p.A.
| CC           Carmine Celozzi           Akhela S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 12/giu/13   0.1  MM       First draft
|-----------------------------------------------------------------------------
| 26/09/14    1.0  CC       Insert the routines PRES_PseudoInit and
|                           PRES_PrPseudoWakeup for new power management done by
|                           LPMS module
|-----------------------------------------------------------------------------
| 
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#define PRES_IF_OWNER

#include "PRES_if.h"

/*______ L O C A L - T Y P E S _______________________________________________*/

typedef struct PRES_FaultSymptom_s
{
  DDMP_FaultSymptom_t  Symptom;
}PRES_FaultSymptom_t;

/* N.B. this array should be aligned with PRES_Fault_t in PRES_typedefs.h */
PRES_FaultSymptom_t PRES_FaultSymptom [PRES_MAX_FAULT] = {
 /* PRES_NOT_TESTED            */  { DDMP_NO_SYMPTOM                },
 /* PRES_NO_FAULT              */  { DDMP_NO_SYMPTOM                },
 /* PRES_SHORT_TO_BAT          */  { DDMP_SCVBATT_SYM               },
 /* PRES_SHORT_TO_GND          */  { DDMP_SCGND_SYM                 },
 /* PRES_OPEN_LOAD             */  { DDMP_OC_SYM                    },
 /* PRES_OVER_VOLTAGE          */  { DDMP_HIGH_VOLTAGE_SYM          },
 /* PRES_UNDER_VOLTAGE         */  { DDMP_LOW_VOLTAGE_SYM           },
 /* PRES_MSG_NOT_RECEIVED      */  { DDMP_MISSING_MESSAGE_SYM       },
 /* PRES_MSG_FAULTY            */  { DDMP_SIGNAL_INVALID_SYM        },
 /* PRES_GENERIC_FAULT         */  { DDMP_GENERAL_FAIL_SYS          },
 /* PRES_PLAU_FAULT            */  { DDMP_SIGNAL_PAUSIB_FAIL_SYM    },
 /* PRES_SIGNAL_ERROR          */  { DDMP_ERRATIC_SYM               },
 /* PRES_SIGNAL_SIGNAL_INVALID */  { DDMP_SIGNAL_SIGNAL_INVALID_SYM },
 /* PRES_BUS_OFF_FAULT         */  { DDMP_BUS_OFF_SYM               },
 /* PRES_DEVICE_FAULT          */  { DDMP_COMP_INT_FAIL_SYS         },
 /* PRES_NOT_PROGRAMMED        */  { DDMP_NOT_PROGRAMMED            },
 /* PRES_OC_OR_STG             */  { DDMP_OC_SCGND_SYM              },
 /* PRES_OC_OR_STB             */  { DDMP_OC_SCVBATT_SYM            },
 /* PRES_BUTTON_STUCKED        */  { DDMP_SIGNAL_STUCK_HIGH_SYM     },
 /* PRES_TOO_FEW_TRANS         */  { DDMP_SIGNAL_TOO_FEW_TRANS_SYM  },
 /* PRES_BAD_CONFIGURATION     */  { DDMP_BAD_CONFIGURATION_SYM     },
};

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/*----------------------------------------------------------------------------*/
/*Name :  PRES_Init                                                           */
/*Role :  Inizializzazione del layer Presentation                             */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void PRES_Init(void)
{
/*_____ Inizializzazione del layer PRES ________________*/

/* TLRP module inhibition filter */
#ifdef __TLRP_IS_PRESENT__
  TLRP_Init();  /* Timer low resolution manager       */
#endif

/* NETP module inhibition filter */
#ifdef __NETP_IS_PRESENT__
  NETP_Init();  /*                                    */
#endif

/* DINP module inhibition filter */
#ifdef __DINP_IS_PRESENT__
  DINP_Init();  /* Digital Input Filtered/Debouced    */
#endif

/* AVGP module inhibition filter */
#ifdef __AVGP_IS_PRESENT__
  AVGP_Init();  /* Analog input averages              */
#endif

/* EEPP module inhibition filter */
#ifdef __EEPP_IS_PRESENT__
  EEPP_Init();  /* Eeprom manager                     */
#endif
/* FUNP module inhibition filter */
#ifdef __FUNP_IS_PRESENT__
  FUNP_Init();  /* FUNP module                        */
#endif

/* FVMP module inhibition filter */
#ifdef __FVMP_IS_PRESENT__
  FVMP_Init();  /* Fault validation manager           */
#endif

/* TP module inhibition filter */
#ifdef __TP_IS_PRESENT__  
  TP_Init();    /* Transport protocol                 */
#endif

/* DDMP module inhibition filter */
#ifdef __DDMP_IS_PRESENT__
  DDMP_Init();  /* Dtc manager                        */
#endif

/* MOTP module inhibition filter */
#ifdef __MOTP_IS_PRESENT__
  MOTP_Init();  /* Dtc manager                        */
#endif

/* SNSP module inhibition filter */
#ifdef __SNSP_IS_PRESENT__
  SNSP_Init();  /* NTC sensor manager L.B.             */
#endif

  /* LINP module inhibition filter */
#ifdef __LINP_IS_PRESENT__
  LINP_Init();  /*                                    */
  /* Send a WakeUp on LIN bus and reset flag */
  LINP_WakeUp(UARTD_CHN_HND);
#endif 
}

/*----------------------------------------------------------------------------*/
/*Name :  PRES_Init                                                           */
/*Role :  Inizializzazione del layer Presentation                             */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void PRES_PseudoInit(void)
{
/*_____ Inizializzazione del layer PRES ________________*/

/* TLRP module inhibition filter */
#ifdef __TLRP_IS_PRESENT__
  TLRP_Init();  /* Timer low resolution manager       */
#endif

/* NETP module inhibition filter */
#ifdef __NETP_IS_PRESENT__
  NETP_Init();  /*                                    */
#endif

/* DINP module inhibition filter */
#ifdef __DINP_IS_PRESENT__
  DINP_Init();  /* Digital Input Filtered/Debouced    */
#endif

  /* FVMP module inhibition filter */
#ifdef __FVMP_IS_PRESENT__
  FVMP_PseudoInit();  /* Fault validation manager     */
#endif
  
/* EEPP module inhibition filter */
#ifdef __EEPP_IS_PRESENT__
  EEPP_PseudoInit();  /* Eeprom manager                     */
#endif
}

/*----------------------------------------------------------------------------*/
/*Name :  PRES_Init                                                           */
/*Role :  Inizializzazione del layer Presentation                             */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
void PRES_PrPseudoWakeup(void)
{
/*_____ Inizializzazione del layer PRES ________________*/

/* AVGP module inhibition filter */
#ifdef __AVGP_IS_PRESENT__
  AVGP_Init();  /* Analog input averages              */
#endif

/* EEPP module inhibition filter */
#ifdef __EEPP_IS_PRESENT__
  EEPP_Init();  /* Eeprom manager                     */
#endif

/* FVMP module inhibition filter */
#ifdef __FVMP_IS_PRESENT__
  FVMP_Init();  /* Fault validation manager           */
#endif

/* FUNP module inhibition filter */
#ifdef __FUNP_IS_PRESENT__
  FUNP_Init();  /* FUNP module                        */
#endif

/* TP module inhibition filter */
#ifdef __TP_IS_PRESENT__  
  TP_Init();    /* Transport protocol                 */
#endif

/* DDMP module inhibition filter */
#ifdef __DDMP_IS_PRESENT__
  DDMP_Init();  /* Dtc manager                        */
#endif

/* MOTP module inhibition filter */
#ifdef __MOTP_IS_PRESENT__
  MOTP_Init();  /* Motor with position fbk manager    */
#endif

/* SNSP module inhibition filter */
#ifdef __SNSP_IS_PRESENT__
  SNSP_Init();  /* NTC sensor manager L.B.            */
#endif

/* LINP module inhibition filter */
#ifdef __LINP_IS_PRESENT__
  LINP_Init();  /*                                    */
/* Send a WakeUp on LIN bus and reset flag */
  LINP_WakeUp(UARTD_CHN_HND);
#endif
}

/**
 * @brief Power off routine for presentation layer. It must call all 
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void PRES_RunPwrOff(void)
{
   /* LINP module inhibition filter */
#ifdef __LINP_IS_PRESENT__
    LINP_GoToSleep(UARTD_CHN_HND);  
#endif

   /* MOTP module inhibition filter */
#ifdef __MOTP_IS_PRESENT__
   /* Scrittura in EE al power off */
   MOTP_PwrOff();
#endif

   /* EEPP module inhibition filter *
    * WARNING: this should be the last function of PRES Layer
    * in order to write in eeprom all data coming from previous
    * switched-off modules. */
 #ifdef __EEPP_IS_PRESENT__
    /* Scrittura in EE al power off */
    EEPP_EcuPowerOff();
 #endif
}

/**
 * @brief Power off routine for presentation layer. It must call all
 * power off routines of the module for power off transition of the
 * power management
 *
 * @param [in]  None
 * @param [out] None
 *
 * @return None
 */
void PRES_PseudoRUNPwrOff(void)
{
   /* LINP module inhibition filter */
#ifdef __LINP_IS_PRESENT__
    LINP_GoToSleep(UARTD_CHN_HND);
#endif

   /* EEPP module inhibition filter *
    * WARNING: this should be the last function of PRES Layer
    * in order to write in eeprom all data coming from previous
    * switched-off modules. */
 #ifdef __EEPP_IS_PRESENT__
    /* Scrittura in EE al power off */
    EEPP_EcuPowerOff();
 #endif
}


/**
 * @brief This routine returns the DTC symptom code from a presentation fault
 * @param [in] PRES_Fault_t the presentation fault
 * @param [out] None
 * @return DDMP_FaultSymptom_t the DTC symptom associated with the fault
 */
DDMP_FaultSymptom_t PRES_GetSymptomByFault(PRES_Fault_t Fault)
{
  DDMP_FaultSymptom_t ret_val;

  ret_val = PRES_FaultSymptom[Fault].Symptom;

  return ret_val;
}

/**
 * @brief This routine returns the layer Presentation fault from a DTC symptom
 * @param [in]  DDMP_FaultSymptom_t the DTC symptom
 * @param [out] None
 * @return PRES_Fault_t the presentation fault associated with the symptom code
 */
PRES_Fault_t PRES_GetFaultBySymptom(DDMP_FaultSymptom_t Symptom)
{
  PRES_Fault_t ret_val;
  u08 i;

  for (i = 0u; i < PRES_MAX_FAULT; i++)
  {
    if (PRES_FaultSymptom[i].Symptom == Symptom)
    {
      ret_val = (PRES_Fault_t)i;
      break;
    }
  }

  return ret_val;
}
/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/*______ L O C A L - F U N C T I O N S _______________________________________*/

/*______ E N D _____ (Template.c) _________________________________________*/

