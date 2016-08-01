/**
 * @file MEMD.c
 * @brief MEMory test Driver. This module performs ram test and stack overflow
 * underflow check.
 * @author Matteo Mastrodonato - Bitron S.p.A.
 * @date 20 October  2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */

#define MEMD_IF_OWNER

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MEMD.h"
#include "MEMD_config.h"

/* Module inhibition filter */
#ifdef __MEMD_IS_PRESENT__

/*______ P R I V A T E - M A C R O S _________________________________________*/

#if (MEMD_RAM_SEGMENT_NUM > 0U)
  #pragma segment = MEMD_RAM_SEGMENT_0
#endif
#if (MEMD_RAM_SEGMENT_NUM > 1U)
  #pragma segment = MEMD_RAM_SEGMENT_1
#endif
#if (MEMD_RAM_SEGMENT_NUM > 2U)
  #pragma segment = MEMD_RAM_SEGMENT_2
#endif
#if (MEMD_RAM_SEGMENT_NUM > 3U)
  #pragma segment = MEMD_RAM_SEGMENT_3
#endif
#if (MEMD_RAM_SEGMENT_NUM > 4U)
  #pragma segment = MEMD_RAM_SEGMENT_4
#endif
#if (MEMD_RAM_SEGMENT_NUM > 5U)
  #pragma segment = MEMD_RAM_SEGMENT_5
#endif
#if (MEMD_RAM_SEGMENT_NUM > 6U)
  #pragma segment = MEMD_RAM_SEGMENT_6
#endif
#if (MEMD_RAM_SEGMENT_NUM > 7U)
  #pragma segment = MEMD_RAM_SEGMENT_7
#endif

#define MEMD_STACK_TOP_1             0xAAAAu
#define MEMD_STACK_TOP_2             0x5555u

#define MEMD_STACK_BOTTOM_1          MEMD_STACK_TOP_1
#define MEMD_STACK_BOTTOM_2          MEMD_STACK_TOP_2

/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef struct Memd_PriveteData_s
{
  DRVD_RStatus_t RamTestResult;
  DRVD_RStatus_t FlashTestResult;
  uint8_t*       EndStackRamPtr;
}Memd_PriveteData_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

static __no_init Memd_PriveteData_t Memd_PrivateData;

#if (MEMD_STACK_CHECK_ENABLE == TRUE)
  #if (MEMD_STACK_SAFETY_AREA_SIZE < 5U)
    #error "Stack safety area must be grater or equal than 5 byte."
  #else
    // allocate STACK TOP contiguous RAM locations (defined in "filename.XCL") used for stack overflow detection (Rule 3.2)
    // l'opzione __root impedisce che il linker "ottimizzi" la variabile o la funzione non usata esplicitamente.
    // remember: stack growth direction is from high address to low address
    #pragma dataseg = STACK_TOP         // TOP of STACK segment
    static __no_init __root uint8_t  MEMD_StackTopSpareSafetyArea[MEMD_STACK_SAFETY_AREA_SIZE - 4U];
    static __no_init        uint16_t MEMD_StackTop2;     // address CSTACK-4
    static __no_init        uint16_t MEMD_StackTop1;     // address CSTACK-2
    #pragma dataseg = default

    // allocate STACK BOTTOM contiguous RAM locations (defined in "filename.XCL") used for stack underflow detection (Rule 3.2)
    #pragma dataseg = STACK_BOTTOM      // BOTTOM of STACK segment
    static __no_init        uint16_t MEMD_StackBottom1;  // address CSTACK+_CSTACK_SIZE+2
    static __no_init        uint16_t MEMD_StackBottom2;  // address CSTACK+_CSTACK_SIZE+4
    static __no_init __root uint8_t  MEMD_StackBottomSpareSafetyArea[MEMD_STACK_SAFETY_AREA_SIZE - 4U];
    #pragma dataseg = default
  #endif
#endif
/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

static DRVD_RStatus_t Memd_RamTestInternal(uint8_t* start_addr, uint8_t* end_addr, uint8_t test_val_in, uint8_t test_val_out);

