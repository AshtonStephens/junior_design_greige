
int MOTOR_L_IN1_PIN   = 2;
int MOTOR_L_IN2_PIN   = 3;
int MOTOR_L_ENA_PIN   = 22;
int MOTOR_R_IN1_PIN   = 4;
int MOTOR_R_IN2_PIN   = 5;
int MOTOR_R_ENA_PIN   = 23;
int ANALOG_TURN       = 155;

#define POT1_PIN A4 
#define POT2_PIN A3  
#define RUN_TEST_PIN 18 

void setup() {
  // put your setup code here, to run once:

  
    // ----- SETUP SERIAL COMM ----------- //
    Serial.begin(9600);
    while (!Serial)  {}
    Serial.print("printing ready\n");
  
    // ----- LED Output Pins ------------- //
    pinMode(MOTOR_L_IN1_PIN, OUTPUT);
    pinMode(MOTOR_L_IN2_PIN, OUTPUT);
    pinMode(MOTOR_L_ENA_PIN, OUTPUT);
    
    pinMode(MOTOR_R_IN1_PIN, OUTPUT);
    pinMode(MOTOR_R_IN2_PIN, OUTPUT);
    pinMode(MOTOR_R_ENA_PIN, OUTPUT);
  
    // ----- TED Potentiometer Control --- //
    pinMode(POT1_PIN, INPUT);
    pinMode(POT2_PIN, INPUT);  
    pinMode(RUN_TEST_PIN, INPUT_PULLUP); 
  
    attachInterrupt(digitalPinToInterrupt(RUN_TEST_PIN), run_test_turn, RISING);
    interrupts();
  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  turn_right_90();
  stop(); delay(1000);
  
  turn_left_90();
  stop(); delay(1000);
  
  turn_right_180();
  stop(); delay(1000);
  
  turn_left_180();
  stop(); delay(1000);

  while(1)
  {
    stop();
  }
  
}

void run_test_turn () 
{
  
  static unsigned long  LastPress = 0;
  static const unsigned long debounce_delay = 500;
  int pot1, pot2;
  attachInterrupt(digitalPinToInterrupt(RUN_TEST_PIN), nothing, RISING);
  interrupts();
   if (millis() - LastPress > debounce_delay) {
      LastPress = millis();
      // RUN TEST ----------------------------------
        pot1 = (((double)analogRead (POT1_PIN)/1023)*255);  // scale : 0-255
        pot2 = analogRead (POT2_PIN);                       // scale : 0-1023

        Serial.print("(pot1:");
        Serial.print(pot1);
        Serial.print("[speed])(pot2:");
        Serial.print(pot2);
        Serial.println("[time])--LAUNCH:");
          
        // Left wheel forward
        analogWrite(MOTOR_L_IN1_PIN, 0);
        analogWrite(MOTOR_L_IN2_PIN, pot1);
        digitalWrite(MOTOR_L_ENA_PIN, 1);

        // Right wheel backward
        analogWrite(MOTOR_R_IN1_PIN, 0);
        analogWrite(MOTOR_R_IN2_PIN, pot1);
        digitalWrite(MOTOR_R_ENA_PIN, 1);
                        
        delay (pot2);
        Serial.println("TEST CONCLUDED");
        stop();
        
      // RUN TEST ----------------------------------
   }
   attachInterrupt(digitalPinToInterrupt(RUN_TEST_PIN), run_test_turn, RISING);
  
}


void turn_right_90()
{
  int speed_ = 73;
  int delay_ = 782; 
  
  // Left wheel backward
  analogWrite(MOTOR_L_IN1_PIN, 0);
  analogWrite(MOTOR_L_IN2_PIN, speed_);
  digitalWrite(MOTOR_L_ENA_PIN, 1);

  // Right wheel backward
  analogWrite(MOTOR_R_IN1_PIN, 0);
  analogWrite(MOTOR_R_IN2_PIN, speed_);
  digitalWrite(MOTOR_R_ENA_PIN, 1);

  delay(delay_);
  
}

void turn_right_180()
{
  int speed_ = 165;
  int delay_ = 816; 
  
  analogWrite(MOTOR_L_IN1_PIN, 0);
  analogWrite(MOTOR_L_IN2_PIN, speed_);
  digitalWrite(MOTOR_L_ENA_PIN, 1);

  // Right wheel backward
  analogWrite(MOTOR_R_IN1_PIN, 0);
  analogWrite(MOTOR_R_IN2_PIN, speed_);
  digitalWrite(MOTOR_R_ENA_PIN, 1);

  delay(delay_);
  
}

