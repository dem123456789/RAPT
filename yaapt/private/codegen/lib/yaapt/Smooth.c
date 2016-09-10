/*
 * File: Smooth.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 05-Sep-2016 15:50:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "Smooth.h"
#include "yaapt_emxutil.h"

/* Function Definitions */

/*
 * Smooth frequency data by 3 chunks
 *  arr = frequency data
 *  out = data after smoothed
 *  3 chunks is one window, if the lengh of the middle chunk is below
 *  threshold it will be absorbed by the head or tail chunk.
 * Arguments    : emxArray_real_T *arr
 *                double Prm_smooth_threshold
 * Return Type  : void
 */
void Smooth(emxArray_real_T *arr, double Prm_smooth_threshold)
{
  emxArray_real_T *chunk1;
  emxArray_real_T *chunk2;
  emxArray_real_T *chunk3;
  double chunk1_value;
  double chunk2_value;
  double chunk3_value;
  int i34;
  int pointer;
  int i;
  emxArray_real_T *b_chunk3;
  emxArray_real_T *b_chunk2;
  emxArray_real_T *b_chunk1;
  int n;
  int mtmp;
  int itmp;
  unsigned int len_tmp[3];
  int m;
  int ix;
  unsigned int b_mtmp;
  emxInit_real_T(&chunk1, 2);
  emxInit_real_T(&chunk2, 2);
  emxInit_real_T(&chunk3, 2);
  chunk1_value = 0.0;
  chunk2_value = 0.0;
  chunk3_value = 0.0;
  i34 = chunk1->size[0] * chunk1->size[1];
  chunk1->size[0] = 0;
  chunk1->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)chunk1, i34, (int)sizeof(double));
  i34 = chunk2->size[0] * chunk2->size[1];
  chunk2->size[0] = 0;
  chunk2->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)chunk2, i34, (int)sizeof(double));
  i34 = chunk3->size[0] * chunk3->size[1];
  chunk3->size[0] = 0;
  chunk3->size[1] = 0;
  emxEnsureCapacity((emxArray__common *)chunk3, i34, (int)sizeof(double));
  pointer = 0;

  /*  10 frames */
  /*  percent_threshold = 0.01; % 1 percent */
  i34 = arr->size[1];
  i = 0;
  emxInit_real_T(&b_chunk3, 2);
  emxInit_real_T(&b_chunk2, 2);
  emxInit_real_T(&b_chunk1, 2);
  while (i <= i34 - 1) {
    if (pointer == 0) {
      chunk1_value = arr->data[i];
      n = chunk1->size[0] * chunk1->size[1];
      chunk1->size[0] = 1;
      chunk1->size[1] = 1;
      emxEnsureCapacity((emxArray__common *)chunk1, n, (int)sizeof(double));
      chunk1->data[0] = 1.0 + (double)i;
      pointer = 1;
    } else if (pointer == 1) {
      if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
        chunk1_value = arr->data[i];
        n = chunk1->size[0] * chunk1->size[1];
        chunk1->size[0] = 1;
        chunk1->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)chunk1, n, (int)sizeof(double));
        chunk1->data[0] = 1.0 + (double)i;
      } else if (arr->data[i] == chunk1_value) {
        mtmp = chunk1->size[1];
        n = b_chunk1->size[0] * b_chunk1->size[1];
        b_chunk1->size[0] = 1;
        b_chunk1->size[1] = mtmp + 1;
        emxEnsureCapacity((emxArray__common *)b_chunk1, n, (int)sizeof(double));
        for (n = 0; n < mtmp; n++) {
          b_chunk1->data[b_chunk1->size[0] * n] = chunk1->data[n];
        }

        b_chunk1->data[b_chunk1->size[0] * mtmp] = 1.0 + (double)i;
        n = chunk1->size[0] * chunk1->size[1];
        chunk1->size[0] = b_chunk1->size[0];
        chunk1->size[1] = b_chunk1->size[1];
        emxEnsureCapacity((emxArray__common *)chunk1, n, (int)sizeof(double));
        mtmp = b_chunk1->size[1];
        for (n = 0; n < mtmp; n++) {
          itmp = b_chunk1->size[0];
          for (ix = 0; ix < itmp; ix++) {
            chunk1->data[ix + chunk1->size[0] * n] = b_chunk1->data[ix +
              b_chunk1->size[0] * n];
          }
        }
      } else {
        pointer = 2;
        chunk2_value = arr->data[i];
        n = chunk2->size[0] * chunk2->size[1];
        chunk2->size[0] = 1;
        chunk2->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)chunk2, n, (int)sizeof(double));
        chunk2->data[0] = 1.0 + (double)i;
      }
    } else if (pointer == 2) {
      if (arr->data[i] == chunk2_value) {
        if (!((chunk2->size[0] == 0) || (chunk2->size[1] == 0))) {
          mtmp = chunk2->size[1];
        } else {
          mtmp = 0;
        }

        n = b_chunk2->size[0] * b_chunk2->size[1];
        b_chunk2->size[0] = 1;
        b_chunk2->size[1] = mtmp + 1;
        emxEnsureCapacity((emxArray__common *)b_chunk2, n, (int)sizeof(double));
        for (n = 0; n < mtmp; n++) {
          b_chunk2->data[b_chunk2->size[0] * n] = chunk2->data[n];
        }

        b_chunk2->data[b_chunk2->size[0] * mtmp] = 1.0 + (double)i;
        n = chunk2->size[0] * chunk2->size[1];
        chunk2->size[0] = b_chunk2->size[0];
        chunk2->size[1] = b_chunk2->size[1];
        emxEnsureCapacity((emxArray__common *)chunk2, n, (int)sizeof(double));
        mtmp = b_chunk2->size[1];
        for (n = 0; n < mtmp; n++) {
          itmp = b_chunk2->size[0];
          for (ix = 0; ix < itmp; ix++) {
            chunk2->data[ix + chunk2->size[0] * n] = b_chunk2->data[ix +
              b_chunk2->size[0] * n];
          }
        }
      } else {
        pointer = 3;
        chunk3_value = arr->data[i];
        n = chunk3->size[0] * chunk3->size[1];
        chunk3->size[0] = 1;
        chunk3->size[1] = 1;
        emxEnsureCapacity((emxArray__common *)chunk3, n, (int)sizeof(double));
        chunk3->data[0] = 1.0 + (double)i;
      }
    } else {
      if (pointer == 3) {
        if (arr->data[i] == chunk3_value) {
          if (!((chunk3->size[0] == 0) || (chunk3->size[1] == 0))) {
            mtmp = chunk3->size[1];
          } else {
            mtmp = 0;
          }

          n = b_chunk3->size[0] * b_chunk3->size[1];
          b_chunk3->size[0] = 1;
          b_chunk3->size[1] = mtmp + 1;
          emxEnsureCapacity((emxArray__common *)b_chunk3, n, (int)sizeof(double));
          for (n = 0; n < mtmp; n++) {
            b_chunk3->data[b_chunk3->size[0] * n] = chunk3->data[n];
          }

          b_chunk3->data[b_chunk3->size[0] * mtmp] = 1.0 + (double)i;
          n = chunk3->size[0] * chunk3->size[1];
          chunk3->size[0] = b_chunk3->size[0];
          chunk3->size[1] = b_chunk3->size[1];
          emxEnsureCapacity((emxArray__common *)chunk3, n, (int)sizeof(double));
          mtmp = b_chunk3->size[1];
          for (n = 0; n < mtmp; n++) {
            itmp = b_chunk3->size[0];
            for (ix = 0; ix < itmp; ix++) {
              chunk3->data[ix + chunk3->size[0] * n] = b_chunk3->data[ix +
                b_chunk3->size[0] * n];
            }
          }
        } else {
          /*  new chunk found */
          if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
            n = 0;
          } else {
            n = chunk1->size[1];
          }

          if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
            mtmp = 0;
          } else {
            mtmp = chunk2->size[1];
          }

          if ((chunk3->size[0] == 0) || (chunk3->size[1] == 0)) {
            itmp = 0;
          } else {
            itmp = chunk3->size[1];
          }

          len_tmp[0] = (unsigned int)n;
          len_tmp[1] = (unsigned int)mtmp;
          len_tmp[2] = (unsigned int)itmp;
          mtmp = n;
          itmp = 1;
          for (ix = 2; ix < 4; ix++) {
            if ((int)len_tmp[ix - 1] < mtmp) {
              mtmp = (int)len_tmp[ix - 1];
              itmp = ix;
            }
          }

          if (mtmp <= Prm_smooth_threshold) {
            if (itmp == 1) {
              if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
                n = 0;
              } else {
                n = chunk1->size[1];
              }

              for (m = 0; m < n; m++) {
                arr->data[(int)chunk1->data[m] - 1] = chunk2_value;
              }
            } else if (itmp == 2) {
              mtmp = n;
              for (ix = 1; ix + 1 < 4; ix++) {
                if ((int)len_tmp[ix] > mtmp) {
                  mtmp = (int)len_tmp[ix];
                }
              }

              len_tmp[1] = mtmp + 100U;
              b_mtmp = (unsigned int)n;
              itmp = 1;
              for (ix = 2; ix < 4; ix++) {
                if (len_tmp[ix - 1] < b_mtmp) {
                  b_mtmp = len_tmp[ix - 1];
                  itmp = ix;
                }
              }

              if (itmp == 1) {
                if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
                  n = 0;
                } else {
                  n = chunk2->size[1];
                }

                for (m = 0; m < n; m++) {
                  arr->data[(int)chunk2->data[m] - 1] = chunk1_value;
                }
              } else {
                if (itmp == 3) {
                  if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
                    n = 0;
                  } else {
                    n = chunk2->size[1];
                  }

                  for (m = 0; m < n; m++) {
                    arr->data[(int)chunk2->data[m] - 1] = chunk3_value;
                  }
                }
              }
            } else {
              if ((chunk3->size[0] == 0) || (chunk3->size[1] == 0)) {
                n = 0;
              } else {
                n = chunk3->size[1];
              }

              for (m = 0; m < n; m++) {
                arr->data[(int)chunk3->data[m] - 1] = chunk2_value;
              }
            }
          }

          chunk1_value = arr->data[i];
          chunk2_value = 0.0;
          chunk3_value = 0.0;
          n = chunk1->size[0] * chunk1->size[1];
          chunk1->size[0] = 1;
          chunk1->size[1] = 1;
          emxEnsureCapacity((emxArray__common *)chunk1, n, (int)sizeof(double));
          chunk1->data[0] = 1.0 + (double)i;
          n = chunk2->size[0] * chunk2->size[1];
          chunk2->size[0] = 0;
          chunk2->size[1] = 0;
          emxEnsureCapacity((emxArray__common *)chunk2, n, (int)sizeof(double));
          n = chunk3->size[0] * chunk3->size[1];
          chunk3->size[0] = 0;
          chunk3->size[1] = 0;
          emxEnsureCapacity((emxArray__common *)chunk3, n, (int)sizeof(double));
          pointer = 1;
        }
      }
    }

    if (1.0 + (double)i == arr->size[1]) {
      if (pointer == 2) {
        if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
          n = 0;
        } else {
          n = chunk1->size[1];
        }

        if (n < Prm_smooth_threshold) {
          if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
            n = 0;
          } else {
            n = chunk1->size[1];
          }

          for (m = 0; m < n; m++) {
            arr->data[(int)chunk1->data[m] - 1] = chunk2_value;
          }
        }
      } else {
        if (pointer == 3) {
          if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
            n = 0;
          } else {
            n = chunk1->size[1];
          }

          if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
            mtmp = 0;
          } else {
            mtmp = chunk2->size[1];
          }

          if ((chunk3->size[0] == 0) || (chunk3->size[1] == 0)) {
            itmp = 0;
          } else {
            itmp = chunk3->size[1];
          }

          len_tmp[0] = (unsigned int)n;
          len_tmp[1] = (unsigned int)mtmp;
          len_tmp[2] = (unsigned int)itmp;
          mtmp = n;
          itmp = 1;
          for (ix = 2; ix < 4; ix++) {
            if ((int)len_tmp[ix - 1] < mtmp) {
              mtmp = (int)len_tmp[ix - 1];
              itmp = ix;
            }
          }

          if (mtmp <= Prm_smooth_threshold) {
            if (itmp == 1) {
              if ((chunk1->size[0] == 0) || (chunk1->size[1] == 0)) {
                n = 0;
              } else {
                n = chunk1->size[1];
              }

              for (m = 0; m < n; m++) {
                arr->data[(int)chunk1->data[m] - 1] = chunk2_value;
              }
            } else if (itmp == 2) {
              mtmp = n;
              for (ix = 1; ix + 1 < 4; ix++) {
                if ((int)len_tmp[ix] > mtmp) {
                  mtmp = (int)len_tmp[ix];
                }
              }

              len_tmp[1] = mtmp + 100U;
              b_mtmp = (unsigned int)n;
              itmp = 1;
              for (ix = 2; ix < 4; ix++) {
                if (len_tmp[ix - 1] < b_mtmp) {
                  b_mtmp = len_tmp[ix - 1];
                  itmp = ix;
                }
              }

              if (itmp == 1) {
                if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
                  n = 0;
                } else {
                  n = chunk2->size[1];
                }

                for (m = 0; m < n; m++) {
                  arr->data[(int)chunk2->data[m] - 1] = chunk1_value;
                }
              } else {
                if (itmp == 3) {
                  if ((chunk2->size[0] == 0) || (chunk2->size[1] == 0)) {
                    n = 0;
                  } else {
                    n = chunk2->size[1];
                  }

                  for (m = 0; m < n; m++) {
                    arr->data[(int)chunk2->data[m] - 1] = chunk3_value;
                  }
                }
              }
            } else {
              if ((chunk3->size[0] == 0) || (chunk3->size[1] == 0)) {
                n = 0;
              } else {
                n = chunk3->size[1];
              }

              for (m = 0; m < n; m++) {
                arr->data[(int)chunk3->data[m] - 1] = chunk2_value;
              }
            }
          }
        }
      }
    }

    i++;
  }

  emxFree_real_T(&b_chunk1);
  emxFree_real_T(&b_chunk2);
  emxFree_real_T(&b_chunk3);
  emxFree_real_T(&chunk3);
  emxFree_real_T(&chunk2);
  emxFree_real_T(&chunk1);
}

/*
 * File trailer for Smooth.c
 *
 * [EOF]
 */