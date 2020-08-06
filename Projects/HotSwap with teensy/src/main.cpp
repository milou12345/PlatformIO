#include "main.h"
#include "Arduino.h"

double Input; //MEasured Current
byte buttonPins[] = {SWITCH_PIN_MOS1, SWITCH_PIN_MOS2, BUTTON_PIN_SWAP};
//shopper shopperMain(PWM_PIN_1, PWM_FREQ);
//shopper shopperBackup(PWM_PIN_2, PWM_FREQ);
LED ledMos1(LED_PIN_MOS_1);
LED ledMos2(LED_PIN_MOS_2);
LED ledSwap(BUTTON_PIN_SWAP);
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
  Buttons.begin(buttonPins, 3);
  //Initialize PID for shopper
  //shopperMain.PidInit(&Input, SETPOINT, KP, KI, KD);
  //shopperBackup.PidInit(&Input, SETPOINT, KP, KI, KD);
  Serial.begin(115200);
}

void loop()
{
  //Aktivate HotSwap with switch
  /* if (digitalRead(hotSwapEnablePin) == true)
    hotSwapEnable = true;
  if (hotSwapEnable == true)
    digitalWrite(onboardLed, HIGH); */

  if (Buttons.down(1))
  {
    Serial.println("Switch1 switched down");
    ledMos1.switchOn();
  }
  if (Buttons.down(2))
  {
    Serial.println("Switch2 switched down");
    ledMos2.switchOn();
  }
  if (Buttons.changed(3))
  {
    Serial.println("Button changed ");
    ledSwap.changeState();
  }

  Input = currentSensor.getCurrentSensed();

  //shopperMain.PidCompute();
}
