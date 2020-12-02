#include <Arduino.h>
class grondVochtigheid
{
    public:
    grondVochtigheid(int pin);
    void begin();
    int getMoisture();
    int processMoisturetoPercent();
    void printRawdata();
    void printProcesseddata();
    String dataTostring();
    String clearString();

    private:
    int pin;
    int rawData;
    int processedData;
    String strprocessedData;
};