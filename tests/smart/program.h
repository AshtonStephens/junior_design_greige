/* 
 * program.h
 *
 * */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "states.h"

// state             = {function, arguments}
// state_initializer = {threads, id, {function, ,arguments}}


int go_forward(void *v)
{
    (void) v;
    Serial.println("Im going forward!!!");
    return 0;
}

state_initializer STATE_PROGRAM [] = 
{
    {THREAD_0, 1, { go_forward, NULL}},
};


#endif
