#ifndef __c2_APSA_h__
#define __c2_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_APSAInstanceStruct
#define typedef_SFc2_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  uint8_T c2_tp_WRITE_MAP_BACKWARD;
  boolean_T c2_isStable;
  uint8_T c2_is_active_c2_APSA;
  uint8_T c2_is_c2_APSA;
  real_T c2_index_vector;
  real_T c2_mod;
  uint8_T c2_Lenght_Segment;
  real_T c2_Mod;
  real_T c2_Counter_Sample_Current;
  real_T c2_Current_Read;
  real_T c2_Current_Read_Average;
  real_T c2_data;
  uint8_T c2_doSetSimStateSideEffects;
  const mxArray *c2_setSimStateSideEffectsInfo;
  real_T (*c2_EERAM_Current_Map_Backward_Write)[100];
  real_T *c2_Lenght_Motor_Stroke;
  real_T *c2_Cmd_Motor;
  real_T *c2_Current;
  real_T *c2_Hall_Counter_Backward;
  real_T *c2_Index_vector;
  real_T *c2_Mappa;
} SFc2_APSAInstanceStruct;

#endif                                 /*typedef_SFc2_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_APSA_get_check_sum(mxArray *plhs[]);
extern void c2_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
