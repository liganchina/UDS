/* Include files */

#include <stddef.h>
#include "blas.h"
#include "APSA_sfun.h"
#include "c1_APSA.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "APSA_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_ANTIPINCH_ACTIVE_BACKWARD ((uint8_T)1U)
#define c1_IN_ANTIPINCH_ACTIVE_FORWARD ((uint8_T)2U)
#define c1_IN_IDLE                     ((uint8_T)3U)
#define c1_IN_WRITE_MAP_BACKWARD       ((uint8_T)4U)
#define c1_IN_WRITE_MAP_FORWARD        ((uint8_T)5U)
#define c1_IN_CHECK_ANTIPINCH_FORWARD  ((uint8_T)1U)
#define c1_IN_WAIT_ADAPTATION_TIME_FORWARD ((uint8_T)2U)
#define c1_IN_WAIT_INRUSH_TIME_FORWARD ((uint8_T)3U)
#define c1_IN_CHECK_ANTIPINCH_BACKWARD ((uint8_T)1U)
#define c1_IN_WAIT_ADAPTATION_TIME_BACKWARD ((uint8_T)2U)
#define c1_IN_WAIT_INRUSH_TIME_BACKWARD ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void initialize_params_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void enable_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void disable_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance);
static void set_sim_state_c1_APSA(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance);
static void finalize_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void sf_gateway_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void mdl_start_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void c1_chartstep_c1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void initSimStructsc1_APSA(SFc1_APSAInstanceStruct *chartInstance);
static void c1_IDLE(SFc1_APSAInstanceStruct *chartInstance);
static void c1_ANTIPINCH_ACTIVE_FORWARD(SFc1_APSAInstanceStruct *chartInstance);
static void c1_exit_internal_ANTIPINCH_ACTIVE_FORWARD(SFc1_APSAInstanceStruct
  *chartInstance);
static void c1_CHECK_ANTIPINCH_FORWARD(SFc1_APSAInstanceStruct *chartInstance);
static void c1_ANTIPINCH_ACTIVE_BACKWARD(SFc1_APSAInstanceStruct *chartInstance);
static void c1_exit_internal_ANTIPINCH_ACTIVE_BACKWARD(SFc1_APSAInstanceStruct
  *chartInstance);
static void c1_CHECK_ANTIPINCH_BACKWARD(SFc1_APSAInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber);
static void c1_Check_Min_Threshold(SFc1_APSAInstanceStruct *chartInstance);
static void c1_Calculate_Lenght_Segment(SFc1_APSAInstanceStruct *chartInstance);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int32_T c1_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_b_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_tp_IDLE, const char_T *c1_identifier);
static uint8_T c1_c_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_d_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Lenght_Segment, const char_T *c1_identifier);
static real_T c1_e_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_f_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_b_EERAM_Current_Map_Forward_Write, const char_T *c1_identifier,
  uint16_T c1_y[100]);
static void c1_g_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint16_T c1_y[100]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_h_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_b_EERAM_Current_Map_Backward_Write, const char_T *c1_identifier,
  int16_T c1_y[100]);
static void c1_i_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, int16_T c1_y[100]);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint16_T c1_j_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Average_Current, const char_T *c1_identifier);
static uint16_T c1_k_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int16_T c1_l_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Averege_Difference, const char_T *c1_identifier);
static int16_T c1_m_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_n_emlrt_marshallIn(SFc1_APSAInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier);
static const mxArray *c1_o_emlrt_marshallIn(SFc1_APSAInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static int32_T c1__s32d_mod__(SFc1_APSAInstanceStruct *chartInstance, int32_T
  c1_b, int32_T c1_c);
static void init_dsm_address_info(SFc1_APSAInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc1_APSAInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 0U;
  chartInstance->c1_tp_CHECK_ANTIPINCH_BACKWARD = 0U;
  chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 0U;
  chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 0U;
  chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 0U;
  chartInstance->c1_tp_CHECK_ANTIPINCH_FORWARD = 0U;
  chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 0U;
  chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 0U;
  chartInstance->c1_tp_IDLE = 0U;
  chartInstance->c1_tp_WRITE_MAP_BACKWARD = 0U;
  chartInstance->c1_tp_WRITE_MAP_FORWARD = 0U;
  chartInstance->c1_is_active_c1_APSA = 0U;
  chartInstance->c1_is_c1_APSA = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_Lenght_Segment = 0.0;
  chartInstance->c1_Inrush_time = 0.0;
  chartInstance->c1_Avarage_EERAM_Current_Map = 0.0;
  chartInstance->c1_Average_Current = 0U;
  chartInstance->c1_Mod = 0.0;
  chartInstance->c1_Segments_Cnt = 0.0;
  chartInstance->c1_Averege_Difference = 0;
  chartInstance->c1_Cnt_Fail_Sens_Current = 0.0;
  chartInstance->c1_Current_Read = 0.0;
  chartInstance->c1_Counter_Sample_Current = 0.0;
  chartInstance->c1_Delta_Current = 0.0;
  if (!(sf_get_output_port_reusable(chartInstance->S, 1) != 0)) {
    for (c1_i0 = 0; c1_i0 < 100; c1_i0++) {
      (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i0] = 0U;
    }
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 2) != 0)) {
    for (c1_i1 = 0; c1_i1 < 100; c1_i1++) {
      (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i1] = 0;
    }
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 3) != 0)) {
    *chartInstance->c1_Fail_Sens_Current = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 4) != 0)) {
    *chartInstance->c1_cnt_antipinch = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 5) != 0)) {
    *chartInstance->c1_Antipinch_Active = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 6) != 0)) {
    *chartInstance->c1_Index_vector = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 7) != 0)) {
    *chartInstance->c1_Threshold_AntiPinch_Update = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 8) != 0)) {
    *chartInstance->c1_Threshold_Attention_Update = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 9) != 0)) {
    *chartInstance->c1_Delta_Current_next = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 10) != 0)) {
    *chartInstance->c1_Delta_Current_actual = 0.0;
  }

  if (!(sf_get_output_port_reusable(chartInstance->S, 11) != 0)) {
    *chartInstance->c1_Current_Read_Average = 0.0;
  }
}

