/**
 * @file DRVD_typedefs.h
 * @author Mastrodonato Matteo
 * @date 15 giu 2013
 * @brief File containing the datatypes used by the Driver layer.
 *
 * @see www.Bitron.net
 */

#ifndef DRVD_TYPEDEFS_H_
#define DRVD_TYPEDEFS_H_

#include "global.h"

typedef enum
{
  DRVD_NOT_OK = 0,
  DRVD_OK,
  DRVD_BUSY,
  DRVD_PAR_NOT_OK
}DRVD_ResSts_t;

typedef enum
{
  MS_NOT_OK,
  MS_OK,
  MS_BUSY,
  MS_PAR_NOT_OK,
  MS_NOT_ENABLED
}DRVD_RStatus_t;

typedef enum
{
	L_LOW,
	L_HIGH
} DRVD_Level_t;

/* Utilizzo interfacce */

#define USER	0x01
#define OWNER	0x02

#define CHAN_NOT_USED 0xFF

#endif /* DRVD_TYPEDEFS_H_ */
