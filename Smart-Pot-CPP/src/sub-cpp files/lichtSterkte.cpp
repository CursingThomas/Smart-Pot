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

void lichtSterkte::printRawdata()
{
  Serial.print(rawData);
}

void lichtSterkte::printProcesseddata()
{
  Serial.print(processedData);
}

String lichtSterkte::dataTostring()
{
  strprocessedData = strprocessedData + processedData;

  return strprocessedData;
}

String lichtSterkte::clearString()
{
  strprocessedData = "";

  return strprocessedData;
}

