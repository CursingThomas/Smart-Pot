#include <Arduino.h>
#include "ultrasonicSensor.h"

ultrasonicSensor::ultrasonicSensor(int trigPin, int echoPin)
{
    trigPin = trigPin;
    echoPin = echoPin;
}

void ultrasonicSensor::begin()
{
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
}

int ultrasonicSensor::getRawdata()
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

ultrasonicSensor::printRawdata()
{
    char strrawData = strrawData + rawData;

    return strrawData;    
}

ultrasonicSensor::printProcesseddata()
{
  char strprocessedData = strprocessedData + processedData
}