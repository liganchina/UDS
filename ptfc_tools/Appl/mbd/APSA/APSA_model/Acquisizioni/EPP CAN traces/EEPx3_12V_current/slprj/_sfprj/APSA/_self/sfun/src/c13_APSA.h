#ifndef __c13_APSA_h__
#define __c13_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc13_APSAInstanceStruct
#define typedef_SFc13_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c13_sfEvent;
  uint8_T c13_tp_AVERAGE;
  boolean_T c13_isStable;
  uint8_T c13_is_active_c13_APSA;
  uint8_T c13_is_active_AVERAGE;
  real_T c13_circular_buffer[8];
  real_T c13_index_vector_filter;
  real_T c13_sum_samples;
  real_T c13_sum_weights;
  uint8_T c13_doSetSimStateSideEffects;
  const mxArray *c13_setSimStateSideEffectsInfo;
  real_T *c13_Current_AD;
  real_T *c13_average_filter;
} SFc13_APSAInstanceStruct;

#endif                                 /*typedef_SFc13_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c13_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c13_APSA_get_check_sum(mxArray *plhs[]);
extern void c13_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
