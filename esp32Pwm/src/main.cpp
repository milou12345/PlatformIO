#include "main.h"
#include "Arduino.h"
#define pwm 200


double Input, Setpoint;
shopper myCuteShopShop(pwmPin1, PWM_FREQ);
MosfetMatrix matrix(mosfet1Pin, mosfet2Pin);
Sensor currentSensor(PIN_INPUT, 8);

// int hotSwap(double currentMeasure)
// { // Function for the HotSwap event
//   if (hotSwapEnable == true)
//   {
//     if ((currentMeasure <= hotSwapLimit))
//     {
//       // Switch Mosfets for Hotswap
//       matrix.switchToPS2();

//       // PWM to 100% till current rises to wanted value
//       do
//       {
//         ledcWrite(ledChannel, maxPwm);
//       } while (analogRead(PIN_INPUT) <= sollwert);
//       hotSwapEnable = false;
//       return 1;
//     }
//   }
//   return 0;
// }

void setup()
{
  //initialize the variables we're linked to for PID
  Input = currentSensor.getCurrentSensed();
}

void loop()
{
  //Aktivate HotSwap with switch
  /* if (digitalRead(hotSwapEnablePin) == true)
    hotSwapEnable = true;
  if (hotSwapEnable == true)
    digitalWrite(onboardLed, HIGH); */

  Input = currentSensor.getCurrentSensed();

  myCuteShopShop.PidControll(&Input, &Setpoint);
  myCuteShopShop.setDutyCyle(pwm);

  //hotSwap(Input);
}
