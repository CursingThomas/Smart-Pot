#include <Arduino.h>
#include <ESP32Servo.h>
#include "grondVochtigheid.h"

grondVochtigheid::grondVochtigheid(int pin)
{
    this->pin = pin;
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

void grondVochtigheid::printRawdata()
{
    Serial.print(rawData);
}

void grondVochtigheid::printProcesseddata()
{
    Serial.print(processedData);
}

String grondVochtigheid::dataTostring()
{
    strprocessedData = strprocessedData + processedData;

    return strprocessedData;
}

String grondVochtigheid::clearString()
{
    strprocessedData = "";

    return strprocessedData;
}

void grondVochtigheid::giveWater()
{
    
}