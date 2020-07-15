#include <Arduino.h>


const int pwmPin = 15;  
const int currentSensPin = 13;
// setting PWM properties
const int freq = 10000;
const int ledChannel = 0;
const int resolution = 8;
int pwm=50;
int mappwm=0;
int sensVal=0;
int counter=0;
void setup(){
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(pwmPin, ledChannel);
  pinMode(12, OUTPUT);

  //Serial
  Serial.begin(115200);
}
 
void loop(){
    mappwm=map(pwm,0,100,0,254);
    ledcWrite(ledChannel, mappwm);
    digitalWrite(12,OUTPUT);
    counter++;
    if (counter>=100)
    {
    sensVal=analogRead(currentSensPin);
    Serial.print(sensVal);
    Serial.print("\n");
    counter=0;
    }
    
    
}