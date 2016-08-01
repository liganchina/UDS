/*
|-----------------------------------------------------------------------------
|               A U T H O R   I D E N T I T Y
|-----------------------------------------------------------------------------
| Initials     Name                      Company
| --------     ---------------------     -------------------------------------
| GC           Gianpaolo Cacciavillani   Bitron
|-----------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-----------------------------------------------------------------------------
| Date       Ver  Author  Description
| ---------  ---  ------  ----------------------------------------------------
| 28/07/15   0.1  GC      First release
|-----------------------------------------------------------------------------
| 15/07/15   0.2  GC      Second release
|-----------------------------------------------------------------------------
*/

#ifndef MOTA_CONFIG_H
#define MOTA_CONFIG_H
/*----------------------------------------------------------------------------*\
 DEFINES
\*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

#define MOTA_CLOSED                    0U
#define MOTA_OPEN                      1U
 
#define MOTA_NOTVALID                  0U
#define MOTA_VALID                     1U
        
#define MOTA_OFF                       0U
#define MOTA_ON                        1U

#define MOTA_KEY_OFF                   0U
#define MOTA_KEY_ON                    1U
#define MOTA_KEY_CRANK                 2U

#define MOTA_OUT_RANGE                 0U
#define MOTA_NOMINAL_RANGE             1U 

#define MOTA_CMD_STOP                  0U
#define MOTA_CMD_FORWARD               1U
#define MOTA_CMD_BACKWARD              2U


/*StatusMotor_<NomeMotore>*/
#define MOTA_STS_STOP                  0U
#define MOTA_STS_FORWARD               1U
#define MOTA_STS_BACKWARD              2U
#define MOTA_STS_FAIL                  3U
#define MOTA_STS_MECH_STROKE_FORWARD   4U
#define MOTA_STS_MECH_STROKE_BACKWARD  5U


/*Init_From_Diag */
#define MOTA_NOT_REQUEST            0U
#define MOTA_REQUEST                1U
 
 /*Antipanic*/
#define MOTA_ABSENT                 0U
#define MOTA_PRESENT                1U

#define MOTA_DISABLE                0U
#define MOTA_ENABLE                 1U

#define MOTA_NOT_PUSHED             0U
#define MOTA_PUSHED                 1U

#define MOTA_NO_MEMORY              0U
#define MOTA_MEMORY_1               1U
#define MOTA_MEMORY_2               2U
#define MOTA_MEMORY_3               3U

#define MOTA_FALSE                  0U
#define MOTA_TRUE                   1U

#define MOTA_NOT_INIT               0U
#define MOTA_INIT                   1U
#define MOTA_IN_PROGRESS            2U

/* MDEN - Issue redmine #3833. Added MOTA_ACTIVE define */
#define MOTA_ACTIVE                 1U
#define MOTA_NOT_ACTIVE             0U

#define MOTA_RECALL_IN_PROGRESS     1U
#define MOTA_SUCCESS                2U
#define MOTA_NOT_SUCCESS            3U 
       
#define MOTA_NOT_COMPLETED          0U
#define MOTA_COMPLETED              1U 

#define MOTA_EEG_NOT_POSITION       0U
#define MOTA_EEG_POSITION           1U
#define MOTA_EEG_POSITION_COMPLETED 2U

/*Movement_Enable*/
#define MOTA_RUN                        0U
#define MOTA_SUSPEND                    1U
#define MOTA_ABORT                      2U

#define MOTA_NO_STROKE                  0U
#define MOTA_STROKE_FWD                 1U
#define MOTA_STROKE_BWD                 2U

#define MOTA_SET_NONE                   0U
#define MOTA_SET_ZERO                   1U
#define MOTA_SET_STROKE                 2U

#define MOTA_RECOVERY_NOT_IN_PROGRESS   0U
#define MOTA_RECOVERY_IN_PROGRESS       1U

#define MOTA_EEG_GO_FWD 1u
#define MOTA_EEG_IDLE   0u
#define MOTA_EEG_GO_BWD 2u


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*%%%%%%%%%%%%%%%%%    Configuration parameters    %%%%%%%%%%%%%%%%%%%%%%%%%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* MOTA module Shedule Time [ms]*/
#define MOTA_TIME_STEP 10

/*Number of stroke allowed before invalidate the init*/
#define MOTA_MAX_ERROR_STROKE 3

/*Number of seat motors*/
#define MOTA_NUM_MOTORS 4U

/*Number of memory used to memo recall*/
#define MOTA_NUM_MEMO 3U

/*time used to delay from the starts from two motors*/
#define MOTA_DELAY 100

/* time used to delay the start APSA recovery movement */
#define MOTA_APSA_DELAY 10

/*Max number of motors that can be start together  */
#define MOTA_MAX_MOTORS 3

/* Tolerance in hall used on Pillar check to start the EEG movement */
#define MOTA_PILLAR_TOL  30

/*Tolerance in hall used in automatic recall*/
#define MOTA_TOL 5

/*Difference between mechanical stroke and electric stroke*/
#define MOTA_ELECTRIC_TOL 10

/*Max time to terminate the manual procedure for start the Initialization*/
#define MOTA_MAX_INIT_PHASE 500


#define MOTA_REPULSION    168

#define SWING_DELAY 100 /*100ms*/


/*Index of the memory array*/
#define MOTA_INDEX_SLIDE 0
#define MOTA_INDEX_TILT 1
#define MOTA_INDEX_LIFT 2
#define MOTA_INDEX_BACKREST 3

/*Define to establish the sequence of memo recall */


#define NUM_MOTORS_STEP_0  0    
#define NUM_MOTORS_STEP_1  2 + NUM_MOTORS_STEP_0                            
#define NUM_MOTORS_STEP_2  2 + NUM_MOTORS_STEP_1


#define MOTA_AUTO_SLIDE_ENABLE (NUM_MOTORS_STEP_0) 
#define MOTA_AUTO_BACKREST_ENABLE (NUM_MOTORS_STEP_0)
#define MOTA_AUTO_TILT_ENABLE (NUM_MOTORS_STEP_1) 
#define MOTA_AUTO_LIFT_ENABLE (NUM_MOTORS_STEP_1)
#define MOTA_AUTO_END (NUM_MOTORS_STEP_2)


/*Timeout used to disable the movement*/
#define MOTA_TIMEOUT_SLIDE          20000 /*ms*/
#define MOTA_TIMEOUT_LIFT           20000 /*ms*/
#define MOTA_TIMEOUT_TILT           20000 /*ms*/
#define MOTA_TIMEOUT_BACKREST       20000 /*ms*/

#endif /* MOTA_CONFIG_H */
/*----------------------------------------------------------------------------*\
  END OF FILE
\*----------------------------------------------------------------------------*/



