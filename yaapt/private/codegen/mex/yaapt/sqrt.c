/*
 * sqrt.c
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "sqrt.h"
#include "error1.h"
#include "eml_int_forloop_overflow_check.h"
#include "yaapt_data.h"
#include "lapacke.h"

/* Variable Definitions */
static emlrtRSInfo jh_emlrtRSI = { 11, "sqrt",
  "F:\\MATLAB\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m" };

static emlrtRSInfo kh_emlrtRSI = { 15, "sqrt",
  "F:\\MATLAB\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m" };

/* Function Definitions */

/*
 *
 */
void b_sqrt(const emlrtStack *sp, real_T *x)
{
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  if (*x < 0.0) {
    st.site = &td_emlrtRSI;
    error(&st);
  }

  *x = muDoubleScalarSqrt(*x);
}

/*
 *
 */
void c_sqrt(const emlrtStack *sp, emxArray_real_T *x)
{
  boolean_T overflow;
  int32_T k;
  int32_T nx;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &jh_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  overflow = false;
  for (k = 0; k < x->size[0]; k++) {
    if (overflow || (x->data[k] < 0.0)) {
      overflow = true;
    } else {
      overflow = false;
    }
  }

  if (overflow) {
    st.site = &td_emlrtRSI;
    error(&st);
  }

  st.site = &kh_emlrtRSI;
  nx = x->size[0];
  b_st.site = &eb_emlrtRSI;
  if (1 > x->size[0]) {
    overflow = false;
  } else {
    overflow = (x->size[0] > 2147483646);
  }

  if (overflow) {
    c_st.site = &cb_emlrtRSI;
    check_forloop_overflow_error(&c_st, true);
  }

  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = muDoubleScalarSqrt(x->data[k]);
  }
}

/* End of code generation (sqrt.c) */
