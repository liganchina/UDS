/**
 * @file DIOD_config.c
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the user configuration of DIOD Driver.
 *
 * @see www.Bitron.net
 */


/*______ I N C L U D E - F I L E S ___________________________________________*/

#include "DIOD.h"

/* Module inhibition filter */
#ifdef __DIOD_IS_PRESENT__

/*______ G L O B A L - D A T A _______________________________________________*/

const DIOD_CfgTable_t DIOD_CfgTable[DIOD_HDL_MAX] =
{
  /**@{*/
  /* Output Channels      */
  /* DIOD_CmdLiftUp       */  PORT_00 , /**< P00  */
  /* DIOD_MuxSa           */  PORT_12 , /**< P12  */
  /* DIOD_MuxSb           */  PORT_13 , /**< P13  */
  /* DIOD_MuxSc           */  PORT_14 , /**< P14  */
  /* DIOD_ExtWatchDog     */  PORT_30 , /**< P30  */
  /* DIOD_CmdHeatDrv      */  PORT_31 , /**< P31  */
  /* DIOD_CmdFanPass      */  PORT_32 , /**< P32  */
  /* DIOD_KeyEN           */  PORT_42 , /**< P42  */
  /* DIOD_5V_En           */  PORT_43 , /**< P43  */
  /* DIOD_CAN_En          */  PORT_50 , /**< P50  */
  /* DIOD_CmdHeatSteer    */  PORT_51 , /**< P51  */
  /* DIOD_CAN_Stb         */  PORT_52 , /**< P52  */
  /* DIOD_CmdHeatPass     */  PORT_53 , /**< P53  */
  /* DIOD_7V5_En          */  PORT_60 , /**< P60  */
  /* DIOD_SpareMotCom     */  PORT_61 , /**< P61  */
  /* DIOD_SpareMotDw      */  PORT_62 , /**< P62  */
  /* DIOD_CmdFanPass      */  PORT_70 , /**< P70  */
  /* DIOD_SteerHeat(L.B.) */  PORT_71 , /**< P70  */
  /* DIOD_CmdRelProtEN    */  PORT_74 , /**< P74  */
  /* DIOD_CmdTiltSlideCom */  PORT_75 , /**< P75  */
  /* DIOD_CmdSlideFd      */  PORT_76 , /**< P76  */
  /* DIOD_CmdTiltUp       */  PORT_77 , /**< P77  */
  /* DIOD_MuxFkbRel1      */  PORT_96 , /**< P96  */
  /* DIOD_LIN_SLP         */  PORT_125, /**< P125 */
  /* DIOD_CmdLiftBackrCom */  PORT_130, /**< P130 */
  /* DIOD_CmdBackrFd      */  PORT_140, /**< P140 */

  /* Input Channels       */
  /* DIOD_CAN_Ner         */  PORT_123, /**< P123 */
  /* DIOD_SteerHeatSw     */  PORT_124, /**< P124 */
  /**@}*/
};

#endif /* end __DIOD_IS_PRESENT__ */

/*______ E N D _____ (DIOD_config.c) _________________________________________*/

