/**
 * @file EEPC.c
 * @author Michele Tedeschi
 * @date 15/10/2009
 * @brief File containing EEPROM Driver functions. Includes SPI protocol implementation.
 *
 * @see www.Bitron.net
 */

#define EEPC_IF_OWNER

// *------------------------------------------------------------------------- *
// *       Include files                                                      *
// *------------------------------------------------------------------------- *
#include "global.h"
#include "EEPC.h"

/* Module inhibition filter */
#ifdef __EEPC_IS_PRESENT__

// CS setup time 100ns

// valori possibili di ReadType
#define NORMAL_READ     0U  // read data request
#define SAFETY_READ     1U  // read back written data to check the write operation (upon write data request)

#define EEPROM_RECOVERY_COUNTER 3U          // // // 254U     // number of retries to access EEPROM
                                        // durata dei tentativi =  EEPROM_RECOVERY_COUNTER*EEPROM_CLK_TICK ms
                                        // se vale uno non esegue i ritentativi

#define EEPROM_RESULT_COUNTER   (100U/EEPROM_CLK_TICK)  // [ms] max time to let the EEPROM calling task read the operation result

typedef struct {
  u08 CRC_8;//tm224.   // one more byte needed for automatic CRC management
  u08 Data[EEPROM_BUFFER_SIZE];
} EepromMemoryBuffer;


typedef struct {
  u16 ReadType            :1; // type of read access request: normal data read or last written data re-read for integrity check
  u16 ReadWriteRaw        :1; // Read data without crc check
}teepromFlag;

static __saddr teepromFlag eepromFlag;

//#pragma dataseg = IXRAM

// dati da impostare per richiedere al driver l'operazione di read/write

#if  EEPROM_BUFFER_SIZE < 255U
static  u08 EepromByteCounter;             // Number of data byte to read/write
#else
static  u16 EepromByteCounter;             // Number of data byte to read/write
#endif
static  u08 EepromRecoveryCounter;         // Contatore dei tentativi di accesso in caso di errore
static  u16 EepromAddress;                 // Start address of the EEPROM location(s) to read/write
static  u08 *pEepromData;                  // Puntatore ai dati RAM da scrivere/leggere su EEPROM. tm224
#pragma dataseg = default



// Instruction Set for the SPI EEPROM
#define WREN    0x06U   // Set Write Enable Latch
#define WRDI    0x04U   // Reset Write Enable Latch
#define RDSR    0x05U   // Read Status Register
#define WRSR    0x01U   // Write Status Register
#define READ    0x03U   // Read Data from Memory Array
#define WRITE   0x02U   // Write Data to Memory Array


// Calculate CRC-8 Values.  Uses The CCITT-8 Polynomial, Expressed As X^8 + X^5 + X^4 + 1

#define CRC_8_TABLE_SIZE    256

/* Global variables declaration */
__saddr EEPC_StatiCSI      EEPC_StatoCSI;
__saddr EEPC_StatiEEPROM   EEPC_StatoEEPROM;


//tm332. inizio
static void calculateCRC_8(u08 data);
static void copyEepromBuffer(void);
static void eepromGetData(u08 rxData);
static u08  eepromSetData(void);
//tm332. fine


