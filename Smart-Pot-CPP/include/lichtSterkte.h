#include <Arduino.h>
class lichtSterkte
{
  public:
  lichtSterkte(int pin);
  void begin();
  int pullData();
  int processData();
  void printData();

  private:
  int pin;
  int processedData;
  char strprocessedData;
  int rawData;
};

