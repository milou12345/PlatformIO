#ifndef __SENSOR_H__
#define __SENSOR_H__
#include <Arduino.h>

class Sensor
{
private:
    byte resolutionBit;
    byte resolution;
    int adcValue;
    byte pin;
    int currentVal;


public:
    Sensor(byte pin, byte resolutionBit);
    void init();
    int getSensorValue();
};
#endif