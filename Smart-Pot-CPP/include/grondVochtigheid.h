#include <Arduino.h>
class GrondVochtigheid
{
    public:
    GrondVochtigheid(int pin);
    void begin();
    int getMoisture();
    int processMoistureToPercent();
    void printRawData();
    void printProcessedData();
    String dataToString();
    String clearString();
    void giveWater();
    int rawData;

    private:
    int pin;
    int processedData;
    String strProcessedData;
    const int vermenigvuldiger = 100;
    const int deler = 4095;
};