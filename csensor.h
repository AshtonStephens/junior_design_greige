//
// csensor.h
//
// Purpose: To define the color sensor system of the autonomous bot
// By: Ashton Stephens
// Date: 3/3/18 
//

#ifndef CSENSOR_H
#define CSENSOR_H

#include "color.h"
#include "classification.h"

// MAKE MORE PROMINENT
typedef float Betas[NPARAMS+1];

//#define DEBUG_CSENSOR_COLORS
//#define DEBUG_CSENSOR_RAW

/* csensor - color sensor class for both front sensors.
 * 
 * .sense() - ensures the internal sensor values are up to date
 *            and gives permission to the sensor unit to perform
 *            any action it need to do achieve that
 * 
 * .left()  - provides most up to date color from the left sensor
 * .right() - provides most up to date color from the right sensor  
 * 
 * .off()   - shuts the power off
 * 
 */
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
    
    /* sets up the sensors with the relavent pins. 
     * 
     * The "Betas" are the beta coefficients we use to determine 
     * if the given color sensor has detected the given color. Since
     * there are two sensors, and we detect the presence of two colors
     * per sensor, we have 4 Beta arrays. 
     */
    csensor(int sensor_pin_left, int sensor_pin_right,int red_pin, int blue_pin,
            int stabilization_time, 
            const Betas &redB_left , const Betas &bluB_left,
            const Betas &redB_right, const Betas &bluB_right) : 
            sensor_pin_left(sensor_pin_left), sensor_pin_right(sensor_pin_right),
            red_pin(red_pin), blue_pin(blue_pin), led_color_state(0), 
            color_left(NONE),color_right(NONE), 
            stabilization_time(stabilization_time), time_of_last_read(0), 
            redB_left (redB_left ), bluB_left (bluB_left ),
            redB_right(redB_right), bluB_right(bluB_right)
            {reset_readings();}

    ~csensor(){};

    // sense - updates the internal left and right color values (if it can)
    // 
    // after calling sense, the sensor guarantees that the readings inside 
    // the sensor struct as up to date as possible.
    void sense ()
    {
        // Because the analog light sensor has some capacitance, the 
        // red or blue light needs to stay on for enough time for the
        // reading to stabilize. This if statement prevents any decisions
        // being made about the color until the light has been on long
        // enough for the sensor value to be stable.
        if (stabilization_time < millis() - time_of_last_read) {
            time_of_last_read = millis();

            get_readings(); // update internal readings from given on color
            switch_led_color(); 

            // if we've finished cycling through colors, decide what
            // color we're on (uses logistic algorithm)
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

    void off ()
    {
        digitalWrite(blue_pin, LOW); 
        digitalWrite(red_pin , LOW); 
    }
    
    private:
    
    void switch_led_color ()
    {
        switch (led_color_state++) {
            case 0:
                // BOTH off
                digitalWrite(blue_pin, LOW); 
                digitalWrite(red_pin , HIGH); 
                break;
            case 1:
                // blue on
                digitalWrite(blue_pin, HIGH); 
                digitalWrite(red_pin,  LOW);
                led_color_state = 0;
                break;
            case 2:
                // BOTH on
                digitalWrite(blue_pin, HIGH); 
                digitalWrite(red_pin,  HIGH); 
                break;
            case 3:
                // red on
                digitalWrite(blue_pin, LOW); 
                digitalWrite(red_pin,  HIGH); 
                led_color_state = 0;
                break;
            default:
                break;
        }
    }
    
    void reset_readings ()
    {
        for (int i = 0; i < NPARAMS; ++i) {
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
        color_left  = predict_full(readings_left , redB_left , bluB_left ); 
        color_right = predict_full(readings_right, redB_right, bluB_right); 

    // ----------------------------- TEMPORARY DEBUG CODE -----------------

        #ifdef  DEBUG_CSENSOR_COLORS
          Serial.print("[");
          print_color(color_left);
          Serial.print("][");
          print_color(color_right);
          Serial.println("]");
        #endif
        
        #ifdef DEBUG_CSENSOR_RAW
          print_readings(readings_left,readings_right);
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
            // for when you're sure about your code,
            // but apparently not too sure..?
            Serial.print("IMPOSSIBLE");
            break;
        }
    }

    /* print_readings - literally just for debugging
     *
     * outputs the literal readings within the sensor. Each "sensor" on this bot
     * actually has two analog sensors which will have a reading when the blue
     * light is being flashed, and when the red light is being flashed. As such, 
     * we print out here a blue and red reading for the left sensor, and a blue and
     * red reading for the right sensor. 
     */
    void print_readings(float readingsl[NPARAMS],float readingsr[NPARAMS]) 
    {
        Serial.print("{csensor}:");
        Serial.print("[ lB: ");
        Serial.print(readingsl[0]);
        Serial.print(" | lR: ");
        Serial.print(readingsl[1]);
        Serial.print(" | rB: ");
        Serial.print(readingsr[0]);
        Serial.print(" | rR: ");
        Serial.print(readingsr[1]);
        Serial.println(" ]");
    }

};

#endif
