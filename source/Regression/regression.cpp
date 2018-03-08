/* 
 * regression.cpp
 *
 * Purpose: linear regression implementation
 * Date: 03/07/18
 * By: Ashton Stephens
 *
 */

#include "regression.h"

static inline float fabs(float a);

int   split (
        const struct color    Yi[N_REG_MEASUREMENTS],
        int     Ys[LOG2_BUCKETS][N_REG_MEASUREMENTS])
{
    // Breaks up the classification of the sepatate classes
    // into binary decisions. Since we have 4 different colors
    // to decide between we are using 2 binary decisions to 
    // determine the classificaton.
    //
    // Logically it made sense to break this up into red detect
    // versus blue detect
    for (int i = 0; i < N_REG_MEASUREMENTS; ++i) {
        switch (Yi[i]) {
            case BLUE:
                Ys[(int)BLUE][i] = 1;
                Ys[(int)RED ][i] = 0;
                break;
            case RED:
                Ys[(int)BLUE][i] = 0;
                Ys[(int)RED ][i] = 1;
                break;
            case YELLOW:
                Ys[(int)BLUE][i] = 1;
                Ys[(int)RED ][i] = 1;
                break;
            case BLACK:
                Ys[(int)BLUE][i] = 0;
                Ys[(int)RED ][i] = 0;
                break;
            case default:
                Ys[(int)BLUE][i] = 0;
                Ys[(int)RED ][i] = 0;
                break;
        } 
    }
}

color classification (float red, float blue)
{
    // _____ DEBUG _____
    Serial.print("{classification}:");
    Serial.print("[ R: ");
    Serial.print(red);
    Serial.print("| B: ");
    Serial.print(blue);
    Serial.print("]");
    Serial.print("REMEMBER TO REMOVE ALSO DEBUGGG! :)");
    Serial.print("\n");

    // _____ DEBUG _____
    
    if (red) {
        if (blue) {
            return YELLOW;
        } else {
            return RED;
        }
    } else {
        if (blue) {
            return BLUE;
        } else {
            return BLACK;
        } 
    }
}


float hypothesis (
        const int Xi[N_REG_PARAMS+1], 
        const float Bk[N_REG_PARAMS+1]) 
{
    // Linear summation of B[i] with X[i]
    for (int i = 0; i < N_REG_PARAMS; ++i) {
        sum = Bk[i] * Xi[i];
    }
}

float Gradient_Descent_Error (
        int Y[N_REG_MEASYREMENTS],
        int X[N_REG_MEASUREMENTS][N_REG_PARAMS+1], 
        float Bk[N_REG_PARAMS+1])
{
    static float Bk_buff [N_REG_PARAMS+1];
    float sum, diff, diff_check;

    for (int j = 0; j < N_REG_PARAMS+1; ++j) {
        sum = 0;
        for (int i = 0; i < N_REG_MEASUREMENTS; ++i) {
            sum += (hypothesis(X[i], Bk) - (float)Y[i]) * X[i][j];
        }
        Bk_buff[j] = Bk[j] - LEARNING_RATE * sum;
    }
    
    diff = 0;
    diff_check = 0;
    for (int j = 0; j < N_REG_PARAMS+1; ++j) {
        diff_check = Bk[j] - Bk_buff[j]; // get diff
        Bk[j] = Bk_buff[j];              // update coeff
        diff_check = fabs(diff_check);   // get abs of diff
        if (diff_check > diff) {         
            diff = diff_check;           // set diff if greatest diff
        }
    }
    return diff;
}

// -------------------------------------------------
// Helper Functions 
// -------------------------------------------------

static inline float fabs(float a)
{
    if (a < 0) return a*-1;
    return a;
}