/*______ E X T E R N A L - D A T A ___________________________________________*/


void MEMD_Init(void)
{

#if (MEMD_STACK_CHECK_ENABLE == TRUE)
  /* Init stack check */
  MEMD_StackTop1    = MEMD_STACK_TOP_1;
  MEMD_StackBottom1 = MEMD_STACK_BOTTOM_1;
  MEMD_StackTop2    = MEMD_STACK_TOP_2;
  MEMD_StackBottom2 = MEMD_STACK_BOTTOM_2;

  MEMD_StackTopSpareSafetyArea[0]    = 0x66U; /* Just to use and avoid warnings */
  MEMD_StackBottomSpareSafetyArea[0] = 0x33U; /* Just to use and avoid warnings */
#endif

}

void MEMD_RamTest(void)
{
  uint8_t        i;
  bool_t         RamTestEnabled;
  DRVD_RStatus_t RamTestResult;
  uint8_t*       RamSegment[MEMD_RAM_SEGMENT_NUM][2];

#if (MEMD_RAM_SEGMENT_NUM > 0U)
  RamSegment[0][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_0);
  RamSegment[0][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_0);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 1U)
  RamSegment[1][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_1);
  RamSegment[1][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_1);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 2U)
  RamSegment[2][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_2);
  RamSegment[2][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_2);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 3U)
  RamSegment[3][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_3);
  RamSegment[3][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_3);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 4U)
  RamSegment[4][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_4);
  RamSegment[4][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_4);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 5U)
  RamSegment[5][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_5);
  RamSegment[5][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_5);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 6U)
  RamSegment[6][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_6);
  RamSegment[6][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_6);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 7U)
  RamSegment[7][0] = (uint8_t*) __segment_begin(MEMD_RAM_SEGMENT_7);
  RamSegment[7][1] = (uint8_t*) __segment_end(MEMD_RAM_SEGMENT_7);
#endif
#if (MEMD_RAM_SEGMENT_NUM > 8U)
  #error "MEMD_RAM_SEGMENT_NUM invalid. Max value is 8."
#endif

  RamTestResult  = MS_OK;
  RamTestEnabled = MEMD_RAM_TEST_ENABLE;

  if (RamTestEnabled)
  {
    for(i = 0U; (i < MEMD_RAM_SEGMENT_NUM) && (RamTestResult == MS_OK); i++)
    {
      if(RamSegment[i][0] != RamSegment[i][1])
      {
        MEMD_SAFETY_ACK()
        
        /* Perform RAM TEST PATTERN. i.e.: 0xAA55 */
        if (MS_OK != Memd_RamTestInternal((uint8_t*)RamSegment[i][0], (uint8_t*)RamSegment[i][1] - 1U,
            (uint8_t)MEMD_RAM_TEST_PATTERN1,(uint8_t)MEMD_RAM_TEST_PATTERN2)) 
        {
          RamTestResult = MS_NOT_OK;
        }
        else
        {
        }
        
        MEMD_SAFETY_ACK()
        
        /* Perform RAM TEST PATTERN. i.e.: 0x55AA */
        if (MS_OK != Memd_RamTestInternal((uint8_t*)RamSegment[i][0],(uint8_t*)RamSegment[i][1] - 1U,
            (uint8_t)MEMD_RAM_TEST_PATTERN2,(uint8_t)MEMD_RAM_TEST_PATTERN1))
        {
          RamTestResult = MS_NOT_OK;
        }
        else
        {
        }
      }
    }/* for */
  }
  
  Memd_PrivateData.RamTestResult = RamTestResult; /* Performance:  3KByte -> 2,0ms */
}

#if (MEMD_STACK_CHECK_ENABLE == TRUE)
/* From SDF, rule 3.2 */
void MEMD_StackCheck(void)
{
  if ((MEMD_StackTop1 != MEMD_STACK_TOP_1) || (MEMD_StackTop2 != MEMD_STACK_TOP_2))
  {
    // stack overflow detected
    for(;;)
    {
    }
  }
  else
  {
    if ((MEMD_StackBottom1 != MEMD_STACK_BOTTOM_1) || (MEMD_StackBottom2 != MEMD_STACK_BOTTOM_2))
    {
      // stack underflow detected
      for(;;)
      {
      }
    }
    else
    {
      /* Stack OK! */
    }
  }
}
#endif

