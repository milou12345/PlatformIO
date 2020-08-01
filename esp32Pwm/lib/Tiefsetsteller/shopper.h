#ifndef __SHOPPER_H__
#define __SHOPPER_H__
#include "Arduino.h"
#include "PID_v1.h"
#define ledChannel 0
#define resolution 8

class shopper
{
private:
    byte freq; // Frequenz in 1/s
    byte dutyCyle; // 0-100 
    byte iSoll; // Sollwirt des Stromes
    byte iIst; //Istwert des Stromes
    byte pwmPin; // Pin für Ausgabe der PWM
    PID cuurentPID; //PID controler


public:
    shopper(byte pwmPin,byte freq);
    void init();
    void setDutyCyle(byte dutyCyle);
    void currentControler(double Input, &Output, &Setpoint, Kp, Ki, Kd)
};




#endif // __SHOPPER_H__