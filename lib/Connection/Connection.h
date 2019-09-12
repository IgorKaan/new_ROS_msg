#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <MotorControl.h>

class Connection : public MotorControl
{
    public:

    void connect();

    void connectRight();

    void connectLeft();

    void capture();

    void setup();

    struct sensor
    {
        short sensor1_data;
        short sensor2_data;
        bool sensor3_data;
        bool sensor4_data;
    };
    

    private:

};

#endif