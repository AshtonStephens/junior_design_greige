#include "smart_bot.h"
#include "states.h"
#include "smart_motor.h"

#define POT_A  A14
#define POT_B  A15

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

#define STABILIZATION_TIME 20
/*    ZINNOBAR
const float redBsl[NPARAMS+1] = {-6.101946, -14.323162, 23.169413};
const float bluBsl[NPARAMS+1] = {-14.618992, 19.059864, -1.598202};
const float redBsr[NPARAMS+1] = {-3.953188, -16.098141, 23.316850};
const float bluBsr[NPARAMS+1] = {-12.612396, 13.973304, 2.472246};
*/ 

const float redBsr[NPARAMS+1] = {-6.388153, -12.839205, 22.176529};
const float bluBsr[NPARAMS+1] = {-13.134911, 19.116380, -2.625003};
const float redBsl[NPARAMS+1] = {-5.140660, -14.058928, 22.504624};
const float bluBsl[NPARAMS+1] = {-12.176397, 16.411099, -0.047437};

smart_bot Bot ( LED_YELLOW_TRACK, LED_BLUE_TRACK, LED_RED_TRACK,
                LED_STATE_GREEN, LED_STATE_BLUE, LED_STATE_RED,
                PIN1_M1, PIN2_M1,
                PIN1_M2, PIN2_M2, PINE_M,
                SENDING, RECEIVING,
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

    pinMode (POT_A, INPUT);
    pinMode (POT_B, INPUT);
  
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

    // ENSURE MOTORS OFF
    analogWrite(PIN1_M1,0);
    analogWrite(PIN2_M1,0);
    analogWrite(PIN1_M2,0);
    analogWrite(PIN2_M2,0);

    attachInterrupt(digitalPinToInterrupt(HALL),      hall_detect,      FALLING);
    attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect, FALLING);
    interrupts();
}

/* --------------------------------------------------------------- */

void loop ()
{
    //Serial.println(__FILE__);
    //Bot.lmotor.debug(); 
    //Bot.rmotor.debug();

    digitalWrite (L_TURNSIGNAL,LOW);
    digitalWrite (BREAKLIGHTS,HIGH);
   
    //digitalWrite (PINE_M,HIGH);
    
    // ----------------------------------
    long long timer = millis ();
    while (2000 > millis() - timer) { Bot.sensors.sense();} 
    
    int routine = 
        ((digitalRead(STATE_SWITCH_1)^1) << 3) 
      + ((digitalRead(STATE_SWITCH_2)^1) << 2) 
      + ((digitalRead(STATE_SWITCH_3)^1) << 1)
      + ((digitalRead(STATE_SWITCH_4)^1) << 0);
    
    Serial.print  ("ROUTINE [");
    Serial.print  (routine);
    Serial.println("]");
    //----------------------------------
    /*
    Serial.print  ("Lmotor: ");
    Serial.println(analogRead(POT_A)>>2);
    c1b1_starting_run2.Lmotor_speed = analogRead(POT_A)>>2;
    Serial.print  ("Rmotor: ");
    Serial.println(analogRead(POT_B)>>2);
    c1b1_starting_run2.Rmotor_speed = analogRead(POT_B)>>2;
    */

    
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
  DBG;
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

