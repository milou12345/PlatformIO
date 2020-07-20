#include <Arduino.h>
#include "Filter.h"
#include </home/milou/Documents/PlatformIO/esp32Pwm/.pio/libdeps/esp32doit-devkit-v1/Arduino-PID-Library/PID_v1/PID_v1.h>

// Defines
#define PIN_INPUT 13 //Current Mesaurment
#define pwmPin1 15   //PWM Output 1
#define pwmPin2 14   //PWM Output 1
#define SampleTime 100  //Current Measurment periodic in microseconds 
#define ledChannel 0
#define resolution 8
#define eneablePin 12
#define maxPwm pow(2, resolution)
#define hotSwapMosfet1 11 
#define hotSwapMosfet2 10
#define sollwert 150
#define freq 100000

#define hotSwapLimit 100


//Define Variables we'll be connecting to
double Setpoint=sollwert, Input, Output;
bool hotSwapEnable = 1;
//Specify the links and initial tuning parameters
double Kp=0.1, Ki=0.2, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

int hotSwap(double currentMeasure){ // Function for the HotSwap event
if (hotSwapEnable==true)
  {
    if ((currentMeasure<=hotSwapLimit))
    {
      // Switch Mosfets for Hotswap
      digitalWrite(hotSwapMosfet1,LOW); 
      digitalWrite(hotSwapMosfet2,HIGH);
      
      // PWM to 100% till current rises to wanted value
      do
      {
        ledcWrite(ledChannel, maxPwm);
      } while (analogRead(PIN_INPUT)<=sollwert);
      hotSwapEnable=false;
      return 1;
      
    }
    return 0;
  }

}

// Create a new exponential filter with a weight of 5 and an initial value of 0. 
//ExponentialFilter<long> ADCFilter(5, 0);

void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin1, ledChannel);
  ledcAttachPin(pwmPin2, ledChannel);

  //Inh Pin DC-Motor Control board
  pinMode(eneablePin, OUTPUT);
  digitalWrite(eneablePin,HIGH);

  //Hot-Swap Matrix Mosfet Ini
  pinMode(hotSwapMosfet1, OUTPUT);
  pinMode(hotSwapMosfet2, OUTPUT);

  //initialize the variables we're linked to for PID
  Input = analogRead(PIN_INPUT);

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetResolution(MICROS);
  myPID.SetSampleTime(SampleTime);
}
 
void loop(){
  Input = analogRead(PIN_INPUT);
  myPID.Compute();
  //Wirte pwm
  ledcWrite(ledChannel, Output);
  //ADCFilter.Filter(sensVal);
  hotSwap(Input);
}



