#include <Arduino.h>
#include "ultrasonicSensor.h"

ultrasonicSensor::ultrasonicSensor(int trigPin, int echoPin)
{
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

int ultrasonicSensor::getRawData()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  
  return distance;
}

int ultrasonicSensor::processData()
{ 
  int processedData = ((distance * honderdWaarde) / potDiepte) - honderdWaarde;

  return processedData;
}

void ultrasonicSensor::printRawData()
{
  Serial.print(rawData);
}

void ultrasonicSensor::printProcessedData()
{
  Serial.print(processedData);
}

String ultrasonicSensor::dataToString()
{
  strProcessedData = strProcessedData + processedData;

  return strProcessedData;
}

String ultrasonicSensor::clearString()
{
  strProcessedData = "";

  return strProcessedData;
}