static void initialize_params_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void enable_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c1_update_debugger_state_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c1_is_active_c1_APSA == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_APSA == c1_IN_IDLE) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_APSA == c1_IN_WRITE_MAP_FORWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_APSA == c1_IN_ANTIPINCH_ACTIVE_FORWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
      c1_IN_WAIT_INRUSH_TIME_FORWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
      c1_IN_CHECK_ANTIPINCH_FORWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
      c1_IN_WAIT_ADAPTATION_TIME_FORWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_APSA == c1_IN_WRITE_MAP_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_APSA == c1_IN_ANTIPINCH_ACTIVE_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
      c1_IN_WAIT_ADAPTATION_TIME_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
      c1_IN_WAIT_INRUSH_TIME_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
      c1_IN_CHECK_ANTIPINCH_BACKWARD) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  int32_T c1_i2;
  int16_T c1_e_u[100];
  const mxArray *c1_f_y = NULL;
  int32_T c1_i3;
  uint16_T c1_f_u[100];
  const mxArray *c1_g_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  real_T c1_h_hoistedGlobal;
  real_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  real_T c1_i_hoistedGlobal;
  real_T c1_k_u;
  const mxArray *c1_l_y = NULL;
  real_T c1_j_hoistedGlobal;
  real_T c1_l_u;
  const mxArray *c1_m_y = NULL;
  uint16_T c1_k_hoistedGlobal;
  uint16_T c1_m_u;
  const mxArray *c1_n_y = NULL;
  int16_T c1_l_hoistedGlobal;
  int16_T c1_n_u;
  const mxArray *c1_o_y = NULL;
  real_T c1_m_hoistedGlobal;
  real_T c1_o_u;
  const mxArray *c1_p_y = NULL;
  real_T c1_n_hoistedGlobal;
  real_T c1_p_u;
  const mxArray *c1_q_y = NULL;
  real_T c1_o_hoistedGlobal;
  real_T c1_q_u;
  const mxArray *c1_r_y = NULL;
  real_T c1_p_hoistedGlobal;
  real_T c1_r_u;
  const mxArray *c1_s_y = NULL;
  real_T c1_q_hoistedGlobal;
  real_T c1_s_u;
  const mxArray *c1_t_y = NULL;
  real_T c1_r_hoistedGlobal;
  real_T c1_t_u;
  const mxArray *c1_u_y = NULL;
  real_T c1_s_hoistedGlobal;
  real_T c1_u_u;
  const mxArray *c1_v_y = NULL;
  real_T c1_t_hoistedGlobal;
  real_T c1_v_u;
  const mxArray *c1_w_y = NULL;
  uint8_T c1_u_hoistedGlobal;
  uint8_T c1_w_u;
  const mxArray *c1_x_y = NULL;
  uint8_T c1_v_hoistedGlobal;
  uint8_T c1_x_u;
  const mxArray *c1_y_y = NULL;
  uint8_T c1_w_hoistedGlobal;
  uint8_T c1_y_u;
  const mxArray *c1_ab_y = NULL;
  uint8_T c1_x_hoistedGlobal;
  uint8_T c1_ab_u;
  const mxArray *c1_bb_y = NULL;
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellmatrix(26, 1), false);
  c1_hoistedGlobal = *chartInstance->c1_Antipinch_Active;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *chartInstance->c1_Current_Read_Average;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *chartInstance->c1_Delta_Current_actual;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *chartInstance->c1_Delta_Current_next;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  for (c1_i2 = 0; c1_i2 < 100; c1_i2++) {
    c1_e_u[c1_i2] = (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i2];
  }

  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", c1_e_u, 4, 0U, 1U, 0U, 1, 100),
                false);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  for (c1_i3 = 0; c1_i3 < 100; c1_i3++) {
    c1_f_u[c1_i3] = (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i3];
  }

  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", c1_f_u, 5, 0U, 1U, 0U, 1, 100),
                false);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_e_hoistedGlobal = *chartInstance->c1_Fail_Sens_Current;
  c1_g_u = c1_e_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_f_hoistedGlobal = *chartInstance->c1_Index_vector;
  c1_h_u = c1_f_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_g_hoistedGlobal = *chartInstance->c1_Threshold_AntiPinch_Update;
  c1_i_u = c1_g_hoistedGlobal;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_h_hoistedGlobal = *chartInstance->c1_Threshold_Attention_Update;
  c1_j_u = c1_h_hoistedGlobal;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_i_hoistedGlobal = *chartInstance->c1_cnt_antipinch;
  c1_k_u = c1_i_hoistedGlobal;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_j_hoistedGlobal = chartInstance->c1_Avarage_EERAM_Current_Map;
  c1_l_u = c1_j_hoistedGlobal;
  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_l_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_k_hoistedGlobal = chartInstance->c1_Average_Current;
  c1_m_u = c1_k_hoistedGlobal;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_m_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 12, c1_n_y);
  c1_l_hoistedGlobal = chartInstance->c1_Averege_Difference;
  c1_n_u = c1_l_hoistedGlobal;
  c1_o_y = NULL;
  sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_n_u, 4, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_m_hoistedGlobal = chartInstance->c1_Cnt_Fail_Sens_Current;
  c1_o_u = c1_m_hoistedGlobal;
  c1_p_y = NULL;
  sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_o_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 14, c1_p_y);
  c1_n_hoistedGlobal = chartInstance->c1_Counter_Sample_Current;
  c1_p_u = c1_n_hoistedGlobal;
  c1_q_y = NULL;
  sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_p_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 15, c1_q_y);
  c1_o_hoistedGlobal = chartInstance->c1_Current_Read;
  c1_q_u = c1_o_hoistedGlobal;
  c1_r_y = NULL;
  sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_q_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 16, c1_r_y);
  c1_p_hoistedGlobal = chartInstance->c1_Delta_Current;
  c1_r_u = c1_p_hoistedGlobal;
  c1_s_y = NULL;
  sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_r_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 17, c1_s_y);
  c1_q_hoistedGlobal = chartInstance->c1_Inrush_time;
  c1_s_u = c1_q_hoistedGlobal;
  c1_t_y = NULL;
  sf_mex_assign(&c1_t_y, sf_mex_create("y", &c1_s_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 18, c1_t_y);
  c1_r_hoistedGlobal = chartInstance->c1_Lenght_Segment;
  c1_t_u = c1_r_hoistedGlobal;
  c1_u_y = NULL;
  sf_mex_assign(&c1_u_y, sf_mex_create("y", &c1_t_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 19, c1_u_y);
  c1_s_hoistedGlobal = chartInstance->c1_Mod;
  c1_u_u = c1_s_hoistedGlobal;
  c1_v_y = NULL;
  sf_mex_assign(&c1_v_y, sf_mex_create("y", &c1_u_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 20, c1_v_y);
  c1_t_hoistedGlobal = chartInstance->c1_Segments_Cnt;
  c1_v_u = c1_t_hoistedGlobal;
  c1_w_y = NULL;
  sf_mex_assign(&c1_w_y, sf_mex_create("y", &c1_v_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 21, c1_w_y);
  c1_u_hoistedGlobal = chartInstance->c1_is_active_c1_APSA;
  c1_w_u = c1_u_hoistedGlobal;
  c1_x_y = NULL;
  sf_mex_assign(&c1_x_y, sf_mex_create("y", &c1_w_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 22, c1_x_y);
  c1_v_hoistedGlobal = chartInstance->c1_is_c1_APSA;
  c1_x_u = c1_v_hoistedGlobal;
  c1_y_y = NULL;
  sf_mex_assign(&c1_y_y, sf_mex_create("y", &c1_x_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 23, c1_y_y);
  c1_w_hoistedGlobal = chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD;
  c1_y_u = c1_w_hoistedGlobal;
  c1_ab_y = NULL;
  sf_mex_assign(&c1_ab_y, sf_mex_create("y", &c1_y_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 24, c1_ab_y);
  c1_x_hoistedGlobal = chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD;
  c1_ab_u = c1_x_hoistedGlobal;
  c1_bb_y = NULL;
  sf_mex_assign(&c1_bb_y, sf_mex_create("y", &c1_ab_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c1_y, 25, c1_bb_y);
  sf_mex_assign(&c1_st, c1_y, false);
  return c1_st;
}

static void set_sim_state_c1_APSA(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  int16_T c1_iv0[100];
  int32_T c1_i4;
  uint16_T c1_uv0[100];
  int32_T c1_i5;
  c1_u = sf_mex_dup(c1_st);
  *chartInstance->c1_Antipinch_Active = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 0)), "Antipinch_Active");
  *chartInstance->c1_Current_Read_Average = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "Current_Read_Average");
  *chartInstance->c1_Delta_Current_actual = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 2)), "Delta_Current_actual");
  *chartInstance->c1_Delta_Current_next = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 3)), "Delta_Current_next");
  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 4)),
                        "EERAM_Current_Map_Backward_Write", c1_iv0);
  for (c1_i4 = 0; c1_i4 < 100; c1_i4++) {
    (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i4] = c1_iv0[c1_i4];
  }

  c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)),
                        "EERAM_Current_Map_Forward_Write", c1_uv0);
  for (c1_i5 = 0; c1_i5 < 100; c1_i5++) {
    (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i5] = c1_uv0[c1_i5];
  }

  *chartInstance->c1_Fail_Sens_Current = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 6)), "Fail_Sens_Current");
  *chartInstance->c1_Index_vector = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 7)), "Index_vector");
  *chartInstance->c1_Threshold_AntiPinch_Update = c1_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 8)),
     "Threshold_AntiPinch_Update");
  *chartInstance->c1_Threshold_Attention_Update = c1_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 9)),
     "Threshold_Attention_Update");
  *chartInstance->c1_cnt_antipinch = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 10)), "cnt_antipinch");
  chartInstance->c1_Avarage_EERAM_Current_Map = c1_d_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 11)),
     "Avarage_EERAM_Current_Map");
  chartInstance->c1_Average_Current = c1_j_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 12)), "Average_Current");
  chartInstance->c1_Averege_Difference = c1_l_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 13)), "Averege_Difference");
  chartInstance->c1_Cnt_Fail_Sens_Current = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 14)), "Cnt_Fail_Sens_Current");
  chartInstance->c1_Counter_Sample_Current = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 15)), "Counter_Sample_Current");
  chartInstance->c1_Current_Read = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 16)), "Current_Read");
  chartInstance->c1_Delta_Current = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 17)), "Delta_Current");
  chartInstance->c1_Inrush_time = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 18)), "Inrush_time");
  chartInstance->c1_Lenght_Segment = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 19)), "Lenght_Segment");
  chartInstance->c1_Mod = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 20)), "Mod");
  chartInstance->c1_Segments_Cnt = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 21)), "Segments_Cnt");
  chartInstance->c1_is_active_c1_APSA = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 22)), "is_active_c1_APSA");
  chartInstance->c1_is_c1_APSA = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 23)), "is_c1_APSA");
  chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 24)),
     "is_ANTIPINCH_ACTIVE_FORWARD");
  chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 25)),
     "is_ANTIPINCH_ACTIVE_BACKWARD");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 26)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_APSA(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_APSA(SFc1_APSAInstanceStruct
  *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    if (chartInstance->c1_is_c1_APSA == c1_IN_ANTIPINCH_ACTIVE_BACKWARD) {
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 1U;
    } else {
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
        c1_IN_CHECK_ANTIPINCH_BACKWARD) {
      chartInstance->c1_tp_CHECK_ANTIPINCH_BACKWARD = 1U;
    } else {
      chartInstance->c1_tp_CHECK_ANTIPINCH_BACKWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
        c1_IN_WAIT_ADAPTATION_TIME_BACKWARD) {
      chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 1U;
    } else {
      chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD ==
        c1_IN_WAIT_INRUSH_TIME_BACKWARD) {
      chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 1U;
    } else {
      chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 0U;
    }

    if (chartInstance->c1_is_c1_APSA == c1_IN_ANTIPINCH_ACTIVE_FORWARD) {
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 1U;
    } else {
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
        c1_IN_CHECK_ANTIPINCH_FORWARD) {
      chartInstance->c1_tp_CHECK_ANTIPINCH_FORWARD = 1U;
    } else {
      chartInstance->c1_tp_CHECK_ANTIPINCH_FORWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
        c1_IN_WAIT_ADAPTATION_TIME_FORWARD) {
      chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 1U;
    } else {
      chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 0U;
    }

    if (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD ==
        c1_IN_WAIT_INRUSH_TIME_FORWARD) {
      chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 1U;
    } else {
      chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 0U;
    }

    if (chartInstance->c1_is_c1_APSA == c1_IN_IDLE) {
      chartInstance->c1_tp_IDLE = 1U;
    } else {
      chartInstance->c1_tp_IDLE = 0U;
    }

    if (chartInstance->c1_is_c1_APSA == c1_IN_WRITE_MAP_BACKWARD) {
      chartInstance->c1_tp_WRITE_MAP_BACKWARD = 1U;
    } else {
      chartInstance->c1_tp_WRITE_MAP_BACKWARD = 0U;
    }

    if (chartInstance->c1_is_c1_APSA == c1_IN_WRITE_MAP_FORWARD) {
      chartInstance->c1_tp_WRITE_MAP_FORWARD = 1U;
    } else {
      chartInstance->c1_tp_WRITE_MAP_FORWARD = 0U;
    }

    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_gateway_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  int32_T c1_i9;
  c1_set_sim_state_side_effects_c1_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i6 = 0; c1_i6 < 100; c1_i6++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_EERAM_Current_Map_Forward_Read)
                          [c1_i6], 0U);
  }

  for (c1_i7 = 0; c1_i7 < 100; c1_i7++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c1_EERAM_Current_Map_Backward_Read)
                          [c1_i7], 1U);
  }

  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_EERAM_Threshold_Attention_Forward, 2U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_EERAM_Threshold_Attention_Backward,
                        3U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_EERAM_Threshold_Antipinch_Forward, 4U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_EERAM_Threshold_Antipinch_Backward,
                        5U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Check_Antipinch, 6U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Cmd_Motor, 7U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Write_Map, 8U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Lenght_Motor_Stroke, 9U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Hall_Counter_Forward, 10U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Hall_Counter_Backward, 11U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current, 12U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Enable_APSA, 13U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Lenght_Segment, 14U);
  for (c1_i8 = 0; c1_i8 < 100; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((real_T)
                          (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                          [c1_i8], 15U);
  }

  for (c1_i9 = 0; c1_i9 < 100; c1_i9++) {
    _SFD_DATA_RANGE_CHECK((real_T)
                          (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                          [c1_i9], 16U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map, 18U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current, 19U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Mod, 20U);
  _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U, 100.0);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Averege_Difference, 22U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Fail_Sens_Current, 23U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Cnt_Fail_Sens_Current, 24U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_1, 26U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_2, 27U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_3, 28U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_4, 29U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_5, 31U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_DELTA_6, 32U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_AntiPinch_Update, 34U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_Attention_Update, 35U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_next, 36U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_actual, 37U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Delta_Current, 41U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_APSA(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_APSAMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_chartstep_c1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  int32_T c1_i10;
  real_T c1_d0;
  uint16_T c1_u0;
  int32_T c1_i11;
  int32_T c1_i12;
  real_T c1_d1;
  int16_T c1_i13;
  int32_T c1_i14;
  boolean_T c1_out;
  boolean_T c1_temp;
  boolean_T c1_b_out;
  int32_T c1_i15;
  int32_T c1_i16;
  boolean_T c1_b_temp;
  boolean_T c1_c_out;
  boolean_T c1_c_temp;
  boolean_T c1_d_out;
  real_T c1_d2;
  int32_T c1_i17;
  real_T c1_d3;
  int16_T c1_i18;
  int32_T c1_i19;
  boolean_T c1_e_out;
  boolean_T c1_d_temp;
  boolean_T c1_f_out;
  int32_T c1_i20;
  int32_T c1_i21;
  boolean_T c1_e_temp;
  boolean_T c1_g_out;
  boolean_T c1_f_temp;
  boolean_T c1_h_out;
  real_T c1_d4;
  int32_T c1_i22;
  real_T c1_d5;
  uint16_T c1_u1;
  int32_T c1_i23;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_c1_APSA == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_c1_APSA = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    *chartInstance->c1_Index_vector = 0.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
    chartInstance->c1_Inrush_time = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
    chartInstance->c1_Segments_Cnt = 0.0;
    _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U, 100.0);
    chartInstance->c1_Cnt_Fail_Sens_Current = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Cnt_Fail_Sens_Current, 24U);
    for (c1_i10 = 0; c1_i10 < 100; c1_i10++) {
      c1_d0 = (*chartInstance->c1_EERAM_Current_Map_Forward_Read)[c1_i10];
      if (c1_d0 < 65536.0) {
        if (CV_SATURATION_EVAL(5, 9, 0, 1, c1_d0 >= 0.0)) {
          c1_u0 = (uint16_T)c1_d0;
        } else {
          c1_u0 = 0U;
        }
      } else if (CV_SATURATION_EVAL(5, 9, 0, 0, c1_d0 >= 65536.0)) {
        c1_u0 = MAX_uint16_T;
      } else {
        c1_u0 = 0U;
      }

      (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i10] = c1_u0;
    }

    for (c1_i11 = 0; c1_i11 < 100; c1_i11++) {
      _SFD_DATA_RANGE_CHECK((real_T)
                            (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                            [c1_i11], 15U);
    }

    for (c1_i12 = 0; c1_i12 < 100; c1_i12++) {
      c1_d1 = (*chartInstance->c1_EERAM_Current_Map_Forward_Read)[c1_i12];
      if (c1_d1 < 32768.0) {
        if (CV_SATURATION_EVAL(5, 9, 1, 1, c1_d1 >= -32768.0)) {
          c1_i13 = (int16_T)c1_d1;
        } else {
          c1_i13 = MIN_int16_T;
        }
      } else if (CV_SATURATION_EVAL(5, 9, 1, 0, c1_d1 >= 32768.0)) {
        c1_i13 = MAX_int16_T;
      } else {
        c1_i13 = 0;
      }

      (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i12] = c1_i13;
    }

    for (c1_i14 = 0; c1_i14 < 100; c1_i14++) {
      _SFD_DATA_RANGE_CHECK((real_T)
                            (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                            [c1_i14], 16U);
    }

    _SFD_SYMBOL_SCOPE_POP();
    _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
    c1_Calculate_Lenght_Segment(chartInstance);
    chartInstance->c1_is_c1_APSA = c1_IN_IDLE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_IDLE = 1U;
    *chartInstance->c1_Antipinch_Active = (real_T)APSA_NOT_ACTIVE;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
  } else {
    switch (chartInstance->c1_is_c1_APSA) {
     case c1_IN_ANTIPINCH_ACTIVE_BACKWARD:
      CV_CHART_EVAL(0, 0, 1);
      c1_ANTIPINCH_ACTIVE_BACKWARD(chartInstance);
      break;

     case c1_IN_ANTIPINCH_ACTIVE_FORWARD:
      CV_CHART_EVAL(0, 0, 2);
      c1_ANTIPINCH_ACTIVE_FORWARD(chartInstance);
      break;

     case c1_IN_IDLE:
      CV_CHART_EVAL(0, 0, 3);
      c1_IDLE(chartInstance);
      break;

     case c1_IN_WRITE_MAP_BACKWARD:
      CV_CHART_EVAL(0, 0, 4);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 87U,
                   chartInstance->c1_sfEvent);
      c1_out = (CV_TRANSITION_EVAL(87U, (int32_T)_SFD_CCP_CALL(87U, 0,
                  CV_RELATIONAL_EVAL(5U, 87U, 0, *chartInstance->c1_Write_Map,
        (real_T)APSA_NOT_ACTIVE, -1, 0U, *chartInstance->c1_Write_Map == (real_T)
        APSA_NOT_ACTIVE) != 0U, chartInstance->c1_sfEvent)) != 0);
      if (c1_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 87U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_WRITE_MAP_BACKWARD = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_APSA = c1_IN_IDLE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_IDLE = 1U;
        *chartInstance->c1_Antipinch_Active = (real_T)APSA_NOT_ACTIVE;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 85U,
                     chartInstance->c1_sfEvent);
        c1_temp = (_SFD_CCP_CALL(85U, 0, CV_RELATIONAL_EVAL(5U, 85U, 0,
          *chartInstance->c1_Write_Map, (real_T)APSA_ACTIVE, -1, 0U,
          *chartInstance->c1_Write_Map == (real_T)APSA_ACTIVE) != 0U,
                    chartInstance->c1_sfEvent) != 0);
        if (c1_temp) {
          c1_temp = (_SFD_CCP_CALL(85U, 1, CV_RELATIONAL_EVAL(5U, 85U, 1,
            *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_FORWARD, -1, 0U,
            *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_FORWARD) != 0U,
                      chartInstance->c1_sfEvent) != 0);
        }

        c1_b_out = (CV_TRANSITION_EVAL(85U, (int32_T)c1_temp) != 0);
        if (c1_b_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 85U, chartInstance->c1_sfEvent);
          for (c1_i15 = 0; c1_i15 < 100; c1_i15++) {
            (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i15] = 0U;
          }

          for (c1_i16 = 0; c1_i16 < 100; c1_i16++) {
            _SFD_DATA_RANGE_CHECK((real_T)
                                  (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                  [c1_i16], 15U);
          }

          chartInstance->c1_tp_WRITE_MAP_BACKWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_c1_APSA = c1_IN_WRITE_MAP_FORWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WRITE_MAP_FORWARD = 1U;
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Forward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          chartInstance->c1_Current_Read = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
          chartInstance->c1_Counter_Sample_Current = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 138U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 139U,
                       chartInstance->c1_sfEvent);
          c1_b_temp = (_SFD_CCP_CALL(139U, 0, CV_RELATIONAL_EVAL(5U, 139U, 0,
            *chartInstance->c1_Hall_Counter_Backward,
            *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment +
            chartInstance->c1_Lenght_Segment, -1, 5U,
            *chartInstance->c1_Hall_Counter_Backward >=
            *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment +
            chartInstance->c1_Lenght_Segment) != 0U, chartInstance->c1_sfEvent)
                       != 0);
          if (c1_b_temp) {
            c1_b_temp = (_SFD_CCP_CALL(139U, 1, CV_RELATIONAL_EVAL(5U, 139U, 1, *
              chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1), -1,
              3U, *chartInstance->c1_Index_vector <= (real_T)(MAX_NUM_ELEMENT -
              1)) != 0U, chartInstance->c1_sfEvent) != 0);
          }

          c1_c_out = (CV_TRANSITION_EVAL(139U, (int32_T)c1_b_temp) != 0);
          if (c1_c_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 139U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 160U,
                         chartInstance->c1_sfEvent);
            c1_c_temp = (_SFD_CCP_CALL(160U, 0, CV_RELATIONAL_EVAL(5U, 160U, 0,
              chartInstance->c1_Counter_Sample_Current, 0.0, -1, 0U,
              chartInstance->c1_Counter_Sample_Current == 0.0) != 0U,
              chartInstance->c1_sfEvent) != 0);
            if (!c1_c_temp) {
              c1_c_temp = (_SFD_CCP_CALL(160U, 1, CV_RELATIONAL_EVAL(5U, 160U, 1,
                chartInstance->c1_Current_Read, 0.0, -1, 0U,
                chartInstance->c1_Current_Read == 0.0) != 0U,
                chartInstance->c1_sfEvent) != 0);
            }

            c1_d_out = (CV_TRANSITION_EVAL(160U, (int32_T)c1_c_temp) != 0);
            if (c1_d_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 160U,
                           chartInstance->c1_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 161U,
                           chartInstance->c1_sfEvent);
              *chartInstance->c1_Current_Read_Average =
                *chartInstance->c1_Current;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 162U,
                           chartInstance->c1_sfEvent);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 137U,
                           chartInstance->c1_sfEvent);
              *chartInstance->c1_Current_Read_Average =
                chartInstance->c1_Current_Read /
                chartInstance->c1_Counter_Sample_Current;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
            }

            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 140U, chartInstance->c1_sfEvent);
            c1_d2 = *chartInstance->c1_Index_vector;
            if (c1_d2 < 2.147483648E+9) {
              if (CV_SATURATION_EVAL(5, 140U, 0, 1, c1_d2 >= -2.147483648E+9)) {
                c1_i17 = (int32_T)c1_d2;
              } else {
                c1_i17 = MIN_int32_T;
              }
            } else if (CV_SATURATION_EVAL(5, 140U, 0, 0, c1_d2 >= 2.147483648E+9))
            {
              c1_i17 = MAX_int32_T;
            } else {
              c1_i17 = 0;
            }

            c1_d3 = *chartInstance->c1_Current_Read_Average;
            if (c1_d3 < 32768.0) {
              if (CV_SATURATION_EVAL(5, 140U, 1, 1, c1_d3 >= -32768.0)) {
                c1_i18 = (int16_T)c1_d3;
              } else {
                c1_i18 = MIN_int16_T;
              }
            } else if (CV_SATURATION_EVAL(5, 140U, 1, 0, c1_d3 >= 32768.0)) {
              c1_i18 = MAX_int16_T;
            } else {
              c1_i18 = 0;
            }

            (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
              [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i17, 0, 99, 1, 0)] = c1_i18;
            for (c1_i19 = 0; c1_i19 < 100; c1_i19++) {
              _SFD_DATA_RANGE_CHECK((real_T)
                                    (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                                    [c1_i19], 16U);
            }

            c1_Check_Min_Threshold(chartInstance);
            chartInstance->c1_Current_Read = 0.0;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
            chartInstance->c1_Counter_Sample_Current = 0.0;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
            (*chartInstance->c1_Index_vector)++;
            _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 135U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 136U, chartInstance->c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c1_sfEvent);
      break;

     case c1_IN_WRITE_MAP_FORWARD:
      CV_CHART_EVAL(0, 0, 5);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U,
                   chartInstance->c1_sfEvent);
      c1_e_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0,
        CV_RELATIONAL_EVAL(5U, 2U, 0, *chartInstance->c1_Write_Map, (real_T)
                           APSA_NOT_ACTIVE, -1, 0U, *chartInstance->c1_Write_Map
                           == (real_T)APSA_NOT_ACTIVE) != 0U,
        chartInstance->c1_sfEvent)) != 0);
      if (c1_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_WRITE_MAP_FORWARD = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_APSA = c1_IN_IDLE;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_IDLE = 1U;
        *chartInstance->c1_Antipinch_Active = (real_T)APSA_NOT_ACTIVE;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 84U,
                     chartInstance->c1_sfEvent);
        c1_d_temp = (_SFD_CCP_CALL(84U, 0, CV_RELATIONAL_EVAL(5U, 84U, 0,
          *chartInstance->c1_Write_Map, (real_T)APSA_ACTIVE, -1, 0U,
          *chartInstance->c1_Write_Map == (real_T)APSA_ACTIVE) != 0U,
          chartInstance->c1_sfEvent) != 0);
        if (c1_d_temp) {
          c1_d_temp = (_SFD_CCP_CALL(84U, 1, CV_RELATIONAL_EVAL(5U, 84U, 1,
            *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_BACKWARD, -1, 0U,
            *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_BACKWARD) != 0U,
            chartInstance->c1_sfEvent) != 0);
        }

        c1_f_out = (CV_TRANSITION_EVAL(84U, (int32_T)c1_d_temp) != 0);
        if (c1_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 84U, chartInstance->c1_sfEvent);
          for (c1_i20 = 0; c1_i20 < 100; c1_i20++) {
            (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i20] = 0;
          }

          for (c1_i21 = 0; c1_i21 < 100; c1_i21++) {
            _SFD_DATA_RANGE_CHECK((real_T)
                                  (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                                  [c1_i21], 16U);
          }

          chartInstance->c1_tp_WRITE_MAP_FORWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_c1_APSA = c1_IN_WRITE_MAP_BACKWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WRITE_MAP_BACKWARD = 1U;
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Backward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          chartInstance->c1_Current_Read = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
          chartInstance->c1_Counter_Sample_Current = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U,
                       chartInstance->c1_sfEvent);
          c1_e_temp = (_SFD_CCP_CALL(6U, 0, CV_RELATIONAL_EVAL(5U, 6U, 0,
            *chartInstance->c1_Hall_Counter_Forward,
            *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment +
            chartInstance->c1_Lenght_Segment, -1, 5U,
            *chartInstance->c1_Hall_Counter_Forward >=
            *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment +
            chartInstance->c1_Lenght_Segment) != 0U, chartInstance->c1_sfEvent)
                       != 0);
          if (c1_e_temp) {
            c1_e_temp = (_SFD_CCP_CALL(6U, 1, CV_RELATIONAL_EVAL(5U, 6U, 1,
              *chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1), -1,
              3U, *chartInstance->c1_Index_vector <= (real_T)(MAX_NUM_ELEMENT -
              1)) != 0U, chartInstance->c1_sfEvent) != 0);
          }

          c1_g_out = (CV_TRANSITION_EVAL(6U, (int32_T)c1_e_temp) != 0);
          if (c1_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 156U,
                         chartInstance->c1_sfEvent);
            c1_f_temp = (_SFD_CCP_CALL(156U, 0, CV_RELATIONAL_EVAL(5U, 156U, 0,
              chartInstance->c1_Counter_Sample_Current, 0.0, -1, 0U,
              chartInstance->c1_Counter_Sample_Current == 0.0) != 0U,
              chartInstance->c1_sfEvent) != 0);
            if (!c1_f_temp) {
              c1_f_temp = (_SFD_CCP_CALL(156U, 1, CV_RELATIONAL_EVAL(5U, 156U, 1,
                chartInstance->c1_Current_Read, 0.0, -1, 0U,
                chartInstance->c1_Current_Read == 0.0) != 0U,
                chartInstance->c1_sfEvent) != 0);
            }

            c1_h_out = (CV_TRANSITION_EVAL(156U, (int32_T)c1_f_temp) != 0);
            if (c1_h_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 156U,
                           chartInstance->c1_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 157U,
                           chartInstance->c1_sfEvent);
              *chartInstance->c1_Current_Read_Average =
                *chartInstance->c1_Current;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 158U,
                           chartInstance->c1_sfEvent);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 155U,
                           chartInstance->c1_sfEvent);
              *chartInstance->c1_Current_Read_Average =
                chartInstance->c1_Current_Read /
                chartInstance->c1_Counter_Sample_Current;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
            }

            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 159U, chartInstance->c1_sfEvent);
            c1_d4 = *chartInstance->c1_Index_vector;
            if (c1_d4 < 2.147483648E+9) {
              if (CV_SATURATION_EVAL(5, 159U, 0, 1, c1_d4 >= -2.147483648E+9)) {
                c1_i22 = (int32_T)c1_d4;
              } else {
                c1_i22 = MIN_int32_T;
              }
            } else if (CV_SATURATION_EVAL(5, 159U, 0, 0, c1_d4 >= 2.147483648E+9))
            {
              c1_i22 = MAX_int32_T;
            } else {
              c1_i22 = 0;
            }

            c1_d5 = *chartInstance->c1_Current_Read_Average;
            if (c1_d5 < 65536.0) {
              if (CV_SATURATION_EVAL(5, 159U, 1, 1, c1_d5 >= 0.0)) {
                c1_u1 = (uint16_T)c1_d5;
              } else {
                c1_u1 = 0U;
              }
            } else if (CV_SATURATION_EVAL(5, 159U, 1, 0, c1_d5 >= 65536.0)) {
              c1_u1 = MAX_uint16_T;
            } else {
              c1_u1 = 0U;
            }

            (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
              [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i22, 0, 99, 1, 0)] = c1_u1;
            for (c1_i23 = 0; c1_i23 < 100; c1_i23++) {
              _SFD_DATA_RANGE_CHECK((real_T)
                                    (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                    [c1_i23], 15U);
            }

            c1_Check_Min_Threshold(chartInstance);
            chartInstance->c1_Current_Read = 0.0;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
            chartInstance->c1_Counter_Sample_Current = 0.0;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
            (*chartInstance->c1_Index_vector)++;
            _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
        }
      }

      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c1_sfEvent);
      break;

     default:
      CV_CHART_EVAL(0, 0, 0);
      chartInstance->c1_is_c1_APSA = c1_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_APSA(SFc1_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c1_IDLE(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_out;
  int32_T c1_i24;
  int32_T c1_i25;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_b_out;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_c_out;
  int32_T c1_i26;
  int32_T c1_i27;
  boolean_T c1_g_temp;
  boolean_T c1_h_temp;
  boolean_T c1_d_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 86U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(86U, 0, CV_RELATIONAL_EVAL(5U, 86U, 0,
    *chartInstance->c1_Write_Map, (real_T)APSA_ACTIVE, -1, 0U,
    *chartInstance->c1_Write_Map == (real_T)APSA_ACTIVE) != 0U,
              chartInstance->c1_sfEvent) != 0);
  if (c1_temp) {
    c1_temp = (_SFD_CCP_CALL(86U, 1, CV_RELATIONAL_EVAL(5U, 86U, 1,
      *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_BACKWARD, -1, 0U,
      *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_BACKWARD) != 0U,
                chartInstance->c1_sfEvent) != 0);
  }

  c1_b_temp = c1_temp;
  if (c1_b_temp) {
    c1_b_temp = (_SFD_CCP_CALL(86U, 2, CV_RELATIONAL_EVAL(5U, 86U, 2,
      *chartInstance->c1_Enable_APSA, (real_T)APSA_ACTIVE, -1, 0U,
      *chartInstance->c1_Enable_APSA == (real_T)APSA_ACTIVE) != 0U,
      chartInstance->c1_sfEvent) != 0);
  }

  c1_out = (CV_TRANSITION_EVAL(86U, (int32_T)c1_b_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 86U, chartInstance->c1_sfEvent);
    c1_Calculate_Lenght_Segment(chartInstance);
    for (c1_i24 = 0; c1_i24 < 100; c1_i24++) {
      (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i24] = 0;
    }

    for (c1_i25 = 0; c1_i25 < 100; c1_i25++) {
      _SFD_DATA_RANGE_CHECK((real_T)
                            (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                            [c1_i25], 16U);
    }

    chartInstance->c1_tp_IDLE = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_APSA = c1_IN_WRITE_MAP_BACKWARD;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_WRITE_MAP_BACKWARD = 1U;
    *chartInstance->c1_Index_vector = *chartInstance->c1_Hall_Counter_Backward /
      chartInstance->c1_Lenght_Segment;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
    chartInstance->c1_Current_Read = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
    chartInstance->c1_Counter_Sample_Current = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U, chartInstance->c1_sfEvent);
    c1_c_temp = (_SFD_CCP_CALL(3U, 0, CV_RELATIONAL_EVAL(5U, 3U, 0,
      *chartInstance->c1_Check_Antipinch, (real_T)APSA_ACTIVE, -1, 0U,
      *chartInstance->c1_Check_Antipinch == (real_T)APSA_ACTIVE) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_c_temp) {
      c1_c_temp = (_SFD_CCP_CALL(3U, 1, CV_RELATIONAL_EVAL(5U, 3U, 1,
        *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_FORWARD, -1, 0U,
        *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_FORWARD) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_d_temp = c1_c_temp;
    if (c1_d_temp) {
      c1_d_temp = (_SFD_CCP_CALL(3U, 2, CV_RELATIONAL_EVAL(5U, 3U, 2,
        *chartInstance->c1_Enable_APSA, (real_T)APSA_ACTIVE, -1, 0U,
        *chartInstance->c1_Enable_APSA == (real_T)APSA_ACTIVE) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(3U, (int32_T)c1_d_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_IDLE = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_c1_APSA = c1_IN_ANTIPINCH_ACTIVE_FORWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 1U;
      chartInstance->c1_Inrush_time = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD =
        c1_IN_WAIT_INRUSH_TIME_FORWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 1U;
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U,
                   chartInstance->c1_sfEvent);
      c1_e_temp = (_SFD_CCP_CALL(1U, 0, CV_RELATIONAL_EVAL(5U, 1U, 0,
        *chartInstance->c1_Write_Map, (real_T)APSA_ACTIVE, -1, 0U,
        *chartInstance->c1_Write_Map == (real_T)APSA_ACTIVE) != 0U,
        chartInstance->c1_sfEvent) != 0);
      if (c1_e_temp) {
        c1_e_temp = (_SFD_CCP_CALL(1U, 1, CV_RELATIONAL_EVAL(5U, 1U, 1,
          *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_FORWARD, -1, 0U,
          *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_FORWARD) != 0U,
          chartInstance->c1_sfEvent) != 0);
      }

      c1_f_temp = c1_e_temp;
      if (c1_f_temp) {
        c1_f_temp = (_SFD_CCP_CALL(1U, 2, CV_RELATIONAL_EVAL(5U, 1U, 2,
          *chartInstance->c1_Enable_APSA, (real_T)APSA_ACTIVE, -1, 0U,
          *chartInstance->c1_Enable_APSA == (real_T)APSA_ACTIVE) != 0U,
          chartInstance->c1_sfEvent) != 0);
      }

      c1_c_out = (CV_TRANSITION_EVAL(1U, (int32_T)c1_f_temp) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        for (c1_i26 = 0; c1_i26 < 100; c1_i26++) {
          (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i26] = 0U;
        }

        for (c1_i27 = 0; c1_i27 < 100; c1_i27++) {
          _SFD_DATA_RANGE_CHECK((real_T)
                                (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                [c1_i27], 15U);
        }

        chartInstance->c1_tp_IDLE = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_c1_APSA = c1_IN_WRITE_MAP_FORWARD;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_WRITE_MAP_FORWARD = 1U;
        *chartInstance->c1_Index_vector =
          *chartInstance->c1_Hall_Counter_Forward /
          chartInstance->c1_Lenght_Segment;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
        chartInstance->c1_Current_Read = 0.0;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
        chartInstance->c1_Counter_Sample_Current = 0.0;
        _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
      } else {
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 83U,
                     chartInstance->c1_sfEvent);
        c1_g_temp = (_SFD_CCP_CALL(83U, 0, CV_RELATIONAL_EVAL(5U, 83U, 0,
          *chartInstance->c1_Check_Antipinch, (real_T)APSA_ACTIVE, -1, 0U,
          *chartInstance->c1_Check_Antipinch == (real_T)APSA_ACTIVE) != 0U,
          chartInstance->c1_sfEvent) != 0);
        if (c1_g_temp) {
          c1_g_temp = (_SFD_CCP_CALL(83U, 1, CV_RELATIONAL_EVAL(5U, 83U, 1,
            *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_BACKWARD, -1, 0U,
            *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_BACKWARD) != 0U,
            chartInstance->c1_sfEvent) != 0);
        }

        c1_h_temp = c1_g_temp;
        if (c1_h_temp) {
          c1_h_temp = (_SFD_CCP_CALL(83U, 2, CV_RELATIONAL_EVAL(5U, 83U, 2,
            *chartInstance->c1_Enable_APSA, (real_T)APSA_ACTIVE, -1, 0U,
            *chartInstance->c1_Enable_APSA == (real_T)APSA_ACTIVE) != 0U,
            chartInstance->c1_sfEvent) != 0);
        }

        c1_d_out = (CV_TRANSITION_EVAL(83U, (int32_T)c1_h_temp) != 0);
        if (c1_d_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 83U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_IDLE = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_c1_APSA = c1_IN_ANTIPINCH_ACTIVE_BACKWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 1U;
          chartInstance->c1_Inrush_time = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 96U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD =
            c1_IN_WAIT_INRUSH_TIME_BACKWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 1U;
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                       chartInstance->c1_sfEvent);
        }
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c1_sfEvent);
}

static void c1_ANTIPINCH_ACTIVE_FORWARD(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  boolean_T c1_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  real_T c1_d6;
  uint16_T c1_u2;
  real_T c1_d7;
  int16_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  boolean_T c1_d_out;
  boolean_T c1_b_temp;
  boolean_T c1_e_out;
  real_T c1_d8;
  uint16_T c1_u3;
  real_T c1_d9;
  int32_T c1_i32;
  boolean_T c1_f_out;
  boolean_T c1_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 4U, chartInstance->c1_sfEvent);
  c1_out = (CV_TRANSITION_EVAL(4U, (int32_T)_SFD_CCP_CALL(4U, 0,
              CV_RELATIONAL_EVAL(5U, 4U, 0, *chartInstance->c1_Check_Antipinch,
               (real_T)APSA_NOT_ACTIVE, -1, 0U,
    *chartInstance->c1_Check_Antipinch == (real_T)APSA_NOT_ACTIVE) != 0U,
              chartInstance->c1_sfEvent)) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    c1_exit_internal_ANTIPINCH_ACTIVE_FORWARD(chartInstance);
    chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_APSA = c1_IN_IDLE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_IDLE = 1U;
    *chartInstance->c1_Antipinch_Active = (real_T)APSA_NOT_ACTIVE;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 88U,
                 chartInstance->c1_sfEvent);
    c1_temp = (_SFD_CCP_CALL(88U, 0, CV_RELATIONAL_EVAL(5U, 88U, 0,
      *chartInstance->c1_Check_Antipinch, (real_T)APSA_ACTIVE, -1, 0U,
      *chartInstance->c1_Check_Antipinch == (real_T)APSA_ACTIVE) != 0U,
                chartInstance->c1_sfEvent) != 0);
    if (c1_temp) {
      c1_temp = (_SFD_CCP_CALL(88U, 1, CV_RELATIONAL_EVAL(5U, 88U, 1,
        *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_BACKWARD, -1, 0U,
        *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_BACKWARD) != 0U,
                  chartInstance->c1_sfEvent) != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(88U, (int32_T)c1_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 88U, chartInstance->c1_sfEvent);
      c1_exit_internal_ANTIPINCH_ACTIVE_FORWARD(chartInstance);
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_c1_APSA = c1_IN_ANTIPINCH_ACTIVE_BACKWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 1U;
      chartInstance->c1_Inrush_time = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 96U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD =
        c1_IN_WAIT_INRUSH_TIME_BACKWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c1_sfEvent);
      switch (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD) {
       case c1_IN_CHECK_ANTIPINCH_FORWARD:
        CV_STATE_EVAL(4, 0, 1);
        c1_CHECK_ANTIPINCH_FORWARD(chartInstance);
        break;

       case c1_IN_WAIT_ADAPTATION_TIME_FORWARD:
        CV_STATE_EVAL(4, 0, 2);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 27U,
                     chartInstance->c1_sfEvent);
        c1_c_out = (CV_TRANSITION_EVAL(27U, (int32_T)_SFD_CCP_CALL(27U, 0,
          CV_RELATIONAL_EVAL(5U, 27U, 0, chartInstance->c1_Inrush_time, (real_T)
                             ADAPTATION_TIME, -1, 5U,
                             chartInstance->c1_Inrush_time >= (real_T)
                             ADAPTATION_TIME) != 0U, chartInstance->c1_sfEvent))
                    != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c1_sfEvent);
          c1_d6 = (real_T)chartInstance->c1_Average_Current /
            chartInstance->c1_Segments_Cnt;
          if (c1_d6 < 65536.0) {
            if (CV_SATURATION_EVAL(5, 27, 2, 1, c1_d6 >= 0.0)) {
              c1_u2 = (uint16_T)c1_d6;
            } else {
              c1_u2 = 0U;
            }
          } else if (CV_SATURATION_EVAL(5, 27, 2, 0, c1_d6 >= 65536.0)) {
            c1_u2 = MAX_uint16_T;
          } else {
            c1_u2 = 0U;
          }

          chartInstance->c1_Average_Current = c1_u2;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current, 19U);
          chartInstance->c1_Avarage_EERAM_Current_Map /=
            chartInstance->c1_Segments_Cnt;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map, 18U);
          c1_d7 = (real_T)chartInstance->c1_Average_Current -
            chartInstance->c1_Avarage_EERAM_Current_Map;
          if (c1_d7 < 32768.0) {
            if (CV_SATURATION_EVAL(5, 27, 0, 1, c1_d7 >= -32768.0)) {
              c1_i28 = (int16_T)c1_d7;
            } else {
              c1_i28 = MIN_int16_T;
            }
          } else if (CV_SATURATION_EVAL(5, 27, 0, 0, c1_d7 >= 32768.0)) {
            c1_i28 = MAX_int16_T;
          } else {
            c1_i28 = 0;
          }

          chartInstance->c1_Averege_Difference = c1_i28;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Averege_Difference,
                                22U);
          for (c1_i29 = 0; c1_i29 < 100; c1_i29++) {
            c1_i30 = (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i29]
              + chartInstance->c1_Averege_Difference;
            if (CV_SATURATION_EVAL(5, 27, 1, 0, c1_i30 < 0)) {
              c1_i30 = 0;
            } else {
              if (c1_i30 > 65535) {
                c1_i30 = 65535;
              }
            }

            (*chartInstance->c1_EERAM_Current_Map_Forward_Write)[c1_i29] =
              (uint16_T)c1_i30;
          }

          for (c1_i31 = 0; c1_i31 < 100; c1_i31++) {
            _SFD_DATA_RANGE_CHECK((real_T)
                                  (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                  [c1_i31], 15U);
          }

          chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD =
            c1_IN_CHECK_ANTIPINCH_FORWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_CHECK_ANTIPINCH_FORWARD = 1U;
          *chartInstance->c1_cnt_antipinch = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Forward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          chartInstance->c1_Current_Read = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
          chartInstance->c1_Counter_Sample_Current = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 18U,
                       chartInstance->c1_sfEvent);
          c1_d_out = (CV_TRANSITION_EVAL(18U, (int32_T)_SFD_CCP_CALL(18U, 0,
            CV_RELATIONAL_EVAL(5U, 18U, 0, chartInstance->c1_Inrush_time,
                               (real_T)ADAPTATION_TIME, -1, 2U,
                               chartInstance->c1_Inrush_time < (real_T)
                               ADAPTATION_TIME) != 0U, chartInstance->c1_sfEvent))
                      != 0);
          if (c1_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c1_sfEvent);
            chartInstance->c1_Inrush_time++;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 24U,
                         chartInstance->c1_sfEvent);
            c1_b_temp = (_SFD_CCP_CALL(24U, 0, CV_RELATIONAL_EVAL(5U, 24U, 0,
              *chartInstance->c1_Hall_Counter_Forward,
              *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment
              + chartInstance->c1_Lenght_Segment, -1, 5U,
              *chartInstance->c1_Hall_Counter_Forward >=
              *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment
              + chartInstance->c1_Lenght_Segment) != 0U,
              chartInstance->c1_sfEvent) != 0);
            if (c1_b_temp) {
              c1_b_temp = (_SFD_CCP_CALL(24U, 1, CV_RELATIONAL_EVAL(5U, 24U, 1, *
                chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1),
                -1, 3U, *chartInstance->c1_Index_vector <= (real_T)
                (MAX_NUM_ELEMENT - 1)) != 0U, chartInstance->c1_sfEvent) != 0);
            }

            c1_e_out = (CV_TRANSITION_EVAL(24U, (int32_T)c1_b_temp) != 0);
            if (c1_e_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c1_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c1_sfEvent);
              c1_d8 = (real_T)chartInstance->c1_Average_Current +
                *chartInstance->c1_Current;
              if (c1_d8 < 65536.0) {
                if (CV_SATURATION_EVAL(5, 26, 0, 1, c1_d8 >= 0.0)) {
                  c1_u3 = (uint16_T)c1_d8;
                } else {
                  c1_u3 = 0U;
                }
              } else if (CV_SATURATION_EVAL(5, 26, 0, 0, c1_d8 >= 65536.0)) {
                c1_u3 = MAX_uint16_T;
              } else {
                c1_u3 = 0U;
              }

              chartInstance->c1_Average_Current = c1_u3;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current,
                                    19U);
              c1_d9 = *chartInstance->c1_Index_vector;
              if (c1_d9 < 2.147483648E+9) {
                if (CV_SATURATION_EVAL(5, 26, 1, 1, c1_d9 >= -2.147483648E+9)) {
                  c1_i32 = (int32_T)c1_d9;
                } else {
                  c1_i32 = MIN_int32_T;
                }
              } else if (CV_SATURATION_EVAL(5, 26, 1, 0, c1_d9 >= 2.147483648E+9))
              {
                c1_i32 = MAX_int32_T;
              } else {
                c1_i32 = 0;
              }

              chartInstance->c1_Avarage_EERAM_Current_Map +=
                (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
                [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i32, 0, 99, 1, 0)];
              _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map,
                                    18U);
              (*chartInstance->c1_Index_vector)++;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
              chartInstance->c1_Segments_Cnt++;
              _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U,
                100.0);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c1_sfEvent);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 167U,
                           chartInstance->c1_sfEvent);
            }

            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c1_sfEvent);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c1_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_WAIT_INRUSH_TIME_FORWARD:
        CV_STATE_EVAL(4, 0, 3);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                     chartInstance->c1_sfEvent);
        c1_f_out = (CV_TRANSITION_EVAL(23U, (int32_T)_SFD_CCP_CALL(23U, 0,
          CV_RELATIONAL_EVAL(5U, 23U, 0, chartInstance->c1_Inrush_time, (real_T)
                             INRUSH_TIME, -1, 5U, chartInstance->c1_Inrush_time >=
                             (real_T)INRUSH_TIME) != 0U,
          chartInstance->c1_sfEvent)) != 0);
        if (c1_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD =
            c1_IN_WAIT_ADAPTATION_TIME_FORWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 1U;
          chartInstance->c1_Average_Current = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current, 19U);
          chartInstance->c1_Avarage_EERAM_Current_Map = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map, 18U);
          chartInstance->c1_Averege_Difference = 0;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Averege_Difference,
                                22U);
          chartInstance->c1_Segments_Cnt = 0.0;
          _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U, 100.0);
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Forward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 7U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 12U,
                       chartInstance->c1_sfEvent);
          c1_g_out = (CV_TRANSITION_EVAL(12U, (int32_T)_SFD_CCP_CALL(12U, 0,
            CV_RELATIONAL_EVAL(5U, 12U, 0, chartInstance->c1_Inrush_time,
                               (real_T)(INRUSH_TIME + 5), -1, 2U,
                               chartInstance->c1_Inrush_time < (real_T)
                               (INRUSH_TIME + 5)) != 0U,
            chartInstance->c1_sfEvent)) != 0);
          if (c1_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
            chartInstance->c1_Inrush_time++;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c1_sfEvent);
        break;

       default:
        CV_STATE_EVAL(4, 0, 0);
        chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
}

