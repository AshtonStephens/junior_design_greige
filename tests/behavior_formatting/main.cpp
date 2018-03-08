//
// main.c
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "state.h"

void print(FILE *fp, const char *c, const int spd);

void turn_right (void *a) 
{   int spd = *(int*)a; 
    print(stdout,__func__,spd);}

void turn_left (void *a) 
{   int spd = *(int*)a; 
    print(stdout,__func__,spd);}

void go_forward (void *a) 
{   int spd = *(int*)a; 
    print(stdout,__func__,spd);}

void take_measurements_and_set_on_fire (void *a) 
{   int spd = *(int*)a; 
    print(stdout,__func__,spd);}

int speed60   = 60;
int speed70   = 70;
int speed90   = 90;
int speed100  = 100;
int speed1000 = 1000;

int main (int argc, char* argv[])
{ 
    (void) argc; (void) argv;

    struct behavior action0 = {take_measurements_and_set_on_fire ,&speed90};
    struct behavior action1 = {go_forward ,&speed1000};
    struct behavior action2 = {turn_left  ,&speed60};
    struct behavior action3 = {turn_right ,&speed100};
    struct behavior action4 = {go_forward,&speed1000};
    
    fprintf(stderr, "TESTING FILE %s\n", __FILE__);

    // COOL OR WHAT?!?!?!?!?!?!
    action0.func(action0.params); 
    action1.func(action1.params); 
    action2.func(action2.params); 
    action3.func(action3.params); 
    action4.func(action4.params); 


}


void print(FILE *fp,const char *c, const int spd)
{fprintf(fp,"%s with magnitude [\033[1;31m%d\033[0m]\n",c,spd);}


