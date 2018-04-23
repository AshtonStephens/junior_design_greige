/* 
 * arduino.h
 * 
 *
 */

#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#include <iostream>
#include <stdint.h>
#include <time.h> 
#include <sys/types.h>
#include <string>

#define HIGH 255
#define LOW  0

#define pinMode(name,type) pinMode_func( #name , name , type )

enum arduino_pintype 
{
    INPUT = 0,
    INPUT_PULLUP = 1,
    OUTPUT =  2,
    DEBUG_  =  3
};

struct serialport 
{
    template <typename T>
    void print(T toPrint)   { std::cerr << toPrint;}

    template <typename T>
    void println(T toPrint) { std::cerr << toPrint << '\n';}
};

extern long long millis();

extern void pinMode_func (
        const std::string pin_name, 
        const int pin_num, 
        const arduino_pintype pin);

extern void analogWrite  (int pin, int write);
extern int  analogRead   (int pin);
extern void digitalWrite (int pin, int write);
extern int  digitalRead  (int pin);

extern void printPins    ();

extern void init_fake_ports ();

extern serialport Serial;

#endif