/*
  Quando un task vuole accedere alla EEPROM deve eseguire le seguenti operazioni:
1) attendere EEPC_StatoEEPROM == EEPROM_IDLE
2) caricare il numero di byte richiesti in EepromByteCounter (valore massimo EEPROM_BUFFER_SIZE, minimo 1)
3) caricare l'indirizzo iniziale dei dati EEPROM in EepromAddress (valore massimo EEPROM_SIZE-1, minimo 0)
4) caricare l'indirizzo iniziale dei dati RAM in pEepromData
5) impegnare la EEPROM in READ/WRITE, impostando EEPC_StatoEEPROM = EEPROM_READ_REQUEST oppure EEPROM_WRITE_REQUEST
-> queste operazioni sono fatte chiamando eepromRead/eepromWrite(void *ramStartAddress, u16 byteNumber, u16 eepromStartAddress).

6) attendere il risultato: EEPC_StatoEEPROM >= EEPROM_READ_GOOD (oppure EEPC_StatoEEPROM == EEPROM_IDLE, nel caso di timeout)
7) leggere il risultato dell'operazione: test EEPC_StatoEEPROM == EEPROM_READ_GOOD, EEPROM_WRITE_GOOD oppure errore
8) liberare la EEPROM, impostando EEPC_StatoEEPROM = EEPROM_IDLE;
-> queste operazioni sono eseguite da EepromManager(void).

Nota:
se la EEPROM rimane impegnata (EEPC_StatoEEPROM != EEPROM_IDLE) oltre EEPROM_RESULT_COUNTER dopo che il risultato è pronto
(nel caso ad esempio che il task chiamante non liberi il device), viene sbloccata in automatico.
-> forzatura di EEPC_StatoEEPROM = EEPROM_IDLE sulla scadenza di EepromResultTimer.
*/


#if  EEPROM_BUFFER_SIZE < 255U  // tm471
/**
 * @brief This function reads data from eeprom.
 * @param ramStartAddress The address of the destination of data (ram)
 * @param byteNumber data size to read
 * @param eepromStartAddress The address of source data (eeprom)
 */
EEPC_StatiEEPROM EEPC_Read(void *ramStartAddress, u08 byteNumber, u16 eepromStartAddress, bool readRaw)
#else
EEPC_StatiEEPROM EEPC_Read(void *ramStartAddress, u16 byteNumber, u16 eepromStartAddress, bool readRaw)
#endif
{
  u16 lastDataAddress;

  if (EEPC_StatoEEPROM == EEPROM_IDLE)
  {
    if (readRaw == TRUE)
    {
      lastDataAddress = eepromStartAddress + byteNumber;
    }
    else
    {
      lastDataAddress = eepromStartAddress + byteNumber + 1u; /* 1 byte di CRC */
    }
    
    // CheckParameters
    if ((byteNumber == 0U) || (byteNumber > EEPROM_BUFFER_SIZE) || (lastDataAddress > EEPROM_SIZE))
    {
      EEPC_StatoEEPROM = EEPROM_BAD_PARAMETERS;        // segnala errore parametri fuori range
    }
    else
    {
      EepromByteCounter = byteNumber;
      EepromRecoveryCounter = EEPROM_RECOVERY_COUNTER;
      EepromAddress = eepromStartAddress;
      pEepromData = (u08 *)ramStartAddress;//tm224

      eepromFlag.ReadType = NORMAL_READ;
      if (readRaw == TRUE)
      {
        eepromFlag.ReadWriteRaw = TRUE;
      }
      else
      {
        eepromFlag.ReadWriteRaw = FALSE;
      }
      EEPC_StatoEEPROM = EEPROM_READ_REQUEST;
    }
  }
  else
  {
    // EEPROM is busy: return driver internal state
  }
  return EEPC_StatoEEPROM;
}

// identica alla read, cambia solo EEPROM_WRITE_REQUEST/EEPROM_READ_REQUEST e SAFETY_READ

#if  EEPROM_BUFFER_SIZE < 255U
/**
 * @brief This function writes data to eeprom.
 * @param ramStartAddress The address of the source of data (ram)
 * @param byteNumber data size to write
 * @param eepromStartAddress The address of destination data (eeprom)
 */

