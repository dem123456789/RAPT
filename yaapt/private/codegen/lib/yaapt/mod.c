/*
 * File: mod.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Feb-2016 23:38:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "mod.h"

/* Function Definitions */

/*
 * Arguments    : double x
 * Return Type  : double
 */
double b_mod(double x)
{
  return x - floor(x / 2.0) * 2.0;
}

/*
 * File trailer for mod.c
 *
 * [EOF]
 */