void turn_left_90()
{
  int speed_ = 73;
  int delay_ = 782; 
  
  // Left wheel backward
  analogWrite(MOTOR_L_IN1_PIN, speed_);
  analogWrite(MOTOR_L_IN2_PIN, 0);
  digitalWrite(MOTOR_L_ENA_PIN, 1);

  // Right wheel backward
  analogWrite(MOTOR_R_IN1_PIN, speed_);
  analogWrite(MOTOR_R_IN2_PIN, 0);
  digitalWrite(MOTOR_R_ENA_PIN, 1);
  
  delay(delay_);
}

void turn_left_180()
{
  int speed_ = 165;
  int delay_ = 816; 
  
  // Left wheel backward
  analogWrite(MOTOR_L_IN1_PIN, speed_);
  analogWrite(MOTOR_L_IN2_PIN, 0);
  digitalWrite(MOTOR_L_ENA_PIN, 1);

  // Right wheel backward
  analogWrite(MOTOR_R_IN1_PIN, speed_);
  analogWrite(MOTOR_R_IN2_PIN, 0);
  digitalWrite(MOTOR_R_ENA_PIN, 1);

  delay(delay_);
}

// ----------------------------------- //
// --- MEMBER FUNCTIONS -------------- //
// ----------------------------------- //

void forward(int spd)
{
  // Both wheels forward
  analogWrite(MOTOR_L_IN1_PIN, spd);
  analogWrite(MOTOR_L_IN2_PIN, 0);
  digitalWrite(MOTOR_L_ENA_PIN, 1); // L goes bw
  
  analogWrite(MOTOR_R_IN1_PIN, spd);
  analogWrite(MOTOR_R_IN2_PIN, 0);
  digitalWrite(MOTOR_R_ENA_PIN, 1); // R goes fwd

}

void backward(int spd)
{
  // Both wheels backward
  analogWrite(MOTOR_L_IN1_PIN, 0);
  analogWrite(MOTOR_L_IN2_PIN, spd);
  digitalWrite(MOTOR_L_ENA_PIN, 1);
  
  analogWrite(MOTOR_R_IN1_PIN, 0);
  analogWrite(MOTOR_R_IN2_PIN, spd);
  digitalWrite(MOTOR_R_ENA_PIN, 1);
}

void turn_left(int dgrs)
{
  // Left wheel forward
  analogWrite(MOTOR_L_IN1_PIN, ANALOG_TURN);
  analogWrite(MOTOR_L_IN2_PIN, 0);
  digitalWrite(MOTOR_L_ENA_PIN, 1);
  // Right wheel backward
  analogWrite(MOTOR_R_IN1_PIN, 0);
  analogWrite(MOTOR_R_IN2_PIN, ANALOG_TURN);
  digitalWrite(MOTOR_R_ENA_PIN, 1);

  delay(dgrs*3);
}

void turn_right(int dgrs)
{
  // Left wheel backward
  analogWrite(MOTOR_L_IN1_PIN, 0);
  analogWrite(MOTOR_L_IN2_PIN, ANALOG_TURN);
  digitalWrite(MOTOR_L_ENA_PIN, 1);
  // Right wheel forward
  analogWrite(MOTOR_R_IN1_PIN, ANALOG_TURN);
  analogWrite(MOTOR_R_IN2_PIN, 0);
  digitalWrite(MOTOR_R_ENA_PIN, 1);

  delay(dgrs*3);
}

void stop()
{
  digitalWrite(MOTOR_L_IN1_PIN, 0);
  digitalWrite(MOTOR_L_IN2_PIN, 0);
  digitalWrite(MOTOR_L_ENA_PIN, 0);

  digitalWrite(MOTOR_R_IN1_PIN, 0);
  digitalWrite(MOTOR_R_IN2_PIN, 0);
  digitalWrite(MOTOR_R_ENA_PIN, 0);
}

void test_print() 
{
  int i = random(10);
  if (i = 0) {
    Serial.println("Fuck off Aji you piece of human filth");
  }
}

void nothing () {
  
}




