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

void grondVochtigheid::printProcesseddata()
{
    Serial.print(processedData);
}

String grondVochtigheid::dataToString()
{
    strprocessedData = strprocessedData + processedData;

    return strprocessedData;
}

String grondVochtigheid::clearString()
{
    strprocessedData = "";

    return strprocessedData;
}
