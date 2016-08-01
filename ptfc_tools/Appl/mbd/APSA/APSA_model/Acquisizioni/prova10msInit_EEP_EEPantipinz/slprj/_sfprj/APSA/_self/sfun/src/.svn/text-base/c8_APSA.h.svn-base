#ifndef __c8_APSA_h__
#define __c8_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc8_APSAInstanceStruct
#define typedef_SFc8_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c8_sfEvent;
  uint8_T c8_tp_AVERAGE;
  boolean_T c8_isStable;
  uint8_T c8_is_active_c8_APSA;
  uint8_T c8_is_active_AVERAGE;
  real_T c8_circular_buffer[16];
  real_T c8_index_vector_filter;
  real_T c8_last_sample;
  real_T c8_sum_samples;
  real_T c8_Sample_number;
  real_T c8_Inrush_time;
  real_T c8_second_sample;
  real_T c8_sum_weights;
  real_T c8_StartAdapter;
  uint8_T c8_doSetSimStateSideEffects;
  const mxArray *c8_setSimStateSideEffectsInfo;
  real_T *c8_Current_AD;
  real_T *c8_average_filter;
  real_T *c8_filter_current;
} SFc8_APSAInstanceStruct;

#endif                                 /*typedef_SFc8_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c8_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c8_APSA_get_check_sum(mxArray *plhs[]);
extern void c8_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
