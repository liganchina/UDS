#ifndef __c5_APSA_h__
#define __c5_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc5_APSAInstanceStruct
#define typedef_SFc5_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c5_sfEvent;
  uint8_T c5_tp_AVERAGE;
  boolean_T c5_isStable;
  uint8_T c5_is_active_c5_APSA;
  uint8_T c5_is_active_AVERAGE;
  real_T c5_circular_buffer[16];
  real_T c5_index_vector_filter;
  real_T c5_last_sample;
  real_T c5_sum_samples;
  real_T c5_Sample_number;
  real_T c5_Inrush_time;
  real_T c5_second_sample;
  real_T c5_sum_weights;
  real_T c5_StartAdapter;
  uint8_T c5_doSetSimStateSideEffects;
  const mxArray *c5_setSimStateSideEffectsInfo;
  real_T *c5_Current_AD;
  real_T *c5_average_filter;
  real_T *c5_filter_current;
} SFc5_APSAInstanceStruct;

#endif                                 /*typedef_SFc5_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c5_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c5_APSA_get_check_sum(mxArray *plhs[]);
extern void c5_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
