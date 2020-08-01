#include <Arduino.h>
#include "Filter.h"
#include <../.pio/libdeps/esp32doit-devkit-v1/Arduino-PID-Library/PID_v1/PID_v1.h>
#include "mosfet.h"
#include "MosfetMatrix.h"
#include "sensor.h"
// Defines
#define PIN_INPUT 13 //Current Mesaurment
#define pwmPin1 23   //PWM Output 1
#define pwmPin2 14   //PWM Output 1
#define SampleTime 200  //Current Measurment periodic in microseconds 
#define ledChannel 0
#define resolution 8
#define eneablePin 12
#define maxPwm pow(2, resolution)
#define mosfet1Pin 4 
#define mosfet2Pin 10
#define sollwert 50
#define freq 100000
#define hotSwapEnablePin 9
#define onboardLed 2

#define hotSwapLimit 100

