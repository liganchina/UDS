/**
 * @file TP_config.h
 * @author Auto-Generated - dbc ver.: W11Y15
 * @date 02/07/2015 - 14:30:7
 * @brief File containing the user configuration of TP module.
 * 
 * @see www.Bitron.net
 */
#ifndef __TP_CONFIG_H
#define __TP_CONFIG_H

/*______ G L O B A L - D E F I N E S _________________________________________*/

#define BLOCK_SIZE       0U      // Se BLOCK_SIZE = 0, il protocollo TP non invia mai il FC durante la sequenza di CF.
#define STMIN            0U

#define TICK_TPTX        10U   /* tm050. Correzione Soft_defect_40. Questo tick divisor era impostato a 5,
                                  ma il task era chiamato a 10ms, quindi i timeout valevano il doppio. PSA_ACP_B0_FR_13.*/

#define TP_N_AS  0U
#define TP_N_BS  1000U
#define TP_N_BR  200U
#define TP_N_CR  1000U

#define TP_CHECK_FUNCTP   ((CAND_GetDiagType() == CAND_FUNCTIONAL_DIAG_REQ) && \
                           (TpRx_Buffer[1] == 0x3EU) && \
                           (TpRx_Buffer[2] == 0x80U))          /*FRAT - macro per gestire la ricezione di un Tester Present funzionale*/

#define TP_TIMEOUT_TDIAG_CAN   10U /*FRAT - tempo minimo di attesa tra una richiesta e la successiva*/


/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

extern CAND_TxMsgName_t TP_GetMsgNameHnd(void);
extern CAND_RxMsgName_t TP_GetUdsPhysMsgRequestHnd(void);
extern CAND_RxMsgName_t TP_GetUdsFuncMsgRequestHnd(void);

#endif /* __NETP_CONFIG_H */

/*______ E N D _____ (TP_config.h) _________________________________________*/
