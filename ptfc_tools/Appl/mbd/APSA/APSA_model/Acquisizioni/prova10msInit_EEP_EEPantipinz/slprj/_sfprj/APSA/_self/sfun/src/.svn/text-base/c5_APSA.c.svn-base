/* Include files */

#include <stddef.h>
#include "blas.h"
#include "APSA_sfun.h"
#include "c5_APSA.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "APSA_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c5_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void initialize_params_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void enable_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void disable_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void c5_update_debugger_state_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance);
static void set_sim_state_c5_APSA(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_st);
static void c5_set_sim_state_side_effects_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance);
static void finalize_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void sf_gateway_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void mdl_start_c5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void initSimStructsc5_APSA(SFc5_APSAInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber);
static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData);
static int32_T c5_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static uint8_T c5_b_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_b_tp_AVERAGE, const char_T *c5_identifier);
static uint8_T c5_c_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static real_T c5_d_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_b_average_filter, const char_T *c5_identifier);
static real_T c5_e_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData);
static void c5_f_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_b_circular_buffer, const char_T *c5_identifier, real_T c5_y[16]);
static void c5_g_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[16]);
static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData);
static const mxArray *c5_h_emlrt_marshallIn(SFc5_APSAInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier);
static const mxArray *c5_i_emlrt_marshallIn(SFc5_APSAInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId);
static void init_dsm_address_info(SFc5_APSAInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc5_APSAInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  int32_T c5_i0;
  chartInstance->c5_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c5_doSetSimStateSideEffects = 0U;
  chartInstance->c5_setSimStateSideEffectsInfo = NULL;
  chartInstance->c5_is_active_AVERAGE = 0U;
  chartInstance->c5_tp_AVERAGE = 0U;
  chartInstance->c5_is_active_c5_APSA = 0U;
  for (c5_i0 = 0; c5_i0 < 16; c5_i0++) {
    chartInstance->c5_circular_buffer[c5_i0] = 0.0;
  }

  chartInstance->c5_index_vector_filter = 0.0;
  chartInstance->c5_last_sample = 0.0;
  chartInstance->c5_sum_samples = 0.0;
  chartInstance->c5_Sample_number = 0.0;
  chartInstance->c5_Inrush_time = 0.0;
  chartInstance->c5_second_sample = 0.0;
  chartInstance->c5_sum_weights = 0.0;
  chartInstance->c5_StartAdapter = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c5_average_filter = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c5_filter_current = 0.0;
  }
}

