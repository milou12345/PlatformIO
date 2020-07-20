#include <Arduino.h>
#include "Filter.h"
#include </home/milan/Documents/PlatformIO/esp32Pwm/.pio/libdeps/esp32doit-devkit-v1/Arduino-PID-Library/PID_v1/PID_v1.h>

//
#define PIN_INPUT 13
#define SampleTime 0
#define freq 100000
//#define PIN_OUTPUT 3

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=0.1, Ki=0.2, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


// Create a new exponential filter with a weight of 5 and an initial value of 0. 
//ExponentialFilter<long> ADCFilter(5, 0);
//Pin Assigment
const int pwmPin = 15;  
int pwm=0;
int mappwm=0;
int sensVal=0;
int counter=0;

// setting PWM properties

const int ledChannel = 0;
const int resolution = 8;

void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin, ledChannel);
  pinMode(12, OUTPUT);

  //Serial
 // Serial.begin(115200);

  //Inh Pin DC-Motor Control board
  digitalWrite(12,OUTPUT);

    //initialize the variables we're linked to for PID
  Input = analogRead(PIN_INPUT);
  Setpoint = 50;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetResolution(MICROS);
  myPID.SetSampleTime(100);
}
 
void loop(){
  Input = analogRead(PIN_INPUT);
  
  myPID.Compute();
  
  //Map Pwm Duty cyle to dac value
   // mappwm=map(pwm,0,100,0,254);
    //Wirte pwm
    ledcWrite(ledChannel, Output);
    
    //Serial Output every 100 cyles
    //sensVal=analogRead(PIN_INPUT);

    //ADCFilter.Filter(sensVal);
     
    
}