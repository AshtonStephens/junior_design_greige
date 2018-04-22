//
// motor.h
//
// Purpose: To define the motor system for the autonomous bot
//
// Date: 3-3-18 
// By:  Ashton Stephens and Joseph Mang
//

#ifndef MOTOR_H
#define MOTOR_H

#define CURRENT_SPEED 1000

class smart_motor
{
 private:
  int pin1;
  int pin2;
  int current_speed;
  int final_speed;
  int coeff;
  long long last_update;
public:
  smart_motor (int pin1, int pin2) :
              pin1(pin1), pin2(pin2),
              coeff(1), final_speed(0),
              current_speed(0), last_update(0) {}

  // TODO: add diff function options
  set_transition (int start_speed, int end_speed,
                  int coefficient)
  {

    // validates slope
    if ((start_speed < end_speed && coeff < 0) ||
        (start_speed > end_speed && coeff > 0)) {
      coefficient = -coefficient; 
    }

    // allows for current speed to be used
    if(start_speed != CURRENT_SPEED)
      current_speed = start_speed;

    coeff = coefficient;
    final_speed = end_speed;
    maintain_motor();
  }

  maintain_motor () 
  { 
    long long update_time = millis();
    current_speed += ((float)coeff/1000) * (update_time - last_update);
    forward(current_speed);
    last_update = update_time;
  }
  
  void forward (int spd) {
        if (spd < 0) return backward(-spd);
        analogWrite (pin1, spd);
        analogWrite (pin2, 0);
      }
      
  void backward (int spd) {
    if (spd < 0) return forward(-spd);
    analogWrite (pin1, 0);
    analogWrite (pin2, spd);
  }
  
 
};

class motor 
{
  private:
      int pin1;
      int pin2;
 
  public:
	    // TODO: INITIALIZE PINZ
      motor (int pin1, int pin2) :
        pin1(pin1), pin2(pin2) {}
      
      void forward (int spd) {
        if (spd < 0) return backward(-spd);
        analogWrite (pin1, spd);
        analogWrite (pin2, 0);
      }
      
      void backward (int spd) {
        if (spd < 0) return forward(-spd);
        analogWrite (pin1, 0);
        analogWrite (pin2, spd);
      }

      void off() {forward(0);}
      
};

class msystem
{
  public:
  
    motor motorR;
    motor motorL;
  
  msystem(int pin1_R, int pin2_R,
          int pin1_L, int pin2_L):
          motorR(pin1_R, pin2_R),
          motorL(pin1_L, pin2_L) {}
          
  void forward(int spd) {
    motorR.forward(spd);
    motorL.forward(spd);    
  }
  
  void backward(int spd) {
    motorR.backward(spd);
    motorL.backward(spd);    
  }

  // TURNING RIGHT
  void right_rpivot (int spd) {
    motorR.off();   
    motorL.forward(spd); 
  }
   
  void right_mpivot (int spd) {
    motorR.backward(spd);
    motorL.forward (spd);    
  }
  
  void right_lpivot (int spd) {
    motorR.backward(spd);
    motorL.off();   
  }

  // TURNING LEFT 
  void left_rpivot (int spd) {
    motorR.off();
    motorL.backward(spd);    
  }
   
  void left_mpivot (int spd) {
    motorR.forward (spd);
    motorL.backward(spd);    
  }
  
  void left_lpivot (int spd) {
    motorR.forward(spd);
    motorL.off();    
  }
  
  void off() {
    motorR.off();  
  }
  
};


#endif
