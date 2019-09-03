#ifndef _ROS_rosserial_msgs_ActionAtTime_h
#define _ROS_rosserial_msgs_ActionAtTime_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"



  class ActionAtTime
  {
    public:
      typedef float _time_type;
      _time_type time;
      typedef int16_t _angle_type;
      _angle_type angle;
      typedef bool _movement_type;
      _movement_type movement;
      typedef bool _rotation_type;
      _rotation_type rotation;

    ActionAtTime():
      time(0),
      angle(0),
      movement(0),
      rotation(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
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
        float real;
        uint32_t base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time = u_time.real;
      offset += sizeof(this->time);
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

    const char * getType(){ return "mars/ActionAtTime"; };
    const char * getMD5(){ return "c8cc7a98db3f18232eb7cf6bb727fbf0"; };

  };
#endif
