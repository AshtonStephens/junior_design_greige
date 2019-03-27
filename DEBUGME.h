// 
// DEBUGME.h
// purpose: gives us functions that quickly print out variables and 
// 			perform typical debug functions that we otherwise would
//			be writing repetitively.
// By: Ashton Stephens
// Date: 3/3/18

#ifndef DEBUGME_H_
#define DEBUGME_H_

// print a variable's value along with its name
#define VAR_(a) Serial.print(#a); Serial.print(": "); Serial.println(a)

// print the function and line number
#define DBG  Serial.print("{");Serial.print("--");Serial.print("}[");Serial.print(__func__);Serial.print("](");Serial.print(__LINE__);Serial.println(")")

// print the function, line number, and halt functionality
#define DBG_STP DBG; do {} while(true)
	
#endif

