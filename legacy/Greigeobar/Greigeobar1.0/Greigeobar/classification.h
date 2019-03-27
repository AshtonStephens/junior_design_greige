// 
// regression2.h
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include "color.h"
#include "math.h"

#define NPARAMS 4

float hypothesis (
                const float X[NPARAMS], 
                const float B[NPARAMS+1]);

float logistic (const float X[NPARAMS], 
                const float B[NPARAMS+1]);

bool predict_component (
                const float X[NPARAMS], 
                const float B[NPARAMS+1]); 

color predict(
                bool red, 
                bool blue); 

color predict_full (
                const float X[NPARAMS], 
                const float redB[NPARAMS+1], 
                const float bluB[NPARAMS+1]);
#endif
