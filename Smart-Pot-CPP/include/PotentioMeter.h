class PotentioMeter
{
    public:
    PotentioMeter(int pin);
    int readValuePot();
    int getProcessedData();

    private:
    int pin;
    int potValue;
    const int deler = 1024;
    const int vermenigvuldiger = 100;
};