//
// csensor.h
//
// Purpose: To define the color sensor system of the autonomous bot
//
// Date: 3-3-18 
// By:  Ashton Stephens and Joseph Ming
//

#include "state.h"

#ifndef CSENSOR_H
#define CSENSOR_H

class csensor 
{
  private:
  
    int sensor_pin;    
    int red_pin;
    int blue_pin;

    
    color led_color; // current LED color
    int readings_left;
    int readings_per_decision;
    int readings[2];
    color path_color;
    
    int stabilization_time; // RENAME WHEN SMARTER
    int last_read_time;     // RENAME WHEN SMARTER

   public:
    
    csensor(int sensor_pin, int red_pin, int blue_pin,
            int readings_per_color, int stabilization_time) :
            sensor_pin(sensor_pin), red_pin(red_pin), blue_pin(blue_pin),
            led_color(RED), readings_per_decision(readings_per_color*2),
            path_color(NONE), stabilization_time(stabilization_time),
            last_read_time(0) {reset_readings();}
            
    ~csensor();
    
    // 
    void sense ()
    {
      if (stabilization_time < millis() - last_read_time) {
        get_reading();
        swap_led_color();
        if (readings_left == 0) {
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
    
    void swap_led_color ()
    {
      if (led_color == BLUE) {
         led_color = RED;
         digitalWrite(blue_pin, LOW); //turn blue led off
         digitalWrite(red_pin, HIGH); //turn red led on
      } else if (led_color == RED) {
         led_color = BLUE;
         digitalWrite(blue_pin, HIGH); //turn blue led on
         digitalWrite(red_pin,  LOW);  //turn red led off
      }
    }
    
    void reset_readings ()
    {
      readings[(int)RED ] = 0;
      readings[(int)BLUE] = 0;
      readings_left = readings_per_decision;
    }
    
    void get_reading ()
    {
      readings_left --;
      readings[(int)led_color] += analogRead(sensor_pin);
    }
    
    color csensor_decide_color     (csensor_T cs)
    {
      float red_reads  = ((((float)readings[(int)RED])) *2)/readings_per_decision;
      float blue_reads = ((((float)readings[(int)BLUE]))*2)/readings_per_decision;

      // ----------------------------- TEMPORARY DEBUG CODE ----------------------
      Serial.print("[B: ");
      Serial.print(blue_reads);
      Serial.print(" R: ");
      Serial.print(red_reads);
      Serial.println("]");
      return NONE;
    }
};

#endif
