/******************************************************************************/
/* @F_PROJECT:          TTM636                                                */
/* F_NAME:              FVMP_config                                           */
/* @F_PURPOSE:                                                                */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                   */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                */
/* F_CREATION_DATE:     02/lug/2013                                           */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                  */
/******************************************* (C) Copyright 2013 Bitron S.p.A. */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| MAM          Matteo MASTRODONATO       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 02/lug/2013 0.1  MAM
*/

#define FVMP_CONFIG_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "FVMP.h"

/* Module inhibition filter */
#ifdef __FVMP_IS_PRESENT__

/*______ L O C A L - M A C R O S _____________________________________________*/

#define CARE          FALSE
#define DONT_CARE     TRUE

#define FVMP_NUM_DTC         30U
#define FVMP_NUM_LINE_INIT   10U

/*______ L O C A L - T Y P E S__ _____________________________________________*/

typedef struct FVMP_DtcMgmInfo_s
{
  DDMP_ID_t DtcId        ;
  u08       Vbatt_Ele  :1;
  u08       Vbatt_Mot  :1;
  u08       KeyOn      :1;
  u08       EngineOn   :1;
  u08       Net        :1;
  u08       ProtRele   :1;
  u08       Crank5sec  :1;
}FVMP_DtcMgmInfo_t;

typedef DRVD_RStatus_t (*FVMP_InitDiagCbk_t)(u08 hdl, u08 Fault); /* Fault Init Callback  */

typedef struct FVMP_InitDiag_s
{
  FVMP_Handle_t        FvmpHdl;
  FVMP_InitDiagCbk_t   InitFault;
}FVMP_InitDiag_t;

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static DDMP_FaultSymptom_t FVMP_GetSymptom     (PRES_Fault_t Fault);
static bool                DctSetResetEnabled  (FVMP_Handle_t hdl);
static void                Fvmp_SetVbattState  (FVMP_Handle_t hdl, bool state, PRES_Fault_t Fault, bool FaultDestructive);
static void                Fvmp_BattOkReset    (FVMP_Handle_t batt_hdl, FVMP_Handle_t hdl);

/*______ L O C A L - D A T A _________________________________________________*/

