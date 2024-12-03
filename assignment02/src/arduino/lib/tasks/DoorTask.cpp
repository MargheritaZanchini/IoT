#include "DoorTask.h"

DoorTask::DoorTask(Door* door, Button* closeButton, Button* openButton, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector) {
    _door = door;
    _closeButton = closeButton;
    _openButton = openButton;
    _temperatureDetector = temperatureDetector;
    _wasteDetector = wasteDetector;
}

void DoorTask::init(int period) {
    Task::init(period);
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
                _door->setDoorPosition(Constants::Servo::USER_DOOR_OPENED);
                _state = OPENED;
            }
            if(MsgService.isMsgAvailable()) {
                Msg* msg = MsgService.receiveMsg();

                if(msg->getContent() == "[Action:Empty]") {
                    _lastEmptiedTime = 0;
                    _state = OPERATOR_OPENED;
                    _door->setDoorPosition(Constants::Servo::OPERATOR_DOOR_OPENED);
                }

                delete msg;
            }

            break;
        
        case OPENED:
            if(closePressed || isInAlarm || isFull) {
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