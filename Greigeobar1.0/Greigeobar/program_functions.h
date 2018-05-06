
#ifndef PROGRAM_FUNCTIONS_H_
#define PROGRAM_FUNCTIONS_H_

#define RIGHT_TRACK true
#define LEFT_TRACK  false

#define RED_STATE_LED_FLASH    1 << 0
#define GREEN_STATE_LED_FLASH  1 << 1
#define BLUE_STATE_LED_FLASH   1 << 2

#define BLUE_PATH_LED_FLASH    1 << 3
#define RED_PATH_LED_FLASH     1 << 4
#define YELLOW_PATH_LED_FLASH  1 << 5

#define HEADLIGHT_LED_FLASH    1 << 6
#define BREAKLIGHT_LED_FLASH   1 << 7
#define LTURN_LED_FLASH        1 << 8
#define RTURN_LED_FLASH        1 << 9

#define TURNSIGNAL_THRESHOLD 50

#define DEFAULT_END 69

#define IS_GO 1
#define IS_ADJUST_RIGHT 2
#define IS_ADJUST_LEFT  3
#define XX 69

#define DEBUG_COMMS
    

bool yellowblack () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == YELLOW) && ((Bot.sensors.right() == BLACK) ||(Bot.sensors.right() == RED));
}
bool yellowblue () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == YELLOW) && (Bot.sensors.right() == BLUE);
}
bool blueblack () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == BLUE) && (Bot.sensors.right() == BLACK);
}
bool blueblue () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == BLUE) && (Bot.sensors.right() == BLUE);
}
bool blueoblue () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == BLUE) || (Bot.sensors.right() == BLUE);
}
bool yellowyellow () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == YELLOW) && (Bot.sensors.right() == YELLOW);
}
bool blackblack () 
{ //Serial.print("adjusting");
  return (Bot.sensors.left() == BLACK) && (Bot.sensors.right() == BLACK);
}

bool redred ()
{
  return (Bot.sensors.left() == RED) && (Bot.sensors.right() == RED);
}

bool hall (){return Bot.hall_interrupt;}
bool collision (){return Bot.collision_interrupt;}

// --------------------------------------------------------------- CHALLENGE 2/3
static const int light_threshold = 800;
#define HEADLIGHTS_SENSE_L A13
#define HEADLIGHTS_SENSE_R A14

bool headlights_sensed()
{
  return ((analogRead(HEADLIGHTS_SENSE_L) < light_threshold) || (analogRead(HEADLIGHTS_SENSE_R) < light_threshold)); 
}
// ---------------------------------------------------------------  CHALLENGE 2/3

struct talk_data 
{
    int duration;
    int NS;
    /* ---- TEMPS ---- */
    long long start_time;
};

struct listen_data 
{
    int  duration;
    int  rising_edge;
    int  falling_edge;
    int  time_deviation;
    int NS; 
    int reception_leds;
    /* ---- TEMPS ---- */
    bool high;
    long long start_time;
};

struct move_time_data
{
  int ramp_time;
  int run_time;
  int Lmotor_speed; 
  int Rmotor_speed;
  int NS; 
  /* ---- TEMPS ---- */
  long long start_time;
};

struct move_if_data
{
  int ramp_time;
  bool (*iff)();
  int Lmotor_speed; 
  int Rmotor_speed;
  int NS;
  /* ---- TEMPS ---- */
};

struct flashled_data
{
    int  leds;
    int  flashes;
    int  NS;
    /* ---- TEMPS ---- */
    bool last_on;
    bool started;
    int  count;
};

struct tracktrack_data
{
  color L;          // left color
  color R;          // right color
  bool (*iff)();    // condition to leave
  int  ft;          // fullthrottle
  int  mt;          // mediumthrottle
  int  lt;          // lowthrottle
  int  slope;       // duration of motor change
  int  NS ;         // next state
  color forgive;
  /* ---- TEMPS ---- */
  int  last_state;  // 
};

/* BOT 1 Challenge 1 ----------------------------- */
/*struct listen_data 
{
    int  duration;
    int  rising_edge;
    int  falling_edge;
    int  time_deviation;
    int NS;
    bool high;
    long long start_time;
};*/

