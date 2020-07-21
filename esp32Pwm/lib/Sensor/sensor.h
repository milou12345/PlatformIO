#ifndef __SENSOR_H__
#define __SENSOR_H__
#include <Arduino.h>
class sensor
{
private:
    int  adcValue;
    byte pin;

public:
    sensor(byte pin);
    ~sensor();
};

sensor::sensor(/* args */)
{
}

sensor::~sensor()
{
}

#endif // __SENSOR_H__