EEPC_StatiEEPROM EEPC_Write(void *ramStartAddress, u08 byteNumber, u16 eepromStartAddress, bool writeRaw)
#else
EEPC_StatiEEPROM EEPC_Write(void *ramStartAddress, u16 byteNumber, u16 eepromStartAddress, bool writeRaw)
#endif
{
  u16 lastDataAddress;

  if (EEPC_StatoEEPROM == EEPROM_IDLE)
  {
    if (writeRaw == TRUE)
    {
      lastDataAddress = eepromStartAddress + byteNumber;
    }
    else
    {
      lastDataAddress = eepromStartAddress + byteNumber + 1u; /* 1 byte di CRC */
    }

    if ((byteNumber == 0U) || (byteNumber > EEPROM_BUFFER_SIZE) || (lastDataAddress > EEPROM_SIZE))
    {
      EEPC_StatoEEPROM = EEPROM_BAD_PARAMETERS;
    }
    else
    {
      EepromByteCounter = byteNumber;
      EepromRecoveryCounter = EEPROM_RECOVERY_COUNTER;
      EepromAddress = eepromStartAddress;
      pEepromData = (u08 *)ramStartAddress;//tm224

      if (writeRaw == TRUE)
      {
        eepromFlag.ReadWriteRaw = TRUE;
      }
      else
      {
        eepromFlag.ReadWriteRaw = FALSE;
      }
      EEPC_StatoEEPROM = EEPROM_READ_REQUEST;

      eepromFlag.ReadType = SAFETY_READ;     // VERIFICA LA SCRITTURA TRAMITE RILETTURA DEI DATI...
      EEPC_StatoEEPROM = EEPROM_WRITE_REQUEST;
    }
  }
  return EEPC_StatoEEPROM;
}


#if  EEPROM_BUFFER_SIZE < 255U
    static __saddr u08 EepromLocationCounter;   // Number of memory locations to read/write.tm224
#else
    static __saddr u16 EepromLocationCounter;   // Number of memory locations to read/write.tm224
#endif
static __saddr u08 CRC_8;                           // CRC_8 calcolato. Deve essere inizializzato a zero ad inizio calcolo.
//#pragma dataseg = IXRAM
    static  EepromMemoryBuffer EepromBuffer;   // buffer interno al driver
    // 1) Usato per contenere i dati letti da EEPROM prima della verifica CRC e copia nella RAM utente.
    // -> serve per non modificare i dati utente nel caso di lettura dati non validi
    // 2) Usato per contenere i dati riletti dopo una scrittura.
    // -> serve per verifica della scrittura.
#pragma dataseg = default
    /**
     * @brief This function manages the SPI communication with the chip.
     * @note  It must be called to start SPI protocol and in the SPI end of transmission interrupt
     */