static void initialize_params_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c5_update_debugger_state_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance)
{
  uint32_T c5_prevAniVal;
  c5_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c5_is_active_c5_APSA == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
  }

  if (chartInstance->c5_is_active_AVERAGE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
  }

  _SFD_SET_ANIMATION(c5_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance)
{
  const mxArray *c5_st;
  const mxArray *c5_y = NULL;
  real_T c5_hoistedGlobal;
  real_T c5_u;
  const mxArray *c5_b_y = NULL;
  real_T c5_b_hoistedGlobal;
  real_T c5_b_u;
  const mxArray *c5_c_y = NULL;
  real_T c5_c_hoistedGlobal;
  real_T c5_c_u;
  const mxArray *c5_d_y = NULL;
  real_T c5_d_hoistedGlobal;
  real_T c5_d_u;
  const mxArray *c5_e_y = NULL;
  real_T c5_e_hoistedGlobal;
  real_T c5_e_u;
  const mxArray *c5_f_y = NULL;
  int32_T c5_i1;
  real_T c5_f_u[16];
  const mxArray *c5_g_y = NULL;
  real_T c5_f_hoistedGlobal;
  real_T c5_g_u;
  const mxArray *c5_h_y = NULL;
  real_T c5_g_hoistedGlobal;
  real_T c5_h_u;
  const mxArray *c5_i_y = NULL;
  real_T c5_h_hoistedGlobal;
  real_T c5_i_u;
  const mxArray *c5_j_y = NULL;
  real_T c5_i_hoistedGlobal;
  real_T c5_j_u;
  const mxArray *c5_k_y = NULL;
  real_T c5_j_hoistedGlobal;
  real_T c5_k_u;
  const mxArray *c5_l_y = NULL;
  uint8_T c5_k_hoistedGlobal;
  uint8_T c5_l_u;
  const mxArray *c5_m_y = NULL;
  uint8_T c5_l_hoistedGlobal;
  uint8_T c5_m_u;
  const mxArray *c5_n_y = NULL;
  c5_st = NULL;
  c5_st = NULL;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_createcellmatrix(13, 1), false);
  c5_hoistedGlobal = *chartInstance->c5_average_filter;
  c5_u = c5_hoistedGlobal;
  c5_b_y = NULL;
  sf_mex_assign(&c5_b_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 0, c5_b_y);
  c5_b_hoistedGlobal = *chartInstance->c5_filter_current;
  c5_b_u = c5_b_hoistedGlobal;
  c5_c_y = NULL;
  sf_mex_assign(&c5_c_y, sf_mex_create("y", &c5_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 1, c5_c_y);
  c5_c_hoistedGlobal = chartInstance->c5_Inrush_time;
  c5_c_u = c5_c_hoistedGlobal;
  c5_d_y = NULL;
  sf_mex_assign(&c5_d_y, sf_mex_create("y", &c5_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 2, c5_d_y);
  c5_d_hoistedGlobal = chartInstance->c5_Sample_number;
  c5_d_u = c5_d_hoistedGlobal;
  c5_e_y = NULL;
  sf_mex_assign(&c5_e_y, sf_mex_create("y", &c5_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 3, c5_e_y);
  c5_e_hoistedGlobal = chartInstance->c5_StartAdapter;
  c5_e_u = c5_e_hoistedGlobal;
  c5_f_y = NULL;
  sf_mex_assign(&c5_f_y, sf_mex_create("y", &c5_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 4, c5_f_y);
  for (c5_i1 = 0; c5_i1 < 16; c5_i1++) {
    c5_f_u[c5_i1] = chartInstance->c5_circular_buffer[c5_i1];
  }

  c5_g_y = NULL;
  sf_mex_assign(&c5_g_y, sf_mex_create("y", c5_f_u, 0, 0U, 1U, 0U, 1, 16), false);
  sf_mex_setcell(c5_y, 5, c5_g_y);
  c5_f_hoistedGlobal = chartInstance->c5_index_vector_filter;
  c5_g_u = c5_f_hoistedGlobal;
  c5_h_y = NULL;
  sf_mex_assign(&c5_h_y, sf_mex_create("y", &c5_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 6, c5_h_y);
  c5_g_hoistedGlobal = chartInstance->c5_last_sample;
  c5_h_u = c5_g_hoistedGlobal;
  c5_i_y = NULL;
  sf_mex_assign(&c5_i_y, sf_mex_create("y", &c5_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 7, c5_i_y);
  c5_h_hoistedGlobal = chartInstance->c5_second_sample;
  c5_i_u = c5_h_hoistedGlobal;
  c5_j_y = NULL;
  sf_mex_assign(&c5_j_y, sf_mex_create("y", &c5_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 8, c5_j_y);
  c5_i_hoistedGlobal = chartInstance->c5_sum_samples;
  c5_j_u = c5_i_hoistedGlobal;
  c5_k_y = NULL;
  sf_mex_assign(&c5_k_y, sf_mex_create("y", &c5_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 9, c5_k_y);
  c5_j_hoistedGlobal = chartInstance->c5_sum_weights;
  c5_k_u = c5_j_hoistedGlobal;
  c5_l_y = NULL;
  sf_mex_assign(&c5_l_y, sf_mex_create("y", &c5_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 10, c5_l_y);
  c5_k_hoistedGlobal = chartInstance->c5_is_active_c5_APSA;
  c5_l_u = c5_k_hoistedGlobal;
  c5_m_y = NULL;
  sf_mex_assign(&c5_m_y, sf_mex_create("y", &c5_l_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 11, c5_m_y);
  c5_l_hoistedGlobal = chartInstance->c5_is_active_AVERAGE;
  c5_m_u = c5_l_hoistedGlobal;
  c5_n_y = NULL;
  sf_mex_assign(&c5_n_y, sf_mex_create("y", &c5_m_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c5_y, 12, c5_n_y);
  sf_mex_assign(&c5_st, c5_y, false);
  return c5_st;
}

static void set_sim_state_c5_APSA(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_st)
{
  const mxArray *c5_u;
  real_T c5_dv0[16];
  int32_T c5_i2;
  c5_u = sf_mex_dup(c5_st);
  *chartInstance->c5_average_filter = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 0)), "average_filter");
  *chartInstance->c5_filter_current = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 1)), "filter_current");
  chartInstance->c5_Inrush_time = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 2)), "Inrush_time");
  chartInstance->c5_Sample_number = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 3)), "Sample_number");
  chartInstance->c5_StartAdapter = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 4)), "StartAdapter");
  c5_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c5_u, 5)),
                        "circular_buffer", c5_dv0);
  for (c5_i2 = 0; c5_i2 < 16; c5_i2++) {
    chartInstance->c5_circular_buffer[c5_i2] = c5_dv0[c5_i2];
  }

  chartInstance->c5_index_vector_filter = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 6)), "index_vector_filter");
  chartInstance->c5_last_sample = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 7)), "last_sample");
  chartInstance->c5_second_sample = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 8)), "second_sample");
  chartInstance->c5_sum_samples = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 9)), "sum_samples");
  chartInstance->c5_sum_weights = c5_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 10)), "sum_weights");
  chartInstance->c5_is_active_c5_APSA = c5_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 11)), "is_active_c5_APSA");
  chartInstance->c5_is_active_AVERAGE = c5_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c5_u, 12)), "is_active_AVERAGE");
  sf_mex_assign(&chartInstance->c5_setSimStateSideEffectsInfo,
                c5_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c5_u, 13)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c5_u);
  chartInstance->c5_doSetSimStateSideEffects = 1U;
  c5_update_debugger_state_c5_APSA(chartInstance);
  sf_mex_destroy(&c5_st);
}

