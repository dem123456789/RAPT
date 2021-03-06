/*
 * File: cmp_rate.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Nov-2015 19:51:15
 */

#ifndef __CMP_RATE_H__
#define __CMP_RATE_H__

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
extern void cmp_rate(const emxArray_real_T *Phi, double Fs, double lag_min,
                     double lag_max, double Pitch_data[], int Pitch_size[2],
                     double Merit_data[], int Merit_size[2]);

#endif

/*
 * File trailer for cmp_rate.h
 *
 * [EOF]
 */
