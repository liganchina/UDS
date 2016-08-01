#ifndef UDSA_H
#define UDSA_H
/********************************************************************************/
/* @F_PROJECT:          TTM 636 FIAT                                            */
/* F_NAME:              UDSA.h                                                  */
/* @F_PURPOSE:                                                                  */
/* @F_CREATED_BY:       G. Lenta                                                */
/* @F_MPROC_TYPE:       Renesas 78kF0R1826-FC3                                  */
/* F_CREATION_DATE:     12/07/2012                                              */
/* @F_CREATION_SITE:    Bitron S.p.A.      - Grugliasco (TO)                    */
/******************************************* (C) Copyright 2012 Bitron S.p.A. ***/
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| MAD          Mario Dallera             Consultant
| FRAT         Francesco TALARICO        Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 23/12/2012  0.1  MAD     First release
| 09/05/2013  0.2  GIL     Iveco porting
| 13/03/2014  1.0  GIL     Finally remove UDS subfunction table, managed in UDSA_Subfunction_t
|                          table type adding field AdSch
| 13/10/2015  1.2  FRAT    Issues #1875, 1876 - Platform Alignment
*/

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "APPL_if.h"

/* Module inhibition filter */
#ifdef __UDSA_IS_PRESENT__

#include "UDSA_config.h"
#include "UDSA_cbk.h"

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef struct
{
  u08 SubFunction;
  u08 Enable;
  u16 RxDL;
  u08 Session; //DF 02.02.2015 //UDSA_DiagSession_t Session[MAX_NUM_SESSION];
  u08 (*Callback)(u08 *Data, u16 Length);
  UDSA_AddressingScheme_t    AdSch;
} UDSA_Subfunction_t;

typedef struct
{
  u08 Service;
  u08 Enable;
  u08 SuppSubFunc;
  u16 RxDL;
  u08 Session; //DF 02.02.2015 //UDSA_DiagSession_t Session[MAX_NUM_SESSION];
  u08 (*Callback)(u08 *Data, u16 Length);
  const UDSA_Subfunction_t *PntSubF;
} UDSA_Diagnostic_Services_t;

typedef struct
{
  u16 DID;
  u08 Enable;
  u16 RxDL;
  u08 Session; //DF: 29.01.2015 //UDSA_DiagSession_t  Session[MAX_NUM_SESSION];
  UDSA_AddressingScheme_t        AdSch;
  u08 (*Callback)(u08 *Data, u16 Length);
} UDSA_CmdByIdentifier_Service_t;


typedef union
{
 u32 L;    // esempio memorizzazione dato.L    = 0x167E41C6
 u16 I[2]; //   dato.I[0]=0x41C6;   dato.I[1]=0x167E
 u08 B[4]; //   dato.B[0]=0xC6; dato.B[1]=0x41; dato.B[2]=0x7E; dato.B[3]=0x16;
}UDSA_NecD;

//DF: aggiunta union per gestire dati a 16 bit e inserirli nella risposta UDS:
typedef union
{
  u16 word;
  u08 bytes[2];
}UDSA_WordByte;


/*______ G L O B A L - D E F I N E S _________________________________________*/

#define UDSA_CCT_RXBIT                          0x02u
#define UDSA_CCT_TXBIT                          0x01u

// DEFINIZIONE SERVIZI DIAGNOSI DIAG
#define START_DIAGNOSTIC_SESSION                0x10u
#define ECU_RESET                               0x11u
#define SECURITY_ACCESS                         0x27u
#define COMMUNICATION_CONTROL                   0x28U
#define TESTER_PRESENT                          0x3Eu

#define READ_DATA_BY_IDENTIFIER                 0x22u
#define READ_MEMORY_BY_ADDRESS                  0x23U
#define DYNAMICALLY_DEFINE_DATAID               0x2Cu
#define WRITE_DATA_BY_IDENTIFIER                0x2Eu
#define WRITE_MEMORY_BY_ADDRESS                 0x3Du

