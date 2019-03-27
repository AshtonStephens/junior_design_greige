
#ifndef DEBUGME_H_
#define DEBUGME_H_

#define VAR_(a) Serial.print(#a); Serial.print(": "); Serial.println(a)
#define DBG  Serial.print("{");Serial.print("--");Serial.print("}[");Serial.print(__func__);Serial.print("](");Serial.print(__LINE__);Serial.println(")")
#define DBG_STP DBG; do {} while(true)

	#define CATS
	
	
#endif

