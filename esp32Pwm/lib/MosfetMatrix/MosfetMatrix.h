#ifndef __MOSFETMATRIX_H__
#define __MOSFETMATRIX_H__ 
#include <Arduino.h>
#include <mosfet.h>

class MosfetMatrix
{
private:
Mosfet mos1;
Mosfet mos2;
byte switchPosition; // Which switch combination is conduction

public:
    MosfetMatrix(byte pin1,byte pin2);
    void switchPS();
    void switchToPS1();
    void switchToPS2();
    byte getSwitchPos();
};

#endif // __MOSFETMATRIX_H__