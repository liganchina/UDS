/* Include files */

#include <stddef.h>
#include "blas.h"
#include "APSA_sfun.h"
#include "c6_APSA.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "APSA_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c6_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void initialize_params_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void enable_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void disable_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void c6_update_debugger_state_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance);
static void set_sim_state_c6_APSA(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_st);
static void c6_set_sim_state_side_effects_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance);
static void finalize_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void sf_gateway_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void mdl_start_c6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void initSimStructsc6_APSA(SFc6_APSAInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber);
static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData);
static int32_T c6_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static uint8_T c6_b_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_b_tp_AVERAGE, const char_T *c6_identifier);
static uint8_T c6_c_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static real_T c6_d_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_b_average_filter, const char_T *c6_identifier);
static real_T c6_e_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData);
static void c6_f_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_b_circular_buffer, const char_T *c6_identifier, real_T c6_y[16]);
static void c6_g_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[16]);
static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData);
static const mxArray *c6_h_emlrt_marshallIn(SFc6_APSAInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier);
static const mxArray *c6_i_emlrt_marshallIn(SFc6_APSAInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_APSAInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc6_APSAInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  int32_T c6_i0;
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_doSetSimStateSideEffects = 0U;
  chartInstance->c6_setSimStateSideEffectsInfo = NULL;
  chartInstance->c6_is_active_AVERAGE = 0U;
  chartInstance->c6_tp_AVERAGE = 0U;
  chartInstance->c6_is_active_c6_APSA = 0U;
  for (c6_i0 = 0; c6_i0 < 16; c6_i0++) {
    chartInstance->c6_circular_buffer[c6_i0] = 0.0;
  }

  chartInstance->c6_index_vector_filter = 0.0;
  chartInstance->c6_last_sample = 0.0;
  chartInstance->c6_sum_samples = 0.0;
  chartInstance->c6_Sample_number = 0.0;
  chartInstance->c6_Inrush_time = 0.0;
  chartInstance->c6_second_sample = 0.0;
  chartInstance->c6_sum_weights = 0.0;
  chartInstance->c6_StartAdapter = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    *chartInstance->c6_average_filter = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c6_filter_current = 0.0;
  }
}

