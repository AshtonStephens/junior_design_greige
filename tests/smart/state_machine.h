/* 
 *
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "smart_bot.h"

#define STATE_STACK_SIZE  5
#define STATE_EDGES_SIZE  3
#define NUM_STATE_THREADS 8
#define THREAD_SIZE       10

struct state {
    state () : action(NULL), data(NULL) {};
    state (int (*v)(void*), void*) : action(v), data(NULL) {};

    int (*action)(void*);
    void *data;
};

class state_machine 
{

private:
    int     stack_id;
    state   stack  [STATE_STACK_SIZE];
    state   thread [THREAD_SIZE];

public:
    template <int N>
    state_machine(state threads[]);
    
    void setup   (int routine)
    {

    }
    
    void execute ()
    { 
        int move = stack[stack_id].b.action(stack[stack_id].b.data);
        if (move) {
            // if the output was not 0
            if (move < 0) {
                stack_pop();
            } else {
                stack[stack_id] = thread[move];
            }
        }

    }

    /* --------------------------------------------------------------- 
     * 
     * --------------------------------------------------------------- */
    
    stack_pop () {
        if (stack_id == 0) {
            Serial.println("ERROR - TRYING TO REMOVE LAST STACK STATE"); 
        }
    }

    stack_push(int id) {
        if (stack_id == STATE_STACK_SIZE) {
            Serial.println("ERROR - TRYING TO ADD TOO MANY STATES TO STACK"); 
        }
    }
        
}

#endif
