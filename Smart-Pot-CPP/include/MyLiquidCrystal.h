#include <LiquidCrystal.h>
class MyLiquidCrystal : public LiquidCrystal
{
    public:
    MyLiquidCrystal(uint8_t rs, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    MyLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
	uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
    MyLiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    MyLiquidCrystal(uint8_t rs, uint8_t enable,
	uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

    private:
    const int vo = 23;
    const int Rs = 22;
    const int E = 1;
    const int D4 = 3;
    const int D5 = 21;
    const int D6 = 19;
    const int D7 = 18;
};