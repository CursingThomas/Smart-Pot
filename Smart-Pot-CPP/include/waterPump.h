class waterPump
{
    public:
    waterPump(int pin);
    void giveWater(int timer);

    private:
    int pin;
    int timer;
};