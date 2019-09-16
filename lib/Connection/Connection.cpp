#include "Connection.h"
#include <MotorControl.h>
#include <std_msgs/Int8.h>
#include <ros.h>

// #define sensorOnePin 34
// #define sensorTwoPin 35

#define sensorOnePin 34
#define sensorTwoPin 35

using namespace std_msgs;
using namespace rosserial_msgs;



unsigned long time1, time2 , time3;

bool configuredState = 0;
bool getPositionToCaptureRight = 0;
bool getPositionToCaptureLeft = 0;
bool stateMicroMove = 0;
bool stateMicroMove1 = 1;
bool stateMicroMoveForward = 0;

bool microMoveStateLeft = 1;
bool microMoveStateRight = 1;

bool ready = false;
int predSendorData = 0;
int sensorData = 0;
int move_counter = 0;
uint8_t last_movement = 2;

void(*refreshConnectPtr)();

void Connection::delay_at_time(int delay_time) {

    unsigned long start_time = millis();
    while (millis() - start_time < delay_time) {}
}

int read_sensor() {
    sensorData = analogRead(sensorOnePin);
    Serial.println("sensor_data =");
    Serial.println(sensorData);
    return sensorData;
}

void Connection::connectRight() {
    MotorControl::goRight();
    delay_at_time(10);
    MotorControl::stopMovement();
    delay_at_time(300);
    last_movement = 1;  
    Serial.println("move_right");
}

void Connection::connectLeft() {
    MotorControl::goLeft();
    delay_at_time(10);
    MotorControl::stopMovement();
    delay_at_time(300);
    last_movement = 2;  
    Serial.println("move_left"); 
} 

void Connection::initNodeRefresher(void refresh()) {
    refreshConnectPtr = refresh;
}


void Connection::connect(int &state) {

    while (ready != true) {
        refreshConnectPtr();
        read_sensor();
        Serial.println("sensorData");
        Serial.println(sensorData);
        // robotid.data = 9;
        // pubRobotId.publish( &robotid);
        if ((sensorData == 0) && (move_counter < 6)) {
            connectLeft();
            move_counter++;
            Serial.println("111");
        }
        else if ((sensorData == 0) && (move_counter >= 6)) {
            connectRight();
            Serial.println("222");
        }
        else if (sensorData != 0) {
            Serial.println("333");
            if (sensorData > predSendorData) {
                Serial.println("444");
                if (last_movement == 2) {
                    Serial.println("555");
                    connectLeft();
                }
                else {
                    Serial.println("666");
                    connectRight();
                }
            }
            else {
                Serial.println("777");
                
                if (last_movement == 2) {
                    connectRight();
                    ready = true;
                }
                else {
                    connectLeft();
                    ready = true;
                }
            }
        }
        predSendorData = sensorData;
    }
    goForward();
    delay(1500);
    state = 1;
}

void Connection::configured(uint8_t connection_side_id, uint8_t connection_state) {

}

 void Connection::capture() {
     int a;
     int b;
     a = analogRead(34);
     b = analogRead(35);
     Serial.println(a);
     Serial.println(b);
     
 }