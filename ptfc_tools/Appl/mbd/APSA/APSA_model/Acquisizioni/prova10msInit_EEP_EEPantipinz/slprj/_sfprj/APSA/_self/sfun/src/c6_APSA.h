#ifndef __c6_APSA_h__
#define __c6_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc6_APSAInstanceStruct
#define typedef_SFc6_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c6_sfEvent;
  uint8_T c6_tp_AVERAGE;
  boolean_T c6_isStable;
  uint8_T c6_is_active_c6_APSA;
  uint8_T c6_is_active_AVERAGE;
  real_T c6_circular_buffer[16];
  real_T c6_index_vector_filter;
  real_T c6_last_sample;
  real_T c6_sum_samples;
  real_T c6_Sample_number;
  real_T c6_Inrush_time;
  real_T c6_second_sample;
  real_T c6_sum_weights;
  real_T c6_StartAdapter;
  uint8_T c6_doSetSimStateSideEffects;
  const mxArray *c6_setSimStateSideEffectsInfo;
  real_T *c6_Current_AD;
  real_T *c6_average_filter;
  real_T *c6_filter_current;
} SFc6_APSAInstanceStruct;

#endif                                 /*typedef_SFc6_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_APSA_get_check_sum(mxArray *plhs[]);
extern void c6_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
