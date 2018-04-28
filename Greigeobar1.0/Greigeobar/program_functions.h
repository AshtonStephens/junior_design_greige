
#ifndef PROGRAM_FUNCTIONS_H_
#define PROGRAM_FUNCTIONS_H_

#define RIGHT_TRACK true
#define LEFT_TRACK  false

#define RED_LED_FLASH    1 << 0
#define GREEN_LED_FLASH  1 << 1
#define BLUE_LED_FLASH   1 << 2

#define DEFAULT_END 69

#define IS_GO 1
#define IS_ADJUST_RIGHT 2
#define IS_ADJUST_LEFT  3

#define MR_ 2  // MOTOR RELATIONSHIP

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
    int leds;
    int flashes;
    int on_time;
    int off_time;
    int temp1;
    long long temp2;
    int  NS;
};

struct tracktrack_data
{
  color L; // left color
  color R; // right color
  color D; // destination color
  int  last_state; // 
  int  ft; // fullthrottle
  int  mt; // mediumthrottle
  int  lt; // lowthrottle
  int  slope; // duration of motor change
  bool transblack;
  int  NS ; // next state
};

/* BOT 1 Challenge 1 ----------------------------- */

flashled_data   c1b1_initflash          = {RED_LED_FLASH|BLUE_LED_FLASH, 3, 200, 800, 0,0, 69}; // state 1
talk_data       c1b1_start_talk         = {500,  0  ,10}; // state 5
flashled_data   c1b1_startflash         = {GREEN_LED_FLASH, 1, 1000, 0, 0, 0, 15}; // state 10

move_data       c1b1_starting_run1      = {100, 2000, 200, 200,  0, 10}; // state 1 -> 10
move_data       c1b1_starting_run2      = {100, 550, -150, -200, 0, 12}; // state 10-> 12 
move_data       c1b1_starting_run3      = {10000, 300, 100, -200,0, 69}; // state 12 -> 69



tracktrack_data c1b1_track_red          = {BLUE, BLUE,  YELLOW, LEFT_TRACK, MR_*50, MR_*0,MR_*-50, 750, false, 15};  // state 10
move_data       c1b1_right_90           = {100, 340, MR_*150, MR_*-50, 0, 20};                           // state 15 -> 20 
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, NONE, LEFT_TRACK, MR_*50,MR_*0,MR_*-50, 750, true, 25}; // state 20 -> 25
move_data       c1b1_left_90            = {100, 350, MR_*-150, MR_*50, 0, 30};                           // state 25 -> 30 
tracktrack_data c1b1_track_blue         = {RED, RED, NONE, LEFT_TRACK, MR_*50,MR_*0,MR_*-50, 750,false, 69}; // state 30 -> 35
/*

ABOVE IS SUPID


tracktrack_data c1b1_track_red          = {RED, RED,    YELLOW, LEFT_TRACK, 50, 0,-50, 750, false, 15};  // state 10
move_data       c1b1_right_90           = {100, 340, 150, -50, 0, 20};                           // state 15 -> 20 
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, NONE, LEFT_TRACK, 50,0,-50, 750, true, 25}; // state 20 -> 25
move_data       c1b1_left_90            = {100, 350, -50, 150, 0, 30};                           // state 25 -> 30 
tracktrack_data c1b1_track_blue         = {BLUE, BLUE, NONE, LEFT_TRACK, 50,50,-50, 750,false, 69}; // state 30 -> 35




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
int hardware_stop (bool first_run, void *v)
{
    (void) first_run; (void) v;
    if (first_run){
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

  //DBG;
  tracktrack_data *ttd = (tracktrack_data*)v;
  int last_off = 0;
  
  if (firstrun) {
      //Serial.println("SET_ME_ON_FIRE");
      // initially set motors to full throttle
      Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      return 0;
  }
  
  // TODO: MAKE VARIABLE
  // IF EITHER MOTOR IS ON THE DESIRED COLOR, THEN TRANSITION
  if (ttd->D == NONE && Bot.collision_interrupt) {
      Bot.collision_interrupt = 0;                            // IF SOMETHING IS GOING WRONG THEN 
      Bot.collision_interrupt_last = 0;                       // IT WILL BE WITH THIS !!!!!!!!!!!!!!!!!!!!!
      return ttd -> NS;
  } else if (ttd->D == Bot.sensors.right() || ttd->D == Bot.sensors.left()) {
      Bot.show_following_path(NONE);
      return ttd->NS;
  }
  
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

int trackytrack (bool firstrun, void *v)
{
    tracktrack_data* ttd = (tracktrack_data*)v;
    if (ttd->R != Bot.sensors.right()) {
        Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
        Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
    } else if (ttd->L != Bot.sensors.left()) {
        Bot.rmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
        Bot.lmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
    } else {
        Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
        Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);      
    }

    if (ttd->D == Bot.sensors.right() || ttd->D == Bot.sensors.left()) {
      Bot.show_following_path(NONE);
      return ttd->NS;
    }
}

/* MOVEBOT ---------------------------------------------------------------------- */
int move_time (bool firstrun, void *v) 
{
  move_data *md = (move_data*)v;


  // TURN ON LEFT TURN SIGNAL IF RIGHT MOTOR IS GOING FASTER THAN THE LEFT
  // TURN ON RIGHT TURN SIGNAL IF LEFT MOTOR IS GOING FASTER THAN THE RIGHT
  // TURN ON BREAK LIGHTS IF BOTH ARE SLOWING DOWN AND NOT TURNING
  
  if (firstrun) {

      Bot.lmotor.set_transition(CURRENT_SPEED, md->Lmotor_speed, md->ramp_time, LINEAR_DURATION);
      Bot.rmotor.set_transition(CURRENT_SPEED, md->Rmotor_speed, md->ramp_time, LINEAR_DURATION);
      md-> start_time = millis();
      
      return 0;
  }
  
  if (md->run_time < (millis() - md->start_time)) {
      DBG;
      return md -> NS;
  }
}

