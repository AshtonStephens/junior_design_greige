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
#define NPARAMS 3
#define NSEEDS  20

long double regression_cost ( 
            const long double Y[NSEEDS],
            const long double X[NSEEDS][NPARAMS],
            const long double B[NPARAMS]);

void log_gradient (
              const long double Y[NSEEDS],
              const long double X[NSEEDS][NPARAMS],
              const long double B[NPARAMS],
              long double      lg[NPARAMS]);

void gradient_descent (
            const long double Y[NSEEDS], 
            const long double X[NSEEDS][NPARAMS], 
                  long double B[NPARAMS], 
            const long double learning_rate, const long double convergence);

long double logistic (const long double X[NPARAMS], const long double B[NPARAMS]);

long double h( const long double X[NPARAMS],
          const long double B[NPARAMS]);

#endif
