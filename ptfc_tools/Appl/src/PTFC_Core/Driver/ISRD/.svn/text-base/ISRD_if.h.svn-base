/**
 * @file ISRD_if.h
 * @brief Interrupt Service Routine Driver: public interface of ISR module 
 * for driver layer.
 * @n The main module features/services are:
 * @li Mapping of all uC physical interrupts
 * @li ISR callback vector (RAM area dedicated)
 * @li API to set any function as ISR callback for a specific interrupt
 * @li RAM protection for re-addressing from physical ISR to ISR callback
 * </ul>
 *
 * @version 1.1
 * @author Carmine Celozzi (Akhela S.r.l.)
 * @date 14 july 2014
 * @note (C) Copyright 2014 Bitron S.p.A. @link www.Bitron.net
 */
/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| CC           Carmine Celozzi           Akhela S.r.l
| MM           Matteo Mastrodonato       Bitron S.p.A.
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 14/07/14   0.1  CC      First draft not tested for RL78 - R5F10AGFLFB/F13
|-----------------------------------------------------------------------------
| 12/09/14   0.2  CC      Porting to 78K0R family - uC 78F1837_80
|-----------------------------------------------------------------------------
| 20/09/14   1.0  CC      First official release
|-----------------------------------------------------------------------------
| 17/11/14   1.1  CC      Porting to 78K0R family
|-----------------------------------------------------------------------------
*/

#ifndef __ISRD_IF_H
#define __ISRD_IF_H

/*_____ I N C L U D E - F I L E S ____________________________________________*/

/*_____ G L O B A L - D E F I N E ____________________________________________*/

#ifndef GLOBAL_ISRD
  #define GLOBAL_ISRD extern
#endif


/*_____ G L O B A L - T Y P E S ______________________________________________*/

/**
 * Enumerative type cointaining the interrupt vector indexes.
 * More indexes can be associated to one interrupt vector and 
 * only one at time can be used.
 */
typedef enum ISRD_VectorIdx_e
{
  /* ---------------------- | ------------------ | ------------ */
  /* Interrupt index        |  Interrupt vector  | Int. address */
  /* ---------------------- | ------------------ | ------------ */
  /**@{*/
  ISRD_VECTOR_INTWDTI = 0,  /**< INTWDTI_vect    - addr: (0x04) */
  ISRD_VECTOR_INTLVI,       /**< INTLVI_vect     - addr: (0x06) */
  ISRD_VECTOR_INTP0,        /**< INTP0_vect      - addr: (0x08) */
  ISRD_VECTOR_INTP1,        /**< INTP1_vect      - addr: (0x0A) */
  ISRD_VECTOR_INTP2,        /**< INTP2_vect      - addr: (0x0C) */
  ISRD_VECTOR_INTP3,        /**< INTP3_vect      - addr: (0x0E) */
  ISRD_VECTOR_INTP4,        /**< INTP4_vect      - addr: (0x10) */
  ISRD_VECTOR_INTP5,        /**< INTP5_vect      - addr: (0x12) */
  ISRD_VECTOR_INTCLM,       /**< INTCLM_vect     - addr: (0x14) */
  ISRD_VECTOR_INTCSI00,     /**< INTCSI00_vect   - addr: (0x16) */
  ISRD_VECTOR_INTCSI01,     /**< INTCSI01_vect   - addr: (0x18) */
  ISRD_VECTOR_INTDMA0,      /**< INTDMA0_vect    - addr: (0x1A) */
  ISRD_VECTOR_INTDMA1,      /**< INTDMA1_vect    - addr: (0x1C) */
  ISRD_VECTOR_INTWUTM,      /**< INTWUTM_vect    - addr: (0x1E) */
  ISRD_VECTOR_INTFL,        /**< INTFL_vect      - addr: (0x20) */
  ISRD_VECTOR_INTLT0,       /**< INTLT0_vect     - addr: (0x22) */
  ISRD_VECTOR_INTLR0,       /**< INTLR0_vect     - addr: (0x24) */
  ISRD_VECTOR_INTLS0,       /**< INTLS0_vect     - addr: (0x26) */
  ISRD_VECTOR_INTPLR0,      /**< INTPLR0_vect    - addr: (0x28) */
  ISRD_VECTOR_INTP8,        /**< INTP8_vect      - addr: (0x2A) */
  ISRD_VECTOR_INTTM00,      /**< INTTM00_vect    - addr: (0x2C) */
  ISRD_VECTOR_INTTM01,      /**< INTTM01_vect    - addr: (0x2E) */
  ISRD_VECTOR_INTTM02,      /**< INTTM02_vect    - addr: (0x30) */
  ISRD_VECTOR_INTTM03,      /**< INTTM03_vect    - addr: (0x32) */
  ISRD_VECTOR_INTAD,        /**< INTAD_vect      - addr: (0x34) */
  ISRD_VECTOR_INTLT1,       /**< INTLT1_vect     - addr: (0x36) */
  ISRD_VECTOR_INTLR1,       /**< INTLR1_vect     - addr: (0x38) */
  ISRD_VECTOR_INTLS1,       /**< INTLS1_vect     - addr: (0x3A) */
  ISRD_VECTOR_INTPLR1,      /**< INTPLR1_vect    - addr: (0x3C) */
  ISRD_VECTOR_INTCSI10,     /**< INTCSI10_vect   - addr: (0x3E) */
  ISRD_VECTOR_INTCSI11,     /**< INTCSI11_vect   - addr: (0x40) */ 
  ISRD_VECTOR_INTIIC11,     /**< INTIIC11_vect   - addr: (0x40) */
  ISRD_VECTOR_INTTM04,      /**< INTTM04_vect    - addr: (0x42) */
  ISRD_VECTOR_INTTM05,      /**< INTTM05_vect    - addr: (0x44) */
  ISRD_VECTOR_INTTM06,      /**< INTTM06_vect    - addr: (0x46) */
  ISRD_VECTOR_INTTM07,      /**< INTTM07_vect    - addr: (0x48) */
  ISRD_VECTOR_INTKR,        /**< INTKR_vect      - addr: (0x4A) */
  ISRD_VECTOR_INTP6,        /**< INTP6_vect      - addr: (0x4A) */
  ISRD_VECTOR_INTP7,        /**< INTP7_vect      - addr: (0x4C) */
  ISRD_VECTOR_INTC0ERR,     /**< INTC0ERR_vect   - addr: (0x4E) */
  ISRD_VECTOR_INTC0WUP,     /**< INTC0WUP_vect   - addr: (0x50) */
  ISRD_VECTOR_INTC0REC,     /**< INTC0REC_vect   - addr: (0x52) */
  ISRD_VECTOR_INTC0TRX,     /**< INTC0TRX_vect   - addr: (0x54) */
  ISRD_VECTOR_INTTM10,      /**< INTTM10_vect    - addr: (0x56) */
  ISRD_VECTOR_INTTM11,      /**< INTTM11_vect    - addr: (0x58) */
  ISRD_VECTOR_INTTM12,      /**< INTTM12_vect    - addr: (0x5A) */
  ISRD_VECTOR_INTTM13,      /**< INTTM13_vect    - addr: (0x5C) */
  ISRD_VECTOR_INTMD,        /**< INTMD_vect      - addr: (0x5E) */
  ISRD_VECTOR_INTIIC20,     /**< INTIIC20_vect   - addr: (0x60) */
  ISRD_VECTOR_INTST2,       /**< INTST2_vect     - addr: (0x60) */
  ISRD_VECTOR_INTSR2,       /**< INTSR2_vect     - addr: (0x62) */
  ISRD_VECTOR_INTPR2,       /**< INTPR2_vect     - addr: (0x64) */
  ISRD_VECTOR_INTTM14,      /**< INTTM14_vect    - addr: (0x66) */
  ISRD_VECTOR_INTTM15,      /**< INTTM15_vect    - addr: (0x68) */
  ISRD_VECTOR_INTTM16,      /**< INTTM16_vect    - addr: (0x6A) */
  ISRD_VECTOR_INTTM17,      /**< INTTM17_vect    - addr: (0x6C) */
  ISRD_VECTOR_INTTM20,      /**< INTTM20_vect    - addr: (0x6E) */
  ISRD_VECTOR_INTTM21,      /**< INTTM21_vect    - addr: (0x70) */
  ISRD_VECTOR_INTTM22,      /**< INTTM22_vect    - addr: (0x72) */
  ISRD_VECTOR_INTTM23,      /**< INTTM23_vect    - addr: (0x74) */
  ISRD_VECTOR_INTTM25,      /**< INTTM25_vect    - addr: (0x76) */
  ISRD_VECTOR_INTTM27,      /**< INTTM27_vect    - addr: (0x78) */
  ISRD_VECTOR_INTDMA2,      /**< INTDMA2_vect    - addr: (0x7A) */
  ISRD_VECTOR_INTDMA3,      /**< INTDMA3_vect    - addr: (0x7C) */
  ISRD_VECTOR_BRK_I,        /**< BRK_I_vect      - addr: (0x7E) */
  ISRD_VECTOR_NMB           /**< Interrupt vectors number       */
  /**@}*/
}ISRD_VectorIdx_t;