DRVD_RStatus_t MEMD_GetFlashTestResult(void)
{
  return MS_OK; /* TODO COBRA: to implement! */
}


DRVD_RStatus_t MEMD_GetRamTestResult(void)
{
  return Memd_PrivateData.RamTestResult;
}

static DRVD_RStatus_t Memd_RamTestInternal(uint8_t* start_addr, uint8_t* end_addr, uint8_t test_val_in, uint8_t test_val_out)
{
  uint16_t       local_test_val;
  uint8_t        local_test_val_in;
  uint8_t        local_test_val_out;
  DRVD_RStatus_t testResult;

  uint16_t*      start_addr_w;
  uint16_t*      end_addr_w;

  if(start_addr >= end_addr)
  {
    testResult = MS_NOT_OK;
  }
  else
  {
    testResult = MS_OK;
    /* Prepare TEST PATTERN */
    local_test_val_in  = test_val_in;
    local_test_val_out = test_val_out;
    local_test_val     = (uint16_t)local_test_val_in + (uint16_t)((uint16_t)local_test_val_out << 8U );

    /* Always start RAM Test loop with WORD (16-bit) alignment */
    if((uint16_t)(start_addr) & 0x1U)
    {
      *((volatile uint8_t*)start_addr) = local_test_val_in;

      if(*((volatile uint8_t*)start_addr) != local_test_val_in)
      {
        testResult = MS_NOT_OK;
      }
      else
      {
        (volatile uint8_t*)start_addr++;
      }
    }
    else
    {
    }

    if (testResult == MS_OK)
    {
      /* End address is BYTE (8-bit) aligned and MUST NOT be tested, so be careful... */
       if(!((uint16_t)(end_addr) & 0x1U))
      {
        *((volatile uint8_t*)end_addr) = local_test_val_out;

        if(*((volatile uint8_t*)end_addr) != local_test_val_out)
        {
          testResult = MS_NOT_OK;
        }
        else
        {
        }
      }

      if (testResult == MS_OK)
      {
        start_addr_w = (uint16_t *)(start_addr);
        end_addr_w   = (uint16_t *)(end_addr);
        
        /* Perform WORD (16-bit) aligned RAM Test */
        while (start_addr_w < end_addr_w)
        {
          *((volatile uint16_t *)start_addr_w) = local_test_val;

          if(*((volatile uint16_t *)start_addr_w) != local_test_val)
          {
            testResult = MS_NOT_OK;
            break;
          }
          else
          {
            (volatile uint16_t *)start_addr_w++;
          }
        }
      }
      else
      {
      }
    }
    else
    {
    }
  }
  return testResult;
}

MEMD_EXTERN u16 MEMD_GetStackPeakLoad(void)
{
  u16 stackFree = 0U;				// Contatore del numero di word (16 bit su 78K0R) non usate nello stack.
  u16* stackWalking = (u16*)&MEMD_StackTop1;	// Pointer used to scan di stack content. Initialize to top of stack address-2.
  u16 stackSize;                                // Dimensione dello stack in word 
  u32 stackLoadPeak;
  
  stackSize = ((uint16_t)&MEMD_StackBottom1 - (uint16_t)&MEMD_StackTop1)/2U;

  // Walk through the stack (starting from top), looking for changed values.
  ++stackWalking;
  while (*stackWalking == 0xCDCDU)// The stack is initialized at 0xCD by cstartup.
  {
    ++stackWalking;
    ++stackFree;	// Count the number of available stack words (2 byte unit on 78K0R 16 bit architecture).
  }
    
  stackLoadPeak = (((u32)stackSize - (u32)stackFree)*1000U)/((u32)stackSize);
  
  return (u16)stackLoadPeak;
}
#endif /* __MEMD_IS_PRESENT__ */
