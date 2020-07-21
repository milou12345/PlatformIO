#include "sensor.h"
Sensor::Sensor(byte pin) 
{
    this->pin=pin;
    init();
}

void Sensor::init() 
{
    pinMode(pin, INPUT);
    adcValue=analogRead(pin);

}

int Sensor::getSensorValue() 
{
    adcValue=analogRead(pin);
    return adcValue;
}
