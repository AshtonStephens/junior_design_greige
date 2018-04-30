
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

#define MR_ 2 // MOTOR RELATIONSHIP

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

bool hall ()
{
  return Bot.hall_interrupt;  
}
bool collision ()
{
  return Bot.collision_interrupt;  
}

///// TESTING FUNCTION FOR THE HALL EFFECT INTERRUPT
//////////////////////////////////////////////////////

struct test_delay_data
{
    int del;
    long long temp;
    int NS;
};

int test_delay (bool firstrun, void *v) 
{
    DBG;
    test_delay_data *td = (test_delay_data*)v;
    if (firstrun) {td-> temp = millis();}
    if (millis() - td-> temp > td-> del) {return td-> NS;}
    Bot.leds.red_path.on_flash();
    return 0;
}

test_delay_data td1 = {6000, 0,69};

//////////////////////////////////////////////////////
///// TESTING FUNCTION FOR THE HALL EFFECT INTERRUPT


/* --------------------------------------------------------------- CHALLENGE 2/3
static const int light_threshold = 200;

bool headlights_sensed()
{
	return analogRead(HEADLIGHT_SENSOR) > light_threshold); 
}
   ---------------------------------------------------------------  CHALLENGE 2/3 */

void nothing();
void hall_detect();
void collision_detect();

struct talk_data 
{
    int duration;
    long long start_time;
    int NS;
};

struct listen_data 
{
    int  duration;
//    int  rising_edge;
//    int  falling_edge;
    int  deviation;
    bool high;
    long long start_time;
    int NS;
};

struct move_data
{
  int ramp_time;
  int run_time;
  int Lmotor_speed; 
  int Rmotor_speed;
  long long start_time;
  int NS;
};

struct move_data_if
{
  int ramp_time;
  bool (*iff)();
  int Lmotor_speed; 
  int Rmotor_speed;
  int NS;
};

struct flashled_data
{
    int  leds;
    int  flashes;
    bool last_on;
    bool started;
    int  count;
    int  NS;
};

struct tracktrack_data
{
  color L; // left color
  color R; // right color
  bool (*iff)(); // condition to leave
  int  last_state; // 
  int  ft; // fullthrottle
  int  mt; // mediumthrottle
  int  lt; // lowthrottle
  int  slope; // duration of motor change
  bool transblack;
  int  NS ; // next state
};

/* BOT 1 Challenge 1 ----------------------------- */

flashled_data   c1b1_initflash          = {RED_STATE_LED_FLASH|BLUE_STATE_LED_FLASH, 3, false, false, 0, 4};                 // state 1 -> 4
talk_data       c1b1_start_talk         = {200,  0  ,5};                                                                     // state 4 -> 5
flashled_data   c1b1_startflash         = {GREEN_STATE_LED_FLASH, 3, false, false,0, 6};                                     // state 5 -> 6
move_data_if    c1b1_initial_collision1 = {100, collision, MR_* 100, MR_ * 87, 8};                                           // state 6 -> 8
move_data       c1b1_initial_collision2 = {100, 1000, -150, -200, 0, 10};                                                    // state 8 -> 10
move_data_if    c1b1_initial_collision3 = {1000, blueblue, 100, 75, 13};                                                     // state 10 -> 13
tracktrack_data c1b1_track_blue         = {BLUE, BLUE,  yellowyellow, LEFT_TRACK, MR_*50, MR_*0,MR_*-50, 750, false, 14};    // state 13 -> 14
move_data       c1b1_forward_smidge1    = {100, 200, MR_*100, MR_*100, 0, 15};;                                              // state 14 -> 15
move_data       c1b1_right_90           = {100, 340, MR_*100, MR_*-100, 0, 20};                                              // state 15 -> 20
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, blackblack, LEFT_TRACK, MR_*50,MR_*0,MR_*-50, 750, true, 25};     // state 20 -> 25
move_data       c1b1_left_90            = {100, 350, MR_*-150, MR_*50, 0, 27};                                               // state 25 -> 27
move_data       c1b1_forward_jolt       = {100, 200, MR_*100, MR_*100, 0, 30};                                               // state 27 -> 30 
tracktrack_data c1b1_track_red          = {RED, RED, hall, LEFT_TRACK, MR_*50,MR_*0,MR_*-50, 750,false, 35};                 // state 30 -> 35
move_data       c1b1_stop_hall_jolt1    = {100, 1000, 0, 0, 0, 36};                                                          // state 35 -> 36
move_data       c1b1_turn_tcc_jolt      = {100, 700, 0, -70, 0, 38};                                                         // state 36 -> 38
talk_data       c1b1_start_talk_tcc     = {200,  0  ,45};                                                                    // state 38 -> 45 (200 ms?)
move_data       c1b1_turn_tcc_jolt2     = {100, 700, 0, 70, 0, 69};                                                          // state 45 -> 50

