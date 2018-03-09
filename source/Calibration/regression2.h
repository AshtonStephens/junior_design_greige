// regression2.h
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#ifndef REGRESSION2_H
#define REGRESSION2_H

#include <math.h>
#include <stdio.h>
#include "color.h"
#define NPARAMS 4
#define NSEEDS  32

struct calibration_data 
{
   color col;
   int none;
   int blue;
   int both;
   int red;
};

void split (
  const calibration_data Cd[NSEEDS],
  double Y[2][NSEEDS],
  double X[NSEEDS][NPARAMS]);
            
double regression_cost ( 
            const double Y[NSEEDS],
            const double X[NSEEDS][NPARAMS],
            const double B[NPARAMS]);

void log_gradient (
              const double Y[NSEEDS],
              const double X[NSEEDS][NPARAMS],
              const double B[NPARAMS],
              double      lg[NPARAMS]);

void gradient_descent (
            const double Y[NSEEDS], 
            const double X[NSEEDS][NPARAMS], 
                  double B[NPARAMS], 
            const double learning_rate, const double convergence, int &runs);

double logistic (const double X[NPARAMS], const double B[NPARAMS]);

double h( const double X[NPARAMS],
          const double B[NPARAMS]);
#endif
