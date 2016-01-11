/*
 * sortIdx.h
 *
 * Code generation for function 'sortIdx'
 *
 */

#ifndef __SORTIDX_H__
#define __SORTIDX_H__

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "yaapt_types.h"

/* Function Declarations */
extern void b_merge(const emlrtStack *sp, int32_T idx[20], real_T x[20], int32_T
                    offset, int32_T np, int32_T nq, int32_T iwork[20], real_T
                    xwork[20]);
extern void merge_block(const emlrtStack *sp, int32_T idx[100], real_T x[100],
  int32_T offset, int32_T n, int32_T preSortLevel, int32_T iwork[100], real_T
  xwork[100]);
extern void sortIdx(const emlrtStack *sp, emxArray_real_T *x, emxArray_int32_T
                    *idx);

#endif

/* End of code generation (sortIdx.h) */