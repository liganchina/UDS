/*==============================================================================
                           B I T R O N    S.p.A.
===============================================================================

    Modulo:     EEPP.c
    Progetto:   -
    Descrizione:
        Gestione dati EEPROM tramite handle.

    Specifica di riferimento:

    Requisiti implementati:

    Storico versioni:
        [num]   [data]        [autore]                  [descrizione]
        [0]     [2009-10-15]  [M.Tedeschi - L.Rinaldi]  integrazione
        [1]     [2012-10-08]  [M.Mastrodonato]          integrazione BRP
        [2]     [2013-02-03]  [M.Mastrodonato]          nuovo driver

==============================================================================s*/

#define EEPP_IF_OWNER

// *------------------------------------------------------------------------- *
// *       Include files                                                      *
// *------------------------------------------------------------------------- *

/* TODO SGR - da ripristinare con i nuovi file da generare */
#include "MCAL_if.h"

#include "EEPP.h"
#include "EEPC.h"

/* Module inhibition filter */
#ifdef __EEPP_IS_PRESENT__

//-------------------------------------------------------------------------//

const u08 Eepp_eraseData[32] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
                                 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
                                 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU,
                                 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU };


Eepp_State_t        EEPP_State;
u16                 EEPP_Timeout;
EeppQueue_t         EEPP_Queue[EEPP_QUEUE_DIM];
u08                 EEPP_Busy;
u08                 EEPP_producer;
u08                 EEPP_consumer;
u08                 EEPP_writingCopy;
EEPP_QueueState_t   EEPP_queueState;
PRES_Fault_t        EEPP_HwBroken;
u08                 EEPP_PagesToErase;
DRVD_RStatus_t      EEPP_dataStatus[EEPP_HDL_MAX];


DRVD_RStatus_t Eepp_ReadEepromNow(EEPP_Handle_t handle);
DRVD_RStatus_t Eepp_QueuePush(EEPP_Handle_t Handle, EeppMgrReq_t Operation, EEPP_Callback_t userCallback);
EeppMgrReq_t   Eepp_QueuePop(EEPP_Handle_t *Handle, EEPP_Callback_t *userCallback);
DRVD_RStatus_t Eepp_ScheduleReadEeprom(void);
void           Eepp_InternalInit(Eepp_InitType_t InitType);
void           Eepp_QueueInit(void);


void EEPP_PseudoInit(void)
{
  Eepp_QueueInit();

  /* Calls pre-init user callback */
  EEPP_PRE_P_INIT()

  Eepp_InternalInit(EEPP_INIT_P_RUN);

  /* Calls post-init user callback */
  EEPP_POST_P_INIT()
}


void EEPP_Init(void)
{
  Eepp_QueueInit();

  /* Calls pre-init user callback */
  EEPP_PRE_INIT()

  Eepp_InternalInit(EEPP_INIT_RUN);

  /* Calls post-init user callback */
  EEPP_POST_INIT();
}

void Eepp_QueueInit(void)
{
  u08 i;

  /* Init ee queue */
  for (i = 0U; i < EEPP_QUEUE_DIM; i++)
  {
    EEPP_Queue[i].OccupationField = EEPP_FREE;
    EEPP_Queue[i].HandleField     = EEPP_HDL_MAX;
    EEPP_Queue[i].OperationField  = EEPP_NO_REQUEST;
    EEPP_Queue[i].UserCallback    = NULL;
  }

  EEPP_queueState = EEPP_FREE;
  EEPP_consumer   = 0U;
  EEPP_producer   = 0U;
  EEPP_State      = EEPP_IDLE;
  EEPP_HwBroken   = PRES_NO_FAULT;
}

