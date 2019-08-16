#ifndef _ROS_ConnectionCfg_h
#define _ROS_ConnectionCfg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

// namespace rosserial_msgs
// {

  class ConnectionCfg
  {
    public:
      typedef int8_t _connection_side_id_type;
      _connection_side_id_type connection_side_id;
      typedef int8_t _connection_state_type;
      _connection_state_type connection_state;

    ConnectionCfg():
      connection_side_id(0),
      connection_state(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_connection_side_id;
      u_connection_side_id.real = this->connection_side_id;
      *(outbuffer + offset + 0) = (u_connection_side_id.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connection_side_id);
      union {
        int8_t real;
        uint8_t base;
      } u_connection_state;
      u_connection_state.real = this->connection_state;
      *(outbuffer + offset + 0) = (u_connection_state.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->connection_state);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int8_t real;
        uint8_t base;
      } u_connection_side_id;
      u_connection_side_id.base = 0;
      u_connection_side_id.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connection_side_id = u_connection_side_id.real;
      offset += sizeof(this->connection_side_id);
      union {
        int8_t real;
        uint8_t base;
      } u_connection_state;
      u_connection_state.base = 0;
      u_connection_state.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->connection_state = u_connection_state.real;
      offset += sizeof(this->connection_state);
     return offset;
    }

    const char * getType(){ return "rosserial_python/ConnectionCfg"; };
    const char * getMD5(){ return "eb72a1fce3a16fd32230a82c22b6cc63"; };

  };

//}
#endif
