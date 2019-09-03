#include "Connection.h"
#include <MotorControl.h>

#define intpin 124

void Connection::setup() {

     pinMode(34,INPUT);
     pinMode(35,INPUT);

 }


void Connection::connect(short aDistaance, short bDictacnce, short cDistance) {

    if (aDistaance != 0) {
    
        MotorControl::goForward(30);

    }

}

 void Connection::capture() {

     int a;
     int b;
     a = analogRead(34);
     b = analogRead(35);
     Serial.println(a);
     Serial.println(b);
     
 }