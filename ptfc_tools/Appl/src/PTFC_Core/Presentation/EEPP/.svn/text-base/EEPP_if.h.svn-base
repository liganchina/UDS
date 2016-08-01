#ifndef __EEPP_IF_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __EEPP_IF_H

/*==============================================================================
                           B I T R O N    S.p.A.
================================================================================

    Modulo:     EEPP_if.h
    Progetto:   generico
    Descrizione:
        File di interfaccia: deve contenere tutti i metodi e i tipi messi 
        a disposizione dal modulo verso l'esterno (gli utenti)        

    Specifica di riferimento: 

    Requisiti implementati:

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [0]     [2012-03-05]  [M.Mastrodonato]          1^ implementazione

==============================================================================*/


/* Dichiarazione dell'interfaccia del Layer */
#ifdef EEPP_IF_OWNER
	#define EEPP_EXTERN
#else
	#define EEPP_EXTERN		extern
#endif

#include "EEPP_cfgIf.h"

/*********************************************
 *
 * DEFINIZIONE TIPI ESPORTATI
 *
 * */

typedef enum EEPP_QueueState_e
{
  EEPP_FREE,
  EEPP_OCCUPIED
}EEPP_QueueState_t;

typedef void (*EEPP_Callback_t)(DRVD_RStatus_t returnStatus, EEPP_Handle_t Handle);

/*********************************************
 *
 * DEFINIZIONE PROTOTIPI ESPORTATI
 *
 * ********************************************/
/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : void EEPP_PseudoInit(void)                                      */
/*Pre-condition : -                                                           */
/*Constraints : Call only when interrupt are disabled                         */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Initiates the module's private data and the ram copy of EEPROM, only    */
/*    for data configured as EEPP_INIT_P_RUN                                  */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN void EEPP_PseudoInit(void);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : void EEPP_Init(void)                                            */
/*Pre-condition : -                                                           */
/*Constraints : Call only when interrupt are disabled                         */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Initiates the module's private data and the ram copy of EEPROM, only    */
/*    for data configured as EEPP_INIT_RUN                                    */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN void EEPP_Init(void);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : void EEPP_Mgm(void)                                             */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Module's periodic call                                    			  */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN EEPP_QueueState_t EEPP_Mgm(void);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : DRVD_RStatus_t EEPP_ReadData(EEPP_Handle_t Handle, 			  */
/* 										   EEPP_Callback_t userCallback)	  */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Read data from EEPROM 			                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN DRVD_RStatus_t EEPP_ReadData(EEPP_Handle_t Handle, EEPP_Callback_t UserCallback);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : DRVD_RStatus_t Eepp_ReadEepromRawNow(u08* eeRamAddr,            */
/*                                                 u16  eeRomAddr,            */
/*                                                 u16  eeRomAddr)            */
/*Pre-condition : -                                                           */
/*Constraints : CALL ONLY WHEN INTERRUPT ARE DISABLED                         */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Read data from EEPROM, raw mode (without CRC check).                    */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN DRVD_RStatus_t Eepp_ReadEepromRawNow(u08* eeRamAddr, u16 eeRomAddr, u08 byteNumber);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : DRVD_RStatus_t EEPP_WriteData(EEPP_Handle_t Handle, 			      */
/* 											EEPP_Callback_t userCallback)	                        */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Write data to EEPROM                                                    */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN DRVD_RStatus_t EEPP_WriteData(EEPP_Handle_t Handle, EEPP_Callback_t UserCallback);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : PRES_Fault_t EEPP_GetDiag(u08 dummy)                            */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Get EEPROM diagnosis                                                    */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN PRES_Fault_t EEPP_GetDiag(u08 dummy);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : PRES_Fault_t NVMP_GetDataStatus(NVMP_Handle_t handle)           */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Return the status of the corresponding handle variable.                 */
/*    Values: MS_OK, MS_NOT_OK                                                */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN DRVD_RStatus_t EEPP_GetDataStatus(EEPP_Handle_t handle);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : DRVD_RStatus_t EEPP_WriteEepromNow(EEPP_Handle_t handle)        */
/*Pre-condition : -                                                           */
/*Constraints : CALL ONLY WHEN INTERRUPT ARE DISABLED                         */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Write data to EEPROM IMMEDIATELY                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN DRVD_RStatus_t EEPP_WriteEepromNow(EEPP_Handle_t handle);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : u16 EEPP_GetEepromSize(void)                                    */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Returns the EEPROM size                                                 */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
EEPP_EXTERN u16 EEPP_GetEepromSize(void);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : u16 EEPP_GetEepromPageSize(void)                                */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Returns the EEPROM page size                                            */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
u16 EEPP_GetEepromPageSize(void);

/*----------------------------------------------------------------------------*/
/*Name : Mastrodonato Matteo                                                  */
/*Role : SW designer                                                          */
/*                                                                            */
/*Interface : DRVD_RStatus_t EEPP_EraseEeprom(EEPP_Callback_t callback)       */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    Erase the EEPROM (0xFF)                                                 */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
DRVD_RStatus_t EEPP_EraseEeprom(EEPP_Callback_t callback);

#endif  // __EEPP_IF_H