void EEPC_Mgm(void)
{
  u08 resMemComp;
  static u08 WriteCycleDelay;                 // Timeout on waiting for device ready (write cycle in progress).
  static u08 EepromResultTimer;               // Timer di attesa lettura risultato da parte del task che ha richiesto l'accesso:
  // allo scadere libera il task EEPROM (EEPC_StatoEEPROM = EEPROM_IDLE).

  switch (EEPC_StatoEEPROM)
  {
    case EEPROM_READ_REQUEST:

      EEPROM_CS_ON();
      ++EEPC_StatoEEPROM;//tm332 = EEPROM_READ_ADDRESS_SEND_HIGH;

      CRC_8 = 0U;
      CSI_TX_REGISTER = READ;     // transmit the READ op-code: Read Data from Memory Array
      break;

    case EEPROM_READ_ADDRESS_SEND_HIGH:

      EepromLocationCounter = EepromByteCounter;

      ++EEPC_StatoEEPROM;// = EEPROM_READ_ADDRESS_SEND_LOW;
      CSI_TX_REGISTER = (u08)(EepromAddress>>8);
      break;

    case EEPROM_READ_ADDRESS_SEND_LOW:

      ++EEPC_StatoEEPROM;// = EEPROM_READ_CLOCK_OUT;
      CSI_TX_REGISTER = (u08)EepromAddress;
      break;

    case EEPROM_READ_CLOCK_OUT: // start first 8 bit data receive

      ++EEPC_StatoEEPROM;// = EEPROM_READ;
      CSI_TX_REGISTER = 0U;     // dummy data write to make clock out: CSI interrupt must occur
      break;

    case EEPROM_READ:

      eepromGetData(CSI_RX_REGISTER);
      break;

    case EEPROM_READ_CRC:

      EepromBuffer.CRC_8 = CSI_RX_REGISTER;
      EEPROM_CS_OFF();
      ++EEPC_StatoEEPROM;// = EEPROM_READ_END;//tm171.Controlla risultato operazione ed esegue copia dei buffer (operazione lenta).

      if (CRC_8 == 0U)// debugCRC
      {
        CRC_8 = 0x55U;
      }
      //CRC_8 = EepromBuffer.CRC_8+1; // forzatura errore CRC
      //CRC_8 = EepromBuffer.CRC_8;   // per test senza CRC
      EEPC_StatoCSI = CSI_IDLE;        // libera il bus CSI
      break;

    case EEPROM_READ_END:

      EEPC_StatoCSI = CSI_IDLE;                        // libera il bus CSI
      EepromResultTimer = EEPROM_RESULT_COUNTER;  // load result ready timer at operation end

      if ((eepromFlag.ReadWriteRaw == FALSE) &&
          (CRC_8 != EepromBuffer.CRC_8))           // CRC error: read not ok. (Verifica il checksum dei dati letti).
      {
        EepromRecoveryCounter--;
        if ((EepromRecoveryCounter) == 0U)     // If retry counter is zero: signal operation error
        {
          // ReadType distingue se si tratta di lettura dati normale o rilettura per controllo di scrittura.
          if (eepromFlag.ReadType == NORMAL_READ)
          {
            // Se la lettura non va a buon fine la memoria puntata da pEepromData non viene modificata.
            EEPC_StatoEEPROM = EEPROM_READ_FAIL; // signal read error
          }
          else
          {
            EEPC_StatoEEPROM = EEPROM_WRITE_FAIL;// signal write error
          }
        }
        else
        {
          // Ripete la read fra EEPROM_CLK_TICK ms, per garantire una durata definita della fase di recovery.
          EEPC_StatoEEPROM = EEPROM_READ_REQUEST;  // Start read again after EEPROM_CLK_TICK ms
        }
      }
      else
      {
        if (eepromFlag.ReadType == NORMAL_READ)
        {
          copyEepromBuffer();
          EEPC_StatoEEPROM = EEPROM_READ_GOOD;     // segnala read good
        }
        else
        {
          // ReadType == SAFETY_READ (read back)

          // tm224
          // Il confronto fra buffer scritto e buffer riletto era necessario nella versione originaria,
          // perchè in rilettura non si calcolava il CRC.
          // Il caso di dati scritti che sono modificati prima della fine scrittura non è gestito dal driver:
          // questo controllo deve avvenire a livello di manager/applicazione.
          // Bisogna separare la richiesta di scrittura dallo stato di esecuzione.

          resMemComp = (u08)memcmp((void *)pEepromData, (void *)EepromBuffer.Data, EepromByteCounter);
          if ((eepromFlag.ReadWriteRaw == FALSE) || (resMemComp == 0U))
          {
            EEPC_StatoEEPROM = EEPROM_WRITE_GOOD;    // segnala write good
          }
          else
          {
            EEPC_StatoEEPROM = EEPROM_WRITE_FAIL;    // segnala write fail
          }
        }
        eepromFlag.ReadWriteRaw = FALSE;
      }
      break;

    case EEPROM_WRITE_REQUEST:

      EEPROM_CS_ON();
      ++EEPC_StatoEEPROM;// = EEPROM_WRITE_ENABLE;

      EepromLocationCounter = EepromByteCounter;

      CRC_8 = 0U;
      CSI_TX_REGISTER = WREN;     // transmit the WREN op-code: Set Write Enable Latch
      break;

    case EEPROM_WRITE_ENABLE:

      EEPROM_CS_OFF();                            // WREN transfer complete
      ++EEPC_StatoEEPROM;// = EEPROM_WRITE_ADDRESS_SEND_HIGH;   // inserisce un ritardo pari almeno a CS Time
      EEPROM_CS_ON();
      __no_operation();                           // inserisce un ritardo pari almeno a CS Time
      CSI_TX_REGISTER = WRITE;                    // transmit the WRITE op-code: Write Data to Memory Array
      break;

    case EEPROM_WRITE_ADDRESS_SEND_HIGH:

      ++EEPC_StatoEEPROM;// = EEPROM_WRITE_ADDRESS_SEND_LOW;
      CSI_TX_REGISTER = (u08)(EepromAddress>>8);
      break;

    case EEPROM_WRITE_ADDRESS_SEND_LOW:

      ++EEPC_StatoEEPROM;// = EEPROM_WRITE;
      CSI_TX_REGISTER = (u08)EepromAddress;
      break;

    case EEPROM_WRITE:

      CSI_TX_REGISTER = eepromSetData();
      break;

    case EEPROM_PROGRAM:

      EEPROM_CS_OFF();                            // start the internal write cycle (max duration 5 ms)
      ++EEPC_StatoEEPROM;// = EEPROM_STATUS_REQUEST;   // ogni EEPROM_CLK_TICK ms controlla se ha terminato la programmazione.
      EEPC_StatoCSI = CSI_IDLE;                        // libera il bus CSI
      WriteCycleDelay = 15U/EEPROM_CLK_TICK;      // [ms] timeout on wait for internal write cycle complete
      break;

    case EEPROM_STATUS_REQUEST:

      EEPROM_CS_ON();
      ++EEPC_StatoEEPROM;// = EEPROM_RDSR_CLOCK_OUT;   // inserisce un ritardo pari almeno a CS Time
      CSI_TX_REGISTER = RDSR;                     // transmit the RDSR op-code: Read Status Register
      break;

    case EEPROM_RDSR_CLOCK_OUT:

      ++EEPC_StatoEEPROM;// = EEPROM_STATUS_CHECK;
      CSI_TX_REGISTER = 0U;           // transmit dummy byte to have clock out
      break;

    case EEPROM_STATUS_CHECK:         // check status register

      EEPROM_CS_OFF();
      // polling dello stato di fine scrittura per misura/ottimizzazione tempi di programmazione EEPROM
      if ((CSI_RX_REGISTER & 0x01u) != 0U)// the internal write cycle is in progress
      {
        EEPC_StatoCSI = CSI_IDLE;            // libera il bus CSI
        WriteCycleDelay--;
        if ((WriteCycleDelay) == 0U)  // gestione contatore/timer per segnalare errore in scrittura
        {
          EEPC_StatoEEPROM = EEPROM_WRITE_FAIL;        // segnala write error
        }
        else
        {
          EEPC_StatoEEPROM = EEPROM_STATUS_REQUEST;    // fra EEPROM_CLK_TICK ms controlla di nuovo se ha terminato la programmazione.
        }
      }
      else
      {
        EEPROM_CS_ON();
        if ((CSI_RX_REGISTER & 0x8Au) != 0U)// errore: EEPROM protetta per problema brownout catalyst
        {
          EEPC_StatoEEPROM = EEPROM_WRITE_SR;
          CSI_TX_REGISTER = WREN;     // transmit the WREN op-code: Set Write Enable Latch
        }
        else
        {
          if (EepromLocationCounter == 0xffU)   // se abbiamo scritto il CRC (ultimo byte).tm333
          {
            if (eepromFlag.ReadWriteRaw == TRUE)
            {
#if  EEPROM_BUFFER_SIZE < 255U
              EepromAddress -= (u16)EepromByteCounter;// tm333, tm471: genera codice diverso (migliore) con U.
#else
              EepromAddress -= EepromByteCounter;
#endif
            }
            else
            {
#if  EEPROM_BUFFER_SIZE < 255U
              EepromAddress -= (u16)EepromByteCounter+1U;// tm333, tm471: genera codice diverso (migliore) con U.
#else
              EepromAddress -= EepromByteCounter+1U;
#endif
            }
            CRC_8 = 0U;
            EEPC_StatoEEPROM = EEPROM_READ_ADDRESS_SEND_HIGH;// read back just written data for error control
            CSI_TX_REGISTER = READ;     // transmit the READ op-code: Read Data from Memory Array
          }
          else
          {
            // gestione fine pagina completata: continua la scrittura nella nuova pagina
            EEPC_StatoEEPROM = EEPROM_WRITE_ENABLE;
            CSI_TX_REGISTER = WREN;     // transmit the WREN op-code: Set Write Enable Latch
          }
        }
      }
      break;

    case EEPROM_WRITE_SR:

      EEPROM_CS_OFF();            // WREN transfer complete
      ++EEPC_StatoEEPROM;// = EEPROM_WRITE_PROTECTION;
      __no_operation();
      EEPROM_CS_ON(); // Toggle CS
      __no_operation();// inserisce un ritardo pari almeno a CS Time
      CSI_TX_REGISTER = WRSR;         // transmit the WRSR op-code: Write Status Register
      break;

    case EEPROM_WRITE_PROTECTION:

      EEPC_StatoEEPROM = EEPROM_PROGRAM;   // la write dello status register richiede un tempo uguale al ciclo di write dei dati
      CSI_TX_REGISTER = 0U;           // un-protect all
      break;

    case EEPROM_READ_GOOD:
    case EEPROM_WRITE_GOOD:
    case EEPROM_READ_FAIL:
    case EEPROM_WRITE_FAIL:
    case EEPROM_BAD_PARAMETERS:
      // la chiamata con EEPC_StatoEEPROM >= EEPROM_READ_GOOD serve per gestire EepromResultTimer

      EEPC_StatoCSI = CSI_IDLE;            // libera il bus CSI
      EepromResultTimer--;
      if ((EepromResultTimer) == 0U)// result ready timeout
      {
        EEPC_StatoEEPROM = EEPROM_IDLE;
      }
      else
      {
        // Give the calling task time for EEPROM operation result reading.
      }
      break;

    default:  // errore: stato non previsto

      EEPC_StatoEEPROM = EEPROM_IDLE;
      EEPC_StatoCSI = CSI_IDLE;            // libera il bus CSI
      EEPROM_CS_OFF();
      break;
  }
}


