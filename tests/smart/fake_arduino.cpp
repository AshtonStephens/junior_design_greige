/* 
 * arduino.cpp
 * 
 *
 */

#define DEBUG
#include "debug_macros.h"
#include "fake_arduino.h"

#define NUM_PINS_ARDUINO_ADK 70

/* --------------------------------------------- */
/* -- Arduino Pin Tracker ---------------------- */
/* --------------------------------------------- */

struct ArduinoPin
{
    ArduinoPin (
            arduino_pintype pintype, 
            const std::string name, 
            int pinnumber) :
            pintype(pintype), name (name),
            pinnumber(pinnumber), value(0) {};

    arduino_pintype pintype;
    std::string  name;
    int pinnumber;
    int value;
};

struct ArduinoPin * pins[NUM_PINS_ARDUINO_ADK];

/* --------------------------------------------- */

serialport Serial;
static unsigned long time_reference;

extern void pinMode_func (
        const std::string pin, 
        const int pin_num, 
        const arduino_pintype pintype)
{
    DBG_ASSERT(pins[pin_num] == NULL);
      
    pins[pin_num] = new ArduinoPin 
        (pintype,pin,pin_num);


/*
    std::cerr << " [";
    switch ()
        std::cerr << "\033[34m" << type;
    } else if ("INPUT" == type) {
        std::cerr << "\033[33m" <<  type;
    } else if ("INPUT_PULLUP" == type) {
        std::cerr << "\033[32m" <<  type;
    } else {
        std::cerr << "\033[31m" << type;
    }
    std::cerr << "\033[0m]\t" << pin << std::endl;
*/
}

extern void analogWrite (int pin, int write)
{
    DBG_ASSERT (pin < NUM_PINS_ARDUINO_ADK);
    std::cerr << write  << std::endl;
}
void init_fake_ports ()
{
    for (int i = 0; i < NUM_PINS_ARDUINO_ADK; ++i)
        pins[i] = NULL;
}

/* --------------------------------------------- */
/*  TIMING FUNCTIONS --------------------------- */
/* --------------------------------------------- */

long long ts_to_ll (struct timespec &t);
//void set_time_factor(unsigned long  factor);

long long millis()
{
    static bool timer_started = false;
    struct timespec temp;
    
    if (!timer_started) {
        timer_started = true;
        clock_gettime(CLOCK_REALTIME, &temp);
        time_reference = ts_to_ll(temp);
    }
    clock_gettime(CLOCK_REALTIME, &temp);
    return (ts_to_ll(temp) - time_reference);
}

long long ts_to_ll (struct timespec &t) 
{ return t.tv_sec * 1000 + t.tv_nsec / 10000000; } 

/*  TIMING FUNCTIONS ----------------------------- */


