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

	// challenge 1 bot 1
    {THREAD_1, 1,{flashled,&c1b1_initflash}},           	// state 1 -> 4
    {THREAD_1, 4,{talk,&c1b1_start_talk}},              	// state 4 -> 5
    {THREAD_1, 5,{flashled,&c1b1_startflash}},          	// state 5 -> 6
    {THREAD_1, 6,{move_if,&c1b1_initial_collision1}},   	// state 6 -> 8
    {THREAD_1, 8,{move_time,&c1b1_initial_collision2}}, 	// state 8 -> 10
    {THREAD_1,10,{move_if,&c1b1_initial_collision3}},   	// state 10 -> 13 // 10
    {THREAD_1,13,{tracktrack,&c1b1_track_blue}},        	// state 13 -> 14
    {THREAD_1,14,{move_time,&c1b1_forward_smidge1}},    	// state 14 -> 15
    {THREAD_1,15,{move_time,&c1b1_right_90}},           	// state 15 -> 20
    {THREAD_1,20,{tracktrack,&c1b1_track_yellow}},      	// state 20 -> 25
    {THREAD_1,25,{move_time,&c1b1_left_90}},            	// state 25 -> 27
    {THREAD_1,27,{move_time,&c1b1_forward_jolt}},       	// state 27 -> 30 
    {THREAD_1,30,{tracktrack,&c1b1_track_red}},         	// state 30 -> 35
	{THREAD_1,35,{move_time,  &c1b1_stop_hall_jolt1}},      // state 35 -> 36
	{THREAD_1,36,{move_time,  &c1b1_turn_tcc_jolt}},        // state 36 -> 38 // angle to TCC
	// TODO: ensure that this is the right timing 
	{THREAD_1,38,{flashled,   &c1b1_tcc200ms_flash }},      // state 38 -> 40 
	{THREAD_1,40,{talk,       &c1b1_start_talk_tcc}},       // state 40 -> 43 (200 ms?) // message 1
	// TODO: ensure that this is the right timing make sure this is the right threshold
	{THREAD_1,43,{listen,     &c1b1_start_tisten_tcc}},     // state 43 -> 45 (200 ms?) // message 1
	{THREAD_1,45,{move_time,  &c1b1_turn_tcc_jolt2}},       // state 45 -> 48 // angle back to road
	{THREAD_1,48,{tracktrack, &c1b1_track_red_to_wall}},    // state 48 -> 50
	{THREAD_1,50,{flashled,   &c1b1_redwall_flash}},        // state 50 -> 53
	{THREAD_1,53,{move_time,  &c1b1_back_from_redwall}},    // state 53 -> 55
	{THREAD_1,55,{move_time,  &c1b1_turn_90_to_bot}},       // state 55 -> 57
	{THREAD_1,57,{move_time,  &c1b1_turn_135_to_tcc}},      // state 57 -> 58
	{THREAD_1,58,{talk,       &c1b1_start_talk_tcc2}},      // state 58 -> 59 (300 ms)  // message 2
	{THREAD_1,59,{move_time,  &c1b1_turn_135_to_bot}},      // state 59 -> 60
	{THREAD_1,60,{listen,     &c1b1_listen_bot2_start}},    // state 60 -> 62 (RCV 500 ms) // bot 2 START message
	{THREAD_1,62,{flashled,   &c1b1_receive_startflash}},   // state 62 -> 64 
	{THREAD_1,64,{listen,     &c1b1_listen_bot2_finish}},   // state 64 -> 66 (RCV 500 ms) // bot 2 FINISH message
	{THREAD_1,66,{move_if,    &c1b1_final_collision}},      // state 66 -> 68
	{THREAD_1,68,{flashled,   &c1b1_final_flash }},         // state 68 -> 69
	
	// challenge 1 bot 2
	{THREAD_2, 1,{listen,	    &c1b2_init_listen}}, 			    // state 1 -> 2 *** CHANGE BACK TO 500
	{THREAD_2, 2,{flashled,   &c1b2_initflash}},           	// state 2 -> 4
	{THREAD_2, 4,{talk,       &c1b2_start_talk}},           // state 4 -> 5
	{THREAD_2, 5,{flashled,   &c1b2_startflash}},           // state 5 -> 6
	{THREAD_2, 6,{move_if,    &c1b2_initial_collision1}},   // state 6 -> 8
	{THREAD_2, 8,{move_time,  &c1b2_initial_collision2}},   // state 8 -> 10
	{THREAD_2,10,{move_if,    &c1b2_initial_collision3}},   // state 10 -> 13
	{THREAD_2,13,{tracktrack, &c1b2_track_red}},            // state 13 -> 14 ***
	{THREAD_2,14,{move_time,  &c1b2_forward_smidge1}},      // state 14 -> 15
	{THREAD_2,15,{move_time,  &c1b2_left_90}},              // state 15 -> 20
	{THREAD_2,20,{tracktrack, &c1b2_track_yellow}},         // state 20 -> 25 ***
	{THREAD_2,25,{move_time,  &c1b2_right_90}},             // state 25 -> 27
	{THREAD_2,27,{move_time,  &c1b2_forward_jolt}},         // state 27 -> 30 
	{THREAD_2,30,{tracktrack, &c1b2_track_blue}},           // state 30 -> 35 ***
	{THREAD_2,35,{move_time,  &c1b2_stop_hall_jolt1}},      // state 35 -> 36
	{THREAD_2,36,{move_time,  &c1b2_turn_tcc_jolt}},        // state 36 -> 38 // angle to TCC
	{THREAD_2,38,{flashled,   &c1b2_tcc200ms_flash}},       // state 38 -> 40 
	{THREAD_2,40,{talk,       &c1b2_start_talk_tcc}},       // state 40 -> 43 (400 ms) // message 3
	{THREAD_2,43,{listen,     &c1b2_start_listen_tcc}},     // state 43 -> 45 (RCV 400 ms) // message 3
	{THREAD_2,45,{move_time,  &c1b2_turn_tcc_jolt2}},       // state 45 -> 48 // angle back to road
	{THREAD_2,48,{tracktrack, &c1b2_track_blue_to_wall}},   // state 48 -> 50
	{THREAD_2,50,{flashled,   &c1b2_bluewall_flash}},       // state 50 -> 53
	{THREAD_2,53,{move_time,  &c1b2_back_from_bluewall}},   // state 53 -> 55
	{THREAD_2,55,{move_time,  &c1b2_turn_90_to_bot}},       // state 55 -> 58
	{THREAD_2,58,{talk,       &c1b2_talk_to_bot1}},     	  // state 58 -> 60 (500 ms)  // tell bot 1 to start again
	{THREAD_2,60,{move_if,    &c1b2_final_collision}},      // state 60 -> 65
	{THREAD_2,65,{flashled,   &c1b2_final_flash}}, 			    // state 65 -> 69
	

	
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
