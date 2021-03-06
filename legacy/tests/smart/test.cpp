
#include "fake_arduino.h"

// cool lights ---------
#define L_TURNSIGNAL 0
#define R_TURNSIGNAL 1
#define BREAKLIGHTS  49
#define L_HEADLIGHT  25
#define R_HEADLIGHT  23

// state lights -----------
#define LED_STATE_0      14
#define LED_STATE_1      15
#define LED_STATE_2      16
#define LED_RED_TRACK    17
#define LED_YELLOW_TRACK 18
#define LED_BLUE_TRACK   19

// state switches ---------
#define STATE_SWITCH_1   47
#define STATE_SWITCH_2   45
#define STATE_SWITCH_3   43
#define STATE_SWITCH_4   41

// sensor network ------------//
#define L_LIGHT_SENSOR A5 // ?
#define R_LIGHT_SENSOR A6 // ?
#define HALL_EFFECT    3  //
#define RED_LED        29 //
#define BLUE_LED       28 //

// communicaton -----// 
#define RECEIVING A7 //
#define SENDING   27 //

// motors ---------// 
#define PIN1_M1 7  // ?
#define PIN2_M1 6  // ?
#define PIN1_M2 5  // ?
#define PIN2_M2 4  // ?

void setup ()
{

}


void loop ()
{
    fprintf(stderr,"hi\n");
    Serial.println(millis());
    Serial.println(" ---- STARTING TESTS ---- ");
    
    Serial.println(" ---- DONE WITH TESTS ---- ");
    for(;;) {};
}









/* --------------------------------------------------------------- */

int main () 
{
    setup();
    for(;;) loop();
    return 0;
}
