#ifndef __c4_APSA_h__
#define __c4_APSA_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc4_APSAInstanceStruct
#define typedef_SFc4_APSAInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c4_sfEvent;
  uint8_T c4_tp_CREATE_SIGN;
  boolean_T c4_isStable;
  uint8_T c4_is_active_c4_APSA;
  uint8_T c4_is_c4_APSA;
  real_T c4_index_vector;
  real_T c4_mod;
  uint8_T c4_Lenght_Segment;
  real_T c4_Mod;
  uint8_T c4_doSetSimStateSideEffects;
  const mxArray *c4_setSimStateSideEffectsInfo;
  uint16_T (*c4_EERAM_Current_Map_Forward_Write)[100];
  real_T *c4_Hall_Counter;
  real_T *c4_Lenght_Motor_Stroke;
  real_T *c4_Map_Signal;
  real_T *c4_Cmd_Motor;
} SFc4_APSAInstanceStruct;

#endif                                 /*typedef_SFc4_APSAInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_APSA_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_APSA_get_check_sum(mxArray *plhs[]);
extern void c4_APSA_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
