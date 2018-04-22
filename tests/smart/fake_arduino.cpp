/* 
 * arduino.cpp
 * 
 *
 */

#include "fake_arduino.h"


serialport Serial;
static unsigned long time_factor   ;
static unsigned long time_reference;
bool timer_started = false;

unsigned long ts_to_ul (struct timespec &t);
//void set_time_factor(unsigned long  factor);

unsigned long millis()
{
    struct timespec temp;
    unsigned long PL;
    
    if (!timer_started) {
        timer_started = true;
        clock_gettime(CLOCK_REALTIME, &temp);
        time_reference = ts_to_ul(temp);
    }
    clock_gettime(CLOCK_REALTIME, &temp);
    PL = (ts_to_ul(temp) - time_reference) / time_factor;
    
    Serial.println(ts_to_ul(temp) - time_reference);
    
    return PL;
}

unsigned long ts_to_ul (struct timespec &t) 
{ return t.tv_sec * 1000 + t.tv_nsec / 10000000; } 

/*
void set_time_factor(unsigned long new_factor)
{
    struct timespec temp_ts;
    unsigned long   temp_ul;

    if (timer_started) {
        clock_gettime(CLOCK_REALTIME, &temp_ts);
        temp_ul = ts_to_ul(temp_ts);
        time_reference = temp_ul - 
            (temp_ul - time_reference)*(((float)new_factor)/time_factor);
    }

    time_factor = new_factor;
}
*/
