#include "MotorControl.h"
#include "math.h"
#include <Arduino.h>
#include <WEMOS_Motor.h> 

#define M1_Adress (0x32) 
#define M2_Adress (0x30)
#define M3_Adress (0x2E)  
#define M4_Adress (0x2F)
#define PWM 35
#define PWML 15
#define PWMR 30
#define PWMRL 15

Motor M1(M1_Adress, _MOTOR_B, 1000);
Motor M2(M2_Adress, _MOTOR_B, 1000);
Motor M3(M3_Adress, _MOTOR_B, 1000);
Motor M4(M4_Adress, _MOTOR_B, 1000);

void MotorControl::setupMotor() 
{
    
}

void MotorControl::goForward(short motorSpeed)
{
    if (motorSpeed >= 100) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 100) {
        M1.setmotor(_CW, PWML);
        M2.setmotor(_CW, PWML);
        M3.setmotor(_CCW, PWML);
        M4.setmotor(_CCW, PWML);
    }
}

void MotorControl::goBackward(short motorSpeed)
{
    if (motorSpeed >= 100) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 100) {
        M1.setmotor(_CCW, PWML);
        M2.setmotor(_CCW, PWML);
        M3.setmotor(_CW, PWML);
        M4.setmotor(_CW, PWML);
    }
    
}

void MotorControl::goRight(short motorSpeed)
{
    if (motorSpeed >= 100) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 100) {
        M1.setmotor(_CCW, PWML);
        M2.setmotor(_CW, PWML);
        M3.setmotor(_CCW, PWML);
        M4.setmotor(_CW, PWML);
    }
}

void MotorControl::goLeft(short motorSpeed)
{
    if (motorSpeed >= 100) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 100) {
        M1.setmotor(_CW, PWML);
        M2.setmotor(_CCW, PWML);
        M3.setmotor(_CW, PWML);
        M4.setmotor(_CCW, PWML);
    }
}

void MotorControl::turnLeft(short motorSpeed)
{
    if (abs(motorSpeed)>15) {
        M1.setmotor(_CCW, PWMR);
        M2.setmotor(_CCW, PWMR);
        M3.setmotor(_CCW, PWMR);
        M4.setmotor(_CCW, PWMR);
    }
    else {
        M1.setmotor(_CCW, PWMRL);
        M2.setmotor(_CCW, PWMRL);
        M3.setmotor(_CCW, PWMRL);
        M4.setmotor(_CCW, PWMRL);    
    }
}

void MotorControl::turnRight(short motorSpeed)
{
    if (abs(motorSpeed)>15) {
        M1.setmotor(_CW, PWMR);
        M2.setmotor(_CW, PWMR);
        M3.setmotor(_CW, PWMR);
        M4.setmotor(_CW, PWMR);
    }
    else {
        M1.setmotor(_CW, PWMRL);
        M2.setmotor(_CW, PWMRL);
        M3.setmotor(_CW, PWMRL);
        M4.setmotor(_CW, PWMRL);
    }
}

void MotorControl::stopMovement()
{
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, 0);
}


