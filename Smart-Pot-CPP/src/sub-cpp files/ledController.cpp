#include <Arduino.h>
#include "ledController.h"

LedController::LedController(int pinG, int pinR)
{
    this->pinG = pinG;
    this->pinR = pinR;

    pinMode(pinG, OUTPUT);
    pinMode(pinR, OUTPUT);
}

void LedController::setLedStatusVol()
{
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
}

void LedController::setLedStatusLeeg()
{
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
}

