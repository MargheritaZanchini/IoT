#include "Pir.h"
#include <Arduino.h>

Pir::Pir(int pin){
    _pin = pin;
}

void Pir::read(){
    return digitalRead(_pin);
}