/*
  Tempi di esecuzione:   RIFARE LE MISURE !!!

  SPI clock = 1 MHz
  Calcolo CRC8: 1,8 us
  Lettura 250 byte (dimensione massima di una singola read): 7,2ms (durata CS basso)
-> 8us per trasmissione byte + 14..21us durata interrupt: (8+16)*250
  Scrittura 250 byte (dimensione massima singola write): xxx us

Definizione dei casi di test per il driver EEPROM

                                          EepromAddress
                            0   EEPROM_PAGE_SIZE    EEPROM_PAGE_SIZE-1  EEPROM_SIZE-2
EepromByteCounter
1                                                                            ok
2
7                           ok
8                                                              ok
EEPROM_PAGE_SIZE
EEPROM_PAGE_SIZE-1
(EEPROM_PAGE_SIZE*2)                                           ok
(EEPROM_PAGE_SIZE*2)-1                                         ok
*/

#pragma optimize=no_inline
static void calculateCRC_8(u08 data)
{
  static const u08 CRC_8_Table[CRC_8_TABLE_SIZE] =
  {
      0x00U, 0x5eU, 0xbcU, 0xe2U, 0x61U, 0x3fU, 0xddU, 0x83U,
      0xc2U, 0x9cU, 0x7eU, 0x20U, 0xa3U, 0xfdU, 0x1fU, 0x41U,
      0x9dU, 0xc3U, 0x21U, 0x7fU, 0xfcU, 0xa2U, 0x40U, 0x1eU,
      0x5fU, 0x01U, 0xe3U, 0xbdU, 0x3eU, 0x60U, 0x82U, 0xdcU,
      0x23U, 0x7dU, 0x9fU, 0xc1U, 0x42U, 0x1cU, 0xfeU, 0xa0U,
      0xe1U, 0xbfU, 0x5dU, 0x03U, 0x80U, 0xdeU, 0x3cU, 0x62U,
      0xbeU, 0xe0U, 0x02U, 0x5cU, 0xdfU, 0x81U, 0x63U, 0x3dU,
      0x7cU, 0x22U, 0xc0U, 0x9eU, 0x1dU, 0x43U, 0xa1U, 0xffU,
      0x46U, 0x18U, 0xfaU, 0xa4U, 0x27U, 0x79U, 0x9bU, 0xc5U,
      0x84U, 0xdaU, 0x38U, 0x66U, 0xe5U, 0xbbU, 0x59U, 0x07U,
      0xdbU, 0x85U, 0x67U, 0x39U, 0xbaU, 0xe4U, 0x06U, 0x58U,
      0x19U, 0x47U, 0xa5U, 0xfbU, 0x78U, 0x26U, 0xc4U, 0x9aU,
      0x65U, 0x3bU, 0xd9U, 0x87U, 0x04U, 0x5aU, 0xb8U, 0xe6U,
      0xa7U, 0xf9U, 0x1bU, 0x45U, 0xc6U, 0x98U, 0x7aU, 0x24U,
      0xf8U, 0xa6U, 0x44U, 0x1aU, 0x99U, 0xc7U, 0x25U, 0x7bU,
      0x3aU, 0x64U, 0x86U, 0xd8U, 0x5bU, 0x05U, 0xe7U, 0xb9U,
      0x8cU, 0xd2U, 0x30U, 0x6eU, 0xedU, 0xb3U, 0x51U, 0x0fU,
      0x4eU, 0x10U, 0xf2U, 0xacU, 0x2fU, 0x71U, 0x93U, 0xcdU,
      0x11U, 0x4fU, 0xadU, 0xf3U, 0x70U, 0x2eU, 0xccU, 0x92U,
      0xd3U, 0x8dU, 0x6fU, 0x31U, 0xb2U, 0xecU, 0x0eU, 0x50U,
      0xafU, 0xf1U, 0x13U, 0x4dU, 0xceU, 0x90U, 0x72U, 0x2cU,
      0x6dU, 0x33U, 0xd1U, 0x8fU, 0x0cU, 0x52U, 0xb0U, 0xeeU,
      0x32U, 0x6cU, 0x8eU, 0xd0U, 0x53U, 0x0dU, 0xefU, 0xb1U,
      0xf0U, 0xaeU, 0x4cU, 0x12U, 0x91U, 0xcfU, 0x2dU, 0x73U,
      0xcaU, 0x94U, 0x76U, 0x28U, 0xabU, 0xf5U, 0x17U, 0x49U,
      0x08U, 0x56U, 0xb4U, 0xeaU, 0x69U, 0x37U, 0xd5U, 0x8bU,
      0x57U, 0x09U, 0xebU, 0xb5U, 0x36U, 0x68U, 0x8aU, 0xd4U,
      0x95U, 0xcbU, 0x29U, 0x77U, 0xf4U, 0xaaU, 0x48U, 0x16U,
      0xe9U, 0xb7U, 0x55U, 0x0bU, 0x88U, 0xd6U, 0x34U, 0x6aU,
      0x2bU, 0x75U, 0x97U, 0xc9U, 0x4aU, 0x14U, 0xf6U, 0xa8U,
      0x74U, 0x2aU, 0xc8U, 0x96U, 0x15U, 0x4bU, 0xa9U, 0xf7U,
      0xb6U, 0xe8U, 0x0aU, 0x54U, 0xd7U, 0x89U, 0x6bU, 0x35U
  };
  u08 indexCRC;

  indexCRC = data ^ CRC_8;
  CRC_8 = CRC_8_Table[indexCRC];
}