static void initialize_params_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c6_update_debugger_state_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance)
{
  uint32_T c6_prevAniVal;
  c6_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c6_is_active_c6_APSA == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
  }

  if (chartInstance->c6_is_active_AVERAGE == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
  }

  _SFD_SET_ANIMATION(c6_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance)
{
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  real_T c6_hoistedGlobal;
  real_T c6_u;
  const mxArray *c6_b_y = NULL;
  real_T c6_b_hoistedGlobal;
  real_T c6_b_u;
  const mxArray *c6_c_y = NULL;
  real_T c6_c_hoistedGlobal;
  real_T c6_c_u;
  const mxArray *c6_d_y = NULL;
  real_T c6_d_hoistedGlobal;
  real_T c6_d_u;
  const mxArray *c6_e_y = NULL;
  real_T c6_e_hoistedGlobal;
  real_T c6_e_u;
  const mxArray *c6_f_y = NULL;
  int32_T c6_i1;
  real_T c6_f_u[16];
  const mxArray *c6_g_y = NULL;
  real_T c6_f_hoistedGlobal;
  real_T c6_g_u;
  const mxArray *c6_h_y = NULL;
  real_T c6_g_hoistedGlobal;
  real_T c6_h_u;
  const mxArray *c6_i_y = NULL;
  real_T c6_h_hoistedGlobal;
  real_T c6_i_u;
  const mxArray *c6_j_y = NULL;
  real_T c6_i_hoistedGlobal;
  real_T c6_j_u;
  const mxArray *c6_k_y = NULL;
  real_T c6_j_hoistedGlobal;
  real_T c6_k_u;
  const mxArray *c6_l_y = NULL;
  uint8_T c6_k_hoistedGlobal;
  uint8_T c6_l_u;
  const mxArray *c6_m_y = NULL;
  uint8_T c6_l_hoistedGlobal;
  uint8_T c6_m_u;
  const mxArray *c6_n_y = NULL;
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(13, 1), false);
  c6_hoistedGlobal = *chartInstance->c6_average_filter;
  c6_u = c6_hoistedGlobal;
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_b_hoistedGlobal = *chartInstance->c6_filter_current;
  c6_b_u = c6_b_hoistedGlobal;
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", &c6_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_c_hoistedGlobal = chartInstance->c6_Inrush_time;
  c6_c_u = c6_c_hoistedGlobal;
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", &c6_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  c6_d_hoistedGlobal = chartInstance->c6_Sample_number;
  c6_d_u = c6_d_hoistedGlobal;
  c6_e_y = NULL;
  sf_mex_assign(&c6_e_y, sf_mex_create("y", &c6_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 3, c6_e_y);
  c6_e_hoistedGlobal = chartInstance->c6_StartAdapter;
  c6_e_u = c6_e_hoistedGlobal;
  c6_f_y = NULL;
  sf_mex_assign(&c6_f_y, sf_mex_create("y", &c6_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 4, c6_f_y);
  for (c6_i1 = 0; c6_i1 < 16; c6_i1++) {
    c6_f_u[c6_i1] = chartInstance->c6_circular_buffer[c6_i1];
  }

  c6_g_y = NULL;
  sf_mex_assign(&c6_g_y, sf_mex_create("y", c6_f_u, 0, 0U, 1U, 0U, 1, 16), false);
  sf_mex_setcell(c6_y, 5, c6_g_y);
  c6_f_hoistedGlobal = chartInstance->c6_index_vector_filter;
  c6_g_u = c6_f_hoistedGlobal;
  c6_h_y = NULL;
  sf_mex_assign(&c6_h_y, sf_mex_create("y", &c6_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 6, c6_h_y);
  c6_g_hoistedGlobal = chartInstance->c6_last_sample;
  c6_h_u = c6_g_hoistedGlobal;
  c6_i_y = NULL;
  sf_mex_assign(&c6_i_y, sf_mex_create("y", &c6_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 7, c6_i_y);
  c6_h_hoistedGlobal = chartInstance->c6_second_sample;
  c6_i_u = c6_h_hoistedGlobal;
  c6_j_y = NULL;
  sf_mex_assign(&c6_j_y, sf_mex_create("y", &c6_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 8, c6_j_y);
  c6_i_hoistedGlobal = chartInstance->c6_sum_samples;
  c6_j_u = c6_i_hoistedGlobal;
  c6_k_y = NULL;
  sf_mex_assign(&c6_k_y, sf_mex_create("y", &c6_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 9, c6_k_y);
  c6_j_hoistedGlobal = chartInstance->c6_sum_weights;
  c6_k_u = c6_j_hoistedGlobal;
  c6_l_y = NULL;
  sf_mex_assign(&c6_l_y, sf_mex_create("y", &c6_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 10, c6_l_y);
  c6_k_hoistedGlobal = chartInstance->c6_is_active_c6_APSA;
  c6_l_u = c6_k_hoistedGlobal;
  c6_m_y = NULL;
  sf_mex_assign(&c6_m_y, sf_mex_create("y", &c6_l_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 11, c6_m_y);
  c6_l_hoistedGlobal = chartInstance->c6_is_active_AVERAGE;
  c6_m_u = c6_l_hoistedGlobal;
  c6_n_y = NULL;
  sf_mex_assign(&c6_n_y, sf_mex_create("y", &c6_m_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c6_y, 12, c6_n_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_APSA(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv0[16];
  int32_T c6_i2;
  c6_u = sf_mex_dup(c6_st);
  *chartInstance->c6_average_filter = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 0)), "average_filter");
  *chartInstance->c6_filter_current = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 1)), "filter_current");
  chartInstance->c6_Inrush_time = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 2)), "Inrush_time");
  chartInstance->c6_Sample_number = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 3)), "Sample_number");
  chartInstance->c6_StartAdapter = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 4)), "StartAdapter");
  c6_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 5)),
                        "circular_buffer", c6_dv0);
  for (c6_i2 = 0; c6_i2 < 16; c6_i2++) {
    chartInstance->c6_circular_buffer[c6_i2] = c6_dv0[c6_i2];
  }

  chartInstance->c6_index_vector_filter = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 6)), "index_vector_filter");
  chartInstance->c6_last_sample = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 7)), "last_sample");
  chartInstance->c6_second_sample = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 8)), "second_sample");
  chartInstance->c6_sum_samples = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 9)), "sum_samples");
  chartInstance->c6_sum_weights = c6_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 10)), "sum_weights");
  chartInstance->c6_is_active_c6_APSA = c6_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 11)), "is_active_c6_APSA");
  chartInstance->c6_is_active_AVERAGE = c6_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c6_u, 12)), "is_active_AVERAGE");
  sf_mex_assign(&chartInstance->c6_setSimStateSideEffectsInfo,
                c6_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c6_u, 13)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c6_u);
  chartInstance->c6_doSetSimStateSideEffects = 1U;
  c6_update_debugger_state_c6_APSA(chartInstance);
  sf_mex_destroy(&c6_st);
}

