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
    rawData = analogRead(pin);
    
    return rawData;
}

int grondVochtigheid::processMoisturetoPercent()
{
    processedData = ((rawData * 100) / 4095);

    return processedData;
}

char grondVochtigheid::printEindwaarde()
{
    strprocessedData = strprocessedData + processedData;
    
    Serial.print(strprocessedData);

    return strprocessedData;
}