void Eepp_InternalInit(Eepp_InitType_t InitType)
{
  EEPP_Handle_t handle = (EEPP_Handle_t) 0;
  DRVD_RStatus_t valueReturn;

  while (handle < EEPP_HDL_MAX)
  {
    EEPP_SAFETY_ACK()
    /* Verifico se devo caricare i dati al pwr on */
    if (eepromTable[handle].initLoad == InitType)
    {
      valueReturn = Eepp_ReadEepromNow(handle);

      if (valueReturn == MS_OK)
      {
        /* Dati ok, passo al prossimo handle */
        EEPP_dataStatus[handle] = MS_OK;
      }
      else
      {
  #if (ENABLE_MIRRORING == TRUE)
        /* Errore in letture: controllo se è prevista una copia di backup */
        if ((handle < (EEPP_HDL_MAX - 1))
            && (eepromTable[handle].mirror_handle != EEPP_HDL_MAX))
        {
          /* I dati sono duplicati, leggo il backup */
          valueReturn = Eepp_ReadEepromNow(eepromTable[handle].mirror_handle);
          if (valueReturn == MS_OK)
          {
            /* Dati backup ok, li copio in eeprom nella posizione della prima copia */
            //Eepp_QueuePush(handle, EEPP_WRITE_REQUEST, NULL);
            EEPP_WriteEepromNow(handle);
            EEPP_dataStatus[currentHandle] = MS_OK;
          }
          else
          {
            /* Dati backup errati: copio in ram i dati di default */
            memcpy(eepromTable[handle].ram_data,
                   eepromTable[handle].rom_data,
                   eepromTable[handle].data_size);
            /* Errore sul lettura di entrambe le copie, scrivo i default su entrambe */
            //Eepp_QueuePush(handle, EEPP_WRITE_REQUEST, NULL);
            //Eepp_QueuePush(eepromTable[handle].mirror_handle, EEPP_WRITE_REQUEST, NULL);
            EEPP_WriteEepromNow(handle);
            EEPP_dataStatus[currentHandle] = MS_NOT_OK;
          }
        }
        else
  #endif
        {
          EEPP_dataStatus[handle] = MS_NOT_OK;
          /* Dato non duplicato, copio in ram i dati di default */
          memcpy(eepromTable[handle].ram_data,
                 eepromTable[handle].rom_data,
                 (u16)eepromTable[handle].data_size);
          /* Errore in lettura, scrivo i valori di default */
          //Eepp_QueuePush(handle, EEPP_WRITE_REQUEST, NULL);
          EEPP_WriteEepromNow(handle);
        }
      }
    }
    else
    {
      /* Dato da non caricare al pwr-on, passo al prossimo */
    }
    handle++;
  }
}


