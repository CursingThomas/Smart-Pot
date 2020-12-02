#include <Arduino.h>
class lichtSterkte
{
  public:
  lichtSterkte(int pin);
  void begin();
  int pullData();
  int processData();
  void printRawdata();
  void printProcesseddata();
  String dataTostring();
  String clearString();


  private:
  int pin;
  int processedData;
  String strprocessedData;
  int rawData;
};

