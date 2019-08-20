#include "Connection.h"
#include <MotorControl.h>


void Connection::Connect(short aDistaance, short bDictacnce, short cDistance) {

    if (aDistaance != 0) {
    
        MotorControl::goForward(30);

    }

}

 void Connection::Capture() {

     digitalWrite(1,1);
     digitalWrite(2,2);
     
 }