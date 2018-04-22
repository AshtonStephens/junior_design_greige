#include "fake_arduino.h"
#include "smart_motor.h"

#define DEBUG
#include "debug_macros.h"

#define A5 60
#define A6 61
#define A7 62

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

    init_fake_ports(); // FOR DEBUGGING 
/* ----------------------------------------------- *
 *  PINMODE SETUPS
 * ----------------------------------------------- */

// cool lights ---------
    pinMode( L_TURNSIGNAL, OUTPUT);
    pinMode( R_TURNSIGNAL, OUTPUT);
    pinMode( BREAKLIGHTS , OUTPUT);
    pinMode( L_HEADLIGHT , OUTPUT);
    pinMode( R_HEADLIGHT , OUTPUT);

// state lights -----------
    pinMode( LED_STATE_0      , OUTPUT);
    pinMode( LED_STATE_1      , OUTPUT);
    pinMode( LED_STATE_2      , OUTPUT);
    pinMode( LED_RED_TRACK    , OUTPUT);
    pinMode( LED_YELLOW_TRACK , OUTPUT);
    pinMode( LED_BLUE_TRACK   , OUTPUT);

// state switches ---------
    pinMode( STATE_SWITCH_1 , INPUT_PULLUP);
    pinMode( STATE_SWITCH_2 , INPUT_PULLUP);
    pinMode( STATE_SWITCH_3 , INPUT_PULLUP);
    pinMode( STATE_SWITCH_4 , INPUT_PULLUP);

// sensor network ------------//
    pinMode( L_LIGHT_SENSOR , INPUT);  // ?
    pinMode( R_LIGHT_SENSOR , INPUT);  // ?
    pinMode( HALL_EFFECT    , INPUT);  //
    pinMode( RED_LED        , OUTPUT); //
    pinMode( BLUE_LED       , OUTPUT); //

// communicaton -----// 
    pinMode( RECEIVING , INPUT  ); // !!! ? <------------
    pinMode( SENDING   , OUTPUT ); // !!! ? <------------

// motors ---------// 
    pinMode( PIN1_M1 , OUTPUT); // ?
    pinMode( PIN2_M1 , OUTPUT); // ?
    pinMode( PIN1_M2 , OUTPUT); // ?
    pinMode( PIN2_M2 , OUTPUT); // ?

}

smart_motor lmotor () ;

void loop ()
{
    millis();
    Serial.println(" ---- STARTING TESTS ---- ");
    printPins(); 

    printPins(); 

    Serial.println(" ---- ENDING TESTS ---- ");
    for (;;) {DBG_ASSERT(false);};
}

/* --------------------------------------------------------------- */

int main () 
{
    setup();
    for(;;) loop();
    return 0;
}
