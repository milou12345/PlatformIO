#ifndef __LED_H__
#define __LED_H__
#include <Arduino.h>
class LED
{
private:
    byte status;
    byte pin;

public:
    LED(byte pin);
    void switchOn();
    void switchOff();
    void changeState();
    bool getStatus();
};

#endif // __LED_H__