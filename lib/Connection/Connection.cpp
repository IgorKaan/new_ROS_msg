#include "Connection.h"
#include <MotorControl.h>
#include "RobotId.h"
#include <std_msgs/Int8.h>
#include <ros.h>

#define sensorOnePin 34
#define sensorTwoPin 35

bool configuredState = 0;

int sensorData = 0;
int predSendorData = 0;
int data = 0;
int count = 0;
int controlMassive[10] = {1,2,3,4,5,6,7,8,9,10};

std_msgs::Int8 robotid;
ros::Publisher pubConfigured("configured", &robotid);

void Connection::setup() {

     pinMode(sensorOnePin,INPUT);
     pinMode(sensorTwoPin,INPUT);

 }

void Connection::connectRight() {

    if(sensorData >= predSendorData) {

        predSendorData = sensorData;
        sensorData = analogRead(sensorOnePin);
        Serial.println("sensorData = ");
        Serial.println(sensorData);
        
        //delay(10); 
        microMoveRight();
        
       
        Serial.println("predSensorData = ");
        Serial.println(predSendorData);


    }

    if(sensorData < predSendorData) {

        Serial.println("stop = ");
        goLeft(44);
        delay(100);
        stopMovement();
        delay(500);
        goForward(500);
        delay(2500);
        stopMovement();
        delay(100000);
        
    }
    
}

void Connection::connectLeft() {

    if(sensorData >= predSendorData) {

        
        sensorData = analogRead(sensorOnePin);
        predSendorData = sensorData;
        Serial.println("sensorData = ");
        Serial.println(sensorData);
        
        //delay(10); 
        microMoveLeft();
        
        Serial.println(count);
        controlMassive[count] = sensorData;
        count++;

        Serial.println("predSensorData = ");
        Serial.println(predSendorData);

    }

    if(sensorData < predSendorData) {

        Serial.println("stop = ");
        goRight(44);
        delay(100);
        stopMovement();
        delay(500);
        goForward(500);
        delay(2500);
        stopMovement();
        delay(100000);
        
    }
    
}

void Connection::connect() {

    if (controlMassive[3] != controlMassive [4]) {

        connectLeft();
    }    

    else if (controlMassive[3] == controlMassive [4]) {

        connectRight();  

    }
    

}

void Connection::configured(uint8_t connection_side_id, uint8_t connection_state) {

    pubConfigured.publish( &robotid );

}

 void Connection::capture() {

     int a;
     int b;
     a = analogRead(34);
     b = analogRead(35);
     Serial.println(a);
     Serial.println(b);
     
 }