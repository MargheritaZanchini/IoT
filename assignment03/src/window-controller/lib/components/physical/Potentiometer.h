#pragma once

#include <Arduino.h>

/**
 * \brief Potentiometer Class
 * \details Manages Potentiometer Actions
 */
class Potentiometer {
public:
    /**
     * \brief Creates New Potentiometer Instance
     * \param pin Input Pin for Potentiometer Connection
     */
    Potentiometer(int pin);

    /**
     * \brief Reads the Potentiometer Value
     * \return Analog value read from the potentiometer
     */
    int readValue();

private:
    int _pin; /** Pin Number for Analog Input */
};