#include "main.h"

//Define Variables we'll be connecting to
double Setpoint = sollwert, Input, Output;
bool hotSwapEnable = 0;
//Specify the links and initial tuning parameters
double Kp = 0.1, Ki = 0.2, Kd = 0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

MosfetMatrix matrix(mosfet1Pin, mosfet2Pin);
Sensor currentSensor(PIN_INPUT);

void setup()
{
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin1, ledChannel);
  ledcAttachPin(pwmPin2, ledChannel);

  //Inh Pin DC-Motor Control board
  pinMode(eneablePin, OUTPUT);
  digitalWrite(eneablePin, HIGH);

  //Onboard LED output
  pinMode(onboardLed, OUTPUT);
  //initialize the variables we're linked to for PID
  Input = currentSensor.getSensorValue();

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetResolution(MICROS);
  myPID.SetSampleTime(SampleTime);
}

void loop()
{
  //Aktivatew HotSwap with switch
  if (digitalRead(hotSwapEnablePin) == true)
    hotSwapEnable = true;
  if (hotSwapEnable == true)
    digitalWrite(onboardLed, HIGH);

  Input =
      myPID.Compute();
  //Wirte pwm
  ledcWrite(ledChannel, Output);
  //ADCFilter.Filter(sensVal);
  hotSwap(Input);
}