//move_time_data       c2b1_fwd_12in        = {100, INCH_TRAVEL*12, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD,   0, 10};
//move_time_data  c1b1_initial_collision2 = {100,550, -70, -105, 10};                             // state 8 -> 10

/* --------------------------------------------------- *
 |  bot 1 challenge 1                                  |
 * --------------------------------------------------- */
flashled_data   c1b1_initflash          = {RED_STATE_LED_FLASH|BLUE_STATE_LED_FLASH, 3, 4};    // state 1 -> 4
talk_data       c1b1_start_talk         = {600, 5};                                            // state 4 -> 5
flashled_data   c1b1_startflash         = {GREEN_STATE_LED_FLASH, 3, 6};                       // state 5 -> 6
move_if_data    c1b1_initial_collision1 = {100, collision,   100, 100, 8};                     // state 6 -> 8
move_time_data  c1b1_initial_collision2 = {100,550, -70, -105, 10};                             // state 8 -> 10
move_time_data  c1b1_init_col_wait      = {100, 200,    0,    0, 12}; //*** brief pause           state 10 -> 12
move_if_data    c1b1_initial_collision3 = {1000, blueblue, 80, 70, 13};                        // state 12 -> 13
tracktrack_data c1b1_track_blue         = {BLUE, BLUE,  yellowyellow,  70,  0, -40, 750, 14};  // state 13 -> 14
move_time_data  c1b1_forward_smidge1    = {100, 200,   70,   70, 15};;                         // state 14 -> 15
move_time_data  c1b1_right_90           = {100, 350,  70,  -70, 20};                           // state 15 -> 20
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, blackblack,  70, 0, -40, 750, 25};  // state 20 -> 25
move_time_data  c1b1_left_90            = {100, 350,  -150,  50, 27};                          // state 25 -> 27
move_time_data  c1b1_forward_jolt       = {100, 200,  100,  100, 30};                          // state 27 -> 30 
tracktrack_data c1b1_track_red          = {RED, RED, hall,  70, 0, -40, 750, 35};              // state 30 -> 35
/*                                                     *
 |  bot 1 after detecting hall sensor                  |
 * --------------------------------------------------- */
move_time_data  c1b1_stop_hall_jolt1    = {100, 1000, 0, 0,  36};                              // state 35 -> 36
move_time_data  c1b1_turn_tcc_jolt      = {100, 700, 0, -130, 38};                             // state 36 -> 38 // angle to TCC

// TODO: ensure that this is the right timing 
flashled_data   c1b1_tcc200ms_flash     = {GREEN_STATE_LED_FLASH, 3, 40};                      // state 38 -> 40 
talk_data       c1b1_start_talk_tcc     = {210, 43};                                           // state 40 -> 43 (200 ms?) // message 1

// TODO: ensure that this is the right timing make sure this is the right threshold
listen_data     c1b1_start_tisten_tcc   = {215, 300, 100, 40, 45, BLUE_STATE_LED_FLASH};       // state 43 -> 45 (200 ms?) // message 1

move_time_data  c1b1_turn_tcc_jolt2     = {100, 700, 0, 130, 48};                              // state 45 -> 48 // angle back to road
tracktrack_data c1b1_track_red_to_wall  = {RED, RED, collision,  70, 0, -40, 750, 50};         // state 48 -> 50
flashled_data   c1b1_redwall_flash      = {RED_STATE_LED_FLASH, 3, 53};                        // state 50 -> 53
move_time_data  c1b1_back_from_redwall  = {100, 1000, 0, 0, 55};                               // state 53 -> 55

move_time_data  c1b1_turn_90_to_bot     = {100, 350,  -150,  50, 57};                          // state 55 -> 57
move_time_data  c1b1_turn_135_to_tcc    = {100, 450,  -150,  50, 70};                          // state 57 -> 70**
move_time_data  c1b1_pause_tcc          = {100, 200,    0,    0, 58}; //*** brief pause           state 70 ->58
talk_data       c1b1_start_talk_tcc2    = {330, 71};                                           // state 58 -> 71 (300 ms)  // message 2
move_time_data  c1b1_pause_after_tcc    = {100, 200,    0,    0, 59}; //*** brief pause           state 71 -> 59

