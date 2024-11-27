#include "DoorTask.h"

DoorTask::DoorTask(ServoMotor& servo, Button& closeButton, Button& openButton, bool& full, bool& alarm, String& msg, long& time) {
    _servo = &servo;
    _closeButton = &closeButton;
    _openButton = &openButton;
    _full = &full;
    _alarm = &alarm;
    _msg = &msg;
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
                _servo->on();
                _servo->setPosition(USER_DOOR_OPENED);
                //_servo->off();
                *_msg = MSG_PRESS_CLOSE;
                _state = OPENED;
                Serial.println("Closed->Open");
            }
            break;
        
        case OPENED:
            if(closePressed) {
                //_servo->on();
                _servo->setPosition(USER_DOOR_CLOSED);
                //_servo->off();
                *_msg = MSG_WASTE_RECEIVED;
                _state = CLOSED;
                Serial.println("Open->Closed");
            }
            break;
            
        case OPERATOR_OPENED:
            /* code */
            break;
    }
}