/* Include files */

#include <stddef.h>
#include "blas.h"
#include "APSA_sfun.h"
#include "c2_APSA.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "APSA_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c2_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c2_IN_WRITE_MAP_BACKWARD       ((uint8_T)1U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void initialize_params_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void enable_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void disable_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance);
static void set_sim_state_c2_APSA(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_st);
static void c2_set_sim_state_side_effects_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance);
static void finalize_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void sf_gateway_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void mdl_start_c2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void initSimStructsc2_APSA(SFc2_APSAInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static int32_T c2_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static uint8_T c2_b_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_b_tp_WRITE_MAP_BACKWARD, const char_T *c2_identifier);
static uint8_T c2_c_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_d_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_b_EERAM_Current_Map_Backward_Write, const char_T *c2_identifier,
  real_T c2_y[100]);
static void c2_e_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[100]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_f_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_b_index_vector, const char_T *c2_identifier);
static real_T c2_g_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_emlrt_marshallIn(SFc2_APSAInstanceStruct
  *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T
  *c2_identifier);
static const mxArray *c2_i_emlrt_marshallIn(SFc2_APSAInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static int32_T c2__s32d_mod__(SFc2_APSAInstanceStruct *chartInstance, int32_T
  c2_b, int32_T c2_c);
static void init_dsm_address_info(SFc2_APSAInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_APSAInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  int32_T c2_i0;
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_doSetSimStateSideEffects = 0U;
  chartInstance->c2_setSimStateSideEffectsInfo = NULL;
  chartInstance->c2_tp_WRITE_MAP_BACKWARD = 0U;
  chartInstance->c2_is_active_c2_APSA = 0U;
  chartInstance->c2_is_c2_APSA = c2_IN_NO_ACTIVE_CHILD;
  chartInstance->c2_index_vector = 0.0;
  chartInstance->c2_mod = 0.0;
  chartInstance->c2_Lenght_Segment = 0U;
  chartInstance->c2_Mod = 0.0;
  chartInstance->c2_Counter_Sample_Current = 0.0;
  chartInstance->c2_Current_Read = 0.0;
  chartInstance->c2_Current_Read_Average = 0.0;
  chartInstance->c2_data = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    for (c2_i0 = 0; c2_i0 < 100; c2_i0++) {
      (*chartInstance->c2_EERAM_Current_Map_Backward_Write)[c2_i0] = 0.0;
    }
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    *chartInstance->c2_Index_vector = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c2_Mappa = 0.0;
  }
}

