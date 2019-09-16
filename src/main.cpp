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

bool stateMove;

unsigned long time11 = 0;

using namespace std_msgs;
using namespace rosserial_msgs;

//unsigned long time1, time2 , time3;

float actionTime;

bool t = 1;

int connFromcenterX,connFromcenterY, connFromsideX, connFromsideY;
int connTocenterX,connTocenterY, connTosideX, connTosideY;
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
uint8_t platformNumber = 9;

bool moveForwardValue = 0;
bool getConnectPosition = 0;
bool configuredSended = 0;
bool rotateValue = 0;

bool stop = 0;
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

// void robotId(const RobotId& msg) {

//   robot_id = msg.robot_id;

// }

ros::Subscriber<ActionAtTime> sub("robot_movement/9", &timeMovementCallback);
ros::Subscriber<ConnectionCfg> subConnectionCfg("connectCfg/9", &connectionCallback);
// ros::Subscriber<FineTuneConnection> subFineConnection("robot_points/0", &pointsCallback);
ros::Subscriber<std_msgs::Int8> connectionState("on_position", &on_connect);

std_msgs::Int8 robotid;
// std_msgs::Int8 robotid2;
// std_msgs::Int8 robotid3;
// std_msgs::Int8 robotid4;

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
  pinMode(34,INPUT);
  pinMode(35,INPUT);
  setupWiFi();
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(subConnectionCfg);
  nh.subscribe(connectionState);
  // pinMode(15, INPUT);
  // ledcSetup(0, 500, 8);
  // ledcAttachPin(25, 0);
  // attachInterrupt(15,isr,CHANGE);
  // sei();
  nh.advertise(pubRobotId);
  // nh.advertise(pubConnected);
  // nh.advertise(pubConfigured);
  // nh.advertise(pubReadyToConnect);
  robotid.data = platformNumber;
  pubRobotId.publish( &robotid );
     
}

void loop() { 

  modulePlatform.goForward();

  // nh.spinOnce();
  // modulePlatform.navigation(moveForwardValue,rotateValue,correctValue, actionTime); 
  // moveForwardValue = 0;
  // rotateValue = 0;
  // correctValue = 0;
  // actionTime = 0;
  // robotid.data = platformNumber;
  // pubRobotId.publish( &robotid);
  // Serial.println("here");
  
  
  // if (stop == 0){

  // if ((connection_side_id != 0 || connection_state !=0) && configuredSended == 0) {

  //   //nh.spinOnce();
  //   robotid.data = platformNumber+20;
  //   pubRobotId.publish(&robotid);
  //   configuredSended = 1;

  // }

  // if ((ready_to_connect == platformNumber) && (getConnectPosition == 0)) {
  //   Serial.println("FUCK1");
  //   robot.connect(state);
  //   if (state == 1) {
  //   //   robot.stopMovement();
  //     robotid.data = platformNumber+30;
  //     pubRobotId.publish(&robotid);
  //   //   Serial.println("state =");
  //   //   Serial.println(state);
  //   }

  //   //  delay(100);
  //   getConnectPosition = 1;
  //   // }
  //   // delay(100000);
      
  // }

  // else if (getConnectPosition == 1) {
  //   Serial.println("SSSSUUKKKKAAAAAAAA");

  //   //nh.spinOnce();
  //   // robot.stopMovement();
  //   //robot.delay_at_time(2000);
  //   // robotid.data = platformNumber+40;
  //   // pubRobotId.publish(&robotid);
  //   Serial.println("gptc");
  //   Serial.println(getConnectPosition);
  //   Serial.println("finish");
  //   Serial.println("state =");
  //   Serial.println(state);
  //   stop = 1;
  // }

  // }
  

}
  

