#include <Arduino.h>

int pwm=0;
int d=50;

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  pwm=map(d,0,100,0,255);
  analogWrite(13,pwm);
  
}