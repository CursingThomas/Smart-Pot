class LedController
{
    public:
    LedController(int pinG, int pinR);
    void setLedStatusVol();
    void setLedStatusLeeg();


    private:
    int pinG;
    int pinR;
};