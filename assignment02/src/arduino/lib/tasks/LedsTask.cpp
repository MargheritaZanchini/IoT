#include "LedsTask.h"

LedsTask::LedsTask(int pin1, int pin2) {
    this->_pin1 = pin1;
    this->_pin2 = pin2;
}

void LedsTask::init(int period) {
    Task::init(period);
    _alarm = true;
    _state = L1_ON;
}

void LedsTask::tick() {
    switch (_state)
    {
        case L1_ON:
            /* code */
            break;
        case L2_ON:
            /* code */
            break;
    }
}