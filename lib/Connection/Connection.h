#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <MotorControl.h>

class Connection : public MotorControl
{
    public:

    void connectForward(int &state);

    void connectBackward(int &state);

    void configured(uint8_t connection_side_id, uint8_t connection_state);

    void connectRight();

    void connectLeft();

    void delay_at_time(int delay_time);

    void capture();

    void initNodeRefresher(void refresh());

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