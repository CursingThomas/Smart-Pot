#include "MyDHT.h"
#include <DHT.h>

MyDHT::MyDHT(uint8_t pin, uint8_t type, uint8_t count = 6) : DHT(pin,type,count)
{
    
}

String MyDHT::dataToString(double x)
{
    y = f + y;

    return y;
}

String MyDHT::clearString(String y)
{
    y = "";

    return y;
}

/*float DHT::readHumidity(bool force) {
  float f = NAN;
  if (read(force)) {
    switch (_type) {
    case DHT11:
    case DHT12:
      f = data[0] + data[1] * 0.1;
      break;
    case DHT22:
    case DHT21:
      f = ((word)data[0]) << 8 | data[1];
      f *= 0.1;
      break;
    }
  }
  return f;
}*/
