/*
 * File: Myspecgram.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Nov-2015 19:51:15
 */

#ifndef __MYSPECGRAM_H__
#define __MYSPECGRAM_H__

/* Include Files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "yaapt_types.h"

/* Function Declarations */
extern void Myspecgram(emxArray_real_T *x, double window, double noverlap,
  emxArray_creal_T *yo);

#endif

/*
 * File trailer for Myspecgram.h
 *
 * [EOF]
 */
