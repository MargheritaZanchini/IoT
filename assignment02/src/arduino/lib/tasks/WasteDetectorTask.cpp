#include "WasteDetectorTask.h"

WasteDetectorTask::WasteDetectorTask(WasteDetector& detector) {
    _detector = &detector;
}

void WasteDetectorTask::init(int period) {
    Task::init(period);
    _detector->setFullnessAlarm(false);
    _state = NOT_FULL;
}

void WasteDetectorTask::tick() {
    Serial.print("[Value:WasteLevel]");
    Serial.println(_detector->getFormattedValue());

    bool isFull = checkFullness();
    switch(_state) {
        case NOT_FULL:
            if(isFull) {
                _detector->setFullnessAlarm(isFull);
                _state = FULL;
            }
            break;
        case FULL:
            if(!isFull) {
                _detector->setFullnessAlarm(isFull);
                _state = NOT_FULL;
            }
            break;
    }
}

/**
 * @brief Check if Container is Full
 * @return if Waste Level >= Alarm Threshold @see{Constants::Sonar::ALARM_THRESHOLD}
 */
bool WasteDetectorTask::checkFullness() {
    return (_detector->read() <= Constants::Sonar::FULL_THRESHOLD);
}