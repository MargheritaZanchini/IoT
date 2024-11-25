#include "LCD.h"
#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

/**
 * @brief Construct a new LCD object.
 * 
 * @param address I2C address of the LCD.
 */
LCD::LCD(int address) : _lcd(address, LCD_COLS, LCD_ROWS) {
    this->_address = address;
    this->init();
}

/**
 * @brief Initialize the LCD.
 */
void LCD::init() {
    _lcd.init();
    _lcd.backlight();
    _lcd.clear();
}

/**
 * @brief Clear the LCD display.
 */
void LCD::clear() {
    _lcd.clear();
}

/**
 * @brief Print Text on the LCD at Specified Position.
 * 
 * @param text The text to print.
 * @param row=0 The row position.
 * @param col=0 The column position.
 */
void LCD::print(const String& text, int row, int col) {
    _lcd.setCursor(col, row);
    _lcd.print(text);
}

/**
 * @brief Get the LiquidCrystal I2C Object.
 * 
 * @return [LiquidCrystal_I2C*] Reference Pointer to the LiquidCrystal I2C Object.
 */
LiquidCrystal_I2C* LCD::getDisplay() {
    return &_lcd;
}