#include "Thermistor.h"

Thermistor::Thermistor(int pin) : Sensor(pin) { }

float Thermistor::read() {
    float temperature = analogRead(_pin);
    temperature = (temperature * 4.88);
    temperature = (temperature / 10);
    return temperature;
}