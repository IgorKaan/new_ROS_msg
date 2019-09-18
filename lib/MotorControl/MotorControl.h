#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <WEMOS_Motor.h>
#include "math.h" 

class MotorControl
{
    public:
        
        void navigation(bool moveforwardValue, bool rotateValue ,short correctValue, float actionTime);

        void goForward(short speed);

        void forwardConnect(short time);

        void leftConnect(short time);

        void rightConnect(short time);

        void goBackward();

        void goLeft();

        void goRight();

        void turnLeft();

        void turnRight();

        void leftForward();

        void rightForward();

        void leftBackward();

        void rightBackward();

        void calibrate();

        void calibrateLeft();

        void microMoveLeft();

        void microMoveRight();

        void leftGrabCapture();

        void leftGrabRelease();

        void leftGrabStop();

        void rightGrabCapture();

        void rightGrabRelease();

        void rightGrabStop();

        void stopMovement();

        void brake();

};

// class Connection 
// {
//     public:

// };


#endif