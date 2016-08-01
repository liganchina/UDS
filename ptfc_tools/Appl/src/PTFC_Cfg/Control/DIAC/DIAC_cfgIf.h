/**
 * @file DIAC_cfgIf.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of DIAC Driver.
 *  In particular contains the object idx (es: enumerator) of DIAC,
 *  extern of user defined function or variables.
 *
 * @see www.Bitron.net
 */

#ifndef DIAC_CFGIF_H_
#define DIAC_CFGIF_H_


/*______ I N C L U D E - F I L E S ___________________________________________*/

#ifdef DIAC_CFG_IF_OWNER
  #define DIAC_CFG_IF_EXTERN
#else
  #define DIAC_CFG_IF_EXTERN   extern
#endif


/*______ G L O B A L - T Y P E S _____________________________________________*/

typedef enum DIAC_Vref_e
{
  DIAC_KeyRef = 0,
  DIAC_VREF_MAX
}DIAC_Vref_t;

typedef enum DIAC_Thresholds_e
{
  DIAC_0Key0    = 0,
  DIAC_0Key16     ,
  DIAC_0Key30     ,
  DIAC_0Key47     ,
  DIAC_0Key61     ,
  DIAC_0Key77     ,
  DIAC_0Key84     ,
  DIAC_0Key90     ,
  DIAC_0Key98     ,
  DIAC_KB_5V00    ,
  DIAC_FHall_9V5  ,
  DIAC_FHall_5V5  ,
  DIAC_RProt_5V5  ,
  DIAC_RProt_2V5  ,
  DIAC_THRES_MAX
}DIAC_Thresholds_t;

typedef enum DIAC_Channel_e
{
  DIAC_Mem1  = 0 ,  /*  0 */
  DIAC_Mem2      ,  /*  1 */
  DIAC_Mem3      ,  /*  2 */
  DIAC_Back_BW   ,  /*  3 */
  DIAC_Back_FW   ,  /*  4 */
  DIAC_Tilt_UP   ,  /*  5 */
  DIAC_Tilt_DW   ,  /*  6 */
  DIAC_Slide_FW  ,  /*  7 */
  DIAC_Slide_BW  ,  /*  8 */
  DIAC_Lift_DW   ,  /*  9 */
  DIAC_Lift_UP   ,  /* 10 */
  DIAC_Fbk7V5    ,  /* 11 */
  DIAC_SlideTilt_OPEN,/* 12 */
  DIAC_BackrLift_OPEN,/* 13 */
  DIAC_Mem_OPEN      ,/* 14 */
  DIAC_FbkProtRel,  /* 15 */
  DIAC_HDL_MAX
}DIAC_Channel_t;

/*______ G L O B A L - D E F I N E S _________________________________________*/

/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

DIAC_CFG_IF_EXTERN CTRL_Fault_t DIAC_GetButtonDiag(DIAC_Channel_t chan);
DIAC_CFG_IF_EXTERN CTRL_Fault_t DIAC_GetBtnTiltSlideDiag(DIAC_Channel_t chan);
DIAC_CFG_IF_EXTERN CTRL_Fault_t DIAC_GetBtnLiftBackDiag(DIAC_Channel_t chan);
DIAC_CFG_IF_EXTERN CTRL_Fault_t DIAC_GetBtnSSDiag(DIAC_Channel_t chan);
DIAC_CFG_IF_EXTERN CTRL_Fault_t DIAC_GetBtnMemDiag(DIAC_Channel_t chan);


/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* DIAC_CFGIF_H_ */
