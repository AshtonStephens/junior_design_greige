
#include "regression.h"
#include "color.h"
#include "csensor.h"


static const int MOTOR1_PIN1   = 8;  // 
static const int MOTOR1_PIN2   = 9;  //
static const int MOTOR1_ENABLE = 32; //
                                  
static const int MOTOR2_PIN1   = 7;  //
static const int MOTOR2_PIN2   = 6;  //
static const int MOTOR2_ENABLE    = 30; //
                                  
static const int CSENSOR_LED_RED  = 5; //
static const int CSENSOR_LED_BLUE = 4; //

// pin definitions

#define BLUE_LED_PIN 5
#define  RED_LED_PIN 4
#define   SENSOR_PIN A5

#define BLUE_LIGHT_BRIGHTNESS 200
#define RED_LIGHT_BRIGHTNESS  255
#define STABILIZATION_TIME 50

void setup() {
  // put your setup code here, to run once:
  
  // Setting up serial printing
  Serial.begin(115200);
  while (!Serial)  {}
  Serial.print("printing ready\n");
}

void loop() {
  calibrate();
  // put your main code here, to run repeatedly:
    csensor sensor(
        SENSOR_PIN,
        RED_LED_PIN,  RED_LIGHT_BRIGHTNESS,
        BLUE_LED_PIN, BLUE_LIGHT_BRIGHTNESS,
        STABILIZATION_TIME);
        
    while (true) {
      sensor.sense();
    }
}

void calibrate() {
    Serial.println("calibrating...");
    static int   Y[LOG2_BUCKETS][N_REG_MEASUREMENTS];
    static float X[N_REG_MEASUREMENTS][N_REG_PARAMS+1];
    static float B[LOG2_BUCKETS][N_REG_PARAMS+1];

   float temp;
   int counter = 0;
   
   split(c,Y,X);
    
    for (int j = 0; j < LOG2_BUCKETS; ++j) {
      for (int i = 0; i < N_REG_PARAMS+1; ++i) {
        B[j][i] = 0.0;
      }
    }
    
    do {
      temp = Gradient_Descent_Error(Y[0],X,B[0]);
      Serial.print("calib [");
      Serial.print(counter++);
      Serial.print("](");
      Serial.print(temp);
      Serial.print(")(");
      temp = Gradient_Descent_Error(Y[1],X,B[1]);
      Serial.print(temp);
      Serial.println(")");
    } while (counter < 100);

    for (int i = 0; i < N_REG_PARAMS+1; ++i) {
      for (int j = 0; j < LOG2_BUCKETS; ++j) {  
        Serial.print(B[j][i]);
        Serial.print("|");
      }
      Serial.print('\n');
    }

    
}




















