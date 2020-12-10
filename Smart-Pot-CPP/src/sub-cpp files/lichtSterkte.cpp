#include <Arduino.h>
#include "lichtSterkte.h"

lichtSterkte::lichtSterkte(int pin, String sensorNaam)
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
  Serial.print("Processed data lichtsensor ");
  Serial.print(sensorNaam);
  Serial.print(": ") ;
  Serial.println(rawData);
}

void lichtSterkte::printProcessedData()
{
  Serial.print("Processed data lichtsensor ");
  Serial.print(sensorNaam);
  Serial.print(": ") ;
  Serial.println(processedData);
}

String lichtSterkte::dataToString()
{
  strProcessedData = strProcessedData + processedData;

  return strProcessedData;
}

String lichtSterkte::clearString()
{
  strProcessedData = "";

  return strProcessedData;
}

