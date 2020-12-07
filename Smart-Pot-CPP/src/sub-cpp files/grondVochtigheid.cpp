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
    Serial.print("Raw data grondvochtigheid: ");
    Serial.println(rawData);
}

void grondVochtigheid::printProcessedData()
{
    Serial.print("Processed data grondvochtigheid: ");
    Serial.println(processedData);
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