EEPP_QueueState_t EEPP_Mgm(void)
{
  EeppMgrReq_t Request;
  static EEPP_Handle_t currentHandle;
  static EEPP_Callback_t currentUsrCbk;

#if (ENABLE_MIRRORING == TRUE)  
  EEPP_Handle_t handleCopy;
#endif

  /* Interrogo il manager dell'interfaccia per sapere cosa fare */
  EEPP_PREMGM()

  switch (EEPP_State)
  {
  case EEPP_IDLE:
    /* Prendo il prossimo elemento dalla coda */
    Request = Eepp_QueuePop(&currentHandle, &currentUsrCbk);

    if (Request != EEPP_NO_REQUEST)
    {
      EEPP_Timeout = EEPP_INT_TIMEOUT;
      EEPC_StatoEEPROM = EEPROM_IDLE;
      /* Init delle variabili del banco di EE da scrivere oppure leggere */
      if (Request == EEPP_WRITE_REQUEST)
      {
        /* Richiedo una scrittura driver eeprom */
        EEPC_Write(eepromTable[currentHandle].ram_data,
                   eepromTable[currentHandle].data_size,
                   eepromTable[currentHandle].ee_Addr,
                   FALSE);

        EEPP_State = EEPP_WRITE_IN_PROG;
      }
      else if(Request == EEPP_READ_REQUEST)
      {
        /* Richiedo una lettura driver eeprom */
        EEPC_Read(eepromTable[currentHandle].ram_data,
                  eepromTable[currentHandle].data_size,
                  eepromTable[currentHandle].ee_Addr,
                  FALSE);

        EEPP_State = EEPP_READ_IN_PROG;
      }
      else if(Request == EEPP_ERASE_REQUEST)
      {
        EEPP_PagesToErase--;
        /* Richiedo una scrittura raw driver eeprom */
        EEPC_Write((void*)Eepp_eraseData,
                   EEPROM_PAGE_SIZE,
                   (u16)((u16)EEPROM_PAGE_SIZE * (u16)EEPP_PagesToErase),
                   TRUE);

        EEPP_State = EEPP_ERASE_IN_PROG;
      }
      else
      {
      }
    }
    else
    {
      /* non faccio niente e aspetto il prossimo giro di task */
    }
    break;

  case EEPP_READ_IN_PROG:
    if (EEPC_StatoEEPROM == EEPROM_READ_GOOD)
    {
      /* Chiamo l'interface manager per comunicare la fine lettura */
      //SWI_EEPP_POSTMGM(MS_OK, currentHandle);
      EEPP_dataStatus[currentHandle] = MS_OK;
      if (currentUsrCbk != NULL)
      {
        currentUsrCbk(MS_OK, currentHandle);
      }
      EEPP_State = EEPP_IDLE;
    }
    else
    {
      if (EEPP_Timeout == 0U)
      {
        EEPC_StatoEEPROM = EEPROM_IDLE;

#if (ENABLE_MIRRORING == TRUE)
        /* Errore in lettura, verfico se il dato è duplicato */
        if (eepromTable[currentHandle].mirror_handle != EEPP_HDL_MAX)
        {
          handleCopy = eepromTable[currentHandle].mirror_handle;
          /* Provo a leggere il duplicato */
          EEPP_Timeout = EEPP_INT_TIMEOUT;

          EEPC_Read(eepromTable[handleCopy].ram_data,
                    eepromTable[handleCopy].data_size,
                    eepromTable[handleCopy].ee_Addr,
                    FALSE);
        }
        else /* Non ha duplicati, carico i valori di default */
#endif
        {
          memcpy(eepromTable[currentHandle].ram_data,
                 eepromTable[currentHandle].rom_data,
                 (u16)eepromTable[currentHandle].data_size);

          EEPP_dataStatus[currentHandle] = MS_NOT_OK;

          /* Chiamo l'eventuale callback per comunicare la fine lettura */
          if (currentUsrCbk != NULL)
          {
            currentUsrCbk(MS_OK, currentHandle);
          }
          EEPP_State = EEPP_IDLE;
        }
      }
    }

    break;

  case EEPP_WRITE_IN_PROG:
    if (EEPC_StatoEEPROM == EEPROM_WRITE_GOOD)
    {
#if (ENABLE_MIRRORING == TRUE)
      /* Verfico se il dato è duplicato */
      if ((currentHandle < (EEPP_HDL_MAX - 1))
          && (eepromTable[currentHandle].mirror_handle != EEPP_HDL_MAX)
          && (EEPP_writingCopy == FALSE))
      {
        EEPP_Timeout = EEPP_INT_TIMEOUT;
        EEPC_StatoEEPROM  = EEPROM_IDLE;
        handleCopy   = eepromTable[currentHandle].mirror_handle;

        EEPC_Write(eepromTable[handleCopy].ram_data,
                   eepromTable[handleCopy].data_size,
                   eepromTable[handleCopy].ee_Addr,
                   FALSE);

        EEPP_writingCopy = TRUE;
      }
      else
#endif
      {
        EEPP_writingCopy = FALSE;
        EEPP_HwBroken    = PRES_NO_FAULT; /* Resetto errore HW */
        EEPP_dataStatus[currentHandle] = MS_OK;
        /* Chiamo l'interface manager per comunicare la fine scrittura */
        //SWI_EEPP_POSTMGM(MS_OK, currentHandle);
        if (currentUsrCbk != NULL)
        {
          currentUsrCbk(MS_OK, currentHandle);
        }
        EEPP_State = EEPP_IDLE;
      }
    }
    else
    {
      if (EEPP_Timeout == 0U)
      {
        EEPP_HwBroken = PRES_DEVICE_FAULT; /* Setto errore HW */
        EEPP_dataStatus[currentHandle] = MS_NOT_OK;
        EEPC_StatoEEPROM   = EEPROM_IDLE;
        /* Chiamo l'interface manager per comunicare errore in scrittura */
        //SWI_EEPP_POSTMGM(MS_NOT_OK, currentHandle);
        if (currentUsrCbk != NULL)
        {
          currentUsrCbk(MS_NOT_OK, currentHandle);
        }
        EEPP_State = EEPP_IDLE;
      }
    }
    break;

  case EEPP_ERASE_IN_PROG:

    if (EEPC_StatoEEPROM == EEPROM_WRITE_GOOD)
    {
      if(EEPP_PagesToErase == 0U)
      {
        /* Chiamo l'interface manager per comunicare la fine lettura */
        //SWI_EEPP_POSTMGM(MS_OK, currentHandle);
        if (currentUsrCbk != NULL)
        {
          currentUsrCbk(MS_OK, currentHandle);
        }
        else
        {
        }
      }
      else
      {
        Eepp_QueuePush(EEPP_HDL_MAX, EEPP_ERASE_REQUEST, currentUsrCbk);
      }
      EEPP_State = EEPP_IDLE;
    }
    else
    {
      if (EEPP_Timeout == 0U)
      {
        EEPC_StatoEEPROM = EEPROM_IDLE;

        /* Chiamo l'eventuale callback per comunicare la fine lettura */
        if (currentUsrCbk != NULL)
        {
          currentUsrCbk(MS_NOT_OK, currentHandle);
        }
        EEPP_State = EEPP_IDLE;
      }
    }
    break;

    default:
    {
      EEPC_StatoEEPROM = EEPROM_IDLE;
      EEPP_State  = EEPP_IDLE;
    }
    break;
  }

  /* Chiamo la gestione eeprom (protocollo SPI) */
  if (EEPP_State != EEPP_IDLE)
  {
    if (EEPC_StatoCSI == CSI_IDLE)
    {
      /* Non ci sono trasmissioni SPI in corso */
      if (EEPC_StatoEEPROM != EEPROM_IDLE)
      {
        /* La macchina a stati deve ancora evolvere */
        EEPC_StatoCSI = CSI_WAIT_EEPROM; // assegna il bus alla EEPROM
        EEPC_Mgm();
      }
    }
    EEPP_Timeout--;
  }

  return EEPP_queueState;
}

