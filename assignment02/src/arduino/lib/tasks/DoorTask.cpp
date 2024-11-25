#include "DoorTask.h"

DoorTask::DoorTask(ServoMotor& servo, Button& closeButton, Button& openButton) {
    _servo = &servo;
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

    switch (_state)
    {
        case CLOSED:
            if(openPressed) {
                /* msg = ... */
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