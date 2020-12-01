#include <Arduino.h>
#include "lichtSterkte.h"

lichtSterkte::lichtSterkte(int pin)
{
  pin = pin;
}

void lichtSterkte::begin()
{
  pinMode(pin, INPUT);
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

char lichtSterkte::printData()
{
  strprocessedData = processedData + strprocessedData;
  Serial.print(processedData);

  return strprocessedData;
}
