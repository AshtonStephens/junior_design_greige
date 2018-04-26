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
#define LED_STATE_BLUE   14 
#define LED_STATE_GREEN  15
#define LED_STATE_RED    16
#define LED_RED_TRACK    17
#define LED_YELLOW_TRACK 18
#define LED_BLUE_TRACK   19

// state switches ------ //
#define STATE_SWITCH_1   47
#define STATE_SWITCH_2   45
#define STATE_SWITCH_3   43
#define STATE_SWITCH_4   41

// sensor network ------- //
#define L_LIGHT_SENSOR A6 // ?
#define R_LIGHT_SENSOR A7 // ?
#define HALL           3  //
#define COLLISION      2  //
#define RED_LED        39 //
#define BLUE_LED       37 //

// communicaton -----// 
#define RECEIVING A5 //
#define SENDING   51 //

// motors ---------// 
#define PIN1_M1 6  //
#define PIN2_M1 7  //
#define PIN1_M2 5  //
#define PIN2_M2 4  //
#define PINE_M  21 // 

#define HALL_DEBOUNCE       250 // DEBOUNCE TIME 
#define COLLISION_DEBOUNCE  250 // FOR INTERRUPT SENSORS

#define STABILIZATION_TIME 50

const float redBsl[NPARAMS+1] = {-5.713125, 15.103408, 6.903004, -5.565095, -1.073656};
const float bluBsl[NPARAMS+1] = {-6.896294, -1.757802, -0.295036, 11.303079, 3.536464};
const float redBsr[NPARAMS+1] =  {-5.627664, 15.468755, 6.993172, -5.601236, -1.420434};
const float bluBsr[NPARAMS+1] = {-6.935288, -1.787222, -0.303681, 11.240418, 3.810915};

smart_bot Bot ( LED_YELLOW_TRACK, LED_BLUE_TRACK, LED_RED_TRACK,
                LED_STATE_GREEN, LED_STATE_BLUE, LED_STATE_RED,
                SENDING, RECEIVING,
                PIN1_M1, PIN2_M1,
                PIN1_M2, PIN2_M2, PINE_M,
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
    pinMode( LED_STATE_GREEN  , OUTPUT);
    pinMode( LED_STATE_RED    , OUTPUT);
    pinMode( LED_STATE_BLUE   , OUTPUT);
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
    pinMode( HALL           , INPUT);  //
    pinMode( COLLISION      , INPUT_PULLUP); //
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

    attachInterrupt(digitalPinToInterrupt(HALL),      hall_detect,      FALLING);
    attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect, FALLING);
    interrupts();
}

/* --------------------------------------------------------------- */

void loop ()
{


    digitalWrite (L_TURNSIGNAL,LOW);
    digitalWrite (BREAKLIGHTS,HIGH);
   
    digitalWrite (PINE_M,HIGH);
    
    // ----------------------------------
    int routine = 
        ((digitalRead(STATE_SWITCH_1)^1) << 3) 
      + ((digitalRead(STATE_SWITCH_2)^1) << 2) 
      + ((digitalRead(STATE_SWITCH_3)^1) << 1)
      + ((digitalRead(STATE_SWITCH_4)^1) << 0);
      
    Serial.print  ("ROUTINE [");
    Serial.print  (routine);
    Serial.println("]");
    //----------------------------------

    long long timer = millis ();
    while (1000 > millis() - timer) { Bot.sensors.sense();} 
    
    Bot.run_(STATE_PROGRAM,routine);  

}

/* --------------------------------------------------------------- */

void hall_detect () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = HALL_DEBOUNCE;

  attachInterrupt(digitalPinToInterrupt(HALL), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // -------------------------------------------------------
      Bot.hall_interrupt = 1;
      // -------------------------------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(HALL), hall_detect, FALLING); 
}


void collision_detect () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = COLLISION_DEBOUNCE;

  attachInterrupt(digitalPinToInterrupt(COLLISION), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // -------------------------------------------------------
      Bot.collision_interrupt = 1;
      // -------------------------------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect, FALLING); 
}

void nothing () {}

