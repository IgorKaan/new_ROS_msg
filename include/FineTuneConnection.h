#ifndef _ROS_rosserial_msgs_FineTuneConnection_h
#define _ROS_rosserial_msgs_FineTuneConnection_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "RobotKeyPoints.h"

namespace rosserial_msgs
{

  class FineTuneConnection : public ros::Msg
  {
    public:
      typedef rosserial_msgs::RobotKeyPoints _conn_to_type;
      _conn_to_type conn_to;
      typedef rosserial_msgs::RobotKeyPoints _conn_from_type;
      _conn_from_type conn_from;

    FineTuneConnection():
      conn_to(),
      conn_from()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->conn_to.serialize(outbuffer + offset);
      offset += this->conn_from.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->conn_to.deserialize(inbuffer + offset);
      offset += this->conn_from.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rosserial_msgs/FineTuneConnection"; };
    const char * getMD5(){ return "9917973bb51ce8420b60baf66dff5fc8"; };

  };

}
#endif
