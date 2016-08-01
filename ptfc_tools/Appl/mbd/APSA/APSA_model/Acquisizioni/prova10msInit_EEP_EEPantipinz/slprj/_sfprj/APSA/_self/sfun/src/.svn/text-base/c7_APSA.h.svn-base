#ifndef __c7_APSA_h__
#define __c7_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc7_APSAInstanceStruct
#define typedef_SFc7_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c7_sfEvent;
  uint8_T c7_tp_AVERAGE;
  boolean_T c7_isStable;
  uint8_T c7_is_active_c7_APSA;
  uint8_T c7_is_active_AVERAGE;
  real_T c7_circular_buffer[32];
  real_T c7_index_vector_filter;
  real_T c7_last_sample;
  real_T c7_sum_samples;
  real_T c7_Sample_number;
  real_T c7_Inrush_time;
  real_T c7_second_sample;
  real_T c7_sum_weights;
  real_T c7_StartAdapter;
  uint8_T c7_doSetSimStateSideEffects;
  const mxArray *c7_setSimStateSideEffectsInfo;
  real_T *c7_Current_AD;
  real_T *c7_average_filter;
  real_T *c7_filter_current;
} SFc7_APSAInstanceStruct;

#endif                                 /*typedef_SFc7_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c7_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c7_APSA_get_check_sum(mxArray *plhs[]);
extern void c7_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
