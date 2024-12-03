#pragma once

#include <Arduino.h>

/**
 * @brief Generic Sensor Helper Base Class
 */
class Sensor {
public:
    /**
     * @brief Base Reading Implementation
     * @return Digital Float Value
     */
    virtual float read() {
        return digitalRead(_pin);
    }
    
protected:
    int _pin; /** Pin Number for Sensor Input */

    /** @brief Default Destructor for Inheritance */
    virtual ~Sensor() = default;

    /** @brief Default Constructor, Creates Uninitialized Sensor */
    Sensor() = default;

    /**
     * @brief Creates New Generic Sensor Instance
     * @param pin Input Pin for Sensor
     */
    explicit Sensor(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }
};
