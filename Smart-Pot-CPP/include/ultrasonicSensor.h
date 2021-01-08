#include <Arduino.h>
class UltrasonicSensor
{
    public:
    UltrasonicSensor(int trigPin, int echoPin);
    void begin();
    int getRawData();
    int processData();
    void printRawData();
    void printProcessedData();
    String dataToString();
    String clearString();
    

    private:
    int trigPin;
    int echoPin;
    int rawData;
    int processedData;
    String strProcessedData;
    int distance;   
    int potDiepte = 30;
    int honderdWaarde = 100;

};