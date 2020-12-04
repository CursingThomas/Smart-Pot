#include <Arduino.h>
#include "grondVochtigheid.h"

grondVochtigheid::grondVochtigheid(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

int grondVochtigheid::getMoisture()
{
    rawData = analogRead(pin);
    
    return rawData;
}

int grondVochtigheid::processMoistureToPercent()
{
    processedData = ((rawData * 100) / 4095);

    return processedData;
}

void grondVochtigheid::printRawData()
{
    Serial.print(rawData);
}

void grondVochtigheid::printProcessedData()
{
    Serial.print(processedData);
}

String grondVochtigheid::dataToString()
{
    strProcessedData = strProcessedData + processedData;

    return strProcessedData;
}

String grondVochtigheid::clearString()
{
    strProcessedData = "";

    return strProcessedData;
}