DRVD_RStatus_t EEPP_ReadData(EEPP_Handle_t Handle, EEPP_Callback_t UserCallback)
{
  DRVD_RStatus_t result;
  
  if (Handle >= EEPP_HDL_MAX)
  {
    result = MS_PAR_NOT_OK;
  }
  else
  {
    result = Eepp_QueuePush(Handle, EEPP_READ_REQUEST, UserCallback);
  }
  return (result);
}

DRVD_RStatus_t EEPP_WriteData(EEPP_Handle_t Handle, EEPP_Callback_t UserCallback)
{
  DRVD_RStatus_t result;
  
  if (Handle >= EEPP_HDL_MAX)
  {
    result = MS_PAR_NOT_OK;
  }
  else
  {
    result = Eepp_QueuePush(Handle, EEPP_WRITE_REQUEST, UserCallback);
  }
  return (result);
}

DRVD_RStatus_t Eepp_QueuePush(EEPP_Handle_t Handle, EeppMgrReq_t Operation,
    EEPP_Callback_t userCallback)
{
  DRVD_RStatus_t valueReturn;

  /* Non controllo l'handle, è già stato verificato dalle richieste di Read/Write */

  /* Controllo se la coda è piena */
  if (EEPP_Queue[EEPP_producer].OccupationField == EEPP_FREE)
  {
    EEPP_Queue[EEPP_producer].OccupationField = EEPP_OCCUPIED;
    EEPP_Queue[EEPP_producer].HandleField     = Handle;
    EEPP_Queue[EEPP_producer].OperationField  = Operation;
    EEPP_Queue[EEPP_producer].UserCallback    = userCallback;

    EEPP_queueState = EEPP_OCCUPIED;

    EEPP_producer++;
    if (EEPP_producer >= EEPP_QUEUE_DIM)
    {
      EEPP_producer = 0U;
    }
    valueReturn = MS_OK;
  }
  else
  {
    valueReturn = MS_BUSY;
  }

  return (valueReturn);
}

