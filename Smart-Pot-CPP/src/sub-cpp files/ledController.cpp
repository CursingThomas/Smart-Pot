#include <Arduino.h>
#include "ledController.h"

ledController::ledController(int pinG, int pinR)
{
    this->pinG = pinG;
    this->pinR = pinR;

    pinMode(pinG, OUTPUT);
    pinMode(pinR, OUTPUT);
}

void ledController::setLedStatusVol()
{
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
}

void ledController::setLedStatusLeeg()
{
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
}

