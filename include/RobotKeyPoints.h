#ifndef _ROS_rosserial_msgs_RobotKeyPoints_h
#define _ROS_rosserial_msgs_RobotKeyPoints_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "Point2d.h"
// #include "rosserial_msgs/Point2d.h"

namespace rosserial_msgs
{

  class RobotKeyPoints : public ros::Msg
  {
    public:
      typedef rosserial_msgs::Point2d _center_type;
      _center_type center;
      typedef rosserial_msgs::Point2d _side_point_type;
      _side_point_type side_point;

    RobotKeyPoints():
      center(),
      side_point()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->center.serialize(outbuffer + offset);
      offset += this->side_point.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->center.deserialize(inbuffer + offset);
      offset += this->side_point.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rosserial_msgs/RobotKyePoints"; };
    const char * getMD5(){ return "fea57d0b3a12d3693e07fea59ee374f9"; };

  };

}
#endif
