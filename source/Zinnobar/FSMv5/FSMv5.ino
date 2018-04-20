//http://playground.arduino.cc/uploads/Code/Button.zip
#include <Arduino.h>

class SmartLED
{   
  int ledPin;      // the number of the LED pin
  long OnTime; 
  byte ledState;                   // ledState used to set the LED
  byte on_off;
  long currentMillis;
  long previousMillis;
 
  public: SmartLED(int pin){
    ledPin = pin;
    on_off = HIGH;
    previousMillis = 0;  
    ledState = HIGH;
    pinMode(ledPin, OUTPUT);  
  }
  void setLedState(int new_State){ledState = new_State;}
  void togOff(){ ledState = LOW;digitalWrite(ledPin, ledState);}
  void togOn(){ ledState = HIGH;digitalWrite(ledPin, ledState);}
  void resetLed(){togOff(); on_off = LOW;}
  
  void updateLed(long current_OnTime){
      if (current_OnTime != 0) {on_off = HIGH; OnTime = current_OnTime;}
      unsigned long currentMillis1 = millis();
      if(currentMillis - previousMillis >= OnTime){
        if(ledState == HIGH){
          togOff();
          previousMillis = currentMillis;  // Remember the time
        }
        else{
          togOn();
          previousMillis = currentMillis;   // Remember the time
        }
      }
  }

  
};

class driveSystem{
  int motorMode;     //0 for stopped, 1 for forward, 2 for backwards, 3 for left, 4 for right
  long motorModeTime; // duration of movement directoin
  int driveSpeed; // target speed
  int rampSpeed; // current motor speed
  
  int motor1pin1; // these values will be anywhere from 0 to 255 for Arduino PWM
  int motor1pin2; // they connect to the H-bridge
  int motor2pin1;
  int motor2pin2;
 
  long driveMillisC; // current drive time
  long driveMillisP; // previous drive time
  
  public: driveSystem(int motor1_Pin1, int motor1_Pin2,int motor2_Pin1, int motor2_Pin2){
    motorMode = 0;
    driveSpeed = 0;
    driveMillisP = 0;
    rampSpeed = 0;
    motor1pin1 = motor1_Pin1; // Arduino pins connecting to the H-bridge IC
    motor1pin2 = motor1_Pin2;
    motor2pin1 = motor2_Pin1;
    motor2pin2 = motor2_Pin2;
  }
  void ramp(){
    if(rampSpeed < driveSpeed && (driveMillisC-driveMillisP >= 10)){ // wait 10ms before updating speed
      rampSpeed = rampSpeed + (driveSpeed/10);                       // updates in 0.1 seconds
      driveMillisP = driveMillisC;
    }
    else if(rampSpeed >= driveSpeed){ rampSpeed = driveSpeed;}
  }
  void setDriveTime(long time_to_drive,int new_speed, int motor_mode){
    motorMode = motor_mode;
    motorModeTime = time_to_drive;
    driveMillisP = millis();
    driveSpeed = new_speed;
    rampSpeed = 0;
  }
  
