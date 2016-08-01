/**
 * @file DIOD.h
 * @author Mastrodonato Matteo
 * @date 11 giu 2013
 * @brief File containing the header and include chain of DIOD Driver.
 *
 * @see www.Bitron.net
 */

#ifndef __DIOD_H
#define __DIOD_H

#include "DRVD_if.h"

/* Module inhibition filter */
#ifdef __DIOD_IS_PRESENT__

#include "DIOD_config.h"

#define OUTPUT  0
#define INPUT   1

#define BIT_0_MASK  0x01U
#define BIT_1_MASK  0x02U
#define BIT_2_MASK  0x04U
#define BIT_3_MASK  0x08U
#define BIT_4_MASK  0x10U
#define BIT_5_MASK  0x20U
#define BIT_6_MASK  0x40U
#define BIT_7_MASK  0x80U

#if (DRVD_UC_PACKAGE == DRVD_48_PIN) /* uC 78F1826 - 48pin */
typedef enum DIOD_IntChannel_e
{
  PORT_00,

  PORT_10,
  PORT_11,
  PORT_12,
  PORT_13,
  PORT_14,
  PORT_15,
  PORT_16,
  PORT_17,

  PORT_30,
  PORT_31,
  PORT_32,

  PORT_40,
  PORT_41,

  PORT_60,
  PORT_61,
  PORT_62,
  PORT_63,

  PORT_70,
  PORT_71,
  PORT_72,
  PORT_73,

  PORT_80,
  PORT_81,
  PORT_82,
  PORT_83,
  PORT_84,
  PORT_85,
  PORT_86,
  PORT_87,

  PORT_90,
  PORT_91,
  PORT_92,

  PORT_120,
  PORT_121,
  PORT_122,
  PORT_123,
  PORT_124,
  PORT_125,

  PORT_130,
  PORT_140,
  PORT_HDL_MAX
}DIOD_IntChannel_t;

#endif


#if (DRVD_UC_PACKAGE == DRVD_64_PIN) /* uC 78F1833 - 64pin */
typedef enum DIOD_IntChannel_e
{
  PORT_00,

  PORT_10,
  PORT_11,
  PORT_12,
  PORT_13,
  PORT_14,
  PORT_15,
  PORT_16,
  PORT_17,

  PORT_30,
  PORT_31,
  PORT_32,

  PORT_40,
  PORT_41,
  PORT_42,
  PORT_43,

  PORT_50,
  PORT_51,
  PORT_52,
  PORT_53,

  PORT_60,
  PORT_61,
  PORT_62,
  PORT_63,

  PORT_70,
  PORT_71,
  PORT_72,
  PORT_73,
  PORT_74,
  PORT_75,
  PORT_76,
  PORT_77,

  PORT_80,
  PORT_81,
  PORT_82,
  PORT_83,
  PORT_84,
  PORT_85,
  PORT_86,
  PORT_87,

  PORT_90,
  PORT_91,
  PORT_92,
  PORT_93,
  PORT_94,
  PORT_95,
  PORT_96,

  PORT_120,
  PORT_121,
  PORT_122,
  PORT_123,
  PORT_124,
  PORT_125,

  PORT_130,

  PORT_140,
  PORT_HDL_MAX
}DIOD_IntChannel_t;

#endif

#if (DRVD_UC_PACKAGE == DRVD_80_PIN) /* uC 78F1837 - 80pin */

typedef enum DIOD_IntChannel_e
{
  PORT_00,
  PORT_01,
  PORT_02,

  PORT_10,
  PORT_11,
  PORT_12,
  PORT_13,
  PORT_14,
  PORT_15,
  PORT_16,
  PORT_17,

  PORT_30,
  PORT_31,
  PORT_32,

  PORT_40,
  PORT_41,
  PORT_42,
  PORT_43,
  PORT_44,
  PORT_45,
  PORT_46,
  PORT_47,

  PORT_50,
  PORT_51,
  PORT_52,
  PORT_53,
  PORT_54,
  PORT_55,
  PORT_56,
  PORT_57,

  PORT_60,
  PORT_61,
  PORT_62,
  PORT_63,
  PORT_64,
  PORT_65,
  PORT_66,
  PORT_67,

  PORT_70,
  PORT_71,
  PORT_72,
  PORT_73,
  PORT_74,
  PORT_75,
  PORT_76,
  PORT_77,

  PORT_80,
  PORT_81,
  PORT_82,
  PORT_83,
  PORT_84,
  PORT_85,
  PORT_86,
  PORT_87,

  PORT_90,
  PORT_91,
  PORT_92,
  PORT_93,
  PORT_94,
  PORT_95,
  PORT_96,
  PORT_97,

  PORT_120,
  PORT_121,
  PORT_122,
  PORT_123,
  PORT_124,
  PORT_125,
  PORT_126,

  PORT_130,

  PORT_140,
  PORT_HDL_MAX
}DIOD_IntChannel_t;

#endif

#if (DRVD_UC_PACKAGE == DRVD_100_PIN) /* uC 78F1837 - 80pin */

typedef enum DIOD_IntChannel_e
{
  PORT_00,
  PORT_01,
  PORT_02,
  PORT_03,

  PORT_10,
  PORT_11,
  PORT_12,
  PORT_13,
  PORT_14,
  PORT_15,
  PORT_16,
  PORT_17,

  PORT_30,
  PORT_31,
  PORT_32,

  PORT_40,
  PORT_41,
  PORT_42,
  PORT_43,
  PORT_44,
  PORT_45,
  PORT_46,
  PORT_47,

  PORT_50,
  PORT_51,
  PORT_52,
  PORT_53,
  PORT_54,
  PORT_55,
  PORT_56,
  PORT_57,

  PORT_60,
  PORT_61,
  PORT_62,
  PORT_63,
  PORT_64,
  PORT_65,
  PORT_66,
  PORT_67,

  PORT_70,
  PORT_71,
  PORT_72,
  PORT_73,
  PORT_74,
  PORT_75,
  PORT_76,
  PORT_77,

  PORT_80,
  PORT_81,
  PORT_82,
  PORT_83,
  PORT_84,
  PORT_85,
  PORT_86,
  PORT_87,

  PORT_90,
  PORT_91,
  PORT_92,
  PORT_93,
  PORT_94,
  PORT_95,
  PORT_96,
  PORT_97,

  PORT_100,
  PORT_101,
  PORT_102,
  PORT_103,
  PORT_104,
  PORT_105,
  PORT_106,
  PORT_107,

  PORT_120,
  PORT_121,
  PORT_122,
  PORT_123,
  PORT_124,
  PORT_125,
  PORT_126,
  PORT_127,

  PORT_130,

  PORT_140,

  PORT_150,
  PORT_151,
  PORT_152,
  PORT_153,
  PORT_154,
  PORT_155,
  PORT_156,
  PORT_157,

  PORT_HDL_MAX
}DIOD_IntChannel_t;

#endif

typedef struct
{
  u08 volatile *outPort;
  u08           bitMask;
}DIOD_ResourceTab_t;

#if 0
/*
typedef struct
{
  DIOD_IntChannel_t port;
  u08               direction;
}DIOD_CfgTable_t;
*/
#endif

typedef DIOD_IntChannel_t DIOD_CfgTable_t;

extern const DIOD_CfgTable_t DIOD_CfgTable[DIOD_HDL_MAX];

#endif /* end __DIOD_IS_PRESENT__ */

#endif  // __DIOD_H
