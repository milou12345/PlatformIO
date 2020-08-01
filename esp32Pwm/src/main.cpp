#include "main.h"
#define pwm 200
#define tasterPin 5
//Define Variables we'll be connecting to
double Setpoint = sollwert, Input, Output;
bool hotSwapEnable = 0;
//Specify the links and initial tuning parameters
double Kp = 0.1, Ki = 0.2, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

MosfetMatrix matrix(mosfet1Pin, mosfet2Pin);
Sensor currentSensor(PIN_INPUT);

int hotSwap(double currentMeasure)
{ // Function for the HotSwap event
  if (hotSwapEnable == true)
  {
    if ((currentMeasure <= hotSwapLimit))
    {
      // Switch Mosfets for Hotswap
      matrix.switchToPS2();

      // PWM to 100% till current rises to wanted value
      do
      {
        ledcWrite(ledChannel, maxPwm);
      } while (analogRead(PIN_INPUT) <= sollwert);
      hotSwapEnable = false;
      return 1;
    }
  }
  return 0;
}

void setup()
{
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin1, ledChannel);
  ledcAttachPin(pwmPin2, ledChannel);

  //initialize the variables we're linked to for PID
  Input = currentSensor.getSensorValue();

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetResolution(MICROS);
  myPID.SetSampleTime(SampleTime);

  pinMode(tasterPin,INPUT);
}

void loop()
{
  //Aktivatew HotSwap with switch
  /* if (digitalRead(hotSwapEnablePin) == true)
    hotSwapEnable = true;
  if (hotSwapEnable == true)
    digitalWrite(onboardLed, HIGH); */

  Input = currentSensor.getSensorValue();
  myPID.Compute();
  //Wirte pwm
  ledcWrite(ledChannel, Output);
  if (digitalRead(tasterPin)==true)
  {
    matrix.switchToPS1();
  }else
  {
    matrix.switchToPS2();
  }
  
  

  //ADCFilter.Filter(sensVal);
  //hotSwap(Input);
}