  void updateDrive(){                                               // change driving direction and/or speed
    driveMillisC = millis();
    if(motorMode == 1){ 
      if(rampSpeed < driveSpeed){ramp();}
      if((driveMillisC - driveMillisP) >= motorModeTime){
        motorMode = 0;
        driveSpeed = 0;
        rampSpeed = 0;
      }
     digitalWrite(motor1pin2,LOW);
     digitalWrite(motor2pin2,LOW);
     analogWrite(motor1pin1,rampSpeed);
     analogWrite(motor2pin1,rampSpeed);
    }
    else if(motorMode == 2){
      if(rampSpeed < driveSpeed){ramp();}
      if((driveMillisC - driveMillisP) >= motorModeTime){
        motorMode = 0;
        driveSpeed = 0;
        rampSpeed = 0;
      }
     digitalWrite(motor1pin1,LOW);
     digitalWrite(motor2pin1,LOW);
     analogWrite(motor1pin2,rampSpeed);
     analogWrite(motor2pin2,rampSpeed);
    }
    else if(motorMode == 3){ //LEFT Turn
      if(rampSpeed < driveSpeed){ramp();}
      if((driveMillisC - driveMillisP) >= motorModeTime){
        motorMode = 0;
        driveSpeed = 0;
        rampSpeed = 0;
      }
     digitalWrite(motor1pin1,LOW);
     digitalWrite(motor2pin2,LOW);
     analogWrite(motor1pin2,rampSpeed);
     analogWrite(motor2pin1,rampSpeed);
    }
    else if(motorMode == 4){ //RIGHT Turn
      if(rampSpeed < driveSpeed){ramp();}
      if((driveMillisC - driveMillisP) >= motorModeTime){
        motorMode = 0;
        driveSpeed = 0;
        rampSpeed = 0;
      }
     digitalWrite(motor1pin2,LOW);
     digitalWrite(motor2pin1,LOW);
     analogWrite(motor1pin1,rampSpeed);
     analogWrite(motor2pin2,rampSpeed);
    }
    else if(motorMode == 0){
      motorMode = 0;
      driveSpeed = 0;
      rampSpeed = 0;
      analogWrite(motor1pin1,LOW);
      analogWrite(motor1pin2,LOW);
      analogWrite(motor2pin1,LOW);
      analogWrite(motor2pin2,LOW);
    }
  }
 
  int getMotorMode(){return motorMode;}
  void setMotorMode(int low){motorMode = low;}
  long getDriveTime(){return motorModeTime;}
  
};
driveSystem d1(0,1,2,3);
SmartLED led10(10);
SmartLED led11(11);
SmartLED led12(12);

int state = 0;
int subStateCount = 0; //This is for sequential execution of challenges.
byte Flag = HIGH;
long em = 0; // time when starting case 3 (fixed)
long cm = 0; // current time in case 3 (constantly updated)

void setup(){
  pinMode(0, OUTPUT); 
  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(7, OUTPUT); 
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  attachInterrupt(digitalPinToInterrupt(2), testWheels1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), stopWheels, FALLING);
  state = 0;
  subStateCount = 0;
  }
 #define SPEED_ 50
void loop(){
    switch (state){
      //__________________________________________________________________
      case 0: //ON STATE
      led11.updateLed(200);
      updateAllLeds();
      d1.updateDrive();
      if(subStateCount == 0){d1.setDriveTime(1000,SPEED_,3); state = 3;}  //drive forward 5 sec
      if(subStateCount == 1){d1.setDriveTime(1000,SPEED_,2); state = 3;}  //turn left 3 sec
      if(subStateCount == 2){d1.setDriveTime(1000,SPEED_,4); state = 3;}  //turn right 3 sec
      if(subStateCount == 3){d1.setDriveTime(1000,SPEED_,1); state = 3;}  //turn right 3 sec
      break;
      //___________________________________________________________________
      case 1: break; //OFF STATE (NO LEDS)
      //___________________________________________________________________
      case 2: //RUN STATE
      led11.updateLed(200);
      updateAllLeds();
      break;
      //__________________________________________________________________
      case 3: //FORWARD/BACKWARD
      if(Flag == HIGH){
        em = millis();
        Flag = LOW;
      }
      cm = millis();
      if(cm-em < 70){break;}
      d1.updateDrive();
      led12.updateLed(200);
      if(d1.getMotorMode() == 0){
        state = 0;
        stateReset();
        ++subStateCount;
        Flag = HIGH;
      }
      break;
      //__________________________________________________________________
      case 4: break;//LEFT TURN
      
      //__________________________________________________________________
      case 5: break;//RIGHT TURN
      
      //__________________________________________________________________
      
    }
}

void testWheels1(){
  subStateCount = 0;
}
void stopWheels(){
  d1.setMotorMode(0);
}

void stateReset(){
  led10.resetLed();
  led11.resetLed();
  led12.resetLed();
}
void updateAllLeds(){
  led10.updateLed(0);
  led11.updateLed(0);
  led12.updateLed(0);
}


