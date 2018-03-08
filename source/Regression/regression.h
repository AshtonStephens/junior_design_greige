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
#define N_REG_MEASUREMENTS 10
#define LEARNING_RATE 0.5
#define LOG2_BUCKETS 2

int   split (
        const struct color    Yi[N_REG_MEASUREMENTS],
        int     Ys[LOG2_BUCKETS][N_REG_MEASUREMENTS]);

float hypothesis (  
        const int Xi[N_REG_PARAMS+1], 
        const float Bk[N_REG_PARAMS+1]);

float Gradient_Descent_Error (
        int Y[N_REG_MEASYREMENTS],
        int X[N_REG_MEASUREMENTS][N_REG_PARAMS+1], 
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