move_time_data  c1b1_turn_135_to_bot    = {100, 450,  50,  -150, 60};                          // state 59 -> 60

/*                                                     *
 |  bot 2 starts its test                              |
 * --------------------------------------------------- */

listen_data     c1b1_listen_bot2_start  = {615, 250, 90, 40, 62, BLUE_STATE_LED_FLASH};       // state 60 -> 62 (RCV 500 ms) // bot 2 START message
flashled_data   c1b1_receive_startflash = {GREEN_STATE_LED_FLASH, 3, 64};                      // state 62-> 64 

listen_data     c1b1_listen_bot2_finish = {615, 210, 70, 40, 66, BLUE_STATE_LED_FLASH};       // state 64 -> 66 (RCV 500 ms) // bot 2 FINISH message
move_if_data    c1b1_final_collision    = {100, collision,   80, 80, 68};                    // state 66 -> 68
flashled_data   c1b1_final_flash        = {HEADLIGHT_LED_FLASH | BREAKLIGHT_LED_FLASH |
                                           LTURN_LED_FLASH     | RTURN_LED_FLASH, 10, 69};     // state 68 -> 69

										   
/* --------------------------------------------------- *
 |  bot 2 challenge 1                                  |
 * --------------------------------------------------- */
listen_data		  c1b2_init_listen		    = {315, 250, 100, 50, 2, BLUE_STATE_LED_FLASH};        // state 1 -> 2
flashled_data   c1b2_initflash          = {RED_STATE_LED_FLASH|BLUE_STATE_LED_FLASH, 3, 5};    // state 2 -> 4
talk_data       c1b2_start_talk         = {600, 5};                                            // state 4 -> 5
flashled_data   c1b2_startflash         = {GREEN_STATE_LED_FLASH, 3, 6};                       // state 5 -> 6
move_if_data    c1b2_initial_collision1 = {100, collision,   100, 100, 8};                     // state 6 -> 8
move_time_data  c1b2_initial_collision2 = {100, 500, -100, -75, 10};                           // state 8 -> 10
move_time_data  c1b2_init_col_wait      = {100, 200,    0,    0, 12}; //*** brief pause           state 10 -> 12
move_if_data    c1b2_initial_collision3 = {1000, redred, 70, 80, 13};                          // state 12 -> 13
tracktrack_data c1b2_track_red          = {RED, RED,  yellowyellow,  70,  0, -40, 750, 14};    // state 13 -> 14 ***
move_time_data  c1b2_forward_smidge1    = {100, 200,   70,   70, 15};;                         // state 14 -> 15
move_time_data  c1b2_left_90            = {100, 340,  -70,  70, 20};                           // state 15 -> 20
tracktrack_data c1b2_track_yellow       = {YELLOW, YELLOW, blackblack,  70, 0, -40, 750, 25};  // state 20 -> 25 ***
move_time_data  c1b2_right_90           = {100, 350,  50,  -150, 27};                          // state 25 -> 27
move_time_data  c1b2_forward_jolt       = {100, 200,  100,  100, 30};                          // state 27 -> 30 
tracktrack_data c1b2_track_blue         = {BLUE, BLUE, hall,  70, 0, -40, 750, 35, YELLOW};            // state 30 -> 35 ***
/*                                                     *
 |  bot 2 after detecting hall sensor                  |
 * --------------------------------------------------- */
move_time_data  c1b2_stop_hall_jolt1    = {100, 350,  0,  0,  36};                         // state 35 -> 36
move_time_data  c1b2_turn_tcc_jolt      = {100, 460,  0,  -150, 38};                             // state 36 -> 38 // angle to TCC

// DID: SENDING TWO PULSES TO DOUBLE OUR CHANCES
flashled_data   c1b2_tcc200ms_flash     = {GREEN_STATE_LED_FLASH, 3, 40};                      // state 38 -> 40 
talk_data       c1b2_start_talk_tcc     = {430, 41};                                           // state 40 -> 41 (400 ms) // message 3
move_time_data  c1b2_pause_tcc          = {100, 200, 0, 0, 42};                                // state 41 -> 42
talk_data       c1b2_start_talk_tcc2    = {430, 43};                                           // state 42 -> 43 (400 ms) // message 3


