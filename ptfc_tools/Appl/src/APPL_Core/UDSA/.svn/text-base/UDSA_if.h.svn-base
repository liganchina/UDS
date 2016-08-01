/********************************************************************************/
/* @F_PROJECT:          TTM 520 FIAT                                            */
/* F_NAME:              UDSA_if                                                 */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       Matteo MASTRODONATO                                     */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     24/lug/2013                                             */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
|              Matteo MASTRODONATO       Bitron S.p.A.
| FRAT         Francesco TALARICO        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 24/lug/2013     0.1  Matteo MASTRODONATO
| 13/10/2015      1.2  FRAT    Issues #1875, 1876 - Platform Alignment
*/

#ifndef UDSA_IF_H_
#define UDSA_IF_H_


#ifdef UDSA_IF_OWNER
	#define UDSA_EXTERN
#else
	#define UDSA_EXTERN		extern
#endif

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "UDSA_cfgIf.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum
{
  SEC_ACC_ECU_LOCKED  = 0x00U,
  SEC_ACC_ECU_PROGRAMMING_UNLOCKED  = 0x01U
}UDSA_SecurityAccess_t;

typedef enum
{
  UDSA_ADS_NONE  = 0x00U,
  UDSA_ADS_FUNCT = 0x01U,
  UDSA_ADS_PHYS  = 0x02U,
  UDSA_ADS_BOTH  = 0x03U
}UDSA_AddressingScheme_t;

typedef enum
{
  SEC_ACC_VIN_LOCKED       = 0x00U,
  SEC_ACC_VIN_UNLOCKED     = 0x01U
}UDSA_VINSecAccess_t;

typedef enum
{
  RETURN_CONTROL_TO_ECU = 0U,
  RESET_TO_DEFAULT,
  FREEZE_CURRENT_STATE,
  SHORT_TERM_ADJUSTMENT
}UDSA_IOControlSubf_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

#define SERVICE_OK                              0x00u

// DEFINIZIONE RISPOSTE NEGATIVE
// #define COPY_OF_SUBFUNCTION_NOT_SUPPORTED                0x01U
// #define COPY_OF_INCORRECT_MESSAGE_LENGTH                 0x02U
// #define COPY_OF_CONDITIONS_NOT_CORRECT                   0x03U
// #define COPY_OF_REQUEST_OUT_OF_RANGE                     0x04U
#define GENERAL_REJECT                                   0x10U
#define SERVICE_NOT_SUPPORTED                            0x11U
#define SUBFUNCTION_NOT_SUPPORTED                        0x12U
#define INCORRECT_MESSAGE_LENGHT_OR_INVALID_FORMAT       0x13U
// #define RESPONS_TOO_LONG                                0x14U
#define BUSY_REPEAT_REQUEST                              0x21U
#define CONDITIONS_NOT_CORRECT                           0x22U
// #define ROUTINE_NOT_COMPLETE                             0x23U
#define REQUEST_SEQUENCE_ERROR                           0x24U
//#define NO_RESPONSE_FROM_SUBNET_COMPONENT                0x25U
//#define FAILURE_PREVENTS_EXECUTION_OF_REQUESTED_ACTION   0x26U
#define REQUEST_OUT_OF_RANGE                             0x31U
#define SECURITY_ACCESS_DENIED                           0x33U
#define INVALID_KEY                                      0x35U
#define EXCEED_NUMBER_OF_ATTEMPTS                        0x36U
#define REQUIRED_TIME_DELAY_NOT_EXPIRED                  0x37U
// #define DOWNLOAD_NOT_ACCEPTED                            0x40U
// #define IMPROPER_DOWNLOAD_TYPE                           0x41U
// #define CANNOT_DOWNLOAD_TO_SPECIFIC_ADDRESS              0x42U
// #define CANNOT_DOWNLOAD_NUMBER_OF_BYTES_REQUESTED        0x43U
#define UPLOAD_DOWNLOAD_NOT_ACCEPTED                     0x70U
#define TRANSFER_SUSPENDED                               0x71U
#define GENERAL_PROGRAMMING_FAILURE                      0x72U
// #define WRONG_BLOCK_SEQUENCE_COUNTER                    0x73U
// #define ILLEGAL_ADDRESS_IN_BLOCK_TRANSFER                0x74U
// #define ILLEGAT_BYTE_COUNT_IN_BLOCK_TRANSFER             0x75U
// #define BLOCK_TRANSFER_DATA_CHECKSUM_ERROR               0x77U
#define REQUEST_CORRECTLY_RECEIVED_RESPONSE_PENDING      0x78U
#define SUBFUNCTION_NOT_SUPPORTED_IN_ACTIVE_SESSION      0x7EU
#define SERVICE_NOT_SUPPORTED_IN_ACTIVE_SESSION          0x7FU
//#define SERVICE_NOT_SUPPORTED_IN_ACTIVE_DIAGNOSTIC_MODE  0x80U
#define UDSA_NRC_VOLTAGE_TOO_HIGH                        0x92U
#define UDSA_NRC_VOLTAGE_TOO_LOW                         0x93U
#define RANGE_CHECK_FAILED                               0xA0U
#define CONFIGURATION_NOT_SUPPOERTED                     0xA1U
#define NO_RESPONSE                                      0xFFU
/*______ G L O B A L - D A T A _______________________________________________*/

UDSA_EXTERN u08 UDSA_DiagSession; //DF: diagsession bitwise

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*----------------------------------------------------------------------------*/
/*Name :                                                                      */
/*Role :                                                                      */
/*                                                                            */
/*Interface : -                                                               */
/*Pre-condition : -                                                           */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_EXTERN void UDSA_Init(void);

/*----------------------------------------------------------------------------*/
/*Name : UDSA_Decoding                                                        */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_EXTERN void UDSA_Decoding(u08 *Data, u16 Length);

/*----------------------------------------------------------------------------*/
/*Name : UDSA_DiagnosticServicesResponse                                      */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_EXTERN u08 UDSA_DiagnosticServicesResponse(u08 *Data, u16 Length );

/*----------------------------------------------------------------------------*/
/*Name : UDSA_GetSecAccessState                                               */
/*Role :                                                                      */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_EXTERN UDSA_SecurityAccess_t UDSA_GetSecAccessState(void);

/*----------------------------------------------------------------------------*/
/*Name : UDSA_GetSuppPosRspMsgIndBit                                          */
/*Role : Get suppress positive message response indication bit                */
/*Interface : -                                                               */
/*Pre-condition :                                                             */
/*Constraints :                                                               */
/*Behavior :                                                                  */
/*  DO                                                                        */
/*    []                                                                      */
/*  OD                                                                        */
/*----------------------------------------------------------------------------*/
UDSA_EXTERN bool UDSA_GetSuppPosRspMsgIndBit(void);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* UDSA_IF_H_ */
