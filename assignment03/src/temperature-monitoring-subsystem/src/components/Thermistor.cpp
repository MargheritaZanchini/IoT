#include "Thermistor.h"

Thermistor::Thermistor(int pin) : Sensor(pin) { }

float Thermistor::read() {
    float temperature = analogRead(_pin);
    return map(temperature, 0, 4095, -30, 50);
}