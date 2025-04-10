#include "Button.h"

Button::Button(int pin) {
    _pin = pin;
    _previous = 0;
    _state = LOW;

    pinMode(pin, INPUT);
}

bool Button::isPressed() {
    long _delta = millis() - _previous;

    if(_delta > CONFIG_DEBOUNCE_TIME) {
        _state = bool(digitalRead(_pin));
        _previous = millis();
    }
    
    return _state;
};