#pragma optimize=no_inline  // i registri di appoggio non servono negli altri case: evita push/pop ad ogni chiamata di EEPROM()
static void copyEepromBuffer(void)
{
#if EEPROM_BUFFER_SIZE < 255U
  u08 i = EepromByteCounter;
#else
  u16 i = EepromByteCounter;
#endif
  u08 *pDestination = pEepromData;    // memoria utente
  u08 *pSource = EepromBuffer.Data;   // buffer interno

  // Copia i dati letti dal buffer interno alla memoria utente.
  // Durata 480us (per 250 byte).
  // Durata 254us (per 146 byte).
  do
  {
    *pDestination = *pSource;
    *pDestination++;
    *pSource++;
    i--;
  }while (i != 0U);
}


#pragma optimize=no_inline
/* TODO: Attenzione: nella lettura RAW i dati vengono letti invertiti. Questo perchè
 * in fase di scrittura il driver eeprom li scrive dall'ultimo al primo.
 *
 * ES: Dati da scrivere: " 1, 2, 3, 4 "
 *
 *     Dati che verranno scritti in eeprom: " 4, 3, 2, 1, CRC"
 * */
static void eepromGetData(u08 rxData)
{
  if(eepromFlag.ReadWriteRaw == TRUE)
  {
    if ((EepromLocationCounter) == 1U)
    {
      EepromBuffer.Data[EepromByteCounter - EepromLocationCounter] = rxData;
      EEPC_StatoEEPROM += 2U;      /* EEPROM_READ_END */
      EEPROM_CS_OFF();
      EEPC_StatoCSI = CSI_IDLE;   /* libera il bus CSI */
    }
    else
    {
      EepromBuffer.Data[EepromByteCounter - EepromLocationCounter] = rxData;
      EepromLocationCounter--;
    }
  }
  else
  {
    EepromLocationCounter--;
    if ((EepromLocationCounter) == 0U)     // last data byte read
    {
      ++EEPC_StatoEEPROM;// = EEPROM_READ_CRC; // Read one more byte to retrieve the CRC.tm333
    }
    EepromBuffer.Data[EepromLocationCounter] = rxData;
    calculateCRC_8(rxData);
  }

  CSI_TX_REGISTER = 0U;       // dummy data write to make clock out
}