// TODO: ensure that this is the right timing make sure this is the right threshold
listen_data     c1b2_start_listen_tcc   = {415, 300, 100, 40, 45, BLUE_STATE_LED_FLASH};       // state 43 -> 45 (RCV 400 ms) // message 3
 
move_time_data  c1b2_turn_tcc_jolt2     = {100, 460,  0,  150, 48};                           // state 45 -> 48 // angle back to road
tracktrack_data c1b2_track_blue_to_wall = {BLUE, BLUE, collision,  70, 0, -40, 750, 50, YELLOW};      // state 48 -> 50
flashled_data   c1b2_bluewall_flash     = {BLUE_STATE_LED_FLASH, 3, 53};                      // state 50 -> 53
move_time_data  c1b2_back_from_bluewall = {100, 1000, 0, 0, 55};                              // state 53 -> 55

move_time_data  c1b2_turn_90_to_bot     = {100, 300,  50,  -150, 58};                         // state 55 -> 58
move_time_data  c1b2_pause_before_bot1  = {100, 500,    0,    0, 59};                         // state 58 -> 59
talk_data       c1b2_talk_to_bot1    	  = {600, 80};                                          // state 59 -> 80 (500 ms)  // tell bot 1 to start again
move_time_data  c1b2_pause2_before_bot1  = {100, 2000,    0,    0, 85};                         // state 80 -> 85
talk_data       c1b2_talk2_to_bot1       = {600, 60};                                          // state 85 -> 60 (500 ms)  // tell bot 1 to start (#2)

/*                                                     *
 |  bots start to move until collision                          |
 * --------------------------------------------------- */
move_if_data    c1b2_final_collision    = {100, collision,   80, 80, 65};                    // state 60 -> 65
flashled_data   c1b2_final_flash        = {HEADLIGHT_LED_FLASH | BREAKLIGHT_LED_FLASH |
                                           LTURN_LED_FLASH     | RTURN_LED_FLASH, 10, 69};     // state 65 -> 69


/* COMMS_TEST 
    {THREAD_3, 1, {talk,    &testComms_talk_400}},        // state: 1 -> 5
    {THREAD_3, 5, {move_time, &testComms_pause}},         // state: 5 -> 10 
    {THREAD_3, 10, {move_time, &testComms_talk_400_2}},         // state: 10 -> 69 
*/
talk_data       testComms_talk_400      = {600, 5};
move_time_data  testComms_pause         = {100, 200, 0, 0, 10};
talk_data       testComms_talk_400_2    = {600, 69};


/* BOT 1 Challenge 1 ----------------------------- */
/*struct listen_data 
{
    int  duration;
    int  rising_edge;
    int  falling_edge;
    int  time_deviation;
    int NS;
    bool high;
    long long start_time;
};


struct move_time_data
{
  int ramp_time;
  int run_time;
  int Lmotor_speed; 
  int Rmotor_speed;
  int NS; 
  long long start_time;
};


*/


listen_data    listen_test     = {400, 300, 200, 50, 6, BLUE_PATH_LED_FLASH};                               // state 1 -> 69
flashled_data testflasjh   = {RED_STATE_LED_FLASH|BLUE_STATE_LED_FLASH, 500, 69}; // state 6 -> 69

/*

ABOVE IS SUPID


tracktrack_data c1b1_track_red          = {RED, RED,    YELLOW, LEFT_TRACK, 50, 0,-50, 750, false, 15};  // state 10
move_time_data       c1b1_right_90           = {100, 340, 150, -50, 0, 20};                           // state 15 -> 20 
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, NONE, LEFT_TRACK, 50,0,-50, 750, true, 25}; // state 20 -> 25
move_time_data       c1b1_left_90            = {100, 350, -50, 150, 0, 30};                           // state 25 -> 30 
tracktrack_data c1b1_track_blue         = {BLUE, BLUE, NONE, LEFT_TRACK, 50,50,-50, 750,false, 69}; // state 30 -> 35
f

 struct move_time_data
{
  int ramp_time;
  int run_time;
  int Lmotor_speed; 
  int Rmotor_speed;
  long long start_time;
  int NS;
};
 

 */


 
