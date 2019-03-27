// regression2.h
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#ifndef REGRESSION2_H
#define REGRESSION2_H

#include "calibration_datasets.h"
#include "calibration_datatypes.h"
#include <math.h>
#include <stdio.h>
#include "color.h"

// ------------------------
// CALIBRATION DATA


// CALIBRATION DATA
// ------------------------

long double logistic (
        const long double X[NPARAMS], 
        const long double B[NPARAMS]);

long double h( 
        const long double X[NPARAMS],
        const long double B[NPARAMS]);

bool predict_component(const long double X[NPARAMS], const long double B[NPARAMS]); 

color predict(bool red, bool blue); 

long double regression_cost ( 
            const long double Y[NSEEDS],
            const long double X[NSEEDS][NPARAMS],
            const long double B[NPARAMS]); 

void log_gradient (
              const long double Y[NSEEDS],
              const long double X[NSEEDS][NPARAMS],
                    long double B[NPARAMS],
              long double      lg[NPARAMS]); 

void gradient_descent (
            const long double Y[NSEEDS], 
            const long double X[NSEEDS][NPARAMS], 
                  long double B[NPARAMS], 
            const long double learning_rate, const long double convergence,
            int &runs); 

// formatting data:
// Adds the 1 column to matrix X and normalizes the matrix
void split (
  const calibration_data Cd[NSEEDS],
  long double Ys[2][NSEEDS],
  long double X[NSEEDS][NPARAMS]);

void print_beta (FILE* fp, color c, long double B[NPARAMS]); 

color color_print (FILE *fp, color c);

float accuracy(FILE *fp,
    calibration_data c[NSEEDS], 
    const long double B[2][NPARAMS]); 

void print_csv (FILE *fp, calibration_data C[NSEEDS], long double Y[NSEEDS]);

#endif
