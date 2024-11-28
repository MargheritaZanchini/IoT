#include "DoorTask.h"
#include "../Constants.h"

DoorTask::DoorTask(Door& door, Button& closeButton, Button& openButton) {
    _door = &door;
    _closeButton = &closeButton;
    _openButton = &openButton;
}

void DoorTask::init(int period) {
    Task::init(period);
    _state = CLOSED;
}

void DoorTask::tick() {
    bool closePressed = _closeButton->isPressed();
    bool openPressed = _openButton->isPressed();

    switch (_state) {
        case CLOSED:
            if(openPressed) {
                _door->setDoorPosition(Constants::Servo::USER_DOOR_OPENED);

                _state = OPENED;
            }
            break;
        
        case OPENED:
            if(closePressed) {
                _door->setDoorPosition(Constants::Servo::USER_DOOR_CLOSED);
                _state = CLOSED;
            }
            break;
            
        case OPERATOR_OPENED:
            /* code */
            break;
    }
}