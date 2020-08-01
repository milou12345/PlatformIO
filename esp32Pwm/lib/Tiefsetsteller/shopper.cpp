#include "shopper.h"

shopper::shopper(byte pwmPin,byte freq) 
{
    this->pwmPin=pwmPin;
    this->freq=freq;

}

void shopper::init() 
{
     // configure LED PWM functionalitites
    ledcSetup(ledChannel, freq, resolution);
    ledcAttachPin(pwmPin, ledChannel);
    dutyCyle=0;
    iSoll=0;
    iIst=0;
  
}

void shopper::setDutyCyle(byte dutyCyle) 
{
    this->dutyCyle=dutyCyle;
    ledcWrite(ledChannel, dutyCyle);
}
