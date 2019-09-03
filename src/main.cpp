#include <std_msgs/String.h>
#include "RobotMovement.h"
#include "ConnectionCfg.h"
#include "ActionAtTime.h"
#include <MotorControl.h>
#include <Connection.h>
#include <Arduino.h>
#include <sstream>
#include <WiFi.h>
#include "Bool.h"
#include <ros.h>

using namespace std_msgs;

int status = WL_IDLE_STATUS;
int correctValue = 0;
int distance = 0;
float actionTime = 0;

short a,b,c;
bool flag = 1;
//bool* flag;

uint8_t connection_side_id = 0;
uint8_t connection_state = 0;

bool rotateValue = 0;
bool moveForwardValue = 0;

// const char* ssid = "213_Guest";
// const char* password = "11081975";

const char* ssid = "Keenetic-SPIRAS";
const char* password = "1122334455";

IPAddress server(192, 168, 1, 65); 
IPAddress ip_address;

WiFiClient client;

MotorControl modulePlatform;

Connection robot;

//Connection* Robot1;

class WiFiHardware {

  public:
  WiFiHardware() {};

  void init() {
  
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
  
  //ROS_INFO_STREAM(ros::Time::now() - msg->header.stamp);
}

// void connectData(const Bool& msg) {
//   correctValue = msg.data;
// }

void timeMovementCallback(const ActionAtTime& msg) {
  correctValue = msg.angle;
  moveForwardValue = msg.movement;
  rotateValue = msg.rotation;
  actionTime = msg.time;
  Serial.print(correctValue);
  Serial.print("\n");
  Serial.print(actionTime);
  Serial.print("\n");
  Serial.print("\n");
  //flag = 1;
  //ROS_INFO_STREAM(ros::Time::now() - msg->header.stamp);
}

void connectionCallback(const ConnectionCfg& msg) {
  connection_side_id = msg.connection_side_id;
  connection_state = msg.connection_state;
  // Serial.print(connection_side_id);
  // Serial.print("\n");
  // Serial.print(connection_state);
  // Serial.print("\n");
  // Serial.print("\n");
}

// ros::Subscriber<RobotMovement> sub("robot_movement/9", &movementCallback);
// ros::Subscriber<ConnectionCfg> sub_1("connect", &connectionCallback);

ros::Subscriber<ActionAtTime> sub("robot_movement/0", &timeMovementCallback);
ros::NodeHandle_<WiFiHardware> nh;
// ros::NodeHandle_<WiFiHardware> n;
//ros::Publisher pub = nh.advertise<std_msgs::Bool>("robotConnect", 1000);
// std_msgs::String str;
// str.data = "hello world";
// pub.publish(str);
   

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
    modulePlatform = MotorControl();
    setupWiFi();
    nh.initNode();
    nh.subscribe(sub);
    //nh.subscribe(sub_1);
    //nh.publish(1,"2424");
    
}

void loop()
{ 
  
  nh.spinOnce();
  modulePlatform.navigation(moveForwardValue,rotateValue,correctValue, actionTime); 
  moveForwardValue = 0;
  rotateValue = 0;
  correctValue = 0;
  actionTime = 0;
    // modulePlatform.navigation(1,0,15, 5000, &flag); 
    // Serial.println(flag);
  // modulePlatform.navigation(1,0,15, 10000); 
  //modulePlatform.navigation(0,0,0,0);
  // modulePlatform.navigation(0,1,15, 8500, flag);
  //modulePlatform.goForward(50);
}
  

