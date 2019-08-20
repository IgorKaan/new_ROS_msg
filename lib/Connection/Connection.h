#ifndef CONNECTION_H
#define CONNECTION_H

#include <Arduino.h>
#include <MotorControl.h>

class Connection : public MotorControl
{
    public:

    void Connect(short aDistaance, short bDictacnce, short cDistance);

    void Capture();

    private:

};

#endif