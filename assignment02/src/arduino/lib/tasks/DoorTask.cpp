#include "DoorTask.h"

DoorTask::DoorTask(ServoMotor& servo, Button& closeButton, Button& openButton, bool& full, bool& alarm, String msg, long& time) {
    _servo = &servo;
    _closeButton = &closeButton;
    _openButton = &openButton;
    _full = &full;
    _alarm = &alarm;
    _msg = msg;
    _time = &time;
}

void DoorTask::init(int period) {
    Task::init(period);
    _state = CLOSED; 
}

void DoorTask::tick() {
    bool closePressed = _closeButton->isPressed();
    bool openPressed = _openButton->isPressed();

    switch (_state)
    {
        case CLOSED:
            if(openPressed) {
                _servo->setPosition(USER_DOOR_OPENED);
                _msg = MSG_PRESS_CLOSE;
                _state = OPENED;
            }
            break;
        
        case OPENED:
            if(closePressed) {
                /* msg = ... */
            }
            /* code */
            break;
            
        case OPERATOR_OPENED:
            /* code */
            break;
    }
}