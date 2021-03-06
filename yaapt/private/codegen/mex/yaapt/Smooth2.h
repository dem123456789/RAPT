/*
 * Smooth2.h
 *
 * Code generation for function 'Smooth2'
 *
 */

#ifndef SMOOTH2_H
#define SMOOTH2_H

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
extern void Smooth2(const emlrtStack *sp, const emxArray_real_T *arr, real_T
                    Prm_smooth_threshold, emxArray_real_T *out);

#endif

/* End of code generation (Smooth2.h) */
