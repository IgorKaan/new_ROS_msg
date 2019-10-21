#include "MotorControl.h"
#include "math.h"
#include <Arduino.h>
#include <WEMOS_Motor.h> 

#define M1_Adress (0x2A) 
#define M2_Adress (0x2B)
#define M3_Adress (0x2C)  
#define M4_Adress (0x2D)

#define M5_Adress (0x32)  
#define M6_Adress (0x30)

#define PWM 21 //35
// #define PWM 45 //35
#define PWML 15
#define PWMR  15//30
#define PWMRL 15
#define MICROPWM 17

Motor M1(M1_Adress, _MOTOR_B, 1000);
Motor M2(M2_Adress, _MOTOR_B, 1000);
Motor M3(M3_Adress, _MOTOR_B, 1000);
Motor M4(M4_Adress, _MOTOR_B, 1000);

Motor M5(M5_Adress, _MOTOR_B, 1000);
Motor M6(M6_Adress, _MOTOR_B, 1000);

void MotorControl::navigation(bool moveForwardValue, bool rotateValue ,short correctValue, float actionTime) 
{
    if ((moveForwardValue == 1) && (rotateValue == 0)) {

        if (correctValue <= 30 && correctValue >= -30) {
            MotorControl::goForward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
        }

        if (correctValue < -30 && correctValue > -60) {
            MotorControl::leftForward();
            delay(actionTime*0.7); 
            MotorControl::brake();
        }

        if (correctValue > 30 && correctValue < 60) {
            MotorControl::rightForward();
            delay(actionTime*0.7); 
            MotorControl::brake();
        }

        else if (correctValue >= 150 || correctValue <= -150) {
            MotorControl::goBackward(PWM);
            delay(actionTime*0.7); 
            MotorControl::brake();
        } 

        else if (correctValue > -150 && correctValue < -120) {
            MotorControl::leftBackward();
            delay(actionTime*0.7); 
            MotorControl::brake();           
        } 

        else if (correctValue > 120 && correctValue < 150) {
            MotorControl::rightBackward(); 
            delay(actionTime*0.7); 
            MotorControl::brake();           
        } 

        else if (correctValue >= 60 && correctValue <= 120) {
            // if (actionTime > 500) {
            MotorControl::goRight();
            delay(actionTime*0.7); 
            MotorControl::brake(); 
            // }
            // else
            // {
            // MotorControl::microMoveRight();    /* code */
            // }
                          
        }

        else if (correctValue <= -60 && correctValue >= -120) {
            // if (actionTime > 500) {
            MotorControl::goLeft();
            delay(actionTime*0.7); 
            MotorControl::brake(); 
            //}
            // else
            // {
            // MotorControl::microMoveLeft();    /* code */
            // }                 
        } 

        else if (moveForwardValue == 0 && rotateValue == 0) {
            MotorControl::stopMovement();           
        }
    }
    else if ((moveForwardValue == 0) && (rotateValue == 1)) {

        if (correctValue > 0) {
            MotorControl::turnRight();
            delay(actionTime*0.7); 
            MotorControl::brake();           
        }
        else if (correctValue < 0) {
            MotorControl::turnLeft();
            delay(actionTime*0.7); 
            MotorControl::brake();     
        }
    }   
    else if (moveForwardValue == 0 && rotateValue == 0) {
        MotorControl::stopMovement();     
    }
}

void MotorControl::goForward(short speed)
{
        M1.setmotor(_CW, speed);
        M2.setmotor(_CW, speed);
        M3.setmotor(_CCW, speed);
        M4.setmotor(_CCW, speed);
}

void MotorControl::forwardConnect(short time) {

    M1.setmotor(_CW, PWM);
    M2.setmotor(_CW, PWM);
    M3.setmotor(_CCW, PWM);
    M4.setmotor(_CCW, PWM);
    delay(time);
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, 0);
    delay(time);
}

void MotorControl::leftForward()
{
    M1.setmotor(_CW, PWM);
    M2.setmotor(_CW, 0);
    M3.setmotor(_CCW, PWM);
    M4.setmotor(_CCW, 0);
}

