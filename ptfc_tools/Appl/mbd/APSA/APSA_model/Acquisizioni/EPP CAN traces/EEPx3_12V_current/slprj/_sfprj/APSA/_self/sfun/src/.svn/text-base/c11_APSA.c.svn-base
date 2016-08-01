/* Include files */

#include <stddef.h>
#include "blas.h"
#include "APSA_sfun.h"
#include "c11_APSA.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "APSA_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c11_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void initialize_params_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void enable_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void disable_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void c11_update_debugger_state_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance);
static void set_sim_state_c11_APSA(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_st);
static void c11_set_sim_state_side_effects_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance);
static void finalize_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void sf_gateway_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void mdl_start_c11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void initSimStructsc11_APSA(SFc11_APSAInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber);
static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static int32_T c11_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static uint8_T c11_b_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_tp_AVERAGE, const char_T *c11_identifier);
static uint8_T c11_c_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static real_T c11_d_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_average_filter, const char_T *c11_identifier);
static real_T c11_e_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData);
static void c11_f_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_circular_buffer, const char_T *c11_identifier, real_T
  c11_y[8]);
static void c11_g_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId, real_T c11_y[8]);
static void c11_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData);
static const mxArray *c11_h_emlrt_marshallIn(SFc11_APSAInstanceStruct
  *chartInstance, const mxArray *c11_b_setSimStateSideEffectsInfo, const char_T *
  c11_identifier);
static const mxArray *c11_i_emlrt_marshallIn(SFc11_APSAInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId);
static void init_dsm_address_info(SFc11_APSAInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc11_APSAInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  int32_T c11_i0;
  chartInstance->c11_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c11_doSetSimStateSideEffects = 0U;
  chartInstance->c11_setSimStateSideEffectsInfo = NULL;
  chartInstance->c11_is_active_AVERAGE = 0U;
  chartInstance->c11_tp_AVERAGE = 0U;
  chartInstance->c11_is_active_c11_APSA = 0U;
  for (c11_i0 = 0; c11_i0 < 8; c11_i0++) {
    chartInstance->c11_circular_buffer[c11_i0] = 0.0;
  }

  chartInstance->c11_index_vector_filter = 0.0;
  chartInstance->c11_sum_samples = 0.0;
  chartInstance->c11_sum_weights = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c11_average_filter = 0.0;
  }
}

