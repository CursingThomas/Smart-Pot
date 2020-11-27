#include <Arduino.h>
class lichtsterkte
{
  public:
  lichtsterkte(int pin);
  void begin();
  int pullData();
  int processData();
  char printData();

  private:
  int pin;
  int processedData;
  char strprocessedData;
  int rawData;
};

lichtsterkte::lichtsterkte(int pin)
{
  pin = pin;
}

void lichtsterkte::begin()
{
  pinMode(pin, INPUT);
}

int lichtsterkte::pullData()
{
  rawData = analogRead(pin);

  return rawData;
}

int lichtsterkte::processData()
{
  processedData = (rawData * 100) / 4095;

  return processedData;
}

char lichtsterkte::printData()
{
  strprocessedData = processedData + strprocessedData;
  Serial.print(processedData);

  return strprocessedData;
}