#ifndef __TEMPERATURE_TASK__
#define __TEMPERATURE_TASK__

#include "Task.h"
#include "UserScreenTask.h"
#include "../components/logical/TemperatureDetector.h"

//#define MSG_PROBLEM "Problem detected"

class TemperatureTask : public Task {
public:
    TemperatureTask(TemperatureDetector& temperatureDetector, String& msg, bool& clear);  
    void init(int period);  
    void tick();

private:
    int _pin;
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED};
    State _state;
    TemperatureDetector* _temperatureDetector;
    String* _msg;
    bool* _clear;
    unsigned long _lastDetectedTime;

    String MSG_PROBLEM = "Problem detected";
};

#endif