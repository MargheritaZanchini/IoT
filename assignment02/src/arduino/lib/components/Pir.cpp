#include "PIR.h"
#include <Arduino.h>

PIR::PIR(int pin){
    this->_pin = pin;
}

float PIR::read() {
    return digitalRead(_pin);
}