#define CLEAR_DIAGNOSTIC_INFORMATION            0x14u
#define READ_DTC_INFORMATION                    0x19u
//#define STOP_DIAGNOSTIC_SESSION                 0x20u
#define INPUT_OUTPUT_CONTROL_BY_IDENTIFIER      0x2Fu
#define ROUTINE_CONTROL                         0x31u

//#define START_ROUTINE_BY_LID                    0x31U
//#define STOP_ROUTINE_BY_LID                     0x32U
//#define REQ_ROUTINE_RESULT_BY_LID               0x33U
#define REQUEST_DOWNLOAD                        0x34u
#define REQUEST_UPLOAD                          0x35u
#define REQUEST_TRANSFER_DATA                   0x36u
#define REQUEST_TRANSFER_EXIT                   0x37u

//Lettura dei DTCs
#define REPORT_NUMBER_OF_DTC_BY_STATUS          0x01u
#define REPORT_DTC_BY_STATUS                    0x02u
#define REPORT_DTC_SNAPSHOT_IDENTIFICATION      0x03u
#define REPORT_DTC_SNAPSHOT_BY_DTC_NUMBER       0x04u
#define REPORT_EXTENDED_DATA_BY_DTC_NUMBER      0x06u
#define REPORT_SUPPORTED_DTC                    0x0Au
#define REPORT_DTC_FAULT_DETECTION_COUNTER      0x0Au

#define DIAGNOSTIC_VERSION                      0x0104u
#define PROCESS_PARAMETER                       0x0124u
#define PROGRESSIVE_NUMBER                      0x0126u
#define SEAT_POSITIONS                          0x0130u
#define INPUTS                                  0x0131u
#define OUTPUTS                                 0x0132u

#define TIME_STAMP_RAM                          0x1008u
#define TIME_STAMP_EEPROM                       0x2008u
#define KEY_ON_COUNTER                          0x200Au

#define EEPROM_RESET                            0x04u
#define CAN_MSG_DEBUG                           0x05u
#define KEY_OFF_ON_RESET                        0x02u


// #define DEFAULT_SESSION         0x01U
// #define PROGRAMMING_SESSION     0x02U
// #define EXTENDED_SESSION        0x04U
// #define VMS_SESSION             0x08U
// #define SYSTEM_SUPPL_SESSION    0x10U

//Routines
#define ROUTINE_ERASE_FLASH_BLOCK    0xFF00U
#define ROUTINE_FLASH_BLOCK_CHECKSUM 0xFF01U
#define ROUTINE_START           0x01U
#define ROUTINE_STOP            0x02U
#define ROUTINE_RESULT          0x03U

#define APPL_CKSUM_OK           0x5A5AU
#define APPL_CKSUM_NOK          0xAA55U

#define CHECK_VALID_MODULE           0x0203U

#define TIMER30S                    300U


#define NUMBER_DTC_BLOCS            10U
#define UDSA_SUP_POS_RSP_BIT      0x80U /* SuppressPosRspMsgIndicationBit */
#define UDSA_SUBF_END_TABLEROW    0xffU

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

u16 UDSA_BinarySearch(u16 pid, u08 num_elem, const UDSA_CmdByIdentifier_Service_t struct_pnt[]);
u16 UDSA_BinarySearch2(u16 pid, u08 num_elem, const UDSA_Diagnostic_Services_t struct_pnt[]);

/*______ E X T E R N A L - D A T A ___________________________________________*/

extern const UDSA_Diagnostic_Services_t       UDSA_Diagnostic_Services[MAX_NUM_SERVICE];
extern UDSA_SecurityAccess_t ECU_SecAccessSts;
extern u08 UDSA_FingerCount;
extern UDSA_AddressingScheme_t UDSA_AddresScheme;
extern u08 UDSA_FoundedSubf;
extern UDSA_VINSecAccess_t VIN_SecAccessSts;


#endif /* end __UDSA_IS_PRESENT__ */

#endif /* end UDSA_H */