static void c1_exit_internal_ANTIPINCH_ACTIVE_FORWARD(SFc1_APSAInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD) {
   case c1_IN_CHECK_ANTIPINCH_FORWARD:
    CV_STATE_EVAL(4, 1, 1);
    chartInstance->c1_tp_CHECK_ANTIPINCH_FORWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_WAIT_ADAPTATION_TIME_FORWARD:
    CV_STATE_EVAL(4, 1, 2);
    chartInstance->c1_tp_WAIT_ADAPTATION_TIME_FORWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_WAIT_INRUSH_TIME_FORWARD:
    CV_STATE_EVAL(4, 1, 3);
    chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(4, 1, 0);
    chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    break;
  }
}

static void c1_CHECK_ANTIPINCH_FORWARD(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_out;
  real_T c1_d10;
  int32_T c1_i33;
  real_T c1_d11;
  int32_T c1_i34;
  real_T c1_d12;
  int32_T c1_i35;
  boolean_T c1_b_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_c_temp;
  boolean_T c1_d_out;
  real_T c1_d13;
  int32_T c1_i36;
  real_T c1_d14;
  int32_T c1_i37;
  real_T c1_d15;
  uint16_T c1_u4;
  int32_T c1_i38;
  boolean_T c1_d_temp;
  real_T c1_d16;
  int32_T c1_i39;
  real_T c1_d17;
  boolean_T c1_e_out;
  real_T c1_d18;
  int32_T c1_i40;
  real_T c1_d19;
  int32_T c1_i41;
  real_T c1_d20;
  uint16_T c1_u5;
  int32_T c1_i42;
  real_T c1_d21;
  int32_T c1_i43;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_f_out;
  real_T c1_d22;
  int32_T c1_i44;
  real_T c1_d23;
  int32_T c1_i45;
  real_T c1_d24;
  uint16_T c1_u6;
  int32_T c1_i46;
  boolean_T c1_g_temp;
  real_T c1_d25;
  int32_T c1_i47;
  real_T c1_d26;
  boolean_T c1_h_temp;
  boolean_T c1_g_out;
  real_T c1_d27;
  int32_T c1_i48;
  real_T c1_d28;
  int32_T c1_i49;
  real_T c1_d29;
  uint16_T c1_u7;
  int32_T c1_i50;
  boolean_T c1_h_out;
  boolean_T c1_i_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 40U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 41U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(41U, 0, CV_RELATIONAL_EVAL(5U, 41U, 0,
    *chartInstance->c1_Hall_Counter_Forward, *chartInstance->c1_Index_vector *
    chartInstance->c1_Lenght_Segment + chartInstance->c1_Lenght_Segment, -1, 5U,
    *chartInstance->c1_Hall_Counter_Forward >= *chartInstance->c1_Index_vector *
    chartInstance->c1_Lenght_Segment + chartInstance->c1_Lenght_Segment) != 0U,
              chartInstance->c1_sfEvent) != 0);
  if (c1_temp) {
    c1_temp = (_SFD_CCP_CALL(41U, 1, CV_RELATIONAL_EVAL(5U, 41U, 1,
      *chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1), -1, 3U,
      *chartInstance->c1_Index_vector <= (real_T)(MAX_NUM_ELEMENT - 1)) != 0U,
                chartInstance->c1_sfEvent) != 0);
  }

  c1_out = (CV_TRANSITION_EVAL(41U, (int32_T)c1_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 41U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 165U, chartInstance->c1_sfEvent);
    *chartInstance->c1_Current_Read_Average = *chartInstance->c1_Current;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 163U, chartInstance->c1_sfEvent);
    c1_d10 = *chartInstance->c1_Index_vector;
    if (c1_d10 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 163U, 2, 1, c1_d10 >= -2.147483648E+9)) {
        c1_i33 = (int32_T)c1_d10;
      } else {
        c1_i33 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 163U, 2, 0, c1_d10 >= 2.147483648E+9)) {
      c1_i33 = MAX_int32_T;
    } else {
      c1_i33 = 0;
    }

    *chartInstance->c1_Delta_Current_actual =
      *chartInstance->c1_Current_Read_Average -
      (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i33, 0, 99, 1, 0)];
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_actual, 37U);
    c1_d11 = *chartInstance->c1_Index_vector;
    if (c1_d11 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 163U, 0, 1, c1_d11 >= -2.147483648E+9)) {
        c1_i34 = (int32_T)c1_d11;
      } else {
        c1_i34 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 163U, 0, 0, c1_d11 >= 2.147483648E+9)) {
      c1_i34 = MAX_int32_T;
    } else {
      c1_i34 = 0;
    }

    *chartInstance->c1_Threshold_Attention_Update =
      (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i34, 0, 99, 1, 0)] *
      *chartInstance->c1_EERAM_Threshold_Attention_Forward / 100.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_Attention_Update, 35U);
    c1_d12 = *chartInstance->c1_Index_vector;
    if (c1_d12 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 163U, 1, 1, c1_d12 >= -2.147483648E+9)) {
        c1_i35 = (int32_T)c1_d12;
      } else {
        c1_i35 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 163U, 1, 0, c1_d12 >= 2.147483648E+9)) {
      c1_i35 = MAX_int32_T;
    } else {
      c1_i35 = 0;
    }

    *chartInstance->c1_Threshold_AntiPinch_Update =
      (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i35, 0, 99, 1, 0)] *
      *chartInstance->c1_EERAM_Threshold_Antipinch_Forward / 100.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_AntiPinch_Update, 34U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 43U,
                 chartInstance->c1_sfEvent);
    c1_b_temp = (_SFD_CCP_CALL(43U, 0, CV_RELATIONAL_EVAL(5U, 43U, 0,
      *chartInstance->c1_Delta_Current_actual,
      *chartInstance->c1_Threshold_AntiPinch_Update, -1, 4U,
      *chartInstance->c1_Delta_Current_actual >
      *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_b_temp) {
      c1_b_temp = (_SFD_CCP_CALL(43U, 1, CV_RELATIONAL_EVAL(5U, 43U, 1,
        *chartInstance->c1_cnt_antipinch, (real_T)T_ANTIPINCH, -1, 2U,
        *chartInstance->c1_cnt_antipinch < (real_T)T_ANTIPINCH) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(43U, (int32_T)c1_b_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 43U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 45U, chartInstance->c1_sfEvent);
      (*chartInstance->c1_cnt_antipinch)++;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 48U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 44U,
                   chartInstance->c1_sfEvent);
      c1_c_out = (CV_TRANSITION_EVAL(44U, (int32_T)_SFD_CCP_CALL(44U, 0,
        CV_RELATIONAL_EVAL(5U, 44U, 0, *chartInstance->c1_cnt_antipinch, 0.0, -1,
                           4U, *chartInstance->c1_cnt_antipinch > 0.0) != 0U,
        chartInstance->c1_sfEvent)) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 44U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 46U, chartInstance->c1_sfEvent);
        *chartInstance->c1_cnt_antipinch = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 49U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 47U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 50U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 51U,
                 chartInstance->c1_sfEvent);
    c1_c_temp = (_SFD_CCP_CALL(51U, 0, CV_RELATIONAL_EVAL(5U, 51U, 0,
      *chartInstance->c1_Delta_Current_actual,
      *chartInstance->c1_Threshold_Attention_Update, -1, 4U,
      *chartInstance->c1_Delta_Current_actual >
      *chartInstance->c1_Threshold_Attention_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_c_temp) {
      c1_c_temp = (_SFD_CCP_CALL(51U, 1, CV_RELATIONAL_EVAL(5U, 51U, 1,
        *chartInstance->c1_Delta_Current_actual,
        *chartInstance->c1_Threshold_AntiPinch_Update, -1, 2U,
        *chartInstance->c1_Delta_Current_actual <
        *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_d_out = (CV_TRANSITION_EVAL(51U, (int32_T)c1_c_temp) != 0);
    if (c1_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 51U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 53U, chartInstance->c1_sfEvent);
      c1_d13 = *chartInstance->c1_Index_vector;
      if (c1_d13 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 53, 1, 1, c1_d13 >= -2.147483648E+9)) {
          c1_i36 = (int32_T)c1_d13;
        } else {
          c1_i36 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 53, 1, 0, c1_d13 >= 2.147483648E+9)) {
        c1_i36 = MAX_int32_T;
      } else {
        c1_i36 = 0;
      }

      c1_d14 = *chartInstance->c1_Index_vector;
      if (c1_d14 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 53, 1, 1, c1_d14 >= -2.147483648E+9)) {
          c1_i37 = (int32_T)c1_d14;
        } else {
          c1_i37 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 53, 1, 0, c1_d14 >= 2.147483648E+9)) {
        c1_i37 = MAX_int32_T;
      } else {
        c1_i37 = 0;
      }

      c1_d15 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Forward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i37, 0, 99, 1, 0)] +
        *chartInstance->c1_Delta_Current_actual / *chartInstance->c1_DELTA_1;
      if (c1_d15 < 65536.0) {
        if (CV_SATURATION_EVAL(5, 53, 0, 1, c1_d15 >= 0.0)) {
          c1_u4 = (uint16_T)c1_d15;
        } else {
          c1_u4 = 0U;
        }
      } else if (CV_SATURATION_EVAL(5, 53, 0, 0, c1_d15 >= 65536.0)) {
        c1_u4 = MAX_uint16_T;
      } else {
        c1_u4 = 0U;
      }

      (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i36, 0, 99, 1, 0)] = c1_u4;
      for (c1_i38 = 0; c1_i38 < 100; c1_i38++) {
        _SFD_DATA_RANGE_CHECK((real_T)
                              (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                              [c1_i38], 15U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 55U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 52U,
                   chartInstance->c1_sfEvent);
      c1_d_temp = (_SFD_CCP_CALL(52U, 0, CV_RELATIONAL_EVAL(5U, 52U, 0,
        *chartInstance->c1_Delta_Current_actual,
        -*chartInstance->c1_Threshold_Attention_Update, -1, 2U,
        *chartInstance->c1_Delta_Current_actual <
        -*chartInstance->c1_Threshold_Attention_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
      if (c1_d_temp) {
        c1_d16 = *chartInstance->c1_Index_vector;
        if (c1_d16 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 52, 0, 1, c1_d16 >= -2.147483648E+9)) {
            c1_i39 = (int32_T)c1_d16;
          } else {
            c1_i39 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 52, 0, 0, c1_d16 >= 2.147483648E+9)) {
          c1_i39 = MAX_int32_T;
        } else {
          c1_i39 = 0;
        }

        c1_d17 = (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
          [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i39, 0, 99, 1, 0)];
        c1_d_temp = (_SFD_CCP_CALL(52U, 1, CV_RELATIONAL_EVAL(5U, 52U, 1, c1_d17,
                       (real_T)MIN_CURRENT_THRESHOLD, -1, 4U, c1_d17 > (real_T)
          MIN_CURRENT_THRESHOLD) != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_e_out = (CV_TRANSITION_EVAL(52U, (int32_T)c1_d_temp) != 0);
      if (c1_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 52U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 54U, chartInstance->c1_sfEvent);
        c1_d18 = *chartInstance->c1_Index_vector;
        if (c1_d18 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 54, 1, 1, c1_d18 >= -2.147483648E+9)) {
            c1_i40 = (int32_T)c1_d18;
          } else {
            c1_i40 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 54, 1, 0, c1_d18 >= 2.147483648E+9)) {
          c1_i40 = MAX_int32_T;
        } else {
          c1_i40 = 0;
        }

        c1_d19 = *chartInstance->c1_Index_vector;
        if (c1_d19 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 54, 1, 1, c1_d19 >= -2.147483648E+9)) {
            c1_i41 = (int32_T)c1_d19;
          } else {
            c1_i41 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 54, 1, 0, c1_d19 >= 2.147483648E+9)) {
          c1_i41 = MAX_int32_T;
        } else {
          c1_i41 = 0;
        }

        c1_d20 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Forward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i41, 0, 99, 1, 0)] -
          -*chartInstance->c1_Delta_Current_actual / *chartInstance->c1_DELTA_2;
        if (c1_d20 < 65536.0) {
          if (CV_SATURATION_EVAL(5, 54, 0, 1, c1_d20 >= 0.0)) {
            c1_u5 = (uint16_T)c1_d20;
          } else {
            c1_u5 = 0U;
          }
        } else if (CV_SATURATION_EVAL(5, 54, 0, 0, c1_d20 >= 65536.0)) {
          c1_u5 = MAX_uint16_T;
        } else {
          c1_u5 = 0U;
        }

        (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i40, 0, 99, 1, 0)] = c1_u5;
        for (c1_i42 = 0; c1_i42 < 100; c1_i42++) {
          _SFD_DATA_RANGE_CHECK((real_T)
                                (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                [c1_i42], 15U);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 56U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 57U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 58U, chartInstance->c1_sfEvent);
    c1_d21 = *chartInstance->c1_Index_vector + 1.0;
    if (c1_d21 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 58, 0, 1, c1_d21 >= -2.147483648E+9)) {
        c1_i43 = (int32_T)c1_d21;
      } else {
        c1_i43 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 58, 0, 0, c1_d21 >= 2.147483648E+9)) {
      c1_i43 = MAX_int32_T;
    } else {
      c1_i43 = 0;
    }

    *chartInstance->c1_Delta_Current_next = *chartInstance->c1_Current -
      (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i43, 0, 99, 1, 0)];
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_next, 36U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 59U,
                 chartInstance->c1_sfEvent);
    c1_e_temp = (_SFD_CCP_CALL(59U, 0, CV_RELATIONAL_EVAL(5U, 59U, 0,
      *chartInstance->c1_Delta_Current_next,
      *chartInstance->c1_Threshold_Attention_Update, -1, 4U,
      *chartInstance->c1_Delta_Current_next >
      *chartInstance->c1_Threshold_Attention_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_e_temp) {
      c1_e_temp = (_SFD_CCP_CALL(59U, 1, CV_RELATIONAL_EVAL(5U, 59U, 1,
        *chartInstance->c1_Delta_Current_next,
        *chartInstance->c1_Threshold_AntiPinch_Update, -1, 2U,
        *chartInstance->c1_Delta_Current_next <
        *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_f_temp = c1_e_temp;
    if (c1_f_temp) {
      c1_f_temp = (_SFD_CCP_CALL(59U, 2, CV_RELATIONAL_EVAL(5U, 59U, 2,
        *chartInstance->c1_Index_vector + 1.0, (real_T)(MAX_NUM_ELEMENT - 1), -1,
        2U, *chartInstance->c1_Index_vector + 1.0 < (real_T)(MAX_NUM_ELEMENT - 1))
        != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_f_out = (CV_TRANSITION_EVAL(59U, (int32_T)c1_f_temp) != 0);
    if (c1_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 59U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 64U, chartInstance->c1_sfEvent);
      c1_d22 = *chartInstance->c1_Index_vector + 1.0;
      if (c1_d22 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 64, 1, 1, c1_d22 >= -2.147483648E+9)) {
          c1_i44 = (int32_T)c1_d22;
        } else {
          c1_i44 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 64, 1, 0, c1_d22 >= 2.147483648E+9)) {
        c1_i44 = MAX_int32_T;
      } else {
        c1_i44 = 0;
      }

      c1_d23 = *chartInstance->c1_Index_vector + 1.0;
      if (c1_d23 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 64, 1, 1, c1_d23 >= -2.147483648E+9)) {
          c1_i45 = (int32_T)c1_d23;
        } else {
          c1_i45 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 64, 1, 0, c1_d23 >= 2.147483648E+9)) {
        c1_i45 = MAX_int32_T;
      } else {
        c1_i45 = 0;
      }

      c1_d24 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Forward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i45, 0, 99, 1, 0)] +
        *chartInstance->c1_Delta_Current_next / *chartInstance->c1_DELTA_3;
      if (c1_d24 < 65536.0) {
        if (CV_SATURATION_EVAL(5, 64, 0, 1, c1_d24 >= 0.0)) {
          c1_u6 = (uint16_T)c1_d24;
        } else {
          c1_u6 = 0U;
        }
      } else if (CV_SATURATION_EVAL(5, 64, 0, 0, c1_d24 >= 65536.0)) {
        c1_u6 = MAX_uint16_T;
      } else {
        c1_u6 = 0U;
      }

      (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i44, 0, 99, 1, 0)] = c1_u6;
      for (c1_i46 = 0; c1_i46 < 100; c1_i46++) {
        _SFD_DATA_RANGE_CHECK((real_T)
                              (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                              [c1_i46], 15U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 65U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 60U,
                   chartInstance->c1_sfEvent);
      c1_g_temp = (_SFD_CCP_CALL(60U, 0, CV_RELATIONAL_EVAL(5U, 60U, 0,
        *chartInstance->c1_Delta_Current_next,
        -*chartInstance->c1_Threshold_Attention_Update, -1, 2U,
        *chartInstance->c1_Delta_Current_next <
        -*chartInstance->c1_Threshold_Attention_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
      if (c1_g_temp) {
        c1_d25 = *chartInstance->c1_Index_vector;
        if (c1_d25 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 60, 0, 1, c1_d25 >= -2.147483648E+9)) {
            c1_i47 = (int32_T)c1_d25;
          } else {
            c1_i47 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 60, 0, 0, c1_d25 >= 2.147483648E+9)) {
          c1_i47 = MAX_int32_T;
        } else {
          c1_i47 = 0;
        }

        c1_d26 = (*chartInstance->c1_EERAM_Current_Map_Forward_Read)
          [_SFD_ARRAY_BOUNDS_CHECK(0U, c1_i47, 0, 99, 1, 0)];
        c1_g_temp = (_SFD_CCP_CALL(60U, 1, CV_RELATIONAL_EVAL(5U, 60U, 1, c1_d26,
                       (real_T)MIN_CURRENT_THRESHOLD, -1, 4U, c1_d26 > (real_T)
          MIN_CURRENT_THRESHOLD) != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_h_temp = c1_g_temp;
      if (c1_h_temp) {
        c1_h_temp = (_SFD_CCP_CALL(60U, 2, CV_RELATIONAL_EVAL(5U, 60U, 2,
          *chartInstance->c1_Index_vector + 1.0, (real_T)(MAX_NUM_ELEMENT - 1),
          -1, 2U, *chartInstance->c1_Index_vector + 1.0 < (real_T)
          (MAX_NUM_ELEMENT - 1)) != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_g_out = (CV_TRANSITION_EVAL(60U, (int32_T)c1_h_temp) != 0);
      if (c1_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 60U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 62U, chartInstance->c1_sfEvent);
        c1_d27 = *chartInstance->c1_Index_vector + 1.0;
        if (c1_d27 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 62, 1, 1, c1_d27 >= -2.147483648E+9)) {
            c1_i48 = (int32_T)c1_d27;
          } else {
            c1_i48 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 62, 1, 0, c1_d27 >= 2.147483648E+9)) {
          c1_i48 = MAX_int32_T;
        } else {
          c1_i48 = 0;
        }

        c1_d28 = *chartInstance->c1_Index_vector + 1.0;
        if (c1_d28 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 62, 1, 1, c1_d28 >= -2.147483648E+9)) {
            c1_i49 = (int32_T)c1_d28;
          } else {
            c1_i49 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 62, 1, 0, c1_d28 >= 2.147483648E+9)) {
          c1_i49 = MAX_int32_T;
        } else {
          c1_i49 = 0;
        }

        c1_d29 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Forward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i49, 0, 99, 1, 0)] -
          -*chartInstance->c1_Delta_Current_next / *chartInstance->c1_DELTA_4;
        if (c1_d29 < 65536.0) {
          if (CV_SATURATION_EVAL(5, 62, 0, 1, c1_d29 >= 0.0)) {
            c1_u7 = (uint16_T)c1_d29;
          } else {
            c1_u7 = 0U;
          }
        } else if (CV_SATURATION_EVAL(5, 62, 0, 0, c1_d29 >= 65536.0)) {
          c1_u7 = MAX_uint16_T;
        } else {
          c1_u7 = 0U;
        }

        (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(15U, c1_i48, 0, 99, 1, 0)] = c1_u7;
        for (c1_i50 = 0; c1_i50 < 100; c1_i50++) {
          _SFD_DATA_RANGE_CHECK((real_T)
                                (*chartInstance->c1_EERAM_Current_Map_Forward_Write)
                                [c1_i50], 15U);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 63U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 61U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 66U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 67U,
                 chartInstance->c1_sfEvent);
    c1_h_out = (CV_TRANSITION_EVAL(67U, (int32_T)_SFD_CCP_CALL(67U, 0,
      CV_RELATIONAL_EVAL(5U, 67U, 0, *chartInstance->c1_cnt_antipinch, (real_T)
                         T_ANTIPINCH, -1, 5U, *chartInstance->c1_cnt_antipinch >=
                         (real_T)T_ANTIPINCH) != 0U, chartInstance->c1_sfEvent))
                != 0);
    if (c1_h_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 67U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 69U, chartInstance->c1_sfEvent);
      *chartInstance->c1_Antipinch_Active = (real_T)APSA_ACTIVE;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 71U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 68U, chartInstance->c1_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 70U, chartInstance->c1_sfEvent);
    c1_Check_Min_Threshold(chartInstance);
    (*chartInstance->c1_Index_vector)++;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 152U,
                 chartInstance->c1_sfEvent);
    c1_i_out = (CV_TRANSITION_EVAL(152U, (int32_T)_SFD_CCP_CALL(152U, 0,
      CV_RELATIONAL_EVAL(5U, 152U, 0, *chartInstance->c1_cnt_antipinch, (real_T)
                         T_ANTIPINCH, -1, 4U, *chartInstance->c1_cnt_antipinch >
                         (real_T)T_ANTIPINCH) != 0U, chartInstance->c1_sfEvent))
                != 0);
    if (c1_i_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 152U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 164U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 42U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 72U, chartInstance->c1_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 151U, chartInstance->c1_sfEvent);
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 73U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
}

static void c1_ANTIPINCH_ACTIVE_BACKWARD(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  boolean_T c1_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  real_T c1_d30;
  uint16_T c1_u8;
  real_T c1_d31;
  int16_T c1_i51;
  int32_T c1_i52;
  int32_T c1_i53;
  int32_T c1_i54;
  boolean_T c1_d_out;
  boolean_T c1_b_temp;
  boolean_T c1_e_out;
  real_T c1_d32;
  uint16_T c1_u9;
  real_T c1_d33;
  int32_T c1_i55;
  boolean_T c1_f_out;
  boolean_T c1_g_out;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 82U, chartInstance->c1_sfEvent);
  c1_out = (CV_TRANSITION_EVAL(82U, (int32_T)_SFD_CCP_CALL(82U, 0,
              CV_RELATIONAL_EVAL(5U, 82U, 0, *chartInstance->c1_Check_Antipinch,
               (real_T)APSA_NOT_ACTIVE, -1, 0U,
    *chartInstance->c1_Check_Antipinch == (real_T)APSA_NOT_ACTIVE) != 0U,
              chartInstance->c1_sfEvent)) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 82U, chartInstance->c1_sfEvent);
    c1_exit_internal_ANTIPINCH_ACTIVE_BACKWARD(chartInstance);
    chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_APSA = c1_IN_IDLE;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_IDLE = 1U;
    *chartInstance->c1_Antipinch_Active = (real_T)APSA_NOT_ACTIVE;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 89U,
                 chartInstance->c1_sfEvent);
    c1_temp = (_SFD_CCP_CALL(89U, 0, CV_RELATIONAL_EVAL(5U, 89U, 0,
      *chartInstance->c1_Check_Antipinch, (real_T)APSA_ACTIVE, -1, 0U,
      *chartInstance->c1_Check_Antipinch == (real_T)APSA_ACTIVE) != 0U,
                chartInstance->c1_sfEvent) != 0);
    if (c1_temp) {
      c1_temp = (_SFD_CCP_CALL(89U, 1, CV_RELATIONAL_EVAL(5U, 89U, 1,
        *chartInstance->c1_Cmd_Motor, (real_T)APSA_CMD_FORWARD, -1, 0U,
        *chartInstance->c1_Cmd_Motor == (real_T)APSA_CMD_FORWARD) != 0U,
                  chartInstance->c1_sfEvent) != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(89U, (int32_T)c1_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 89U, chartInstance->c1_sfEvent);
      c1_exit_internal_ANTIPINCH_ACTIVE_BACKWARD(chartInstance);
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_BACKWARD = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_c1_APSA = c1_IN_ANTIPINCH_ACTIVE_FORWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_ANTIPINCH_ACTIVE_FORWARD = 1U;
      chartInstance->c1_Inrush_time = 0.0;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_ANTIPINCH_ACTIVE_FORWARD =
        c1_IN_WAIT_INRUSH_TIME_FORWARD;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_WAIT_INRUSH_TIME_FORWARD = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U,
                   chartInstance->c1_sfEvent);
      switch (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD) {
       case c1_IN_CHECK_ANTIPINCH_BACKWARD:
        CV_STATE_EVAL(0, 0, 1);
        c1_CHECK_ANTIPINCH_BACKWARD(chartInstance);
        break;

       case c1_IN_WAIT_ADAPTATION_TIME_BACKWARD:
        CV_STATE_EVAL(0, 0, 2);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 134U,
                     chartInstance->c1_sfEvent);
        c1_c_out = (CV_TRANSITION_EVAL(134U, (int32_T)_SFD_CCP_CALL(134U, 0,
          CV_RELATIONAL_EVAL(5U, 134U, 0, chartInstance->c1_Inrush_time, (real_T)
                             ADAPTATION_TIME, -1, 5U,
                             chartInstance->c1_Inrush_time >= (real_T)
                             ADAPTATION_TIME) != 0U, chartInstance->c1_sfEvent))
                    != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 134U, chartInstance->c1_sfEvent);
          c1_d30 = (real_T)chartInstance->c1_Average_Current /
            chartInstance->c1_Segments_Cnt;
          if (c1_d30 < 65536.0) {
            if (CV_SATURATION_EVAL(5, 134U, 2, 1, c1_d30 >= 0.0)) {
              c1_u8 = (uint16_T)c1_d30;
            } else {
              c1_u8 = 0U;
            }
          } else if (CV_SATURATION_EVAL(5, 134U, 2, 0, c1_d30 >= 65536.0)) {
            c1_u8 = MAX_uint16_T;
          } else {
            c1_u8 = 0U;
          }

          chartInstance->c1_Average_Current = c1_u8;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current, 19U);
          chartInstance->c1_Avarage_EERAM_Current_Map /=
            chartInstance->c1_Segments_Cnt;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map, 18U);
          c1_d31 = (real_T)chartInstance->c1_Average_Current -
            chartInstance->c1_Avarage_EERAM_Current_Map;
          if (c1_d31 < 32768.0) {
            if (CV_SATURATION_EVAL(5, 134U, 0, 1, c1_d31 >= -32768.0)) {
              c1_i51 = (int16_T)c1_d31;
            } else {
              c1_i51 = MIN_int16_T;
            }
          } else if (CV_SATURATION_EVAL(5, 134U, 0, 0, c1_d31 >= 32768.0)) {
            c1_i51 = MAX_int16_T;
          } else {
            c1_i51 = 0;
          }

          chartInstance->c1_Averege_Difference = c1_i51;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Averege_Difference,
                                22U);
          for (c1_i52 = 0; c1_i52 < 100; c1_i52++) {
            c1_i53 = (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
              [c1_i52] + chartInstance->c1_Averege_Difference;
            if (c1_i53 > 32767) {
              CV_SATURATION_EVAL(5, 134U, 1, 0, 1);
              c1_i53 = 32767;
            } else {
              if (CV_SATURATION_EVAL(5, 134U, 1, 0, c1_i53 < -32768)) {
                c1_i53 = -32768;
              }
            }

            (*chartInstance->c1_EERAM_Current_Map_Backward_Write)[c1_i52] =
              (int16_T)c1_i53;
          }

          for (c1_i54 = 0; c1_i54 < 100; c1_i54++) {
            _SFD_DATA_RANGE_CHECK((real_T)
                                  (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                                  [c1_i54], 16U);
          }

          chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD =
            c1_IN_CHECK_ANTIPINCH_BACKWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_CHECK_ANTIPINCH_BACKWARD = 1U;
          *chartInstance->c1_cnt_antipinch = 0.0;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Backward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
          chartInstance->c1_Current_Read = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
          chartInstance->c1_Counter_Sample_Current = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 147U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 145U,
                       chartInstance->c1_sfEvent);
          c1_d_out = (CV_TRANSITION_EVAL(145U, (int32_T)_SFD_CCP_CALL(145U, 0,
            CV_RELATIONAL_EVAL(5U, 145U, 0, chartInstance->c1_Inrush_time,
                               (real_T)ADAPTATION_TIME, -1, 2U,
                               chartInstance->c1_Inrush_time < (real_T)
                               ADAPTATION_TIME) != 0U, chartInstance->c1_sfEvent))
                      != 0);
          if (c1_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 145U, chartInstance->c1_sfEvent);
            chartInstance->c1_Inrush_time++;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 144U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 143U,
                         chartInstance->c1_sfEvent);
            c1_b_temp = (_SFD_CCP_CALL(143U, 0, CV_RELATIONAL_EVAL(5U, 143U, 0, *
              chartInstance->c1_Hall_Counter_Backward,
              *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment
              + chartInstance->c1_Lenght_Segment, -1, 5U,
              *chartInstance->c1_Hall_Counter_Backward >=
              *chartInstance->c1_Index_vector * chartInstance->c1_Lenght_Segment
              + chartInstance->c1_Lenght_Segment) != 0U,
              chartInstance->c1_sfEvent) != 0);
            if (c1_b_temp) {
              c1_b_temp = (_SFD_CCP_CALL(143U, 1, CV_RELATIONAL_EVAL(5U, 143U, 1,
                *chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1),
                -1, 3U, *chartInstance->c1_Index_vector <= (real_T)
                (MAX_NUM_ELEMENT - 1)) != 0U, chartInstance->c1_sfEvent) != 0);
            }

            c1_e_out = (CV_TRANSITION_EVAL(143U, (int32_T)c1_b_temp) != 0);
            if (c1_e_out) {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 143U,
                           chartInstance->c1_sfEvent);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 148U,
                           chartInstance->c1_sfEvent);
              *chartInstance->c1_Current_Read_Average =
                *chartInstance->c1_Current;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
              c1_d32 = (real_T)chartInstance->c1_Average_Current +
                *chartInstance->c1_Current_Read_Average;
              if (c1_d32 < 65536.0) {
                if (CV_SATURATION_EVAL(5, 148U, 1, 1, c1_d32 >= 0.0)) {
                  c1_u9 = (uint16_T)c1_d32;
                } else {
                  c1_u9 = 0U;
                }
              } else if (CV_SATURATION_EVAL(5, 148U, 1, 0, c1_d32 >= 65536.0)) {
                c1_u9 = MAX_uint16_T;
              } else {
                c1_u9 = 0U;
              }

              chartInstance->c1_Average_Current = c1_u9;
              _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current,
                                    19U);
              c1_d33 = *chartInstance->c1_Index_vector;
              if (c1_d33 < 2.147483648E+9) {
                if (CV_SATURATION_EVAL(5, 148U, 0, 1, c1_d33 >= -2.147483648E+9))
                {
                  c1_i55 = (int32_T)c1_d33;
                } else {
                  c1_i55 = MIN_int32_T;
                }
              } else if (CV_SATURATION_EVAL(5, 148U, 0, 0, c1_d33 >=
                          2.147483648E+9)) {
                c1_i55 = MAX_int32_T;
              } else {
                c1_i55 = 0;
              }

              chartInstance->c1_Avarage_EERAM_Current_Map +=
                (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
                [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i55, 0, 99, 1, 0)];
              _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map,
                                    18U);
              (*chartInstance->c1_Index_vector)++;
              _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
              chartInstance->c1_Segments_Cnt++;
              _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U,
                100.0);
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 149U,
                           chartInstance->c1_sfEvent);
            } else {
              _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 146U,
                           chartInstance->c1_sfEvent);
            }

            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 150U, chartInstance->c1_sfEvent);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 142U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 141U, chartInstance->c1_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c1_sfEvent);
        break;

       case c1_IN_WAIT_INRUSH_TIME_BACKWARD:
        CV_STATE_EVAL(0, 0, 3);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 97U,
                     chartInstance->c1_sfEvent);
        c1_f_out = (CV_TRANSITION_EVAL(97U, (int32_T)_SFD_CCP_CALL(97U, 0,
          CV_RELATIONAL_EVAL(5U, 97U, 0, chartInstance->c1_Inrush_time, (real_T)
                             INRUSH_TIME, -1, 5U, chartInstance->c1_Inrush_time >=
                             (real_T)INRUSH_TIME) != 0U,
          chartInstance->c1_sfEvent)) != 0);
        if (c1_f_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 97U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 0U;
          _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
          chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD =
            c1_IN_WAIT_ADAPTATION_TIME_BACKWARD;
          _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
          chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 1U;
          chartInstance->c1_Average_Current = 0U;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Average_Current, 19U);
          chartInstance->c1_Avarage_EERAM_Current_Map = 0.0;
          _SFD_DATA_RANGE_CHECK(chartInstance->c1_Avarage_EERAM_Current_Map, 18U);
          chartInstance->c1_Averege_Difference = 0;
          _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c1_Averege_Difference,
                                22U);
          chartInstance->c1_Segments_Cnt = 0.0;
          _SFD_DATA_RANGE_CHECK_MAX(chartInstance->c1_Segments_Cnt, 21U, 100.0);
          *chartInstance->c1_Index_vector =
            *chartInstance->c1_Hall_Counter_Backward /
            chartInstance->c1_Lenght_Segment;
          _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
        } else {
          _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                       chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 90U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 91U,
                       chartInstance->c1_sfEvent);
          c1_g_out = (CV_TRANSITION_EVAL(91U, (int32_T)_SFD_CCP_CALL(91U, 0,
            CV_RELATIONAL_EVAL(5U, 91U, 0, chartInstance->c1_Inrush_time,
                               (real_T)(INRUSH_TIME + 5), -1, 2U,
                               chartInstance->c1_Inrush_time < (real_T)
                               (INRUSH_TIME + 5)) != 0U,
            chartInstance->c1_sfEvent)) != 0);
          if (c1_g_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 91U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 93U, chartInstance->c1_sfEvent);
            chartInstance->c1_Inrush_time++;
            _SFD_DATA_RANGE_CHECK(chartInstance->c1_Inrush_time, 17U);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 94U, chartInstance->c1_sfEvent);
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 92U, chartInstance->c1_sfEvent);
          }

          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 95U, chartInstance->c1_sfEvent);
        }

        _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
        break;

       default:
        CV_STATE_EVAL(0, 0, 0);
        chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
        break;
      }
    }
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void c1_exit_internal_ANTIPINCH_ACTIVE_BACKWARD(SFc1_APSAInstanceStruct
  *chartInstance)
{
  switch (chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD) {
   case c1_IN_CHECK_ANTIPINCH_BACKWARD:
    CV_STATE_EVAL(0, 1, 1);
    chartInstance->c1_tp_CHECK_ANTIPINCH_BACKWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_WAIT_ADAPTATION_TIME_BACKWARD:
    CV_STATE_EVAL(0, 1, 2);
    chartInstance->c1_tp_WAIT_ADAPTATION_TIME_BACKWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_WAIT_INRUSH_TIME_BACKWARD:
    CV_STATE_EVAL(0, 1, 3);
    chartInstance->c1_tp_WAIT_INRUSH_TIME_BACKWARD = 0U;
    chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(0, 1, 0);
    chartInstance->c1_is_ANTIPINCH_ACTIVE_BACKWARD = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    break;
  }
}

