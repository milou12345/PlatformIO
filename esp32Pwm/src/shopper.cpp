#include "shopper.h"

shopper::shopper(byte pwmPin, int freq)
{
    this->pwmPin = pwmPin;
    this->freq = freq;
}

void shopper::init()
{
    Kp = 0;
    Ki = 0;
    Kd = 0;
    Setpoint = 0;
    Output = 0;
    dutyCyle = 0;

    currentPID.SetMode(AUTOMATIC);
    //currentPID.SetResolution(MICROS);
    currentPID.SetSampleTime(SAMPLE_TIME);

    // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, PWM_RESOLUTION);
    ledcAttachPin(pwmPin, ledChannel);
}

void shopper::setDutyCyle(byte dutyCyle)
{
    this->dutyCyle = dutyCyle;
    ledcWrite(ledChannel, dutyCyle);
}

void shopper::PidCompute()
{

    currentPID.Compute();
    //Wirte pwm
    ledcWrite(ledChannel, Output);
}

void shopper::PidInit(double *const &Input, double Setpoint,
                      double Kp, double Ki, double Kd)
{
    //this->Input = &Input;
    this->Setpoint = Setpoint;
    this->Kp = Kp;
    this->Kd = Kd;
    this->Ki = Ki;

    currentPID.Init(Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
}

void shopper::setSetpoint(double Setpoint)
{
    this->Setpoint = Setpoint;
}

void shopper::setKp(double Kp)
{
    this->Kp = Kp;
}

void shopper::setKi(double Ki)
{
    this->Ki = Ki;
}

void shopper::setKd(double Kd)
{
    this->Kd = Kd;
}
