class WaterPump
{
    public:
    WaterPump(int pin);
    void giveWater(int timer);

    private:
    int pin;
    int timer;
};