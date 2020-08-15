#include "sensor.h"
Sensor::Sensor(byte pin, byte resolutionBit)
{

    this->pin = pin;
    this->resolutionBit = resolutionBit;
    init();
}

void Sensor::init()
{
    pinMode(this->pin, INPUT);
    analogReadResolution(this->pin);
    this->resolution = pow(2, resolutionBit);
    adcValue = 0;
    currentVal = 0;
    voltageRead = 0;
}

double Sensor::getVoltageSensed()
{

    adcValue = analogRead(pin);
    voltageRead = map(adcValue, 0, 4095, 0, 3300) / 1000.0;
    return voltageRead;
}

double Sensor::getCurrentSensed()
{
    adcValue = analogRead(pin);
    currentVal = map(adcValue, 0, 4095, 0, 60000)/ 1000.0;
    return currentVal;
}
