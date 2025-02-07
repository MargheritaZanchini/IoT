#pragma once

#include <Arduino.h>

/**
 * \brief LED Component Helper Class
 */
class Led {
public:
    /**
     * \brief Creates New LED Instance
     * \param pin Output Pin for LED Connection
     */
    Led(int pin);

    /**
     * \brief Sets LED to High State
     */
    void on();

    /**
     * \brief Sets LED to Low State
     */
    void off();

    /**
     * \brief Inverts Current LED State
     */
    void toggle();

private:
    int _pin; /** Pin Number for Digital Output */
};
