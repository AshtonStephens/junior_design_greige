
#ifndef CALIBRATION_DATATYPES_H
#define CALIBRATION_DATATYPES_H

#include "color.h"

#define NPARAMS 5
#define NSEEDS  16

struct calibration_data 
{
   color col;
   int  none;
   int  blue;
   int  both;
   int  red ;
};

#endif

