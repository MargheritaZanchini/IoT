#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "UserScreenTask.h"
#include "../components/Thermistor.h"

#define MSG_PROBLEM "Problem detected"

#define MAX_TEMP
#define MAX_TEMP_TIME

class TemperatureTask : public Task {
public:
    bool alarm;
    TemperatureTask(Thermistor& thermistor);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED};
    State _state;
    Thermistor* _thermistor;
};

#endif