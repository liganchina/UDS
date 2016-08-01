#ifndef __c9_APSA_h__
#define __c9_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc9_APSAInstanceStruct
#define typedef_SFc9_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c9_sfEvent;
  uint8_T c9_tp_AVERAGE;
  boolean_T c9_isStable;
  uint8_T c9_is_active_c9_APSA;
  uint8_T c9_is_active_AVERAGE;
  real_T c9_circular_buffer[32];
  real_T c9_index_vector_filter;
  real_T c9_last_sample;
  real_T c9_sum_samples;
  real_T c9_Sample_number;
  real_T c9_Inrush_time;
  real_T c9_second_sample;
  real_T c9_sum_weights;
  real_T c9_StartAdapter;
  uint8_T c9_doSetSimStateSideEffects;
  const mxArray *c9_setSimStateSideEffectsInfo;
  real_T *c9_Current_AD;
  real_T *c9_average_filter;
  real_T *c9_filter_current;
} SFc9_APSAInstanceStruct;

#endif                                 /*typedef_SFc9_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c9_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c9_APSA_get_check_sum(mxArray *plhs[]);
extern void c9_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
