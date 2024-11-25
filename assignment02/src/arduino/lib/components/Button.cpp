#include <Arduino.h>
#include "Button.h"

Button::Button(int pin) : _pin(pin), _state(LOW), _previous(0) {
    pinMode(pin, INPUT);
}

bool Button::isPressed() {
    long _delta = millis() - _previous;

    if(_delta > BUTTON_DEBOUNCE_TIME) {
        _state = bool(digitalRead(_pin));
        _previous = millis();
    }
    
    return _state;
};