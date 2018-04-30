/*
 * smart_bot.h
 *
 *
 *
 */

#ifndef SMART_STATE_H
#define SMART_STATE_H

#include "DEBUGME.h"
#include "smart_motor.h"
#include "state_machine.h"
#include "csensor.h"
#include "color.h"
#include "lights.h"

void collision_detect ();
void hall_detect ();
void nothing ();

class smart_bot 
{
public:

    int routine;
    
    lights leds;

    int comms_sending;
    int comms_receiving;
    
    smart_motor rmotor;
    smart_motor lmotor;
    int mpinE; // motor enable
    int hall_pin;
    int collision_pin;
    csensor     sensors;
    state_machine bot_state_machine;
    bool hardware_on; 

    bool hall_interrupt;
    bool collision_interrupt; 
    
    smart_bot(
        //  LEDS
        int yellow_path_pin, int blue_path_pin,  int red_path_pin,
        int green_state_pin, int blue_state_pin, int red_state_pin,
        int headlights_pin,  int breaklights_pin,
        int lturn_pin,       int rturn_pin,
        // MOTORS
        int mpin1_R, int mpin2_R,
        int mpin1_L, int mpin2_L, int mpinE,
        int comms_sending, int comms_receiving,
        // COLOR SENSORS
        int sensor_pin_left, int sensor_pin_right,
        int hall_pin, int collision_pin,
        int red_pin, int blue_pin, int stabilization_time, 
        const Betas &redB_left , const Betas &bluB_left,
        const Betas &redB_right, const Betas &bluB_right) :
            routine(0),
            leds (yellow_path_pin, blue_path_pin,  red_path_pin,
            green_state_pin, blue_state_pin, red_state_pin,
            headlights_pin,  breaklights_pin,
            lturn_pin,       rturn_pin),
            comms_sending(comms_sending), 
            comms_receiving(comms_receiving), 
            rmotor(mpin1_R,mpin2_R),
            lmotor(mpin1_L,mpin2_L), mpinE(mpinE),
            hall_pin(hall_pin), collision_pin(collision_pin),
            sensors(sensor_pin_left,sensor_pin_right,
                    red_pin, blue_pin, stabilization_time,
                    redB_left,bluB_left,redB_right,bluB_right), 
                    hardware_on(true), hall_interrupt(0), collision_interrupt(0)
                    {pinMode (mpinE,OUTPUT);digitalWrite(mpinE,HIGH);}
       
    template <int N> 
    void run_ (state_initializer (&si)[N],int routine) 
    {
        
        this-> routine = routine;
        bot_state_machine.setup(si,routine);

        while (!bot_state_machine.complete()) {
            if (hardware_on) {
                poll_sensors();
            } else {
                Serial.println("HARDWARE OFF");
                digitalWrite(mpinE,LOW);
                rmotor.off();
                lmotor.off(); 
                sensors.off();
            }
            maintain_hardware();
            bot_state_machine.execute();
        }
    }

    void handle_hall_interrupt()
    {
        bot_state_machine.stack_push(HALL_INTERRUPT);
    }
    
    void handle_collision_interrupt()
    {
        bot_state_machine.stack_push(COLLISION_INTERRUPT);
    }

    void maintain_hardware () 
    {
        // maintains the motor behavior
        rmotor.maintain();
        lmotor.maintain();
        if (rmotor.decelerating() && lmotor.decelerating()) leds.breaklights.on_solid();
        leds.maintain();
        leds.reset();
    }

    void show_following_path(color C)
    {
        switch (C) {
            case RED:
                    leds.red_path.on_solid();
                break;
            case BLUE:
                    leds.blue_path.on_solid();
                break;
            case YELLOW:
                    leds.yellow_path.on_solid();
                break;
        }
    }

    void sending_on() {digitalWrite(comms_sending, HIGH);}
    void sending_off() {digitalWrite(comms_sending, LOW );}
    bool receiving ()  {return digitalRead(comms_receiving);}
    void poll_sensors () {sensors.sense();}

    void disable_hall_interrupt      () {attachInterrupt(digitalPinToInterrupt(hall_pin), nothing, FALLING);}
    void disable_collision_interrupt () {attachInterrupt(digitalPinToInterrupt(collision_pin), nothing, FALLING);}
    
    void enable_hall_interrupt () 
    {
        hall_interrupt = false;
        attachInterrupt(digitalPinToInterrupt(hall_pin), hall_detect, FALLING);
    }
    
    void enable_collision_interrupt () {
        collision_interrupt = false;
        attachInterrupt(digitalPinToInterrupt(collision_pin), collision_detect, FALLING);
    }


    
};

#endif

