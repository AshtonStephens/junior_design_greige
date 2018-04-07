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
  
    int id_number;
    int sensor_pin;    
    int red_pin;
    int blue_pin;
    int red_light_brightness;
    int blue_light_brightness;

    int   led_color_state; // current LED color
    float readings[NPARAMS];
    color path_color;
    
    int stabilization_time;
    long long time_of_last_read;     
    
    // Beta values for logistic classification
    const Betas &redB;
    const Betas &bluB;

    public:
    
    csensor(int id_number, int sensor_pin, int red_pin, int red_light_brightness, int blue_pin,
            int blue_light_brightness, int stabilization_time, 
            const Betas &redB, const Betas &bluB) : id_number(id_number),
            sensor_pin(sensor_pin), red_pin(red_pin), blue_pin(blue_pin),
            red_light_brightness (red_light_brightness),
            blue_light_brightness(blue_light_brightness), led_color_state(0), 
            path_color(NONE), stabilization_time(stabilization_time),
            time_of_last_read(0), redB(redB), bluB(bluB) {reset_readings();}

    ~csensor(){};
    
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
                analogWrite(blue_pin, blue_light_brightness); 
                analogWrite(red_pin,  0); 
                break;
            case 2:
                // BOTH on
                analogWrite(blue_pin, blue_light_brightness); 
                analogWrite(red_pin,  red_light_brightness); 
                break;
            case 3:
                // red on
                analogWrite(blue_pin, 0); 
                analogWrite(red_pin,  red_light_brightness); 
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
        readings[led_color_state] = analogRead(sensor_pin) / 1023.0;
    }
   
    color decide_color  ()
    {
        // ----------------------------- TEMPORARY DEBUG CODE -----------------
        color new_color;

        new_color = predict_full(readings,redB,bluB); 

        #ifdef DEBUG_CSENSOR 
        Serial.print("ID: ");
        Serial.print(id_number);
        Serial.print(" - [");
        switch (new_color) {
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
        Serial.println("]");
        #endif
        
        return new_color;
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
