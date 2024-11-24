#ifndef __PIR__
#define __PIR__

#include "Sensor.h"

class PIR : public Sensor {
public:
    PIR(int pin, int mode = INPUT);
    float read();
    const bool getValue() {
        return bool(this->read());
    }

private:
    int _pin;
};

#endif
