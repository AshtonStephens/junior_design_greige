/* 
 * program.h
 *
 * */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "states.h"
#include "program_functions.h"

// state             = {function, arguments}
// state_initializer = {threads, id, {function, ,arguments}}

state_initializer STATE_PROGRAM [] = 
{
    //---
    {THREAD_0,  1, {none, NULL}},
    // --- 
    {THREAD_1,  1, {flashled, &c1b1_initflash}},
    {THREAD_1,  5, {talk,     &c1b1_start_talk}},
    {THREAD_1, 10, {flashled, &c1b1_startflash}},
    {THREAD_1, 15, {move_collision, &c1b1_starting_run}},
    {THREAD_1, 20, {move_time, &c1b1_go_back_a_bit_bot1}},
    {THREAD_1, 23, {move_time, &c1b1_turn_a_bit_bot1}},
    {THREAD_1, 25, {tracktrack, &c1b1_track_blue}},
    {THREAD_1, 30, {move_time, &c1b1_turn_after_blue}},
    {THREAD_1, 35, {tracktrack, &c1b1_track_yellow}},
    {THREAD_1, 40, {move_time, &c1b1_turn_after_yellow}},
    {THREAD_1, 45, {tracktrack, &c1b1_track_red}},
    {THREAD_1, 50, {tracktrack, &c1b1_turn_after_red}},
    {THREAD_1, 55, {hardware_stop, NULL}}, //// debug end

    {THREAD_3, 1, {tracktrack, &testtrack}},
    
    {THREAD_2, 1, {none, NULL}},


   {THREAD_15, 1, {move_time, &c1b1_starting_run}},
   
    // STATE 1.
      // FLASH BLUE AND READ LEDS 3 TIMES
    // STATE 2.
      // SIGNAL TO BOT 2 WITH 500 MS MESSAGE
    // STATE 3.
    //    ILLUMINATE START LED
    //    GO FORWARD UNTIL A COLLISION
    //    

   {THREAD_1,1,{hardware_stop,NULL}},
    // STOPPING STATE
    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, 69,{none,NULL}}
     
};


#endif
