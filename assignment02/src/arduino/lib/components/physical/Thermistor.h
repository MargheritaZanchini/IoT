#pragma once

#include <Arduino.h>
#include "arduino/lib/components/physical/Sensor.h"

/**
 * @brief Thermistor Component Helper Class
 * @implements{Sensor}
 */
class Thermistor : public Sensor {
public:
    /**
     * @brief Creates New Temperature Sensor Instance
     * @param pin Analog Input for Thermistor
     */
    Thermistor(int pin);

    /**
     * @brief Read the Temperature from the Thermistor. 
     * 
     * Convert ADC Value to Equivalent Voltage and Gives Output of 10mv/°C
     * @return Temperature in Celsius
     */
    float read() override;
};
