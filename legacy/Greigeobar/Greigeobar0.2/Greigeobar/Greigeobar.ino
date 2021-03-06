

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


// state switches ------ 
#define STATE_SWITCH_1   47
#define STATE_SWITCH_2   45
#define STATE_SWITCH_3   43
#define STATE_SWITCH_4   41

// sensor network ------- 
#define L_LIGHT_SENSOR  A6 // ?
#define R_LIGHT_SENSOR  A7 // ?
#define HALL_EFFECT     3  
#define RED_SENSOR_LED  39 
#define BLUE_SENSOR_LED 37 
#define COLLISION_PIN   2

// communicaton ---- // 
#define RECEIVING A7 //
#define SENDING   27 //

// motors -------------- // 
#define R_MOTOR_PIN2 7  // ?
#define R_MOTOR_PIN1 6  // ?
#define L_MOTOR_PIN2 5  // ?
#define L_MOTOR_PIN1 4  // ?

#define STABILIZATION_TIME 50

#include "bot.h"

const float redBsl[NPARAMS+1] = {-5.713125, 15.103408, 6.903004, -5.565095, -1.073656};
const float bluBsl[NPARAMS+1] = {-6.896294, -1.757802, -0.295036, 11.303079, 3.536464};
const float redBsr[NPARAMS+1] =  {-5.627664, 15.468755, 6.993172, -5.601236, -1.420434};
const float bluBsr[NPARAMS+1] = {-6.935288, -1.787222, -0.303681, 11.240418, 3.810915};

bot BOTTY(R_MOTOR_PIN1, R_MOTOR_PIN2,
          L_MOTOR_PIN1, L_MOTOR_PIN2,
          L_LIGHT_SENSOR, R_LIGHT_SENSOR,
          RED_SENSOR_LED, BLUE_SENSOR_LED, STABILIZATION_TIME,
          redBsl,bluBsl,redBsr,bluBsr);


void setup() {
  pinMode(0, OUTPUT); 
  pinMode(1, OUTPUT); 
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)  {}
  Serial.print("printing ready\n");
  
  
  pinMode(R_MOTOR_PIN1, OUTPUT); 
  pinMode(R_MOTOR_PIN2, OUTPUT); 
  pinMode(L_MOTOR_PIN1, OUTPUT);
  pinMode(L_MOTOR_PIN2, OUTPUT);
  
  
}
 

 /* bot(int mpin_enable_R, int mpin1_R, int mpin2_R,
        int mpin_enable_L, int mpin1_L, int mpin2_L,
        int sensor_pin_left, int sensor_pin_right,int red_pin, int blue_pin, 
        int stabilization_time, 
        const Betas &redB_left , const Betas &bluB_left,
        const Betas &redB_right, const Betas &bluB_right) :
          motors( mpin_enable_R,mpin1_R,mpin2_R,
                  mpin_enable_L,mpin1_L,mpin2_L),
          sensors(sensor_pin_left,sensor_pin_right,red_pin,blue_pin,
                  stabilization_time,redB_left,bluB_left,redB_right,bluB_right){}
*/

    
void loop() 
{

    BOTTY.sensors.sense();   
    unsigned long timer;
    color r_color = BOTTY.sensors.right();

    bool run = false;
 
    
    int spd = 50; 

    

    if (run) {
      analogWrite (R_MOTOR_PIN1, 0);
      analogWrite (R_MOTOR_PIN2, 50);
      analogWrite (L_MOTOR_PIN1, 50);
      analogWrite (L_MOTOR_PIN2, 0);
    } else {
      analogWrite (R_MOTOR_PIN1, 0);
      analogWrite (R_MOTOR_PIN2, 0);
      analogWrite (L_MOTOR_PIN1, 0);
      analogWrite (L_MOTOR_PIN2, 0);
    }

      

}
