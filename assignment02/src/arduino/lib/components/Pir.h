#ifndef __PIR__
#define __PIR__

#include "Sensor.h"

class PIR : public Sensor {
public:
    PIR() : PIR(-1) {}
    PIR(int pin);
    float read() override;

private:
    int _pin;    
};

#endif
