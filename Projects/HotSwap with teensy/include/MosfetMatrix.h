#ifndef __MOSFETMATRIX_H__
#define __MOSFETMATRIX_H__
#include <Arduino.h>
#include <mosfet.h>
#include "PID_v1.h"
class MosfetMatrix
{
private:
    bool hotSwapEnable;

    byte switchPosition; // Which switch combination is conduction

public:
    Mosfet mos1;
    Mosfet mos2;
    MosfetMatrix(byte pin1, byte pin2);
    void switchPS();
    void switchToPS1();
    void switchToPS2();
    
    byte getSwitchPos();
    bool getHotSwapEnable();
    void setHotSwapEnable();
};

#endif // __MOSFETMATRIX_H__