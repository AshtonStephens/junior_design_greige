/*
 * smart_state.h
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

class smart_bot 
{
public:


    int routine;
    
    int yellow_path_led; 
    int blue_path_led; 
    int red_path_led;

    int green_state_led; 
    int blue_state_led; 
    int red_state_led;

    int comms_sending;
    int comms_receiving;
    
    smart_motor rmotor;
    smart_motor lmotor;
    int mpinE; // motor enable
    csensor     sensors;
    state_machine bot_state_machine;
    bool hardware_on; 

    char hall_interrupt;
    char collision_interrupt; 
    
    char hall_interrupt_last;
    char collision_interrupt_last;
    
    smart_bot(
        //  LEDS
        int yellow_path_led, int blue_path_led, int red_path_led,
        int green_state_led, int blue_state_led, int red_state_led,
        // MOTORS
        int mpin1_R, int mpin2_R,
        int mpin1_L, int mpin2_L, int mpinE,
        int comms_sending, int comms_receiving,
        // COLOR SENSORS
        int sensor_pin_left, int sensor_pin_right,
        int red_pin, int blue_pin, int stabilization_time, 
        const Betas &redB_left , const Betas &bluB_left,
        const Betas &redB_right, const Betas &bluB_right) :
            routine(0),
            yellow_path_led(yellow_path_led),  
            blue_path_led(blue_path_led), 
            red_path_led(red_path_led),
            green_state_led(green_state_led),
            blue_state_led(blue_state_led), 
            red_state_led(red_state_led),
            comms_sending(comms_sending), 
            comms_receiving(comms_receiving), 
            rmotor(mpin1_R,mpin2_R),
            lmotor(mpin1_L,mpin2_L), mpinE(mpinE),
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

        hall_interrupt_last      = hall_interrupt;
        collision_interrupt_last = collision_interrupt;

        while (!bot_state_machine.complete()) {
            check_interrupts();
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

    void check_interrupts()
    {
        if (hall_interrupt_last != hall_interrupt) {
            hall_interrupt_last = hall_interrupt;
            handle_hall_interrupt();
        }
        
        if (collision_interrupt_last != collision_interrupt) {
            collision_interrupt_last = collision_interrupt;
            handle_collision_interrupt();
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
    }

    void show_following_path(color C)
    {
        switch (C) {
            case RED:
                digitalWrite(yellow_path_led,LOW);
                digitalWrite(red_path_led   ,HIGH);
                digitalWrite(blue_path_led  ,LOW);
                break;
            case BLUE:
                digitalWrite(yellow_path_led,LOW);
                digitalWrite(red_path_led   ,LOW);
                digitalWrite(blue_path_led  ,HIGH);
                break;
            case YELLOW:
                digitalWrite(yellow_path_led,HIGH);
                digitalWrite(red_path_led   ,LOW);
                digitalWrite(blue_path_led  ,LOW);
                break;
            default:
                digitalWrite(yellow_path_led,LOW);
                digitalWrite(red_path_led   ,LOW);
                digitalWrite(blue_path_led  ,LOW);
                break;
        }
    }

    void sending_on() {digitalWrite(comms_sending, HIGH);}
    void sending_off() {digitalWrite(comms_sending, LOW );}

    bool receiving ()  {return digitalRead(comms_receiving);}

    void green_state_led_on () {digitalWrite(green_state_led, HIGH);}
    void green_state_led_off() {digitalWrite(green_state_led, LOW );}
    
    void blue_state_led_on () {digitalWrite(blue_state_led, HIGH);}
    void blue_state_led_off() {digitalWrite(blue_state_led, LOW );}
    
    void red_state_led_on () {digitalWrite(red_state_led, HIGH);}
    void red_state_led_off() {digitalWrite(red_state_led, LOW );} 
 
    void poll_sensors () {sensors.sense();}
};

#endif

