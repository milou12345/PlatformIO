#ifndef __SENSOR_H__
#define __SENSOR_H__
#include <Arduino.h>
#include "define.h"
#define DCCT_MAX_CURRENT 60
#define DCCT_MAX_VOLTAG 10

class Sensor
{
private:
    byte resolutionBit;
    byte resolution;
    int adcValue;
    byte pin;
    double currentVal;
    double voltageRead;


public:
    Sensor(byte pin, byte resolutionBit);
    void init();
    double getVoltageSensed();
    double getCurrentSensed();
};
#endif