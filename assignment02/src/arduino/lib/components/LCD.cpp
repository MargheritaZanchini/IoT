#include "LCD.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

LCD::LCD(int address) : _lcd(address, LCD_COLS, LCD_ROWS) {
    this->_address = address;
    this->init();
}

void LCD::init() {
    _lcd.init();
    _lcd.backlight();
    _lcd.clear();
}

void LCD::clear() {
    _lcd.clear();
}

void LCD::print(const String& text, int row, int col) {
    _lcd.setCursor(col, row);
    _lcd.print(text);
}

LiquidCrystal_I2C* LCD::getDisplay() {
    return &_lcd;
}