static void initialize_params_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c11_update_debugger_state_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance)
{
  uint32_T c11_prevAniVal;
  c11_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c11_is_active_c11_APSA == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 3U, chartInstance->c11_sfEvent);
  }

  if (chartInstance->c11_is_active_AVERAGE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c11_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c11_sfEvent);
  }

  _SFD_SET_ANIMATION(c11_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance)
{
  const mxArray *c11_st;
  const mxArray *c11_y = NULL;
  real_T c11_hoistedGlobal;
  real_T c11_u;
  const mxArray *c11_b_y = NULL;
  int32_T c11_i1;
  real_T c11_b_u[8];
  const mxArray *c11_c_y = NULL;
  real_T c11_b_hoistedGlobal;
  real_T c11_c_u;
  const mxArray *c11_d_y = NULL;
  real_T c11_c_hoistedGlobal;
  real_T c11_d_u;
  const mxArray *c11_e_y = NULL;
  real_T c11_d_hoistedGlobal;
  real_T c11_e_u;
  const mxArray *c11_f_y = NULL;
  uint8_T c11_e_hoistedGlobal;
  uint8_T c11_f_u;
  const mxArray *c11_g_y = NULL;
  uint8_T c11_f_hoistedGlobal;
  uint8_T c11_g_u;
  const mxArray *c11_h_y = NULL;
  c11_st = NULL;
  c11_st = NULL;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_createcellmatrix(7, 1), false);
  c11_hoistedGlobal = *chartInstance->c11_average_filter;
  c11_u = c11_hoistedGlobal;
  c11_b_y = NULL;
  sf_mex_assign(&c11_b_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 0, c11_b_y);
  for (c11_i1 = 0; c11_i1 < 8; c11_i1++) {
    c11_b_u[c11_i1] = chartInstance->c11_circular_buffer[c11_i1];
  }

  c11_c_y = NULL;
  sf_mex_assign(&c11_c_y, sf_mex_create("y", c11_b_u, 0, 0U, 1U, 0U, 1, 8),
                false);
  sf_mex_setcell(c11_y, 1, c11_c_y);
  c11_b_hoistedGlobal = chartInstance->c11_index_vector_filter;
  c11_c_u = c11_b_hoistedGlobal;
  c11_d_y = NULL;
  sf_mex_assign(&c11_d_y, sf_mex_create("y", &c11_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 2, c11_d_y);
  c11_c_hoistedGlobal = chartInstance->c11_sum_samples;
  c11_d_u = c11_c_hoistedGlobal;
  c11_e_y = NULL;
  sf_mex_assign(&c11_e_y, sf_mex_create("y", &c11_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 3, c11_e_y);
  c11_d_hoistedGlobal = chartInstance->c11_sum_weights;
  c11_e_u = c11_d_hoistedGlobal;
  c11_f_y = NULL;
  sf_mex_assign(&c11_f_y, sf_mex_create("y", &c11_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 4, c11_f_y);
  c11_e_hoistedGlobal = chartInstance->c11_is_active_c11_APSA;
  c11_f_u = c11_e_hoistedGlobal;
  c11_g_y = NULL;
  sf_mex_assign(&c11_g_y, sf_mex_create("y", &c11_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 5, c11_g_y);
  c11_f_hoistedGlobal = chartInstance->c11_is_active_AVERAGE;
  c11_g_u = c11_f_hoistedGlobal;
  c11_h_y = NULL;
  sf_mex_assign(&c11_h_y, sf_mex_create("y", &c11_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c11_y, 6, c11_h_y);
  sf_mex_assign(&c11_st, c11_y, false);
  return c11_st;
}

static void set_sim_state_c11_APSA(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_st)
{
  const mxArray *c11_u;
  real_T c11_dv0[8];
  int32_T c11_i2;
  c11_u = sf_mex_dup(c11_st);
  *chartInstance->c11_average_filter = c11_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 0)), "average_filter");
  c11_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c11_u, 1)),
    "circular_buffer", c11_dv0);
  for (c11_i2 = 0; c11_i2 < 8; c11_i2++) {
    chartInstance->c11_circular_buffer[c11_i2] = c11_dv0[c11_i2];
  }

  chartInstance->c11_index_vector_filter = c11_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 2)), "index_vector_filter");
  chartInstance->c11_sum_samples = c11_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 3)), "sum_samples");
  chartInstance->c11_sum_weights = c11_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 4)), "sum_weights");
  chartInstance->c11_is_active_c11_APSA = c11_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 5)), "is_active_c11_APSA");
  chartInstance->c11_is_active_AVERAGE = c11_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c11_u, 6)), "is_active_AVERAGE");
  sf_mex_assign(&chartInstance->c11_setSimStateSideEffectsInfo,
                c11_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c11_u, 7)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c11_u);
  chartInstance->c11_doSetSimStateSideEffects = 1U;
  c11_update_debugger_state_c11_APSA(chartInstance);
  sf_mex_destroy(&c11_st);
}

static void c11_set_sim_state_side_effects_c11_APSA(SFc11_APSAInstanceStruct
  *chartInstance)
{
  if (chartInstance->c11_doSetSimStateSideEffects != 0) {
    if (chartInstance->c11_is_active_AVERAGE == 1U) {
      chartInstance->c11_tp_AVERAGE = 1U;
    } else {
      chartInstance->c11_tp_AVERAGE = 0U;
    }

    chartInstance->c11_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c11_setSimStateSideEffectsInfo);
}

