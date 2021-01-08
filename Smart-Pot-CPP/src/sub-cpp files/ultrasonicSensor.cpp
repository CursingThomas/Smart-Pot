#include <Arduino.h>
#include "ultrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin)
{
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
}

int UltrasonicSensor::getRawData()
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

int UltrasonicSensor::processData()
{ 
  int processedData = ((distance * honderdWaarde) / potDiepte) - honderdWaarde;

  return processedData;
}

void UltrasonicSensor::printRawData()
{
  Serial.print("Raw data ultrasonic: ");
  Serial.println(rawData);
}

void UltrasonicSensor::printProcessedData()
{
  Serial.print("Processed data ultrasonic: ");
  Serial.println(processedData);
}

String UltrasonicSensor::dataToString()
{
  strProcessedData = strProcessedData + processedData;

  return strProcessedData;
}

String UltrasonicSensor::clearString()
{
  strProcessedData = "";

  return strProcessedData;
}
