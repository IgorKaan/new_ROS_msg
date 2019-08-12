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
    if (motorSpeed >= 200) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 200) {
        short speed;
        short kp;
        kp = motorSpeed/200;
        speed = PWM*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);
    }
}

void MotorControl::goBackward(short motorSpeed)
{
    if (motorSpeed >= 200) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 200) {
        short speed;
        short kp;
        kp = motorSpeed/200;
        speed = PWM*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CW, speed);
    }
    
}

void MotorControl::goRight(short motorSpeed)
{
    if (motorSpeed >= 200) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 200) {
        short speed;
        short kp;
        kp = motorSpeed/200;
        speed = PWM*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CW, speed);
    }
}

void MotorControl::goLeft(short motorSpeed)
{
    if (motorSpeed >= 200) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 200) {
        short speed;
        short kp;
        kp = motorSpeed/200;
        speed = PWM*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CCW, speed);
    }
}

void MotorControl::turnLeft(short motorSpeed)
{
    if (abs(motorSpeed)>20) {
        M1.setmotor(_CCW, PWMR);
        M2.setmotor(_CCW, PWMR);
        M3.setmotor(_CCW, PWMR);
        M4.setmotor(_CCW, PWMR);
    }
    else if (abs(motorSpeed)<=20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWMR*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);    
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
    else if (abs(motorSpeed)<=20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWMR*kp;
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CW, speed);    
    }
}

void MotorControl::stopMovement()
{
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, 0);
}