static void initialize_params_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance)
{
  uint32_T c2_prevAniVal;
  c2_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c2_is_active_c2_APSA == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  if (chartInstance->c2_is_c2_APSA == c2_IN_WRITE_MAP_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
  }

  _SFD_SET_ANIMATION(c2_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  real_T c2_u[100];
  const mxArray *c2_b_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_u;
  const mxArray *c2_e_y = NULL;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_u;
  const mxArray *c2_f_y = NULL;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  uint8_T c2_f_hoistedGlobal;
  uint8_T c2_g_u;
  const mxArray *c2_h_y = NULL;
  real_T c2_g_hoistedGlobal;
  real_T c2_h_u;
  const mxArray *c2_i_y = NULL;
  real_T c2_h_hoistedGlobal;
  real_T c2_i_u;
  const mxArray *c2_j_y = NULL;
  real_T c2_i_hoistedGlobal;
  real_T c2_j_u;
  const mxArray *c2_k_y = NULL;
  real_T c2_j_hoistedGlobal;
  real_T c2_k_u;
  const mxArray *c2_l_y = NULL;
  uint8_T c2_k_hoistedGlobal;
  uint8_T c2_l_u;
  const mxArray *c2_m_y = NULL;
  uint8_T c2_l_hoistedGlobal;
  uint8_T c2_m_u;
  const mxArray *c2_n_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(13, 1), false);
  for (c2_i1 = 0; c2_i1 < 100; c2_i1++) {
    c2_u[c2_i1] = (*chartInstance->c2_EERAM_Current_Map_Backward_Write)[c2_i1];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 100), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = *chartInstance->c2_Index_vector;
  c2_b_u = c2_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_b_hoistedGlobal = *chartInstance->c2_Mappa;
  c2_c_u = c2_b_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  c2_c_hoistedGlobal = chartInstance->c2_Counter_Sample_Current;
  c2_d_u = c2_c_hoistedGlobal;
  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", &c2_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 3, c2_e_y);
  c2_d_hoistedGlobal = chartInstance->c2_Current_Read;
  c2_e_u = c2_d_hoistedGlobal;
  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", &c2_e_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 4, c2_f_y);
  c2_e_hoistedGlobal = chartInstance->c2_Current_Read_Average;
  c2_f_u = c2_e_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 5, c2_g_y);
  c2_f_hoistedGlobal = chartInstance->c2_Lenght_Segment;
  c2_g_u = c2_f_hoistedGlobal;
  c2_h_y = NULL;
  sf_mex_assign(&c2_h_y, sf_mex_create("y", &c2_g_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 6, c2_h_y);
  c2_g_hoistedGlobal = chartInstance->c2_Mod;
  c2_h_u = c2_g_hoistedGlobal;
  c2_i_y = NULL;
  sf_mex_assign(&c2_i_y, sf_mex_create("y", &c2_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 7, c2_i_y);
  c2_h_hoistedGlobal = chartInstance->c2_data;
  c2_i_u = c2_h_hoistedGlobal;
  c2_j_y = NULL;
  sf_mex_assign(&c2_j_y, sf_mex_create("y", &c2_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 8, c2_j_y);
  c2_i_hoistedGlobal = chartInstance->c2_index_vector;
  c2_j_u = c2_i_hoistedGlobal;
  c2_k_y = NULL;
  sf_mex_assign(&c2_k_y, sf_mex_create("y", &c2_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 9, c2_k_y);
  c2_j_hoistedGlobal = chartInstance->c2_mod;
  c2_k_u = c2_j_hoistedGlobal;
  c2_l_y = NULL;
  sf_mex_assign(&c2_l_y, sf_mex_create("y", &c2_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 10, c2_l_y);
  c2_k_hoistedGlobal = chartInstance->c2_is_active_c2_APSA;
  c2_l_u = c2_k_hoistedGlobal;
  c2_m_y = NULL;
  sf_mex_assign(&c2_m_y, sf_mex_create("y", &c2_l_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 11, c2_m_y);
  c2_l_hoistedGlobal = chartInstance->c2_is_c2_APSA;
  c2_m_u = c2_l_hoistedGlobal;
  c2_n_y = NULL;
  sf_mex_assign(&c2_n_y, sf_mex_create("y", &c2_m_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 12, c2_n_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_APSA(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T c2_dv0[100];
  int32_T c2_i2;
  c2_u = sf_mex_dup(c2_st);
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                        "EERAM_Current_Map_Backward_Write", c2_dv0);
  for (c2_i2 = 0; c2_i2 < 100; c2_i2++) {
    (*chartInstance->c2_EERAM_Current_Map_Backward_Write)[c2_i2] = c2_dv0[c2_i2];
  }

  *chartInstance->c2_Index_vector = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "Index_vector");
  *chartInstance->c2_Mappa = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 2)), "Mappa");
  chartInstance->c2_Counter_Sample_Current = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 3)), "Counter_Sample_Current");
  chartInstance->c2_Current_Read = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 4)), "Current_Read");
  chartInstance->c2_Current_Read_Average = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 5)), "Current_Read_Average");
  chartInstance->c2_Lenght_Segment = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 6)), "Lenght_Segment");
  chartInstance->c2_Mod = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 7)), "Mod");
  chartInstance->c2_data = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 8)), "data");
  chartInstance->c2_index_vector = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 9)), "index_vector");
  chartInstance->c2_mod = c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 10)), "mod");
  chartInstance->c2_is_active_c2_APSA = c2_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 11)), "is_active_c2_APSA");
  chartInstance->c2_is_c2_APSA = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 12)), "is_c2_APSA");
  sf_mex_assign(&chartInstance->c2_setSimStateSideEffectsInfo,
                c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c2_u, 13)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c2_u);
  chartInstance->c2_doSetSimStateSideEffects = 1U;
  c2_update_debugger_state_c2_APSA(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void c2_set_sim_state_side_effects_c2_APSA(SFc2_APSAInstanceStruct
  *chartInstance)
{
  if (chartInstance->c2_doSetSimStateSideEffects != 0) {
    if (chartInstance->c2_is_c2_APSA == c2_IN_WRITE_MAP_BACKWARD) {
      chartInstance->c2_tp_WRITE_MAP_BACKWARD = 1U;
    } else {
      chartInstance->c2_tp_WRITE_MAP_BACKWARD = 0U;
    }

    chartInstance->c2_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c2_setSimStateSideEffectsInfo);
}

static void sf_gateway_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  int32_T c2_i3;
  boolean_T c2_out;
  boolean_T c2_temp;
  boolean_T c2_b_out;
  boolean_T c2_b_temp;
  boolean_T c2_c_out;
  real_T c2_d0;
  int32_T c2_i4;
  int32_T c2_i5;
  real_T c2_d1;
  int32_T c2_i6;
  c2_set_sim_state_side_effects_c2_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i3 = 0; c2_i3 < 100; c2_i3++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c2_EERAM_Current_Map_Backward_Write)
                          [c2_i3], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Hall_Counter, 1U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Lenght_Motor_Stroke, 2U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_index_vector, 3U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_mod, 4U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c2_Lenght_Segment, 5U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_Mod, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Cmd_Motor, 7U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Current, 8U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Hall_Counter_Backward, 9U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_Counter_Sample_Current, 10U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read, 11U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read_Average, 12U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Index_vector, 13U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Mappa, 14U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c2_data, 15U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  if (chartInstance->c2_is_active_c2_APSA == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_active_c2_APSA = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
    _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_Mod = (real_T)c2__s32d_mod__(chartInstance, (int32_T)
      *chartInstance->c2_Lenght_Motor_Stroke, (int32_T)MAX_NUM_ELEMENT);
    _SFD_DATA_RANGE_CHECK(chartInstance->c2_Mod, 6U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c2_sfEvent);
    c2_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
                CV_RELATIONAL_EVAL(5U, 2U, 0, chartInstance->c2_Mod, 0.0, -1, 0U,
      chartInstance->c2_Mod == 0.0) != 0U, chartInstance->c2_sfEvent)) != 0);
    if (c2_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c2_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c2_sfEvent);
      chartInstance->c2_Lenght_Segment = (uint8_T)
        (*chartInstance->c2_Lenght_Motor_Stroke / MAX_NUM_ELEMENT);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c2_Lenght_Segment, 5U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c2_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c2_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c2_sfEvent);
      chartInstance->c2_Lenght_Segment = (uint8_T)
        (*chartInstance->c2_Lenght_Motor_Stroke / MAX_NUM_ELEMENT + 1);
      _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c2_Lenght_Segment, 5U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c2_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c2_sfEvent);
    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 0U, chartInstance->c2_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
    chartInstance->c2_is_c2_APSA = c2_IN_WRITE_MAP_BACKWARD;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c2_sfEvent);
    chartInstance->c2_tp_WRITE_MAP_BACKWARD = 1U;
    *chartInstance->c2_Index_vector = *chartInstance->c2_Hall_Counter_Backward /
      (real_T)chartInstance->c2_Lenght_Segment;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Index_vector, 13U);
    chartInstance->c2_Current_Read = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read, 11U);
    chartInstance->c2_Counter_Sample_Current = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c2_Counter_Sample_Current, 10U);
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c2_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 10U,
                 chartInstance->c2_sfEvent);
    c2_temp = (_SFD_CCP_CALL(10U, 0, CV_RELATIONAL_EVAL(5U, 10U, 0,
      *chartInstance->c2_Hall_Counter_Backward, *chartInstance->c2_Index_vector *
                 (real_T)chartInstance->c2_Lenght_Segment + (real_T)
      chartInstance->c2_Lenght_Segment, -1, 5U,
      *chartInstance->c2_Hall_Counter_Backward >=
      *chartInstance->c2_Index_vector * (real_T)chartInstance->c2_Lenght_Segment
      + (real_T)chartInstance->c2_Lenght_Segment) != 0U,
                chartInstance->c2_sfEvent) != 0);
    if (c2_temp) {
      c2_temp = (_SFD_CCP_CALL(10U, 1, CV_RELATIONAL_EVAL(5U, 10U, 1,
        *chartInstance->c2_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1), -1, 3U, *
        chartInstance->c2_Index_vector <= (real_T)(MAX_NUM_ELEMENT - 1)) != 0U,
                  chartInstance->c2_sfEvent) != 0);
    }

    c2_b_out = (CV_TRANSITION_EVAL(10U, (int32_T)c2_temp) != 0);
    if (c2_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c2_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 11U,
                   chartInstance->c2_sfEvent);
      c2_b_temp = (_SFD_CCP_CALL(11U, 0, CV_RELATIONAL_EVAL(5U, 11U, 0,
        chartInstance->c2_Counter_Sample_Current, 0.0, -1, 0U,
        chartInstance->c2_Counter_Sample_Current == 0.0) != 0U,
        chartInstance->c2_sfEvent) != 0);
      if (!c2_b_temp) {
        c2_b_temp = (_SFD_CCP_CALL(11U, 1, CV_RELATIONAL_EVAL(5U, 11U, 1,
          chartInstance->c2_Current_Read, 0.0, -1, 0U,
          chartInstance->c2_Current_Read == 0.0) != 0U,
          chartInstance->c2_sfEvent) != 0);
      }

      c2_c_out = (CV_TRANSITION_EVAL(11U, (int32_T)c2_b_temp) != 0);
      if (c2_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c2_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c2_sfEvent);
        chartInstance->c2_Current_Read_Average = *chartInstance->c2_Current;
        _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read_Average, 12U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c2_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c2_sfEvent);
        chartInstance->c2_Current_Read_Average = chartInstance->c2_Current_Read /
          chartInstance->c2_Counter_Sample_Current;
        _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read_Average, 12U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c2_sfEvent);
      c2_d0 = *chartInstance->c2_Index_vector;
      if (c2_d0 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 15, 1, 1, c2_d0 >= -2.147483648E+9)) {
          c2_i4 = (int32_T)c2_d0;
        } else {
          c2_i4 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 15, 1, 0, c2_d0 >= 2.147483648E+9)) {
        c2_i4 = MAX_int32_T;
      } else {
        c2_i4 = 0;
      }

      (*chartInstance->c2_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(0U, c2_i4, 0, 99, 1, 0)] =
        chartInstance->c2_Current_Read_Average;
      for (c2_i5 = 0; c2_i5 < 100; c2_i5++) {
        _SFD_DATA_RANGE_CHECK
          ((*chartInstance->c2_EERAM_Current_Map_Backward_Write)[c2_i5], 0U);
      }

      c2_d1 = *chartInstance->c2_Index_vector;
      if (c2_d1 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 15, 0, 1, c2_d1 >= -2.147483648E+9)) {
          c2_i6 = (int32_T)c2_d1;
        } else {
          c2_i6 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 15, 0, 0, c2_d1 >= 2.147483648E+9)) {
        c2_i6 = MAX_int32_T;
      } else {
        c2_i6 = 0;
      }

      *chartInstance->c2_Mappa =
        (*chartInstance->c2_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(0U, c2_i6, 0, 99, 1, 0)];
      _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Mappa, 14U);
      chartInstance->c2_Current_Read = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c2_Current_Read, 11U);
      chartInstance->c2_Counter_Sample_Current = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c2_Counter_Sample_Current, 10U);
      (*chartInstance->c2_Index_vector)++;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c2_Index_vector, 13U);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c2_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c2_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_APSAMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void initSimStructsc2_APSA(SFc2_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  (void)c2_chartNumber;
  (void)c2_instanceNumber;
}

