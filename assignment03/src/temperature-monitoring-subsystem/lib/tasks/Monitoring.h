#pragma once

#include <Arduino.h>

#include "Led.h"
#include "Thermistor.h"

#include "config.h"

class Monitoring {
public:
    Monitoring();

    bool hasProblem();
    void setProblem();
    void clearProblem();
    float getTemperature();

private:
    Led _ok;
    Led _error;
    Thermistor _thermistor;

    bool _problem;
};
