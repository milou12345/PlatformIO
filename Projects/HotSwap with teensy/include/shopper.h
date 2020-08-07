#ifndef __SHOPPER_H__
#define __SHOPPER_H__
#include "Arduino.h"
#include "PID_v1.h"
#include "define.h"

class shopper
{
private:
    byte pwmPin;    // Pin für Ausgabe der PWM
    PID currentPID; //PID controller
public:
    int freq;      // Frequenz in 1/s
    byte dutyCyle; // 0-100
    double Setpoint, Output;
    double Kp, Ki, Kd;
    //double Input;

    shopper(byte pwmPin, int freq);

    void init();
    void setDutyCyle(byte dutyCyle);
    void PidCompute();
    void PidInit(double *const &Input, double Setpoint,
                 double Kp, double Ki, double Kd);
    void setSetpoint(double Setpoint);
    void setKp(double Kp);
    void setKi(double Ki);
    void setKd(double Kd);
    //void currentControler(double Input, &Output, &Setpoint, Kp, Ki, Kd)
};

#endif // __SHOPPER_H__