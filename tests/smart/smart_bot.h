/*
 * smart_state.h
 *
 *
 *
 */

#ifndef SMART_STATE_H
#define SMART_STATE_H

#include "smart_motor.h"
#include "state_machine.h"
#include "csensor.h"
#include "color.h"

class smart_bot 
{
public:
    smart_motor rmotor;
    smart_motor lmotor;
    csensor     sensors;
    state_machine bot_state_machine;

    smart_bot(
        // MOTORS
        int mpin1_R, int mpin2_R,
        int mpin1_L, int mpin2_L,
        // COLOR SENSORS
        int sensor_pin_left, int sensor_pin_right,
        int red_pin, int blue_pin, int stabilization_time, 
        const Betas &redB_left , const Betas &bluB_left,
        const Betas &redB_right, const Betas &bluB_right) :
            rmotor(mpin1_R,mpin2_R),
            lmotor(mpin1_L,mpin2_L),
            sensors(sensor_pin_left,sensor_pin_right,
                    red_pin, blue_pin, stabilization_time,
                    redB_left,bluB_left,redB_right,bluB_right) {}
       
    template <int N> 
    void run (state_initializer (&si)[N],int routine) 
    {
        bot_state_machine.setup(si,routine);

        while (!bot_state_machine.complete()) {
            maintain_hardware();
            poll_sensors();
            bot_state_machine.execute();
        }
    }    

    void maintain_hardware () 
    {
        // maintains the motor behavior
        rmotor.maintain();
        lmotor.maintain(); 
    }

    void poll_sensors ()
    {
        sensors.sense(); 
    }
};

#endif

