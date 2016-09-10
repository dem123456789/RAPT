/*
 * File: Preprocess.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 05-Sep-2016 15:50:20
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "Preprocess.h"
#include "yaapt_emxutil.h"

/* Function Definitions */

/*
 * Preprocess the raw data from android voice recorder
 *
 *  Data_in = Raw data android voice recorder
 *  Data_out = Head and tail muted data
 *  The noise comes from opening mic and closing mic
 * Arguments    : const emxArray_real_T *Data_in
 *                emxArray_real_T *Data_out
 * Return Type  : void
 */
void Preprocess(const emxArray_real_T *Data_in, emxArray_real_T *Data_out)
{
  int i0;
  int loop_ub;
  int i1;
  emxArray_int32_T *r3;
  i0 = Data_out->size[0] * Data_out->size[1];
  Data_out->size[0] = 1;
  Data_out->size[1] = Data_in->size[1];
  emxEnsureCapacity((emxArray__common *)Data_out, i0, (int)sizeof(double));
  loop_ub = Data_in->size[0] * Data_in->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Data_out->data[i0] = Data_in->data[i0];
  }

  for (i0 = 0; i0 < 600; i0++) {
    Data_out->data[i0] = 0.0;
  }

  if (Data_out->size[1] - 2000 > Data_out->size[1]) {
    i0 = 1;
    i1 = 0;
  } else {
    i0 = Data_out->size[1] - 2000;
    i1 = Data_out->size[1];
  }

  emxInit_int32_T(&r3, 2);
  loop_ub = r3->size[0] * r3->size[1];
  r3->size[0] = 1;
  r3->size[1] = (i1 - i0) + 1;
  emxEnsureCapacity((emxArray__common *)r3, loop_ub, (int)sizeof(int));
  loop_ub = (i1 - i0) + 1;
  for (i1 = 0; i1 < loop_ub; i1++) {
    r3->data[r3->size[0] * i1] = (i0 + i1) - 1;
  }

  loop_ub = r3->size[0] * r3->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    Data_out->data[r3->data[i0]] = 0.0;
  }

  emxFree_int32_T(&r3);
}

/*
 * File trailer for Preprocess.c
 *
 * [EOF]
 */