static void sf_gateway_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  int32_T c11_i3;
  int32_T c11_i4;
  int32_T c11_i5;
  boolean_T c11_out;
  real_T c11_d0;
  int32_T c11_i6;
  real_T c11_d1;
  int32_T c11_i7;
  int32_T c11_i8;
  real_T c11_d2;
  int32_T c11_i9;
  real_T c11_d3;
  int32_T c11_i10;
  real_T c11_d4;
  boolean_T c11_b_out;
  real_T c11_d5;
  int32_T c11_i11;
  int32_T c11_i12;
  real_T c11_d6;
  int32_T c11_i13;
  int32_T exitg1;
  c11_set_sim_state_side_effects_c11_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c11_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c11_Current_AD, 0U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c11_average_filter, 1U);
  for (c11_i3 = 0; c11_i3 < 8; c11_i3++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_circular_buffer[c11_i3], 2U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c11_index_vector_filter, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_samples, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_weights, 5U);
  chartInstance->c11_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c11_sfEvent);
  if (chartInstance->c11_is_active_c11_APSA == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 3U, chartInstance->c11_sfEvent);
    chartInstance->c11_is_active_c11_APSA = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c11_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c11_sfEvent);
    for (c11_i4 = 0; c11_i4 < 8; c11_i4++) {
      chartInstance->c11_circular_buffer[c11_i4] = 0.0;
    }

    for (c11_i5 = 0; c11_i5 < 8; c11_i5++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c11_circular_buffer[c11_i5], 2U);
    }

    chartInstance->c11_is_active_AVERAGE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c11_sfEvent);
    chartInstance->c11_tp_AVERAGE = 1U;
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c11_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c11_sfEvent);
    chartInstance->c11_sum_weights = 1.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_weights, 5U);
    chartInstance->c11_sum_samples = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_samples, 4U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c11_sfEvent);
    chartInstance->c11_index_vector_filter = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_index_vector_filter, 3U);
    do {
      exitg1 = 0;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c11_sfEvent);
      c11_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
        CV_RELATIONAL_EVAL(5U, 2U, 0, chartInstance->c11_index_vector_filter,
                           (real_T)(SIZE_FILTER - 1), -1, 2U,
                           chartInstance->c11_index_vector_filter < (real_T)
                           (SIZE_FILTER - 1)) != 0U, chartInstance->c11_sfEvent))
                 != 0);
      if (c11_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c11_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c11_sfEvent);
        c11_d0 = chartInstance->c11_index_vector_filter;
        if (c11_d0 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 1, 1, c11_d0 >= -2.147483648E+9)) {
            c11_i6 = (int32_T)c11_d0;
          } else {
            c11_i6 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 1, 0, c11_d0 >= 2.147483648E+9)) {
          c11_i6 = MAX_int32_T;
        } else {
          c11_i6 = 0;
        }

        c11_d1 = chartInstance->c11_index_vector_filter + 1.0;
        if (c11_d1 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 2, 1, c11_d1 >= -2.147483648E+9)) {
            c11_i7 = (int32_T)c11_d1;
          } else {
            c11_i7 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 2, 0, c11_d1 >= 2.147483648E+9)) {
          c11_i7 = MAX_int32_T;
        } else {
          c11_i7 = 0;
        }

        chartInstance->c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c11_i6, 0,
          7, 1, 0)] = chartInstance->c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK
          (2U, c11_i7, 0, 7, 1, 0)];
        for (c11_i8 = 0; c11_i8 < 8; c11_i8++) {
          _SFD_DATA_RANGE_CHECK(chartInstance->c11_circular_buffer[c11_i8], 2U);
        }

        c11_d2 = chartInstance->c11_index_vector_filter;
        if (c11_d2 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 0, 1, c11_d2 >= -2.147483648E+9)) {
            c11_i9 = (int32_T)c11_d2;
          } else {
            c11_i9 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 0, 0, c11_d2 >= 2.147483648E+9)) {
          c11_i9 = MAX_int32_T;
        } else {
          c11_i9 = 0;
        }

        chartInstance->c11_sum_samples += chartInstance->
          c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c11_i9, 0, 7, 1, 0)];
        _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_samples, 4U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c11_sfEvent);
        c11_d3 = chartInstance->c11_index_vector_filter;
        if (c11_d3 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 8, 0, 1, c11_d3 >= -2.147483648E+9)) {
            c11_i10 = (int32_T)c11_d3;
          } else {
            c11_i10 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 8, 0, 0, c11_d3 >= 2.147483648E+9)) {
          c11_i10 = MAX_int32_T;
        } else {
          c11_i10 = 0;
        }

        c11_d4 = chartInstance->c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U,
          c11_i10, 0, 7, 1, 0)];
        c11_b_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
          CV_RELATIONAL_EVAL(5U, 8U, 0, c11_d4, 0.0, -1, 1U, c11_d4 != 0.0) !=
          0U, chartInstance->c11_sfEvent)) != 0);
        if (c11_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c11_sfEvent);
          chartInstance->c11_sum_weights++;
          _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_weights, 5U);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c11_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c11_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c11_sfEvent);
        chartInstance->c11_index_vector_filter++;
        _SFD_DATA_RANGE_CHECK(chartInstance->c11_index_vector_filter, 3U);
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c11_sfEvent);
    c11_d5 = chartInstance->c11_index_vector_filter;
    if (c11_d5 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 0, 1, c11_d5 >= -2.147483648E+9)) {
        c11_i11 = (int32_T)c11_d5;
      } else {
        c11_i11 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 0, 0, c11_d5 >= 2.147483648E+9)) {
      c11_i11 = MAX_int32_T;
    } else {
      c11_i11 = 0;
    }

    chartInstance->c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c11_i11, 0, 7,
      1, 0)] = *chartInstance->c11_Current_AD;
    for (c11_i12 = 0; c11_i12 < 8; c11_i12++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c11_circular_buffer[c11_i12], 2U);
    }

    c11_d6 = chartInstance->c11_index_vector_filter;
    if (c11_d6 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 1, 1, c11_d6 >= -2.147483648E+9)) {
        c11_i13 = (int32_T)c11_d6;
      } else {
        c11_i13 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 1, 0, c11_d6 >= 2.147483648E+9)) {
      c11_i13 = MAX_int32_T;
    } else {
      c11_i13 = 0;
    }

    chartInstance->c11_sum_samples += chartInstance->
      c11_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c11_i13, 0, 7, 1, 0)];
    _SFD_DATA_RANGE_CHECK(chartInstance->c11_sum_samples, 4U);
    *chartInstance->c11_average_filter = chartInstance->c11_sum_samples /
      chartInstance->c11_sum_weights;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c11_average_filter, 1U);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c11_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c11_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_APSAMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc11_APSA(SFc11_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c11_machineNumber, uint32_T
  c11_chartNumber, uint32_T c11_instanceNumber)
{
  (void)c11_machineNumber;
  (void)c11_chartNumber;
  (void)c11_instanceNumber;
}

