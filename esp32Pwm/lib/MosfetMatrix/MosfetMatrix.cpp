#include "MosfetMatrix.h"

MosfetMatrix::MosfetMatrix(Mosfet mos1,Mosfet mos2) 
{
    this->mos1=mos1;
    this->mos2=mos2;
    
    switch (mos1.getState()) {
        case 0:
          switchPosition=0;
          break;
        case 1:
          switchPosition=1;
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
        switchPosition=1; //Standart PS

    case 1:
        mos1.switchOff();
        mos2.switchOn();
        switchPosition=0; //HotSwap PS
        break;
    
    default:
        break;
    }
}

byte MosfetMatrix::getSwitchPos() 
{
    return switchPosition;
}
