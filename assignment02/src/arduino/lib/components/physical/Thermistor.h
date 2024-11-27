#ifndef __THERMISTOR__
#define __THERMISTOR__

#include "Sensor.h"

/**
 * @brief Thermistor Component Helper Class
 * @implements Sensor
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class Thermistor : public Sensor {
public:
    /**
     * @brief Creates New Temperature Sensor Instance
     * @param pin Analog Input for Thermistor
     */
    Thermistor(int pin) : Sensor(pin) { }

    /**
     * @brief Read the Temperature from the Thermistor. 
     * 
     * Convert ADC Value to Equivalent Voltage and Gives Output of 10mv/°C
     * @return Temperature in Celsius
     */
    float read() override {
        float temperature = analogRead(_pin);
        temperature = (temperature*4.88);
        temperature = (temperature/10);
        return temperature;
    }
};

#endif