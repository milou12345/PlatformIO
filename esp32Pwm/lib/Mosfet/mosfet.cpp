#include "mosfet.h"
Mosfet::Mosfet(byte pin) 
{
    this->pin=pin;
    init();
}

void Mosfet::init() 
{
    pinMode(pin, OUTPUT);
    switchOff();
}

void Mosfet::switchOn() 
{
    digitalWrite(pin, HIGH);  
    state=1; 
}

void Mosfet::switchOff() 
{
    digitalWrite(pin, LOW); 
    state=0;
}

byte Mosfet::getState() 
{
    return state;
}
