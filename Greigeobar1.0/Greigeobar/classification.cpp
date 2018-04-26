//
// regression2.cpp
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#include "classification.h"

float hypothesis ( 
        const float X[NPARAMS],
        const float B[NPARAMS+1]) 
{
    float sum = B[0];
    for (int i = 0; i < NPARAMS; ++i) {
        sum += B[i+1] * X[i];
    }
    return sum;
}

float logistic (
        const float X[NPARAMS], 
        const float B[NPARAMS+1])
{
    return ((float)1.0) / (1 + exp(-hypothesis(X,B)));
}

bool predict_component(const float X[NPARAMS], const float B[NPARAMS+1]) 
{
    float temp =  logistic(X,B);
    return temp >= 0.5;
}

color predict(bool red, bool blue) 
{
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

color predict_full (const float X[NPARAMS], const float redB[NPARAMS+1], 
                    const float bluB[NPARAMS+1])
{
    return predict( predict_component(X,redB),
                    predict_component(X,bluB));  
}

