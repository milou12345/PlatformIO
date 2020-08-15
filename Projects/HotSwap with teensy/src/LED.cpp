#include "LED.h"

LED::LED(byte pin)
{
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
    this->status = 0;
}

void LED::switchOn()
{
    if (this->status == 0)
    {
        this->status = 1;
        digitalWrite(this->pin, HIGH);
    }
}

void LED::switchOff()
{
    if (status == 1)
    {
        status = 0;
        digitalWrite(pin, LOW);
    }
}

void LED::changeState()
{
    switch (status)
    {
    case 1:
        switchOff();

        break;

    default:
        switchOn();
        break;
    }
}

bool LED::getStatus()
{
    return status;
}
