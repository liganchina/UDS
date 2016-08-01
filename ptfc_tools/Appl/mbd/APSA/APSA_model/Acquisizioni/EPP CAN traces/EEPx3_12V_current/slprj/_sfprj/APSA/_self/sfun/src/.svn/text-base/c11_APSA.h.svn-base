#ifndef __c11_APSA_h__
#define __c11_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc11_APSAInstanceStruct
#define typedef_SFc11_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c11_sfEvent;
  uint8_T c11_tp_AVERAGE;
  boolean_T c11_isStable;
  uint8_T c11_is_active_c11_APSA;
  uint8_T c11_is_active_AVERAGE;
  real_T c11_circular_buffer[8];
  real_T c11_index_vector_filter;
  real_T c11_sum_samples;
  real_T c11_sum_weights;
  uint8_T c11_doSetSimStateSideEffects;
  const mxArray *c11_setSimStateSideEffectsInfo;
  real_T *c11_Current_AD;
  real_T *c11_average_filter;
} SFc11_APSAInstanceStruct;

#endif                                 /*typedef_SFc11_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c11_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c11_APSA_get_check_sum(mxArray *plhs[]);
extern void c11_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