const mxArray *sf_c11_APSA_get_eml_resolved_functions_info(void)
{
  const mxArray *c11_nameCaptureInfo = NULL;
  c11_nameCaptureInfo = NULL;
  sf_mex_assign(&c11_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c11_nameCaptureInfo;
}

static const mxArray *c11_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(int32_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static int32_T c11_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  int32_T c11_y;
  int32_T c11_i14;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_i14, 1, 6, 0U, 0, 0U, 0);
  c11_y = c11_i14;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_sfEvent;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  int32_T c11_y;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_b_sfEvent = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_sfEvent),
    &c11_thisId);
  sf_mex_destroy(&c11_b_sfEvent);
  *(int32_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_b_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  uint8_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(uint8_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static uint8_T c11_b_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_tp_AVERAGE, const char_T *c11_identifier)
{
  uint8_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_tp_AVERAGE),
    &c11_thisId);
  sf_mex_destroy(&c11_b_tp_AVERAGE);
  return c11_y;
}

static uint8_T c11_c_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  uint8_T c11_y;
  uint8_T c11_u0;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_u0, 1, 3, 0U, 0, 0U, 0);
  c11_y = c11_u0;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_tp_AVERAGE;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  uint8_T c11_y;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_b_tp_AVERAGE = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_tp_AVERAGE),
    &c11_thisId);
  sf_mex_destroy(&c11_b_tp_AVERAGE);
  *(uint8_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_c_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  real_T c11_u;
  const mxArray *c11_y = NULL;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  c11_u = *(real_T *)c11_inData;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", &c11_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static real_T c11_d_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_average_filter, const char_T *c11_identifier)
{
  real_T c11_y;
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_average_filter),
    &c11_thisId);
  sf_mex_destroy(&c11_b_average_filter);
  return c11_y;
}

