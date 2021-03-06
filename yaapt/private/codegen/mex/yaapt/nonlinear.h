/*
 * nonlinear.h
 *
 * Code generation for function 'nonlinear'
 *
 */

#ifndef NONLINEAR_H
#define NONLINEAR_H

/* Include files */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mwmathutil.h"
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "covrt.h"
#include "rtwtypes.h"
#include "omp.h"
#include "yaapt_types.h"

/* Function Declarations */
extern void nonlinear(const emlrtStack *sp, const emxArray_real_T *DataA, real_T
                      Fs, real_T Prm_bp_forder, real_T Prm_bp_low, real_T
                      Prm_bp_high, real_T Prm_dec_factor, emxArray_real_T *DataB,
                      emxArray_real_T *DataC, emxArray_real_T *DataD, real_T
                      *newFs);

#endif

/* End of code generation (nonlinear.h) */
