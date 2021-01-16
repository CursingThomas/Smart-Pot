#include <PotentioMeter.h>
#include <Arduino.h>

PotentioMeter::PotentioMeter(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

int PotentioMeter::readValuePot()
{
    potValue = analogRead(pin);
    
    return potValue;
}

int PotentioMeter::getProcessedData()
{
    potValue = (potValue / deler) * vermenigvuldiger;

    return potValue;
}