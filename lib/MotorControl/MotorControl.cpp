#include "MotorControl.h"
#include "math.h"
#include <Arduino.h>
#include <WEMOS_Motor.h> 

#define M1_Adress (0x2A) 
#define M2_Adress (0x2B)
#define M3_Adress (0x2C)  
#define M4_Adress (0x2D)
#define PWM 22 //35
#define PWML 15
#define PWMR 17 //30
#define PWMRL 15

Motor M1(M1_Adress, _MOTOR_B, 1000);
Motor M2(M2_Adress, _MOTOR_B, 1000);
Motor M3(M3_Adress, _MOTOR_B, 1000);
Motor M4(M4_Adress, _MOTOR_B, 1000);

void MotorControl::navigation(bool moveForwardValue, bool rotateValue ,short correctValue) 
{
    if (correctValue <= 45 && correctValue >= -45 && moveForwardValue == 1 && rotateValue == 0) {

        MotorControl::goForward(30); 

    }
    else if ((correctValue >= 135 || correctValue <= -135) && moveForwardValue == 1 && rotateValue == 0) {

        MotorControl::goBackward(30); 

    } 
    else if (correctValue > 45 && correctValue < 135 && moveForwardValue == 1 && rotateValue == 0) {

        MotorControl::goRight(30);    

    }
    else if ((correctValue < -45 && correctValue > -135) && moveForwardValue == 1 && rotateValue == 0 ) {

        MotorControl::goLeft(30);        

    } 
    else if (moveForwardValue == 0 && rotateValue == 0) {

        MotorControl::stopMovement();

    }
    else if (rotateValue == 1) {

        if (correctValue > 0) {

            MotorControl::turnRight(correctValue);

        }
        else if (correctValue < 0) {

            MotorControl::turnLeft(correctValue);

        }
        else if ((abs(correctValue)<=3)) {

        MotorControl::stopMovement();
        delay(5000);

        }
        else if (moveForwardValue == 0 && rotateValue == 0) {

        MotorControl::stopMovement();

        }
    }   
}

void MotorControl::goForward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);
    }
}

void MotorControl::goBackward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CW, speed);
    }
    
}

void MotorControl::goRight(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CCW, speed);
    }
}

void MotorControl::goLeft(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CW, speed);
    }
}

void MotorControl::turnLeft(short motorSpeed)
{
    if (abs(motorSpeed)>30) {
        M1.setmotor(_CW, PWMR);
        M2.setmotor(_CW, PWMR);
        M3.setmotor(_CW, PWMR);
        M4.setmotor(_CW, PWMR);
    }
    else if (abs(motorSpeed)<=30) {
        short speed;
        short kp;
        kp = motorSpeed/30;
        speed = PWMR*kp;
        if (speed < 10) {speed = 10;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CW, speed);    
    }
}

void MotorControl::turnRight(short motorSpeed)
{
    if (abs(motorSpeed)>30) {
        M1.setmotor(_CCW, PWMR);
        M2.setmotor(_CCW, PWMR);
        M3.setmotor(_CCW, PWMR);
        M4.setmotor(_CCW, PWMR);
    }
    else if (abs(motorSpeed)<=30) {
        short speed;
        short kp;
        kp = motorSpeed/30;
        speed = PWMR*kp;
        if (speed < 10) {speed = 10;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);    
    }
}

void MotorControl::stopMovement()
{
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, 0);
}