static void c5_set_sim_state_side_effects_c5_APSA(SFc5_APSAInstanceStruct
  *chartInstance)
{
  if (chartInstance->c5_doSetSimStateSideEffects != 0) {
    if (chartInstance->c5_is_active_AVERAGE == 1U) {
      chartInstance->c5_tp_AVERAGE = 1U;
    } else {
      chartInstance->c5_tp_AVERAGE = 0U;
    }

    chartInstance->c5_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c5_setSimStateSideEffectsInfo);
}

static void sf_gateway_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  int32_T c5_i3;
  int32_T c5_i4;
  int32_T c5_i5;
  boolean_T c5_out;
  real_T c5_d0;
  int32_T c5_i6;
  real_T c5_d1;
  int32_T c5_i7;
  int32_T c5_i8;
  real_T c5_d2;
  int32_T c5_i9;
  real_T c5_d3;
  int32_T c5_i10;
  real_T c5_d4;
  boolean_T c5_b_out;
  real_T c5_d5;
  int32_T c5_i11;
  int32_T c5_i12;
  real_T c5_d6;
  int32_T c5_i13;
  int32_T exitg1;
  c5_set_sim_state_side_effects_c5_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_Current_AD, 0U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_average_filter, 1U);
  for (c5_i3 = 0; c5_i3 < 16; c5_i3++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_circular_buffer[c5_i3], 2U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c5_index_vector_filter, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_last_sample, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_samples, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c5_filter_current, 6U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_Sample_number, 7U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_Inrush_time, 8U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_second_sample, 9U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_weights, 10U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c5_StartAdapter, 11U);
  chartInstance->c5_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  if (chartInstance->c5_is_active_c5_APSA == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
    chartInstance->c5_is_active_c5_APSA = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c5_sfEvent);
    for (c5_i4 = 0; c5_i4 < 16; c5_i4++) {
      chartInstance->c5_circular_buffer[c5_i4] = 0.0;
    }

    for (c5_i5 = 0; c5_i5 < 16; c5_i5++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c5_circular_buffer[c5_i5], 2U);
    }

    chartInstance->c5_StartAdapter = 2.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_StartAdapter, 11U);
    chartInstance->c5_is_active_AVERAGE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
    chartInstance->c5_tp_AVERAGE = 1U;
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c5_sfEvent);
    chartInstance->c5_sum_weights = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_weights, 10U);
    chartInstance->c5_sum_samples = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_samples, 5U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c5_sfEvent);
    chartInstance->c5_index_vector_filter = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_index_vector_filter, 3U);
    do {
      exitg1 = 0;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c5_sfEvent);
      c5_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
                  CV_RELATIONAL_EVAL(5U, 2U, 0,
        chartInstance->c5_index_vector_filter, (real_T)(SIZE_FILTER - 1), -1, 2U,
        chartInstance->c5_index_vector_filter < (real_T)(SIZE_FILTER - 1)) != 0U,
                  chartInstance->c5_sfEvent)) != 0);
      if (c5_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c5_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c5_sfEvent);
        c5_d0 = chartInstance->c5_index_vector_filter;
        if (c5_d0 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 1, 1, c5_d0 >= -2.147483648E+9)) {
            c5_i6 = (int32_T)c5_d0;
          } else {
            c5_i6 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 1, 0, c5_d0 >= 2.147483648E+9)) {
          c5_i6 = MAX_int32_T;
        } else {
          c5_i6 = 0;
        }

        c5_d1 = chartInstance->c5_index_vector_filter + 1.0;
        if (c5_d1 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 2, 1, c5_d1 >= -2.147483648E+9)) {
            c5_i7 = (int32_T)c5_d1;
          } else {
            c5_i7 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 2, 0, c5_d1 >= 2.147483648E+9)) {
          c5_i7 = MAX_int32_T;
        } else {
          c5_i7 = 0;
        }

        chartInstance->c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c5_i6, 0,
          15, 1, 0)] = chartInstance->c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK
          (2U, c5_i7, 0, 15, 1, 0)];
        for (c5_i8 = 0; c5_i8 < 16; c5_i8++) {
          _SFD_DATA_RANGE_CHECK(chartInstance->c5_circular_buffer[c5_i8], 2U);
        }

        c5_d2 = chartInstance->c5_index_vector_filter;
        if (c5_d2 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 0, 1, c5_d2 >= -2.147483648E+9)) {
            c5_i9 = (int32_T)c5_d2;
          } else {
            c5_i9 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 0, 0, c5_d2 >= 2.147483648E+9)) {
          c5_i9 = MAX_int32_T;
        } else {
          c5_i9 = 0;
        }

        chartInstance->c5_sum_samples += chartInstance->
          c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c5_i9, 0, 15, 1, 0)] *
          (chartInstance->c5_index_vector_filter + 1.0);
        _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_samples, 5U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c5_sfEvent);
        c5_d3 = chartInstance->c5_index_vector_filter;
        if (c5_d3 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 8, 0, 1, c5_d3 >= -2.147483648E+9)) {
            c5_i10 = (int32_T)c5_d3;
          } else {
            c5_i10 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 8, 0, 0, c5_d3 >= 2.147483648E+9)) {
          c5_i10 = MAX_int32_T;
        } else {
          c5_i10 = 0;
        }

        c5_d4 = chartInstance->c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U,
          c5_i10, 0, 15, 1, 0)];
        c5_b_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
          CV_RELATIONAL_EVAL(5U, 8U, 0, c5_d4, 0.0, -1, 1U, c5_d4 != 0.0) != 0U,
          chartInstance->c5_sfEvent)) != 0);
        if (c5_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c5_sfEvent);
          chartInstance->c5_sum_weights += chartInstance->c5_index_vector_filter
            + 1.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_weights, 10U);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c5_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c5_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c5_sfEvent);
        chartInstance->c5_index_vector_filter++;
        _SFD_DATA_RANGE_CHECK(chartInstance->c5_index_vector_filter, 3U);
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c5_sfEvent);
    c5_d5 = chartInstance->c5_index_vector_filter;
    if (c5_d5 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 0, 1, c5_d5 >= -2.147483648E+9)) {
        c5_i11 = (int32_T)c5_d5;
      } else {
        c5_i11 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 0, 0, c5_d5 >= 2.147483648E+9)) {
      c5_i11 = MAX_int32_T;
    } else {
      c5_i11 = 0;
    }

    chartInstance->c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c5_i11, 0, 15,
      1, 0)] = *chartInstance->c5_Current_AD;
    for (c5_i12 = 0; c5_i12 < 16; c5_i12++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c5_circular_buffer[c5_i12], 2U);
    }

    c5_d6 = chartInstance->c5_index_vector_filter;
    if (c5_d6 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 1, 1, c5_d6 >= -2.147483648E+9)) {
        c5_i13 = (int32_T)c5_d6;
      } else {
        c5_i13 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 1, 0, c5_d6 >= 2.147483648E+9)) {
      c5_i13 = MAX_int32_T;
    } else {
      c5_i13 = 0;
    }

    chartInstance->c5_sum_samples += chartInstance->
      c5_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c5_i13, 0, 15, 1, 0)] *
      (chartInstance->c5_index_vector_filter + 1.0);
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_samples, 5U);
    chartInstance->c5_sum_weights += chartInstance->c5_index_vector_filter + 1.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c5_sum_weights, 10U);
    *chartInstance->c5_average_filter = chartInstance->c5_sum_samples /
      chartInstance->c5_sum_weights;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c5_average_filter, 1U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c5_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c5_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c5_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_APSAMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc5_APSA(SFc5_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c5_machineNumber, uint32_T
  c5_chartNumber, uint32_T c5_instanceNumber)
{
  (void)c5_machineNumber;
  (void)c5_chartNumber;
  (void)c5_instanceNumber;
}