// HALL EFFECT REACTION BOT_1
move_time_data c1b1_run_person_over_part1 = {100,340,0,-150,0,90};
talk_data c1b1_run_person_over_part2 = {200, 0, -1};

int none (bool first_run, void *v)
{
  (void) first_run; (void) v;
  return 0;  
}

int pop (bool first_run, void *v)
{
    (void) first_run; (void) v;
    return  -1;
}


/* DO_NOTHING ---------------------------------------------------------------------- */
int hardware_stop (bool firstrun, void *v)
{
    (void) firstrun; (void) v;
    if (firstrun){
        //Serial.println("hardware off");
        Bot.lmotor.set_transition(CURRENT_SPEED,0, 100, LINEAR_SLOPE);
        Bot.rmotor.set_transition(CURRENT_SPEED,0, 100, LINEAR_SLOPE);
        Bot.hardware_on = false;
    }
    Bot.hardware_on = false;
    return 0;
} 
  
/* TRACKTRACK ---------------------------------------------------------------------- */
int tracktrack (bool firstrun, void *v) 
{
  // ;
  tracktrack_data *ttd = (tracktrack_data*)v;
  int last_off = 0;
  
  if (firstrun) {
      // initially set motors to full throttle
      Bot.enable_hall_interrupt();
      Bot.enable_collision_interrupt();
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      return 0;
  }
  
  // TODO: MAKE VARIABLE
  // IF EITHER MOTOR IS ON THE DESIRED COLOR, THEN TRANSITION
  if( ttd->iff() ) return ttd-> NS;
  
  // FOR THE TRACK BEING ON THE RIGHT -> ATTEND TO LEFT ERROR FIRST
  
  // IF THE left IS ON THE TRACK COLOR +> MAKE SURE THE LEFT IS GOING SLOW 
  //                                   +> MAKE SURE THE RIGHT IS GOING FAST
   Bot.show_following_path(ttd->L);
   if ((Bot.sensors.left() == ttd->L || Bot.sensors.left() == ttd->forgive)&& Bot.sensors.right() == ttd->R) { 
      Serial.println("go forward");
      ttd->last_state = 0;
      // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
  } else if (  ((Bot.sensors.right() != ttd->R && Bot.sensors.right() != ttd->forgive ) && (Bot.sensors.left() == ttd->L || Bot.sensors.left() == ttd->forgive)) ||
              (((Bot.sensors.right() != ttd->R && Bot.sensors.right() != ttd->forgive ) && (Bot.sensors.left() != ttd->L && Bot.sensors.left() != ttd->forgive)) && (ttd->last_state == 1))) {
      Serial.println("adjust left");
      ttd->last_state = 1;
      // ADJUST LEFT
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
  } else if ( ( (Bot.sensors.left()   != ttd->L && Bot.sensors.left()  != ttd->forgive) && (Bot.sensors.right() == ttd->R || Bot.sensors.right() == ttd->forgive) ) || 
              ( ((Bot.sensors.right() != ttd->R && Bot.sensors.right() != ttd->forgive) && (Bot.sensors.left()  != ttd->L && Bot.sensors.left()  != ttd->forgive)) && (ttd->last_state == 2))) {
      ttd->last_state = 2;
      Serial.println("adjust right");
      // ADJUST RIGHT
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
  } else {
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
      Serial.println("wtf");
      // TODO: IF I'M ON SOMETHING I DON'T UNDERSTAND THEN WTF
  }

  return 0;
}

/* 

struct tracktrack_data
{
  color L; // left color
  color R; // right color
  color D; // destination color
  bool track_right;
  int  ft; // fullthrottle
  int  mt; // mediumthrottle
  int  lt; // lowthrottle
  int  slope; // duration of motor change
  int  NS ; // next state
};


*/


