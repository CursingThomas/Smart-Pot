class PotentioMeter
{
    public:
    PotentioMeter(int pin);
    int readValuePot();
    int getProcessedData();

    private:
    int pin;
    int potValue;
};