static void c1_CHECK_ANTIPINCH_BACKWARD(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_out;
  real_T c1_d34;
  int32_T c1_i56;
  real_T c1_d35;
  int32_T c1_i57;
  real_T c1_d36;
  int32_T c1_i58;
  boolean_T c1_b_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_c_temp;
  real_T c1_d37;
  int32_T c1_i59;
  real_T c1_d38;
  boolean_T c1_d_out;
  real_T c1_d39;
  int32_T c1_i60;
  real_T c1_d40;
  int32_T c1_i61;
  real_T c1_d41;
  int16_T c1_i62;
  int32_T c1_i63;
  boolean_T c1_d_temp;
  boolean_T c1_e_out;
  real_T c1_d42;
  int32_T c1_i64;
  real_T c1_d43;
  int32_T c1_i65;
  real_T c1_d44;
  int16_T c1_i66;
  int32_T c1_i67;
  real_T c1_d45;
  int32_T c1_i68;
  boolean_T c1_e_temp;
  real_T c1_d46;
  int32_T c1_i69;
  real_T c1_d47;
  boolean_T c1_f_temp;
  boolean_T c1_f_out;
  real_T c1_d48;
  int32_T c1_i70;
  real_T c1_d49;
  int32_T c1_i71;
  real_T c1_d50;
  int16_T c1_i72;
  int32_T c1_i73;
  boolean_T c1_g_temp;
  boolean_T c1_h_temp;
  boolean_T c1_g_out;
  real_T c1_d51;
  int32_T c1_i74;
  real_T c1_d52;
  int32_T c1_i75;
  real_T c1_d53;
  int16_T c1_i76;
  int32_T c1_i77;
  boolean_T c1_h_out;
  boolean_T c1_i_out;
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 98U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 100U, chartInstance->c1_sfEvent);
  c1_temp = (_SFD_CCP_CALL(100U, 0, CV_RELATIONAL_EVAL(5U, 100U, 0,
    *chartInstance->c1_Hall_Counter_Backward, *chartInstance->c1_Index_vector *
    chartInstance->c1_Lenght_Segment + chartInstance->c1_Lenght_Segment, -1, 5U,
    *chartInstance->c1_Hall_Counter_Backward >= *chartInstance->c1_Index_vector *
    chartInstance->c1_Lenght_Segment + chartInstance->c1_Lenght_Segment) != 0U,
              chartInstance->c1_sfEvent) != 0);
  if (c1_temp) {
    c1_temp = (_SFD_CCP_CALL(100U, 1, CV_RELATIONAL_EVAL(5U, 100U, 1,
      *chartInstance->c1_Index_vector, (real_T)(MAX_NUM_ELEMENT - 1), -1, 3U,
      *chartInstance->c1_Index_vector <= (real_T)(MAX_NUM_ELEMENT - 1)) != 0U,
                chartInstance->c1_sfEvent) != 0);
  }

  c1_out = (CV_TRANSITION_EVAL(100U, (int32_T)c1_temp) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 100U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 166U, chartInstance->c1_sfEvent);
    *chartInstance->c1_Current_Read_Average = *chartInstance->c1_Current;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Current_Read_Average, 40U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 102U, chartInstance->c1_sfEvent);
    c1_d34 = *chartInstance->c1_Index_vector;
    if (c1_d34 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 102, 0, 1, c1_d34 >= -2.147483648E+9)) {
        c1_i56 = (int32_T)c1_d34;
      } else {
        c1_i56 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 102, 0, 0, c1_d34 >= 2.147483648E+9)) {
      c1_i56 = MAX_int32_T;
    } else {
      c1_i56 = 0;
    }

    *chartInstance->c1_Delta_Current_actual =
      *chartInstance->c1_Current_Read_Average -
      (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i56, 0, 99, 1, 0)];
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_actual, 37U);
    c1_d35 = *chartInstance->c1_Index_vector;
    if (c1_d35 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 102, 1, 1, c1_d35 >= -2.147483648E+9)) {
        c1_i57 = (int32_T)c1_d35;
      } else {
        c1_i57 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 102, 1, 0, c1_d35 >= 2.147483648E+9)) {
      c1_i57 = MAX_int32_T;
    } else {
      c1_i57 = 0;
    }

    *chartInstance->c1_Threshold_Attention_Update =
      (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i57, 0, 99, 1, 0)] *
      *chartInstance->c1_EERAM_Threshold_Attention_Backward / 100.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_Attention_Update, 35U);
    c1_d36 = *chartInstance->c1_Index_vector;
    if (c1_d36 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 102, 2, 1, c1_d36 >= -2.147483648E+9)) {
        c1_i58 = (int32_T)c1_d36;
      } else {
        c1_i58 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 102, 2, 0, c1_d36 >= 2.147483648E+9)) {
      c1_i58 = MAX_int32_T;
    } else {
      c1_i58 = 0;
    }

    *chartInstance->c1_Threshold_AntiPinch_Update =
      (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i58, 0, 99, 1, 0)] *
      *chartInstance->c1_EERAM_Threshold_Antipinch_Backward / 100.0;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Threshold_AntiPinch_Update, 34U);
    chartInstance->c1_Current_Read = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Current_Read, 38U);
    chartInstance->c1_Counter_Sample_Current = 0.0;
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Counter_Sample_Current, 39U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 103U,
                 chartInstance->c1_sfEvent);
    c1_b_temp = (_SFD_CCP_CALL(103U, 0, CV_RELATIONAL_EVAL(5U, 103U, 0,
      *chartInstance->c1_Delta_Current_actual,
      *chartInstance->c1_Threshold_AntiPinch_Update, -1, 4U,
      *chartInstance->c1_Delta_Current_actual >
      *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_b_temp) {
      c1_b_temp = (_SFD_CCP_CALL(103U, 1, CV_RELATIONAL_EVAL(5U, 103U, 1,
        *chartInstance->c1_cnt_antipinch, (real_T)T_ANTIPINCH, -1, 2U,
        *chartInstance->c1_cnt_antipinch < (real_T)T_ANTIPINCH) != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(103U, (int32_T)c1_b_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 103U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 105U, chartInstance->c1_sfEvent);
      (*chartInstance->c1_cnt_antipinch)++;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 108U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 104U,
                   chartInstance->c1_sfEvent);
      c1_c_out = (CV_TRANSITION_EVAL(104U, (int32_T)_SFD_CCP_CALL(104U, 0,
        CV_RELATIONAL_EVAL(5U, 104U, 0, *chartInstance->c1_cnt_antipinch, 0.0,
                           -1, 4U, *chartInstance->c1_cnt_antipinch > 0.0) != 0U,
        chartInstance->c1_sfEvent)) != 0);
      if (c1_c_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 104U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 107U, chartInstance->c1_sfEvent);
        *chartInstance->c1_cnt_antipinch = 0.0;
        _SFD_DATA_RANGE_CHECK(*chartInstance->c1_cnt_antipinch, 25U);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 109U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 106U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 110U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 112U,
                 chartInstance->c1_sfEvent);
    c1_c_temp = (_SFD_CCP_CALL(112U, 0, CV_RELATIONAL_EVAL(5U, 112U, 0,
      *chartInstance->c1_Delta_Current_actual,
      -*chartInstance->c1_Threshold_Attention_Update, -1, 2U,
      *chartInstance->c1_Delta_Current_actual <
      -*chartInstance->c1_Threshold_Attention_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_c_temp) {
      c1_d37 = *chartInstance->c1_Index_vector;
      if (c1_d37 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 112, 0, 1, c1_d37 >= -2.147483648E+9)) {
          c1_i59 = (int32_T)c1_d37;
        } else {
          c1_i59 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 112, 0, 0, c1_d37 >= 2.147483648E+9)) {
        c1_i59 = MAX_int32_T;
      } else {
        c1_i59 = 0;
      }

      c1_d38 = (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
        [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i59, 0, 99, 1, 0)];
      c1_c_temp = (_SFD_CCP_CALL(112U, 1, CV_RELATIONAL_EVAL(5U, 112U, 1, c1_d38,
                     (real_T)MIN_CURRENT_THRESHOLD, -1, 4U, c1_d38 > (real_T)
        MIN_CURRENT_THRESHOLD) != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_d_out = (CV_TRANSITION_EVAL(112U, (int32_T)c1_c_temp) != 0);
    if (c1_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 112U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 115U, chartInstance->c1_sfEvent);
      c1_d39 = *chartInstance->c1_Index_vector;
      if (c1_d39 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 115, 1, 1, c1_d39 >= -2.147483648E+9)) {
          c1_i60 = (int32_T)c1_d39;
        } else {
          c1_i60 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 115, 1, 0, c1_d39 >= 2.147483648E+9)) {
        c1_i60 = MAX_int32_T;
      } else {
        c1_i60 = 0;
      }

      c1_d40 = *chartInstance->c1_Index_vector;
      if (c1_d40 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 115, 1, 1, c1_d40 >= -2.147483648E+9)) {
          c1_i61 = (int32_T)c1_d40;
        } else {
          c1_i61 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 115, 1, 0, c1_d40 >= 2.147483648E+9)) {
        c1_i61 = MAX_int32_T;
      } else {
        c1_i61 = 0;
      }

      c1_d41 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i61, 0, 99, 1, 0)] -
        -*chartInstance->c1_Delta_Current_actual / *chartInstance->c1_DELTA_2;
      if (c1_d41 < 32768.0) {
        if (CV_SATURATION_EVAL(5, 115, 0, 1, c1_d41 >= -32768.0)) {
          c1_i62 = (int16_T)c1_d41;
        } else {
          c1_i62 = MIN_int16_T;
        }
      } else if (CV_SATURATION_EVAL(5, 115, 0, 0, c1_d41 >= 32768.0)) {
        c1_i62 = MAX_int16_T;
      } else {
        c1_i62 = 0;
      }

      (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i60, 0, 99, 1, 0)] = c1_i62;
      for (c1_i63 = 0; c1_i63 < 100; c1_i63++) {
        _SFD_DATA_RANGE_CHECK((real_T)
                              (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                              [c1_i63], 16U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 117U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 111U,
                   chartInstance->c1_sfEvent);
      c1_d_temp = (_SFD_CCP_CALL(111U, 0, CV_RELATIONAL_EVAL(5U, 111U, 0,
        *chartInstance->c1_Delta_Current_actual,
        *chartInstance->c1_Threshold_Attention_Update, -1, 4U,
        *chartInstance->c1_Delta_Current_actual >
        *chartInstance->c1_Threshold_Attention_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
      if (c1_d_temp) {
        c1_d_temp = (_SFD_CCP_CALL(111U, 1, CV_RELATIONAL_EVAL(5U, 111U, 1,
          *chartInstance->c1_Delta_Current_actual,
          *chartInstance->c1_Threshold_AntiPinch_Update, -1, 2U,
          *chartInstance->c1_Delta_Current_actual <
          *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
          chartInstance->c1_sfEvent) != 0);
      }

      c1_e_out = (CV_TRANSITION_EVAL(111U, (int32_T)c1_d_temp) != 0);
      if (c1_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 111U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 113U, chartInstance->c1_sfEvent);
        c1_d42 = *chartInstance->c1_Index_vector;
        if (c1_d42 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 113, 1, 1, c1_d42 >= -2.147483648E+9)) {
            c1_i64 = (int32_T)c1_d42;
          } else {
            c1_i64 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 113, 1, 0, c1_d42 >= 2.147483648E+9)) {
          c1_i64 = MAX_int32_T;
        } else {
          c1_i64 = 0;
        }

        c1_d43 = *chartInstance->c1_Index_vector;
        if (c1_d43 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 113, 1, 1, c1_d43 >= -2.147483648E+9)) {
            c1_i65 = (int32_T)c1_d43;
          } else {
            c1_i65 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 113, 1, 0, c1_d43 >= 2.147483648E+9)) {
          c1_i65 = MAX_int32_T;
        } else {
          c1_i65 = 0;
        }

        c1_d44 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Backward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i65, 0, 99, 1, 0)] +
          *chartInstance->c1_Delta_Current_actual / *chartInstance->c1_DELTA_1;
        if (c1_d44 < 32768.0) {
          if (CV_SATURATION_EVAL(5, 113, 0, 1, c1_d44 >= -32768.0)) {
            c1_i66 = (int16_T)c1_d44;
          } else {
            c1_i66 = MIN_int16_T;
          }
        } else if (CV_SATURATION_EVAL(5, 113, 0, 0, c1_d44 >= 32768.0)) {
          c1_i66 = MAX_int16_T;
        } else {
          c1_i66 = 0;
        }

        (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i64, 0, 99, 1, 0)] = c1_i66;
        for (c1_i67 = 0; c1_i67 < 100; c1_i67++) {
          _SFD_DATA_RANGE_CHECK((real_T)
                                (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                                [c1_i67], 16U);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 116U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 114U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 118U, chartInstance->c1_sfEvent);
    c1_d45 = *chartInstance->c1_Index_vector + 1.0;
    if (c1_d45 < 2.147483648E+9) {
      if (CV_SATURATION_EVAL(5, 118, 0, 1, c1_d45 >= -2.147483648E+9)) {
        c1_i68 = (int32_T)c1_d45;
      } else {
        c1_i68 = MIN_int32_T;
      }
    } else if (CV_SATURATION_EVAL(5, 118, 0, 0, c1_d45 >= 2.147483648E+9)) {
      c1_i68 = MAX_int32_T;
    } else {
      c1_i68 = 0;
    }

    *chartInstance->c1_Delta_Current_next = *chartInstance->c1_Current -
      (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
      [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i68, 0, 99, 1, 0)];
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Delta_Current_next, 36U);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 120U,
                 chartInstance->c1_sfEvent);
    c1_e_temp = (_SFD_CCP_CALL(120U, 0, CV_RELATIONAL_EVAL(5U, 120U, 0,
      *chartInstance->c1_Delta_Current_next,
      -*chartInstance->c1_Threshold_Attention_Update, -1, 2U,
      *chartInstance->c1_Delta_Current_next <
      -*chartInstance->c1_Threshold_Attention_Update) != 0U,
      chartInstance->c1_sfEvent) != 0);
    if (c1_e_temp) {
      c1_d46 = *chartInstance->c1_Index_vector;
      if (c1_d46 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 120, 0, 1, c1_d46 >= -2.147483648E+9)) {
          c1_i69 = (int32_T)c1_d46;
        } else {
          c1_i69 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 120, 0, 0, c1_d46 >= 2.147483648E+9)) {
        c1_i69 = MAX_int32_T;
      } else {
        c1_i69 = 0;
      }

      c1_d47 = (*chartInstance->c1_EERAM_Current_Map_Backward_Read)
        [_SFD_ARRAY_BOUNDS_CHECK(1U, c1_i69, 0, 99, 1, 0)];
      c1_e_temp = (_SFD_CCP_CALL(120U, 1, CV_RELATIONAL_EVAL(5U, 120U, 1, c1_d47,
                     (real_T)MIN_CURRENT_THRESHOLD, -1, 4U, c1_d47 > (real_T)
        MIN_CURRENT_THRESHOLD) != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_f_temp = c1_e_temp;
    if (c1_f_temp) {
      c1_f_temp = (_SFD_CCP_CALL(120U, 2, CV_RELATIONAL_EVAL(5U, 120U, 2,
        *chartInstance->c1_Index_vector + 1.0, (real_T)(MAX_NUM_ELEMENT - 1), -1,
        2U, *chartInstance->c1_Index_vector + 1.0 < (real_T)(MAX_NUM_ELEMENT - 1))
        != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_f_out = (CV_TRANSITION_EVAL(120U, (int32_T)c1_f_temp) != 0);
    if (c1_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 120U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 123U, chartInstance->c1_sfEvent);
      c1_d48 = *chartInstance->c1_Index_vector + 1.0;
      if (c1_d48 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 123, 1, 1, c1_d48 >= -2.147483648E+9)) {
          c1_i70 = (int32_T)c1_d48;
        } else {
          c1_i70 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 123, 1, 0, c1_d48 >= 2.147483648E+9)) {
        c1_i70 = MAX_int32_T;
      } else {
        c1_i70 = 0;
      }

      c1_d49 = *chartInstance->c1_Index_vector + 1.0;
      if (c1_d49 < 2.147483648E+9) {
        if (CV_SATURATION_EVAL(5, 123, 1, 1, c1_d49 >= -2.147483648E+9)) {
          c1_i71 = (int32_T)c1_d49;
        } else {
          c1_i71 = MIN_int32_T;
        }
      } else if (CV_SATURATION_EVAL(5, 123, 1, 0, c1_d49 >= 2.147483648E+9)) {
        c1_i71 = MAX_int32_T;
      } else {
        c1_i71 = 0;
      }

      c1_d50 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i71, 0, 99, 1, 0)] -
        -*chartInstance->c1_Delta_Current_next / *chartInstance->c1_DELTA_4;
      if (c1_d50 < 32768.0) {
        if (CV_SATURATION_EVAL(5, 123, 0, 1, c1_d50 >= -32768.0)) {
          c1_i72 = (int16_T)c1_d50;
        } else {
          c1_i72 = MIN_int16_T;
        }
      } else if (CV_SATURATION_EVAL(5, 123, 0, 0, c1_d50 >= 32768.0)) {
        c1_i72 = MAX_int16_T;
      } else {
        c1_i72 = 0;
      }

      (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
        [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i70, 0, 99, 1, 0)] = c1_i72;
      for (c1_i73 = 0; c1_i73 < 100; c1_i73++) {
        _SFD_DATA_RANGE_CHECK((real_T)
                              (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                              [c1_i73], 16U);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 125U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 119U,
                   chartInstance->c1_sfEvent);
      c1_g_temp = (_SFD_CCP_CALL(119U, 0, CV_RELATIONAL_EVAL(5U, 119U, 0,
        *chartInstance->c1_Delta_Current_next,
        *chartInstance->c1_Threshold_Attention_Update, -1, 4U,
        *chartInstance->c1_Delta_Current_next >
        *chartInstance->c1_Threshold_Attention_Update) != 0U,
        chartInstance->c1_sfEvent) != 0);
      if (c1_g_temp) {
        c1_g_temp = (_SFD_CCP_CALL(119U, 1, CV_RELATIONAL_EVAL(5U, 119U, 1,
          *chartInstance->c1_Delta_Current_next,
          *chartInstance->c1_Threshold_AntiPinch_Update, -1, 2U,
          *chartInstance->c1_Delta_Current_next <
          *chartInstance->c1_Threshold_AntiPinch_Update) != 0U,
          chartInstance->c1_sfEvent) != 0);
      }

      c1_h_temp = c1_g_temp;
      if (c1_h_temp) {
        c1_h_temp = (_SFD_CCP_CALL(119U, 2, CV_RELATIONAL_EVAL(5U, 119U, 2,
          *chartInstance->c1_Index_vector + 1.0, (real_T)(MAX_NUM_ELEMENT - 1),
          -1, 2U, *chartInstance->c1_Index_vector + 1.0 < (real_T)
          (MAX_NUM_ELEMENT - 1)) != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_g_out = (CV_TRANSITION_EVAL(119U, (int32_T)c1_h_temp) != 0);
      if (c1_g_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 119U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 121U, chartInstance->c1_sfEvent);
        c1_d51 = *chartInstance->c1_Index_vector + 1.0;
        if (c1_d51 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 121, 1, 1, c1_d51 >= -2.147483648E+9)) {
            c1_i74 = (int32_T)c1_d51;
          } else {
            c1_i74 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 121, 1, 0, c1_d51 >= 2.147483648E+9)) {
          c1_i74 = MAX_int32_T;
        } else {
          c1_i74 = 0;
        }

        c1_d52 = *chartInstance->c1_Index_vector + 1.0;
        if (c1_d52 < 2.147483648E+9) {
          if (CV_SATURATION_EVAL(5, 121, 1, 1, c1_d52 >= -2.147483648E+9)) {
            c1_i75 = (int32_T)c1_d52;
          } else {
            c1_i75 = MIN_int32_T;
          }
        } else if (CV_SATURATION_EVAL(5, 121, 1, 0, c1_d52 >= 2.147483648E+9)) {
          c1_i75 = MAX_int32_T;
        } else {
          c1_i75 = 0;
        }

        c1_d53 = (real_T)(*chartInstance->c1_EERAM_Current_Map_Backward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i75, 0, 99, 1, 0)] +
          *chartInstance->c1_Delta_Current_next / *chartInstance->c1_DELTA_3;
        if (c1_d53 < 32768.0) {
          if (CV_SATURATION_EVAL(5, 121, 0, 1, c1_d53 >= -32768.0)) {
            c1_i76 = (int16_T)c1_d53;
          } else {
            c1_i76 = MIN_int16_T;
          }
        } else if (CV_SATURATION_EVAL(5, 121, 0, 0, c1_d53 >= 32768.0)) {
          c1_i76 = MAX_int16_T;
        } else {
          c1_i76 = 0;
        }

        (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
          [_SFD_ARRAY_BOUNDS_CHECK(16U, c1_i74, 0, 99, 1, 0)] = c1_i76;
        for (c1_i77 = 0; c1_i77 < 100; c1_i77++) {
          _SFD_DATA_RANGE_CHECK((real_T)
                                (*chartInstance->c1_EERAM_Current_Map_Backward_Write)
                                [c1_i77], 16U);
        }

        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 124U, chartInstance->c1_sfEvent);
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 122U, chartInstance->c1_sfEvent);
      }
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 126U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 127U,
                 chartInstance->c1_sfEvent);
    c1_h_out = (CV_TRANSITION_EVAL(127U, (int32_T)_SFD_CCP_CALL(127U, 0,
      CV_RELATIONAL_EVAL(5U, 127U, 0, *chartInstance->c1_cnt_antipinch, (real_T)
                         T_ANTIPINCH, -1, 5U, *chartInstance->c1_cnt_antipinch >=
                         (real_T)T_ANTIPINCH) != 0U, chartInstance->c1_sfEvent))
                != 0);
    if (c1_h_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 127U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 129U, chartInstance->c1_sfEvent);
      *chartInstance->c1_Antipinch_Active = (real_T)APSA_ACTIVE;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Antipinch_Active, 30U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 130U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 128U, chartInstance->c1_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 131U, chartInstance->c1_sfEvent);
    c1_Check_Min_Threshold(chartInstance);
    (*chartInstance->c1_Index_vector)++;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Index_vector, 33U);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 153U,
                 chartInstance->c1_sfEvent);
    c1_i_out = (CV_TRANSITION_EVAL(153U, (int32_T)_SFD_CCP_CALL(153U, 0,
      CV_RELATIONAL_EVAL(5U, 153U, 0, *chartInstance->c1_cnt_antipinch, (real_T)
                         T_ANTIPINCH, -1, 5U, *chartInstance->c1_cnt_antipinch >=
                         (real_T)T_ANTIPINCH) != 0U, chartInstance->c1_sfEvent))
                != 0);
    if (c1_i_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 153U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 99U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 101U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 132U, chartInstance->c1_sfEvent);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 154U, chartInstance->c1_sfEvent);
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 133U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber, uint32_T c1_instanceNumber)
{
  (void)c1_machineNumber;
  (void)c1_chartNumber;
  (void)c1_instanceNumber;
}

