#ifndef MY_MOSFET_H
#define MY_MOSFET_H
#include <Arduino.h>
class Mosfet {
  
  private:
    byte pin;
    byte state;
    
  public:
    Mosfet(byte pin);
    Mosfet();
    void init();
    void switchOn();
    void switchOff();
    byte getState();
    
};
#endif