#ifndef TP_H // MISRA C Rule 19.15: protect include file against repeated inclusion.
#define TP_H

#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __TP_IS_PRESENT__

/* =========================       include           ========================== */
/* =========================       define            ========================== */

#define SINGLE_FRAME            0x00U
#define FIRST_FRAME             0x10U
#define CONSECUTIVE_FRAME       0x20U
#define FLOW_CONTROL_FRAME      0x30U

#define IDLE_TX                    0U
#define WAIT_FLOWCONTROL_RX        1U
#define SEND_CONSECUTIVE_FRAME_TX  2U

// See § 2.5 "Communication Sequence [Non-OBD Compliant Systems]" in document [wprocan-a00-00-b_Eng.doc].
// See Table 4 Message Timing Rules.
#define N_AS                        (TP_N_AS/TICK_TPTX)    // SF/FF/CF transmission start => Transmission end. 25ms
#define N_BS                        (TP_N_BS/TICK_TPTX) // FF/CF Transmission end =>FC reception end.
#define N_BR                        (TP_N_BR/TICK_TPTX)  // FF/CF reception end =>FC transmission start.
#define N_CR                        (TP_N_CR/TICK_TPTX) // FC transmission end => CF reception end. CF reception end => CF reception end.
//#define N_CS                  (900U/TICK_TPTX)  // ex ST_MIN_LONGEST. (N_Cs + N_As) < 0.9 N_Cr_max. 463.229-0112-01F.2

// See requirements 463.229-0112-01A.1 and 463.229-0112-01B.1, document [96 463 229 99 Ind. F]: Pour les calculateurs connectés aux réseaux CAN Inter-Systèmes et CAN Diag, ces deux paramètres (N_As, N_Ar) sont sans objet.
// N_As: Délai de transfert sur le bus d’une trame CAN émise par l’émetteur
// N_Ar: Délai de transfert sur le bus d’une trame CAN émise par le récepteur

// N_Bs: Délai jusqu’à réception du prochain message Flow_Control.            Requirement 463.229-0112-01C.1: 1000 ms pour sous-capot (CAN_IS).
// N_Br: Délai jusqu’à transmission du prochain message Flow_Control.         Requirement 463.229-0112-01D.1:  200 ms pour sous-capot (CAN_IS).
// N_Cr: Délai jusqu’à réception du premier ou du prochain segment du bloc en cours.  Requirement 463.229-0112-01E.1: 1000 ms pour sous-capot (CAN_IS).


#define TIMEOUT_TDIAG_CAN   (TP_TIMEOUT_TDIAG_CAN/TICK_TPTX) /*FRAT - tempo minimo di attesa tra una richiesta e la successiva*/

#define CLEAR_TO_SEND              0U
#define WAIT                       1U
#define OVERFLOW                   2U

#define TPX_MAKING                 1U
#define TPTX_END                   0U

// Attenzione: la dimensione del buffer TX dipende dal numero max di dati gestiti (verificare numero DTC oppure servizi di read data)
// Buffer allocation depends on DTC lines number ((IND_MAX_CHANNEL*3) + 2)

/* =========================   enum and typedef   ========================== */
typedef struct
{
// tm221. Spostato i flag che appartengono al TP (erano dichiarati nella struttura KW_Type).
  u08 FlowControlTx    :1;
  u08 FlowControlRx    :1;
  u08 FlowControlError :1; // tm077. Controllo errata ricezione di un Flow Control inatteso.
  u08 DIAG_REP_Abort   :1; // tm221. Questo flag era definito nella struttura StatusCAN (eliminata).
  u08 TP_TX_running    :1; // Segnala richiesta di trasmissione messaggio TP in corso.
}TP_Flag_t;

typedef struct
{
  u08 Service            :1;   // Identifica lo stato del servizio: KW_SERVICE_COMPLETED/KW_SERVICE_RUNNING.

                             // Q&A ID 63. If requested, DTC memorization inhibition has to be kept in case of diagnosis session closed / expired.
                             // Additional comment : the behavior expected for other SRBLID services is not the same. Routine stopped when diagnosis session is closed/expired
  u08 Interd_Memo_Def    :1; // tm069. Servizio/richiesta di interdizione memorizzazione difetti: SRBLID 0x31 90.
                             // tm159. $-DIAG-HAB-430: Au démarrage de son logiciel applicatif un calculateur est dans l’état « autorisation de mémorisation des défauts ».

  u08 EnableDiag         :1;
  u08 DiagnosticRequest  :1;
  u08 DiagnosticResponse :1;
  u08 Type               :2; // diagType : functional, physic
} TP_Diag_t;


#endif /* end __TP_IS_PRESENT__ */

#endif  // TP_H
