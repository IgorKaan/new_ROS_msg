#ifndef _ROS_RobotMovement_h
#define _ROS_RobotMovement_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

// namespace rosserial_msgs//
// {

  class RobotMovement // : public ros::Msg
  {
    public:
      typedef int16_t _distance_type;
      _distance_type distance;
      typedef int16_t _angle_type;
      _angle_type angle;
      typedef bool _movement_type;
      _movement_type movement;
      typedef bool _rotation_type;
      _rotation_type rotation;

    RobotMovement():
      distance(0),
      angle(0),
      movement(0),
      rotation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle);
      union {
        bool real;
        uint8_t base;
      } u_movement;
      u_movement.real = this->movement;
      *(outbuffer + offset + 0) = (u_movement.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->movement);
      union {
        bool real;
        uint8_t base;
      } u_rotation;
      u_rotation.real = this->rotation;
      *(outbuffer + offset + 0) = (u_rotation.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->rotation);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
      union {
        bool real;
        uint8_t base;
      } u_movement;
      u_movement.base = 0;
      u_movement.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->movement = u_movement.real;
      offset += sizeof(this->movement);
      union {
        bool real;
        uint8_t base;
      } u_rotation;
      u_rotation.base = 0;
      u_rotation.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->rotation = u_rotation.real;
      offset += sizeof(this->rotation);
     return offset;
    }

    const char * getType(){ return "mars/RobotMovement"; };
    const char * getMD5(){ return "e8cce422c0166f0db63d80772d72fe4f"; };

  };

// }
#endif