const mxArray *sf_c1_APSA_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c1_nameCaptureInfo;
}

static void c1_Check_Min_Threshold(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 31U, chartInstance->c1_sfEvent);
  c1_out = (CV_TRANSITION_EVAL(31U, (int32_T)_SFD_CCP_CALL(31U, 0,
              CV_RELATIONAL_EVAL(5U, 31U, 0, *chartInstance->c1_Current, (real_T)
    MIN_CURRENT_THRESHOLD, -1, 3U, *chartInstance->c1_Current <= (real_T)
    MIN_CURRENT_THRESHOLD) != 0U, chartInstance->c1_sfEvent)) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 32U,
                 chartInstance->c1_sfEvent);
    c1_b_out = (CV_TRANSITION_EVAL(32U, (int32_T)_SFD_CCP_CALL(32U, 0,
      CV_RELATIONAL_EVAL(5U, 32U, 0, chartInstance->c1_Cnt_Fail_Sens_Current,
                         (real_T)MAX_CNT_MIN_CURRENT_THRESHOLD, -1, 4U,
                         chartInstance->c1_Cnt_Fail_Sens_Current > (real_T)
                         MAX_CNT_MIN_CURRENT_THRESHOLD) != 0U,
      chartInstance->c1_sfEvent)) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 32U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 35U, chartInstance->c1_sfEvent);
      *chartInstance->c1_Fail_Sens_Current = (real_T)APSA_TRUE;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Fail_Sens_Current, 23U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 38U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 34U, chartInstance->c1_sfEvent);
      chartInstance->c1_Cnt_Fail_Sens_Current++;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_Cnt_Fail_Sens_Current, 24U);
    }

    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 37U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 30U,
                 chartInstance->c1_sfEvent);
    c1_c_out = (CV_TRANSITION_EVAL(30U, (int32_T)_SFD_CCP_CALL(30U, 0,
      CV_RELATIONAL_EVAL(5U, 30U, 0, chartInstance->c1_Cnt_Fail_Sens_Current,
                         0.0, -1, 1U, chartInstance->c1_Cnt_Fail_Sens_Current !=
                         0.0) != 0U, chartInstance->c1_sfEvent)) != 0);
    if (c1_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 33U, chartInstance->c1_sfEvent);
      chartInstance->c1_Cnt_Fail_Sens_Current--;
      _SFD_DATA_RANGE_CHECK(chartInstance->c1_Cnt_Fail_Sens_Current, 24U);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 36U, chartInstance->c1_sfEvent);
    } else {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c1_sfEvent);
      *chartInstance->c1_Fail_Sens_Current = (real_T)APSA_FALSE;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c1_Fail_Sens_Current, 23U);
    }
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 39U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
}

