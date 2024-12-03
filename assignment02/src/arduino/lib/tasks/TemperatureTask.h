#pragma once

#include "arduino/lib/Constants.h"
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"

class TemperatureTask : public Task {
public:
    TemperatureTask(TemperatureDetector* temperatureDetector);
    void tick() override;

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED };
    State _state;
    TemperatureDetector* _temperatureDetector;
    unsigned long _lastDetectedTime;
};
