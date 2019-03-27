/*  
 * lights.h
 *
 * purpose: maintains the proper outputs of the lights and
 *          adds fancy functionality with non-cumbersome 
 *          functions.
 *
 * date: 4/28/18
 * by: Ashton Stephens
 */


#ifndef LIGHTS_H_
#define LIGHTS_H_

#define LED_OFF      0
#define LED_ON_SOLID 1
#define LED_ON_FLASH 2

//#define FLASH_MASK 1 << 9
#define FLASH_MASK 1 << 6

struct light 
{
    int  pin;
    char state;

    // constructor
    light (int pin): pin(pin), state(LED_OFF) {}

    void on_solid () {state = LED_ON_SOLID;}
    void on_flash () {state = LED_ON_FLASH;}
    void off      () {state = LED_OFF;}
    void reset    () {state = LED_OFF;}
   
    void maintain () 
    {
        switch (state) {
            case LED_ON_SOLID :
              digitalWrite(pin,HIGH);
              break;
            case LED_ON_FLASH :
              digitalWrite(pin,!!(millis()&FLASH_MASK));
              break;
            case LED_OFF :
              digitalWrite(pin,LOW);
              break; 
        }
    }    

};

class lights
{
public:

    light yellow_path; 
    light blue_path; 
    light red_path;
    
    light green_state; 
    light blue_state; 
    light red_state;

    light headlights;
    light breaklights;
    
    light lturn;
    light rturn;

    lights ( int yellow_path_pin, int blue_path_pin,  int red_path_pin,
             int green_state_pin, int blue_state_pin, int red_state_pin,
             int headlights_pin,  int breaklights_pin,
             int lturn_pin,       int rturn_pin):
             yellow_path(yellow_path_pin), blue_path(blue_path_pin),  red_path(red_path_pin),
             green_state(green_state_pin), blue_state(blue_state_pin), red_state(red_state_pin),
             headlights(headlights_pin),  breaklights(breaklights_pin),
             lturn(lturn_pin),            rturn(rturn_pin) {}
        
    void maintain ()  
    {
        yellow_path.maintain(); 
        blue_path.maintain();  
        red_path.maintain(); 
        
        green_state.maintain();  
        blue_state.maintain();  
        red_state.maintain(); 
        
        headlights.maintain(); 
        breaklights.maintain();

        lturn.maintain();
        rturn.maintain(); 
    }

    bool flashing_on() {return !!(millis()&FLASH_MASK);}
    
    void reset ()  
    {
        yellow_path.reset(); 
        blue_path.reset();  
        red_path.reset(); 
        
        green_state.reset();  
        blue_state.reset();  
        red_state.reset(); 
        
        headlights.reset(); 
        breaklights.reset();

        lturn.reset();
        rturn.reset(); 
    }

};

#undef LED_OFF
#undef LED_ON_SOLID
#undef LED_ON_FLASH

#endif
