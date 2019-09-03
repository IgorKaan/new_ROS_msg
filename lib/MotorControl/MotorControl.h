#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <WEMOS_Motor.h>
#include "math.h" 

class MotorControl
{
    public:
        
        void navigation(bool moveforwardValue, bool rotateValue ,short correctValue, float actionTime);

        void goForward(short motorSpeed);

        void goBackward(short motorSpeed);

        void goLeft(short motorSpeed);

        void goRight(short motorSpeed);

        void turnLeft(short motorSpeed);

        void turnRight(short motorSpeed);

        void leftForward(short motorSpeed);

        void rightForward(short motorSpeed);

        void leftBackward(short motorSpeed);

        void rightBackward(short motorSpeed);

        void calibrate(short motorSpeed);

        void stopMovement();

        void brake();

};

// class Connection 
// {
//     public:

// };


#endif