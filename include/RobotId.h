#ifndef _ROS_rosserial_msgs_RobotId_h
#define _ROS_rosserial_msgs_RobotId_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosserial_msgs
{

  class RobotId : public ros::Msg
  {
    public:
      typedef int8_t _robot_id_type;
      _robot_id_type robot_id;

    RobotId():
      robot_id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_robot_id;
      u_robot_id.real = this->robot_id;
      *(outbuffer + offset + 0) = (u_robot_id.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->robot_id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_robot_id;
      u_robot_id.base = 0;
      u_robot_id.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->robot_id = u_robot_id.real;
      offset += sizeof(this->robot_id);
     return offset;
    }

    const char * getType(){ return "rosserial_msgs/RobotId"; };
    const char * getMD5(){ return "1328874702d4d4dc05502772826507bb"; };

  };

}
#endif
