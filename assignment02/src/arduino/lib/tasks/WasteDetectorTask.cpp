#include "WasteDetectorTask.h"

WasteDetectorTask::WasteDetectorTask(Sonar& sonar, String& msg, bool& clear) {
    _sonar = &sonar;
    _msg = &msg;
    _clear = &clear;
}

void WasteDetectorTask::init(int period) {
    Task::init(period);
    full = false;
}

void WasteDetectorTask::tick() {
    switch (_state)
    {
        case NOT_FULL:
            /* code */
            break;
    
        case FULL:
            /* code */
            break;
    }
}