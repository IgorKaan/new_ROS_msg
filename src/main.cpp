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

using namespace std_msgs;
using namespace rosserial_msgs;

int status = WL_IDLE_STATUS;
int correctValue = 0;
int distance = 0;
float actionTime = 0;

int connTocenterX,connTocenterY, connTosideX, connTosideY;
int connFromcenterX,connFromcenterY, connFromsideX, connFromsideY;

int angle;
int sensor = 0;
int k;
int iprev;
int tick;
int targetTick;
int startPos = 17;

int i;
int ikSensorData = 0;


uint8_t connection_side_id = 0;
uint8_t connection_state = 0;
uint8_t robot_id = 0;
uint8_t platformNumber = 9;

bool rotateValue = 0;
bool moveForwardValue = 0;
uint8_t ready_to_connect = 0;

// const char* ssid = "213_Guest";
// const char* password = "11081975";

const char* ssid = "Keenetic-SPIRAS";
const char* password = "1122334455";

IPAddress server(192, 168, 1, 65); 
IPAddress ip_address;

WiFiClient client;

MotorControl modulePlatform;

Connection robot;

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
  //k = 0;
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
  Serial.print(correctValue);
  Serial.print("\n");
  Serial.print(actionTime);
  Serial.print("\n");
  Serial.print("\n");
}

void connectionCallback(const ConnectionCfg& msg) {
  connection_side_id = msg.connection_side_id;
  connection_state = msg.connection_state;
}

void pointsCallback(const FineTuneConnection& msg) {

  connTocenterX = msg.conn_to.center.x;
  connTocenterY = msg.conn_to.center.y;
  connTosideX = msg.conn_to.side_point.x;
  connTosideY = msg.conn_to.side_point.y;

}

void on_connect(const Int8& msg) {

  ready_to_connect = msg.data;

}

void robotId(const RobotId& msg) {

  robot_id = msg.robot_id;

}

// ros::Subscriber<RobotMovement> sub("robot_movement/9", &movementCallback);


ros::Subscriber<ActionAtTime> sub("robot_movement/9", &timeMovementCallback);
//ros::Subscriber<RobotId> subrobotId("robot_id", &robotId);
ros::Subscriber<ConnectionCfg> subConnectionCfg("connectCfg/9", &connectionCallback);
//ros::Subscriber<RobotKeyPoints> subPoints("robot_points/2", &pointsCallback);
ros::Subscriber<FineTuneConnection> subFineConnection("robot_points/9", &pointsCallback);

ros::Subscriber<std_msgs::Int8> connectionState("on_position", &on_connect);

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

std_msgs::Int8 robotid;
ros::Publisher pubRobotId("connect", &robotid);
ros::Publisher pubConfigured("configured", &robotid);

void setup()
{
    Serial.begin(115200);
    modulePlatform = MotorControl();
    pinMode(34,INPUT);
    pinMode(35,INPUT);
    setupWiFi();
    nh.initNode();
    nh.subscribe(sub);
    //nh.subscribe(subrobotId);
    nh.subscribe(subConnectionCfg);
    nh.subscribe(connectionState);
    // pinMode(15, INPUT);
    // ledcSetup(0, 500, 8);
    // ledcAttachPin(25, 0);
    // attachInterrupt(15,isr,CHANGE);
    // sei();
    nh.advertise(pubRobotId);
    robotid.data = platformNumber;
    pubRobotId.publish( &robotid );
       
}

void loop()
{ 
  //robot.connect();
  //robot.connectLeft();
  //robot.connect();
  //modulePlatform.microMoveLeft();
  // ikSensorData = analogRead(34);
  // Serial.println(ikSensorData);
  // delay(30);
  // if(ikSensorData < 200) {
  //   //modulePlatform.goForward(ikSensorData);  
  // }
  // else {
  //   //modulePlatform.navigation(0,0,0, 0);   
  //   modulePlatform.goForward(0); 
  // }
  nh.spinOnce();
  modulePlatform.navigation(moveForwardValue,rotateValue,correctValue, actionTime); 
  moveForwardValue = 0;
  rotateValue = 0;
  correctValue = 0;
  actionTime = 0;
  robotid.data = platformNumber;
  pubRobotId.publish( &robotid );

  if (connection_side_id != 0 || connection_state !=0) {

    pubConfigured.publish(&robotid);

  }

  if (ready_to_connect == platformNumber) {

    robot.connect();

  }
  
  
}
  

