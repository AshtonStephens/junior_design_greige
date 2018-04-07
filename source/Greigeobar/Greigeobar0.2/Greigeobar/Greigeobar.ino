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

const float redBsl[NPARAMS+1] ={-1.349832, 4.145434, 0.030029, -0.406456, 0.027082};
const float bluBsl[NPARAMS+1] ={-1.900788, -0.087606, 0.029076, 3.875049, 0.035082};


const float redBsr[NPARAMS+1] ={-0.925573, 3.758495, 0.050483, -0.110437, 0.045874};
const float bluBsr[NPARAMS+1] ={-1.812837, 0.007340, 0.001000, 3.970372, 0.027169};

csensor sensor_l( 0,
    SENSOR_PIN_L,
    RED_LED_PIN,  RED_LIGHT_BRIGHTNESS,
    BLUE_LED_PIN, BLUE_LIGHT_BRIGHTNESS,
    STABILIZATION_TIME,redBsl,bluBsl);

csensor sensor_r( 1,
    SENSOR_PIN_R,
    RED_LED_PIN,  RED_LIGHT_BRIGHTNESS,
    BLUE_LED_PIN, BLUE_LIGHT_BRIGHTNESS,
    STABILIZATION_TIME,redBsr,bluBsr);
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)  {}
  Serial.print("printing ready\n");
}

void loop() {
  // put your main code here, to run repeatedly:
  // sensor_l.sense();
  sensor_r.sense();
}
