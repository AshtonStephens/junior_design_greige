/* 
 * program.h
 *
 * */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "states.h"

// state             = {function, arguments}
// state_initializer = {threads, id, {function, ,arguments}}


struct 

int go_forward(bool first_run, void *v)
{
    long long timer;
    if (first_run) {
        
    }
    (void) v;
    Serial.println("Im going forward!!!");
    return 0;
}

int stop_fastly (bool first_run, void *v)
{
    (void) v;
    if (first_run){
        Serial.println("I'm stopping m'lady");
        Bot.lmotor.set_transition(CURRENT_SPEED,-30,100,LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED,-30,100,LINEAR_DURATION);
    }
    
    if (Bot.lmotor.at_final_speed() && Bot.rmotor.at_final_speed()) {
        Serial.println("I'm stopping m'lady");
        Bot.lmotor.set_transition(CURRENT_SPEED,0,100,LINEAR_DURATION);
        Bot.rmotor.set_transition(CURRENT_SPEED,0,100,LINEAR_DURATION);
    }
} 

state_initializer STATE_PROGRAM [] = 
{
    {THREAD_0, 1, { go_forward, NULL}},
    {THREAD_0, 2, { stop_fastly, NULL}}
};


#endif
