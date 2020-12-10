#include <DHT.h>
class MyDHT : public DHT 
{
    public:
    MyDHT(uint8_t pin, uint8_t type, uint8_t count);
    String dataToString(double x);
    String clearString(String y);
    void printTemperatuur();
    void printLuchtVochtigheid();
    
    private:
    String strLuchtVochtigheid;
    String strTemperatuur;
    float temperatuur;
    float luchtVochtigheid;
    String y;
    double x;
};