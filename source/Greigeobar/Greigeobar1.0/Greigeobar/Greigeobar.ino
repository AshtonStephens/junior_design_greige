#include "smart_bot.h"
#include "states.h"
#include "smart_motor.h"

// cool lights ----- //
#define L_TURNSIGNAL 0
#define R_TURNSIGNAL 1
#define BREAKLIGHTS  49
#define L_HEADLIGHT  25
#define R_HEADLIGHT  23

// state lights -------- //
#define LED_STATE_0      14
#define LED_STATE_1      15
#define LED_STATE_2      16
#define LED_RED_TRACK    17
#define LED_YELLOW_TRACK 18
#define LED_BLUE_TRACK   19

// state switches ------ //
#define STATE_SWITCH_1   47
#define STATE_SWITCH_2   45
#define STATE_SWITCH_3   43
#define STATE_SWITCH_4   41

// sensor network ------- //
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

#define STABILIZATION_TIME 50

const float redBsl[NPARAMS+1] ={-1.903868, 3.080066, 1.502316, -0.705124, 0.515389};
const float bluBsl[NPARAMS+1] ={-2.091942, -0.156429, -0.035497, 3.392170, 0.478369};
const float redBsr[NPARAMS+1] = {-1.840674, 3.160087, 1.472051, -0.787523, 0.539282};
const float bluBsr[NPARAMS+1] = {-2.182819, -0.093342, 0.034828, 3.400515, 0.624078};

smart_bot Bot ( PIN1_M1, PIN2_M1,
                PIN1_M2, PIN2_M2,
                L_LIGHT_SENSOR, R_LIGHT_SENSOR,
                RED_LED, BLUE_LED, STABILIZATION_TIME,
                redBsl, bluBsl, redBsr, bluBsr);

/* DO NOT MOVE THIS INCLUDE VVVV */
#include "program.h"
/* DO NOT MOVE THIS INCLUDE ^^^^ */

void setup ()
{
    
/* ----------------------------------------------- *
 *  PINMODE SETUPS
 * ----------------------------------------------- */

    Serial.begin(9600);
    while (!Serial)  {}
    Serial.print("printing ready\n");
    
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

// sensor network ----------- //
    pinMode( L_LIGHT_SENSOR , INPUT);  // ?
    pinMode( R_LIGHT_SENSOR , INPUT);  // ?
    pinMode( HALL_EFFECT    , INPUT);  //
    pinMode( RED_LED        , OUTPUT); //
    pinMode( BLUE_LED       , OUTPUT); //
    
// communicaton ------------- // 
    pinMode( RECEIVING , INPUT  ); // ?
    pinMode( SENDING   , OUTPUT ); // ?

// motors ------------------- // 
    pinMode( PIN1_M1 , OUTPUT); // ?
    pinMode( PIN2_M1 , OUTPUT); // ?
    pinMode( PIN1_M2 , OUTPUT); // ?
    pinMode( PIN2_M2 , OUTPUT); // ?
}

/* --------------------------------------------------------------- */

void loop ()
{
    Bot.run_(STATE_PROGRAM,0);   
    for (;;) {};
}

/* --------------------------------------------------------------- */


