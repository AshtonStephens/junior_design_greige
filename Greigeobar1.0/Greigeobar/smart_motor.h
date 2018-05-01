/* 
 * smart_motor.h
 * 
 * purpose: to allow for complex / asynchronous movement from
 *          the motors without need for complex maintenence
 *
 * by   :   Ashton Stephens
 * date :   4/22/18
 *
 */

#ifndef SMART_MOTOR_H
#define SMART_MOTOR_H

#define MAX_MOTOR_SPEED 255
#define MIN_MOTOR_SPEED -255

#define CURRENT_SPEED   500


enum motor_transition
{
    LINEAR_SLOPE     = 0,
    LINEAR_DURATION  = 1,
    EXPONENTIAL      = 2
};

class smart_motor {
private:

    int pin1;
    int pin2;
    
    motor_transition transition;
    float motor_ratio;
    int current_speed;
    int final_speed;
    float coeff;

    long long last_update;
    
public:

    // declares and make a smart_motor - Sets up pins
    smart_motor (int pin1, int pin2, float motor_ratio):
        pin1(pin1), pin2(pin2), motor_ratio(motor_ratio), transition(LINEAR_SLOPE),
        current_speed(0), final_speed(0), coeff(0),
        last_update(0) 
    {   
        pinMode (pin1,OUTPUT);
        pinMode (pin2,OUTPUT);
        motor_go(0);
    } 

    int speed_ () {
        return current_speed; 
    }

    bool decelerating () {return (coeff < 0) && (current_speed != final_speed);}

    void off ()
    {
        this->set_transition (CURRENT_SPEED, 0, 1000, LINEAR_SLOPE);
    }

    // returns true if the motor has achieved the final speed
    bool at_final_speed () 
    {
        return (final_speed == current_speed);
    }
    
    void maintain ()
    {
        /*
        Serial.println(__func__);
        Serial.print("current_speed: ");
        Serial.println(current_speed);
        Serial.print("final_speed: ");
        Serial.println(final_speed);
        Serial.print("coeff: ");
        Serial.println(coeff);
        Serial.println(); */
        
        int ds;
        int new_speed;
        long long current_update;
        
        if (at_final_speed()) return; // leave if there's nothing to calculate
        
        current_update = millis();
        
        switch (transition) {
            case LINEAR_SLOPE:
            case LINEAR_DURATION:
            ds = coeff * (current_update - last_update);
            break;

            case EXPONENTIAL:
            ds = coeff * (current_speed - final_speed) 
                       * (current_update- last_update); 
            break;
        }
        
        new_speed = current_speed + ds;
        
        if (ds == 0) { 
            return;
        } else if (ds > 0 && new_speed > final_speed) {
            new_speed = final_speed;
        } else if (ds < 0 && new_speed < final_speed) {
            new_speed = final_speed;
        }
        
        current_speed = motor_go(new_speed);
        last_update = current_update;
    }

    void debug () 
    {
      /*
        DBG;
        _VAR(current_speed);
        _VAR(final_speed);
        _VAR(coeff);
    */
    }
    
    void set_transition (int current_speed_, int final_speed_, 
            int constant, motor_transition transition_)
    {
        if (current_speed_ != CURRENT_SPEED) // checks against flag
            this-> current_speed = force_into_range(current_speed_); 
        this-> final_speed = force_into_range (final_speed_);
        this-> transition    = transition_;
        
        switch (transition) { 
            case LINEAR_SLOPE: 
            // turns coeff into slope s.t. the input constant defines
            // the change in motor value per second
            (*this).coeff  = ((float)constant) / 1000;

            // make the slope the right sign
            if ( ((this-> coeff) < 0 && (final_speed_ - current_speed_) > 0 )||
                 ((this-> coeff) > 0 && (final_speed_ - current_speed_) < 0 ))
                 this->coeff = -this-> coeff; 
            
            break;

            case LINEAR_DURATION:
            // turns coeff into the slope that will make the transition
            // happen in the input constant number of milliseconds
            (*this).coeff  = ((float)((*this).final_speed - (*this).current_speed))/
                        constant;
            break;

            case EXPONENTIAL:
            // Doesn't really translate
            (*this).coeff  = ((float)constant) / 1000; 
            break;
        }
    }

private:
    // applies the current speed to the motor.
    // Takes in a negative number for backwards
    // and a positive number for forwards
    int motor_go (int speed) 
    {
        if (speed > 0) {
            analogWrite (pin1, (int)(motor_ratio * speed));

            VAR_(motor_ratio);
            VAR_(speed);
            VAR_((int)(motor_ratio * speed));
            analogWrite (pin2, 0);
            return speed;
        } else {
            speed = -speed;   
            analogWrite (pin1, 0);
            analogWrite (pin2, (int)(motor_ratio * speed));
            Serial.print(motor_ratio * speed);
            return -speed;
        }
    }

    // returns a speed that is forced into the range
    // of valid speeds
    int force_into_range (int speed) {
        if (speed > MAX_MOTOR_SPEED) {
            return MAX_MOTOR_SPEED;
        } else if (speed < MIN_MOTOR_SPEED) {
            return MIN_MOTOR_SPEED;
        } else {
            return speed;
        }
    }
};

#endif

