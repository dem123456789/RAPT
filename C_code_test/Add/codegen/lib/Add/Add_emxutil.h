/*
 * File: Add_emxutil.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 15-Nov-2015 19:57:34
 */

#ifndef __ADD_EMXUTIL_H__
#define __ADD_EMXUTIL_H__

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "Add_types.h"

/* Function Declarations */
extern void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, int
  elementSize);
extern void emxFree_real_T(emxArray_real_T **pEmxArray);
extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for Add_emxutil.h
 *
 * [EOF]
 */
