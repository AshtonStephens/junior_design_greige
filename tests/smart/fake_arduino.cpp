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
            pinnumber(pinnumber), value(0),
            digital(true) {};

    arduino_pintype pintype;
    std::string  name;
    int pinnumber;
    int value;
    bool digital;
};

struct ArduinoPin * pins[NUM_PINS_ARDUINO_ADK];

/* --------------------------------------------- */

serialport Serial;
static unsigned long time_reference;

extern void pinMode_func (
        const std::string pin_name, 
        const int pin_num, 
        const arduino_pintype pintype)
{
    DBG_ASSERT(pins[pin_num] == NULL);
    DBG;
    pins[pin_num] = new ArduinoPin 
        (pintype,pin_name,pin_num);
    std::cerr << pin_num << std::endl;
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

extern void printPins    ()
{
    for (int i = 0; i < NUM_PINS_ARDUINO_ADK; ++i) {
        if (pins[i] != NULL) {
            std::cerr << "[";
            if (i < 55) {
                std::cerr << i;
            } else {
                std::cerr << "A" << i - 55 ;
            }
            std::cerr << "][";
            switch (pins[i]->pintype) {
                case INPUT:
                    std::cerr << "\033[34mINPUT";
                    break;
                case INPUT_PULLUP:
                    std::cerr << "\033[33mINPUT_PULLUP";
                    break;
                case OUTPUT:
                    std::cerr << "\033[32mOUTPUT";
                    break;
            }
            std::cerr << "\033[0m]\t";
            if (pins[i]->digital) {
                if (!!(pins[i]->value)) {
                    std::cerr << "HIGH";
                } else {
                    std::cerr << "LOW";
                }
            } else {
                std::cerr << pins[i]->value;
            }
            std::cerr << std::endl;
        }    
    }
}

extern void digitalWrite (int pin, int write)
{
    DBG_ASSERT (pins[pin] != NULL);
    DBG_ASSERT (pin < NUM_PINS_ARDUINO_ADK);
    DBG_ASSERT (pins[pin]-> pintype == OUTPUT);
    DBG_ASSERT (write == HIGH || write == LOW);
    pins[pin]->digital = true;
    pins[pin]->value   = write;
}

extern void analogWrite (int pin, int write)
{
    DBG_ASSERT (pins[pin] != NULL);
    DBG_ASSERT (pin < NUM_PINS_ARDUINO_ADK);
    DBG_ASSERT (pins[pin]-> pintype == OUTPUT);
    pins[pin]->digital = false;
    pins[pin]->value   = write;
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


