#include "LED.h"

LED::LED(byte pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
    status = 0;
}

void LED::switchOn()
{
    status = 1;
    digitalWrite(pin, status);
}

void LED::switchOFf()
{
    status = 0;
    digitalWrite(pin, status);
}

void LED::changeState()
{
    switch (status)
    {
    case 1:
        switchOFf();

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
