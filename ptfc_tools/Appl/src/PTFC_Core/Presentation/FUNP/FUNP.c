/**
 * @file FUNP.c
 * @brief Generic function content (crc various, conversion...).
 * @author Gianpiero Lenta - Bitron S.p.A.
 * @date 24 october 2014
 * @note (C) Copyright 2014 Bitron S.p.A.
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GIL          Gianpiero Lenta           Bitron S.p.A.
| DF           Davide Foglian            Polimatica S.r.l.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date        Ver  Author  Description
| ----------  ---  ------  ----------------------------------------------------
| 22/05/2013  0.1  GIL     First DRAFT
| 24/10/2014  0.2  GIL     porting on platform CLUSTER 2
*/


/*______ I N C L U D E - F I L E S ___________________________________________*/
#include "FUNP.h"
#include "FUNP_config.h"

/* Module inhibition filter */
#ifdef __FUNP_IS_PRESENT__
/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - D A T A _____________________________________________*/

/* Following constant table is valid for CRC_CCITT                            */
/* Referenced by crcFast(), CrcResult() functions                             */
static const uint16_t crcTable[256] =
{
    0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U,
    0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
    0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U,
    0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
    0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
    0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
    0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U,
    0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,
    0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
    0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
    0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U,
    0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
    0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U,
    0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
    0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
    0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,
    0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU,
    0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
    0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU,
    0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
    0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU,
    0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
    0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU,
    0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
    0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
    0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
    0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU,
    0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
    0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U,
    0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
    0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U,
    0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
};

/*______ L O C A L - D A T A _________________________________________________*/

#define FUNP_LOW_BAT_THRES  ((u08)210u)  /* 10.5V thresold */
#define FUNP_HIGH_BAT_THRES ((u08)330u)  /* 16.5V thresold */

/*______ L O C A L - M A C R O S _____________________________________________*/

#define CRC_CCITT

#if defined(CRC_CCITT)

  //typedef uint16_t  crc;

  #define CRC_NAME          "CRC-CCITT"
  #define POLYNOMIAL          0x1021U
  #define INITIAL_REMAINDER 0xFFFFU
  #define FINAL_XOR_VALUE   0x0000U
  #define REFLECT_DAT   FALSE
  #define REFLECT_REM         FALSE
  #define CHECK_VALUE   0x29B1U

   // Derive parameters from the standard-specific parameters in crc.h.
  #define WIDTH    (8U * sizeof(uint16_t))
  #define TOPBIT   (1 << (WIDTH - 1))

  #if (REFLECT_DAT == TRUE)
    //#undef  REFLECT_DATA
    #define REFLECT_DATA(X)     ((unsigned char) reflect((X), 8))
  #else
    //#undef  REFLECT_DATA
    #define REFLECT_DATA(X)     (X)
  #endif

  #if (REFLECT_REM == TRUE)
    //#undef  REFLECT_REMAINDER
    #define REFLECT_REMAINDER(X)  ((crc) reflect((X), WIDTH))
  #else
    //#undef  REFLECT_REMAINDER
    #define REFLECT_REMAINDER(X)  (X)
  #endif
#endif

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/

/**
 * @brief This function is called once at system boot to init module
 * @return none
 * @retval none
 */
void FUNP_Init(void)
{
  /* User defined init procedure */
  FUNP_CONFIG_INIT;
}

/**
 * @brief This function Convert hex (2 byte) into BCD
 * @param num (u16 to convert) *result (output string)
 * @return void (work directly on string pointed)
 * @retval none
 */
void FUNP_ConvertU16ToString(u16 num, u08 *result)
{
  u08 i = 0u;

  while(i < 5u)
  {
   *result = (u08)(num % 10U) + 0x30u;
    num /= 10U;
    result++;
    i++;
  }
}

/**
 * @brief compute crc 16
 * @param *data(pointer to data vector from whom calculate crc), len (data vector lenght)
 * @return u16
 * @retval crc calculated
 */
u16 FUNP_crc16_little(u08 *data, u16 len) {

  u16 crc = 0u;
  u08 BitCount = 0u;
  u08 NextByte = 0u;
  u08 carry = 0u;

  while (len > 0U)
  {
    BitCount = 0u;
    NextByte = *data;
    *data++;

    while (BitCount < 8U) 
    {
      carry = ((u08)crc & 0x0001u);
      crc >>= 1;
      
      if (carry ^ (NextByte & 0x01u))
      {
        crc ^= POLY;
      }

      NextByte = (u08)(NextByte >> 1);
      BitCount++;
    }
    len--;
  }

  return crc;
}



