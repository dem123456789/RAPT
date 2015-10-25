/*
 * File: peaks.c
 *
 * MATLAB Coder version            : 2.6
 * C/C++ source code generated on  : 25-Oct-2015 03:48:36
 */

/* Include files */
#include "rt_nonfinite.h"
#include "yaapt.h"
#include "peaks.h"
#include "eml_sort.h"
#include "yaapt_emxutil.h"
#include "mean.h"
#include "rdivide.h"

/* Function Definitions */

/*
 * PEAKS  find peaks in SHC
 *
 *    [Pitch,Merit] = peaks(Data, delta, maxpeaks, Prm)
 *    computes peaks in a frequency domain function
 *    associated with the peaks found in each frame based on the
 *    correlation sequence.
 *
 * INPUTS:
 *    Data:  The input signal(either autocorrelated/normalized cross correlated).
 *    delta: The resolution of spectrum
 *    maxpeaks: The max number of peaks picked
 *    Prm:   Parameters
 *
 * OUTPUTS:
 *    Pitch:  The Pitch/Pitch values for the peaks found for each frame.
 *    Merit:  The Merit values of the peaks found in each frame.
 * Arguments    : emxArray_real_T *Data
 *                double delta
 *                double Pitch_data[]
 *                int Pitch_size[2]
 *                double Merit_data[]
 *                int Merit_size[2]
 * Return Type  : void
 */
