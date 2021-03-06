#include "MyDHT.h"
#include <DHT.h>

MyDHT::MyDHT(uint8_t pin, uint8_t type, uint8_t count = 6) : DHT(pin,type,count)
{

}

String MyDHT::dataToString(double x)
{
    y = "";
    y = x + y;
    x = 0;

    return y;
}

String MyDHT::clearString()
{
    y = "";

    return y;
}

void MyDHT::printTemperatuur()
{
    temperatuur = readTemperature();

    Serial.print(temperatuur);
}

void MyDHT::printLuchtVochtigheid()
{
    luchtVochtigheid = readHumidity();

    Serial.print(luchtVochtigheid);
}

