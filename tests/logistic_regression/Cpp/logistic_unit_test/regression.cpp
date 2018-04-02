// regression2.cpp
//
// purpose: to properly execute logistic regression
// By: Ashton Stephens
// Date: 3/8/18
//

#include "regression.h"
#include "calibration_datasets.h"

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
    long double sum;
    for (int i = 0; i < NPARAMS; ++i) {
        sum = B[i] * X[i];
    }
    return sum;
}

bool predict_component(const long double X[NPARAMS], const long double B[NPARAMS]) 
{
    long double temp =  logistic(X,B);
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

long double regression_cost ( 
            const long double Y[NSEEDS],
            const long double X[NSEEDS][NPARAMS],
            const long double B[NPARAMS]) 
{
    long double sum;
    long double logistics [NSEEDS];
    long double likelihood[NSEEDS];

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
              const long double Y[NSEEDS],
              const long double X[NSEEDS][NPARAMS],
                    long double B[NPARAMS],
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
            const long double learning_rate, const long double convergence,
            int &runs) 
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
        cost = regression_cost(Y,X,B);
        change_cost = old_cost - cost;
        ++num_iter;
    }
    runs = num_iter; 
}

void split (
  const calibration_data Cd[NSEEDS],
  long double Ys[2][NSEEDS],
  long double X[NSEEDS][NPARAMS])
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
        X[i][1] = Cd[i].none/1023.0;
        X[i][2] = Cd[i].blue/1023.0;
        X[i][3] = Cd[i].both/1023.0;
        X[i][4] = Cd[i].red/ 1023.0;
    }
}

void print_beta (FILE* fp, color c, long double B[NPARAMS]) 
{
    fprintf(fp,"B[(int)");
    color_print (fp, c);
    fprintf(fp,"] = {");
    for (int i = 0; i < NPARAMS; ++i) {
        fprintf(fp,"%Lf",B[i]); 
        if (i+1 < NPARAMS) fprintf(fp, ", "); 
    }
    fprintf(fp,"};");
}

color color_print (FILE *fp, color c)
{
    switch (c) {
        case BLUE:
            fprintf(fp,"BLUE  ");
            break;
        case RED:
            fprintf(fp,"RED   ");
            break;
        case YELLOW:
            fprintf(fp,"YELLOW");
            break;
        case BLACK:
            fprintf(fp,"BLACK ");
            break;
        case NONE:
            fprintf(fp,"NONE  ");
            break;
        case ERR:
            fprintf(fp,"ERR   ");
            break;
        default:
            break;
    }
    return c;
}

float accuracy(FILE *fp,
    calibration_data c[NSEEDS], 
    const long double X[NSEEDS][NPARAMS],
    const long double B[2][NPARAMS]) 
{
    color temp;
    float percent_acc = 0;
    for (int i = 0; i < NSEEDS; ++i) {
        color_print(fp,c[i].col);
        fprintf(fp," = ");
        temp = predict(predict_component(X[i],B[(int)RED ]),
                       predict_component(X[i],B[(int)BLUE]));
        color_print(fp,temp);
        if (c[i].col == temp) 
        {
            percent_acc += 1;
        }
        fprintf(fp,"\n");
    }
    return percent_acc / NSEEDS;
}   

void print_csv (FILE *fp, calibration_data C[NSEEDS], long double Y[NSEEDS])
{
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(fp,"%d",C[i].none);
        if (i + 1 < NSEEDS) fprintf(fp, ", ");
    } 
    fprintf(fp, "\n");
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(fp,"%d",C[i].blue);
        if (i + 1 < NSEEDS) fprintf(fp, ", ");
    }
    fprintf(fp, "\n");
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(fp,"%d",C[i].both);
        if (i + 1 < NSEEDS) fprintf(fp, ", ");
    }
    fprintf(fp, "\n");
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(fp,"%d",C[i].red);
        if (i + 1 < NSEEDS) fprintf(fp, ", ");
    }
    fprintf(fp, "\n");
    for (int i = 0; i < NSEEDS; ++i) {
        fprintf(fp,"%d", (int)(Y[i]));
        if (i + 1 < NSEEDS) fprintf(fp, ", ");
    }   
}

