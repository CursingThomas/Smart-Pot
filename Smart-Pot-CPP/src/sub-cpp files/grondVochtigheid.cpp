#include <Arduino.h>
#include "grondVochtigheid.h"

grondVochtigheid::grondVochtigheid(int pin)
{
    pin = pin;
}

void grondVochtigheid::begin()
{
    pinMode(pin, INPUT);
}

int grondVochtigheid::getMoisture()
{
    
}