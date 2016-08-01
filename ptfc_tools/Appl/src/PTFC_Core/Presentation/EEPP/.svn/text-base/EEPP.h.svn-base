#ifndef __EEPP_H // MISRA C Rule 19.15: protect include file against repeated inclusion
#define __EEPP_H


/*==============================================================================
                           B I T R O N    S.p.A.
================================================================================

    Modulo:     EEPP.h
    Progetto:   -
    Descrizione:

    Specifica di riferimento:

    Requisiti implementati:

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [0]     [2012-03-05]  [M.Mastrodonato]          1^ implementazione

==============================================================================*/
#include "global.h"
#include "PRES_if.h"

/* Module inhibition filter */
#ifdef __EEPP_IS_PRESENT__

#include "EEPP_config.h"

#define EEPP_Default()  /* Elimina le eventuali callback non configurate in EEPP_config.h */

#define EEPP_INT_TIMEOUT  (EEPP_TIMEOUT/EEPP_TICK)

typedef enum Eepp_InitType_e
{
  EEPP_NO_INIT = 0,
  EEPP_INIT_P_RUN,
  EEPP_INIT_RUN,
}Eepp_InitType_t;

typedef enum EeppMgrReq_e
{
  EEPP_NO_REQUEST,
  EEPP_WRITE_REQUEST,
  EEPP_READ_REQUEST,
  EEPP_ERASE_REQUEST
}EeppMgrReq_t;


typedef struct EeppQueue_s
{
  EEPP_QueueState_t OccupationField;
  EEPP_Handle_t     HandleField;
  EeppMgrReq_t      OperationField;
  EEPP_Callback_t   UserCallback;
} EeppQueue_t;

typedef enum Eepp_State_e
{
    EEPP_IDLE,
    EEPP_READ_IN_PROG,
    EEPP_WRITE_IN_PROG,
    EEPP_ERASE_IN_PROG
}Eepp_State_t;

typedef struct EEPP_CfgTable_s
{
    void*           ram_data;
    const void *    rom_data;  /* Default Value */
    u16             ee_Addr; 
    u08             data_size; /*  NB: Max size 256 byte! */
    Eepp_InitType_t initLoad;
#if (ENABLE_MIRRORING == TRUE)
    EEPP_Handle_t   mirror_handle;
#endif
}EEPP_CfgTable_t;

extern const EEPP_CfgTable_t eepromTable[EEPP_HDL_MAX]; /*Definita in EepromManager_config.c */

#endif /* end __EEPP_IS_PRESENT__ */

#endif  // __EEPP_H
