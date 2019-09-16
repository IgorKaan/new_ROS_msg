#include "MotorControl.h"
#include "math.h"
#include <Arduino.h>
#include <WEMOS_Motor.h> 

#define M1_Adress (0x2A) 
#define M2_Adress (0x2B)
#define M3_Adress (0x2C)  
#define M4_Adress (0x2D)

#define M5_Adress (0x30)  
#define M6_Adress (0x32)

#define PWM 17 //35
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

            //*flag = 0;
            MotorControl::goForward();
            delay(actionTime*0.7); 
            MotorControl::brake();

        }

        if (correctValue < -30 && correctValue > -60) {

            //*flag = 0;
            MotorControl::leftForward();
            delay(actionTime*0.7); 
            MotorControl::brake();
            ;

        }

        if (correctValue > 30 && correctValue < 60) {

            //*flag = 0;
            MotorControl::rightForward();
            delay(actionTime*0.7); 
            MotorControl::brake();
            

        }

        else if (correctValue >= 150 || correctValue <= -150) {

            //*flag = 0;
            MotorControl::goBackward();
            delay(actionTime*0.7); 
            MotorControl::brake();
             

        } 

        else if (correctValue > -150 && correctValue < -120) {

            //*flag = 0;
            MotorControl::leftBackward();
            delay(actionTime*0.7); 
            MotorControl::brake(); 
            

        } 

        else if (correctValue > 120 && correctValue < 150) {

            //*flag = 0;
            MotorControl::rightBackward(); 
            delay(actionTime*0.7); 
            MotorControl::brake();
            

        } 

        else if (correctValue >= 60 && correctValue <= 120) {

            //*flag = 0;
            MotorControl::goRight();
            delay(actionTime*0.7); 
            MotorControl::brake();
                

        }

        else if (correctValue <= -60 && correctValue >= -120) {

            //*flag = 0;
            MotorControl::goLeft();
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
            MotorControl::turnRight();
            delay(actionTime*0.7); 
            MotorControl::brake();
            
        }
        else if (correctValue < 0) {

            //*flag = 0;
            MotorControl::turnLeft();
            delay(actionTime*0.7); 
            MotorControl::brake();
            
        }
    }   
    else if (moveForwardValue == 0 && rotateValue == 0) {

        //*flag = 0;
        MotorControl::stopMovement();
        
    }
}

void MotorControl::goForward()
{
        M1.setmotor(_CW, PWM);
        M2.setmotor(_CW, PWM);
        M3.setmotor(_CCW, PWM);
        M4.setmotor(_CCW, PWM);
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



void MotorControl::goBackward()
{
        M1.setmotor(_CCW, PWM);
        M2.setmotor(_CCW, PWM);
        M3.setmotor(_CW, PWM);
        M4.setmotor(_CW, PWM);
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
        M1.setmotor(_CCW, MICROPWM);
        M2.setmotor(_CW, MICROPWM);
        M3.setmotor(_CW, MICROPWM);
        M4.setmotor(_CCW, MICROPWM);
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
        M1.setmotor(_CW, MICROPWM);
        M2.setmotor(_CCW, MICROPWM);
        M3.setmotor(_CCW, MICROPWM);
        M4.setmotor(_CW, MICROPWM);
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

void MotorControl::leftGrabCaprure()
{

}

void MotorControl::leftGrabRelease()
{
    
}

void MotorControl::rightGrabCaprure()
{

}

void MotorControl::rightGrabRelease()
{
    
}

void MotorControl::stopMovement()
{
    M1.setmotor(_STOP, 0);
    M2.setmotor(_STOP, 0);
    M3.setmotor(_STOP, 0);
    M4.setmotor(_STOP, 0);
}


