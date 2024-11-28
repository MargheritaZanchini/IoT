#pragma once

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
    Display(int address) : LCD(address) {
        printDefaultMessage();
    }

    /**
     * @brief Displays Default Message
     * @param message Default Message
     */
    void printDefaultMessage() {
        clear();
        print(Constants::LCD::MSG_DEFAULT, 0, 0);
    } 
};