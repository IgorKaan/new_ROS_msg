#include <WiFi.h>
#include <ros.h>
#include "RobotMovement.h"
#include "ConnectionCfg.h"
#include <Arduino.h>
#include <Wire.h>
#include "math.h"
#include <I2Cdev.h>
#include <MotorControl.h>
#include <Navigation.h>
#include <stdio.h>
#include <HardwareSerial.h>

std::string receivedData;
std::string sign;
std::string angle;
std::string move;
std::string rotate;
std::string finish;

short speed = 100;
int correctValue = 0;
int distance = 0;

uint8_t finishValue = 0;
uint8_t splitindex;
bool rotateValue = 0;
bool moveForwardValue = 0;
uint8_t platformNumber = 201;
uint8_t sensorId;
uint8_t connection_side_id = 0;
uint8_t connection_state = 0;

bool moveSide = true;

const char* ssid = "213_Guest";
const char* password = "11081975";

IPAddress server(192, 168, 1, 44); // ip of your ROS server
IPAddress ip_address;
int status = WL_IDLE_STATUS;

WiFiClient client;

MotorControl GyroRobot;

Navigation Robot;

class WiFiHardware {

  public:
  WiFiHardware() {};

  void init() {
    // do your initialization here. this probably includes TCP server/client setup
    client.connect(server, 11411);
  }

  // read a byte from the serial port. -1 = failure
  int read() {
    // implement this method so that it reads a byte from the TCP connection and returns it
    //  you may return -1 is there is an error; for example if the TCP connection is not open
    return client.read();         //will return -1 when it will works
  }

  // write data to the connection to ROS
  void write(uint8_t* data, int length) {
    // implement this so that it takes the arguments and writes or prints them to the TCP connection
    for(int i=0; i<length; i++)
      client.write(data[i]);
  }

  // returns milliseconds since start of program
  unsigned long time() {
     return millis(); // easy; did this one for you
  }
};

void movementCallback(const RobotMovement& msg) {
  correctValue = msg.angle;
  moveForwardValue = msg.movement;
  rotateValue = msg.rotation;
  distance = msg.distance;
  Serial.print(correctValue);
  Serial.print("\n");
  Serial.print(moveForwardValue);
  Serial.print("\n");
  Serial.print(rotateValue);
  Serial.print("\n");
  Serial.print("\n");
}

void connectionCallback(const ConnectionCfg& msg) {
  connection_side_id = msg.connection_side_id;
  connection_state = msg.connection_state;
  Serial.print(connection_side_id);
  Serial.print("\n");
  Serial.print(connection_state);
  Serial.print("\n");
  Serial.print("\n");
}

ros::Subscriber<RobotMovement> sub("robot_movement", &movementCallback);
ros::Subscriber<ConnectionCfg> sub_1("robot_movement1", &connectionCallback);
ros::NodeHandle_<WiFiHardware> nh;

void setupWiFi()
{
  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 2000) delay(500);
  if(i == 2001){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  Serial.print("Ready! Use ");
  Serial.print(WiFi.localIP());
  Serial.println(" to access client");
}

void setup()
{
    Serial.begin(115200);
    GyroRobot = MotorControl();
    setupWiFi();
    nh.initNode();
    nh.subscribe(sub);
    nh.subscribe(sub_1);
}

void loop()
{
    nh.spinOnce();
    
    if (correctValue <= 45 && correctValue >= -45 && moveForwardValue == 1 && rotateValue == 0 && finishValue == 0) {
        GyroRobot.goForward(distance);        
    }
    else if ((correctValue >= 135 || correctValue <= -135) && moveForwardValue == 1 && rotateValue == 0 && finishValue == 0) {
        GyroRobot.goBackward(distance);        
    } 
    else if (correctValue > 45 && correctValue < 135 && moveForwardValue == 1 && rotateValue == 0 && finishValue == 0) {
        GyroRobot.goRight(distance);        
    }
    else if ((correctValue < -45 && correctValue > -135) && moveForwardValue == 1 && rotateValue == 0 && finishValue == 0) {
        GyroRobot.goLeft(distance);        
    } 
    else if (moveForwardValue == 0 && rotateValue == 0)
    {
        GyroRobot.stopMovement();
    }
    else if (rotateValue == 1 && finishValue == 0) {

        if (correctValue > 0) {
            GyroRobot.turnRight(correctValue);
        }
        else if (correctValue < 0) {
            GyroRobot.turnLeft(correctValue);
    }
      else if ((abs(correctValue)<=3) && distance<=5) {
        GyroRobot.stopMovement();
        delay(5000);
    }

        // if (correctValue <= 45 && correctValue >= 0) {
        //     GyroRobot.turnRight(speed);
        // }
        // else if (correctValue >= -45 && correctValue <= 0) {
        //     GyroRobot.turnLeft(speed);
        // }
        // else if (correctValue >= 135) {
        //     GyroRobot.turnLeft(speed);       
        // }
        // else if (correctValue <= -135) {
        //     GyroRobot.turnRight(speed);
        // }
        // else if (correctValue > 45 && correctValue < 90) {
        //     GyroRobot.turnLeft(speed);
        // }
        // else if (correctValue >= 90 && correctValue < 135) {
        //     GyroRobot.turnRight(speed);
        // }
        // else if (correctValue < -45 && correctValue >= -90) {
        //     GyroRobot.turnRight(speed);
        // }
        // else if (correctValue < -90 && correctValue >= -135) {
        //     GyroRobot.turnLeft(speed);
        // }
        else if (moveForwardValue == 0 && rotateValue == 0)
        {
        GyroRobot.stopMovement();
        }
    }
  delay(20);
}
  