/* MOVEBOT ---------------------------------------------------------------------- */
int move_time (bool firstrun, void *v) 
{
    move_time_data *md = (move_time_data*)v;
  
    // TURN ON LEFT TURN SIGNAL IF RIGHT MOTOR IS GOING FASTER THAN THE LEFT
    // TURN ON RIGHT TURN SIGNAL IF LEFT MOTOR IS GOING FASTER THAN THE RIGHT
    // TURN ON BREAK LIGHTS IF BOTH ARE SLOWING DOWN AND NOT TURNING
    // TURN ON HEADLIGHTS
    Bot.leds.headlights.on_solid();
    
    if (firstrun) {
        Bot.lmotor.set_transition(CURRENT_SPEED, md->Lmotor_speed, md->ramp_time, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, md->Rmotor_speed, md->ramp_time, LINEAR_DURATION);
        md-> start_time = millis();
        return 0;
    }
  
    if (md->Lmotor_speed > md->Rmotor_speed + TURNSIGNAL_THRESHOLD ) {
        Bot.leds.rturn.on_flash();
    } else if (md->Rmotor_speed > md->Lmotor_speed + TURNSIGNAL_THRESHOLD ) {
        Bot.leds.lturn.on_flash();
    }
    
    if (md->run_time < (millis() - md->start_time)) {
        return md -> NS;
    }
}

int move_if (bool firstrun, void *v) 
{
    move_if_data *md = (move_if_data*)v;

    // TURN ON HEADLIGHTS
    Bot.leds.headlights.on_solid();
   
    if (firstrun) {
        Bot.enable_hall_interrupt ();
        Bot.enable_collision_interrupt ();
        Bot.lmotor.set_transition(CURRENT_SPEED, md->Lmotor_speed, md->ramp_time, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, md->Rmotor_speed, md->ramp_time, LINEAR_DURATION);
        return 0;
    }
    
    if (md->Lmotor_speed > md->Rmotor_speed + TURNSIGNAL_THRESHOLD ) {
        Bot.leds.rturn.on_flash();
    } else if (md->Rmotor_speed > md->Lmotor_speed + TURNSIGNAL_THRESHOLD ) {
        Bot.leds.lturn.on_flash();
    }
    
    if( md->iff() ) return md-> NS;
    return 0;
}

/* FLASHLEDS ---------------------------------------------------------------------- */

int flashled (bool firstrun, void *v) 
{
    flashled_data *fd = (flashled_data*)v;
    bool flash_high   = Bot.leds.flashing_on();

    if (firstrun) {
        Bot.lmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        fd-> count   = fd-> flashes; 
        fd-> started = !flash_high; // if the lights are off
        fd->last_on  = false;
    }

    // if not started and the lights are on, start
    if (!fd-> started && flash_high) {fd-> started = true;}
    
    if (fd-> started) {
      
        if (!flash_high && (fd->last_on)) { fd-> count--;}
        fd-> last_on = flash_high;
        if (fd->count <= 0) { return fd-> NS;}
        
        if (fd->leds & RED_STATE_LED_FLASH)   Bot.leds.red_state.on_flash();
        if (fd->leds & GREEN_STATE_LED_FLASH) Bot.leds.green_state.on_flash();
        if (fd->leds & BLUE_STATE_LED_FLASH)  Bot.leds.blue_state.on_flash();
        if (fd->leds & RED_PATH_LED_FLASH)    Bot.leds.red_path.on_flash();
        if (fd->leds & BLUE_PATH_LED_FLASH)   Bot.leds.blue_path.on_flash();
        if (fd->leds & YELLOW_PATH_LED_FLASH) Bot.leds.yellow_path.on_flash();
        if (fd->leds & HEADLIGHT_LED_FLASH)   Bot.leds.headlights.on_flash();
        if (fd->leds & BREAKLIGHT_LED_FLASH)  Bot.leds.breaklights.on_flash();
        if (fd->leds & LTURN_LED_FLASH)       Bot.leds.lturn.on_flash();
        if (fd->leds & RTURN_LED_FLASH)       Bot.leds.rturn.on_flash(); 
    }
    
    return 0;
}

