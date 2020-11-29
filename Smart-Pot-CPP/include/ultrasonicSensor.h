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
    
};