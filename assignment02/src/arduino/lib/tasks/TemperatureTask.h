#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"

#define MAX_TEMP
#define MAX_TEMP_TIME

class TemperatureTask: public Task {
public:
    bool alarm;
    TemperatureTask(int pin);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED};
    State _state;
};

#endif