//
// bot.h
//
// Purpose: To define the structure that holds everything
//          pertaining to the autonomous bot
//
// Date: 3-3-18 
// By:  Ashton Stephens and Joseph Ding
//

#ifndef BOT_H
#define BOT_H

#include "color.h"
#include "motor.h"
#include "csensor.h"


class bot 
{

public:
    bot(int mpin1_R, int mpin2_R,
        int mpin1_L, int mpin2_L,
        int sensor_pin_left, int sensor_pin_right,int red_pin, int blue_pin, 
        int stabilization_time, 
        const Betas &redB_left , const Betas &bluB_left,
        const Betas &redB_right, const Betas &bluB_right) :
          motors( mpin1_R,mpin2_R,
                  mpin1_L,mpin2_L),
          sensors(sensor_pin_left,sensor_pin_right,red_pin,blue_pin,
                  stabilization_time,redB_left,bluB_left,redB_right,bluB_right){}
                  
    ~bot(){};
    
    msystem motors;
    csensor sensors;
    
};

#endif
