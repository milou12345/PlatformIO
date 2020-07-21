#include "MosfetMatrix.h"

MosfetMatrix::MosfetMatrix(byte pin1, byte pin2)
{

    mos1 = Mosfet(pin1);
    mos2 = Mosfet(pin2);
    this.

    switch (mos1.getState())
    {
    case 0:
        switchPosition = 0;
        break;
    case 1:
        switchPosition = 1;
        break;
    default:
        break;
    }
}

void MosfetMatrix::switchPS()
{
    switch (mos1.getState())
    {

    case 0:
        mos1.switchOn();
        mos2.switchOff();
        switchPosition = 1; //Standart PS

    case 1:
        mos1.switchOff();
        mos2.switchOn();
        switchPosition = 0; //HotSwap PS
        break;

    default:
        break;
    }
}

void MosfetMatrix::switchToPS1()
{
    mos1.switchOn();
    mos2.switchOff();
    switchPosition = 1;
}

void MosfetMatrix::switchToPS2()
{
    mos1.switchOff();
    mos2.switchOn();
    switchPosition = 0;
}

byte MosfetMatrix::getSwitchPos()
{
    return switchPosition;
}

bool isHotSwapEnable()
{
    return this.hotSwapEnable;
}

void setHotSwapEnable(bool hotSwapEnable)
{
    this.hotSwapEnable = hotSwapEnable;
}