const mxArray *sf_c2_APSA_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i7;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i7, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i7;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent), &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  uint8_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(uint8_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static uint8_T c2_b_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_b_tp_WRITE_MAP_BACKWARD, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_WRITE_MAP_BACKWARD), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_WRITE_MAP_BACKWARD);
  return c2_y;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_tp_WRITE_MAP_BACKWARD;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_b_tp_WRITE_MAP_BACKWARD = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_tp_WRITE_MAP_BACKWARD), &c2_thisId);
  sf_mex_destroy(&c2_b_tp_WRITE_MAP_BACKWARD);
  *(uint8_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i8;
  real_T c2_b_inData[100];
  int32_T c2_i9;
  real_T c2_u[100];
  const mxArray *c2_y = NULL;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i8 = 0; c2_i8 < 100; c2_i8++) {
    c2_b_inData[c2_i8] = (*(real_T (*)[100])c2_inData)[c2_i8];
  }

  for (c2_i9 = 0; c2_i9 < 100; c2_i9++) {
    c2_u[c2_i9] = c2_b_inData[c2_i9];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 100), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static void c2_d_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_b_EERAM_Current_Map_Backward_Write, const char_T *c2_identifier,
  real_T c2_y[100])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c2_b_EERAM_Current_Map_Backward_Write), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_EERAM_Current_Map_Backward_Write);
}

