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
    OUTPUT =  2
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
        const std::string pin, 
        const int pin_num, 
        const arduino_pintype);

extern void analogWrite (int pin, int write);

extern void init_fake_ports ();

extern serialport Serial;

#endif
