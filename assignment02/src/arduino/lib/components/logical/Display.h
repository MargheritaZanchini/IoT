#ifndef __A02_DISPLAY__
#define __A02_DISPLAY__

#include "../physical/LCD.h"
#include "../../Constants.h"

/**
 * @brief Display Logical Component
 * @implements{LCD}
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class Display : public LCD {
public:
    /**
     * @brief Creates new display
     * @param address I2C bus address
     */
    Display(LiquidCrystal_I2C* lcd) : LCD(lcd) {
        // printDefaultMessage();
    }

    /**
     * @brief Displays Default Message
     * @param message Default Message
     */
    void printDefaultMessage() {
        print(Constants::LCD::MSG_DEFAULT, 0, 0);
    } 
};

#endif