static real_T c11_e_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  real_T c11_y;
  real_T c11_d7;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), &c11_d7, 1, 0, 0U, 0, 0U, 0);
  c11_y = c11_d7;
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void c11_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_average_filter;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_b_average_filter = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_y = c11_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_average_filter),
    &c11_thisId);
  sf_mex_destroy(&c11_b_average_filter);
  *(real_T *)c11_outData = c11_y;
  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_d_sf_marshallOut(void *chartInstanceVoid, void
  *c11_inData)
{
  const mxArray *c11_mxArrayOutData = NULL;
  int32_T c11_i15;
  real_T c11_b_inData[8];
  int32_T c11_i16;
  real_T c11_u[8];
  const mxArray *c11_y = NULL;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_mxArrayOutData = NULL;
  for (c11_i15 = 0; c11_i15 < 8; c11_i15++) {
    c11_b_inData[c11_i15] = (*(real_T (*)[8])c11_inData)[c11_i15];
  }

  for (c11_i16 = 0; c11_i16 < 8; c11_i16++) {
    c11_u[c11_i16] = c11_b_inData[c11_i16];
  }

  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_create("y", c11_u, 0, 0U, 1U, 0U, 1, 8), false);
  sf_mex_assign(&c11_mxArrayOutData, c11_y, false);
  return c11_mxArrayOutData;
}

static void c11_f_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_b_circular_buffer, const char_T *c11_identifier, real_T
  c11_y[8])
{
  emlrtMsgIdentifier c11_thisId;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_circular_buffer),
    &c11_thisId, c11_y);
  sf_mex_destroy(&c11_b_circular_buffer);
}

static void c11_g_emlrt_marshallIn(SFc11_APSAInstanceStruct *chartInstance,
  const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId, real_T c11_y[8])
{
  real_T c11_dv1[8];
  int32_T c11_i17;
  (void)chartInstance;
  sf_mex_import(c11_parentId, sf_mex_dup(c11_u), c11_dv1, 1, 0, 0U, 1, 0U, 1, 8);
  for (c11_i17 = 0; c11_i17 < 8; c11_i17++) {
    c11_y[c11_i17] = c11_dv1[c11_i17];
  }

  sf_mex_destroy(&c11_u);
}

static void c11_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c11_mxArrayInData, const char_T *c11_varName, void *c11_outData)
{
  const mxArray *c11_b_circular_buffer;
  const char_T *c11_identifier;
  emlrtMsgIdentifier c11_thisId;
  real_T c11_y[8];
  int32_T c11_i18;
  SFc11_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc11_APSAInstanceStruct *)chartInstanceVoid;
  c11_b_circular_buffer = sf_mex_dup(c11_mxArrayInData);
  c11_identifier = c11_varName;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  c11_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c11_b_circular_buffer),
    &c11_thisId, c11_y);
  sf_mex_destroy(&c11_b_circular_buffer);
  for (c11_i18 = 0; c11_i18 < 8; c11_i18++) {
    (*(real_T (*)[8])c11_outData)[c11_i18] = c11_y[c11_i18];
  }

  sf_mex_destroy(&c11_mxArrayInData);
}

static const mxArray *c11_h_emlrt_marshallIn(SFc11_APSAInstanceStruct
  *chartInstance, const mxArray *c11_b_setSimStateSideEffectsInfo, const char_T *
  c11_identifier)
{
  const mxArray *c11_y = NULL;
  emlrtMsgIdentifier c11_thisId;
  c11_y = NULL;
  c11_thisId.fIdentifier = c11_identifier;
  c11_thisId.fParent = NULL;
  sf_mex_assign(&c11_y, c11_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c11_b_setSimStateSideEffectsInfo), &c11_thisId), false);
  sf_mex_destroy(&c11_b_setSimStateSideEffectsInfo);
  return c11_y;
}

static const mxArray *c11_i_emlrt_marshallIn(SFc11_APSAInstanceStruct
  *chartInstance, const mxArray *c11_u, const emlrtMsgIdentifier *c11_parentId)
{
  const mxArray *c11_y = NULL;
  (void)chartInstance;
  (void)c11_parentId;
  c11_y = NULL;
  sf_mex_assign(&c11_y, sf_mex_duplicatearraysafe(&c11_u), false);
  sf_mex_destroy(&c11_u);
  return c11_y;
}

static void init_dsm_address_info(SFc11_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc11_APSAInstanceStruct *chartInstance)
{
  chartInstance->c11_Current_AD = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c11_average_filter = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c11_APSA_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1578296115U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2586768636U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1051405440U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1765998259U);
}

