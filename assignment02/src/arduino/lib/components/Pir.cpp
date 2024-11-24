#include "PIR.h"
#include "Arduino.h"

PIR::PIR(int pin) {
    if(pin == -1) return;
    this->_pin = pin;
}

float PIR::read() {
    return digitalRead(_pin);
}