/*

ABOVE IS SUPID


tracktrack_data c1b1_track_red          = {RED, RED,    YELLOW, LEFT_TRACK, 50, 0,-50, 750, false, 15};  // state 10
move_data       c1b1_right_90           = {100, 340, 150, -50, 0, 20};                           // state 15 -> 20 
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, NONE, LEFT_TRACK, 50,0,-50, 750, true, 25}; // state 20 -> 25
move_data       c1b1_left_90            = {100, 350, -50, 150, 0, 30};                           // state 25 -> 30 
tracktrack_data c1b1_track_blue         = {BLUE, BLUE, NONE, LEFT_TRACK, 50,50,-50, 750,false, 69}; // state 30 -> 35
f

 struct move_data
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
move_data c1b1_run_person_over_part1 = {100,340,0,-150,0,90};
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
    if(firstrun) DBG;
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
  if(firstrun) DBG;
  //DBG;
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
   if (Bot.sensors.left() == ttd->L && Bot.sensors.right() == ttd->R) { 
      Serial.println("go forward");
      ttd->last_state = 0;
      // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
  } else if ( (Bot.sensors.right() != ttd->R && Bot.sensors.left() == ttd->L) ||
              ((Bot.sensors.right() != ttd->R  && Bot.sensors.left() != ttd->L) && (ttd->last_state == 1))) {
      Serial.println("adjust left");
      ttd->last_state = 1;
      // ADJUST LEFT
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
  } else if ( (Bot.sensors.left() != ttd->L && Bot.sensors.right() == ttd->R) || 
              ((Bot.sensors.right() != ttd->R && Bot.sensors.left() != ttd->L) && (ttd->last_state == 2))) {
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

  if (ttd-> transblack && Bot.sensors.left() == BLACK && Bot.sensors.right() == BLACK) {
      return ttd-> NS;
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
    move_data *md = (move_data*)v;
  
    if(firstrun) DBG;
    // TURN ON LEFT TURN SIGNAL IF RIGHT MOTOR IS GOING FASTER THAN THE LEFT
    // TURN ON RIGHT TURN SIGNAL IF LEFT MOTOR IS GOING FASTER THAN THE RIGHT
    // TURN ON BREAK LIGHTS IF BOTH ARE SLOWING DOWN AND NOT TURNING
    
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
    if(firstrun) DBG;
    move_data_if *md = (move_data_if*)v;
    

    
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
    if(firstrun) DBG;
    flashled_data *fd = (flashled_data*)v;
    bool flash_high   = Bot.leds.flashing_on();

    if (firstrun) {
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
    if(firstrun) DBG;
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
    bool high;
    long long start_time;
    int NS;
};
*/