/* TALK ---------------------------------------------------------------------- */
int talk (bool firstrun, void *v) 
{
    talk_data *td = (talk_data *)v;
    if(firstrun)  ;
    Bot.disable_hall_interrupt();
    Bot.disable_collision_interrupt();
    
    
    if (firstrun) {
        Bot.sending_on();
        Bot.lmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        td -> start_time = millis();   
    }

    if (td -> duration > millis() - td-> start_time) {
        Bot.sending_on();
        return  0;
    } else {
        Bot.sending_off();
        Bot.enable_hall_interrupt();
        Bot.enable_collision_interrupt();
        return td-> NS; 
    }
}

/* LISTEN ---------------------------------------------------------------------- */
/*
struct listen_data 
{
    int  duration;
    int  rising_edge;
    int  falling_edge;
    int  time_deviation;
    bool high;
    long long start_time;
    int NS;
};

*/

/*
int RC_mode(bool firstrun, void *v)
{
  (void) firstrun; (void) v;
  Bot.lmotor.set_transition(CURRENT_SPEED, , 100, LINER_SLOPE);
  Bot.rmotor.set_transition(CURRENT_SPEED, , 100, LINEAR_SLOPE);
} 
*/

int listen (bool firstrun, void *v) 
{
    listen_data *ld = (listen_data *)v;
    int input_signal = Bot.receive();

    // TURN ON HEADLIGHTS
    Bot.leds.headlights.on_solid();

    // DEBUG CODE -----
    #ifdef DEBUG_COMMS
    if (!(ld-> high)) {
        VAR_((int)input_signal); 
        VAR_ln((int)(ld-> start_time));
    } else {
       VAR_ln((int)input_signal);
    }
    #endif
    // DEBUG CODE -----

    if (firstrun) {       
        Bot.lmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, 0, 100, LINEAR_DURATION);
        ld -> high = false;
    }
    
    if (!(ld->high) && ((input_signal) > (ld->rising_edge))) {
        ld-> high = true;
        ld-> start_time = millis(); 
    } else if ((ld->high) && ((input_signal) < (ld->falling_edge))) {
        ld-> high = false;
        ld-> start_time = millis() - (ld-> start_time);
        if ( ((ld->duration + ld->time_deviation) > ld-> start_time) 
          && (ld-> start_time > (ld->duration - ld->time_deviation))) {
            return ld-> NS;
        }
    }
    
    if (ld->high) {
        if (ld->reception_leds & RED_STATE_LED_FLASH)   Bot.leds.red_state.on_solid();
        if (ld->reception_leds & GREEN_STATE_LED_FLASH) Bot.leds.green_state.on_solid();
        if (ld->reception_leds & BLUE_STATE_LED_FLASH)  Bot.leds.blue_state.on_solid();
        if (ld->reception_leds & RED_PATH_LED_FLASH)    Bot.leds.red_path.on_solid();
        if (ld->reception_leds & BLUE_PATH_LED_FLASH)   Bot.leds.blue_path.on_solid();
        if (ld->reception_leds & YELLOW_PATH_LED_FLASH) Bot.leds.yellow_path.on_solid();
        if (ld->reception_leds & HEADLIGHT_LED_FLASH)   Bot.leds.headlights.on_solid();
        if (ld->reception_leds & BREAKLIGHT_LED_FLASH)  Bot.leds.breaklights.on_solid();
        if (ld->reception_leds & LTURN_LED_FLASH)       Bot.leds.lturn.on_solid();
        if (ld->reception_leds & RTURN_LED_FLASH)       Bot.leds.rturn.on_solid(); 
    }
    
    return 0;
}


/*
struct listen_data 
{
    int  duration;
    int  rising_edge;
    int  falling_edge;
    int  time_deviation;
    int NS; 
    int reception_leds;
    // ---- TEMPS ---- 
    bool high;
    long long start_time;
};
*/


// BOT 1 Challenge 2 ----------------------------- 
static const int FWD_TRAVEL_SPD   = 60;
static const int INCH_TRAVEL 	    = 80;
static const int TURN_WHEEL_SPD 	= -100;
static const int OPP_WHEEL_SPD 		= 100;
static const int TURN_90 		      = 300;