EeppMgrReq_t Eepp_QueuePop(EEPP_Handle_t *Handle, EEPP_Callback_t *userCallback)
{
  EeppMgrReq_t newRequest;

  if (EEPP_Queue[EEPP_consumer].OccupationField == EEPP_OCCUPIED)
  {
    /* carico il successivo elemento da schedulare */
    newRequest    = EEPP_Queue[EEPP_consumer].OperationField;
    *Handle       = EEPP_Queue[EEPP_consumer].HandleField;
    *userCallback = EEPP_Queue[EEPP_consumer].UserCallback;

    /* Libero il posto nella coda */
    EEPP_Queue[EEPP_consumer].OccupationField = EEPP_FREE;

    /* gestisco i puntatori della coda circolare */
    EEPP_consumer++;
    if (EEPP_consumer >= EEPP_QUEUE_DIM)
    {
      EEPP_consumer = 0U;
    }
  }
  else
  {
    newRequest      = EEPP_NO_REQUEST;
    EEPP_queueState = EEPP_FREE;
  }
  return (newRequest);
}



DRVD_RStatus_t Eepp_ReadEepromNow(EEPP_Handle_t handle)
{
  DRVD_RStatus_t valueReturn;

  EEPC_StatoEEPROM = EEPROM_IDLE;

  if (EEPC_Read(eepromTable[handle].ram_data,
                eepromTable[handle].data_size,
                eepromTable[handle].ee_Addr,
                FALSE) != EEPROM_BAD_PARAMETERS)

  {
    valueReturn = Eepp_ScheduleReadEeprom();
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return (valueReturn);
}

DRVD_RStatus_t Eepp_ReadEepromRawNow(u08* eeRamAddr, u16 eeRomAddr, u08 byteNumber)
{
  DRVD_RStatus_t valueReturn;

  EEPC_StatoEEPROM = EEPROM_IDLE;

  if (EEPC_Read(eeRamAddr,
                byteNumber,
                eeRomAddr,
                TRUE) != EEPROM_BAD_PARAMETERS)
  {
    valueReturn = Eepp_ScheduleReadEeprom();
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return (valueReturn);
}


DRVD_RStatus_t EEPP_WriteEepromNow(EEPP_Handle_t handle)
{
  DRVD_RStatus_t  valueReturn;
  u16             delayCnt;
  u16             timeout;

  EEPC_StatoEEPROM = EEPROM_IDLE;

  if (EEPC_Write(eepromTable[handle].ram_data,
                 eepromTable[handle].data_size,
                 eepromTable[handle].ee_Addr,
                 FALSE) != EEPROM_BAD_PARAMETERS)
  {
    EEPP_SAFETY_ACK()

    timeout = 0x7FFFu;
    /* Scrivo dalla eeprom immediatamente */
    while ((EEPC_StatoEEPROM != EEPROM_WRITE_FAIL) && (EEPC_StatoEEPROM != EEPROM_WRITE_GOOD) && (timeout > 0U))
    {
      timeout--;
      SPID_INTCSI00_IsrPolling(); /* Controlla e chiama l'interrupt di fine trasmissione/ricezione */

      if (EEPC_StatoEEPROM == EEPROM_STATUS_REQUEST) /* Il driver è in attesa della fine scrittura in EEPROM */
      {
        /* EEPROM busy, delay 1ms @ 24MHz (no OPTIMIZATION)*/
        for (delayCnt = 0U; delayCnt < 2400U; delayCnt++)
        {
          NOP();
        }
        EEPP_SAFETY_ACK()
      }
      
      if (EEPC_StatoCSI == CSI_IDLE)
      {
        /* Non ci sono trasmissioni SPI in corso */
        if (EEPC_StatoEEPROM != EEPROM_IDLE)
        {
          /* La macchina a stati deve ancora evolvere */
          EEPC_StatoCSI = CSI_WAIT_EEPROM; // assegna il bus alla EEPROM
          EEPC_Mgm();
        }
      }
    }

    if (EEPC_StatoEEPROM == EEPROM_WRITE_GOOD)
    {
#if (ENABLE_MIRRORING == TRUE)
      /* Verfico se il dato è duplicato */
      if ((handle < (EEPP_HDL_MAX - 1))
          && (eepromTable[handle].mirror_handle != EEPP_HDL_MAX))
      {
        EEPP_WriteEepromNow(eepromTable[handle].mirror_handle);
      }
      else
#endif
      {
        valueReturn   = MS_OK; /* lettura OK */
        EEPP_HwBroken = PRES_NO_FAULT; /* Resetto errore HW */
      }
    }
    else
    {
      valueReturn   = MS_NOT_OK; /* Timeout scaduto */
      EEPP_HwBroken = PRES_DEVICE_FAULT; /* Setto errore HW */
    }

    EEPC_StatoEEPROM = EEPROM_IDLE;
  }
  else
  {
    valueReturn = MS_PAR_NOT_OK;
  }

  return (valueReturn);
}

DRVD_RStatus_t Eepp_ScheduleReadEeprom(void)
{
  DRVD_RStatus_t valueReturn;

  /* Leggo dalla eeprom immediatamente */
  while ((EEPC_StatoEEPROM != EEPROM_READ_FAIL) && (EEPC_StatoEEPROM != EEPROM_READ_GOOD))
  {
    SPID_INTCSI00_IsrPolling(); /* Controlla e chiama l'interrupt di fine trasmissione/ricezione */

    if (EEPC_StatoCSI == CSI_IDLE)
    {
      /* Non ci sono trasmissioni SPI in corso */
      if (EEPC_StatoEEPROM != EEPROM_IDLE)
      {
        /* La macchina a stati deve ancora evolvere */
        EEPC_StatoCSI = CSI_WAIT_EEPROM; // assegna il bus alla EEPROM
        EEPC_Mgm();
      }
    }
  }

  if (EEPC_StatoEEPROM == EEPROM_READ_GOOD)
  {
    valueReturn = MS_OK; /* lettura OK */
  }
  else
  {
    valueReturn = MS_NOT_OK; /* Timeout scaduto */
  }

  EEPC_StatoEEPROM = EEPROM_IDLE;

  return (valueReturn);
}

PRES_Fault_t EEPP_GetDiag(u08 dummy)
{
  return (EEPP_HwBroken);
}


DRVD_RStatus_t EEPP_GetDataStatus(EEPP_Handle_t handle)
{
  return EEPP_dataStatus[handle];
}

u16 EEPP_GetEepromSize(void)
{
  return (EEPROM_SIZE);
}

u16 EEPP_GetEepromPageSize(void)
{
  return (EEPROM_PAGE_SIZE);
}

DRVD_RStatus_t EEPP_EraseEeprom(EEPP_Callback_t callback)
{
  EEPP_PagesToErase = EEPROM_SIZE / EEPROM_PAGE_SIZE;

  return (Eepp_QueuePush(EEPP_HDL_MAX, EEPP_ERASE_REQUEST, callback));
}


#endif /* end __EEPP_IS_PRESENT__ */
