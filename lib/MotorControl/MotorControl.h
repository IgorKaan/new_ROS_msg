#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <WEMOS_Motor.h>
#include "math.h" 

class MotorControl
{
    public:
        short rotateAngle;

        float targetAngle;
    
        void setupMotor();

        void driveMotor();

        void navigation(bool moveforwardValue, bool rotateValue ,short correctValue);

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

    private:

        short currentVectorX;

        short currentVectorY;

        short targetVectorX;

        short targetVectorY;

        short x0, x1, x2, y0, y1, y2;

        float scalprod, mod1, mod2;

};

#endif