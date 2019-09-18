#include "FineTuneConnection.h"
#include <std_msgs/String.h>
#include "RobotKeyPoints.h"
#include <std_msgs/Bool.h>
#include "RobotMovement.h"
#include "ConnectionCfg.h"
#include <std_msgs/Int8.h>
#include "ActionAtTime.h"
#include <MotorControl.h>
#include <Connection.h>
#include <Arduino.h>
#include "RobotId.h"
#include <sstream>
#include <WiFi.h>
#include "Bool.h"
#include <ros.h>

bool grubLeftFinish = 0;
bool grubRightFinish = 0;

using namespace std_msgs;
using namespace rosserial_msgs;

//unsigned long time1, time2 , time3;

float actionTime;

int status = WL_IDLE_STATUS;
int startPos = 17;
int ikSensorData;
int correctValue;
int targetTick;
int distance;
int angle;
int sensor;
int iprev;
int tick;
int i;
int k;
int state;

uint8_t connection_side_id = 0;
uint8_t connection_state = 0;
uint8_t ready_to_connect = -1;
uint8_t platformNumber = 7;
uint8_t grubState = 0;

bool moveForwardValue = 0;
bool getConnectPosition = 0;
bool configuredSended = 0;
bool rotateValue = 0;
// const char* ssid = "213_Guest";
// const char* password = "11081975";

const char* ssid = "Keenetic-SPIRAS";
const char* password = "1122334455";

IPAddress server(192, 168, 1, 65); 
IPAddress ip_address;

MotorControl modulePlatform;
WiFiClient client;
Connection robot;

class WiFiHardware {

  public:
  WiFiHardware() {};

  void init() {
  
    client.connect(server, 11411);

  }

  // read a byte from the serial port. -1 = failure
  int read() {

    return client.read(); 

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

void hall() {

  i++;
  k = k + i;
  Serial.println(i);
  Serial.println(k);
  i = 0;

}

void IRAM_ATTR isr() {

  hall();

}

void rotateToAngle(int angle) {

  tick = map(angle, -90, 90, 0, 34);
  targetTick = tick - startPos;
  if (targetTick > 0) {
   while (k < targetTick) {
    ledcWrite(0,220);               
   }
   ledcWrite(0,190);
  } 
  startPos = tick;

}

void timeMovementCallback(const ActionAtTime& msg) {

  correctValue = msg.angle;
  moveForwardValue = msg.movement;
  rotateValue = msg.rotation;
  actionTime = msg.time;
  
}

void grubCallback(const Int8& msg) {

  grubState = msg.data;

}

void connectionCallback(const ConnectionCfg& msg) {

  connection_side_id = msg.connection_side_id;
  connection_state = msg.connection_state;

}

void on_connect(const Int8& msg) {

  ready_to_connect = msg.data;

}

ros::Subscriber<ActionAtTime> sub("robot_movement/7", &timeMovementCallback);
ros::Subscriber<ConnectionCfg> subConnectionCfg("connectCfg/7", &connectionCallback);
ros::Subscriber<std_msgs::Int8> connectionState("on_position", &on_connect);
ros::Subscriber<std_msgs::Int8> grubGfg("grub/7", &grubCallback);

std_msgs::Int8 robotid;

ros::Publisher pubRobotId("robot_id", &robotid);


// ros::Publisher pubReadyToConnect("ready_to_connect", &robotid);
// ros::Publisher pubRobotId("connected_to_ros", &robotid2);
// ros::Publisher pubConfigured("configured", &robotid3);
// ros::Publisher pubConnected("connected", &robotid4);

ros::NodeHandle_<WiFiHardware> nh;

void setupWiFi() {

  WiFi.begin(ssid, password);
  Serial.print("\nConnecting to "); Serial.println(ssid);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20000) delay(500);
  if(i == 2001){
    Serial.print("Could not connect to"); Serial.println(ssid);
    while(1) delay(500);
  }
  Serial.print("Ready! Use ");
  Serial.print(WiFi.localIP());
  Serial.println(" to access client");

}

void refreshConnection() {

  nh.spinOnce();
  robotid.data = platformNumber;
  pubRobotId.publish(&robotid);
  Serial.println("refresh");

}


void setup() {

  Serial.begin(115200);
  modulePlatform = MotorControl();
  robot.initNodeRefresher(refreshConnection);
  // setupWiFi();
  // nh.initNode();
  // nh.subscribe(sub);
  // nh.subscribe(subConnectionCfg);
  // nh.subscribe(connectionState);
  // nh.subscribe(grubGfg);
  pinMode(15, INPUT);
  ledcSetup(0, 50, 11);
  ledcAttachPin(12, 0);
  attachInterrupt(15,isr,CHANGE);
  sei();
  nh.advertise(pubRobotId);
  robotid.data = platformNumber;
  pubRobotId.publish( &robotid );
     
}

void loop() { 

  modulePlatform.goForward(20);
  delay(2500);
  robot.leftGrabRelease();
  robot.rightGrabRelease();
  delay(2500);
  robot.leftGrabCapture();
  robot.rightGrabCapture();
  delay(2500);
  robot.leftGrabRelease();
  robot.rightGrabRelease();
  delay(2500);
  // nh.spinOnce();
  // modulePlatform.navigation(moveForwardValue,rotateValue,correctValue, actionTime); 
  // moveForwardValue = 0;
  // rotateValue = 0;
  // correctValue = 0;
  // actionTime = 0;
  // robotid.data = platformNumber;
  // pubRobotId.publish( &robotid);
  // Serial.println("here");
  
  // if ((connection_side_id != 0 || connection_state !=0) && configuredSended == 0) {

  //   robotid.data = platformNumber+20;
  //   pubRobotId.publish(&robotid);
  //   configuredSended = 1;

  // }

  // if ((ready_to_connect == platformNumber) && (getConnectPosition == 0)) {

  //   modulePlatform.goForward(25);
  //   delay(1500);
  //   state = 1;
  //   if (state == 1) {
  //     robot.stopMovement();
  //     robotid.data = platformNumber+30;
  //     pubRobotId.publish(&robotid);
  //   }
  //   getConnectPosition = 1;
    
  // }

  // if ((grubState == 1) && (grubLeftFinish == 0)) {

  //     robot.leftGrabCapture();
  //     delay(2500);
  //     robot.leftGrabStop();
  //     delay(10000);
  //     robot.leftGrabRelease();
  //     delay(2500);
  //     robot.leftGrabStop();
  //     grubLeftFinish = 1;
  //     robotid.data = platformNumber+40;
  //     pubRobotId.publish(&robotid);
  //   }

  // else if ((grubState == 2) && (grubRightFinish == 0)) {

  //     robot.rightGrabCapture();
  //     delay(2500);
  //     robot.rightGrabStop();
  //     delay(10000);
  //     robot.rightGrabRelease();
  //     delay(2500);
  //     robot.rightGrabStop();
  //     grubRightFinish = 1;
  //     robotid.data = platformNumber+40;
  //     pubRobotId.publish(&robotid);
  // }

}
  

