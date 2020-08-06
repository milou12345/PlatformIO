#ifndef __LED_H__
#define __LED_H__
#include <Arduino.h>
class LED
{
private:
    byte status;
    bool pin;

public:
    LED(byte pin);
    void switchOn();
    void switchOFf();
    void changeState();
    bool getStatus();
};

#endif // __LED_H__