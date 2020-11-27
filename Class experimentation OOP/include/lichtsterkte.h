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
