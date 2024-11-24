#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

class Sensor {
public:
    virtual ~Sensor() = default;
    
    virtual float read() {
        return analogRead(_pin);
    }

    Sensor() = default;
    Sensor(int pin, int mode) : _pin(pin), _mode(mode) {
        pinMode(_pin, _mode);
    }
    
private:
    int _pin;
    int _mode;
};

#endif