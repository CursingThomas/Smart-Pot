#include <Arduino.h>
class grondVochtigheid
{
    public:
    grondVochtigheid(int pin);
    void begin();
    int getMoisture();
    int processMoistureToPercent();
    void printRawData();
    void printProcessedData();
    String dataToString();
    String clearString();
    void giveWater();

    private:
    int pin;
    int rawData;
    int processedData;
    String strProcessedData;
};