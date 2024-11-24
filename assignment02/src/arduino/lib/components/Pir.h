#ifndef __PIR__
#define __PIR__

#include "Sensor.h"

class PIR : public Sensor {
public:
    PIR(int pin); 
    float read() override;

private:
    int _pin;
};

#endif