/*********************************************************************
 *
 * Function:    crcFast()
 *
 * Description: Compute the CRC of a given message.
 *
 * Notes:   crcInit() must be called first.
 *
 * Returns:   The CRC of the message.
 *
 *********************************************************************/
/**
 * @brief compute crcFast
 * @param message[](pointer to data vector from whom calculate crc), nBytes (data vector lenght)
 * @return u16
 * @retval crc calculated
 */
u16 crcFast(u08 const message[], u16 nBytes)
{
  uint16_t rem = INITIAL_REMAINDER;
  uint8_t  data;
  uint8_t  byte;


  // Divide the message by the polynomial, a byte at a time.

  for (byte = 0U; byte < nBytes; ++byte)
  {
    data = REFLECT_DATA(message[byte]) ^ (uint8_t)(rem >> (WIDTH - 8U));
    rem = crcTable[data] ^ (uint16_t)(rem << 8);
  }

  // The final remainder is the CRC.

  return (REFLECT_REMAINDER(rem) ^ FINAL_XOR_VALUE);

}   // End of crcFast()

/******************************************************************************/
/* Name: Interval_Binary()                                                    */
/* Role:    Library routine: binary searches, into the specified table,       */
/*                           the interval                                     */
/* Interface: none                                                            */
/* Pre-condition: -                                                           */
/* Constraints: none                                                          */
/* Behavior:                                                                  */
/*           	                                                              */
/******************************************************************************/
u08 FUNP_Interval_Binary(s16 X, const FUNP_Interp_curve_point_t ITAB[], u08 num_point)
{
  u08  loIdx;
  u08  hiIdx;
  u08  idx;
  u08  ret_val;
  u08 breakLoop;

  /* Init look-up */
  ret_val = num_point;
  loIdx = 0U;
  hiIdx = num_point;
  
  breakLoop = FALSE;

  if( X <= ITAB[0u].X)
  {
      ret_val = 0u;
  }
  else if (X > ITAB[num_point-1u].X)
  {
       ret_val = num_point-1u;
  }
  else
  {
      do
      {
        idx = (u08)(((u16)((u16)hiIdx + (u16)loIdx)) >> 1);

        /* Check for matching element */
        if((X <= ITAB[idx].X ) && (X > ITAB[idx-1u].X))
        {
          /* Bingoooo :) */
          ret_val = idx;
          breakLoop = TRUE;
        }
    	
        /* Determine which half shall be taken */
        if (X < ITAB[idx].X)
        {
          /* Avoid use of signed types */
          if(idx == 0U)
          {
            breakLoop = TRUE;
          }
          hiIdx = (u08)(idx - 1U);
        }
        else
        {
          /* X 'greater' than half interval value: Use upper half of interval... */
          loIdx = (u08)(idx + 1U);
        }
        
        if (breakLoop)
        {
          break;
        }
      }
      while (loIdx <= hiIdx);
  }

  /* return the search result */
  return ret_val;
}

/******************************************************************************/
/* Name: Curve()                                                              */
/* Role:    Library routine: performs the linear interpolation                */
/*                                                                            */
/* Interface: none                                                            */
/* Pre-condition: -                                                           */
/* Constraints: none                                                          */
/* Behavior:                                                                  */
/*           	                                                              */
/******************************************************************************/
s16  FUNP_Curve(s16 X, const FUNP_Interp_curve_point_t TAB[], u08 num_point)
{
    u08  J1,J2;
    s16  retVal;
    s16  x1,x2,y1,y2;
    s32  tmpVal, deltaX, deltaY, incX;

    J1 = FUNP_Interval_Binary(X,TAB,num_point);
    J2 = J1 + 1U;

    if ((J1 == 0U) || (J2 == (num_point)))
    {// the actual X value is lower than X0 or greater than Xmax -> take Y0
      retVal = TAB[J1].Y;
    }
    else
    {
        x1 = TAB[J1].X;
        x2 = TAB[J2].X;

        y1 = TAB[J1].Y;
        y2 = TAB[J2].Y;

        retVal = y2-y1;
        deltaY = (s32)retVal;

        retVal = X-x1;
        incX = (s32)retVal;

        retVal = x2-x1;
        deltaX = (s32)retVal;

        tmpVal = (deltaY * incX)/deltaX;
        tmpVal += y1;

        retVal = (s16)tmpVal;
    }

    return retVal;
}

#endif /* end __FUNP_IS_PRESENT__ */

/*______ E N D _____ (funp.c) ________________________________________________*/
