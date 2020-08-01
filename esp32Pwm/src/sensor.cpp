#include "sensor.h"
Sensor::Sensor(byte pin, byte resolutionBit) 
{

    this->pin=pin;
    this->resolutionBit=resolutionBit;
    init();
}

void Sensor::init() 
{
    pinMode(pin, INPUT);
    adcValue=analogRead(pin);
    this->resolution=pow(2,resolutionBit);
    map(adcValue,0,resolution-1,0,3.3);
}

int Sensor::getSensorValue() 
{
    adcValue=analogRead(pin);
    return adcValue;
}