static void c2_e_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[100])
{
  real_T c2_dv1[100];
  int32_T c2_i10;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 1, 100);
  for (c2_i10 = 0; c2_i10 < 100; c2_i10++) {
    c2_y[c2_i10] = c2_dv1[c2_i10];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_EERAM_Current_Map_Backward_Write;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[100];
  int32_T c2_i11;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_b_EERAM_Current_Map_Backward_Write = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c2_b_EERAM_Current_Map_Backward_Write), &c2_thisId,
                        c2_y);
  sf_mex_destroy(&c2_b_EERAM_Current_Map_Backward_Write);
  for (c2_i11 = 0; c2_i11 < 100; c2_i11++) {
    (*(real_T (*)[100])c2_outData)[c2_i11] = c2_y[c2_i11];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_f_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_b_index_vector, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_index_vector),
    &c2_thisId);
  sf_mex_destroy(&c2_b_index_vector);
  return c2_y;
}

static real_T c2_g_emlrt_marshallIn(SFc2_APSAInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d2;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d2, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d2;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_index_vector;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc2_APSAInstanceStruct *)chartInstanceVoid;
  c2_b_index_vector = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_index_vector),
    &c2_thisId);
  sf_mex_destroy(&c2_b_index_vector);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_emlrt_marshallIn(SFc2_APSAInstanceStruct
  *chartInstance, const mxArray *c2_b_setSimStateSideEffectsInfo, const char_T
  *c2_identifier)
{
  const mxArray *c2_y = NULL;
  emlrtMsgIdentifier c2_thisId;
  c2_y = NULL;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  sf_mex_assign(&c2_y, c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_setSimStateSideEffectsInfo), &c2_thisId), false);
  sf_mex_destroy(&c2_b_setSimStateSideEffectsInfo);
  return c2_y;
}

