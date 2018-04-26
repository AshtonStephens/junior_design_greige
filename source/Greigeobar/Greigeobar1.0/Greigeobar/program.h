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
  

    {THREAD_0,  1, {flashled, &c1b1_initflash}},
    {THREAD_0,  5, {talk,     &c1b1_start_talk}},
    {THREAD_0, 10, {flashled, &c1b1_startflash}},
    {THREAD_0, 15, {move_collision, &c1b1_starting_run}},
    {THREAD_0, 20, {move_time, &c1b1_go_back_a_bit_bot1}},
    {THREAD_0, 23, {move_time, &c1b1_turn_a_bit_bot1}},
    {THREAD_0, 25, {tracktrack, &c1b1_track_blue}},
    {THREAD_0, 30, {move_time, &c1b1_turn_after_blue}},
    {THREAD_0, 35, {tracktrack, &c1b1_track_yellow}},
    {THREAD_0, 40, {move_time, &c1b1_turn_after_yellow}},
    {THREAD_0, 45, {tracktrack, &c1b1_track_red}},
    {THREAD_0, 50, {tracktrack, &c1b1_turn_after_red}},
    {THREAD_0, 55, {hardware_stop, NULL}}, //// debug end
    
    // STATE 1.
      // FLASH BLUE AND READ LEDS 3 TIMES
    // STATE 2.
      // SIGNAL TO BOT 2 WITH 500 MS MESSAGE
    // STATE 3.
    //    ILLUMINATE START LED
    //    GO FORWARD UNTIL A COLLISION
    //    
/*
flashled_data   c1b1_startflash         = {RED_LED_FLASH|BLUE_LED_FLASH, 3, 200, 800, 0,0, 5}; // state 1
talk_data       c1b1_start_talk         = {500,  0  ,10} // state 5
flashled_data   c1b1_bot1_startflash    = {GREEN_LED_FLASH, 1, 1000, 0, 0, 0, 15}; // state 10
move_data       c1b1_starting_run       = {100, 0, 100, 100, 0, 0, 20}; // state 15
move_data       c1b1_go_back_a_bit_bot1 = {100, 0, 100, 100, 0, 0, 23}; // state 20
move_data       c1b1_turn_a_bit_bot1    = {100, 0, 100, 100, 0, 0, 25}; // state 23
tracktrack_data c1b1_track_blue         = {BLACK, BLUE,  YELLOW, RIGHT_TRACK, 100,75, 25, 750, 30}; // state 25
move_data       c1b1_turn_after_blue    = {100, 0, 100, 100, 0, 0, 35}; // state 30
tracktrack_data c1b1_track_yellow       = {BLACK, YELLOW,  RED, RIGHT_TRACK, 100,75, 25, 750, 40}; // state 35
move_data       c1b1_turn_after_yellow  = {100, 0, 100, 100, 0, 0, 45}; // state 40 
tracktrack_data c1b1_track_red          = {BLACK, RED,  NONE, RIGHT_TRACK, 100,75, 25, 750, 50}; // state 45
move_data       c1b1_turn_after_red     = {100, 0, 100, 100, 0, 0, 55}; // state 50 
     */
   {THREAD_1,1,{hardware_stop,NULL}},
    // STOPPING STATE
    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, 69,{hardware_stop,NULL}}
     
};


#endif
