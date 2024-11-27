#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "UserScreenTask.h"
#include "../components/Thermistor.h"

//#define MSG_PROBLEM "Problem detected"

#define MAX_TEMP 28
#define MAX_TEMP_TIME 4000

class TemperatureTask : public Task {
public:
    bool alarm;
    TemperatureTask(Thermistor& thermistor, String& msg, bool& clear);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED};
    State _state;
    Thermistor* _thermistor;
    String* _msg;
    bool* _clear;
    unsigned long _lastDetectedTime;

    String MSG_PROBLEM = "Problem detected";
};

#endif