static void c6_set_sim_state_side_effects_c6_APSA(SFc6_APSAInstanceStruct
  *chartInstance)
{
  if (chartInstance->c6_doSetSimStateSideEffects != 0) {
    if (chartInstance->c6_is_active_AVERAGE == 1U) {
      chartInstance->c6_tp_AVERAGE = 1U;
    } else {
      chartInstance->c6_tp_AVERAGE = 0U;
    }

    chartInstance->c6_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c6_setSimStateSideEffectsInfo);
}

static void sf_gateway_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  int32_T c6_i3;
  int32_T c6_i4;
  int32_T c6_i5;
  boolean_T c6_out;
  real_T c6_d0;
  int32_T c6_i6;
  real_T c6_d1;
  int32_T c6_i7;
  int32_T c6_i8;
  real_T c6_d2;
  int32_T c6_i9;
  real_T c6_d3;
  int32_T c6_i10;
  real_T c6_d4;
  boolean_T c6_b_out;
  real_T c6_d5;
  int32_T c6_i11;
  int32_T c6_i12;
  real_T c6_d6;
  int32_T c6_i13;
  int32_T exitg1;
  c6_set_sim_state_side_effects_c6_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_Current_AD, 0U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_average_filter, 1U);
  for (c6_i3 = 0; c6_i3 < 16; c6_i3++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_circular_buffer[c6_i3], 2U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c6_index_vector_filter, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_last_sample, 4U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_samples, 5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c6_filter_current, 6U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_Sample_number, 7U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_Inrush_time, 8U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_second_sample, 9U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_weights, 10U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c6_StartAdapter, 11U);
  chartInstance->c6_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  if (chartInstance->c6_is_active_c6_APSA == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
    chartInstance->c6_is_active_c6_APSA = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c6_sfEvent);
    for (c6_i4 = 0; c6_i4 < 16; c6_i4++) {
      chartInstance->c6_circular_buffer[c6_i4] = 0.0;
    }

    for (c6_i5 = 0; c6_i5 < 16; c6_i5++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c6_circular_buffer[c6_i5], 2U);
    }

    chartInstance->c6_StartAdapter = 2.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_StartAdapter, 11U);
    chartInstance->c6_is_active_AVERAGE = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
    chartInstance->c6_tp_AVERAGE = 1U;
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c6_sfEvent);
    chartInstance->c6_sum_weights = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_weights, 10U);
    chartInstance->c6_sum_samples = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_samples, 5U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c6_sfEvent);
    chartInstance->c6_index_vector_filter = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_index_vector_filter, 3U);
    do {
      exitg1 = 0;
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c6_sfEvent);
      c6_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
                  CV_RELATIONAL_EVAL(5U, 2U, 0,
        chartInstance->c6_index_vector_filter, (real_T)(SIZE_FILTER - 1), -1, 2U,
        chartInstance->c6_index_vector_filter < (real_T)(SIZE_FILTER - 1)) != 0U,
                  chartInstance->c6_sfEvent)) != 0);
      if (c6_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c6_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c6_sfEvent);
        c6_d0 = chartInstance->c6_index_vector_filter;
        if (c6_d0 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 1, 1, c6_d0 >= -2.147483648E+9)) {
            c6_i6 = (int32_T)c6_d0;
          } else {
            c6_i6 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 1, 0, c6_d0 >= 2.147483648E+9)) {
          c6_i6 = MAX_int32_T;
        } else {
          c6_i6 = 0;
        }

        c6_d1 = chartInstance->c6_index_vector_filter + 1.0;
        if (c6_d1 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 2, 1, c6_d1 >= -2.147483648E+9)) {
            c6_i7 = (int32_T)c6_d1;
          } else {
            c6_i7 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 2, 0, c6_d1 >= 2.147483648E+9)) {
          c6_i7 = MAX_int32_T;
        } else {
          c6_i7 = 0;
        }

        chartInstance->c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c6_i6, 0,
          15, 1, 0)] = chartInstance->c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK
          (2U, c6_i7, 0, 15, 1, 0)];
        for (c6_i8 = 0; c6_i8 < 16; c6_i8++) {
          _SFD_DATA_RANGE_CHECK(chartInstance->c6_circular_buffer[c6_i8], 2U);
        }

        c6_d2 = chartInstance->c6_index_vector_filter;
        if (c6_d2 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 3, 0, 1, c6_d2 >= -2.147483648E+9)) {
            c6_i9 = (int32_T)c6_d2;
          } else {
            c6_i9 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 3, 0, 0, c6_d2 >= 2.147483648E+9)) {
          c6_i9 = MAX_int32_T;
        } else {
          c6_i9 = 0;
        }

        chartInstance->c6_sum_samples += chartInstance->
          c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c6_i9, 0, 15, 1, 0)] *
          (chartInstance->c6_index_vector_filter + 1.0);
        _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_samples, 5U);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 8U,
                     chartInstance->c6_sfEvent);
        c6_d3 = chartInstance->c6_index_vector_filter;
        if (c6_d3 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 8, 0, 1, c6_d3 >= -2.147483648E+9)) {
            c6_i10 = (int32_T)c6_d3;
          } else {
            c6_i10 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 8, 0, 0, c6_d3 >= 2.147483648E+9)) {
          c6_i10 = MAX_int32_T;
        } else {
          c6_i10 = 0;
        }

        c6_d4 = chartInstance->c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U,
          c6_i10, 0, 15, 1, 0)];
        c6_b_out = (CV_TRANSITION_EVAL(8U, (int32_T)_SFD_CCP_CALL(8U, 0,
          CV_RELATIONAL_EVAL(5U, 8U, 0, c6_d4, 0.0, -1, 1U, c6_d4 != 0.0) != 0U,
          chartInstance->c6_sfEvent)) != 0);
        if (c6_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c6_sfEvent);
          chartInstance->c6_sum_weights += chartInstance->c6_index_vector_filter
            + 1.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_weights, 10U);
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c6_sfEvent);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c6_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c6_sfEvent);
        chartInstance->c6_index_vector_filter++;
        _SFD_DATA_RANGE_CHECK(chartInstance->c6_index_vector_filter, 3U);
        _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c6_sfEvent);
    c6_d5 = chartInstance->c6_index_vector_filter;
    if (c6_d5 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 0, 1, c6_d5 >= -2.147483648E+9)) {
        c6_i11 = (int32_T)c6_d5;
      } else {
        c6_i11 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 0, 0, c6_d5 >= 2.147483648E+9)) {
      c6_i11 = MAX_int32_T;
    } else {
      c6_i11 = 0;
    }

    chartInstance->c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c6_i11, 0, 15,
      1, 0)] = *chartInstance->c6_Current_AD;
    for (c6_i12 = 0; c6_i12 < 16; c6_i12++) {
      _SFD_DATA_RANGE_CHECK(chartInstance->c6_circular_buffer[c6_i12], 2U);
    }

    c6_d6 = chartInstance->c6_index_vector_filter;
    if (c6_d6 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 5, 1, 1, c6_d6 >= -2.147483648E+9)) {
        c6_i13 = (int32_T)c6_d6;
      } else {
        c6_i13 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 5, 1, 0, c6_d6 >= 2.147483648E+9)) {
      c6_i13 = MAX_int32_T;
    } else {
      c6_i13 = 0;
    }

    chartInstance->c6_sum_samples += chartInstance->
      c6_circular_buffer[_SFD_ARRAY_BOUNDS_CHECK(2U, c6_i13, 0, 15, 1, 0)] *
      (chartInstance->c6_index_vector_filter + 1.0);
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_samples, 5U);
    chartInstance->c6_sum_weights += chartInstance->c6_index_vector_filter + 1.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c6_sum_weights, 10U);
    *chartInstance->c6_average_filter = chartInstance->c6_sum_samples /
      chartInstance->c6_sum_weights;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c6_average_filter, 1U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c6_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c6_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c6_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_APSAMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc6_APSA(SFc6_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c6_machineNumber, uint32_T
  c6_chartNumber, uint32_T c6_instanceNumber)
{
  (void)c6_machineNumber;
  (void)c6_chartNumber;
  (void)c6_instanceNumber;
}