mxArray* sf_c11_APSA_get_post_codegen_info(void);
mxArray *sf_c11_APSA_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("tv5adl4TGxqw7SUcRoQ02");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c11_APSA_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c11_APSA_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c11_APSA_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "incompatibleSymbol", };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 3, infoFields);
  mxArray *fallbackReason = mxCreateString("feature_off");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxArray *fallbackType = mxCreateString("early");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c11_APSA_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c11_APSA_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c11_APSA(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x7'type','srcId','name','auxInfo'{{M[1],M[17],T\"average_filter\",},{M[3],M[18],T\"circular_buffer\",},{M[3],M[19],T\"index_vector_filter\",},{M[3],M[21],T\"sum_samples\",},{M[3],M[119],T\"sum_weights\",},{M[8],M[0],T\"is_active_c11_APSA\",},{M[8],M[97],T\"is_active_AVERAGE\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 7, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c11_APSA_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc11_APSAInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc11_APSAInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _APSAMachineNumber_,
           11,
           1,
           10,
           0,
           6,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_APSAMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_APSAMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _APSAMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Current_AD");
          _SFD_SET_DATA_PROPS(1,2,0,1,"average_filter");
          _SFD_SET_DATA_PROPS(2,0,0,0,"circular_buffer");
          _SFD_SET_DATA_PROPS(3,0,0,0,"index_vector_filter");
          _SFD_SET_DATA_PROPS(4,0,0,0,"sum_samples");
          _SFD_SET_DATA_PROPS(5,0,0,0,"sum_weights");
          _SFD_STATE_INFO(0,0,1);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(1);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_ST_SUBSTATE_COUNT(0,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 111, 17, 75 };

          static unsigned int sEndSaturateMap[] = { 130, 36, 76 };

          _SFD_CV_INIT_TRANSITION_SATURATION(3,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 36 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 36 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 41 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(8,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 17 };

          static unsigned int sEndSaturateMap[] = { 36 };

          _SFD_CV_INIT_TRANSITION_SATURATION(8,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 41 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 17, 81 };

          static unsigned int sEndSaturateMap[] = { 36, 100 };

          _SFD_CV_INIT_TRANSITION_SATURATION(5,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)
          c11_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 8;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c11_d_sf_marshallOut,(MexInFcnForType)
            c11_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)
          c11_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)
          c11_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c11_c_sf_marshallOut,(MexInFcnForType)
          c11_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c11_Current_AD);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c11_average_filter);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c11_circular_buffer);
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c11_index_vector_filter);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c11_sum_samples);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c11_sum_weights);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _APSAMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "vkqUyXmLDvMn67hnymfE5E";
}

static void sf_opaque_initialize_c11_APSA(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc11_APSAInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
  initialize_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c11_APSA(void *chartInstanceVar)
{
  enable_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c11_APSA(void *chartInstanceVar)
{
  disable_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c11_APSA(void *chartInstanceVar)
{
  sf_gateway_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c11_APSA(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c11_APSA((SFc11_APSAInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c11_APSA(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c11_APSA((SFc11_APSAInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c11_APSA(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc11_APSAInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_APSA_optimization_info();
    }

    finalize_c11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc11_APSA((SFc11_APSAInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c11_APSA(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c11_APSA((SFc11_APSAInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c11_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_APSA_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,
      11);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,11,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,11,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,11);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,11,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,11,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,11);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3939499368U));
  ssSetChecksum1(S,(2220347931U));
  ssSetChecksum2(S,(1331116038U));
  ssSetChecksum3(S,(92362196U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c11_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c11_APSA(SimStruct *S)
{
  SFc11_APSAInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc11_APSAInstanceStruct *)utMalloc(sizeof
    (SFc11_APSAInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc11_APSAInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c11_APSA;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c11_APSA;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c11_APSA;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c11_APSA;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c11_APSA;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c11_APSA;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c11_APSA;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c11_APSA;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c11_APSA;
  chartInstance->chartInfo.mdlStart = mdlStart_c11_APSA;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c11_APSA;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->checksum = SF_RUNTIME_INFO_CHECKSUM;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  crtInfo->compiledInfo = NULL;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c11_APSA_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c11_APSA(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c11_APSA(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c11_APSA(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c11_APSA_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
