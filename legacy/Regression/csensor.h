//
// csensor.h
//
// Purpose: To define the color sensor system of the autonomous bot
//
// Date: 3-3-18 
// By:  Ashton Stephens and Joseph Bing
//


#ifndef CSENSOR_H
#define CSENSOR_H

#include "color.h"
#include "regression.h"

#define PRINTME true

class csensor 
{
  private:
  
    int sensor_pin;    
    int red_pin;
    int blue_pin;
    int red_light_brighness;
    int blue_light_brighness;

    int led_color_state; // current LED color
   // int readings_left;
   // int readings_per_decision;
    int readings[N_REG_PARAMS];
    color path_color;
    
    int stabilization_time;
    long long time_of_last_read;     
    
   public:
    
    csensor(int sensor_pin, int red_pin, int red_light_brighness, int blue_pin, 
            int blue_light_brighness, int stabilization_time) :
            sensor_pin(sensor_pin), red_pin(red_pin), blue_pin(blue_pin),
            red_light_brighness (red_light_brighness),
            blue_light_brighness(blue_light_brighness), led_color_state(0), 
            path_color(NONE), stabilization_time(stabilization_time),
            time_of_last_read(0) {reset_readings();}
            
    ~csensor();
    
    // 
    void sense ()
    {
        if (stabilization_time < millis() - time_of_last_read) {
            time_of_last_read = millis();
            get_reading();
            switch_led_color();
            if (led_color_state == 0) {
                path_color = decide_color();
                reset_readings();
            }
        }
    }

    // returns last decided path color
    color path() {
        return path_color;  
    }
    
    private:
    
    // DUMB HELPER FUNCTIONS
    
    void switch_led_color ()
    {
        switch (led_color_state++) {
            case 0:
                // BOTH off
                analogWrite(blue_pin, 0); 
                analogWrite(red_pin , 0); 
                break;
            case 1:
                // blue on
                analogWrite(blue_pin, blue_light_brighness); 
                analogWrite(red_pin,  0); 
                break;
            case 2:
                // BOTH on
                analogWrite(blue_pin, blue_light_brighness); 
                analogWrite(red_pin,  red_light_brighness); 
                break;
            case 3:
                // red on
                analogWrite(blue_pin, 0); 
                analogWrite(red_pin,  red_light_brighness); 
                led_color_state = 0;
                break;
            default:
                // SHOULD NEVER HAPPEN
                break;
        }
    }
    
    void reset_readings ()
    {
        for (int i = 0; i < 4; ++i) {
            readings[i] = 0;
        }
    }
    
    void get_reading ()
    {
        readings[led_color_state] = analogRead(sensor_pin);
    }
   
    color decide_color  ()
    {
        // ----------------------------- TEMPORARY DEBUG CODE -----------------
        if (PRINTME) print_readings (); 
        
        return NONE;
    }

    void print_readings() 
    {
        Serial.print("{csensor}:");
        Serial.print("[ __: ");
        Serial.print(readings[0]);
        Serial.print(" | B_: ");
        Serial.print(readings[1]);
        Serial.print(" | BR: ");
        Serial.print(readings[2]);
        Serial.print(" | _R: ");
        Serial.print(readings[3]);
        Serial.print(" ]");
        Serial.print("\n");
    }

};

#endif
