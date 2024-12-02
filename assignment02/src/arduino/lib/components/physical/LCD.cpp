#include "LCD.h"

LCD::LCD(LiquidCrystal_I2C* lcd) {
    _lcd = lcd;
}

void LCD::clear() {
    _lcd->clear();
}

void LCD::print(const String& text, int row, int col) {
    _lcd->clear();
    _lcd->setCursor(col, row);
    _lcd->print(text);
}

LiquidCrystal_I2C* LCD::getDisplay() {
    return _lcd;
}