/* main.cpp
 *
 * to test regression alg
 *
 */

#include "regression.h"
#include "calibration_datasets.h"

int main () 
{
    int  runr, runb;
    runr = runb = 0;

    long double X[NSEEDS][NPARAMS];
    long double B[2][NPARAMS];
    long double Y[2][NSEEDS];
    float learning_rate = 0.0001;
    float precision     = 0.0001;
    float accuracy_sum  = 0.0;

    // allocates the seed data
    split(C1,Y,X); 
    
    for (int i = 0; i < NPARAMS; ++i) {
        B[0][i] = 0;
        B[1][i] = 0;
    }
    
    gradient_descent(Y[(int)BLUE],X,B[(int)BLUE],learning_rate,precision, runb);
    print_beta(stderr,BLUE,B[(int)BLUE]);  
    fprintf   (stderr,"\n");
    
    gradient_descent(Y[(int)RED] ,X,B[(int)RED] ,learning_rate,precision, runr);
    print_beta(stderr,RED,B[(int)RED]);  
    fprintf   (stderr,"\n");
     
    //fprintf   (stderr,"\033[31mred(%d) \033[34mblue(%d)\033[0m\n",runr, runb);
    
    accuracy_sum += accuracy(stderr,C1,B); 
    accuracy_sum += accuracy(stderr,C2,B); 
    accuracy_sum += accuracy(stderr,C3,B); 
    accuracy_sum += accuracy(stderr,C4,B); 
    accuracy_sum += accuracy(stderr,C5,B); 
    accuracy_sum += accuracy(stderr,C6,B); 
    accuracy_sum += accuracy(stderr,C7,B); 

    fprintf(stderr,"accuracy total = %f\n",accuracy_sum/7);
}


