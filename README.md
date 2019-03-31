# Junior Design - Autonomous Car Design

![Introduction Gif of Bots Performing the second challenge the robots can do](./readme/gifs/challenge2.gif)

## The Project

Junior design is a course that undergraduate Electrical and Computer Engineers take at 
Tufts that is intended to prepare them for the real world of product design. The project
boils down to creating an autonomous car that completes a route and some sort of
challenge - in this project, the task was to create an autonomous car that could
complete a route that looked like roads and avoid pedestrians as well as communicate
to a watch tower about its position.

Key details of the course are:
- Every robot is made by a team of 3 Electrical engineering students.
- Each team member needs to keep an engineering notebook documenting the
    design process and parts of the circuit for reference
- Parts of the robot are outsourced to other teams in the class by designing
    a specification sheet and requesting the design. 

What makes this project hard is:
- Every part of the bot is made using rudimentary circuit components except 
    the arduino processor and the physical internals of the motors.
- All rudimentary parts used in the project have spec sheets with somewhat
    wrong data
- Most parts used have enough variation to make the programming required for
    between identical components significantly different
- The project description and requirements are designed to be almost impossible 
    to complete, and the actual project requirements need to be determined by 
    talking to stakeholders - (the professor)

## The Bots

![Labeled photo of robot parts layout without all comonents](./readme/images/bots_together_colored.jpg)

The bots above are the final design of the bots. To the left is "Galactus 
Destroyer of Pedestrians" by team Zinnobar. To the right is "Susan", of team 
Greige. The above photo shows

# Challenges
## Challenge 1
![Gif of Bots Performing the first challenge the robots can do](./readme/gifs/challenge1primary.gif)

```c
/* excerpt from program.h */
// CHALLENGE 1 BOT 1 ------------------------------------------------------

    // the code for this challenge is too long to reasonably place in this 
    // readme, but it can be found in lines  41-79 of 'program.h' above.

```

## Challenge 2
![Gif of Bots Performing the second challenge the robots can do](./readme/gifs/challenge2.gif)

```c
/* excerpt from program.h */
// CHALLENGE 2 BOT 1 ------------------------------------------------------
    {THREAD_3, 1,  {listen,     &c2b1_rcv_500ms}},        // receive 500ms message
    {THREAD_3, 5,  {move_time,  &c2b1_fwd_12in}},         // move forward 12
    {THREAD_3, 8,  {flashled,   &c2b1_flash_head}},       // 
    {THREAD_3, 10, {move_time,  &c2b1_stop_1}},           // STOP #1
    {THREAD_3, 15, {move_time,  &c2b1_turn_180}},         // Turn around 180
    {THREAD_3, 20, {move_time,  &c2b1_back_3}},           // Backwards 3
    {THREAD_3, 25, {move_time,  &c2b1_stop_2}},           // STOP #2
    {THREAD_3, 30, {move_time,  &c2b1_left_90}},          // Turn left 90
    {THREAD_3, 35, {move_time,  &c2b1_right_1}},          // Turn right 
    {THREAD_3, 40, {move_time,  &c2b1_lightstop_1}},      // Light stop
    {THREAD_3, 45, {move_time,  &c2b1_right_2}},          // Turn right
    {THREAD_3, 50, {move_time,  &c2b1_lightstop_2}},      // Light stop
    {THREAD_3, 55, {move_time,  &c2b1_right_3}},          // Turn right 
    {THREAD_3, 60, {move_time,  &c2b1_back_to_start}},    // Do your best to MOVE TO START
    {THREAD_3, 65, {talk,       &c2b1_send_500ms}},       // Send 500ms message to Bot 2 (stop auto)
```

## Challenge 3
![Gif of Bots Performing the third challenge the robots can do](./readme/gifs/challenge3.gif)

```c
    /* excerpt from program.h */
    // CHALLENGE 3 BOT 1 ------------------------------------------------------
    {THREAD_5, 1,  {move_time,  &c3b1_wait_start}},
    {THREAD_5, 3,  {move_if,    &c3b1_forward_light}},    //move forward until light sensed
    {THREAD_5, 5,  {move_time,  &c3b1_stop_5s}},          //stop 5 seconds
    {THREAD_5, 10, {talk,       &c3b1_send_500ms}},
    {THREAD_5, 15, {flashled,   &c3b1_flash_head_twice}},
    {THREAD_5, 20, {flashled,   &c3b1_illuminate_turnL}},
    {THREAD_5, 25, {flashled,   &c3b1_illuminate_turnR}},
```


Contributers:
- Ashton Stephens
- Liam Crowley
- Ashish Neupane
- Aji Sjamsu
- Joseph Meng
- Victor Dinh

