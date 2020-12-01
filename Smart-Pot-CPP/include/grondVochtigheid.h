#include <Arduino.h>
class grondVochtigheid
{
    public:
    grondVochtigheid(int pin);
    void begin();
    int getMoisture();
    int processMoisturetoPercent();
    char printEindwaarde();

    private:
    int pin;
    int rawData;
    int processedData;
    char strprocessedData;
};