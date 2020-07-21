#ifndef __MOSFETMATRIX_H__
#define __MOSFETMATRIX_H__
#include "mosfet.h"
class MosfetMatrix
{
private:
Mosfet mos1;
Mosfet mos2;
byte switchPosition; // Which switch combination is conduction

public:
    MosfetMatrix(Mosfet mos1,Mosfet mos2);
    void switchPS();
    byte getSwitchPos();
};

#endif // __MOSFETMATRIX_H__