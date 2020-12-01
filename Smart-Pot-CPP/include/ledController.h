#include <Arduino.h>
class ledController
{
    public:
    ledController(int pinG, int pinR);
    void begin();
    void setStatus();

    private:
    int pinG;
    int pinR;
};

