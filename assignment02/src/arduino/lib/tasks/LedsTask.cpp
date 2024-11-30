#include "LedsTask.h"

LedsTask::LedsTask(Led& ok, Led& error, TemperatureDetector& temperatureDetector) {
    _ok = &ok;
    _error = &error;
}

void LedsTask::init(int period) {
    Task::init(period);
    _state = OK_ON;
    _ok->on();
}

void LedsTask::tick() {
    switch (_state)
    {
        case OK_ON:
            /* code */
            break;
        case ERROR_ON:
            /* code */
            break;
    }
}