#ifndef __A02_TEMPERATURE_TASK__
#define __A02_TEMPERATURE_TASK__

#include "Task.h"
#include "../components/logical/TemperatureDetector.h"
#include "../Constants.h"

class TemperatureTask : public Task {
public:
    TemperatureTask(TemperatureDetector& temperatureDetector);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED };
    State _state;
    TemperatureDetector* _temperatureDetector;
    unsigned long _lastDetectedTime;
};

#endif