/* TODO: Attenzione: nella scrittura RAW la verifica di lettura è sbagliata. I dati che vengono riletti
 *       tramite la eepromGetData sono al contrario. La verifica funziona in quanto la scrittura RAW è
 *       usata solo per cancellare la eeprom, scrivendo tutti i dati a 0xFF, quindi è indifferende il verso
 *       con cui essi vengono riletti.
 *
 * ES: Dati da scrivere: " 1, 2, 3, 4 "
 *
 *     Dati che verranno scritti in eeprom: " 4, 3, 2, 1, CRC"
 * */
static u08 eepromSetData(void)
{
  u08 txData;

  EepromAddress++;
  if ((EepromAddress & EEPROM_PAGE_MASK) == 0U)  // We have page wrapped!
  {
    ++EEPC_StatoEEPROM;// = EEPROM_PROGRAM;          // scrittura byte di fine pagina
  }
  else
  {
    // Non è il byte di fine pagina: rimane in stato EEPROM_WRITE
  }

  EepromLocationCounter--;
  if ((EepromLocationCounter) == 0xffU)     // Fine scrittura dati utente: scrittura del CRC (ultimo byte)
  {
    EEPC_StatoEEPROM = EEPROM_PROGRAM;   // scrittura ultimo byte

    if (CRC_8 == 0U)// debugCRC
    {
      CRC_8 = 0x55U;
    }
    txData = CRC_8;
  }
  else
  {
    txData=pEepromData[EepromLocationCounter];

    if (eepromFlag.ReadWriteRaw == TRUE)
    {
      if(EepromLocationCounter == 0x0U)
      {
        EepromLocationCounter--; /* Salto la scrittura del CRC */
        EEPC_StatoEEPROM = EEPROM_PROGRAM;   // scrittura ultimo byte
      }
      else
      {
        ;
      }
    }
    else
    {
      calculateCRC_8(txData);
    }
  }
  return txData;
}

/**
 * @brief This function Initializes the EEPROM driver.
 * @note  It must be called only one time at the system init.
 * @see EEPROM()
 */
void EEPC_Init(void)
{
  EEPROM_CS_OFF();
  EEPROM_CS_PORT_OUT();
  EEPROM_CS_INIT();

  EEPC_StatoEEPROM = EEPROM_IDLE;
}


#endif /* end __EEPC_IS_PRESENT__ */

/*______ E N D _____ (EEPD.c) ________________________________________________*/
