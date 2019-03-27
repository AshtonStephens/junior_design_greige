/* 
 * regression.h
 *
 * Purpose: linear regression interface
 * Date: 03/06/18
 * By: Ashton Stephens
 *
 */

#ifndef REGRESSION_H
#define REGRESSION_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "color.h"

#define N_REG_PARAMS 4
#define LEARNING_RATE 0.0000005
#define LOG2_BUCKETS 2

struct calibration_data 
{
   color col;
   int none;
   int blue;
   int both;
   int red;
};

#define N_REG_MEASUREMENTS 16
const calibration_data c[N_REG_MEASUREMENTS] = 
{
  //lights on
  {BLUE  ,310 ,65  ,70  ,311 },
  {BLUE  ,346 ,67  ,71  ,345 },
  {YELLOW,753 ,367 ,496 ,839 },
  {YELLOW,695 ,121 ,357 ,850 }, 
  {RED   ,95  ,17  ,159 ,240 },
  {RED   ,145 ,32  ,219 ,329 },
  {BLACK ,61  ,10  ,29  ,81  },
  {BLACK ,56  ,7   ,23  ,73  },
  // lights off
  {BLUE  ,475 ,41  ,41  ,465 },
  {BLUE  ,420 ,34  ,34  ,412 },
  {YELLOW,452 ,39  ,218 ,604 },
  {YELLOW,545 ,53  ,251 ,681 }, 
  {RED   ,127 ,8   ,181 ,300 },
  {RED   ,123 ,7   ,192 ,305 },
  {BLACK ,50  ,2   ,16  ,68  },
  {BLACK ,63  ,3   ,17  ,81  } 
};

int   split (
        const calibration_data Cd[N_REG_MEASUREMENTS],
        int     Ys[LOG2_BUCKETS][N_REG_MEASUREMENTS],
        float   X[N_REG_MEASUREMENTS][N_REG_PARAMS+1]);

float hypothesis (  
        const float Xi[N_REG_PARAMS+1], 
        const float Bk[N_REG_PARAMS+1]);

float Gradient_Descent_Error (
        int Y[N_REG_MEASUREMENTS],
        float X[N_REG_MEASUREMENTS][N_REG_PARAMS+1], 
        float Bk[N_REG_PARAMS+1]);

/* * * * * Dataset 
 *     ._                   _.
 *     |                     |
 *     | 1 X11 X12 . . . X1p |
 *     | 1 X21 X22 . . . X2p |
 *     | 1 X31 X32 . . . X3p |
 * X = | .  .   .  .      .  |
 *     | .  .   .    .    .  |
 *     | .  .   .      .  .  |
 *     | 1 Xn1 Xn2 . . . Xnp |
 *     |_                   _|
 *
 * Xij = jth value of the ith observation
 *
 * * * * * Coefficients
 *
 *     ._  _.
 *     | B0 |
 *     | B1 |
 *     | B2 |
 * B = | .  |
 *     | .  |
 *     | .  |
 *     | Bp |
 *     |_  _|
 *
 * */

#endif

