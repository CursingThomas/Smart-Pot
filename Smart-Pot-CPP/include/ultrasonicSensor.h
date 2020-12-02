#include <Arduino.h>
class ultrasonicSensor
{
    public:
    ultrasonicSensor(int trigPin, int echoPin);
    void begin();
    int getRawdata();
    int processData();
    void printRawdata();
    void printProcesseddata();
    String dataTostring();
    String clearString();
    

    private:
    int trigPin;
    int echoPin;
    int rawData;
    int processedData;
    String strprocessedData;
    int distance;   
    int potDiepte = 30;
    int honderdWaarde = 100;

};