const mxArray *sf_c5_APSA_get_eml_resolved_functions_info(void)
{
  const mxArray *c5_nameCaptureInfo = NULL;
  c5_nameCaptureInfo = NULL;
  sf_mex_assign(&c5_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c5_nameCaptureInfo;
}

static const mxArray *c5_sf_marshallOut(void *chartInstanceVoid, void *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(int32_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static int32_T c5_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  int32_T c5_y;
  int32_T c5_i14;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_i14, 1, 6, 0U, 0, 0U, 0);
  c5_y = c5_i14;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_sfEvent;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  int32_T c5_y;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_b_sfEvent = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_sfEvent), &c5_thisId);
  sf_mex_destroy(&c5_b_sfEvent);
  *(int32_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_b_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  uint8_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(uint8_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static uint8_T c5_b_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_b_tp_AVERAGE, const char_T *c5_identifier)
{
  uint8_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_tp_AVERAGE),
    &c5_thisId);
  sf_mex_destroy(&c5_b_tp_AVERAGE);
  return c5_y;
}

static uint8_T c5_c_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  uint8_T c5_y;
  uint8_T c5_u0;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_u0, 1, 3, 0U, 0, 0U, 0);
  c5_y = c5_u0;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_tp_AVERAGE;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  uint8_T c5_y;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_b_tp_AVERAGE = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_tp_AVERAGE),
    &c5_thisId);
  sf_mex_destroy(&c5_b_tp_AVERAGE);
  *(uint8_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_c_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  real_T c5_u;
  const mxArray *c5_y = NULL;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  c5_u = *(real_T *)c5_inData;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", &c5_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static real_T c5_d_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_b_average_filter, const char_T *c5_identifier)
{
  real_T c5_y;
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_average_filter),
    &c5_thisId);
  sf_mex_destroy(&c5_b_average_filter);
  return c5_y;
}

