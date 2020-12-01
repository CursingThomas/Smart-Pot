#include <Arduino.h>
#include "ledController.h"

ledController::ledController(int pinG, int pinR)
{
    pinG = pinG;
    pinR = pinR;
}

void ledController::begin()
{
    pinMode(pinG, OUTPUT);
    pinMode(pinR, OUTPUT);
}

void ledController::setStatus()
{
    
}