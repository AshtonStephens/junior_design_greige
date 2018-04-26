
#ifndef PROGRAM_FUNCTIONS_H_
#define PROGRAM_FUNCTIONS_H_

#define RIGHT_TRACK true
#define LEFT_TRACK  false

#define RED_LED_FLASH    1 << 0
#define GREEN_LED_FLASH  1 << 1
#define BLUE_LED_FLASH   1 << 2

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

struct move_data
{
  int ramp_time;
  int run_time;
  int Lmotor_speed; 
  int Rmotor_speed;
  long long start_time;
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

/* BOT 1 Challenge 1 ----------------------------- */
flashled_data   c1b1_initflash          = {RED_LED_FLASH|BLUE_LED_FLASH, 3, 200, 800, 0,0, 69}; // state 1
talk_data       c1b1_start_talk         = {500,  0  ,10}; // state 5
flashled_data   c1b1_startflash         = {GREEN_LED_FLASH, 1, 1000, 0, 0, 0, 15}; // state 10
move_data       c1b1_starting_run       = {100, 0, 100, 100, 0, 20}; // state 15
move_data       c1b1_go_back_a_bit_bot1 = {100, 1000, -100, -100, 0, 23}; // state 20
move_data       c1b1_turn_a_bit_bot1    = {100, 300, 100, -100, 0, 25}; // state 23
tracktrack_data c1b1_track_blue         = {BLACK, BLUE,  YELLOW, RIGHT_TRACK, 100,75, 25, 750, 30}; // state 25
move_data       c1b1_turn_after_blue    = {100, 400, 100, -100, 0, 35}; // state 30
tracktrack_data c1b1_track_yellow       = {BLACK, YELLOW,  RED, RIGHT_TRACK, 100,75, 25, 750, 40}; // state 35
move_data       c1b1_turn_after_yellow  = {100, 400, -100, 100, 0, 45}; // state 40 
tracktrack_data c1b1_track_red          = {BLACK, RED,  NONE, RIGHT_TRACK, 100,75, 25, 750, 50}; // state 45
move_data       c1b1_turn_after_red     = {100, 400, -100, 100, 0,55}; // state 50 
 
move_data testbot2 = {100,1000,100,-100,0,69};
 
tracktrack_data testtrack          = {YELLOW, RED,  BLACK, RIGHT_TRACK, 100,75, 25, 750, 50}; // state 45-

int none (bool first_run, void *v)
{
  (void) first_run; (void) v;
  return 0;  
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
    return 0;
} 
  
/* TRACKTRACK ---------------------------------------------------------------------- */
int tracktrack (bool firstrun, void *v) 
{

  DBG;
  tracktrack_data *ttd = (tracktrack_data*)v;
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
  if (ttd->track_right) {
      Bot.show_following_path(ttd->R);
      if (Bot.sensors.left() == ttd->L && Bot.sensors.right() == ttd->R) {
          Serial.println("go forward");
          // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      } else if (Bot.sensors.left() == ttd->R) {
          Serial.println("adjust left");
          // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
      } else if (Bot.sensors.right() == ttd->L) {
          Serial.println("adjust right");
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
      } else {
         // Serial.println("wtf");
          // TODO: IF I'M ON SOMETHING I DON'T UNDERSTAND THEN WTF
      }
  } else {
       Bot.show_following_path(ttd->L);
       if (Bot.sensors.left() == ttd->L && Bot.sensors.right() == ttd->R) { 
          Serial.println("go forward");
          // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->ft, ttd->slope, LINEAR_SLOPE);
      } else if (Bot.sensors.right() == ttd->L) {
          Serial.println("adjust right");
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
      } else if (Bot.sensors.left() == ttd->R) {
          Serial.println("adjust left");
          // IF IM CORRECTLY ON THE TRACK THEN GO FORWARD
          Bot.lmotor.set_transition(CURRENT_SPEED, ttd->lt, ttd->slope, LINEAR_SLOPE);
          Bot.rmotor.set_transition(CURRENT_SPEED, ttd->mt, ttd->slope, LINEAR_SLOPE);
      } else {
          Serial.println("wtf");
          // TODO: IF I'M ON SOMETHING I DON'T UNDERSTAND THEN WTF
      }
  }
  return 0;
}

/* MOVEBOT ---------------------------------------------------------------------- */
int move_time (bool firstrun, void *v) 
{
  DBG;
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
  DBG;
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
