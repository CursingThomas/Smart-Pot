#include <Arduino.h>

class lichtsterkte
{
  public:
  lichtsterkte(int pin);
  void begin();
  int pullData();
  int processData();
  String printData();

  private:
  int pin;
  int processedData;
  String strprocessedData;
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

  return processedData
}

String lichtsterkte::printData()
{
  strprocessedData = processedData + strprocessedData;
  Serial.print(processedData);

  return strprocessedData;
}


class ledHandling
{
  public: 
  ledHandling(int pin);
  void begin();
  void aan();
  void stop();
  String statusVanled();

  private:
  int pin;
  String status;
};

ledHandling::ledHandling(int pin)
{
  pin = pin;
}

void ledHandling::begin()
{
  pinMode(pin, OUTPUT);
}

void ledHandling::aan()
{
  digitalWrite(pin, HIGH);
  status = "Aan";
}

void ledHandling::stop()
{
  digitalWrite(pin, LOW);
  status = "Uit";
}

String ledHandling::statusVanled()
{
  return status;
}


lichtsterkte Lichtsensor1(12);
ledHandling Led1(10);

void setup() 
{
  Serial.begin(9600);
  Led1.begin();
  Lichtsensor1.begin();
}

void loop() 
{
  Led1.statusVanled();
  Led1.aan();
  Led1.statusVanled();
  Led1.stop();
  Lichtsensor1.pullData();
  Lichtsensor1.processData();
  Lichtsensor1.printData();
}