
#ifndef PROGRAM_FUNCTIONS_H_
#define PROGRAM_FUNCTIONS_H_

#define RIGHT_TRACK true
#define LEFT_TRACK  false

#define RED_LED_FLASH    1 << 0
#define GREEN_LED_FLASH  1 << 1
#define BLUE_LED_FLASH   1 << 2


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





/* -------------------   =  ramp_time| run_time | Lmotor_speed | Rmotor_speed | temporary |  NS */
move_data turn_right_9069 = {100,       10000,     170,           -100,           0,           69};
move_data turn_left_9069  = {100,       400,       -100,           170,           0,           69};
move_data turn_right_905  = {100,       400,       170,           -100,           0,           5};
move_data turn_left_903   = {100,       400,       -100,           170,           0,           3};

move_data turn_right_90   = {100,       400,       170,           -100,           0,           69};




flashled_data fdt1     = {RED_LED_FLASH|BLUE_LED_FLASH, 10, 200, 200, 0,0,69};
flashled_data bluered3 = {RED_LED_FLASH|BLUE_LED_FLASH, 3, 500, 200,  0,0,69};
flashled_data bluered3i = {RED_LED_FLASH|GREEN_LED_FLASH, 3, 500, 200,  0,0,-1};

talk_data   send500_test   = {500,0,69};
listen_data listen500_test = {500,75,false,0,69};

tracktrack_data YELLOW_RED_TEST = {YELLOW,  RED,  BLACK, RIGHT_TRACK ,130,90, 25, 1000, 69};

// ALSO WORKS
// tracktrack_data YELLOW_RED_TEST = {YELLOW,  RED,  BLACK, RIGHT_TRACK ,100,75, 25, 1000, 69};




// track tracking
// -----------------    =  LEFT    RIGHT  DEST   track_side   SPD TSPD  TDR   NS
tracktrack_data lyrr_rt = {YELLOW, RED,   BLACK, RIGHT_TRACK ,150,100, -50, 750, 69};
tracktrack_data lrry_lt = {RED, YELLOW,   BLACK, LEFT_TRACK  ,150,100, -50, 750, 69};

tracktrack_data lbrr_rt = {BLACK, RED,   YELLOW, RIGHT_TRACK ,150,100, -50, 750, 69};
tracktrack_data lrrb_lt = {RED, BLACK,   YELLOW, LEFT_TRACK  ,150,100, -50, 750, 69};

/*
tracktrack_data lbrr_rt2 = {YELLOW, RED,    BLACK, RIGHT_TRACK , 100, 0, 750, 69};
tracktrack_data lbry_rt4 = {BLACK,  YELLOW, BLUE,   RIGHT_TRACK ,150, 30, 750, 4};
tracktrack_data llrb_lt6 = {BLUE,   BLACK,  YELLOW, LEFT_TRACK  ,150, 30, 750, 6};
*/

tracktrack_data lbrr_rt2 = {BLACK, RED,    YELLOW, RIGHT_TRACK ,170, 150, 50, 750, 2};
tracktrack_data lbry_rt4 = {BLACK, YELLOW, BLUE,   RIGHT_TRACK ,170, 150, 50, 750, 4};
tracktrack_data llrb_lt6 = {BLUE,  BLACK,  YELLOW, LEFT_TRACK  ,170, 150, 50, 750, 6};






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
  if (ttd->D == Bot.sensors.right() || ttd->D == Bot.sensors.left()) {
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
int movemedaddy (bool firstrun, void *v) 
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

/* FLASHLEDS ---------------------------------------------------------------------- */
int flashleds (bool firstrun, void *v) 
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
    
    if (firstrun) {
        Bot.sending_on();
        td -> start_time = millis();   
    }

    if (td -> duration > millis() - td-> start_time) {
        Bot.sending_on();
        return  0;
    } else {
        Bot.sending_off();
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