static void c1_Calculate_Lenght_Segment(SFc1_APSAInstanceStruct *chartInstance)
{
  boolean_T c1_out;
  _SFD_CS_CALL(FUNCTION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 74U, chartInstance->c1_sfEvent);
  chartInstance->c1_Mod = (real_T)c1__s32d_mod__(chartInstance, (int32_T)
    *chartInstance->c1_Lenght_Motor_Stroke, (int32_T)MAX_NUM_ELEMENT);
  _SFD_DATA_RANGE_CHECK(chartInstance->c1_Mod, 20U);
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 75U, chartInstance->c1_sfEvent);
  c1_out = (CV_TRANSITION_EVAL(75U, (int32_T)_SFD_CCP_CALL(75U, 0,
              CV_RELATIONAL_EVAL(5U, 75U, 0, chartInstance->c1_Mod, 0.0, -1, 0U,
    chartInstance->c1_Mod == 0.0) != 0U, chartInstance->c1_sfEvent)) != 0);
  if (c1_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 75U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 77U, chartInstance->c1_sfEvent);
    chartInstance->c1_Lenght_Segment = (real_T)
      (*chartInstance->c1_Lenght_Motor_Stroke / MAX_NUM_ELEMENT);
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Lenght_Segment, 14U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 80U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 76U, chartInstance->c1_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 78U, chartInstance->c1_sfEvent);
    chartInstance->c1_Lenght_Segment = (real_T)
      (*chartInstance->c1_Lenght_Motor_Stroke / MAX_NUM_ELEMENT + 1);
    _SFD_DATA_RANGE_CHECK(chartInstance->c1_Lenght_Segment, 14U);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 79U, chartInstance->c1_sfEvent);
  }

  _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 81U, chartInstance->c1_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CS_CALL(FUNCTION_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int32_T c1_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i78;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i78, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i78;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint8_T c1_b_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_tp_IDLE, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_IDLE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_IDLE);
  return c1_y;
}

