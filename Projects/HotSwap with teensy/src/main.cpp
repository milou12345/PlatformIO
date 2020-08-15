#include "main.h"
#include "Arduino.h"

double Input, Output; //MEasured Current
bool manualControl;
bool hotSwapControl;
shopper shopperMain(PWM_PIN_1, PWM_FREQ);
shopper shopperBackup(PWM_PIN_2, PWM_FREQ);
LED ledMos1(LED_PIN_MOS_1);
LED ledMos2(LED_PIN_MOS_2);
LED ledManualControl(LED_PIN_MAN_EN);
LED ledHotSwapEnable(LED_PIN_HS_EN);
MosfetMatrix matrix(MOSFET_PIN_1, MOSFET_PIN_2);
Sensor currentSensor(PIN_INPUT, 12);
Button switchMos1 = Button();
Button switchMos2 = Button();
Button buttonSwap = Button();
Button buttonHSEnable = Button();
Button buttonManualControl = Button();

void setup()
{
    //  analogWriteFrequency(33, 10000000);
    hotSwapControl = false;
    switchMos1.attach(SWITCH_PIN_MOS1, INPUT_PULLUP);
    switchMos2.attach(SWITCH_PIN_MOS2, INPUT_PULLUP);
    buttonSwap.attach(BUTTON_PIN_SWAP, INPUT_PULLUP);
    buttonHSEnable.attach(BUTTON_PIN_HS_Enable, INPUT_PULLUP);
    buttonManualControl.attach(BUTTON_PIN_MANUAL_CONTROL, INPUT_PULLUP);

    buttonSwap.interval(5);
    switchMos2.interval(5);
    switchMos1.interval(5);
    buttonHSEnable.interval(5);
    buttonManualControl.interval(5);

    buttonSwap.setPressedState(LOW);
    switchMos1.setPressedState(LOW);
    switchMos2.setPressedState(LOW);
    buttonHSEnable.setPressedState(LOW);
    buttonManualControl.setPressedState(LOW);

    //initialize the variables we're linked to for PID
    Input = currentSensor.getCurrentSensed();

    //Initialize PID for shopper
    shopperMain.PidInit(&Input, SETPOINT, KP, KI, KD);
    shopperBackup.PidInit(&Input, SETPOINT, KP, KI, KD);

    Serial.begin(115200);

    pinMode(13, OUTPUT); //Onboard led
}

void loop()
{
    //analogWrite(33, 100);
    buttonSwap.update();
    switchMos1.update();
    switchMos2.update();
    buttonHSEnable.update();
    buttonManualControl.update();

    digitalWrite(13, HIGH); //Switch on Led to see board working
    //Aktivate HotSwap with switch
    /* if (digitalRead(hotSwapEnablePin) == true)
      hotSwapEnable = true;
    if (hotSwapEnable == true)
      digitalWrite(onboardLed, HIGH); */

    if (buttonManualControl.risingEdge() && (manualControl == false))
    {
        manualControl = true;
        hotSwapControl = false;
        Serial.println("Manual Control Activated!");
    }
    else if (buttonManualControl.risingEdge() && (manualControl == true))
    {
        manualControl = false;
        Serial.println("Manual Control Deactivated!!");
        ledManualControl.switchOff();
        matrix.mos1.switchOff();
        matrix.mos2.switchOff();
        ledMos1.switchOff();
        ledMos2.switchOff();
    }
    else if (buttonHSEnable.risingEdge() && (hotSwapControl == false))
    {
        hotSwapControl = true;
        manualControl = false;
        Serial.println("HS Controll activated!");
    }
    else if (buttonHSEnable.risingEdge() && (hotSwapControl == false))
    {
        hotSwapControl = false;
        ledHotSwapEnable.switchOff();
        Serial.println("HS Controll deactivated!");
    }

    /*****************************************************
     * Manual control over IGBT/MOSFET switch status.
     * Can be acivated with Manual control switch.
     * ***************************************************/

    if (manualControl == true)
    {
        ledManualControl.switchOn();
        hotSwapControl = false;

        if (switchMos1.pressed())
        {
            Serial.println("Switch1 pressed");
            ledMos1.switchOn();
            matrix.mos1.switchOn();
            shopperMain.PidCompute();
        }
        else if (switchMos1.released())
        {

            ledMos1.switchOff();
            matrix.mos1.switchOff();
        }

        if (switchMos2.pressed())
        {

            ledMos2.switchOn();
            matrix.mos2.switchOn();
            //shopperBackup.PidCompute();
        }
        else if (switchMos2.released())
        {

            ledMos2.switchOff();
            matrix.mos2.switchOff();
        }

        if (buttonSwap.risingEdge())
        {

            matrix.switchPS();
        }
    }
    /**********************************
     * Automatic current watch, with swap of
     * powersupplys if conditions are mett
     * *******************************/
    else if (hotSwapControl == true)
    {
        ledHotSwapEnable.switchOn();
        matrix.switchToPS1();
        delay(1);

        if ((currentSensor.getCurrentSensed() <= HOT_SWAP_LIM))
        {
            // Switch Mosfets for Hotswap
            matrix.switchToPS2();

            // PWM to 100% till current rises to wanted value
            do
            {
                shopperBackup.setDutyCyle(100);
            } while (currentSensor.getCurrentSensed() <= SETPOINT);
        }
    }

    Input = currentSensor.getCurrentSensed();

    //shopperMain.PidCompute();
    /* Serial.print("Output: ");
    Serial.println(shopperMain.Output); */
    // Serial.print("Input: ");
    //Serial.println(Input);
    shopperMain.setDutyCyle(15);
    shopperBackup.setDutyCyle(15);
}
