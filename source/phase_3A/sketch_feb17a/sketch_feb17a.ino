int LED_ON    = 255;
int LED_OFF   = 0;
int RED_PIN   = 12;
int BLUE_PIN  = 10;

int BLUE_BUTTON = 19;
int RED_BUTTON  = 18;

#define SENSOR_PIN A1 // Blue LED brightness

void setup() 
{
    // ----- SETUP SERIAL COMM ----------- //
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.print("printing ready\n");

    // ----- LED Output Pins ------------- //

    pinMode(RED_PIN,  OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);

    pinMode(RED_BUTTON,  INPUT_PULLUP); 
    pinMode(BLUE_BUTTON, INPUT_PULLUP);
    pinMode(SENSOR_PIN,  INPUT_PULLUP);
}

void loop() 
{
    int sensor_reading = analogRead(SENSOR_PIN);
    
    Serial.write("Sensor reading: [ "); 
    Serial.write(sensor_reading); 
    Serial.write(" ]\n"); 
    
    if (digitalRead(BLUE_BUTTON)) {
      analogWrite(BLUE_PIN, LED_ON);     
    } else {
      analogWrite(BLUE_PIN, LED_OFF);
    }
    
    if (digitalRead(RED_BUTTON)) {
      analogWrite(RED_PIN, LED_ON);     
    } else {
      analogWrite(RED_PIN, LED_OFF);
    }
  
}