static uint8_T c1_c_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u10;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u10, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u10;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_tp_IDLE;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_tp_IDLE = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_tp_IDLE),
    &c1_thisId);
  sf_mex_destroy(&c1_b_tp_IDLE);
  *(uint8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i79;
  real_T c1_b_inData[100];
  int32_T c1_i80;
  real_T c1_u[100];
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i79 = 0; c1_i79 < 100; c1_i79++) {
    c1_b_inData[c1_i79] = (*(real_T (*)[100])c1_inData)[c1_i79];
  }

  for (c1_i80 = 0; c1_i80 < 100; c1_i80++) {
    c1_u[c1_i80] = c1_b_inData[c1_i80];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 100), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static real_T c1_d_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Lenght_Segment, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Lenght_Segment),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Lenght_Segment);
  return c1_y;
}

static real_T c1_e_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d54;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d54, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d54;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_Lenght_Segment;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_Lenght_Segment = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Lenght_Segment),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Lenght_Segment);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i81;
  uint16_T c1_b_inData[100];
  int32_T c1_i82;
  uint16_T c1_u[100];
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i81 = 0; c1_i81 < 100; c1_i81++) {
    c1_b_inData[c1_i81] = (*(uint16_T (*)[100])c1_inData)[c1_i81];
  }

  for (c1_i82 = 0; c1_i82 < 100; c1_i82++) {
    c1_u[c1_i82] = c1_b_inData[c1_i82];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 5, 0U, 1U, 0U, 1, 100), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_f_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_b_EERAM_Current_Map_Forward_Write, const char_T *c1_identifier,
  uint16_T c1_y[100])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c1_b_EERAM_Current_Map_Forward_Write), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_EERAM_Current_Map_Forward_Write);
}

static void c1_g_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, uint16_T c1_y[100])
{
  uint16_T c1_uv1[100];
  int32_T c1_i83;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_uv1, 1, 5, 0U, 1, 0U, 1, 100);
  for (c1_i83 = 0; c1_i83 < 100; c1_i83++) {
    c1_y[c1_i83] = c1_uv1[c1_i83];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_EERAM_Current_Map_Forward_Write;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint16_T c1_y[100];
  int32_T c1_i84;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_EERAM_Current_Map_Forward_Write = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c1_b_EERAM_Current_Map_Forward_Write), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_b_EERAM_Current_Map_Forward_Write);
  for (c1_i84 = 0; c1_i84 < 100; c1_i84++) {
    (*(uint16_T (*)[100])c1_outData)[c1_i84] = c1_y[c1_i84];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i85;
  int16_T c1_b_inData[100];
  int32_T c1_i86;
  int16_T c1_u[100];
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i85 = 0; c1_i85 < 100; c1_i85++) {
    c1_b_inData[c1_i85] = (*(int16_T (*)[100])c1_inData)[c1_i85];
  }

  for (c1_i86 = 0; c1_i86 < 100; c1_i86++) {
    c1_u[c1_i86] = c1_b_inData[c1_i86];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 4, 0U, 1U, 0U, 1, 100), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static void c1_h_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_b_EERAM_Current_Map_Backward_Write, const char_T *c1_identifier,
  int16_T c1_y[100])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c1_b_EERAM_Current_Map_Backward_Write), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_EERAM_Current_Map_Backward_Write);
}

static void c1_i_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, int16_T c1_y[100])
{
  int16_T c1_iv1[100];
  int32_T c1_i87;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_iv1, 1, 4, 0U, 1, 0U, 1, 100);
  for (c1_i87 = 0; c1_i87 < 100; c1_i87++) {
    c1_y[c1_i87] = c1_iv1[c1_i87];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_EERAM_Current_Map_Backward_Write;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int16_T c1_y[100];
  int32_T c1_i88;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_EERAM_Current_Map_Backward_Write = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup
                        (c1_b_EERAM_Current_Map_Backward_Write), &c1_thisId,
                        c1_y);
  sf_mex_destroy(&c1_b_EERAM_Current_Map_Backward_Write);
  for (c1_i88 = 0; c1_i88 < 100; c1_i88++) {
    (*(int16_T (*)[100])c1_outData)[c1_i88] = c1_y[c1_i88];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint16_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint16_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 5, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static uint16_T c1_j_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Average_Current, const char_T *c1_identifier)
{
  uint16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Average_Current),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Average_Current);
  return c1_y;
}

static uint16_T c1_k_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint16_T c1_y;
  uint16_T c1_u11;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u11, 1, 5, 0U, 0, 0U, 0);
  c1_y = c1_u11;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_Average_Current;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint16_T c1_y;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_Average_Current = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Average_Current),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Average_Current);
  *(uint16_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int16_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int16_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 4, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, false);
  return c1_mxArrayOutData;
}

static int16_T c1_l_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_b_Averege_Difference, const char_T *c1_identifier)
{
  int16_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Averege_Difference),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Averege_Difference);
  return c1_y;
}

static int16_T c1_m_emlrt_marshallIn(SFc1_APSAInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int16_T c1_y;
  int16_T c1_i89;
  (void)chartInstance;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i89, 1, 4, 0U, 0, 0U, 0);
  c1_y = c1_i89;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_Averege_Difference;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int16_T c1_y;
  SFc1_APSAInstanceStruct *chartInstance;
  chartInstance = (SFc1_APSAInstanceStruct *)chartInstanceVoid;
  c1_b_Averege_Difference = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_Averege_Difference),
    &c1_thisId);
  sf_mex_destroy(&c1_b_Averege_Difference);
  *(int16_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_n_emlrt_marshallIn(SFc1_APSAInstanceStruct
  *chartInstance, const mxArray *c1_b_setSimStateSideEffectsInfo, const char_T
  *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  sf_mex_assign(&c1_y, c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), false);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_o_emlrt_marshallIn(SFc1_APSAInstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  (void)chartInstance;
  (void)c1_parentId;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), false);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static int32_T c1__s32d_mod__(SFc1_APSAInstanceStruct *chartInstance, int32_T
  c1_b, int32_T c1_c)
{
  (void)chartInstance;
  if (c1_c == 0) {
    _SFD_OVERFLOW_DETECTION(SFDB_DIVIDE_BY_ZERO);
  }

  return c1_b % c1_c;
}

static void init_dsm_address_info(SFc1_APSAInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc1_APSAInstanceStruct *chartInstance)
{
  chartInstance->c1_EERAM_Current_Map_Forward_Read = (real_T (*)[100])
    ssGetInputPortSignal_wrapper(chartInstance->S, 0);
  chartInstance->c1_EERAM_Current_Map_Backward_Read = (real_T (*)[100])
    ssGetInputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c1_EERAM_Threshold_Attention_Forward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c1_EERAM_Threshold_Attention_Backward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 3);
  chartInstance->c1_EERAM_Threshold_Antipinch_Forward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 4);
  chartInstance->c1_EERAM_Threshold_Antipinch_Backward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 5);
  chartInstance->c1_Check_Antipinch = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_Cmd_Motor = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c1_Write_Map = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 8);
  chartInstance->c1_Lenght_Motor_Stroke = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_Hall_Counter_Forward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 10);
  chartInstance->c1_Hall_Counter_Backward = (real_T *)
    ssGetInputPortSignal_wrapper(chartInstance->S, 11);
  chartInstance->c1_Current = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 12);
  chartInstance->c1_Enable_APSA = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 13);
  chartInstance->c1_EERAM_Current_Map_Forward_Write = (uint16_T (*)[100])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
  chartInstance->c1_EERAM_Current_Map_Backward_Write = (int16_T (*)[100])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 2);
  chartInstance->c1_Fail_Sens_Current = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c1_cnt_antipinch = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c1_DELTA_1 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 14);
  chartInstance->c1_DELTA_2 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 15);
  chartInstance->c1_DELTA_3 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 16);
  chartInstance->c1_DELTA_4 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 17);
  chartInstance->c1_Antipinch_Active = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c1_DELTA_5 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 18);
  chartInstance->c1_DELTA_6 = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 19);
  chartInstance->c1_Index_vector = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c1_Threshold_AntiPinch_Update = (real_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 7);
  chartInstance->c1_Threshold_Attention_Update = (real_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 8);
  chartInstance->c1_Delta_Current_next = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 9);
  chartInstance->c1_Delta_Current_actual = (real_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 10);
  chartInstance->c1_Current_Read_Average = (real_T *)
    ssGetOutputPortSignal_wrapper(chartInstance->S, 11);
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

void sf_c1_APSA_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(952633107U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1025245823U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2924467301U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(894461247U);
}

mxArray* sf_c1_APSA_get_post_codegen_info(void);
mxArray *sf_c1_APSA_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("gfwgYAWE4u08pcS9RoID2F");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,20,3,dataFields);

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
      pr[0] = (double)(100);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,11,3,dataFields);

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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(5));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(100);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(6));
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c1_APSA_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_APSA_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_APSA_jit_fallback_info(void)
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

mxArray *sf_c1_APSA_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c1_APSA_get_post_codegen_info(void)
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

