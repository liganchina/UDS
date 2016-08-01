/*
 * Tp_if.h
 *
 *  Created on: 17/lug/2013
 *      Author: glenta
 */

#ifndef TP_IF_H_
#define TP_IF_H_

#ifdef TP_IF_OWNER
	#define TP_EXTERN
#else
	#define TP_EXTERN		extern
#endif

#include "TP_cfgIf.h"

typedef enum
{
  NAK78_NOT_PENDING        = 0x00U,
  NAK78_PENDING            = 0x01U
}UDSA_Nak78Pending_t;

TP_EXTERN u08 Diag_Requeste[RXBUF_LENGTH+2U];
TP_EXTERN u16 Diag_Requeste_Ln;
TP_EXTERN u08 Diag_Response[TXBUF_LENGTH];
TP_EXTERN u16 Diag_Response_Ln;
TP_EXTERN u16 Diag_Resp_MRDI;

TP_EXTERN UDSA_Nak78Pending_t UDSA_Nak78Pending;
TP_EXTERN u08 UDSA_Nak78PendingResp[4];
TP_EXTERN u08 UDSA_Nak78PendingResp_Ln;


/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name : TP_Init                                                              */
/*Role : Init Tp variable                                                     */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [...]                                                                   */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TP_Init(void);

/*----------------------------------------------------------------------------*/
/*Name : TpRx                                                                 */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [...]                                                                   */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TpRx (u08 * diagbuf, u08 diaglen);

/*----------------------------------------------------------------------------*/
/*Name : TpTx                                                                 */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    [...]                                                                   */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TpTx(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_CheckDiagnosticDataReady                                          */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN u08 TP_CheckDiagnosticDataReady(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_ResetDiagnosticDataReady                                          */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TP_ResetDiagnosticDataReady(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_RunTpTx                                                           */
/*Role :                                                                      */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TP_RunTpTx(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_ResetTimerDiag                                                    */
/*Role : Reset timer diag.                                                    */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TP_ResetTimerDiag(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_GetAddressingScheme                                               */
/*Role : Get diagnose request message type (Physical, Functional)             */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN u08 TP_GetAddressingScheme(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagPhysMsgReceived                                               */
/*Role : Physical diagnose message received (UDS)                             */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
TP_EXTERN void TP_DiagPhysMsgReceived(void);

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagHiPrtyPhysMsgReceived                                         */
/*Role : Physical diagnose high priority message received (UDS)               */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
#if (TP_HIPRTY_PHYS_MSG_EN == TRUE)
TP_EXTERN void TP_DiagHiPrtyPhysMsgReceived(void);
#endif

/*----------------------------------------------------------------------------*/
/*Name : TP_DiagFuncMsgReceived                                               */
/*Role : Functional diagnose message received (UDS)                           */
/*Interface :                                                                 */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
#if (TP_FUNC_MSG_EN == TRUE)
TP_EXTERN void TP_DiagFuncMsgReceived(void);
#endif


#endif /* TP_IF_H_ */
