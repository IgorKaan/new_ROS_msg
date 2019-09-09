#include "MotorControl.h"
#include "math.h"
#include <Arduino.h>
#include <WEMOS_Motor.h> 

#define M1_Adress (0x2A) 
#define M2_Adress (0x2B)
#define M3_Adress (0x2C)  
#define M4_Adress (0x2D)
#define PWM 17 //35
#define PWML 15
#define PWMR  15//30
#define PWMRL 15

Motor M1(M1_Adress, _MOTOR_B, 1000);
Motor M2(M2_Adress, _MOTOR_B, 1000);
Motor M3(M3_Adress, _MOTOR_B, 1000);
Motor M4(M4_Adress, _MOTOR_B, 1000);

void MotorControl::navigation(bool moveForwardValue, bool rotateValue ,short correctValue, float actionTime) 
{
    if ((moveForwardValue == 1) && (rotateValue == 0)) {

        if (correctValue <= 30 && correctValue >= -30) {

            //*flag = 0;
            MotorControl::goForward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();

        }

        if (correctValue < -30 && correctValue > -60) {

            //*flag = 0;
            MotorControl::leftForward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
            ;

        }

        if (correctValue > 30 && correctValue < 60) {

            //*flag = 0;
            MotorControl::rightForward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
            

        }

        else if (correctValue >= 150 || correctValue <= -150) {

            //*flag = 0;
            MotorControl::goBackward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
             

        } 

        else if (correctValue > -150 && correctValue < -120) {

            //*flag = 0;
            MotorControl::leftBackward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake(); 
            

        } 

        else if (correctValue > 120 && correctValue < 150) {

            //*flag = 0;
            MotorControl::rightBackward(PWM); 
            delay(actionTime*0.7); 
            MotorControl::brake();
            

        } 

        else if (correctValue >= 60 && correctValue <= 120) {

            //*flag = 0;
            MotorControl::goRight(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
                

        }

        else if (correctValue <= -60 && correctValue >= -120) {

            //*flag = 0;
            MotorControl::goLeft(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
                  

        } 

        else if (moveForwardValue == 0 && rotateValue == 0) {

            //*flag = 0;
            MotorControl::stopMovement();
            

        }
    }
    else if ((moveForwardValue == 0) && (rotateValue == 1)) {

        if (correctValue > 0) {

            //*flag = 0;
            MotorControl::turnRight(correctValue);
            delay(actionTime*0.7); 
            MotorControl::brake();
            
        }
        else if (correctValue < 0) {

            //*flag = 0;
            MotorControl::turnLeft(correctValue);
            delay(actionTime*0.7); 
            MotorControl::brake();
            
        }
    }   
    else if (moveForwardValue == 0 && rotateValue == 0) {

        //*flag = 0;
        MotorControl::stopMovement();
        
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
    // M1.setmotor(_CW, motorSpeed);
    // M2.setmotor(_CW, motorSpeed);
    // M3.setmotor(_CCW, motorSpeed);
    // M4.setmotor(_CCW, motorSpeed);
}

void MotorControl::leftForward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CW, 0);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CCW, 0);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, 0);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, 0);
    }
}

void MotorControl::rightForward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CW, 0);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, 0);
        M4.setmotor(_CCW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CW, 0);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CCW, 0);
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

void MotorControl::leftBackward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CCW, 0);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, 0);
        M4.setmotor(_CW, PWM);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CCW, 0);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CW, 0);
        M4.setmotor(_CW, speed);
    } 
}

void MotorControl::rightBackward(short motorSpeed)
{
    if (motorSpeed >= 20) {
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CCW, 0);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CW, 0);
    }
    else if (motorSpeed < 20) {
        short speed;
        short kp;
        kp = motorSpeed/20;
        speed = PWM*kp;
        if (speed < 20) {speed = 20;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, 0);
        M3.setmotor(_CW, speed);
        M4.setmotor(_CW, 0);
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
        if (speed < 15) {speed = 15;}
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
        if (speed < 15) {speed = 15;}
        M1.setmotor(_CCW, speed);
        M2.setmotor(_CCW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);    
    }
}

void MotorControl::calibrate(short motorSpeed)
{    
    M1.setmotor(_CW, 15);
    M2.setmotor(_CW, 15);
    M3.setmotor(_CCW, 15);
    M4.setmotor(_CCW, 15); 
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, 0);
    delay(50);      
}

void MotorControl::brake()
{
    M1.setmotor(_SHORT_BRAKE, 0);
    M2.setmotor(_SHORT_BRAKE, 0);
    M3.setmotor(_SHORT_BRAKE, 0);
    M4.setmotor(_SHORT_BRAKE, 0);
}

void MotorControl::calibrateLeft(short motorSpeed)
{
    // if (motorSpeed >= 20) {
    //     M1.setmotor(_CW, PWM);
    //     M2.setmotor(_CCW, PWM);
    //     M3.setmotor(_CCW, PWM);
    //     M4.setmotor(_CW, PWM);
    // }
    // else if (motorSpeed < 20) {
    //     short speed;
    //     short kp;
    //     kp = motorSpeed/20;
    //     speed = PWM*kp;
    //     if (speed < 20) {speed = 20;}
    //     M1.setmotor(_CW, speed);
    //     M2.setmotor(_CCW, speed);
    //     M3.setmotor(_CCW, speed);
    //     M4.setmotor(_CW, speed);
    // }

    M1.setmotor(_CW, PWM - motorSpeed/4095);
    M2.setmotor(_CCW, PWM - motorSpeed/4095);
    M3.setmotor(_CCW, PWM - motorSpeed/4095);
    M4.setmotor(_CW, PWM - motorSpeed/4095);
}

void MotorControl::stopMovement()
{
    M1.setmotor(_STOP, 0);
    M2.setmotor(_STOP, 0);
    M3.setmotor(_STOP, 0);
    M4.setmotor(_STOP, 0);
}


