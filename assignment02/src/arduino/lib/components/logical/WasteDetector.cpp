#include "WasteDetector.h"

WasteDetector::WasteDetector(Sonar* sonar) {
    _sonar = sonar;
}

float WasteDetector::mapValue(float value) {
    if (value == -1) value = _sonar->read();
    
    if(value >= Constants::Sonar::EMPTY_DISTANCE) return 0.0;
    if(value <= Constants::Sonar::FULL_DISTANCE) return 1.0;
    return ((Constants::Sonar::EMPTY_DISTANCE - value) / (Constants::Sonar::EMPTY_DISTANCE - Constants::Sonar::FULL_DISTANCE));
}

float WasteDetector::getFormattedValue() {
    return mapValue(_sonar->read()) * 100.0;
}

bool WasteDetector::getFullnessAlarm() {
    return _isFullAlarm;
}

void WasteDetector::setFullnessAlarm(bool isFull) {
    _isFullAlarm = isFull;

    Serial.print(F("[Alarm:WasteLevel]"));
    Serial.println(_isFullAlarm ? F("true") : F("false"));
    Serial.flush();
}

float WasteDetector::read() {
    return _sonar->read();
}