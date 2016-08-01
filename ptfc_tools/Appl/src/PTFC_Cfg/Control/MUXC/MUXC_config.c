/**
 * @file MUXC_config.c
 * @author mmastrodonato
 * @date 10/set/2014
 * @brief Configuration of Multiplexer management module.
 *
 * @see www.Bitron.net
 */

/*
 *-------------------------------------------------------------------------------
 *                 A U T H O R   I D E N T I T Y
 *-------------------------------------------------------------------------------
 * Initials       Name                      Company
 * ----------     ---------------------     -------------------------------------
 * MM             mmastrodonato             Bitron S.p.A.
 *-------------------------------------------------------------------------------
 *                R E V I S I O N   H I S T O R Y
 *-------------------------------------------------------------------------------
 * Date           Ver  Author  Description
 * ------------   ---  ------  ---------------------------------------------------
 * 10/set/2014    0.1  MM      First revision
 */

/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "MUXC.h"
#include "MUXC_config.h"

/* Module inhibition filter */
#ifdef __MUXC_IS_PRESENT__

/*______ L O C A L - T Y P E S _______________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

#if (MUXC_ANALOG_EN == TRUE)
/***********************************************/
/**         ANALOG MUX CONFIGURATION          **/
/***********************************************/

/**
 * ANALOG MUX Physical channel mapping.
 * Map the Physical AD channel on the multiplexer output pin.
 * Each line corresponds to values defined in the enumerative MUXC_AnMux_t (MUXC_config.h)
 *
 */
const ADCD_InputChn_t MUXC_AnMuxArray[MUXC_AN_MUX_NUM_HDL] = {
/* MUX               ADCD_Channel  */
/* MUXC_Analog1 */   ADCD_IN_CHN_11,
/* MUXC_Analog2 */   ADCD_IN_CHN_10,
};

/**
 * ANALOG MUX Virtual channel mapping.
 * Map the Virtual Analog Input channels on the multiplexer input pins.
 * Each line corresponds to valued defines in the enumerative MUXC_AnChannel_t (MUXC_cfgIf.h)
 *
 */
const MUXC_AnCfgTable_t MUXC_AnChanCfgTable[MUXC_AN_CH_NUM_HDL] = {
/*  HANDLE                    MUX_HDL          MUX_CHANNEL   */
/* MUXC_KeyDiag         */  { MUXC_Analog1,        0U        },  /**< ANI11 - MUX ch. 0  */
/* MUXC_BackrLiftKey    */  { MUXC_Analog1,        1U        },  /**< ANI11 - MUX ch. 1  */
/* MUXC_SlideTiltKey    */  { MUXC_Analog1,        2U        },  /**< ANI11 - MUX ch. 2  */
/* MUXC_MemKey          */  { MUXC_Analog1,        3U        },  /**< ANI11 - MUX ch. 3  */
/* MUXC_7V5_Fbk         */  { MUXC_Analog1,        5U        },  /**< ANI11 - MUX ch. 5  */
/* MUXC_MOT_Fbk         */  { MUXC_Analog1,        6U        },  /**< ANI11 - MUX ch. 6  */
/* MUXC_HeatSteerFbk    */  { MUXC_Analog1,        7U        },  /**< ANI11 - MUX ch. 7  */
/* MUXC_HeatSteerOutFbk */  { MUXC_Analog2,        0u        },  /**< ANI10 - MUX ch. 0  */
/* MUXC_HeatDrvOutFbk   */  { MUXC_Analog2,        1u        },  /**< ANI10 - MUX ch. 1  */
/* MUXC_HeatPassOutFbk  */  { MUXC_Analog2,        2u        },  /**< ANI10 - MUX ch. 2  */
/* MUXC_NtcDrv          */  { MUXC_Analog2,        3u        },  /**< ANI10 - MUX ch. 3  */
/* MUXC_NtcSteer        */  { MUXC_Analog2,        4u        },  /**< ANI10 - MUX ch. 4  */
/* MUXC_NtcPass         */  { MUXC_Analog2,        5u        },  /**< ANI10 - MUX ch. 5  */
/* MUXC_NtcVFbk         */  { MUXC_Analog2,        6u        },  /**< ANI10 - MUX ch. 6  */
/* MUXC_HeatDrvFbk      */  { MUXC_Analog2,        7u        },  /**< ANI10 - MUX ch. 7  */
};
#endif


#if (MUXC_DIGITAL_EN == TRUE)
/********************************************************/
/**         DIGITAL MULTIPLEXER CONFIGURATION          **/
/********************************************************/

/**
 * DIGITAL MUX Physical channel mapping.
 * Map the Physical Digital Input channel on the multiplexer output pin.
 * Each line corresponds to valued defines in the enumerative MUXC_DgtMux_t (MUXC_config.h)
 *
 */
const DIOD_Channel_t MUXC_DgtMuxArray[MUXC_DGT_MUX_NUM_HDL] = {
/* MUX               DIOD_Channel  */
/* MUXC_Digital1 */  DIOD_MuxFkbRel1,
};

/**
 * DIGITAL MUX Virtual channel mapping.
 * Map the Virtual Digital Input channels on the multiplexer input pins.
 * Each line corresponds to valued defines in the enumerative MUXC_DgtChannel_t (MUXC_cfgIf.h)
 *
 */
const MUXC_DgtCfgTable_t MUXC_DgtChanCfgTable[MUXC_DGT_CH_NUM_HDL] = {
/*   HANDLE                   MUXC_NUM          MUXC_CHAN   */
/*  MUXC_TiltUpFbk         */ { MUXC_Digital1,       0U       },
/*  MUXC_SlideFdFbk        */ { MUXC_Digital1,       1U       },
/*  MUXC_TiltSlideComFdFbk */ { MUXC_Digital1,       2U       },
/*  MUXC_LiftUpFbk         */ { MUXC_Digital1,       3U       },
/*  MUXC_BackrFdFbk        */ { MUXC_Digital1,       4U       },
/*  MUXC_LiftBackrComFbk   */ { MUXC_Digital1,       5U       },
/*  MUXC_SpareDwFbk        */ { MUXC_Digital1,       6U       },
/*  MUXC_SpareComFbk       */ { MUXC_Digital1,       7U       },
};
#endif
/*______ P R I V A T E - D A T A _____________________________________________*/

/*______ L O C A L - D A T A _________________________________________________*/

/*______ L O C A L - M A C R O S _____________________________________________*/

/*______ I M P O R T - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ L O C A L - F U N C T I O N S - P R O T O T Y P E S _________________*/

/*______ G L O B A L - F U N C T I O N S _____________________________________*/


#endif /* end __MUXC_IS_PRESENT__ */
