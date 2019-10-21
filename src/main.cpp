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
int sensor, s2, s3, s4;
int iprev;
int tick;
int i;
int k;
int state;

uint8_t connection_side_id = -1;
uint8_t connection_state = -1;
uint8_t ready_to_connect = -1;
uint8_t platformNumber = 2;
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
  //Serial.println(i);
  Serial.println("k=");
  Serial.println(k);
  i = 0;

}

void IRAM_ATTR isr() {

  hall();

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

void reconfigurationCallback(const Int8& msg) {

  angle = msg.data;
  Serial.println(angle);

}

void on_connect(const Int8& msg) {

  ready_to_connect = msg.data;

}

ros::Subscriber<ActionAtTime> sub("robot_movement/2", &timeMovementCallback);
ros::Subscriber<ConnectionCfg> subConnectionCfg("connectCfg/2", &connectionCallback);
ros::Subscriber<std_msgs::Int8> axialBribge("reconfiguration/2", &reconfigurationCallback);
ros::Subscriber<std_msgs::Int8> connectionState("on_position", &on_connect);
ros::Subscriber<std_msgs::Int8> grubGfg("grub/2", &grubCallback);

std_msgs::Int8 robotid;

ros::Publisher pubRobotId("robot_id", &robotid);


// ros::Publisher pubReadyToConnect("ready_to_connect", &robotid);
// ros::Publisher pubRobotId("connected_to_ros", &robotid2);
// ros::Publisher pubConfigured("configured", &robotid3);
// ros::Publisher pubConnected("connected", &robotid4);

ros::NodeHandle_<WiFiHardware> nh;

void refreshConnection() {

  nh.spinOnce();
  robotid.data = platformNumber;
  pubRobotId.publish(&robotid);
  Serial.println("refresh");

}

void rotateToAngleDown(int angle) {

  tick = abs(angle/5);
  k = 0;
  while (k < tick)
  {
    refreshConnection();
    ledcWrite(0,180);
  }
  if (k >= tick) {

    ledcWrite(0, 150);
  }
}

void rotateToAngleUp(int angle) {
  tick = angle/5;
  k = 0;
  while (k < tick)
  {
    refreshConnection();
    ledcWrite(0,120);
  }
  if (k >= tick) {

    ledcWrite(0, 150);
  }
  
}

void setupWiFi() {

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


void setup() {

  Serial.begin(115200);
  modulePlatform = MotorControl();
  // robot.initNodeRefresher(refreshConnection);
  // setupWiFi();
  // nh.initNode();
  // nh.subscribe(sub);
  // nh.subscribe(subConnectionCfg);
  // nh.subscribe(connectionState);
  // nh.subscribe(grubGfg);
  // nh.subscribe(axialBribge);
  // pinMode(27, INPUT);
  // ledcSetup(0, 50, 11);
  // ledcAttachPin(12, 0);
  // attachInterrupt(27,isr,CHANGE);
  // sei();
  // nh.advertise(pubRobotId);
  // robotid.data = platformNumber;
  // pubRobotId.publish( &robotid );
     
}

void loop() { 
  // // robot.connectForward(state);
  // // delay(300);
  // // // sensor = analogRead(34);
  // // s2 = analogRead(32);
  // // s3 = analogRead(33);
  // // // s4 = analogRead(35);
  // // Serial.println("s2-----------------------");
  // // Serial.println(s2);
  // // Serial.println("s3-----------------------");
  // // Serial.println(s3);
  // // delay(500);
  // // //Serial.println(s4);
  // // //Serial.println(sensor);
  // // delay(100);
  // // modulePlatform.goForward(30);
  // // rotateToAngleDown(90);
  // // delay(3000);
  // nh.spinOnce();
  // modulePlatform.navigation(moveForwardValue,rotateValue,correctValue, actionTime); 
  // moveForwardValue = 0;
  // rotateValue = 0;
  // correctValue = 0;
  // actionTime = 0;
  // robotid.data = platformNumber;
  // pubRobotId.publish( &robotid);
  // //Serial.println("here");
  
  // if ((connection_side_id != -1 || connection_state != -1) && configuredSended == 0) {

  //   if ((connection_side_id == 1) && (connection_state == 0)) {

  //     modulePlatform.rightGrabRelease();
  //     delay(2500);
  //     modulePlatform.rightGrabStop();
  //     robotid.data = platformNumber+20;
  //     pubRobotId.publish(&robotid);
  //     connection_side_id = -1;
  //     connection_state = -1;

  //   }
  //   if ((connection_side_id == 1) && (connection_state == 1)) {

  //     modulePlatform.rightGrabCapture();
  //     delay(2500);
  //     modulePlatform.rightGrabStop();
  //     robotid.data = platformNumber+20;
  //     pubRobotId.publish(&robotid);
  //     connection_side_id = -1;
  //     connection_state = -1;

  //   }
  //   if ((connection_side_id == 3) && (connection_state == 0)) {

  //     modulePlatform.leftGrabRelease();
  //     delay(2500);
  //     modulePlatform.leftGrabStop();
  //     robotid.data = platformNumber+20;
  //     pubRobotId.publish(&robotid);
  //     connection_side_id = -1;
  //     connection_state = -1;

  //   }
  //   if ((connection_side_id == 3) && (connection_state == 1)) {

  //     modulePlatform.leftGrabCapture();
  //     delay(2500);
  //     modulePlatform.leftGrabStop();
  //     robotid.data = platformNumber+20;
  //     pubRobotId.publish(&robotid);
  //     connection_side_id = -1;
  //     connection_state = -1;

  //   }

  //   else if ((connection_side_id == 0) || (connection_side_id == 2)) {

  //     delay(2500);
  //     robotid.data = platformNumber+20;
  //     pubRobotId.publish(&robotid);
  //     connection_side_id = -1;
  //     connection_state = -1;

  //   }
    
  //   //configuredSended = 1;

  // }

  // if ((ready_to_connect == platformNumber) && (getConnectPosition == 0)) {

  //   //modulePlatform.goForward(25);
  //   robot.connectForward(state);
  //   //delay(1500);
  //   //state = 1;
  //   if (state == 1) {
  //     robot.stopMovement();
  //     robotid.data = platformNumber+30;
  //     pubRobotId.publish(&robotid);
  //   }
  //   getConnectPosition = 1;
    
  // }

  // if ((grubState == 1) && (grubLeftFinish == 0)) {

  //   modulePlatform.leftGrabCapture();
  //   delay(2500);
  //   modulePlatform.leftGrabStop();
  //   grubLeftFinish = 1;
  //   //robotid.data = platformNumber+40;
  //   pubRobotId.publish(&robotid);
  // }

  // if ((grubState == 2) && (grubRightFinish == 0)) {

  //   modulePlatform.rightGrabCapture();
  //   delay(2500);
  //   modulePlatform.rightGrabStop();
  //   grubRightFinish = 1;
  //   //robotid.data = platformNumber+40;
  //   pubRobotId.publish(&robotid);
  // }

  // if ((angle <= 90) && (angle > 0)) {

  //   rotateToAngleUp(angle);
  //   //Serial.println(angle);
  //   //delay(2500);
  //   angle = 0;

  // }

  // if ((angle >= -90) && (angle < 0)) {

  //   Serial.println("121451252");
  //   rotateToAngleDown(angle);
  //   //delay(2500);
  //   angle = 0;
  // }
  // Serial.println(angle);
  modulePlatform.goForward(21);
  delay(3000);
  modulePlatform.goRight();
  delay(3000);
  modulePlatform.goBackward(21);
  delay(3000);
  modulePlatform.goLeft();
  delay(3000);
  modulePlatform.turnLeft();
  delay(3000);
  modulePlatform.turnRight();
  delay(3000);


}
  

