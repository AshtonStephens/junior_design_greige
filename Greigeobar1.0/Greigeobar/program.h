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
    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, HALL_INTERRUPT,{pop,NULL}},

    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, COLLISION_INTERRUPT,{pop,NULL}},

    //---
    {THREAD_0,  1, {none, NULL}},
    
    /*
    {THREAD_1,  1, {flashled,&c1b1_initflash}},
    {THREAD_1,  5, {talk,&c1b1_start_talk}},
    {THREAD_1, 10, {flashled,&c1b1_startflash}},
    
tracktrack_data c1b1_track_red          = {RED, RED,    YELLOW, LEFT_TRACK, 50,50,-50, 750, 15};  // state 10
move_data       c1b1_right_90           = {100, 350, 100, -100, 0, 20};                           // state 15 -> 20 
tracktrack_data c1b1_track_yellow       = {YELLOW, YELLOW, BLUE, LEFT_TRACK, 50,50,-50, 750, 25}; // state 20 -> 25
move_data       c1b1_left_90            = {100, 350, -100, 100, 0, 30};                           // state 25 -> 30 
tracktrack_data c1b1_track_blue         = {BLUE, BLUE, NONE, LEFT_TRACK, 50,50,-50, 750, 25}; // state 30 -> 35

    */
    {THREAD_1, 1,  {tracktrack, &c1b1_track_red}},
    {THREAD_1, 15, {move_time,  &c1b1_right_90}},
    {THREAD_1, 20, {tracktrack, &c1b1_track_yellow}},
    {THREAD_1, 25,  {move_time, &c1b1_left_90}},
    {THREAD_1, 30, {tracktrack, &c1b1_track_blue}},

    {THREAD_1, HALL_INTERRUPT, {tracktrack, &c1b1_run_person_over_part1}},
    {THREAD_1, 90, {talk, &c1b1_run_person_over_part2}},
    
    
    /*
    //{THREAD_1, 1,  {move_time,&c1b1_starting_run}},
    {THREAD_1, 1,  {move_collision, &c1b1_starting_run1}},
    {THREAD_1, 10, {move_time,      &c1b1_starting_run2}},
    {THREAD_1, 20, {move_time,      &c1b1_starting_run3}},
    {THREAD_1, 30, {move_if,   &c1b1_turn_to_yellow}},
    {THREAD_1, 35, {tracktrack,&c1b1_track_yellow}},
    {THREAD_1, 40, {move_time,&c1b1_turn_after_yellow}},
    {THREAD_1, 45, {tracktrack,&c1b1_track_red}},
    {THREAD_1, 50, {tracktrack,&c1b1_turn_after_red}},
    {THREAD_1, 55, {hardware_stop, NULL}},              //// debug end
    */


    {THREAD_2, 1, {none, NULL}},


    {THREAD_6, 1, {tracktrack,     &c1b1_track_red}},
    {THREAD_7, 1, {move_collision, &c1b1_starting_run3}},

   
    // STATE 1.
      // FLASH BLUE AND READ LEDS 3 TIMES
    // STATE 2.
      // SIGNAL TO BOT 2 WITH 500 MS MESSAGE
    // STATE 3.
    //    ILLUMINATE START LED
    //    GO FORWARD UNTIL A COLLISION
    //    

 
    // STOPPING STATE
    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, 69,{hardware_stop,NULL}}
};


#endif
