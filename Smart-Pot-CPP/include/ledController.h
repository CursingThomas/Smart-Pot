class ledController
{
    public:
    ledController(int pinG, int pinR);
    void setLedStatusVol();
    void setLedStatusLeeg();


    private:
    int pinG;
    int pinR;
};