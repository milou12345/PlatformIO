#ifndef __SHOPPER_H__
#define __SHOPPER_H__
#include "Arduino.h"
#include "../lib/PID_fast/Arduino-PID-Library/PID_v1/PID_v1.h"
#include "define.h"

class shopper
{
private:
    int freq;      // Frequenz in 1/s
    byte dutyCyle; // 0-100
    double Setpoint, Input, Output;
    double Kp, Ki, Kd;
    byte pwmPin;    // Pin für Ausgabe der PWM
    PID * currentPID = nullptr; //PID controler
public:
    shopper(byte pwmPin, int freq);
    void init();
    void setDutyCyle(byte dutyCyle);
    void PidControll(double *Input, double *Setpoint);
    //void currentControler(double Input, &Output, &Setpoint, Kp, Ki, Kd)
};

#endif // __SHOPPER_H__