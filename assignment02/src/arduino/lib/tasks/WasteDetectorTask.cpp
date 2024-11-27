#include "WasteDetectorTask.h"

WasteDetectorTask::WasteDetectorTask(WasteDetector& detector) {
    _detector = &detector;
    //_lcd = &lcd;

    _state = false;
}

void WasteDetectorTask::init(int period) {
    Task::init(period);
}

void WasteDetectorTask::tick() {
    bool state = isFull(); /** @brief true = Full, false = Not Full */

    if(state) {
        //_lcd->print("Waste Full", 0, 0);
    }
    else {
        //_lcd->clear();
    }
}

/**
 * @brief Check if Container is Full
 * @return if Waste Level >= Alarm Threshold @see{Constants::Sonar::ALARM_THRESHOLD}
 */
bool WasteDetectorTask::isFull() {
    return (_detector->read() >= Constants::Sonar::ALARM_THRESHOLD);
}