#include "WasteDetectorTask.h"

WasteDetectorTask::WasteDetectorTask(WasteDetector& detector) {
    _detector = &detector;
}

void WasteDetectorTask::init(int period) {
    Task::init(period);
}

void WasteDetectorTask::tick() {
    _detector->setFullnessAlarm(checkFullness());
    //MsgService.sendMsg("[Value:WasteLevel]" + String(_detector->getFormattedValue()));
}

/**
 * @brief Check if Container is Full
 * @return if Waste Level >= Alarm Threshold @see{Constants::Sonar::ALARM_THRESHOLD}
 */
bool WasteDetectorTask::checkFullness() {
    return (_detector->read() <= Constants::Sonar::FULL_THRESHOLD);
}