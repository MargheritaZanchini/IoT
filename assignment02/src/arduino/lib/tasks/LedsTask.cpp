#include "LedsTask.h"

LedsTask::LedsTask(Led& ok, Led& error, TemperatureDetector& temperatureDetector, WasteDetector& wasteDetector) {
    _ok = &ok;
    _error = &error;
    _temperatureDetector = &temperatureDetector;
    _wasteDetector = &wasteDetector;
}

void LedsTask::init(int period) {
    Task::init(period);
    _state = OK_ON;
    _ok->on();
}

void LedsTask::tick() {
    bool isInAlarm = _temperatureDetector->getTemperatureAlarm();
    bool isFull = _wasteDetector->getFullnessAlarm();

    switch (_state)
    {
        case OK_ON:
            if(isInAlarm || isFull) {
                _ok->off();
                _error->on();
                _state = ERROR_ON;
            }
            break;
        case ERROR_ON:
            if(!isInAlarm && !isFull) {
                _error->off();
                _ok->on();
                _state = OK_ON;
            }
            break;
    }
}