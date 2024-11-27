#include "LedsTask.h"

LedsTask::LedsTask(Led& ok, Led& error) {
    _ok = &ok;
    _error = &error;
}

void LedsTask::init(int period) {
    Task::init(period);
    _state = OK_ON;
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