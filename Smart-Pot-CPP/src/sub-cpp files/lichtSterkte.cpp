#include <Arduino.h>
#include "lichtSterkte.h"

LichtSterkte::LichtSterkte(int pin, String sensorNaam)
{
  this->pin = pin;
  this-> sensorNaam = sensorNaam;
  pinMode(pin,INPUT);
}

int LichtSterkte::pullData()
{
  rawData = analogRead(pin); 
  return rawData;
}

int LichtSterkte::processData()
{
  processedData = (rawData * vermenigvuldiger) / deler;

  return processedData;
}

void LichtSterkte::printRawData()
{
  Serial.print("Raw data lichtsensor ");
  Serial.print(sensorNaam);
  Serial.print(": ") ;
  Serial.println(rawData);
}

void LichtSterkte::printProcessedData()
{
  Serial.print("Processed data lichtsensor ");
  Serial.print(sensorNaam);
  Serial.print(": ") ;
  Serial.println(processedData);
}

String LichtSterkte::dataToString()
{
  strProcessedData = strProcessedData + processedData;

  return strProcessedData;
}

String LichtSterkte::clearString()
{
  strProcessedData = "";

  return strProcessedData;
}

