#ifndef __LCD_I2C_DISPLAY__
#define __LCD_I2C_DISPLAY__

#include "LiquidCrystal_I2C.h"

#define LCD_COLS 20
#define LCD_ROWS 4

class LCD {
public:
    LCD(int address);
    void init();
    void clear();
    void print(const String& text, int row = 0, int col = 0);
    LiquidCrystal_I2C* getDisplay();

private:
    LiquidCrystal_I2C _lcd;
    int _address;
};

#endif