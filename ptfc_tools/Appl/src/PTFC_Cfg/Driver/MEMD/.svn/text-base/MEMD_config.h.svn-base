/*
 * MEMD_config.h
 *
 *  Created on: 10/ott/2014
 *      Author: mmastrodonato
 */

#ifndef MEMD_CONFIG_H_
#define MEMD_CONFIG_H_

/*______ I N C L U D E - F I L E S ___________________________________________*/

/*______ G L O B A L - T Y P E S _____________________________________________*/

/*______ G L O B A L - D E F I N E S _________________________________________*/

/* RAM Test configuration */
#define MEMD_RAM_TEST_ENABLE           TRUE

#define MEMD_RAM_SEGMENT_NUM           6U

#define MEMD_RAM_TEST_PATTERN1         0x55U
#define MEMD_RAM_TEST_PATTERN2         0xAAU

#define MEMD_RAM_SEGMENT_0             "ISR_CBK"
#define MEMD_RAM_SEGMENT_1             "SADDR_Z"
#define MEMD_RAM_SEGMENT_2             "NEAR_I"
#define MEMD_RAM_SEGMENT_3             "NEAR_Z"
#define MEMD_RAM_SEGMENT_4             "STACK_TOP"
#define MEMD_RAM_SEGMENT_5             "STACK_BOTTOM"
#define MEMD_RAM_SEGMENT_6
#define MEMD_RAM_SEGMENT_7

/* STACK runtime check configuration */
#define MEMD_STACK_CHECK_ENABLE         TRUE
#define MEMD_STACK_SAFETY_AREA_SIZE     20U  /* >= 8 byte */

#define MEMD_SAFETY_ACK()               LPMS_RefreshAllWatchDog()


/*______ G L O B A L - D A T A _______________________________________________*/

/*______ P R I V A T E - M A C R O S _________________________________________*/

/*______ G L O B A L - M A C R O S ___________________________________________*/

/*______ G L O B A L - F U N C T I O N S - P R O T O T Y P E S _______________*/

/*______ E X T E R N A L - D A T A ___________________________________________*/


#endif /* MEMD_CONFIG_H_ */
