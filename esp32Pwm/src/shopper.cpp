#include "shopper.h"

shopper::shopper(byte pwmPin, int freq)
{
    this->pwmPin = pwmPin;
    this->freq = freq;
}

void shopper::init()
{
    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, PWM_RESOLUTION);
    ledcAttachPin(pwmPin, ledChannel);
    Kp = 0;
    Ki = 0;
    Kd = 0;
    Setpoint = 0;
    Input = 0;
    Output = 0;
    PID currentPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
    currentPID.SetMode(AUTOMATIC);
    currentPID.SetResolution(MICROS);
    currentPID.SetSampleTime(SampleTime);
    dutyCyle = 0;
}

void shopper::setDutyCyle(byte dutyCyle)
{
    this->dutyCyle = dutyCyle;
    ledcWrite(ledChannel, dutyCyle);
}

void shopper::PidControll(double *Input, double *Setpoint)
{

    this->currentPID.Compute();
    //Wirte pwm
    ledcWrite(ledChannel, Output);
}
