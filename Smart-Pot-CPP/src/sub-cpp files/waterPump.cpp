#include <Arduino.h>
#include "waterPump.h"

waterPump::waterPump(int pin)
{
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void waterPump::giveWater(int timer)
{
    digitalWrite(pin, HIGH);
    delay(timer);
}