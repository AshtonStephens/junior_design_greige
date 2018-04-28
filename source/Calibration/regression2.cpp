// regression2.cpp
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#include "regression2.h"
#include "arduino.h"

void split (
  const calibration_data Cd[NSEEDS],
  double Ys[2][NSEEDS],
  double X[NSEEDS][NPARAMS])
{
    // Breaks up the classification of the sepatate classes
    // into binary decisions. Since we have 4 different colors
    // to decide between we are using 2 binary decisions to 
    // determine the classificaton.
    //
    // Logically it made sense to break this up into red detect
    // versus blue detect
    for (int i = 0; i < NSEEDS; ++i) {
      
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
        X[i][2] = Cd[i].blue/1023.0;
        X[i][4] = Cd[i].red/ 1023.0;
    }
}

double regression_cost ( 
            const double Y[NSEEDS],
            const double X[NSEEDS][NPARAMS],
            const double B[NPARAMS]) 
{
    double sum;
    double logistics [NSEEDS];
    double likelihood[NSEEDS];
    
    for (int i = 0; i < NSEEDS; ++i) {
        logistics[i] = logistic(X[i],B);
    }

    for (int i = 0; i < NSEEDS; ++i) {
        
        likelihood[i] = -(  Y[i]) * log(    logistics[i]) 
                        -(1-Y[i]) * log(1 - logistics[i]);
    }
    sum = 0;
    for (int i = 0; i < NSEEDS; ++i) {
        sum += likelihood[i];        
    }
    return sum;
}

void log_gradient (
              const double Y[NSEEDS],
              const double X[NSEEDS][NPARAMS],
              const double B[NPARAMS],
              double      lg[NPARAMS]) 
{
    double first_calc[NSEEDS];
    /*
    for (int i = 0; i < NSEEDS; ++i) {
        first_calc[i] = logistic(X[i],B) - Y[i];
    }
    
    for (int j = 0; j < NPARAMS; ++j) {
        lg[j] = 0;
        for (int i = 0; i < NSEEDS; ++i) {
            lg[j] += first_calc[i] * X[i][j];
        }
    }
    */
    return;
}

void gradient_descent (
            const double Y[NSEEDS], 
            const double X[NSEEDS][NPARAMS], 
                  double B[NPARAMS], 
            const double learning_rate, const double convergence, int &runs) 
{
    double lg [NPARAMS];
    double cost = regression_cost(Y,X,B);
    double change_cost = 1;
    double old_cost;
    int    num_iter = 1;
    
    
    while (change_cost > convergence) {
        old_cost = cost;
        
        
        log_gradient(Y,X,B,lg);
        
        B[0] = 0;
        B[1] = 0;
        B[2] = 0;
        B[3] = 0;
        
        //for (int j = 0; j < NPARAMS; ++j) {B[j] = 0;}
        
        /*
        for (int j = 0; j < NPARAMS; ++j) {
            B[j] = B[j] - learning_rate * lg[j];
        }
                    
        cost = regression_cost(Y,X,B);
        change_cost = old_cost - cost;
        */
        
        ++num_iter;
    } 
   
    //runs = num_iter;
}

double logistic (
        const double X[NPARAMS], 
        const double B[NPARAMS])
{
    return ((double)1.0) / (1 + exp(-h(X,B)));
}

double h( const double X[NPARAMS],
          const double B[NPARAMS]) 
{
    double sum;
    for (int i = 0; i < NPARAMS; ++i) {
        sum = B[i] * X[i];
    }
    return sum;
}

