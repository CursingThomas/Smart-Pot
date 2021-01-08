#include <Arduino.h>
#include "waterPump.h"

WaterPump::WaterPump(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void WaterPump::giveWater(int timer)
{
    digitalWrite(pin, HIGH);
    delay(timer);
}