const mxArray *sf_c6_APSA_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c6_nameCaptureInfo;
}

static const mxArray *c6_sf_marshallOut(void *chartInstanceVoid, void *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(int32_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static int32_T c6_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_y;
  int32_T c6_i14;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i14, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i14;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_sfEvent;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_b_sfEvent = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_sfEvent), &c6_thisId);
  sf_mex_destroy(&c6_b_sfEvent);
  *(int32_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_b_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  uint8_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(uint8_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static uint8_T c6_b_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_b_tp_AVERAGE, const char_T *c6_identifier)
{
  uint8_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_AVERAGE),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_AVERAGE);
  return c6_y;
}

static uint8_T c6_c_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  uint8_T c6_y;
  uint8_T c6_u0;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_u0, 1, 3, 0U, 0, 0U, 0);
  c6_y = c6_u0;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_tp_AVERAGE;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  uint8_T c6_y;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_b_tp_AVERAGE = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_tp_AVERAGE),
    &c6_thisId);
  sf_mex_destroy(&c6_b_tp_AVERAGE);
  *(uint8_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_c_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  real_T c6_u;
  const mxArray *c6_y = NULL;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  c6_u = *(real_T *)c6_inData;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", &c6_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static real_T c6_d_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_b_average_filter, const char_T *c6_identifier)
{
  real_T c6_y;
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_average_filter),
    &c6_thisId);
  sf_mex_destroy(&c6_b_average_filter);
  return c6_y;
}

