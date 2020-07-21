#include <Arduino.h>
#include "Filter.h"
#include <../.pio/libdeps/esp32doit-devkit-v1/Arduino-PID-Library/PID_v1/PID_v1.h>
#include "mosfet.h"
#include "MosfetMatrix.h"
#include "sensor.h"
// Defines
#define PIN_INPUT 13 //Current Mesaurment
#define pwmPin1 15   //PWM Output 1
#define pwmPin2 14   //PWM Output 1
#define SampleTime 100  //Current Measurment periodic in microseconds 
#define ledChannel 0
#define resolution 8
#define eneablePin 12
#define maxPwm pow(2, resolution)
#define mosfet1Pin 11 
#define mosfet2Pin 10
#define sollwert 150
#define freq 100000
#define hotSwapEnablePin 9
#define onboardLed 2

#define hotSwapLimit 100

int hotSwap(double currentMeasure){ // Function for the HotSwap event
if (hotSwapEnable==true)
  {
    if ((currentMeasure<=hotSwapLimit))
    {
      // Switch Mosfets for Hotswap
      matrix.switchToPS2();
      
      // PWM to 100% till current rises to wanted value
      do
      {
        ledcWrite(ledChannel, maxPwm);
      } while (analogRead(PIN_INPUT)<=sollwert);
      hotSwapEnable=false;
      return 1;
      
    }
    
  }
  return 0;
}