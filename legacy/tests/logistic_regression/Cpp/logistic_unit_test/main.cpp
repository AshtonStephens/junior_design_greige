/* main.cpp
 *
 * to test regression alg
 *
 */

#include <stdio.h>
#include <math.h>
#define NPARAMS 5

long double logistic (
        const long double X[NPARAMS], 
        const long double B[NPARAMS]);

bool predict_component(
        const long double X[NPARAMS], 
        const long double B[NPARAMS]);

long double h( 
        const long double X[NPARAMS],
        const long double B[NPARAMS]);

int main () 
{
    int  runr, runb;
    runr = runb = 0;
    long double B[NPARAMS] = {-1.22319901,3.31577602,0.6326882,-1.59199493,1.08860841};
    long double X[2][NPARAMS] = {{ 1.,0.53808594,0.07617188,0.36621094,0.76171875},
                                 { 1.,0.04492188,0.00292969,0.05664062,0.10253906}};
    fprintf(stderr, "pred_value: %d\n", predict_component(X[0],B));
}

bool predict_component(const long double X[NPARAMS], const long double B[NPARAMS]) 
{
    long double temp =  logistic(X,B);
    fprintf(stderr, "pred_prob: %Lf\n", temp);
    return temp >= 0.5;
}

long double logistic (
        const long double X[NPARAMS], 
        const long double B[NPARAMS])
{
    return ((long double)1.0) / (1 + exp(-h(X,B)));
}

long double h( 
        const long double X[NPARAMS],
        const long double B[NPARAMS]) 
{
    long double sum = 0;
    for (int i = 0; i < NPARAMS; ++i) {
        sum += B[i] * X[i];
    }
    fprintf(stderr, "minus_npdot: %Lf\n", sum);
    return sum;
}
