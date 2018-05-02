
#define ZINNOBAR

#include "smart_bot.h"
#include "states.h"
#include "smart_motor.h"

#define POT_A  A14
#define POT_B  A15

// cool lights ----- //
#define L_TURNSIGNAL 0
#define R_TURNSIGNAL 1
#define BREAKLIGHTS  49
#define HEADLIGHTS   25

// state lights -------- //
#define LED_STATE_BLUE   14 
#define LED_STATE_GREEN  15
#define LED_STATE_RED    16
#define LED_RED_TRACK    17
#define LED_BLUE_TRACK   19
#define LED_YELLOW_TRACK 18

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

// communicaton ----- // 
#define RECEIVING A14 //
#define SENDING   38  //


#define PIN1_M1 6  //
#define PIN2_M1 7  //
#define PIN1_M2 5  //
#define PIN2_M2 4  //
#define PINE_M  21 // 

// ---------------------------------------------- //
#define HALL_DEBOUNCE       250 // DEBOUNCE TIME 
#define COLLISION_DEBOUNCE  250 // FOR INTERRUPT SENSORS
#define STABILIZATION_TIME  20
#define STARTUP_TIME        1000

bool ROUTINE_STARTED = false;
void startup_script();

#ifdef ZINNOBAR
#define MOTORR_RATIO 0.9
#define MOTORL_RATIO 0.9
const float redBsl[NPARAMS+1] = {-5.328314, -13.148070, 23.613085};
const float bluBsl[NPARAMS+1] = {-10.223347, 18.549933, -0.996931};
const float redBsr[NPARAMS+1] = {-4.765302, -12.646533, 22.950511};
const float bluBsr[NPARAMS+1] = {-9.143999, 19.150152, -2.333729};
#endif
    
#ifdef GREIGE
#define MOTORR_RATIO 0.9
#define MOTORL_RATIO 0.9
 

const float redBsr[NPARAMS+1] =  {-4.778298, -15.261315, 27.312647};
const float bluBsr[NPARAMS+1] = {-10.186932, 22.284243, -4.507212};
const float redBsl[NPARAMS+1] = {-5.795165, -13.741407, 25.120166};
const float bluBsl[NPARAMS+1] = {-4.256994, 25.752916, -18.000910};
#endif





smart_bot Bot ( LED_YELLOW_TRACK, LED_BLUE_TRACK, LED_RED_TRACK,
                LED_STATE_GREEN, LED_STATE_BLUE , LED_STATE_RED,
                HEADLIGHTS     ,  BREAKLIGHTS, 
                L_TURNSIGNAL   ,  R_TURNSIGNAL,
                PIN1_M1, PIN2_M1, MOTORR_RATIO,
                PIN1_M2, PIN2_M2, MOTORL_RATIO, PINE_M,
                SENDING, RECEIVING,
                L_LIGHT_SENSOR, R_LIGHT_SENSOR,
                HALL, COLLISION,
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
    pinMode( HEADLIGHTS  , OUTPUT);

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
    pinMode( PIN1_M1 , OUTPUT); // ? ? ? ?
    pinMode( PIN2_M1 , OUTPUT); // ? ? ?
    pinMode( PIN1_M2 , OUTPUT); // ? ?
    pinMode( PIN2_M2 , OUTPUT); // ?

    // ENSURE MOTORS OFF
    analogWrite(PIN1_M1,0);
    analogWrite(PIN2_M1,0);
    analogWrite(PIN1_M2,0);
    analogWrite(PIN2_M2,0);

    attachInterrupt(digitalPinToInterrupt(HALL),      hall_detect,      FALLING);
    attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect_startup, FALLING);
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
    
    // ----------------------------------

    startup_script();
     
    long long timer = millis ();
    while (!ROUTINE_STARTED) { Bot.sensors.sense();} 

    // attach the normal interrupt
    attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect, FALLING);
    
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
      Bot.hall_interrupt = true;
   }
}

void collision_detect () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = COLLISION_DEBOUNCE;
  attachInterrupt(digitalPinToInterrupt(COLLISION), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      Bot.collision_interrupt = true;
   }
}

void collision_detect_startup () 
{
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = COLLISION_DEBOUNCE;
  attachInterrupt(digitalPinToInterrupt(COLLISION), nothing, FALLING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      ROUTINE_STARTED = true;
   }
}
  
void startup_script()
{
    Serial.println("running...");
    long long timer = millis();
    Bot.leds.red_state.on_flash();
    Bot.leds.green_state.on_flash();
    Bot.leds.blue_state.on_flash();
    Bot.leds.red_path.on_flash();
    Bot.leds.blue_path.on_flash();
    Bot.leds.yellow_path.on_flash();
    Bot.leds.headlights.on_flash();
    Bot.leds.breaklights.on_flash();
    Bot.leds.lturn.on_flash();
    Bot.leds.rturn.on_flash();    

    while (STARTUP_TIME > millis() - timer) Bot.leds.maintain();

    Bot.leds.reset();
    Bot.leds.maintain();
}

void nothing () {}

