#include "Thermistor.h"

Thermistor::Thermistor(int pin) : Sensor(pin) { }

float Thermistor::read() {
    float temperature = analogRead(_pin);
    // Convert the analog reading to a voltage
    float voltage = temperature * (3.3 / 4095.0);
    
    // Convert the voltage to a temperature in Celsius
    float celsius = voltage * 100.0;

    return celsius;
}