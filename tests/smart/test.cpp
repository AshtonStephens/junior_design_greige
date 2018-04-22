
#include "fake_arduino.h"

int main (int argc, char *argv[])
{

    (void) argc;
    (void) argv;

    fprintf(stderr,"hi\n");
    Serial.println(millis());

    unsigned long timer;
    timer = millis();
    
    while ( 1000 > millis() - timer) {}

    Serial.println(millis());

    Serial.println("hi!");
}