static const mxArray *c2_i_emlrt_marshallIn(SFc2_APSAInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  const mxArray *c2_y = NULL;
  (void)chartInstance;
  (void)c2_parentId;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_duplicatearraysafe(&c2_u), false);
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static int32_T c2__s32d_mod__(SFc2_APSAInstanceStruct *chartInstance, int32_T
  c2_b, int32_T c2_c)
{
  (void)chartInstance;
  if (c2_c == 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_DIVIDE_BY_ZERO);
  }

  return c2_b % c2_c;
}

static void init_dsm_address_info(SFc2_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_APSAInstanceStruct *chartInstance)
{
  chartInstance->c2_EERAM_Current_Map_Backward_Write = (real_T (*)[100])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c2_Hall_Counter = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_Lenght_Motor_Stroke = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_Cmd_Motor = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_Current = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_Hall_Counter_Backward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c2_Index_vector = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_Mappa = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
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

void sf_c2_APSA_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1141663128U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(801116627U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1119752109U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1909675355U);
}

mxArray* sf_c2_APSA_get_post_codegen_info(void);
mxArray *sf_c2_APSA_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("YDhojF6BUKMrUJuhmOO8AG");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_APSA_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_APSA_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_APSA_jit_fallback_info(void)
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

mxArray *sf_c2_APSA_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_APSA_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c2_APSA(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[34],T\"EERAM_Current_Map_Backward_Write\",},{M[1],M[75],T\"Index_vector\",},{M[1],M[76],T\"Mappa\",},{M[3],M[72],T\"Counter_Sample_Current\",},{M[3],M[73],T\"Current_Read\",},{M[3],M[74],T\"Current_Read_Average\",},{M[3],M[33],T\"Lenght_Segment\",},{M[3],M[51],T\"Mod\",},{M[3],M[77],T\"data\",},{M[3],M[29],T\"index_vector\",}}",
    "100 S1x3'type','srcId','name','auxInfo'{{M[3],M[32],T\"mod\",},{M[8],M[0],T\"is_active_c2_APSA\",},{M[9],M[0],T\"is_c2_APSA\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 13, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_APSA_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_APSAInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc2_APSAInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _APSAMachineNumber_,
           2,
           2,
           18,
           0,
           16,
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
          _SFD_SET_DATA_PROPS(0,2,0,1,"EERAM_Current_Map_Backward_Write");
          _SFD_SET_DATA_PROPS(1,1,1,0,"Hall_Counter");
          _SFD_SET_DATA_PROPS(2,1,1,0,"Lenght_Motor_Stroke");
          _SFD_SET_DATA_PROPS(3,0,0,0,"index_vector");
          _SFD_SET_DATA_PROPS(4,0,0,0,"mod");
          _SFD_SET_DATA_PROPS(5,0,0,0,"Lenght_Segment");
          _SFD_SET_DATA_PROPS(6,0,0,0,"Mod");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Cmd_Motor");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Current");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Hall_Counter_Backward");
          _SFD_SET_DATA_PROPS(10,0,0,0,"Counter_Sample_Current");
          _SFD_SET_DATA_PROPS(11,0,0,0,"Current_Read");
          _SFD_SET_DATA_PROPS(12,0,0,0,"Current_Read_Average");
          _SFD_SET_DATA_PROPS(13,2,0,1,"Index_vector");
          _SFD_SET_DATA_PROPS(14,2,0,1,"Mappa");
          _SFD_SET_DATA_PROPS(15,0,0,0,"data");
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,1);
          _SFD_ST_SUBSTATE_COUNT(1,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 7 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(3,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(6,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 74 };

          static unsigned int sEndGuardMap[] = { 70, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(10,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 74 };

          static unsigned int sEndRelationalopMap[] = { 70, 105 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(10,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 26, 44 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(11,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 26, 44 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(11,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 110, 35 };

          static unsigned int sEndSaturateMap[] = { 122, 47 };

          _SFD_CV_INIT_TRANSITION_SATURATION(15,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)
            c2_c_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshallOut,(MexInFcnForType)c2_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_d_sf_marshallOut,(MexInFcnForType)c2_d_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U,
          *chartInstance->c2_EERAM_Current_Map_Backward_Write);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_Hall_Counter);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_Lenght_Motor_Stroke);
        _SFD_SET_DATA_VALUE_PTR(3U, &chartInstance->c2_index_vector);
        _SFD_SET_DATA_VALUE_PTR(4U, &chartInstance->c2_mod);
        _SFD_SET_DATA_VALUE_PTR(5U, &chartInstance->c2_Lenght_Segment);
        _SFD_SET_DATA_VALUE_PTR(6U, &chartInstance->c2_Mod);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c2_Cmd_Motor);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c2_Current);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c2_Hall_Counter_Backward);
        _SFD_SET_DATA_VALUE_PTR(10U, &chartInstance->c2_Counter_Sample_Current);
        _SFD_SET_DATA_VALUE_PTR(11U, &chartInstance->c2_Current_Read);
        _SFD_SET_DATA_VALUE_PTR(12U, &chartInstance->c2_Current_Read_Average);
        _SFD_SET_DATA_VALUE_PTR(13U, chartInstance->c2_Index_vector);
        _SFD_SET_DATA_VALUE_PTR(14U, chartInstance->c2_Mappa);
        _SFD_SET_DATA_VALUE_PTR(15U, &chartInstance->c2_data);
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
  return "UCJxgYSedRXhsdcrMQVREB";
}

