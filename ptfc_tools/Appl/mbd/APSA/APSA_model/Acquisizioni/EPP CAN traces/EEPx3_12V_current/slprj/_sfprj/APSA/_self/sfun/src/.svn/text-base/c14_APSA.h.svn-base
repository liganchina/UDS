#ifndef __c14_APSA_h__
#define __c14_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc14_APSAInstanceStruct
#define typedef_SFc14_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c14_sfEvent;
  uint8_T c14_tp_AVERAGE;
  boolean_T c14_isStable;
  uint8_T c14_is_active_c14_APSA;
  uint8_T c14_is_active_AVERAGE;
  real_T c14_circular_buffer[8];
  real_T c14_index_vector_filter;
  real_T c14_sum_samples;
  real_T c14_sum_weights;
  uint8_T c14_doSetSimStateSideEffects;
  const mxArray *c14_setSimStateSideEffectsInfo;
  real_T *c14_Current_AD;
  real_T *c14_average_filter;
} SFc14_APSAInstanceStruct;

#endif                                 /*typedef_SFc14_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c14_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c14_APSA_get_check_sum(mxArray *plhs[]);
extern void c14_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
