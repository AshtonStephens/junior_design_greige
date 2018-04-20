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
#include "classification.h"

// MAKE MORE PROMINENT
typedef float Betas[NPARAMS+1];
#define DEBUG_CSENSOR

class csensor 
{
  private:

    int sensor_pin_left;
    int sensor_pin_right;
      
    int red_pin;
    int blue_pin;

    int   led_color_state; // current LED color
    float readings_left [NPARAMS];
    float readings_right[NPARAMS];

    color color_left;
    color color_right;
    
    int stabilization_time;
    long long time_of_last_read;     
    
    // Beta values for logistic classification
    const Betas &redB_left;
    const Betas &bluB_left;
    const Betas &redB_right;
    const Betas &bluB_right;

    public:
    
    csensor(int sensor_pin_left, int sensor_pin_right,int red_pin, int blue_pin, 
            int stabilization_time, 
            const Betas &redB_left , const Betas &bluB_left,
            const Betas &redB_right, const Betas &bluB_right) : 
            sensor_pin_right(sensor_pin_right), sensor_pin_left(sensor_pin_left), 
            red_pin(red_pin), blue_pin(blue_pin), led_color_state(0), 
            color_left(NONE),color_right(NONE), 
            stabilization_time(stabilization_time), time_of_last_read(0), 
            redB_left (redB_left ), bluB_left (bluB_left ),
            redB_right(redB_right), bluB_right(bluB_right)
            {reset_readings();}

    ~csensor(){};

    void sense ()
    {
        if (stabilization_time < millis() - time_of_last_read) {
            time_of_last_read = millis();
            get_readings();
            switch_led_color();
            if (led_color_state == 0) {
                decide_colors ();
                reset_readings();
            }
        }
    }

    // returns last decided path color
    color right() {
        return color_right;  
    }
    
    color left() {
        return color_left;  
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
                analogWrite(blue_pin, 255); 
                analogWrite(red_pin,  0); 
                break;
            case 2:
                // BOTH on
                analogWrite(blue_pin, 255); 
                analogWrite(red_pin,  255); 
                break;
            case 3:
                // red on
                analogWrite(blue_pin, 0); 
                analogWrite(red_pin,  255); 
                led_color_state = 0;
                break;
            default:
                break;
        }
    }
    
    void reset_readings ()
    {
        for (int i = 0; i < 4; ++i) {
            readings_left [i] = 0;
            readings_right[i] = 0;
        }
    }
    
    void get_readings ()
    {
        readings_right[led_color_state] = analogRead(sensor_pin_right) / 1023.0;
        readings_left [led_color_state] = analogRead(sensor_pin_left ) / 1023.0;
    }
   
    void decide_colors  ()
    {
        // ----------------------------- TEMPORARY DEBUG CODE -----------------
        color new_color;

        color_left  = predict_full(readings_left ,redB_left ,bluB_left ); 
        color_right = predict_full(readings_right,redB_right,bluB_right); 

        #ifdef DEBUG_CSENSOR 
        Serial.print("[");
        print_color(color_left);
        Serial.print("][");
        print_color(color_right);
        Serial.println("]");
        #endif
    }
    
    void print_color  (color c)
    {
        switch (c) {
          case BLUE :
            Serial.print("BLUE");
            break;
          case RED :
            Serial.print("RED");
            break;
          case YELLOW :
            Serial.print("YELLOW");
            break;
          case BLACK :
            Serial.print("BLACK");
            break;  
          default :
            Serial.print("IMPOSSIBLE");
            break;
        }
    }

    void print_readings(float readings[NPARAMS]) 
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
