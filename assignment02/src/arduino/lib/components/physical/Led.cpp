#include "Led.h"
#include <Arduino.h>

Led::Led(int pin) {
    this->_pin = pin;
    pinMode(pin, OUTPUT);
}

void Led::on() {
    digitalWrite(_pin, HIGH);
}

void Led::off() {
    digitalWrite(_pin, LOW);
}

void Led::toggle() {
    int state = digitalRead(_pin);
    digitalWrite(_pin, !state);
}