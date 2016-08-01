#ifndef __c1_APSA_h__
#define __c1_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_APSAInstanceStruct
#define typedef_SFc1_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_IDLE;
  uint8_T c1_tp_WRITE_MAP_FORWARD;
  uint8_T c1_tp_ANTIPINCH_ACTIVE_FORWARD;
  uint8_T c1_tp_WAIT_INRUSH_TIME_FORWARD;
  uint8_T c1_tp_CHECK_ANTIPINCH_FORWARD;
  uint8_T c1_tp_WAIT_ADAPTATION_TIME_FORWARD;
  uint8_T c1_tp_WRITE_MAP_BACKWARD;
  uint8_T c1_tp_ANTIPINCH_ACTIVE_BACKWARD;
  uint8_T c1_tp_WAIT_ADAPTATION_TIME_BACKWARD;
  uint8_T c1_tp_WAIT_INRUSH_TIME_BACKWARD;
  uint8_T c1_tp_CHECK_ANTIPINCH_BACKWARD;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_APSA;
  uint8_T c1_is_c1_APSA;
  uint8_T c1_is_ANTIPINCH_ACTIVE_FORWARD;
  uint8_T c1_is_ANTIPINCH_ACTIVE_BACKWARD;
  real_T c1_Lenght_Segment;
  real_T c1_Inrush_time;
  real_T c1_Avarage_EERAM_Current_Map;
  uint16_T c1_Average_Current;
  real_T c1_Mod;
  real_T c1_Segments_Cnt;
  int16_T c1_Averege_Difference;
  real_T c1_Cnt_Fail_Sens_Current;
  real_T c1_Current_Read;
  real_T c1_Counter_Sample_Current;
  real_T c1_Delta_Current;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
  real_T (*c1_EERAM_Current_Map_Forward_Read)[100];
  real_T (*c1_EERAM_Current_Map_Backward_Read)[100];
  real_T *c1_EERAM_Threshold_Attention_Forward;
  real_T *c1_EERAM_Threshold_Attention_Backward;
  real_T *c1_EERAM_Threshold_Antipinch_Forward;
  real_T *c1_EERAM_Threshold_Antipinch_Backward;
  real_T *c1_Check_Antipinch;
  real_T *c1_Cmd_Motor;
  real_T *c1_Write_Map;
  real_T *c1_Lenght_Motor_Stroke;
  real_T *c1_Hall_Counter_Forward;
  real_T *c1_Hall_Counter_Backward;
  real_T *c1_Current;
  real_T *c1_Enable_APSA;
  uint16_T (*c1_EERAM_Current_Map_Forward_Write)[100];
  int16_T (*c1_EERAM_Current_Map_Backward_Write)[100];
  real_T *c1_Fail_Sens_Current;
  real_T *c1_cnt_antipinch;
  real_T *c1_DELTA_1;
  real_T *c1_DELTA_2;
  real_T *c1_DELTA_3;
  real_T *c1_DELTA_4;
  real_T *c1_Antipinch_Active;
  real_T *c1_DELTA_5;
  real_T *c1_DELTA_6;
  real_T *c1_Index_vector;
  real_T *c1_Threshold_AntiPinch_Update;
  real_T *c1_Threshold_Attention_Update;
  real_T *c1_Delta_Current_next;
  real_T *c1_Delta_Current_actual;
  real_T *c1_Current_Read_Average;
} SFc1_APSAInstanceStruct;

#endif                                 /*typedef_SFc1_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_APSA_get_check_sum(mxArray *plhs[]);
extern void c1_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
