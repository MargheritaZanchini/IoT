#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin) : _pin(pin) {
    pinMode(_pin, INPUT);
}

int Potentiometer::readValue() {
    return map(analogRead(_pin), 0, 1023, 0, 100);
}