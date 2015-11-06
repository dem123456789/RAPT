/*
 * File: yaapt_emxAPI.h
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 27-Oct-2015 00:20:18
 */

#ifndef __YAAPT_EMXAPI_H__
#define __YAAPT_EMXAPI_H__

/* Include files */
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "yaapt_types.h"

/* Function Declarations */
extern emxArray_real_T *emxCreateND_real_T(int numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapperND_real_T(double *data, int
  numDimensions, int *size);
extern emxArray_real_T *emxCreateWrapper_real_T(double *data, int rows, int cols);
extern emxArray_real_T *emxCreate_real_T(int rows, int cols);
extern void emxDestroyArray_real_T(emxArray_real_T *emxArray);

#endif

/*
 * File trailer for yaapt_emxAPI.h
 *
 * [EOF]
 */