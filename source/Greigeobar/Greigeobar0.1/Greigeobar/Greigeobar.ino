
#include "csensor.h"
#include "motor.h"
#include "state.h"

#define CALIBRATION_PIN 18 
#define BLUE_LED_PIN 5
#define  RED_LED_PIN 4
#define   SENSOR_PIN A5

#define BLUE_LIGHT_BRIGHTNESS 200
#define RED_LIGHT_BRIGHTNESS  255
#define STABILIZATION_TIME 50

csensor sensor(
    SENSOR_PIN,
    RED_LED_PIN,  RED_LIGHT_BRIGHTNESS,
    BLUE_LED_PIN, BLUE_LIGHT_BRIGHTNESS,
    STABILIZATION_TIME,
    {-1.224205, 3.316791, 0.632873, -1.593193, 1.088288},
    {-1.327337, 0.200608, 0.206822, 1.879784, 1.554547}
    );
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial)  {}
  Serial.print("printing ready\n");
}

void loop() {
  // put your main code here, to run repeatedly:


}