int move_collision (bool firstrun, void *v) 
{
  move_data *md = (move_data*)v;


  // TURN ON LEFT TURN SIGNAL IF RIGHT MOTOR IS GOING FASTER THAN THE LEFT
  // TURN ON RIGHT TURN SIGNAL IF LEFT MOTOR IS GOING FASTER THAN THE RIGHT
  // TURN ON BREAK LIGHTS IF BOTH ARE SLOWING DOWN AND NOT TURNING
  
  if (firstrun) {

      Bot.lmotor.set_transition(CURRENT_SPEED, md->Lmotor_speed, md->ramp_time, LINEAR_DURATION);
      Bot.rmotor.set_transition(CURRENT_SPEED, md->Rmotor_speed, md->ramp_time, LINEAR_DURATION);
      return 0;
  }
  
  if (Bot.collision_interrupt) {
      Bot.collision_interrupt = 0;
      Bot.collision_interrupt_last = 0;
      return md -> NS;
  }
}

int move_if (bool firstrun, void *v) 
{
    DBG;
    move_data_if *md = (move_data_if*)v;
    
    if (firstrun) {
        Bot.lmotor.set_transition(CURRENT_SPEED, md->Lmotor_speed, md->ramp_time, LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED, md->Rmotor_speed, md->ramp_time, LINEAR_DURATION);
        return 0;
    }
    if( md->iff() ) return md-> NS;
    return 0;
}

/* FLASHLEDS ---------------------------------------------------------------------- */
int flashled (bool firstrun, void *v) 
{
    flashled_data *fd = (flashled_data*)v;
    if (firstrun) {
        fd-> temp1 = fd-> flashes << 1;
        fd-> temp2 = millis();
    }
    
    if (!(fd-> temp1 & 1)) { // LED ON
        if (fd-> on_time > millis() - fd-> temp2) {
            if ((fd->leds) & RED_LED_FLASH)   Bot.red_state_led_on();
            if ((fd->leds) & BLUE_LED_FLASH)  Bot.blue_state_led_on();
            if ((fd->leds) & GREEN_LED_FLASH) Bot.green_state_led_on();
        } else {
            fd-> temp2 = millis();
            if ((fd-> temp1) == 0) return fd-> NS;
            --(fd-> temp1);
            if ((fd-> temp1) == 0) return fd-> NS;
        }
    } else { // LED OFF
        if (fd-> off_time > millis() - fd-> temp2) {
            if ((fd->leds) & RED_LED_FLASH)   Bot.red_state_led_off();
            if ((fd->leds) & BLUE_LED_FLASH)  Bot.blue_state_led_off();
            if ((fd->leds) & GREEN_LED_FLASH) Bot.green_state_led_off();
        } else {
            fd-> temp2 = millis();
            if ((fd-> temp1) == 0) return fd-> NS;
            --(fd-> temp1);
            if ((fd-> temp1) == 0) return fd-> NS;
        }
    }
    return 0;
}

/* TALK ---------------------------------------------------------------------- */
int talk (bool firstrun, void *v) 
{
    talk_data *td = (talk_data *)v;
    
    attachInterrupt(digitalPinToInterrupt(HALL), nothing, FALLING);      //
    attachInterrupt(digitalPinToInterrupt(COLLISION), nothing, FALLING); //
    
    if (firstrun) {
        Bot.sending_on();
        td -> start_time = millis();   
    }

    if (td -> duration > millis() - td-> start_time) {
        Bot.sending_on();
        return  0;
    } else {
        Bot.sending_off();
        attachInterrupt(digitalPinToInterrupt(HALL), hall_detect, FALLING);           //
        attachInterrupt(digitalPinToInterrupt(COLLISION), collision_detect, FALLING); //
        return td-> NS; 
    }
}

/* LISTEN ---------------------------------------------------------------------- */
int listen_ (bool firstrun, void *v) 
{
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

#endif
