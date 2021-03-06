/*
 * nlfer.h
 *
 * Code generation for function 'nlfer'
 *
 */

#ifndef NLFER_H
#define NLFER_H

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
extern void nlfer(const emlrtStack *sp, const emxArray_real_T *Data, real_T Fs,
                  real_T Prm_frame_length, real_T Prm_frame_space, real_T
                  Prm_f0_min, real_T Prm_f0_max, real_T Prm_fft_length, real_T
                  Prm_nlfer_thresh1, emxArray_real_T *Energy, emxArray_boolean_T
                  *VUVEnergy);

#endif

/* End of code generation (nlfer.h) */
