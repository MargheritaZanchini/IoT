#ifndef __TEMPERATURE_DETECTOR__
#define __TEMPERATURE_DETECTOR__

#include "../physical/Thermistor.h"

/**
 * @brief Class for the temperature detector
 * @implements Thermistor
 */
class TemperatureDetector : public Thermistor {
public:
    /**
     * @brief Creates New Temperature Detector Instance
     * @param pin Analog Input for Thermistor
     */
    TemperatureDetector(int pin) : Thermistor(pin) { }

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

    bool getAlarm(){
        return _alarm;
    }

    void setAlarm(bool alarm){
        this-> _alarm = alarm;
    }

private:
    bool _alarm;
};

#endif