static real_T c6_e_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  real_T c6_y;
  real_T c6_d7;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_d7, 1, 0, 0U, 0, 0U, 0);
  c6_y = c6_d7;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void c6_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_average_filter;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_b_average_filter = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_y = c6_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_average_filter),
    &c6_thisId);
  sf_mex_destroy(&c6_b_average_filter);
  *(real_T *)c6_outData = c6_y;
  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_d_sf_marshallOut(void *chartInstanceVoid, void
  *c6_inData)
{
  const mxArray *c6_mxArrayOutData = NULL;
  int32_T c6_i15;
  real_T c6_b_inData[16];
  int32_T c6_i16;
  real_T c6_u[16];
  const mxArray *c6_y = NULL;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_mxArrayOutData = NULL;
  for (c6_i15 = 0; c6_i15 < 16; c6_i15++) {
    c6_b_inData[c6_i15] = (*(real_T (*)[16])c6_inData)[c6_i15];
  }

  for (c6_i16 = 0; c6_i16 < 16; c6_i16++) {
    c6_u[c6_i16] = c6_b_inData[c6_i16];
  }

  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_create("y", c6_u, 0, 0U, 1U, 0U, 1, 16), false);
  sf_mex_assign(&c6_mxArrayOutData, c6_y, false);
  return c6_mxArrayOutData;
}

static void c6_f_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_b_circular_buffer, const char_T *c6_identifier, real_T c6_y[16])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_circular_buffer),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_circular_buffer);
}

static void c6_g_emlrt_marshallIn(SFc6_APSAInstanceStruct *chartInstance, const
  mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[16])
{
  real_T c6_dv1[16];
  int32_T c6_i17;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv1, 1, 0, 0U, 1, 0U, 1, 16);
  for (c6_i17 = 0; c6_i17 < 16; c6_i17++) {
    c6_y[c6_i17] = c6_dv1[c6_i17];
  }

  sf_mex_destroy(&c6_u);
}

static void c6_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c6_mxArrayInData, const char_T *c6_varName, void *c6_outData)
{
  const mxArray *c6_b_circular_buffer;
  const char_T *c6_identifier;
  emlrtMsgIdentifier c6_thisId;
  real_T c6_y[16];
  int32_T c6_i18;
  SFc6_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc6_APSAInstanceStruct *)chartInstanceVoid;
  c6_b_circular_buffer = sf_mex_dup(c6_mxArrayInData);
  c6_identifier = c6_varName;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  c6_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_b_circular_buffer),
                        &c6_thisId, c6_y);
  sf_mex_destroy(&c6_b_circular_buffer);
  for (c6_i18 = 0; c6_i18 < 16; c6_i18++) {
    (*(real_T (*)[16])c6_outData)[c6_i18] = c6_y[c6_i18];
  }

  sf_mex_destroy(&c6_mxArrayInData);
}

