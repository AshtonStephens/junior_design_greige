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
        const calibration_data Cd[N_REG_MEASUREMENTS],
        int     Ys[LOG2_BUCKETS][N_REG_MEASUREMENTS],
        float     X[N_REG_MEASUREMENTS][N_REG_PARAMS+1])
{
    // Breaks up the classification of the sepatate classes
    // into binary decisions. Since we have 4 different colors
    // to decide between we are using 2 binary decisions to 
    // determine the classificaton.
    //
    // Logically it made sense to break this up into red detect
    // versus blue detect
    for (int i = 0; i < N_REG_MEASUREMENTS; ++i) {
        switch (Cd[i].col) {
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
            default:
                Ys[(int)BLUE][i] = 0;
                Ys[(int)RED ][i] = 0;
                break;
        }
        X[i][0] = 1;
        X[i][1] = Cd[i].none/1023.0;
        X[i][2] = Cd[i].blue/1023.0;
        X[i][3] = Cd[i].both/1023.0;
        X[i][4] = Cd[i].red/1023.0;
    }
}

color classification (float red, float blue)
{
    // _____ DEBUG _____
    /*Serial.print("{classification}:");
    Serial.print("[ R: ");
    Serial.print(red);
    Serial.print("| B: ");
    Serial.print(blue);
    Serial.print("]");
    Serial.print("REMEMBER TO REMOVE ALSO DEBUGGG! :)");
    Serial.print("\n");
    */
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
        const float Xi[N_REG_PARAMS+1], 
        const float Bk[N_REG_PARAMS+1]) 
{
    // Linear summation of B[i] with X[i]
    float sum;
    for (int i = 0; i < N_REG_PARAMS; ++i) {
        sum = Bk[i] * Xi[i];
    }
    return sum;
}

float Gradient_Descent_Error (
        int Y[N_REG_MEASUREMENTS],
        float X[N_REG_MEASUREMENTS][N_REG_PARAMS+1], 
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
