#include "DoorTask.h"

DoorTask::DoorTask(ServoMotor& servo) {
    _servo = &servo;
}

void DoorTask::init(int period) {
    Task::init(period);
    _state = CLOSED; 
}

void DoorTask::tick() {
    switch (_state)
    {
        case CLOSED:
            /* code */
            break;
        
        case OPENED:
            /* code */
            break;
            
        case OPERATOR_DOOR_OPENED:
            /* code */
            break;
    }
}