static real_T c5_e_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance,
  const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  real_T c5_y;
  real_T c5_d7;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), &c5_d7, 1, 0, 0U, 0, 0U, 0);
  c5_y = c5_d7;
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void c5_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_average_filter;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_b_average_filter = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_y = c5_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_average_filter),
    &c5_thisId);
  sf_mex_destroy(&c5_b_average_filter);
  *(real_T *)c5_outData = c5_y;
  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_d_sf_marshallOut(void *chartInstanceVoid, void
  *c5_inData)
{
  const mxArray *c5_mxArrayOutData = NULL;
  int32_T c5_i15;
  real_T c5_b_inData[16];
  int32_T c5_i16;
  real_T c5_u[16];
  const mxArray *c5_y = NULL;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_mxArrayOutData = NULL;
  for (c5_i15 = 0; c5_i15 < 16; c5_i15++) {
    c5_b_inData[c5_i15] = (*(real_T (*)[16])c5_inData)[c5_i15];
  }

  for (c5_i16 = 0; c5_i16 < 16; c5_i16++) {
    c5_u[c5_i16] = c5_b_inData[c5_i16];
  }

  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_create("y", c5_u, 0, 0U, 1U, 0U, 1, 16), false);
  sf_mex_assign(&c5_mxArrayOutData, c5_y, false);
  return c5_mxArrayOutData;
}

