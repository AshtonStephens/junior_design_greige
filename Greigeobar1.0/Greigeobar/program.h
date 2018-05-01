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

    {THREAD_1, 1,{flashled,&c1b1_initflash}},           // state 1 -> 4
    {THREAD_1, 4,{talk,&c1b1_start_talk}},              // state 4 -> 5
    {THREAD_1, 5,{flashled,&c1b1_startflash}},          // state 5 -> 6
    {THREAD_1, 6,{move_if,&c1b1_initial_collision1}},   // state 6 -> 8
    {THREAD_1, 8,{move_time,&c1b1_initial_collision2}}, // state 8 -> 10
    {THREAD_1,10,{move_if,&c1b1_initial_collision3}},   // state 10 -> 13
    {THREAD_1,13,{tracktrack,&c1b1_track_blue}},        // state 13 -> 14
    {THREAD_1,14,{move_time,&c1b1_forward_smidge1}},    // state 14 -> 15
    {THREAD_1,15,{move_time,&c1b1_right_90}},           // state 15 -> 20
    {THREAD_1,20,{tracktrack,&c1b1_track_yellow}},      // state 20 -> 25
    {THREAD_1,25,{move_time,&c1b1_left_90}},            // state 25 -> 27
    {THREAD_1,27,{move_time,&c1b1_forward_jolt}},       // state 27 -> 30 
    {THREAD_1,30,{tracktrack,&c1b1_track_red}},         // state 30 -> 35
    {THREAD_1,35,{move_time,&c1b1_stop_hall_jolt1}},    // state 35 -> 36
    {THREAD_1,36,{move_time,&c1b1_turn_tcc_jolt}},      // state 36 -> 38
    {THREAD_1,38,{talk,&c1b1_start_talk_tcc}},          // state 38 -> 45 (200 ms?)
    {THREAD_1,45,{move_time,&c1b1_turn_tcc_jolt2}},     // state 45 -> 50 (69)


    {THREAD_6,1,{listen, &listen_test}},
    {THREAD_6,6,{flashled, &testflasjh}},
    
    
    /*
    {THREAD_1, 1,  {tracktrack, &c1b1_track_red}},
    {THREAD_1, 15, {move_time,  &c1b1_right_90}},
    {THREAD_1, 20, {tracktrack, &c1b1_track_yellow}},
    {THREAD_1, 25, {move_time, &c1b1_left_90}},
    {THREAD_1, 30, {tracktrack, &c1b1_track_blue}},
    {THREAD_1, HALL_INTERRUPT, {tracktrack, &c1b1_run_person_over_part1}},
    {THREAD_1, 90, {talk, &c1b1_run_person_over_part2}},
    */
    
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