static const mxArray *c6_h_emlrt_marshallIn(SFc6_APSAInstanceStruct
  *chartInstance, const mxArray *c6_b_setSimStateSideEffectsInfo, const char_T
  *c6_identifier)
{
  const mxArray *c6_y = NULL;
  emlrtMsgIdentifier c6_thisId;
  c6_y = NULL;
  c6_thisId.fIdentifier = c6_identifier;
  c6_thisId.fParent = NULL;
  sf_mex_assign(&c6_y, c6_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c6_b_setSimStateSideEffectsInfo), &c6_thisId), false);
  sf_mex_destroy(&c6_b_setSimStateSideEffectsInfo);
  return c6_y;
}

static const mxArray *c6_i_emlrt_marshallIn(SFc6_APSAInstanceStruct
  *chartInstance, const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  const mxArray *c6_y = NULL;
  (void)chartInstance;
  (void)c6_parentId;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_duplicatearraysafe(&c6_u), false);
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc6_APSAInstanceStruct *chartInstance)
{
  chartInstance->c6_Current_AD = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c6_average_filter = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_filter_current = (real_T *)ssGetOutputPortSignal_wrapper
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

void sf_c6_APSA_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1050524089U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2917472938U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2907111411U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1710982864U);
}

mxArray* sf_c6_APSA_get_post_codegen_info(void);
mxArray *sf_c6_APSA_get_autoinheritance_info(void)
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
    mxArray* mxPostCodegenInfo = sf_c6_APSA_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c6_APSA_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_APSA_jit_fallback_info(void)
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

mxArray *sf_c6_APSA_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c6_APSA_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c6_APSA(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[17],T\"average_filter\",},{M[1],M[25],T\"filter_current\",},{M[3],M[47],T\"Inrush_time\",},{M[3],M[37],T\"Sample_number\",},{M[3],M[145],T\"StartAdapter\",},{M[3],M[18],T\"circular_buffer\",},{M[3],M[19],T\"index_vector_filter\",},{M[3],M[20],T\"last_sample\",},{M[3],M[48],T\"second_sample\",},{M[3],M[21],T\"sum_samples\",}}",
    "100 S1x3'type','srcId','name','auxInfo'{{M[3],M[119],T\"sum_weights\",},{M[8],M[0],T\"is_active_c6_APSA\",},{M[8],M[97],T\"is_active_AVERAGE\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 13, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_APSA_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc6_APSAInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc6_APSAInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _APSAMachineNumber_,
           6,
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
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 16;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c6_d_sf_marshallOut,(MexInFcnForType)
            c6_d_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c6_c_sf_marshallOut,(MexInFcnForType)c6_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c6_Current_AD);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c6_average_filter);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c6_circular_buffer);
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c6_index_vector_filter);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c6_last_sample);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c6_sum_samples);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c6_filter_current);
        _SFD_SET_DATA_VALUE_PTR(7U, &chartInstance->c6_Sample_number);
        _SFD_SET_DATA_VALUE_PTR(8U, &chartInstance->c6_Inrush_time);
        _SFD_SET_DATA_VALUE_PTR(9U, &chartInstance->c6_second_sample);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c6_sum_weights);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c6_StartAdapter);
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

static void sf_opaque_initialize_c6_APSA(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc6_APSAInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
  initialize_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_APSA(void *chartInstanceVar)
{
  enable_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_APSA(void *chartInstanceVar)
{
  disable_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_APSA(void *chartInstanceVar)
{
  sf_gateway_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c6_APSA(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c6_APSA((SFc6_APSAInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c6_APSA(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c6_APSA((SFc6_APSAInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c6_APSA(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_APSAInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_APSA_optimization_info();
    }

    finalize_c6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc6_APSA((SFc6_APSAInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_APSA(SimStruct *S)
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
    initialize_params_c6_APSA((SFc6_APSAInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c6_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_APSA_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,6);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,6,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,6,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,6);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,6,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,6,2);
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

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,6);
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

static void mdlRTW_c6_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c6_APSA(SimStruct *S)
{
  SFc6_APSAInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc6_APSAInstanceStruct *)utMalloc(sizeof
    (SFc6_APSAInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc6_APSAInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_APSA;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_APSA;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c6_APSA;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_APSA;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_APSA;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_APSA;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_APSA;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_APSA;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_APSA;
  chartInstance->chartInfo.mdlStart = mdlStart_c6_APSA;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_APSA;
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

void c6_APSA_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c6_APSA(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_APSA(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_APSA(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_APSA_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
