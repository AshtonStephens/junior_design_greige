//
// regression2.cpp
//
// purpose: make prediction of sensor color based on binary sensor 
//          input and input Beta Coefficients
// By: Ashton Stephens
// Date: 3/8/18
//

/* THE PROBLEM:
 *
 * The sensors used on this bot are purely brightness sensors. We 
 * can read in a single analog value between 0-1024 and that's it. 
 * using only those kinds of readings our bot needs to isolate which
 * of the following colors it is currently "looking at":
 * 
 *      RED, BLUE, YELLOW, BLACK
 * 
 * In order to determine which color of paper the robot is looking, 
 * it flashes red and blue lights at the surface of the paper and 
 * uses those readings to figure out the red and blue components of
 * the paper.
 * 
 * WHY MACHINE LEARNING?:
 * 
 * Because the sensors used on this bot vary a lot between devices, 
 * the code needs to determine per sensor, how much the sensor values
 * at different states of the blue and red light flashing actually
 * show the red and blue components of the paper. To compensate for 
 * the variability in the sensors, we use a logistic machine learning
 * algorithm to decide whether there is a strong red component and 
 * strong blue component for each period of the red and blue lights
 * flashing. Because we iterate over 4 states of the blue and red
 * lights on we have four readings that allow us to determine what 
 * color we're on.
 * 
 * (both on -> just red on -> both off -> just blue on -> ...)
 * 
 */

#include "classification.h"

/* perform classification based on sensor values X and Beta values B */

float hypothesis (const float X[NPARAMS], const float B[NPARAMS+1])
{
    float sum = B[0];
    for (int i = 0; i < NPARAMS; ++i) {
        sum += B[i+1] * X[i];
    }
    return sum;
}

float logistic (const float X[NPARAMS], const float B[NPARAMS+1])
{
    return ((float)1.0) / (1 + exp(-hypothesis(X,B)));
}


bool predict_component(const float X[NPARAMS], const float B[NPARAMS+1]) 
{
    float temp =  logistic(X,B);
    return temp >= 0.5;
}

/* make a prediction of what color we're on based on each esimated color */

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

/* predict the full color the sensor is on */

color predict_full (const float X[NPARAMS], const float redB[NPARAMS+1], 
                    const float bluB[NPARAMS+1])
{
    return predict(predict_component(X,redB), predict_component(X,bluB));  
}
