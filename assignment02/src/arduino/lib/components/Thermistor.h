#ifndef __THERMISTOR__
#define __THERMISTOR__

#include "Sensor.h"

class Thermistor : public Sensor {
public:
    Thermistor(int pin, int mode);
    
    /***
     * Read the Temperature from the Thermistor
     * 
     * Convert ADC Value to Equivalent Voltage and Gives Output of 10mv/°C
     * @return [float] Temperature in Celsius
     */
    float read() override {
        float temperature = analogRead(_pin);
        temperature = (temperature*4.88);
        temperature = (temperature/10);
        return temperature;
    }

private:
    int _pin;
};

#endif