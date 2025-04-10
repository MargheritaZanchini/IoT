#pragma once

#include <Arduino.h>

#include "../../src/config.h"

/**
 * \brief Button Component Helper Class
 */
class Button {
public:
    /**
     * \brief Creates New Button Instance
     * \param pin Input Pin for Button Connection
     */
    Button(int pin);

    /**
     * \brief Detects Button Press with Debouncing
     * \return true if Button is Pressed, false Otherwise
     */
    bool isPressed();

private:
    int _pin; /** Pin Number for Digital Input */
    long _previous; /** Last Time Reading for Debounce */
    bool _state; /** Current Button State Cache */
};
