// regression2.cpp
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#include "regression2.h"

long double EX[NSEEDS][NPARAMS] = 
{{1,0.0    ,0.0       },
 {1,0.05   ,0.00728597},
 {1,0.1    ,0.00182149},
 {1,0.15   ,0.22586521},
 {1,0.2    ,0.27140255},
 {1,0.25   ,0.31693989},
 {1,0.3    ,0.36247723},
 {1,0.35   ,0.40801457},
 {1,0.4    ,0.45355191},
 {1,0.45   ,0.36247723},
 {1,0.5    ,0.54462659},
 {1,0.55   ,0.59016393},
 {1,0.6    ,0.63570128},
 {1,0.65   ,0.68123862},
 {1,0.7    ,0.72677596},
 {1,0.75   ,0.7723133 },
 {1,0.8    ,0.81785064},
 {1,0.85   ,0.86338798},
 {1,0.9    ,0.90892532},
 {1,1.0    ,1.0        }};

long double WY[NSEEDS] = 
{0.,0.,0.,0.,0.,0.,1.,0.,1.,0.
,1.,0.,1.,0.,1.,1.,1.,1.,1.,1.};


long double X[NSEEDS][NPARAMS];
long double B[NPARAMS];


void NSEEDS_print(long double k[NSEEDS])
{
    fprintf(stderr, "[");
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(stderr, "[%Lf]",k[i]);
        if (i +1< NSEEDS) fprintf(stderr,"\n");
    }
    fprintf(stderr, "]\n");
}

void NPARAMS_print(long double k[NPARAMS])
{
    fprintf(stderr, "[");
    for (int i = 0; i < NPARAMS; ++i) {
        fprintf(stderr, "%Lf",k[i]);
        if (i +1< NPARAMS) fprintf(stderr,", ");
    }
    fprintf(stderr, "]\n");

}


long double regression_cost ( 
            const long double Y[NSEEDS],
            const long double X[NSEEDS][NPARAMS],
            const long double B[NPARAMS]) 
{
    long double sum;
    long double logistics [NSEEDS];
    long double likelihood[NSEEDS];
  //  long double STEP1DEBUG[NSEEDS];
 //   long double STEP2DEBUG[NSEEDS];
   // long double step1sum = 0;
   // long double step2sum = 0;


    for (int i = 0; i < NSEEDS; ++i) {
        logistics[i] = logistic(X[i],B);
    }

    for (int i = 0; i < NSEEDS; ++i) {
        
        likelihood[i] = -(  Y[i]) * log(    logistics[i]) 
                        -(1-Y[i]) * log(1 - logistics[i]);
        
        //STEP1DEBUG[i] =  (Y[i]) * log(logistics[i]);
      //  STEP2DEBUG[i] =  (1-Y[i]) * log(1 - logistics[i]);
    }
    // NSEEDS_print(logistics);
    sum = 0;
    //step1sum = 0;
    //step2sum = 0;
    for (int i = 0; i < NSEEDS; ++i) {
        sum += likelihood[i];        
    //    step1sum += STEP1DEBUG[i];
    //    step2sum += STEP2DEBUG[i];
    }
    return sum;
}

void log_gradient (
              const long double Y[NSEEDS],
              const long double X[NSEEDS][NPARAMS],
              const long double B[NPARAMS],
              long double      lg[NPARAMS]) 
{
    long double first_calc[NSEEDS];
    
    for (int i = 0; i < NSEEDS; ++i) {
        first_calc[i] = logistic(X[i],B) - Y[i];
    }
    
    for (int j = 0; j < NPARAMS; ++j) {
        lg[j] = 0;
        for (int i = 0; i < NSEEDS; ++i) {
            lg[j] += first_calc[i] * X[i][j];
        }
    }

    return;
}

void gradient_descent (
            const long double Y[NSEEDS], 
            const long double X[NSEEDS][NPARAMS], 
                  long double B[NPARAMS], 
            const long double learning_rate, const long double convergence) 
{
    long double lg [NPARAMS];
    long double cost = regression_cost(Y,X,B);
    long double change_cost = 1;
    long double old_cost;
    int    num_iter = 1;
 
    while (change_cost > convergence) {
        old_cost = cost;
        log_gradient(Y,X,B,lg);
        for (int j = 0; j < NPARAMS; ++j) {
            B[j] = B[j] - learning_rate * lg[j];
        }
//        NPARAMS_print(B);
        cost = regression_cost(Y,X,B);
        change_cost = old_cost - cost;
        ++num_iter;
    } 
    fprintf(stderr, "Total Num Iters: %d\n",num_iter);
}

long double logistic (
        const long double X[NPARAMS], 
        const long double B[NPARAMS])
{
    return ((long double)1.0) / (1 + exp(-h(X,B)));
}

long double h( const long double X[NPARAMS],
          const long double B[NPARAMS]) 
{
    long double sum;
    for (int i = 0; i < NPARAMS; ++i) {
        sum = B[i] * X[i];
    }
    return sum;
}

int main () 
{
    long double Beta[NPARAMS] = {0,0,0};
    gradient_descent(WY,EX,Beta,0.0001,0.00000000000001);
     
}