/* !!! NB: gli oggetti che NON settano DTC devono essere tutti al fondo !!! */
const FVMP_CfgTable_t FVMP_CfgTable[FVMP_HDL_MAX] = {
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /* HANDLE                          |  DIAG_CHAN                  | DIAG_FUN_PTR                         |  STATE_FUN_PTR                  | VALID_TIME_MS | INVALID_TIME_MS  | FAULT_IMPACT  |      FAULT_CALLBACK            */
    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /* FVMP_INTERNAL_FAIL,           */ { 0U,                          (GetDiag_t)EEPP_GetDiag,                 (GetState_t)NULL,                        100u,           100u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_MEM_KEY,                 */ { 0U,                          (GetDiag_t)DIAC_GetBtnMemDiag,           (GetState_t)NULL,                      30000u,           100u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_TILT_SLIDE_KEY,          */ { 0U,                          (GetDiag_t)DIAC_GetBtnTiltSlideDiag,     (GetState_t)NULL,                      30000u,           100u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_LIFT_BACKR_KEY,          */ { 0U,                          (GetDiag_t)DIAC_GetBtnLiftBackDiag,      (GetState_t)NULL,                      30000u,           100u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_TILT_SLIDE_RL,           */ { MOTP_ArraySlideTilt,         (GetDiag_t)MOTP_GetCmdArrayDiag,         (GetState_t)MOTP_GetCmdArrayDiagState,  1000u,          1000u,         STB_DESTR|STG_DESTR, FVMP_ReleFaultEvent      },
    /* FVMP_LIFT_BACK_RL             */ { MOTP_ArrayLiftBack,          (GetDiag_t)MOTP_GetCmdArrayDiag,         (GetState_t)MOTP_GetCmdArrayDiagState,  1000u,          1000u,         STB_DESTR|STG_DESTR, FVMP_ReleFaultEvent      },
    /* FVMP_PROT_RL,                 */ { DOVFC_CmdRelProtEN,          (GetDiag_t)DOVFC_GetDiag,                (GetState_t)DOVFC_GetDiagState,          400u,           400u,         STB_DESTR|STG_DESTR, FVMP_ProtReleFaultEvent  },
    /* FVMP_SLIDE_HALL_SENSOR,       */ { MOTP_SLIDE,                  (GetDiag_t)MOTP_GetPosFbkDiag,           (GetState_t)NULL,                          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_TILT_HALL_SENSOR,        */ { MOTP_TILT,                   (GetDiag_t)MOTP_GetPosFbkDiag,           (GetState_t)NULL,                          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_LIFT_HALL_SENSOR,        */ { MOTP_LIFT,                   (GetDiag_t)MOTP_GetPosFbkDiag,           (GetState_t)NULL,                          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_BACKREST_HALL_SENSOR,    */ { MOTP_BACK_R,                 (GetDiag_t)MOTP_GetPosFbkDiag,           (GetState_t)NULL,                          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_DRIVER_SEAT_HEATER       */ { DOIFC_CmdHeatDrv,            (GetDiag_t)DOIFC_GetDiag,                (GetState_t)DOIFC_GetDiagState,          200u,           200u,         STB_DESTR|STG_DESTR, FVMP_FaultEvent          },
    /* FVMP_PSNGR_SEAT_HEATER        */ { DOIFC_CmdHeatPass,           (GetDiag_t)DOIFC_GetDiag,                (GetState_t)DOIFC_GetDiagState,          200u,           200u,         STB_DESTR|STG_DESTR, FVMP_FaultEvent          },
    /* FVMP_STEERW_HEATER            */ { DOIFC_CmdHeatSteer,          (GetDiag_t)DOIFC_GetDiag,                (GetState_t)DOIFC_GetDiagState,          200u,           200u,         STB_DESTR|STG_DESTR, FVMP_FaultEvent          },
    /* FVMP_NTC_STEERW               */ { SNSP_STEER_WHEEL,            (GetDiag_t)SNSP_GetDiag,                 (GetState_t)NULL,                       1000u,          1000u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_NTC_DRV                  */ { SNSP_SEAT_DRV,               (GetDiag_t)SNSP_GetDiag,                 (GetState_t)NULL,                       1000u,          1000u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_NTC_PSG                  */ { SNSP_SEAT_PASS,              (GetDiag_t)SNSP_GetDiag,                 (GetState_t)NULL,                       1000u,          1000u,         DESTR_OFF,           FVMP_FaultEvent          },
	  /* FVMP_VEHICLE_SPEED_MSG        */ { 0U,                          (GetDiag_t)FUNP_GetVehicleSpeedDiag,     (GetState_t)NETP_GetCanDiagState,         50u,            50u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_NODE_MUTE                */ { NETP_NODE_MUTE_HND,          (GetDiag_t)NETP_GetCanDiag,              (GetState_t)NETP_GetCanDiagState,          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_BUS_OFF                  */ { NETP_BUS_OFF_HND,            (GetDiag_t)NETP_GetCanDiag,              (GetState_t)NETP_GetCanDiagState,         50u,            50u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_BCM                      */ { NETP_BCM_ABS_FAULTY,         (GetDiag_t)NETP_GetAbsentFaultyStatus,   (GetState_t)NETP_GetCanDiagState,         50u,            50u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_IPC_Faulty               */ { NETP_IPC_ABS_FAULTY,         (GetDiag_t)NETP_GetAbsentFaultyStatus,   (GetState_t)NETP_GetCanDiagState,          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_ACM_Faulty               */ { NETP_ACM_ABS_FAULTY,         (GetDiag_t)NETP_GetAbsentFaultyStatus,   (GetState_t)NETP_GetCanDiagState,          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_STATUS_BCM1              */ { CAND_STATUS_BH_BCM1_HND,     (GetDiag_t)NETP_GetMsgDiag,              (GetState_t)NETP_GetCanDiagState,          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_STATUS_CCAN3             */ { CAND_STATUS_CCAN3_HND,       (GetDiag_t)NETP_GetMsgDiag,              (GetState_t)NETP_GetCanDiagState,          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_OP_MODE_STS_SNA          */ { 0U,                          (GetDiag_t)VF608_GetOpModeDiag,          (GetState_t)NULL,                          0u,             0u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_SLIDE_LOW_CURRENT        */ { ADCC_MotorsSens,             (GetDiag_t)ADCC_GetSlideCurrentDiag,     (GetState_t)FUNP_IsSlideActive,         1000u,          1000u,         DESTR_OFF,           FVMP_FaultEvent          },
    /* FVMP_VBATT_MOTORS             */ { ADCC_MOT_Fbk,                (GetDiag_t)ADCC_GetDiag ,                (GetState_t)NULL,                        500u,           500u,         DESTR_OFF,           FVMP_VbattEvent          },
    /* FVMP_VBATT_ELE                */ { ADCC_Ele_Fbk,                (GetDiag_t)ADCC_GetDiag ,                (GetState_t)NULL,                        300u,           300u,         DESTR_OFF,           FVMP_VbattEvent          },
    /* FVMP_MOTOR_OVERCURRENT        */ { 0U,                          (GetDiag_t)MOTP_GetMotorsCurrentDiag ,   (GetState_t)NULL,                       1000u,          1000u,         DESTR_OFF,           MOTP_OverCurrentEvent    }
};

MOTP_CFGIF_EXTERN PRES_Fault_t MOTP_GetMotorsCurrentDiag(u08 dummy);

/* Per il test di abilitazione DTC per singola linea di diagnosi               */
/* NB: Questa tabella deve contenere solo per gli oggetti settano dei DTC e    */
/*     deve essere ALLINEATA AGLI HANDLE ALLA TABELLA DI CONFIGURAZIONE FVMP.  */
/*                               */
const FVMP_DtcMgmInfo_t FVMP_DctMgmTable[FVMP_NUM_DTC] = {
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*      DTC                        | DTC_ID                       | Vbatt_Ele OK |  Vbatt_Mot OK   |   KeyOn   |  EngineOn   |   NET On   |  ProtRelè OK   |    Crank      */
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*  (0) FVMP_INTERNAL_FAIL         */ { DDMP_INTERNAL_FAIL,             CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_INTERNAL_FAIL       (2)  */
    /*  (1) FVMP_MEM_KEY               */ { DDMP_MEM_KEY,                   CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_MEM_KEY             (3)  */
    /*  (1) FVMP_TILT_SLIDE_KEY        */ { DDMP_TILT_SLIDE_KEY,            CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_TILT_SLIDE_KEY      (3)  */
    /*  (2) FVMP_LIFT_BACKR_KEY        */ { DDMP_LIFT_BACKR_KEY,            CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_LIFT_BACKR_KEY      (4)  */
    /*  (3) FVMP_TILT_SLIDE_RL         */ { DDMP_TILT_SLIDE_RL,             CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,         CARE},        /* DDMP_SLIDE_CUSH_RL       (5)  */
    /*  (4) FVMP_LIFT_BACK_RL          */ { DDMP_LIFT_BACK_RL,              CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,         CARE},        /* DDMP_LIFT_BACK_RL        (6)  */
    /*  (5) FVMP_PROT_RL               */ { DDMP_PROT_RL,                   CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_PROT_RL             (8)  */
    /*  (6) FVMP_SLIDE_HALL_SENSOR     */ { DDMP_SLIDE_HALL_SENSOR,         CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,    DONT_CARE},        /* DDMP_SLIDE_HALL_SENSOR   (9)  */
    /*  (7) FVMP_TILT_HALL_SENSOR      */ { DDMP_TILT_HALL_SENSOR,          CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,    DONT_CARE},        /* DDMP_TILT_HALL_SENSOR    (10) */
    /*  (8) FVMP_LIFT_HALL_SENSOR      */ { DDMP_LIFT_HALL_SENSOR,          CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,    DONT_CARE},        /* DDMP_LIFT_HALL_SENSOR    (11) */
    /*  (9) FVMP_BACKREST_HALL_SENSOR  */ { DDMP_BACKREST_HALL_SENSOR,      CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,    DONT_CARE},        /* DDMP_BACKREST_HALL_SENSOR(12) */
    /*  (10) FVMP_DRIVER_SEAT_HEATE    */ { DDMP_DRIVER_SEAT_HEATER,        CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_HEATER_BACK         (19) */
    /*  (11) FVMP_PSNGR_SEAT_HEATER    */ { DDMP_PSNGR_SEAT_HEATER,         CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_HEATER_CUSHION      (20) */
    /*  (12) FVMP_STEERW_HEATER        */ { DDMP_STEERW_HEATER,             CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_HEATER_CUSHION      (20) */
    /*  (13) FVMP_NTC_STEERW           */ { DDMP_NTC_STEERW,                CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_NTC_STEERW           */
    /*  (14) FVMP_NTC_DRV              */ { DDMP_NTC_DRV,                   CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_NTC_DRV              */
    /*  (15) FVMP_NTC_PSG              */ { DDMP_NTC_PSG,                   CARE,          DONT_CARE,       CARE,          CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_NTC_PSG              */
	  /*  (13) FVMP_VEHICLE_SPEED_MSG    */ { DDMP_VEHICLE_SPEED,             CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_VEHICLE_SPEED_MSG   (24) */
    /*  (14) FVMP_NODE_MUTE            */ { DDMP_BUS_OFF          ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,         CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_BUS_OFF             (26) */
    /*  (15) FVMP_BUS_OFF              */ { DDMP_BUS_OFF          ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_BUS_OFF             (26) */
    /*  (16) FVMP_BCM                  */ { DDMP_BCM              ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_BCM                 (26) */
    /*  (17) FVMP_IPC_Faulty           */ { DDMP_IPC              ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_IPC                 (26) */
    /*  (19) FVMP_ACM_Faulty           */ { DDMP_ACM              ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_ACM                 (26) */
    /*  (21) FVMP_STATUS_BCM1          */ { DDMP_STATUS_BCM1      ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* FVMP_STATUS_BCM1         (26) */
    /*  (22) FVMP_STATUS_CCAN3         */ { DDMP_STATUS_CCAN3     ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* FVMP_STATUS_CCAN3        (26) */
    /*  (29) FVMP_OP_MODE_STS_SNA      */ { DDMP_IWC_SIGNAL_FROM_BCM,       CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,    DONT_CARE},        /* DDMP_IWC_SIGNAL_FROM_BCM (22) */
    /*  (29) FVMP_SLIDE_LOW_CURRENT    */ { DDMP_SLIDE_LOW_CURRENT,         CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_SLIDE_LOW_CURRENT   (22) */
    /*  (24) FVMP_VBATT_MOTORS         */ { DDMP_VBATT_MOTORS     ,         CARE,          DONT_CARE,       CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_VBATT_MOTORS        (00) */
    /*  (23) FVMP_VBATT_ELE            */ { DDMP_NO_DTC_ID        ,    DONT_CARE,          DONT_CARE,  DONT_CARE,     DONT_CARE,    DONT_CARE,     DONT_CARE,         CARE},        /* DDMP_NO_DTC_ID           (00) */
    /*  (25) FVMP_MOTOR_OVERCURRENT    */ { DDMP_NO_DTC_ID        ,         CARE,               CARE,       CARE,     DONT_CARE,    DONT_CARE,          CARE,         CARE},        /* DDMP_NO_DTC_ID           (00) */
};


/*______ L O C A L - D A T A _________________________________________________*/

/* Elenco dei DTC che necessitano della inizializzazione della macchina
 * a stati di diagnosi dopo una transizione chiave OFF --> ON                 */
const FVMP_InitDiag_t  FVMP_InitDiag_DTC_ID[FVMP_NUM_LINE_INIT] = {
    /* (0) */  { FVMP_TILT_SLIDE_RL,        (FVMP_InitDiagCbk_t)DOVFC_SetFault },
    /* (1) */  { FVMP_LIFT_BACK_RL,         (FVMP_InitDiagCbk_t)DOVFC_SetFault },
    /* (2) */  { FVMP_PROT_RL,              (FVMP_InitDiagCbk_t)DOVFC_SetFault },
    /* (3) */  { FVMP_SLIDE_HALL_SENSOR,    (FVMP_InitDiagCbk_t)MOTP_SetFault  },
    /* (4) */  { FVMP_TILT_HALL_SENSOR,     (FVMP_InitDiagCbk_t)MOTP_SetFault  },
    /* (5) */  { FVMP_LIFT_HALL_SENSOR,     (FVMP_InitDiagCbk_t)MOTP_SetFault  },
    /* (6) */  { FVMP_BACKREST_HALL_SENSOR, (FVMP_InitDiagCbk_t)MOTP_SetFault  },
    /* (7) */  { FVMP_DRIVER_SEAT_HEATER,   (FVMP_InitDiagCbk_t)DOIFC_SetFault },
    /* (8) */  { FVMP_PSNGR_SEAT_HEATER,    (FVMP_InitDiagCbk_t)DOIFC_SetFault },
    /* (9) */  { FVMP_STEERW_HEATER,        (FVMP_InitDiagCbk_t)DOIFC_SetFault }
};

/*______ P R I V A T E - D A T A _____________________________________________*/

FVMP_DtcMgmInfo_t  FVMP_EnableDtc;

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

void FVMP_ConfigPseudoInit(void)
{
  FVMP_EnableDtc.Net           = FALSE;
}

void FVMP_ConfigInit(void)
{
  FVMP_EnableDtc.KeyOn         = FALSE;
  FVMP_EnableDtc.EngineOn      = FALSE;
  FVMP_EnableDtc.Vbatt_Ele     = TRUE;
  FVMP_EnableDtc.Vbatt_Mot     = TRUE;
  FVMP_EnableDtc.ProtRele      = TRUE;  
  FVMP_EnableDtc.Crank5sec     = TRUE;
}

void FVMP_FaultEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive)
{
  DDMP_FaultSymptom_t Ddmp_Fault;
  DDMP_ID_t           Ddmp_ID;
  bool dtcSRenabled;

  Ddmp_ID    = FVMP_DctMgmTable[hdl].DtcId;
  Ddmp_Fault = FVMP_GetSymptom(Fault);
  
  dtcSRenabled = DctSetResetEnabled(hdl);

  if ((Ddmp_Fault == DDMP_NO_SYMPTOM) && (dtcSRenabled))
  {
    DDMP_ResetTestNotCompletedStatusBit(Ddmp_ID);
    DDMP_ResetDtc(Ddmp_ID);
  }
  else if ((Ddmp_Fault != (DDMP_FaultSymptom_t) 0xFFu) && (dtcSRenabled))
  {
    DDMP_ResetTestNotCompletedStatusBit(Ddmp_ID);
    DDMP_SetDtc(Ddmp_ID, Ddmp_Fault);
  }
  else
  {
    /* NOP */
  }
}

void FVMP_VbattEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive)
{
  u08 i;
  bool dtcSRenabled;
  
  dtcSRenabled = DctSetResetEnabled(hdl);

  if ((Fault == PRES_NO_FAULT) && (dtcSRenabled))
  {

    //FVMP_EnableDtc.Vbatt = TRUE;
    Fvmp_SetVbattState(hdl,TRUE,Fault,FaultDestructive);

    /* Resetto la FVMP, così sarà in grado di validare/svalidare un DTC precedentemente settato */
    for (i = 0U; i < FVMP_HDL_MAX; i++)
    {
      Fvmp_BattOkReset(hdl,(FVMP_Handle_t)i);
    }
  }
  else if ((Fault != PRES_NO_FAULT) && (dtcSRenabled))
  {
    // FVMP_EnableDtc.Vbatt = FALSE;
    Fvmp_SetVbattState(hdl,FALSE,Fault,FaultDestructive);
  }
  else
  {
    /* NOP */
  }
}

static void Fvmp_SetVbattState(FVMP_Handle_t hdl, bool state, PRES_Fault_t Fault, bool FaultDestructive)
{
  switch(hdl)
  {
    case FVMP_VBATT_MOTORS:
    /* set or reset DTC */
    FVMP_FaultEvent(hdl, Fault, FaultDestructive);
    FVMP_EnableDtc.Vbatt_Mot = state;
    break;
    
    case FVMP_VBATT_ELE:
    FVMP_EnableDtc.Vbatt_Ele = state;
    break;
    
    default:
    FVMP_EnableDtc.Vbatt_Ele = state;
    break;
  }
}


static void Fvmp_BattOkReset(FVMP_Handle_t batt_hdl, FVMP_Handle_t hdl)
{
  switch(batt_hdl)
  {
    case FVMP_VBATT_MOTORS:
    if (FVMP_DctMgmTable[hdl].Vbatt_Mot == CARE)
    {
      FVMP_ResetLine(hdl);
    }
    break;
    
    case FVMP_VBATT_ELE:
    if (FVMP_DctMgmTable[hdl].Vbatt_Ele == CARE)
    {
      FVMP_ResetLine(hdl);
    }
    break;
    
    default:
    if (FVMP_DctMgmTable[hdl].Vbatt_Ele == CARE)
    {
      FVMP_ResetLine(hdl);
    }
    break;
  }
}

void FVMP_ReleFaultEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive)
{
  //MOTP_OverCurrentEvent(hdl, Fault);
  switch(hdl)
  {
  case FVMP_TILT_SLIDE_RL:
    MOTP_SetCmdArrayFaultEvent(MOTP_ArraySlideTilt,Fault);
    break;
  case FVMP_LIFT_BACK_RL:
    MOTP_SetCmdArrayFaultEvent(MOTP_ArrayLiftBack,Fault);
    break;
  default:
    break;
  }
  FVMP_FaultEvent(hdl, Fault, FaultDestructive);
}

void FVMP_NetOnEvent(void)
{
  u08 i;

  FVMP_EnableDtc.Net = TRUE;

  /* Resetto la FVMP, così sarà in grado di validare/svalidare un DTC precedentemente settato */
  for (i = 0U; i < FVMP_HDL_MAX; i++)
  {
    if (FVMP_DctMgmTable[i].Net == CARE)
    {
      FVMP_ResetLine((FVMP_Handle_t)i);
    }
  }
}

void FVMP_NetOffEvent(void)
{
  FVMP_EnableDtc.Net = FALSE;
}

/*-------------------------------------------------------*/
/* Diagnosis enable/disable events                       */
/*-------------------------------------------------------*/
void FVMP_KeyStsChanged(PRES_KeyStatus_t KeyStatus)
{
  static bool prevKeyStatus = KEYA_OFF_STATUS;
  u08 i;

  if(KeyStatus == KEYA_CRANK_STATUS)
  {
    prevKeyStatus = KEYA_CRANK_STATUS;
    FVMP_EnableDtc.Crank5sec = FALSE;
    FVMP_EnableDtc.KeyOn     = FALSE;
  }
  else
  {
    if (prevKeyStatus == KEYA_CRANK_STATUS)
    {
      TLRP_SetSlow(TLRP_DiagReEnable);
    }
    else
    {
    }

    if(KeyStatus == KEYA_ON_STATUS)
    {
      prevKeyStatus        = KEYA_ON_STATUS;
      FVMP_EnableDtc.KeyOn = TRUE;
      /* Resetto la FVMP, così sarà in grado di validare/svalidare un DTC precedentemente settato */
      for (i = 0U; i < FVMP_HDL_MAX; i++)
      {
        if (FVMP_DctMgmTable[i].KeyOn == CARE)
        {
          FVMP_ResetLine((FVMP_Handle_t)i);
        }
      }
    }
    else
    {
      prevKeyStatus           = KEYA_OFF_STATUS;
      FVMP_EnableDtc.KeyOn    = FALSE;
      /* Non è necessario il reset della FVMP */
    }
  }
}

void FVMP_DiagEnableAfterCrank(void)
{
  u08 i;

  FVMP_EnableDtc.Crank5sec = TRUE;

  /* Resetto la FVMP, così sarà in grado di validare/svalidare un DTC precedentemente settato */
  for (i = 0U; i < FVMP_HDL_MAX; i++)
  {
    if (FVMP_DctMgmTable[i].Crank5sec == CARE)
    {
      FVMP_ResetLine((FVMP_Handle_t)i);
    }
  }
}

void FVMP_KeyOffOnTrans(void)
{
  /* KeyOff to KeyOn transition -> Reset Monitoring Cycle and initialization
   * of the diagnosis state machine for the DTCs already present in faulty memory
   */

  u08                 i;
  FVMP_Handle_t       FVMP_Hdl;
  u08                 StatusDtc;
  DDMP_FaultSymptom_t Fault_symptom;
  DDMP_ID_t           DDMP_Dtc_ID;
  PRES_Fault_t        fault;

  i = 0U;
  FVMP_Hdl    = FVMP_InitDiag_DTC_ID[0].FvmpHdl;
  DDMP_Dtc_ID = FVMP_DctMgmTable[FVMP_Hdl].DtcId;

  /* Check for all DTCs if it is necessary to init the diag state machine of the handle */
  while(i < FVMP_NUM_LINE_INIT)
  {
    /* Check if this DTC was already set */
    if (DDMP_CheckDtcPresence(DDMP_Dtc_ID, &Fault_symptom, &StatusDtc) == TRUE)
    {
      /* Init the state machine of the handle only if the TestFailed bit is TRUE */
      if (StatusDtc & 0x01)
      {
        fault = PRES_GetFaultBySymptom(Fault_symptom);
        FVMP_InitDiag_DTC_ID[i].InitFault(FVMP_CfgTable[FVMP_Hdl].DIAG_CHAN, fault);
      }
    }
    else
    {
      ; /* It is not necessary to initialize this handle, it is NO_FAULT */
    }
    /* go on with next handle */
    i++;
    FVMP_Hdl    = FVMP_InitDiag_DTC_ID[i].FvmpHdl;
    DDMP_Dtc_ID = FVMP_DctMgmTable[FVMP_Hdl].DtcId;
  }
}

void FVMP_OpModeStsChanged(OperationalModeSts_t OpModeStatus)
{
  u08 i;
    
  if (OpModeStatus == CMMD_IGNITION_ON_ENGON)
  {
    FVMP_EnableDtc.EngineOn = TRUE;
    /* Resetto la FVMP, così sarà in grado di validare/svalidare un DTC precedentemente settato */
    for (i = 0U; i < FVMP_HDL_MAX; i++)
    {
      if (FVMP_DctMgmTable[i].EngineOn == CARE)
      {
        FVMP_ResetLine((FVMP_Handle_t)i);
      }
    }
  }
  else
  {
    FVMP_EnableDtc.EngineOn  = FALSE;
  }
}

/*______ P R I V A T E - F U N C T I O N S ___________________________________*/

/* Conversione del fault in sintomo */

static DDMP_FaultSymptom_t FVMP_GetSymptom(PRES_Fault_t Fault)
{
  DDMP_FaultSymptom_t Ddmp_Fault;

  Ddmp_Fault = PRES_GetSymptomByFault(Fault);

  return (Ddmp_Fault);
}

/* Test Abilitazione DTC per singola linea di diagnosi */
static bool DctSetResetEnabled(FVMP_Handle_t hdl)
{
  return (  (FVMP_DctMgmTable[hdl].Vbatt_Ele  | FVMP_EnableDtc.Vbatt_Ele   ) &
      (FVMP_DctMgmTable[hdl].Vbatt_Mot  | FVMP_EnableDtc.Vbatt_Mot   ) &
      (FVMP_DctMgmTable[hdl].Net        | FVMP_EnableDtc.Net         ) &
      (FVMP_DctMgmTable[hdl].ProtRele   | FVMP_EnableDtc.ProtRele    ) &
      (FVMP_DctMgmTable[hdl].Crank5sec  | FVMP_EnableDtc.Crank5sec   ) &
      (FVMP_DctMgmTable[hdl].KeyOn      | FVMP_EnableDtc.KeyOn       ) &
      (FVMP_DctMgmTable[hdl].EngineOn   | FVMP_EnableDtc.EngineOn    )
  );
}

void FVMP_ProtReleFaultEvent(FVMP_Handle_t hdl, PRES_Fault_t Fault, bool FaultDestructive)
{
  /* Call the normal fault event */
  FVMP_ReleFaultEvent(hdl, Fault, FaultDestructive);

  /* set the Prot Relè bit */
  if ((Fault == PRES_NO_FAULT) ||
      (Fault == PRES_NOT_TESTED))
  {
    FVMP_EnableDtc.ProtRele = TRUE;
  }
  else
  {
    FVMP_EnableDtc.ProtRele = FALSE;
  }
}

bool FVMP_isProtReleOk(void)
{
  return FVMP_EnableDtc.ProtRele;
}




#endif /* end __FVMP_IS_PRESENT__ */

/*______ E N D _____ (Template.c) _________________________________________*/

