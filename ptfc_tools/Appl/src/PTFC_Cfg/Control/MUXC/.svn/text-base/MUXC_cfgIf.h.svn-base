/**
 * @file MUXC_cfgIf.h
 * @author mmastrodonato
 * @date 10/set/2014
 * @brief Public interface configuration of Multiplexer management module.
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


#ifndef MUXC_CFGIF_H_
#define MUXC_CFGIF_H_



/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/**
 * This enumerative contains the ANALOG multiplexer identifier used
 * to map the Virtual analog input.
 *
 * WARNING: do not remove the last value (MUXC_AN_MUX_NUM_HDL)
 *
 */
typedef enum MUXC_AnMux_e
{
  MUXC_Analog1 = 0,
  MUXC_Analog2,
  MUXC_AN_MUX_NUM_HDL,
}MUXC_AnMux_t;


/**
 * This enumerative contains the DIGITAL multiplexer identifier used
 * to map the Virtual digital input.
 *
 * WARNING: do not remove the last value (MUXC_DGT_MUX_NUM_HDL)
 *
 */
typedef enum MUXC_DgtMux_e
{
  MUXC_Digital1 = 0,
  MUXC_DGT_MUX_NUM_HDL,
}MUXC_DgtMux_t;

/**
 * Virtual Analog channel list.
 * This enumerative have to be aligned to table MUXC_AnChanCfgTable (MUXC_config.c)
 */
typedef enum MUXC_AnChannel_e
{
  /**@{*/
  MUXC_KeyDiag     = 0 ,  /**< ANI11 - MUX ch. 0  */
  MUXC_BackrLiftKey    ,  /**< ANI11 - MUX ch. 1  */
  MUXC_SlideTiltKey    ,  /**< ANI11 - MUX ch. 2  */
  MUXC_MemKey          ,  /**< ANI11 - MUX ch. 3  */
  MUXC_7V5_Fbk         ,  /**< ANI11 - MUX ch. 5  */
  MUXC_MOT_Fbk         ,  /**< ANI11 - MUX ch. 6  */
  MUXC_HeatSteerFbk    ,  /**< ANI11 - MUX ch. 7  */
  MUXC_HeatSteerOutFbk ,  /**< ANI10 - MUX ch. 0  */
  MUXC_HeatDrvOutFbk   ,  /**< ANI10 - MUX ch. 1  */
  MUXC_HeatPassOutFbk  ,  /**< ANI10 - MUX ch. 2  */
  MUXC_NtcDrv          ,  /**< ANI10 - MUX ch. 3  */
  MUXC_NtcSteer        ,  /**< ANI10 - MUX ch. 4  */
  MUXC_NtcPass         ,  /**< ANI10 - MUX ch. 5  */
  MUXC_NtcVFbk         ,  /**< ANI10 - MUX ch. 6  */
  MUXC_HeatDrvFbk      ,  /**< ANI10 - MUX ch. 7  */
  MUXC_AN_CH_NUM_HDL
  /**@}*/
} MUXC_AnChannel_t;


/**
 * Virtual Digital channel list.
 * This enumerative have to be aligned to table MUXC_DgtChanCfgTable (MUXC_config.c)
 */
typedef enum MUXC_DgtChannel_e
{
  MUXC_TiltUpFbk     = 0 ,  /**< P96 - MUX ch. 0  */
  MUXC_SlideFdFbk        ,  /**< P96 - MUX ch. 1  */
  MUXC_TiltSlideComFdFbk ,  /**< P96 - MUX ch. 2  */
  MUXC_LiftUpFbk         ,  /**< P96 - MUX ch. 3  */
  MUXC_BackrFdFbk        ,  /**< P96 - MUX ch. 4  */
  MUXC_LiftBackrComFbk   ,  /**< P96 - MUX ch. 5  */
  MUXC_SpareDwFbk        ,  /**< P96 - MUX ch. 6  */
  MUXC_SpareComFbk       ,  /**< P96 - MUX ch. 7  */
  MUXC_DGT_CH_NUM_HDL
} MUXC_DgtChannel_t;


/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MUXC_CFGIF_H_ */