int listen (bool firstrun, void *v) 
{
    if(firstrun) DBG;
    listen_data *ld = (listen_data *)v;

    
    
    if (firstrun) {
        ld -> high = false;
    }

    if (ld-> high) {
        if (!Bot.receiving()){
            // if the comms signal is within bounds
            if (( ((ld-> duration - ld-> deviation) < (millis() - ld->start_time)) &&
                  ((millis() - ld->start_time)) < (ld-> duration + ld-> deviation)) ) {
                return ld-> NS;
            } else {
                ld->high = false;
                return 0;
            }
        }
    } else {
        if (Bot.receiving()) {
            ld-> high;
            ld-> start_time = millis();
        }
    }
}
/*
// BOT 1 Challenge 2 ----------------------------- 
static const int FWD_TRAVEL_SPD = 200;
static const int INCH_TRAVEL 	= 150;
static const int TURN_WHEEL_SPD 	= -100;
static const int OPP_WHEEL_SPD 		= 100;
static const int TURN_90 		= 300;

listen_data 	c2b1_rcv_500ms			= {515, 30, 1, 0, 5};
move_data       c2b1_fwd_12in           = {100, INCH_TRAVEL*12, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD,   0, 10};
move_data       c2b1_stop_1      		= {100, 1000,	0,	 0,	  0, 15};
move_data       c2b1_turn_180      		= {100, TURN_90*2, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 0, 20};
move_data       c2b1_back_3     		= {100, INCH_TRAVEL*3, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD,   0, 25};
move_data       c2b1_stop_2      		= {100, 1000,	0,	 0,	  0, 30};
move_data       c2b1_left_90      		= {100, TURN_90, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 0, 35};
move_data       c2b1_right_1      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 0, 40};
move_data       c2b1_lightstop_1      	= {100, 500,	0,	 0,	  0, 45}; 
move_data       c2b1_right_2      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 50};
move_data       c2b1_lightstop_2      	= {100, 500,	0,	 0,	  0, 55};
move_data       c2b1_right_3      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 60};
move_data		c2b1_back_to_start		= {100, INCH_TRAVEL*15, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD,   0, 65};
talk_data		c2b1_send_500ms			= {500, 0, 69};

// BOT 2 Challenge 2 ----------------------------- 
talk_data		c2b2_send_500ms			= {500, 0, 2};
listen_data 	c2b2_rcv_500ms			= {515, 30, 1, 0, 5};
move_data       c2b2_fwd_12in           = {100, INCH_TRAVEL*12, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD,   0, 10};
move_data       c2b2_stop_1      		= {100, 1000,	0,	 0,	  0, 15};
move_data       c2b2_turn_180      		= {100, TURN_90*2, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 0, 20};
move_data       c2b2_back_3     		= {100, INCH_TRAVEL*3, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD,   0, 25};
move_data       c2b2_stop_2      		= {100, 1000,	0,	 0,	  0, 30};
move_data       c2b2_left_90      		= {100, TURN_90, TURN_WHEEL_SPD, OPP_WHEEL_SPD, 0, 35};
move_data       c2b2_right_1      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 0, 40};
move_data       c2b2_lightstop_1      	= {100, 500,	0,	 0,	  0, 45}; 
move_data       c2b2_right_2      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 50};
move_data       c2b2_lightstop_2      	= {100, 500,	0,	 0,	  0, 55};
move_data       c2b2_right_3      		= {100, TURN_90, OPP_WHEEL_SPD, TURN_WHEEL_SPD, 60};
move_data		c2b2_back_to_start		= {100, INCH_TRAVEL*15, -FWD_TRAVEL_SPD, -FWD_TRAVEL_SPD,   0, 69};

// BOT 1 Challenge 3 -------------------------------- 
move_data_if 	c3b1_forward_light		= {100, headlights_sensed, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 5);
move_data       c3b1_stop_5s      		= {100, 5000,	0,	 0,	  0, 10};
talk_data		c3b1_send_500ms			= {500, 0, 15};
flashled_data 	c3b1_flash_head_twice	= {};	
flashed_data 	c3b1_illuminate_turn	= {};

// BOT 1 Challenge 2 -------------------------------- 
move_data_if 	c3b2_forward_light		= {100, headlights_sensed, FWD_TRAVEL_SPD, FWD_TRAVEL_SPD, 5);
listen_data		c3b2_rcv_500ms			= {515, 30, 1, 0, 10};
flashled_data 	c3b2_flash_head_twice	= {};	
flashed_data 	c3b2_illuminate_turn	= {};
*/
#endif