static void c5_f_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_b_circular_buffer, const char_T *c5_identifier, real_T c5_y[16])
{
  emlrtMsgIdentifier c5_thisId;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_circular_buffer),
                        &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_circular_buffer);
}

static void c5_g_emlrt_marshallIn(SFc5_APSAInstanceStruct *chartInstance, const
  mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId, real_T c5_y[16])
{
  real_T c5_dv1[16];
  int32_T c5_i17;
  (void)chartInstance;
  sf_mex_import(c5_parentId, sf_mex_dup(c5_u), c5_dv1, 1, 0, 0U, 1, 0U, 1, 16);
  for (c5_i17 = 0; c5_i17 < 16; c5_i17++) {
    c5_y[c5_i17] = c5_dv1[c5_i17];
  }

  sf_mex_destroy(&c5_u);
}

static void c5_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c5_mxArrayInData, const char_T *c5_varName, void *c5_outData)
{
  const mxArray *c5_b_circular_buffer;
  const char_T *c5_identifier;
  emlrtMsgIdentifier c5_thisId;
  real_T c5_y[16];
  int32_T c5_i18;
  SFc5_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc5_APSAInstanceStruct *)chartInstanceVoid;
  c5_b_circular_buffer = sf_mex_dup(c5_mxArrayInData);
  c5_identifier = c5_varName;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  c5_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c5_b_circular_buffer),
                        &c5_thisId, c5_y);
  sf_mex_destroy(&c5_b_circular_buffer);
  for (c5_i18 = 0; c5_i18 < 16; c5_i18++) {
    (*(real_T (*)[16])c5_outData)[c5_i18] = c5_y[c5_i18];
  }

  sf_mex_destroy(&c5_mxArrayInData);
}

static const mxArray *c5_h_emlrt_marshallIn(SFc5_APSAInstanceStruct
  *chartInstance, const mxArray *c5_b_setSimStateSideEffectsInfo, const char_T
  *c5_identifier)
{
  const mxArray *c5_y = NULL;
  emlrtMsgIdentifier c5_thisId;
  c5_y = NULL;
  c5_thisId.fIdentifier = c5_identifier;
  c5_thisId.fParent = NULL;
  sf_mex_assign(&c5_y, c5_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c5_b_setSimStateSideEffectsInfo), &c5_thisId), false);
  sf_mex_destroy(&c5_b_setSimStateSideEffectsInfo);
  return c5_y;
}

static const mxArray *c5_i_emlrt_marshallIn(SFc5_APSAInstanceStruct
  *chartInstance, const mxArray *c5_u, const emlrtMsgIdentifier *c5_parentId)
{
  const mxArray *c5_y = NULL;
  (void)chartInstance;
  (void)c5_parentId;
  c5_y = NULL;
  sf_mex_assign(&c5_y, sf_mex_duplicatearraysafe(&c5_u), false);
  sf_mex_destroy(&c5_u);
  return c5_y;
}

static void init_dsm_address_info(SFc5_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc5_APSAInstanceStruct *chartInstance)
{
  chartInstance->c5_Current_AD = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c5_average_filter = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c5_filter_current = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
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

void sf_c5_APSA_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1050524089U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2917472938U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2907111411U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1710982864U);
}

mxArray* sf_c5_APSA_get_post_codegen_info(void);
mxArray *sf_c5_APSA_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("uL9jcKGA6838zxLgqZ1il");
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

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c5_APSA_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c5_APSA_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c5_APSA_jit_fallback_info(void)
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

