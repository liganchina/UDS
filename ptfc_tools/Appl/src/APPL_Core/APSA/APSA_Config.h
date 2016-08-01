/*|-----------------------------------------------------------------------------
*|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GV           Giovanni Vaccaro          EMA s.r.l.
|-----------------------------------------------------------------------------
*/

#ifndef APSA_CONFIG_H
#define APSA_CONFIG_H
/*----------------------------------------------------------------------------*\
 DEFINES 
\*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
#define MAX_NUM_ELEMENT 100

#define DELTA_PEACK 80

#define INRUSH_TIME        15 /*150ms*/

#define ADAPTATION_TIME    10 /*100ms*/

#define PEAK_FILTER_TIME   40 /*400ms*/

#define VBATT_DROP 20

#define DROP_DELAY 30 /*300ms*/


/*Input: Check_Antipinch && Write _Map*/

#define APSA_NOT_ACTIVE    0
#define APSA_ACTIVE        1

#define APSA_FALSE   0
#define APSA_TRUE    1


/*Input: Cmd_Motor*/
#define  APSA_CMD_STOP      0
#define  APSA_CMD_FORWARD   1
#define  APSA_CMD_BACKWARD  2

/*MIN CURRENT THRESHOLD*/

#define MIN_CURRENT_THRESHOLD 5
#define MAX_CNT_MIN_CURRENT_THRESHOLD 5

/*After this time ANTIPICNH RECOVERY MUST START*/

#define T_ANTIPINCH 5

#define SIZE_FILTER 8

#define APSA_HIGHSPEED_LIMIT 36
        
#define COUNT_BIT_ZERO 0
#define COUNT_BIT_ONE  	1
#define COUNT_BIT_TWO  (1<<1u)
#define COUNT_BIT_THREE (COUNT_BIT_ONE|COUNT_BIT_TWO)

/*For F151M the value should be L_SHIFT_ADAPTATION 0  and DIV_ADAPTATION 1*/
/*For 952 the value should be L_SHIFT_ADAPTATION 1  and DIV_ADAPTATION 3*/
//#define L_SHIFT_ADAPTATION (1U)
//#define DIV_ADAPTATION (3U)
#define L_SHIFT_ADAPTATION (0U)
#define DIV_ADAPTATION (1U)
			
#endif 
/*----------------------------------------------------------------------------*\
  END OF FILE
\*----------------------------------------------------------------------------*/
