#include "./Led.h"

Led::Led(int pin) {
    this->_pin = pin;
    pinMode(this->_pin, OUTPUT);
}

void Led::on() {
    digitalWrite(this->_pin, 1);
}

void Led::off() {
    digitalWrite(this->_pin, 0);
}

void Led::toggle() {
    int state = digitalRead(_pin);
    digitalWrite(this->_pin, !state);
}

int Led::getPin() {
    return this->_pin;
}