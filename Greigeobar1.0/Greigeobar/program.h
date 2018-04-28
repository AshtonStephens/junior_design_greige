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


    // CHALLENGE 1 BOT 1
    //{THREAD_1, 1,  {move_time,&c1b1_starting_run}},
    {THREAD_1, 1,  {move_collision, &c1b1_starting_run1}},
    {THREAD_1, 10, {move_time,      &c1b1_starting_run2}},
    {THREAD_1, 12, {move_time,      &c1b1_starting_run3}},
    {THREAD_1, 1, {trackytrack,&c1b1_track_blue}},
    {THREAD_1, 30, {move_if,   &c1b1_turn_to_yellow}},
    {THREAD_1, 35, {tracktrack,&c1b1_track_yellow}},
    {THREAD_1, 40, {move_time,&c1b1_turn_after_yellow}},
    {THREAD_1, 45, {tracktrack,&c1b1_track_red}},
    {THREAD_1, 50, {tracktrack,&c1b1_turn_after_red}},
    {THREAD_1, 55, {hardware_stop, NULL}},              //// debug end


    //CHALLENGE 1 BOT 2
    {THREAD_2, 1, {  }}, 
    

    //CHALLENGE 2 BOT 1
    {THREAD_3, 1, {listen_, &c2b1_rcv_500ms}}, 			// receive 500ms message
    {THREAD_3, 5, {move_time, 	&c2b1_forward_12}}, 	// move forward 12
    {THREAD_3, 10, {move_time,	&c2b1_stop_1}}, 		// STOP #1
    {THREAD_3, 15, {move_time,	&c2b1_turn_180}},		// Turn around 180
    {THREAD_3, 20, {move_time,	&c2b1_back_3}},			// Backwards 3
    {THREAD_3, 25, {move_time,	&c2b1_stop_2}},			// STOP #2
    {THREAD_3, 30, {move_time,	&c2b1_left_90}},		// Turn left 90
    {THREAD_3, 35, {move_time,	&c2b1_right_1}},		// Turn right 
    {THREAD_3, 40, {move_time,	&c2b1_lightstop_1}},	// Light stop
    {THREAD_3, 45, {move_time,	&c2b1_right_2}},		// Turn right
    {THREAD_3, 50, {move_time,	&c2b1_lightstop_2}},	// Light stop
    {THREAD_3, 55, {move_time,	&c2b1_right_3}},		// Turn right 
    {THREAD_3, 60, {move_time,	&c2b1_back_to_start}},	// Do your best to MOVE TO START
    {THREAD_3, 65, {talk,	&c2b1_send_500ms}},			// Send 500ms message to Bot 2 (stop auto)

	
    //CHALLENGE 2 BOT 2
	{THREAD_4, 1, {talk, &c2b2_send_500ms}},				// send 500ms message
	{THREAD_4, 2, {listen_, &c2b2_rcv_500ms}}, 			// receive 500ms message
    {THREAD_4, 5, {move_time, 	&c2b2_forward_12}}, 	// move forward 12
    {THREAD_4, 10, {move_time,	&c2b2_stop_1}}, 		// STOP #1
    {THREAD_4, 15, {move_time,	&c2b2_turn_180}},		// Turn around 180
    {THREAD_4, 20, {move_time,	&c2b2_back_3}},			// Backwards 3
    {THREAD_4, 25, {move_time,	&c2b2_stop_2}},			// STOP #2
    {THREAD_4, 30, {move_time,	&c2b2_left_90}},		// Turn left 90
    {THREAD_4, 35, {move_time,	&c2b2_right_1}},		// Turn right 
    {THREAD_4, 40, {move_time,	&c2b2_lightstop_1}},	// Light stop
    {THREAD_4, 45, {move_time,	&c2b2_right_2}},		// Turn right
    {THREAD_4, 50, {move_time,	&c2b2_lightstop_2}},	// Light stop
    {THREAD_4, 55, {move_time,	&c2b2_right_3}},		// Turn right 
    {THREAD_4, 60, {move_time,	&c2b2_back_to_start}},	// Do your best to MOVE TO START

    //CHALLENGE 3 BOT 1
	{THREAD_5, 1, {move_if, &c3b1_forward_light}},		//move forward until light sensed
	{THREAD_5, 5, {move_time, &c3b1_stop_5s}},			//stop 5 seconds
	{THREAD_5, 10, {talk, &c3b1_send_500ms}},
	{THREAD_5, 15, {flashled, &c3b1_flash_head_twice}},
	{THREAD_5, 20, {flashled, &c3b1_illuminate_turn}},
	
    //CHALLENGE 3 BOT 2
	{THREAD_6, 1, {move_if, &c3b2_forward_light}},
	{THREAD_6, 5, {listen_, &c3b2_rcv_500ms}},
	{THREAD_6, 10, {flashled, &c3b2_flash_head_twice}},
	{THREAD_6, 15, {flashled, &c3b2_illuminate_turn}},
	
    // STOPPING STATE
    {THREAD_0|THREAD_1|THREAD_2|
     THREAD_3|THREAD_4|THREAD_5|
     THREAD_6|THREAD_7|
     THREAD_8|THREAD_9|THREAD_10|
     THREAD_11|THREAD_12|THREAD_13|
     THREAD_14|THREAD_15, 69,{hardware_stop,NULL}}
};


#endif
