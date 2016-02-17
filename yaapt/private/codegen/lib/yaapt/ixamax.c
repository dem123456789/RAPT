/*
 * File: ixamax.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 16-Feb-2016 23:38:40
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "ixamax.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const emxArray_real_T *x
 *                int ix0
 * Return Type  : int
 */
int ixamax(int n, const emxArray_real_T *x, int ix0)
{
  int idxmax;
  int ix;
  double smax;
  int k;
  double s;
  if (n < 1) {
    idxmax = 0;
  } else {
    idxmax = 1;
    if (n > 1) {
      ix = ix0 - 1;
      smax = fabs(x->data[ix0 - 1]);
      for (k = 2; k <= n; k++) {
        ix++;
        s = fabs(x->data[ix]);
        if (s > smax) {
          idxmax = k;
          smax = s;
        }
      }
    }
  }

  return idxmax;
}

/*
 * File trailer for ixamax.c
 *
 * [EOF]
 */
