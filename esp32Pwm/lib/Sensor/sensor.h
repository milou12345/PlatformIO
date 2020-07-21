#ifndef __SENSOR_H__
#define __SENSOR_H__
#include <Arduino.h>

class Sensor
{
private:
    int adcValue;
    byte pin;
public:
    Sensor(byte pin);
    void init();
    int getSensorValue();
};
#endif 