#include <Arduino.h>
class ultrasonicSensor
{
    public:
    ultrasonicSensor(int trigPin, int echoPin);
    void begin();
    int getRawdata();
    int processData();
    int printData();

    private:
    int trigPin;
    int echoPin;
    int rawData;
    int processedData;
    int distance;
    int potDiepte = 30;
    int honderdWaarde = 100;
};