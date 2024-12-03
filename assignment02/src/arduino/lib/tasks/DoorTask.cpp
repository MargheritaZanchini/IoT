#include "DoorTask.h"

DoorTask::DoorTask(Door* door, Button* closeButton, Button* openButton, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector) {
    _door = door;
    _closeButton = closeButton;
    _openButton = openButton;
    _temperatureDetector = temperatureDetector;
    _wasteDetector = wasteDetector;
    _state = CLOSED;
}

void DoorTask::tick() {
    bool closePressed = _closeButton->isPressed();
    bool openPressed = _openButton->isPressed();
    bool isInAlarm = _temperatureDetector->getTemperatureAlarm();
    bool isFull = _wasteDetector->getFullnessAlarm();

    switch (_state) {
        case CLOSED:
            if(openPressed && (!isInAlarm && !isFull)) {
                _automaticCloseTime = 0;
                _door->setDoorPosition(Constants::Servo::USER_DOOR_OPENED);
                _state = OPENED;
            }
            if(SerialHelper.emptyActionAvailable()) {
                _lastEmptiedTime = 0;
                _state = OPERATOR_OPENED;
                _door->setDoorPosition(Constants::Servo::OPERATOR_DOOR_OPENED);
            }

            break;
        
        case OPENED:
            if(closePressed || isInAlarm || isFull) {
                _door->setDoorPosition(Constants::Servo::USER_DOOR_CLOSED);
                _state = CLOSED;
            }

            if(_automaticCloseTime == 0) {
                _automaticCloseTime = millis();
            }
            if(millis() - _automaticCloseTime >= Constants::Servo::AUTOMATIC_CLOSE_TIME) {
                _door->setDoorPosition(Constants::Servo::USER_DOOR_CLOSED);
                _state = CLOSED;
            }
            break;
            
        case OPERATOR_OPENED:
            if(_lastEmptiedTime == 0) {
                _lastEmptiedTime = millis();
            }
            if(millis() - _lastEmptiedTime >= Constants::Servo::OPERATOR_EMPTY_TIME) {
                _door->setDoorPosition(Constants::Servo::USER_DOOR_CLOSED);
                _state = CLOSED;
            }
            break;
    }
}