/**
 * Type of function-pointer for ISR callback. The callback routine
 * return an unsigned 16 bit value used for check the routine consistence.
 */
typedef uint16_t(*ISRD_EvtCbk_t)(void);


/*_____ G L O B A L - D A T A ________________________________________________*/

/*_____ G L O B A L - M A C R O S ____________________________________________*/

/**
 * @brief Compute with a simple alghoritm a key from an index (seed) passed by 
 * input parameter. This key will be returned.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] VectIdx: Index for all interrupt vectors present in the micro.
 *             The indexes are described by enumerative type ISRD_VectorIdx_t.
 *             For this routine the index is the seed for compute the final key.
 *
 * @return uint16_t
 * @retval Key value computed from VectIdx.
 */
#define ISRD_ComputeCbkCheck(VectIdx)         (((VectIdx) + 1u) << 4u)


/*_____ G L O B A L - F U N C T I O N S - P R O T O T Y P E S ________________*/

/**
 * @brief Initialization routine for Interrupt Service Routine module
 * of the driver layer.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] None
 * @param [out] None
 *
 * @return None
 */
GLOBAL_ISRD void ISRD_Init(void);

/**
 * @brief This routine store, for a specific index linked to a specific interrupt,
 * the ISR callback in a lookup table. If in the position selected yet exist a 
 * callback the routine will notify the error.
 * @author Carmine Celozzi - Akhela S.r.l.
 * @param [in] VectorIdx: Index for all interrupt vectors present in the micro.
 *             The indexes are described by enumerative type ISRD_VectorIdx_t.
 * @param [in] Cbk: Callback address to set for a specific interrupt. This
 *             parameter is a function-pointer of type ISRD_EvtCbk_t.
 * @param [out] None
 * @return bool_t
 * @retval FALSE The ISR callback storage is failed.
 * @retval TRUE The ISR callback storage is OK.
 */
GLOBAL_ISRD bool_t ISRD_SetEvtCbk(ISRD_VectorIdx_t VectorIdx, ISRD_EvtCbk_t Cbk);


#endif /* end __ISRD_IF_H */

/*_____ E N D _____ (ISRD_if.h) ______________________________________________*/
