#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

/**
 * @brief Generic Sensor Helper Base Class
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class Sensor {
public:
    /**
     * @brief Default Destructor for Inheritance
     */
    virtual ~Sensor() = default;
    
    /**
     * @brief Base Reading Implementation
     * @return Digital Float Value
     */
    virtual float read() {
        return digitalRead(_pin);
    }

    /**
     * @brief Default Constructor, Creates Uninitialized Sensor
     */
    Sensor() = default;

    /**
     * @brief Creates New Generic Sensor Instance
     * @param pin Input Pin for Sensor
     */
    Sensor(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }

protected:
    int _pin; /** Pin Number for Sensor Input */
};

#endif