#include <Arduino.h>
class grondVochtigheid
{
    public:
    grondVochtigheid(int pin);
    void begin();
    int getMoisture();
    int processMoisture();
    char streindwaardeMoisture();

    private:
    int pin;
    int rawData;
    int processedData;
    char strprocessedData;
};