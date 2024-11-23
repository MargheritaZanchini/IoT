#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(int pin) {
    this->_pin = pin;
}

void TemperatureTask::init(int period) {
    Task::init(period);
    alarm = true;
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