listen_data 	       c2b1_rcv_500ms			  = {500, 250, 150, 100, 5,BLUE_PATH_LED_FLASH};
move_time_data       c2b1_fwd_12in        = {100, INCH_TRAVEL*12, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 8};    // state 5 -> 8
flashled_data        c2b1_flash_head      = {HEADLIGHT_LED_FLASH, 2, 10}; //gonna remove later  
move_time_data       c2b1_stop_1      		= {100, 1000,	0,	 0, 15};
move_time_data       c2b1_turn_180        = {100, TURN_90*2, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 20};
move_time_data       c2b1_back_3     		  = {100, INCH_TRAVEL*3, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD, 25};
move_time_data       c2b1_stop_2      		= {100, 1000,	0,	 0,	  30};
move_time_data       c2b1_left_90      		= {100, TURN_90, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 35};
move_time_data       c2b1_right_1      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 40};
move_time_data       c2b1_lightstop_1     = {100, 500,	0,	 0,	  45}; 
move_time_data       c2b1_right_2      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 50};
move_time_data       c2b1_lightstop_2     = {100, 500,	0,	 0,	  55};
move_time_data       c2b1_right_3      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 60};
move_time_data		   c2b1_back_to_start		= {100, INCH_TRAVEL*14, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD,  65};
talk_data		         c2b1_send_500ms			= {500, 69};


// BOT 2 Challenge 2 ----------------------------- 
//listen_data     c1b1_listen_bot2_start  = {615, 500, 300, 40, 62, BLUE_STATE_LED_FLASH};       // state 60 -> 62 (RCV 500 ms

talk_data		         c2b2_send_500ms			= {500, 2};
listen_data 	       c2b2_rcv_500ms			  = {500, 300, 200, 100, 5,BLUE_PATH_LED_FLASH};
move_time_data       c2b2_fwd_12in        = {100, INCH_TRAVEL*12, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 10};
move_time_data       c2b2_stop_1      		= {100, 1000,	0,	 0, 15};
move_time_data       c2b2_turn_180        = {100, TURN_90*2, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 20};
move_time_data       c2b2_back_3     		  = {100, INCH_TRAVEL*3, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD, 25};
move_time_data       c2b2_stop_2      		= {100, 1000,	0,	 0, 30};
move_time_data       c2b2_left_90      		= {100, TURN_90 , TURN_WHEEL_SPD, OPP_WHEEL_SPD, 35};
move_time_data       c2b2_right_1      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 40};
move_time_data       c2b2_lightstop_1     = {100, 500,	0,	 0,	 45}; 
move_time_data       c2b2_right_2      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 50};
move_time_data       c2b2_lightstop_2     = {100, 500,	0,	 0,	 55};
move_time_data       c2b2_right_3      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 60};
move_time_data		   c2b2_back_to_start		= {100, INCH_TRAVEL*14, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD, 69};

// BOT 1 Challenge 3 -------------------------------- 
move_time_data      c3b1_wait_start       = {100, 1000, 0, 0, 3};
move_if_data 	      c3b1_forward_light		= {100, headlights_sensed, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 5};
move_time_data      c3b1_stop_5s      		= {100, 2000,	0,	 0, 10};
talk_data		        c3b1_send_500ms			  = {500, 15};
flashled_data 	    c3b1_flash_head_twice	= {HEADLIGHT_LED_FLASH, 2, 20}; 	
flashled_data 	    c3b1_illuminate_turnL	= {LTURN_LED_FLASH, 10, 25};
flashled_data       c3b1_illuminate_turnR = {RTURN_LED_FLASH, 10, 69};

// BOT 2 Challenge 3 -------------------------------- 
move_time_data      c3b2_wait_start       = {100, 1000, 0, 0, 3};
move_if_data 	      c3b2_forward_light		= {100, headlights_sensed, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 5};
listen_data		      c3b2_rcv_500ms			  = {500, 250, 150, 200, 10, BLUE_PATH_LED_FLASH};
flashled_data 	    c3b2_flash_head_twice	= {HEADLIGHT_LED_FLASH, 2, 15};	
flashled_data       c3b2_illuminate_turnL = {LTURN_LED_FLASH, 10, 20};
flashled_data       c3b2_illuminate_turnR = {RTURN_LED_FLASH, 10, 69};

#endif
