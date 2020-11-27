#include <Arduino.h>
#include "lichtsterkte.h"

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