void MotorControl::rightForward()
{
    M1.setmotor(_CW, 0);
    M2.setmotor(_CW, PWM);
    M3.setmotor(_CCW, 0);
    M4.setmotor(_CCW, PWM);
}



void MotorControl::goBackward(short speed)
{
    M1.setmotor(_CCW, speed);
    M2.setmotor(_CCW, speed);
    M3.setmotor(_CW, speed);
    M4.setmotor(_CW, speed);
}

void MotorControl::leftBackward()
{
    M1.setmotor(_CCW, 0);
    M2.setmotor(_CCW, PWM);
    M3.setmotor(_CW, 0);
    M4.setmotor(_CW, PWM);
}

void MotorControl::rightBackward()
{
    M1.setmotor(_CCW, PWM);
    M2.setmotor(_CCW, 0);
    M3.setmotor(_CW, PWM);
    M4.setmotor(_CW, 0);
}

void MotorControl::goRight()
{
    M1.setmotor(_CCW, PWM);
    M2.setmotor(_CW, PWM);
    M3.setmotor(_CW, PWM);
    M4.setmotor(_CCW, PWM); 
}

void MotorControl::microMoveRight()
{
    M1.setmotor(_CCW, PWM);
    M2.setmotor(_CW, PWM);
    M3.setmotor(_CW, PWM);
    M4.setmotor(_CCW, PWM);
    delay(50);
    M1.setmotor(_SHORT_BRAKE, 0);
    M2.setmotor(_SHORT_BRAKE, 0);
    M3.setmotor(_SHORT_BRAKE, 0);
    M4.setmotor(_SHORT_BRAKE, 0);
    delay(300);
        
}

void MotorControl::goLeft()
{
    M1.setmotor(_CW, PWM);
    M2.setmotor(_CCW, PWM);
    M3.setmotor(_CCW, PWM);
    M4.setmotor(_CW, PWM);
}

void MotorControl::microMoveLeft()
{
    M1.setmotor(_CW, PWM);
    M2.setmotor(_CCW, PWM);
    M3.setmotor(_CCW, PWM);
    M4.setmotor(_CW, PWM);
    delay(50);
    M1.setmotor(_SHORT_BRAKE, 0);
    M2.setmotor(_SHORT_BRAKE, 0);
    M3.setmotor(_SHORT_BRAKE, 0);
    M4.setmotor(_SHORT_BRAKE, 0);
    delay(300);
}

void MotorControl::turnLeft()
{
    M1.setmotor(_CW, PWMR);
    M2.setmotor(_CW, PWMR);
    M3.setmotor(_CW, PWMR);
    M4.setmotor(_CW, PWMR);
}

void MotorControl::turnRight()
{
    M1.setmotor(_CCW, PWMR);
    M2.setmotor(_CCW, PWMR);
    M3.setmotor(_CCW, PWMR);
    M4.setmotor(_CCW, PWMR);
}

void MotorControl::calibrate()
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

// void MotorControl::leftGrabCapture()
// {
//     M5.setmotor(_CW, 40);    
// }

// void MotorControl::leftGrabRelease()
// {
//     M5.setmotor(_CCW, 40);
// }

void MotorControl::leftGrabCapture()
{
    M5.setmotor(_CCW, 40);    
}

void MotorControl::leftGrabRelease() // for platform 2
{
    M5.setmotor(_CW, 40);
}

void MotorControl::leftGrabStop()
{
    M5.setmotor(_CCW, 0);
}

void MotorControl::rightGrabCapture()
{
    M6.setmotor(_CW, 40);  
}

void MotorControl::rightGrabRelease()
{
    M6.setmotor(_CCW, 40);    
}

void MotorControl::rightGrabStop()
{
    M6.setmotor(_CCW, 0);
}

void MotorControl::stopMovement()
{
    M1.setmotor(_STOP, 0);
    M2.setmotor(_STOP, 0);
    M3.setmotor(_STOP, 0);
    M4.setmotor(_STOP, 0);
}