static const mxArray *sf_get_sim_state_info_c1_APSA(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[348],T\"Antipinch_Active\",},{M[1],M[722],T\"Current_Read_Average\",},{M[1],M[714],T\"Delta_Current_actual\",},{M[1],M[713],T\"Delta_Current_next\",},{M[1],M[554],T\"EERAM_Current_Map_Backward_Write\",},{M[1],M[83],T\"EERAM_Current_Map_Forward_Write\",},{M[1],M[226],T\"Fail_Sens_Current\",},{M[1],M[82],T\"Index_vector\",},{M[1],M[285],T\"Threshold_AntiPinch_Update\",},{M[1],M[286],T\"Threshold_Attention_Update\",}}",
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[301],T\"cnt_antipinch\",},{M[3],M[134],T\"Avarage_EERAM_Current_Map\",},{M[3],M[135],T\"Average_Current\",},{M[3],M[161],T\"Averege_Difference\",},{M[3],M[227],T\"Cnt_Fail_Sens_Current\",},{M[3],M[721],T\"Counter_Sample_Current\",},{M[3],M[716],T\"Current_Read\",},{M[3],M[748],T\"Delta_Current\",},{M[3],M[92],T\"Inrush_time\",},{M[3],M[79],T\"Lenght_Segment\",}}",
    "100 S1x6'type','srcId','name','auxInfo'{{M[3],M[136],T\"Mod\",},{M[3],M[160],T\"Segments_Cnt\",},{M[8],M[0],T\"is_active_c1_APSA\",},{M[9],M[0],T\"is_c1_APSA\",},{M[9],M[30],T\"is_ANTIPINCH_ACTIVE_FORWARD\",},{M[9],M[393],T\"is_ANTIPINCH_ACTIVE_BACKWARD\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 26, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_APSA_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_APSAInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc1_APSAInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _APSAMachineNumber_,
           1,
           14,
           168,
           0,
           42,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"EERAM_Current_Map_Forward_Read");
          _SFD_SET_DATA_PROPS(1,1,1,0,"EERAM_Current_Map_Backward_Read");
          _SFD_SET_DATA_PROPS(2,1,1,0,"EERAM_Threshold_Attention_Forward");
          _SFD_SET_DATA_PROPS(3,1,1,0,"EERAM_Threshold_Attention_Backward");
          _SFD_SET_DATA_PROPS(4,1,1,0,"EERAM_Threshold_Antipinch_Forward");
          _SFD_SET_DATA_PROPS(5,1,1,0,"EERAM_Threshold_Antipinch_Backward");
          _SFD_SET_DATA_PROPS(6,1,1,0,"Check_Antipinch");
          _SFD_SET_DATA_PROPS(7,1,1,0,"Cmd_Motor");
          _SFD_SET_DATA_PROPS(8,1,1,0,"Write_Map");
          _SFD_SET_DATA_PROPS(9,1,1,0,"Lenght_Motor_Stroke");
          _SFD_SET_DATA_PROPS(10,1,1,0,"Hall_Counter_Forward");
          _SFD_SET_DATA_PROPS(11,1,1,0,"Hall_Counter_Backward");
          _SFD_SET_DATA_PROPS(12,1,1,0,"Current");
          _SFD_SET_DATA_PROPS(13,1,1,0,"Enable_APSA");
          _SFD_SET_DATA_PROPS(14,0,0,0,"Lenght_Segment");
          _SFD_SET_DATA_PROPS(15,2,0,1,"EERAM_Current_Map_Forward_Write");
          _SFD_SET_DATA_PROPS(16,2,0,1,"EERAM_Current_Map_Backward_Write");
          _SFD_SET_DATA_PROPS(17,0,0,0,"Inrush_time");
          _SFD_SET_DATA_PROPS(18,0,0,0,"Avarage_EERAM_Current_Map");
          _SFD_SET_DATA_PROPS(19,0,0,0,"Average_Current");
          _SFD_SET_DATA_PROPS(20,0,0,0,"Mod");
          _SFD_SET_DATA_PROPS(21,0,0,0,"Segments_Cnt");
          _SFD_SET_DATA_PROPS(22,0,0,0,"Averege_Difference");
          _SFD_SET_DATA_PROPS(23,2,0,1,"Fail_Sens_Current");
          _SFD_SET_DATA_PROPS(24,0,0,0,"Cnt_Fail_Sens_Current");
          _SFD_SET_DATA_PROPS(25,2,0,1,"cnt_antipinch");
          _SFD_SET_DATA_PROPS(26,1,1,0,"DELTA_1");
          _SFD_SET_DATA_PROPS(27,1,1,0,"DELTA_2");
          _SFD_SET_DATA_PROPS(28,1,1,0,"DELTA_3");
          _SFD_SET_DATA_PROPS(29,1,1,0,"DELTA_4");
          _SFD_SET_DATA_PROPS(30,2,0,1,"Antipinch_Active");
          _SFD_SET_DATA_PROPS(31,1,1,0,"DELTA_5");
          _SFD_SET_DATA_PROPS(32,1,1,0,"DELTA_6");
          _SFD_SET_DATA_PROPS(33,2,0,1,"Index_vector");
          _SFD_SET_DATA_PROPS(34,2,0,1,"Threshold_AntiPinch_Update");
          _SFD_SET_DATA_PROPS(35,2,0,1,"Threshold_Attention_Update");
          _SFD_SET_DATA_PROPS(36,2,0,1,"Delta_Current_next");
          _SFD_SET_DATA_PROPS(37,2,0,1,"Delta_Current_actual");
          _SFD_SET_DATA_PROPS(38,0,0,0,"Current_Read");
          _SFD_SET_DATA_PROPS(39,0,0,0,"Counter_Sample_Current");
          _SFD_SET_DATA_PROPS(40,2,0,1,"Current_Read_Average");
          _SFD_SET_DATA_PROPS(41,0,0,0,"Delta_Current");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(1,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,0);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_STATE_INFO(13,0,0);
          _SFD_STATE_INFO(8,0,2);
          _SFD_STATE_INFO(9,0,2);
          _SFD_STATE_INFO(11,0,2);
          _SFD_CH_SUBSTATE_COUNT(5);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,4);
          _SFD_CH_SUBSTATE_INDEX(2,10);
          _SFD_CH_SUBSTATE_INDEX(3,12);
          _SFD_CH_SUBSTATE_INDEX(4,13);
          _SFD_ST_SUBSTATE_COUNT(0,3);
          _SFD_ST_SUBSTATE_INDEX(0,0,1);
          _SFD_ST_SUBSTATE_INDEX(0,1,2);
          _SFD_ST_SUBSTATE_INDEX(0,2,3);
          _SFD_ST_SUBSTATE_COUNT(1,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,3);
          _SFD_ST_SUBSTATE_INDEX(4,0,5);
          _SFD_ST_SUBSTATE_INDEX(4,1,6);
          _SFD_ST_SUBSTATE_INDEX(4,2,7);
          _SFD_ST_SUBSTATE_COUNT(5,0);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
          _SFD_ST_SUBSTATE_COUNT(13,0);
        }

        _SFD_CV_INIT_CHART(5,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,3,1,1,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(4,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(4,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 33, 68 };

          static unsigned int sEndGuardMap[] = { 26, 61, 94 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(1,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 33, 68 };

          static unsigned int sEndRelationalopMap[] = { 26, 61, 94 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(1,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 38, 78 };

          static unsigned int sEndGuardMap[] = { 31, 71, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(3,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 38, 78 };

          static unsigned int sEndRelationalopMap[] = { 31, 71, 104 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(3,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(2,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 38 };

          static unsigned int sEndGuardMap[] = { 31, 67 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(89,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 38 };

          static unsigned int sEndRelationalopMap[] = { 31, 67 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(89,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 38 };

          static unsigned int sEndGuardMap[] = { 31, 67 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(88,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 38 };

          static unsigned int sEndRelationalopMap[] = { 31, 67 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(88,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 32 };

          static unsigned int sEndGuardMap[] = { 25, 59 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(85,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 32 };

          static unsigned int sEndRelationalopMap[] = { 25, 59 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(85,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 32 };

          static unsigned int sEndGuardMap[] = { 25, 60 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(84,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 32 };

          static unsigned int sEndRelationalopMap[] = { 25, 60 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(84,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(87,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(87,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(82,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(82,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 38, 72 };

          static unsigned int sEndGuardMap[] = { 31, 66, 98 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(83,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 38, 72 };

          static unsigned int sEndRelationalopMap[] = { 31, 66, 98 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(83,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 33, 68 };

          static unsigned int sEndGuardMap[] = { 26, 61, 94 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(86,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 33, 68 };

          static unsigned int sEndRelationalopMap[] = { 26, 61, 94 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(86,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(28,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(30,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 1, 1 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(30,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 35 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(31,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 35 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 3, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(31,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2 };

          static unsigned int sEndGuardMap[] = { 55 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(32,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 2 };

          static unsigned int sEndRelationalopMap[] = { 55 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(32,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(33,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(29,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(34,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(35,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(36,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(37,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(38,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(39,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(74,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(75,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 7 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(75,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(76,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(77,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(78,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(80,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(79,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(81,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(9,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 105, 170 };

          static unsigned int sEndSaturateMap[] = { 135, 200 };

          _SFD_CV_INIT_TRANSITION_SATURATION(9,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(5,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 74 };

          static unsigned int sEndGuardMap[] = { 69, 107 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(6,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 74 };

          static unsigned int sEndRelationalopMap[] = { 69, 107 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(6,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 26, 44 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(156,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 26, 44 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(156,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(155,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(7,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(157,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(158,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(159,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 34, 50 };

          static unsigned int sEndSaturateMap[] = { 46, 70 };

          _SFD_CV_INIT_TRANSITION_SATURATION(159,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(23,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 25 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(23,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(27,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 143, 237, 32 };

          static unsigned int sEndSaturateMap[] = { 144, 238, 63 };

          _SFD_CV_INIT_TRANSITION_SATURATION(27,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(27,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(12,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(12,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(16,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(40,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(165,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(164,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 73 };

          static unsigned int sEndGuardMap[] = { 69, 104 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(41,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 73 };

          static unsigned int sEndRelationalopMap[] = { 69, 104 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(41,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(163,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 155, 269, 79 };

          static unsigned int sEndSaturateMap[] = { 167, 281, 91 };

          _SFD_CV_INIT_TRANSITION_SATURATION(163,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(42,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(152,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 26 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(152,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 56 };

          static unsigned int sEndGuardMap[] = { 49, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(43,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 56 };

          static unsigned int sEndRelationalopMap[] = { 49, 83 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 4, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(43,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(44,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 16 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(44,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(45,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(47,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(46,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(48,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(49,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(50,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 22, 82 };

          static unsigned int sEndGuardMap[] = { 74, 149 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(52,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 113 };

          static unsigned int sEndSaturateMap[] = { 125 };

          _SFD_CV_INIT_TRANSITION_SATURATION(52,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 22, 82 };

          static unsigned int sEndRelationalopMap[] = { 74, 149 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 2, 4, 2, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(52,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 21, 79 };

          static unsigned int sEndGuardMap[] = { 70, 128 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(51,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 21, 79 };

          static unsigned int sEndRelationalopMap[] = { 70, 128 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 4, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(51,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(57,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(54,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 33 };

          static unsigned int sEndSaturateMap[] = { 82, 45 };

          _SFD_CV_INIT_TRANSITION_SATURATION(54,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(53,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 33 };

          static unsigned int sEndSaturateMap[] = { 80, 45 };

          _SFD_CV_INIT_TRANSITION_SATURATION(53,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(56,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(55,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(58,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 107 };

          static unsigned int sEndSaturateMap[] = { 108 };

          _SFD_CV_INIT_TRANSITION_SATURATION(58,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 22, 80, 154 };

          static unsigned int sEndGuardMap[] = { 72, 147, 194 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(60,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 111 };

          static unsigned int sEndSaturateMap[] = { 123 };

          _SFD_CV_INIT_TRANSITION_SATURATION(60,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 22, 80, 154 };

          static unsigned int sEndRelationalopMap[] = { 72, 147, 194 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 2, 4, 2, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(60,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 21, 82, 136 };

          static unsigned int sEndGuardMap[] = { 74, 129, 176 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(59,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 21, 82, 136 };

          static unsigned int sEndRelationalopMap[] = { 74, 129, 176 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 4, 2, 2, 4, 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(59,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(61,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(62,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 45 };

          static unsigned int sEndSaturateMap[] = { 82, 46 };

          _SFD_CV_INIT_TRANSITION_SATURATION(62,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(64,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 45 };

          static unsigned int sEndSaturateMap[] = { 80, 46 };

          _SFD_CV_INIT_TRANSITION_SATURATION(64,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(63,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(65,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(66,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(67,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(67,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(68,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(69,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(71,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(70,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(72,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(151,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(73,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(17,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(18,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(18,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 80 };

          static unsigned int sEndGuardMap[] = { 75, 115 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(24,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 80 };

          static unsigned int sEndRelationalopMap[] = { 75, 115 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(24,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(167,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(26,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 231 };

          static unsigned int sEndSaturateMap[] = { 26, 243 };

          _SFD_CV_INIT_TRANSITION_SATURATION(26,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(21,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(25,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(138,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 74 };

          static unsigned int sEndGuardMap[] = { 70, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(139,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 74 };

          static unsigned int sEndRelationalopMap[] = { 70, 105 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(139,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 29 };

          static unsigned int sEndGuardMap[] = { 26, 44 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(160,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 29 };

          static unsigned int sEndRelationalopMap[] = { 26, 44 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 0, 0, 0, 0 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(160,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(135,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(137,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(161,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(140,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 35, 49 };

          static unsigned int sEndSaturateMap[] = { 47, 69 };

          _SFD_CV_INIT_TRANSITION_SATURATION(140,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(162,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(136,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(96,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 29 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(134,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 144, 240, 32 };

          static unsigned int sEndSaturateMap[] = { 145, 241, 63 };

          _SFD_CV_INIT_TRANSITION_SATURATION(134,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 29 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(134,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 25 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(97,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 25 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(97,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(147,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 30 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(145,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 30 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(145,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(142,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(144,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 74 };

          static unsigned int sEndGuardMap[] = { 70, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(143,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 74 };

          static unsigned int sEndRelationalopMap[] = { 70, 105 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(143,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(146,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(148,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 274, 31 };

          static unsigned int sEndSaturateMap[] = { 286, 69 };

          _SFD_CV_INIT_TRANSITION_SATURATION(148,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(150,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(149,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(141,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(90,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 28 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(91,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 28 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(91,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(92,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(93,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(94,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(95,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(98,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(99,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 74 };

          static unsigned int sEndGuardMap[] = { 70, 105 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(100,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 74 };

          static unsigned int sEndRelationalopMap[] = { 70, 105 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 5, 3, 5, 3 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(100,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(166,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(101,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(102,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 100, 177, 293 };

          static unsigned int sEndSaturateMap[] = { 112, 189, 305 };

          _SFD_CV_INIT_TRANSITION_SATURATION(102,3,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(153,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(153,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 16 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(104,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 16 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 4, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(104,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 56 };

          static unsigned int sEndGuardMap[] = { 49, 83 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(103,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1, 56 };

          static unsigned int sEndRelationalopMap[] = { 49, 83 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 4, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(103,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(107,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(105,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(106,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(109,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(108,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(110,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 21, 81 };

          static unsigned int sEndGuardMap[] = { 73, 149 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(112,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 113 };

          static unsigned int sEndSaturateMap[] = { 125 };

          _SFD_CV_INIT_TRANSITION_SATURATION(112,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 21, 81 };

          static unsigned int sEndRelationalopMap[] = { 73, 149 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 2, 4, 2, 4 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(112,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 21, 79 };

          static unsigned int sEndGuardMap[] = { 70, 128 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(111,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 21, 79 };

          static unsigned int sEndRelationalopMap[] = { 70, 128 };

          static int sRelationalopEps[] = { -1, -1 };

          static int sRelationalopType[] = { 4, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(111,2,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(115,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 34 };

          static unsigned int sEndSaturateMap[] = { 83, 46 };

          _SFD_CV_INIT_TRANSITION_SATURATION(115,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(113,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 34 };

          static unsigned int sEndSaturateMap[] = { 81, 46 };

          _SFD_CV_INIT_TRANSITION_SATURATION(113,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(114,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(117,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(116,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(118,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 108 };

          static unsigned int sEndSaturateMap[] = { 109 };

          _SFD_CV_INIT_TRANSITION_SATURATION(118,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 22, 80, 155 };

          static unsigned int sEndGuardMap[] = { 72, 148, 193 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(120,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartSaturateMap[] = { 112 };

          static unsigned int sEndSaturateMap[] = { 124 };

          _SFD_CV_INIT_TRANSITION_SATURATION(120,1,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 22, 80, 155 };

          static unsigned int sEndRelationalopMap[] = { 72, 148, 193 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 2, 4, 2, 2, 4, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(120,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 21, 82, 136 };

          static unsigned int sEndGuardMap[] = { 74, 129, 176 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(119,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 21, 82, 136 };

          static unsigned int sEndRelationalopMap[] = { 74, 129, 176 };

          static int sRelationalopEps[] = { -1, -1, -1 };

          static int sRelationalopType[] = { 4, 2, 2, 4, 2, 2 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(119,3,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(123,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 46 };

          static unsigned int sEndSaturateMap[] = { 83, 47 };

          _SFD_CV_INIT_TRANSITION_SATURATION(123,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(121,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartSaturateMap[] = { 1, 46 };

          static unsigned int sEndSaturateMap[] = { 81, 47 };

          _SFD_CV_INIT_TRANSITION_SATURATION(121,2,&(sStartSaturateMap[0]),
            &(sEndSaturateMap[0]));
        }

        _SFD_CV_INIT_TRANS(122,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(125,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(124,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(126,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 27 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(127,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartRelationalopMap[] = { 1 };

          static unsigned int sEndRelationalopMap[] = { 27 };

          static int sRelationalopEps[] = { -1 };

          static int sRelationalopType[] = { 5, 5 };

          _SFD_CV_INIT_TRANSITION_RELATIONALOP(127,1,&(sStartRelationalopMap[0]),
            &(sEndRelationalopMap[0]),&(sRelationalopEps[0]),
            &(sRelationalopType[0]));
        }

        _SFD_CV_INIT_TRANS(128,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(129,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(130,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(131,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(132,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(154,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(133,0,NULL,NULL,0,NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_UINT16,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_e_sf_marshallOut,(MexInFcnForType)
            c1_d_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 100;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_INT16,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_f_sf_marshallOut,(MexInFcnForType)
            c1_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_UINT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_g_sf_marshallOut,(MexInFcnForType)c1_f_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(22,SF_INT16,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_h_sf_marshallOut,(MexInFcnForType)c1_g_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(33,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(35,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(36,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_VALUE_PTR(0U,
          *chartInstance->c1_EERAM_Current_Map_Forward_Read);
        _SFD_SET_DATA_VALUE_PTR(1U,
          *chartInstance->c1_EERAM_Current_Map_Backward_Read);
        _SFD_SET_DATA_VALUE_PTR(2U,
          chartInstance->c1_EERAM_Threshold_Attention_Forward);
        _SFD_SET_DATA_VALUE_PTR(3U,
          chartInstance->c1_EERAM_Threshold_Attention_Backward);
        _SFD_SET_DATA_VALUE_PTR(4U,
          chartInstance->c1_EERAM_Threshold_Antipinch_Forward);
        _SFD_SET_DATA_VALUE_PTR(5U,
          chartInstance->c1_EERAM_Threshold_Antipinch_Backward);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c1_Check_Antipinch);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c1_Cmd_Motor);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c1_Write_Map);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c1_Lenght_Motor_Stroke);
        _SFD_SET_DATA_VALUE_PTR(10U, chartInstance->c1_Hall_Counter_Forward);
        _SFD_SET_DATA_VALUE_PTR(11U, chartInstance->c1_Hall_Counter_Backward);
        _SFD_SET_DATA_VALUE_PTR(12U, chartInstance->c1_Current);
        _SFD_SET_DATA_VALUE_PTR(13U, chartInstance->c1_Enable_APSA);
        _SFD_SET_DATA_VALUE_PTR(14U, &chartInstance->c1_Lenght_Segment);
        _SFD_SET_DATA_VALUE_PTR(15U,
          *chartInstance->c1_EERAM_Current_Map_Forward_Write);
        _SFD_SET_DATA_VALUE_PTR(16U,
          *chartInstance->c1_EERAM_Current_Map_Backward_Write);
        _SFD_SET_DATA_VALUE_PTR(17U, &chartInstance->c1_Inrush_time);
        _SFD_SET_DATA_VALUE_PTR(18U,
          &chartInstance->c1_Avarage_EERAM_Current_Map);
        _SFD_SET_DATA_VALUE_PTR(19U, &chartInstance->c1_Average_Current);
        _SFD_SET_DATA_VALUE_PTR(20U, &chartInstance->c1_Mod);
        _SFD_SET_DATA_VALUE_PTR(21U, &chartInstance->c1_Segments_Cnt);
        _SFD_SET_DATA_VALUE_PTR(22U, &chartInstance->c1_Averege_Difference);
        _SFD_SET_DATA_VALUE_PTR(23U, chartInstance->c1_Fail_Sens_Current);
        _SFD_SET_DATA_VALUE_PTR(24U, &chartInstance->c1_Cnt_Fail_Sens_Current);
        _SFD_SET_DATA_VALUE_PTR(25U, chartInstance->c1_cnt_antipinch);
        _SFD_SET_DATA_VALUE_PTR(26U, chartInstance->c1_DELTA_1);
        _SFD_SET_DATA_VALUE_PTR(27U, chartInstance->c1_DELTA_2);
        _SFD_SET_DATA_VALUE_PTR(28U, chartInstance->c1_DELTA_3);
        _SFD_SET_DATA_VALUE_PTR(29U, chartInstance->c1_DELTA_4);
        _SFD_SET_DATA_VALUE_PTR(30U, chartInstance->c1_Antipinch_Active);
        _SFD_SET_DATA_VALUE_PTR(31U, chartInstance->c1_DELTA_5);
        _SFD_SET_DATA_VALUE_PTR(32U, chartInstance->c1_DELTA_6);
        _SFD_SET_DATA_VALUE_PTR(33U, chartInstance->c1_Index_vector);
        _SFD_SET_DATA_VALUE_PTR(34U,
          chartInstance->c1_Threshold_AntiPinch_Update);
        _SFD_SET_DATA_VALUE_PTR(35U,
          chartInstance->c1_Threshold_Attention_Update);
        _SFD_SET_DATA_VALUE_PTR(36U, chartInstance->c1_Delta_Current_next);
        _SFD_SET_DATA_VALUE_PTR(37U, chartInstance->c1_Delta_Current_actual);
        _SFD_SET_DATA_VALUE_PTR(38U, &chartInstance->c1_Current_Read);
        _SFD_SET_DATA_VALUE_PTR(39U, &chartInstance->c1_Counter_Sample_Current);
        _SFD_SET_DATA_VALUE_PTR(40U, chartInstance->c1_Current_Read_Average);
        _SFD_SET_DATA_VALUE_PTR(41U, &chartInstance->c1_Delta_Current);
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
  return "W1pLsl8VieHi7tv5i97oaH";
}

static void sf_opaque_initialize_c1_APSA(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_APSAInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
  initialize_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_APSA(void *chartInstanceVar)
{
  enable_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_APSA(void *chartInstanceVar)
{
  disable_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_APSA(void *chartInstanceVar)
{
  sf_gateway_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c1_APSA(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  return get_sim_state_c1_APSA((SFc1_APSAInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c1_APSA(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  set_sim_state_c1_APSA((SFc1_APSAInstanceStruct*)chartInfo->chartInstance, st);
}

static void sf_opaque_terminate_c1_APSA(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_APSAInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_APSA_optimization_info();
    }

    finalize_c1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (crtInfo != NULL) {
      utFree(crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_APSA((SFc1_APSAInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_APSA(SimStruct *S)
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
    initialize_params_c1_APSA((SFc1_APSAInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_APSA_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,1,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 13, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 14, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 15, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 16, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 17, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 18, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 19, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,20);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,11);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=11; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 20; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3428583928U));
  ssSetChecksum1(S,(1276413249U));
  ssSetChecksum2(S,(2326889444U));
  ssSetChecksum3(S,(1970689449U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_APSA(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_APSA(SimStruct *S)
{
  SFc1_APSAInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc1_APSAInstanceStruct *)utMalloc(sizeof
    (SFc1_APSAInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_APSAInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_APSA;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_APSA;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_APSA;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_APSA;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_APSA;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_APSA;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_APSA;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_APSA;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_APSA;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_APSA;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_APSA;
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

void c1_APSA_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_APSA(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_APSA(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_APSA(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_APSA_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
