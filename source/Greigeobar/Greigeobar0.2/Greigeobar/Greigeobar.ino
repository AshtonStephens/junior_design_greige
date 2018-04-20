
#define BLUE_LED_PIN 5
#define  RED_LED_PIN 6
#define   SENSOR_PIN_L A5
#define   SENSOR_PIN_R A6


#define MOTOR_PE_R 23
#define MOTOR_P1_R 2
#define MOTOR_P2_R 3
#define MOTOR_PE_L 25
#define MOTOR_P1_L 4 
#define MOTOR_P2_L 5
            
#define STABILIZATION_TIME 50

#include "bot.h"

const float redBsl[NPARAMS+1] ={-1.349832, 4.145434, 0.030029, -0.406456, 0.027082};
const float bluBsl[NPARAMS+1] ={-1.900788, -0.087606, 0.029076, 3.875049, 0.035082};
const float redBsr[NPARAMS+1] = {-3.586847, 19.002927, 1.154657, -9.447639, 8.105032};
const float bluBsr[NPARAMS+1] = {-5.848949, -3.239512, -0.008792, 11.575479, 8.055332};

/*
csensor sensor(
    SENSOR_PIN_L, SENSOR_PIN_R,
    RED_LED_PIN, BLUE_LED_PIN, STABILIZATION_TIME,
    redBsl,bluBsl,redBsr,bluBsr);*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)  {}
  Serial.print("printing ready\n");

    pinMode(0, OUTPUT); 
  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
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
bot BOTTY(MOTOR_P1_R, MOTOR_P2_R,
          MOTOR_P1_L, MOTOR_P2_L,
    SENSOR_PIN_L, SENSOR_PIN_R,
    RED_LED_PIN, BLUE_LED_PIN, STABILIZATION_TIME,
    redBsl,bluBsl,redBsr,bluBsr);
  
    
void loop() {
    //BOTTY.sensors.sense();
    unsigned long timer;
    //color r_color = BOTTY.sensors.right();

    int spd = 50;
    BOTTY.motors.forward(100);
    delay(1000);
    Serial.print(__LINE__);
    BOTTY.motors.backward(100);
    delay(1000);   
    Serial.print(__LINE__);


}