static void sf_opaque_initialize_c2_APSA(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_APSAInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
  initialize_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_APSA(void *chartInstanceVar)
{
  enable_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_APSA(void *chartInstanceVar)
{
  disable_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_APSA(void *chartInstanceVar)
{
  sf_gateway_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_APSA(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c2_APSA((SFc2_APSAInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_APSA(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c2_APSA((SFc2_APSAInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c2_APSA(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_APSAInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_APSA_optimization_info();
    }

    finalize_c2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_APSA((SFc2_APSAInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_APSA(SimStruct *S)
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
    initialize_params_c2_APSA((SFc2_APSAInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_APSA_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,5);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,3);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=3; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 5; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2257361889U));
  ssSetChecksum1(S,(2574863080U));
  ssSetChecksum2(S,(1680696184U));
  ssSetChecksum3(S,(2783555313U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c2_APSA(SimStruct *S)
{
  SFc2_APSAInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc2_APSAInstanceStruct *)utMalloc(sizeof
    (SFc2_APSAInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_APSAInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_APSA;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_APSA;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_APSA;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_APSA;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_APSA;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_APSA;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_APSA;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_APSA;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_APSA;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_APSA;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_APSA;
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

void c2_APSA_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_APSA(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_APSA(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_APSA(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_APSA_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