mxArray *sf_c5_APSA_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c5_APSA_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c5_APSA(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[17],T\"average_filter\",},{M[1],M[25],T\"filter_current\",},{M[3],M[47],T\"Inrush_time\",},{M[3],M[37],T\"Sample_number\",},{M[3],M[145],T\"StartAdapter\",},{M[3],M[18],T\"circular_buffer\",},{M[3],M[19],T\"index_vector_filter\",},{M[3],M[20],T\"last_sample\",},{M[3],M[48],T\"second_sample\",},{M[3],M[21],T\"sum_samples\",}}",
    "100 S1x3'type','srcId','name','auxInfo'{{M[3],M[119],T\"sum_weights\",},{M[8],M[0],T\"is_active_c5_APSA\",},{M[8],M[97],T\"is_active_AVERAGE\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 13, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c5_APSA_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc5_APSAInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc5_APSAInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _APSAMachineNumber_,
           5,
           1,
           11,
           0,
           12,
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
          _SFD_SET_DATA_PROPS(4,0,0,0,"last_sample");
          _SFD_SET_DATA_PROPS(5,0,0,0,"sum_samples");
          _SFD_SET_DATA_PROPS(6,2,0,1,"filter_current");
          _SFD_SET_DATA_PROPS(7,0,0,0,"Sample_number");
          _SFD_SET_DATA_PROPS(8,0,0,0,"Inrush_time");
          _SFD_SET_DATA_PROPS(9,0,0,0,"second_sample");
          _SFD_SET_DATA_PROPS(10,0,0,0,"sum_weights");
          _SFD_SET_DATA_PROPS(11,0,0,0,"StartAdapter");
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

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 34 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 34 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 111, 17, 75 };

          static unsigned int sEndSaturateMap[] = { 130, 36, 76 };

          _SFD_CV_INIT_TRANSITION_SATURATION(3,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

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

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(8,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 17, 81 };

          static unsigned int sEndSaturateMap[] = { 36, 100 };

          _SFD_CV_INIT_TRANSITION_SATURATION(5,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 16;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c5_d_sf_marshallOut,(MexInFcnForType)
            c5_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c5_c_sf_marshallOut,(MexInFcnForType)c5_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c5_Current_AD);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c5_average_filter);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c5_circular_buffer);
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c5_index_vector_filter);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c5_last_sample);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c5_sum_samples);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c5_filter_current);
        _SFD_SET_DATA_VALUE_PTR(7U, &chartInstance->c5_Sample_number);
        _SFD_SET_DATA_VALUE_PTR(8U, &chartInstance->c5_Inrush_time);
        _SFD_SET_DATA_VALUE_PTR(9U, &chartInstance->c5_second_sample);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c5_sum_weights);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c5_StartAdapter);
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
  return "07vEVLLuwu0mXv45TNSB9F";
}

static void sf_opaque_initialize_c5_APSA(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc5_APSAInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
  initialize_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c5_APSA(void *chartInstanceVar)
{
  enable_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c5_APSA(void *chartInstanceVar)
{
  disable_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c5_APSA(void *chartInstanceVar)
{
  sf_gateway_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c5_APSA(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c5_APSA((SFc5_APSAInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c5_APSA(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c5_APSA((SFc5_APSAInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c5_APSA(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc5_APSAInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_APSA_optimization_info();
    }

    finalize_c5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc5_APSA((SFc5_APSAInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c5_APSA(SimStruct *S)
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
    initialize_params_c5_APSA((SFc5_APSAInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c5_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_APSA_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,5);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,5,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,5,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,5);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,5,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,5,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,5);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1343140576U));
  ssSetChecksum1(S,(1895348323U));
  ssSetChecksum2(S,(385315198U));
  ssSetChecksum3(S,(195439264U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c5_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c5_APSA(SimStruct *S)
{
  SFc5_APSAInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc5_APSAInstanceStruct *)utMalloc(sizeof
    (SFc5_APSAInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc5_APSAInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c5_APSA;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c5_APSA;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c5_APSA;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c5_APSA;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c5_APSA;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c5_APSA;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c5_APSA;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c5_APSA;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c5_APSA;
  chartInstance->chartInfo.mdlStart = mdlStart_c5_APSA;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c5_APSA;
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

void c5_APSA_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c5_APSA(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c5_APSA(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c5_APSA(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c5_APSA_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
