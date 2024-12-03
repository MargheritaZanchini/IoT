#include "WasteDetectorTask.h"

WasteDetectorTask::WasteDetectorTask(WasteDetector* detector) {
    _state = NOT_FULL;

    _detector = detector;
    _detector->setFullnessAlarm(false);
}

void WasteDetectorTask::tick() {
    Serial.print(F("[Value:WasteLevel]"));
    Serial.println(_detector->getFormattedValue());

    bool isFull = checkFullness();
    switch (_state) {
        case NOT_FULL:
            if (isFull) {
                _detector->setFullnessAlarm(isFull);
                _state = FULL;
            }

            break;
        case FULL:
            if (!isFull) {
                _detector->setFullnessAlarm(isFull);
                _state = NOT_FULL;
            }

            break;
    }
}

bool WasteDetectorTask::checkFullness() {
    return (_detector->read() <= Constants::Sonar::FULL_THRESHOLD);
}