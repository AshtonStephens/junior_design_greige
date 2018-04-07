//
// state.h
//
// Purpose: To store the state of the bot at any given point
//
// Date: 3-3-18 
// By:  Ashton Stephens and Joseph Ming
//

#ifndef STATE_H
#define STATE_H

struct behavior {
    void (*func)(void*);
    void *params;
};

struct state 
{

    behavior action;
    color    current_path;

    // cnext = NULL if state is not color dependent
    struct state *  cnext;  // pointer to state triggered by color
    color           ctarget;// color target

    // tnext = NULL if state is not time depentent
    struct state *  tnext;  // pointer to state triggered by timer
    int             ttarget;// timer target

    bool stay_on_path;

};

#endif
