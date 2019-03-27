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

class motor 
{
  private:
      int pin_enable;
      int pin_1;
      int pin_2;
  public:

	// TODO: INITIALIZE PINZ
      motor (int pin_enable, int pin1, int pin2) :
      pin_enable(pin_enable), pin1(pin1), pin2(pin2) {}
          
      void on () {digitalWrite(pin_enable, HIGH);}
      void off() {digitalWrite(pin_enable, LOW);}
      
      void forward (int spd) {
        on();
        analogWrite (pin_1, spd);
        analogWrite (pin_2, 0);
      }
      
      void backward (int spd) {
        on();
        analogWrite (pin_1, spd);
        analogWrite (pin_2, 0);
      }
};

class msystem
{
  public:
  
    class motorR;
    class motorL;
  
  msystem(int pin_enable_R, int pin1_R, int pin2_R,
          int pin_enable_L, int pin1_L, int pin2_L):
          motorR(pin_enable_R, pin1_R, pin2_R),
          motorL(pin_enable_L, pin1_L, pin2_L) {}
          
  forward(int spd) {
    motorR.forward(spd);
    motorL.forward(spd);    
  }
  
  backward(int spd) {
    motorR.backward(spd);
    motorL.backward(spd);    
  }

  // TURNING RIGHT
  right_rpivot (int spd) {
    motorR.off();   
    motorL.forward(spd); 
  }
   
  right_mpivot (int spd) {
    motorR.backward(spd);
    motorL.forward (spd);    
  }
  
  right_lpivot (int spd) {
    motorR.backward(spd);
    motorL.off();   
  }

  // TURNING LEFT 
  left_rpivot (int spd) {
    motorR.off();
    motorL.backward(spd);    
  }
   
  left_mpivot (int spd) {
    motorR.forward (spd);
    motorL.backward(spd);    
  }
  
  left_lpivot (int spd) {
    motorR.forward(spd);
    motorL.off();    
  }
  
  off() {
    motorR.off();  
  }
  
};


#endif
