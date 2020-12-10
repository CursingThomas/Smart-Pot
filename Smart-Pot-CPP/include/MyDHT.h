#include <DHT.h>
class MyDHT : public DHT 
{
    public:
    MyDHT(uint8_t pin, uint8_t type, uint8_t count);
    String dataToString(double x);
    String clearString(String y);
    
    private:
    String strLuchtVochtigheid;
    String strTemperatuur;
    double temperatuur;
    double luchtVochtigheid;
    String y;
    double x;
    float f;

};