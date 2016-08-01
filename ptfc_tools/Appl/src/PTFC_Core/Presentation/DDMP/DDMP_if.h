/*
 * DDMP_if.h
 *
 *  Created on: 16/lug/2013
 *      Author: glenta
 */

#ifndef DDMP_IF_H_
#define DDMP_IF_H_

#ifdef DDMP_IF_OWNER
	#define DDMP_EXTERN
#else
	#define DDMP_EXTERN		extern
#endif

#include "DDMP_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

#define DDMP_DTC_ENABLE  1U
#define DDMP_DTC_DISABLE 0U

/*CANCELLAZIONE DTC*/

typedef enum DDMP_Clear_Result_e
{
  DDMP_CLEAR_OK   = 0,   /*cancellazione ok*/
  DDMP_CLEAR_FAIL = 1,   /*cancellazione fallita a causa di parameti errati*/
  DDMP_CLEAR_BUSY = 2,   /*cancellazione negata in quanto c'è già una operazione in corso*/
} DDMP_Clear_Result_t;


typedef enum DDMP_Write_Result_e
{
  DDMP_WRITE_OK   = 0,   /*scrittura ok*/
  DDMP_WRITE_FAIL = 1,   /*scrittura fallita a causa di parameti errati*/
  DDMP_WRITE_NOT  = 2,   /*scrittura negata per tabella piena*/
  DDMP_WRITE_BUSY = 3    /*scrittura negata in quanto c'è già una operazione in corso*/
} DDMP_Write_Result_t;

/* LETTURA DTC*/

typedef enum DDMP_Read_Result_e
{
  DDMP_READ_OK   = 0,    /*lettura ok*/
  DDMP_READ_FAIL = 1,    /*lettura fallita a causa di parameti errati*/
  DDMP_READ_OVER = 2,    /*lettura fallita a causa di un buffer dati di dimensioni ridotte*/
  DDMP_READ_NULL = 3,    /*lettura fallita a causa di assenza errori*/
  DDMP_READ_BUSY = 4     /*lettura negata in quanto c'è già una operazione in corso*/
} DDMP_Read_Result_t;

typedef enum DDMP_Snapshot_Ext_Num_e
{
  DDMP_FIRST_EXT_EVENT         =  0x01,
  DDMP_LAST_EXT_EVENT          =  0x02,
  DDMP_ALL_EXT_EVENT           =  0xFF
} DDMP_Snapshot_Ext_Num_t;

typedef enum DDMP_Snapshot_Num_Resp_e
{
  DDMP_FIRST_SNAPSHOT          =  0x00,
  DDMP_SECOND_SNAPSHOT         =  0x01
} DDMP_Snapshot_Num_Resp_t;


typedef enum Ddmp_EEPROM_e
{
  DDMP_SAVING_NOT_NEEDED = 0x00,
  DDMP_SAVING_NEEDED     = 0x01
} Ddmp_DtcSave_t;


/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

DDMP_EXTERN bool DDMP_GetGenericFailPresent( void );
DDMP_EXTERN bool DDMP_GetCurrentFailPresent( void );

/* Inizializzazione della funzione per la gestione dei DTC */
DDMP_EXTERN void DDMP_Init(void);
DDMP_EXTERN void DDMP_KeyStsChanged(PRES_KeyStatus_t KeyStatus);

DDMP_EXTERN DDMP_Write_Result_t DDMP_SetDtc( DDMP_ID_t ID, DDMP_FaultSymptom_t Fault );
DDMP_EXTERN DDMP_Write_Result_t DDMP_ResetDtc( DDMP_ID_t ID );

DDMP_EXTERN DDMP_Read_Result_t DDMP_ReadDtcSnapshotRecord(u16 DtcCode, u08 FaultSym, DDMP_Snapshot_Event_Num_t SnapNum, u08 *BufferPntr, u08 *AddLen);
DDMP_EXTERN DDMP_Read_Result_t DDMP_ReadDtcExtendedRecord(u16 DtcCode, u08 FaultSym, DDMP_Snapshot_Ext_Num_t ExtDataNum, u08 *BufferPntr, u08 *AddLen);
DDMP_EXTERN DDMP_Read_Result_t DDMP_ReadAllDtcByMask( u08 * BufferPntr, DDMP_Sub_Func_t SubFunc, u08 *Mask, u08 *NumOfDtc );
DDMP_EXTERN DDMP_Read_Result_t DDMP_ReportDTCSeverity(u16 DtcCode, u08 FaultSym, u08 *BufferPntr);
DDMP_EXTERN void DDMP_ReportFirstLastConfirmedDtc (DDMP_Sub_Func_t SubFun, u08 *DiagBufPtr);

DDMP_EXTERN void DDMP_SetControlDtcSetting(bool EnDisDtc);

DDMP_EXTERN u16  DDMP_CountAllDtcByMask(u08 *Mask);

DDMP_EXTERN u08 DDMP_CheckDtcPresence(DDMP_ID_t Dtc, DDMP_FaultSymptom_t *Fault_symptom, u08 *StatusDtc);

DDMP_EXTERN DDMP_Clear_Result_t DDMP_ClearAllDtc( void );
DDMP_EXTERN u08                 DDMP_GetDTCStatus(DDMP_ID_t DTC_ID);
DDMP_EXTERN Ddmp_DtcSave_t      DDMP_GetDTCSaveStatus(void);

DDMP_EXTERN void DDMP_GetOperationalModeStatus(u08 *DiagBufferPntr, u08 DataLen);

DDMP_EXTERN void DDMP_ComponeOperationalModeStatus(void);

/******************************************************************************/
/* Name :        void DDMP_SetTestNotCompletedStatusBit                       */
/* Role :        Aggiornamento degli StatusByte                               */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   StatusByte BIT6 "testNotCompletedThisMonitoringCycle"        */
/*               is set to 1.                                                 */
/*----------------------------------------------------------------------------*/
DDMP_EXTERN  void DDMP_SetTestNotCompletedStatusBit(PRES_KeyStatus_t KeySts);
 
/******************************************************************************/
/* Name :        void DDMP_ResetTestNotCompletedStatusBit                     */
/* Role :        Aggiornamento degli StatusByte                               */
/* Author:                                                                    */
/* Interface :   None                                                         */
/* Constraints :                                                              */
/* Behaviour :   StatusByte BIT6 "testNotCompletedThisMonitoringCycle"        */
/*               is set to 0.                                                 */
/*----------------------------------------------------------------------------*/
DDMP_EXTERN void DDMP_ResetTestNotCompletedStatusBit(DDMP_ID_t Dtc);
#endif /* DDMP_IF_H_ */
