#include <Arduino.h>
#include "grondVochtigheid.h"

GrondVochtigheid::GrondVochtigheid(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

int GrondVochtigheid::getMoisture()
{
    rawData = analogRead(pin);
    
    return rawData;
}

int GrondVochtigheid::processMoistureToPercent()
{
    processedData = ((rawData * vermenigvuldiger) / deler);

    return processedData;
}

void GrondVochtigheid::printRawData()
{
    Serial.print("Raw data grondvochtigheid: ");
    Serial.println(rawData);
}

void GrondVochtigheid::printProcessedData()
{
    Serial.print("Processed data grondvochtigheid: ");
    Serial.println(processedData);
}

String GrondVochtigheid::dataToString()
{
    strProcessedData = strProcessedData + processedData;

    return strProcessedData;
}

String GrondVochtigheid::clearString()
{
    strProcessedData = "";

    return strProcessedData;
}
