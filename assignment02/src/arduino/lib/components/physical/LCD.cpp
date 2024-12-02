#include "LCD.h"

//vLCD::LCD(int address) : _lcd(address, LCD_COLS, LCD_ROWS) {
LCD::LCD(LiquidCrystal_I2C* lcd) {
    _lcd = lcd;
    // init();
    // _lcd.init();
    // _lcd.backlight();
    // _lcd.clear();
}

// void LCD::init() {
//     _lcd.init();
//     _lcd.backlight();
//     _lcd.clear();
// }

void LCD::clear() {
    _lcd->clear();
}

void LCD::print(const String& text, int row, int col) {
    if(_currentText == text) return;

    _currentText = text;
    _lcd->clear();
    _lcd->setCursor(col, row);
    _lcd->print(_currentText);
}

// LiquidCrystal_I2C* LCD::getDisplay() {
//     return &_lcd;
// }

String LCD::getCurrentText() {
    return _currentText;
}