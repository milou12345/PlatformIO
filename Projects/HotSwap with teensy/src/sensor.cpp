#include "sensor.h"
Sensor::Sensor(byte pin, byte resolutionBit)
{

    this->pin = pin;
    this->resolutionBit = resolutionBit;
    init();
}

void Sensor::init()
{
    pinMode(pin, INPUT);
    this->resolution = pow(2, resolutionBit);
    adcValue = 0;
    currentVal = 0;
    voltageRead = 0;
}

double Sensor::getVoltageSensed()
{

    adcValue = analogRead(pin);
    voltageRead = map(adcValue, 0, resolution - 1, 0, VDD);
    return voltageRead;
}

double Sensor::getCurrentSensed()
{
    adcValue = analogRead(pin);
    voltageRead = map(adcValue, 0, resolution - 1, 0, VDD);
    currentVal = map(voltageRead, 0, DCCT_MAX_VOLTAG, 0, DCCT_MAX_CURRENT);
    return currentVal;
}
