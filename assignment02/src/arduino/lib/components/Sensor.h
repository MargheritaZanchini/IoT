#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

class Sensor {
public:
    virtual ~Sensor() = default;
    
    virtual float read() {
        return digitalRead(_pin);
    }

    Sensor() = default;
    Sensor(int pin) : _pin(pin) {
        pinMode(_pin, INPUT);
    }
    
protected:
    int _pin;
};

#endif