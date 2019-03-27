                                                                                                                                                                                                                                                                                                                                                                                                                              #include "color.h"
#include "csensor.h"

#define CALIBRATION_PIN 18 
#define BLUE_LED_PIN 5
#define  RED_LED_PIN 6
#define   SENSOR_PIN_L A5
#define   SENSOR_PIN_R A6

#define BLUE_LIGHT_BRIGHTNESS 255
#define RED_LIGHT_BRIGHTNESS  255
#define STABILIZATION_TIME 50

const float redBsl[NPARAMS+1] ={-3.979810, 7.405145, 0.902109, -2.237968, 2.449657};
const float bluBsl[NPARAMS+1] ={-4.399028, -1.277574, 0.466518, 9.552000, 3.499715};


const float redBsr[NPARAMS+1] ={-4.298925, 7.001786, 0.671242, -2.276786, 2.878179};
const float bluBsr[NPARAMS+1] ={-4.356282, -1.186936, 0.288712, 9.645810, 3.723741};

csensor sensor(
    SENSOR_PIN_L, SENSOR_PIN_R,
    RED_LED_PIN, BLUE_LED_PIN, STABILIZATION_TIME,
    redBsl,bluBsl,redBsr,bluBsr);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)  {}
  Serial.print("printing ready\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  // sensor_l.sense();
  sensor.sense();
}
