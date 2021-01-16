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
    const int potDiepte = 30;
    const int honderdWaarde = 100;
    const int distanceVermenigvuldiggetal = 0.034;
    const int distanceDeler = 2;

};