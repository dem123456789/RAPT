/*
 * fft.h
 *
 * Code generation for function 'fft'
 *
 */

#ifndef __FFT_H__
#define __FFT_H__

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
#include "omp.h"
#include "yaapt_types.h"

/* Function Declarations */
extern void b_fft(const emlrtStack *sp, const emxArray_real_T *x, real_T
                  varargin_1, emxArray_creal_T *y);
extern void fft(const emlrtStack *sp, const emxArray_creal_T *x, real_T
                varargin_1, emxArray_creal_T *y);

#endif

/* End of code generation (fft.h) */
