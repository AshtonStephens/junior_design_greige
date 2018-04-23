/* 
 *
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "smart_bot.h"
#include "states.h"

#define STATE_STACK_SIZE  5
class state_machine 
{

private:
    int     stack_id;
    state   stack  [STATE_STACK_SIZE];
    state   thread [THREAD_SIZE];
    bool    state_change;
public:
    state_machine () : stack_id() {}
    
    template <int N>
    void setup   (state_initializer (&si)[N], int routine)  
    { 
      stack_id = 0;
      initialize_thread(si,routine,thread);
      stack[stack_id] = thread[1];
    }

    bool complete () // TODO: MAKE THIS ACTUALLY DO SOMETHING
    {return false;}

    void execute ()
    {   
        int move_ = stack[stack_id].action(state_change,stack[stack_id].data);
        state_change = false;
        if (move_) {
            state_change = true;
            // if the output was not 0
            if (move_ < 0) {
                stack_pop();
            } else {
                stack[stack_id] = thread[move_];
            }
        }
    }

    /* --------------------------------------------------------------- 
     * 
     * --------------------------------------------------------------- */
    
    void stack_pop () {
        if (stack_id == 0) {
            //Serial.println("RUNTIME ERROR - TRYING TO REMOVE LAST STACK STATE"); 
        }
    }

    void stack_push(int id) {
        if (stack_id == STATE_STACK_SIZE) {
            // Serial.println("RUNTIME ERROR - TRYING TO ADD TOO MANY STATES TO STACK"); 
        } else {
            stack[++stack_id] = thread[id];
        }
    }
        
};

#endif