void peaks(emxArray_real_T *Data, double delta, double Pitch_data[], int
           Pitch_size[2], double Merit_data[], int Merit_size[2])
{
  double max_lag;
  double width;
  double center;
  double min_lag;
  double Pitch[4];
  double Merit[4];
  int i8;
  int i9;
  int ixstart;
  double mtmp;
  int ix;
  boolean_T exitg2;
  emxArray_real_T *b_Data;
  emxArray_real_T *c_Data;
  int i10;
  double avg_data;
  int numpeaks;
  int n;
  double b_n;
  int itmp;
  boolean_T exitg1;
  double b_Merit[4];
  int iidx[4];
  int tmp_data[3];

  /*   Creation date:   March 1, 2006 */
  /*   Revision dates:  March 11, 2006,  Jun 26, 2006, July 27, 2007 */
  /*   Programmer: S.A.Zahorian, Princy  Dikshit, Hongbing Hu */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*      This file is a part of the YAAPT program, designed for a fundamental  */
  /*    frequency tracking algorithm that is extermely robust for both high quality  */
  /*    and telephone speech.   */
  /*      The YAAPT program was created by the Speech Communication Laboratory of */
  /*    the state university of New York at Binghamton. The program is available  */
  /*    at http://www.ws.binghamton.edu/zahorian as free software. Further  */
  /*    information about the program could be found at "A spectral/temporal  */
  /*    method for robust fundamental frequency tracking," J.Acosut.Soc.Am. 123(6),  */
  /*    June 2008. */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* -- PARAMETERS ---------------------------------------------------------------- */
  /*  Threshold for max avaliable peak */
  /*  Threshold for available peaks */
  /* -- COMPUTED VARIABLES -------------------------------------------------------- */
  /*  Length in Hz of range(must be largest to be a peak) */
  max_lag = 50.0 / delta;
  if (max_lag < 0.0) {
    width = ceil(max_lag);
  } else {
    width = floor(max_lag);
  }

  /*  Window width in sample */
  if (width - floor(width / 2.0) * 2.0 == 0.0) {
    width++;
  }

  /*  The center of the window is defined as the peak location. */
  center = ceil(width / 2.0);

  /*  Lowest frequency at which F0 is allowed */
  max_lag = 60.0 / delta - width / 4.0;
  if (max_lag < 0.0) {
    min_lag = ceil(max_lag);
  } else {
    min_lag = floor(max_lag);
  }

  /*  Highest frequency at which F0 is allowed */
  max_lag = 400.0 / delta + width / 4.0;
  if (max_lag < 0.0) {
    max_lag = ceil(max_lag);
  } else {
    max_lag = floor(max_lag);
  }

  if (min_lag < 1.0) {
    min_lag = 1.0;
  }

  if (max_lag > (double)Data->size[1] - width) {
    max_lag = (double)Data->size[1] - width;
  }

  /* -- INITIALIZATION ----------------------------------------------------------- */
  for (i8 = 0; i8 < 4; i8++) {
    Pitch[i8] = 0.0;

    /*  Peak(Pitch) candidates */
    Merit[i8] = 0.0;
  }

  /*  Merits for peaks */
  /* -- MAIN ROUTINE -------------------------------------------------------------- */
  /*  Normalize the signal so that peak value = 1 */
  if (min_lag > max_lag) {
    i8 = 0;
    i9 = 0;
  } else {
    i8 = (int)min_lag - 1;
    i9 = (int)max_lag;
  }

  ixstart = 1;
  mtmp = Data->data[i8];
  if (i9 - i8 > 1) {
    if (rtIsNaN(mtmp)) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix <= i9 - i8)) {
        ixstart = ix;
        if (!rtIsNaN(Data->data[(i8 + ix) - 1])) {
          mtmp = Data->data[(i8 + ix) - 1];
          exitg2 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < i9 - i8) {
      for (ix = ixstart - 1; ix + 2 <= i9 - i8; ix++) {
        if (Data->data[(i8 + ix) + 1] > mtmp) {
          mtmp = Data->data[(i8 + ix) + 1];
        }
      }
    }
  }

  if (mtmp > 1.0E-14) {
    emxInit_real_T(&b_Data, 2);
    i8 = b_Data->size[0] * b_Data->size[1];
    b_Data->size[0] = 1;
    b_Data->size[1] = Data->size[1];
    emxEnsureCapacity((emxArray__common *)b_Data, i8, (int)sizeof(double));
    ixstart = Data->size[0] * Data->size[1];
    for (i8 = 0; i8 < ixstart; i8++) {
      b_Data->data[i8] = Data->data[i8];
    }

    c_rdivide(b_Data, mtmp, Data);
    emxFree_real_T(&b_Data);
  }

  /*  If true there are no large peaks and we assume that signal is unvoiced */
  if (min_lag > max_lag) {
    i8 = 0;
    i9 = 0;
  } else {
    i8 = (int)min_lag - 1;
    i9 = (int)max_lag;
  }

  emxInit_real_T(&c_Data, 2);
  i10 = c_Data->size[0] * c_Data->size[1];
  c_Data->size[0] = 1;
  c_Data->size[1] = i9 - i8;
  emxEnsureCapacity((emxArray__common *)c_Data, i10, (int)sizeof(double));
  ixstart = i9 - i8;
  for (i9 = 0; i9 < ixstart; i9++) {
    c_Data->data[c_Data->size[0] * i9] = Data->data[i8 + i9];
  }

  avg_data = mean(c_Data);
  emxFree_real_T(&c_Data);
  if (avg_data > 0.2) {
    /*     numpeaks = 0; */
    Pitch_size[0] = 1;
    Pitch_size[1] = 4;
    Merit_size[0] = 1;
    Merit_size[1] = 4;
    for (i8 = 0; i8 < 4; i8++) {
      Pitch_data[i8] = 0.0;
      Merit_data[i8] = 1.0;
    }

    /*  force an early end for unoviced frame  */
  } else {
    /*  Step 1 */
    /*  Find all peaks for search range */
    /*  a "peak" must be the higher than a specfied number of */
    /*  points on either side of point.  Peaks are further "cleaned" */
    /*  up, to retain only best peaks i.e. peaks which do not meet certain */
    /*  criteria are eliminated. */
    numpeaks = -1;
    i8 = (int)(max_lag + (1.0 - min_lag));
    for (n = 0; n < i8; n++) {
      b_n = min_lag + (double)n;
      max_lag = (b_n + width) - 1.0;
      if (b_n > max_lag) {
        i9 = 0;
        i10 = 0;
      } else {
        i9 = (int)b_n - 1;
        i10 = (int)max_lag;
      }

      ixstart = 1;
      mtmp = Data->data[i9];
      itmp = 1;
      if (i10 - i9 > 1) {
        if (rtIsNaN(mtmp)) {
          ix = 2;
          exitg1 = false;
          while ((!exitg1) && (ix <= i10 - i9)) {
            ixstart = ix;
            if (!rtIsNaN(Data->data[(i9 + ix) - 1])) {
              mtmp = Data->data[(i9 + ix) - 1];
              itmp = ix;
              exitg1 = true;
            } else {
              ix++;
            }
          }
        }

        if (ixstart < i10 - i9) {
          for (ix = ixstart + 1; ix <= i10 - i9; ix++) {
            if (Data->data[(i9 + ix) - 1] > mtmp) {
              mtmp = Data->data[(i9 + ix) - 1];
              itmp = ix;
            }
          }
        }
      }

      /*  find peaks which are larger than threshold    */
      if ((itmp == center) && (mtmp > 1.25 * avg_data)) {
        /*  Note Pitch(1) = delta, Pitch(2) = 2*delta */
        /*  Convert FFT indices to Pitch in Hz */
        numpeaks++;
        Pitch[numpeaks] = ((b_n + center) - 1.0) * delta;
        Merit[numpeaks] = mtmp;
      }
    }

    /*  Step 2 */
    /*  Be sure there is large peak */
    mtmp = Merit[0];
    for (ix = 1; ix + 1 < 5; ix++) {
      if (Merit[ix] > mtmp) {
        mtmp = Merit[ix];
      }
    }

    if (mtmp / avg_data < 5.0) {
      /*    numpeaks = 0; */
      Pitch_size[0] = 1;
      Pitch_size[1] = 4;
      Merit_size[0] = 1;
      Merit_size[1] = 4;
      for (i8 = 0; i8 < 4; i8++) {
        Pitch_data[i8] = 0.0;
        Merit_data[i8] = 1.0;
      }
    } else {
      /*  Step 3     */
      /*  Order the peaks according to size,  considering at most maxpeaks */
      for (i8 = 0; i8 < 4; i8++) {
        b_Merit[i8] = Merit[i8];
      }

      eml_sort(b_Merit, Merit, iidx);
      for (i8 = 0; i8 < 4; i8++) {
        b_Merit[i8] = Pitch[iidx[i8] - 1];
      }

      for (i8 = 0; i8 < 4; i8++) {
        Pitch[i8] = b_Merit[i8];
      }

      /*  keep the number of peaks not greater than max number */
      if (1 > numpeaks + 1) {
        ixstart = 0;
      } else {
        ixstart = numpeaks + 1;
      }

      Pitch_size[0] = 1;
      Pitch_size[1] = ixstart;
      for (i8 = 0; i8 < ixstart; i8++) {
        Pitch_data[i8] = Pitch[i8];
      }

      if (1 > numpeaks + 1) {
        ixstart = 0;
      } else {
        ixstart = numpeaks + 1;
      }

      Merit_size[0] = 1;
      Merit_size[1] = ixstart;
      for (i8 = 0; i8 < ixstart; i8++) {
        Merit_data[i8] = Merit[i8];
      }

      /*  Step 4 */
      /*  Insert candidates to reduce pitch doubling and pitch halving, if needed */
      if (numpeaks + 1 > 0) {
        /*  if best peak has F < this, insert peak at 2F */
        if (Pitch[0] > 150.0) {
          if (numpeaks + 2 <= 4) {
            numpeaks++;
          } else {
            numpeaks = 3;
          }

          Pitch_data[numpeaks] = Pitch[0] / 2.0;

          /*  Set merit for inserted peaks */
          Merit_data[numpeaks] = 0.4;
        }

        /*  If best peak has F > this, insert peak at half F */
        if (Pitch_data[0] < 150.0) {
          if (numpeaks + 2 <= 4) {
            numpeaks++;
          } else {
            numpeaks = 3;
          }

          Pitch_data[numpeaks] = 2.0 * Pitch_data[0];
          Merit_data[numpeaks] = 0.4;
        }

        /*  Fill in  frames with less than maxpeaks with best choice */
        if (numpeaks + 1 < 4) {
          i8 = numpeaks - 3;
          ixstart = -i8;
          for (i9 = 0; i9 < ixstart; i9++) {
            tmp_data[i9] = (i8 + i9) + 4;
          }

          max_lag = Pitch_data[0];
          ixstart = -i8;
          for (i8 = 0; i8 < ixstart; i8++) {
            Pitch_data[tmp_data[i8]] = max_lag;
          }

          i8 = numpeaks - 3;
          ixstart = -i8;
          for (i9 = 0; i9 < ixstart; i9++) {
            tmp_data[i9] = (i8 + i9) + 4;
          }

          max_lag = Merit_data[0];
          ixstart = -i8;
          for (i8 = 0; i8 < ixstart; i8++) {
            Merit_data[tmp_data[i8]] = max_lag;
          }
        }
      } else {
        Pitch_size[0] = 1;
        Pitch_size[1] = 4;
        Merit_size[0] = 1;
        Merit_size[1] = 4;
        for (i8 = 0; i8 < 4; i8++) {
          Pitch_data[i8] = 0.0;
          Merit_data[i8] = 1.0;
        }
      }
    }
  }

  /* ============================================================================== */
}

/*
 * File trailer for peaks.c
 *
 * [EOF]
 */
