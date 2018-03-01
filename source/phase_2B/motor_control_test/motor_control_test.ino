
int IN2_PIN = 12;
int IN1_PIN = 11;

int DIRECTION_PIN  = 18;

#define CLOCK  0
#define CCLOCK 1
int DIRECTION = CCLOCK;

#define POT2_PIN A3 //
#define POT1_PIN A4 //

void setup() 
{
    // ----- SETUP SERIAL COMM ----------- //
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.print("printing ready\n");

    // ----- LED Output Pins ------------- //
    pinMode(IN2_PIN, OUTPUT);
    pinMode(IN1_PIN, OUTPUT);

    // ----- SETUP DIAGNOSTIC INTERRUPT -- //
//    pinMode(DIRECTION_PIN, INPUT_PULLUP); 
//    attachInterrupt(digitalPinToInterrupt(DIRECTION_PIN), direction_switch, RISING);

    // ----- LED Potentiometer Control --- //
    pinMode(POT1_PIN, INPUT);
    pinMode(POT2_PIN, INPUT);  
   
    interrupts();
  
}

void loop() 
{
    
    int pot1 = (((double)analogRead (POT1_PIN)/1023)*255);
    int pot2 = (((double)analogRead (POT2_PIN)/1023)*255);
    analogWrite (IN1_PIN, pot1);
    analogWrite (IN2_PIN, pot2);
    
    Serial.print("[pot1: ");
    Serial.print(pot1);
    Serial.print(" ]\t[pot2: ");
    Serial.print(pot2);
    Serial.print(" ]\t(pot1:A0 -> IN1:11)(pot2:A1 -> IN2:12)\n");
    
    /*
    if (DIRECTION == CLOCK) {
      analogWrite (IN1_PIN, pot1);
      analogWrite (IN2_PIN, 0);
      Serial.print("pot1 : ");
      
      Serial.print(pot1);
      Serial.print("\ninput pin : ");
      
      
    } else {
      analogWrite (IN2_PIN, pot1);
      analogWrite (IN1_PIN, 0);
      Serial.print("direction switch to counter_clockwise\n")
    }*/
}



void direction_switch()
{
   static unsigned long  LastPress = 0;
   static const unsigned long debounce_delay = 50;
  
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      if( DIRECTION == CLOCK ){
        DIRECTION = CCLOCK;
        Serial.println("direction switch to counter_clockwise\n");
      } else {
        DIRECTION = CLOCK;
        Serial.println("direction switch to clockwise\n");
      }
   }
}


