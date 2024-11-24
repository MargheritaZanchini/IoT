#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(Thermistor& thermistor) {
    _thermistor = &thermistor;
}

void TemperatureTask::init(int period) {
    Task::init(period);
    alarm = false;
    _state = NORMAL;
}

void TemperatureTask::tick() {
    switch (_state)
    {
        case NORMAL:
            /* code */
            break;
        case HIGH_TEMP:
            /* code */
            break;
        case PROBLEM_DETECTED:
            /* code */
            break;
    }
}