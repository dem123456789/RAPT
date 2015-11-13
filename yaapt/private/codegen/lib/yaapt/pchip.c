/*
 * File: pchip.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 13-Nov-2015 04:43:17
 */

/* Include files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "pchip.h"
#include "yaapt_emxutil.h"

/* Function Declarations */
static double exteriorSlope(double d1, double d2, double h1, double h2);

/* Function Definitions */

/*
 * Arguments    : double d1
 *                double d2
 *                double h1
 *                double h2
 * Return Type  : double
 */
static double exteriorSlope(double d1, double d2, double h1, double h2)
{
  double s;
  double signd1;
  double b_s;
  double b_d2;
  s = ((2.0 * h1 + h2) * d1 - h1 * d2) / (h1 + h2);
  if (d1 < 0.0) {
    signd1 = -1.0;
  } else if (d1 > 0.0) {
    signd1 = 1.0;
  } else if (d1 == 0.0) {
    signd1 = 0.0;
  } else {
    signd1 = d1;
  }

  if (s < 0.0) {
    b_s = -1.0;
  } else if (s > 0.0) {
    b_s = 1.0;
  } else if (s == 0.0) {
    b_s = 0.0;
  } else {
    b_s = s;
  }

  if (b_s != signd1) {
    s = 0.0;
  } else {
    if (d2 < 0.0) {
      b_d2 = -1.0;
    } else if (d2 > 0.0) {
      b_d2 = 1.0;
    } else if (d2 == 0.0) {
      b_d2 = 0.0;
    } else {
      b_d2 = d2;
    }

    if ((signd1 != b_d2) && (fabs(s) > fabs(3.0 * d1))) {
      s = 3.0 * d1;
    }
  }

  return s;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *v_breaks
 *                emxArray_real_T *v_coefs
 * Return Type  : void
 */
void pchip(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
           *v_breaks, emxArray_real_T *v_coefs)
{
  emxArray_real_T *h;
  int k;
  int szdel[2];
  emxArray_real_T *del;
  unsigned int uv2[2];
  emxArray_real_T *slopes;
  double hs;
  double hs3;
  double w1;
  int x_idx_0;
  emxInit_real_T(&h, 2);
  k = h->size[0] * h->size[1];
  h->size[0] = 1;
  h->size[1] = x->size[1] - 1;
  emxEnsureCapacity((emxArray__common *)h, k, (int)sizeof(double));
  for (k = 1; k < x->size[1]; k++) {
    h->data[k - 1] = x->data[k] - x->data[k - 1];
  }

  for (k = 0; k < 2; k++) {
    szdel[k] = y->size[k];
  }

  emxInit_real_T(&del, 2);
  szdel[1]--;
  k = del->size[0] * del->size[1];
  del->size[0] = 1;
  del->size[1] = szdel[1];
  emxEnsureCapacity((emxArray__common *)del, k, (int)sizeof(double));
  for (k = 0; k + 1 < x->size[1]; k++) {
    del->data[k] = (y->data[k + 1] - y->data[k]) / h->data[k];
  }

  for (k = 0; k < 2; k++) {
    uv2[k] = (unsigned int)y->size[k];
  }

  emxInit_real_T(&slopes, 2);
  k = slopes->size[0] * slopes->size[1];
  slopes->size[0] = 1;
  slopes->size[1] = (int)uv2[1];
  emxEnsureCapacity((emxArray__common *)slopes, k, (int)sizeof(double));
  if (x->size[1] == 2) {
    for (k = 0; k < 2; k++) {
      slopes->data[k] = del->data[0];
    }
  } else {
    for (k = 1; k <= x->size[1] - 2; k++) {
      hs = h->data[k - 1] + h->data[k];
      hs3 = 3.0 * hs;
      w1 = (h->data[k - 1] + hs) / hs3;
      hs = (h->data[k] + hs) / hs3;
      hs3 = 0.0;
      if (del->data[k - 1] < 0.0) {
        if (del->data[k] <= del->data[k - 1]) {
          hs3 = del->data[k - 1] / (w1 * (del->data[k - 1] / del->data[k]) + hs);
        } else {
          if (del->data[k] < 0.0) {
            hs3 = del->data[k] / (w1 + hs * (del->data[k] / del->data[k - 1]));
          }
        }
      } else {
        if (del->data[k - 1] > 0.0) {
          if (del->data[k] >= del->data[k - 1]) {
            hs3 = del->data[k - 1] / (w1 * (del->data[k - 1] / del->data[k]) +
              hs);
          } else {
            if (del->data[k] > 0.0) {
              hs3 = del->data[k] / (w1 + hs * (del->data[k] / del->data[k - 1]));
            }
          }
        }
      }

      slopes->data[k] = hs3;
    }

    slopes->data[0] = exteriorSlope(del->data[0], del->data[1], h->data[0],
      h->data[1]);
    slopes->data[x->size[1] - 1] = exteriorSlope(del->data[x->size[1] - 2],
      del->data[x->size[1] - 3], h->data[x->size[1] - 2], h->data[x->size[1] - 3]);
  }

  x_idx_0 = x->size[1];
  k = v_breaks->size[0] * v_breaks->size[1];
  v_breaks->size[0] = 1;
  v_breaks->size[1] = x_idx_0;
  emxEnsureCapacity((emxArray__common *)v_breaks, k, (int)sizeof(double));
  for (k = 0; k < x_idx_0; k++) {
    v_breaks->data[v_breaks->size[0] * k] = x->data[k];
  }

  k = v_coefs->size[0] * v_coefs->size[1];
  v_coefs->size[0] = slopes->size[1] - 1;
  v_coefs->size[1] = 4;
  emxEnsureCapacity((emxArray__common *)v_coefs, k, (int)sizeof(double));
  for (k = 0; k + 1 < x->size[1]; k++) {
    hs = (del->data[k] - slopes->data[k]) / h->data[k];
    hs3 = (slopes->data[k + 1] - del->data[k]) / h->data[k];
    v_coefs->data[k] = (hs3 - hs) / h->data[k];
    v_coefs->data[(slopes->size[1] + k) - 1] = 2.0 * hs - hs3;
    v_coefs->data[((slopes->size[1] - 1) << 1) + k] = slopes->data[k];
    v_coefs->data[3 * (slopes->size[1] - 1) + k] = y->data[k];
  }

  emxFree_real_T(&slopes);
  emxFree_real_T(&del);
  emxFree_real_T(&h);
}

/*
 * File trailer for pchip.c
 *
 * [EOF]
 */