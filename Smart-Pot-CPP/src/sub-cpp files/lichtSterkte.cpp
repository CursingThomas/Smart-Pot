#include <Arduino.h>
#include "lichtSterkte.h"

lichtSterkte::lichtSterkte(int pin)
{
  this->pin = pin;
  pinMode(pin,INPUT);
}

int lichtSterkte::pullData()
{
  rawData = analogRead(pin); 
  return rawData;
}

int lichtSterkte::processData()
{
  processedData = (rawData * 100) / 4095;

  return processedData;
}

void lichtSterkte::printRawData()
{
  Serial.println(rawData);
}

void lichtSterkte::printProcessedData()
{
  Serial.println(processedData);
}

String lichtSterkte::dataToString()
{
  strProcessedData = strProcessedData + processedData;

  return strProcessedData;
}

void lichtSterkte::clearString()
{
  strProcessedData = "";
}

