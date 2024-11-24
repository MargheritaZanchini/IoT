#include "LedsTask.h"

LedsTask::LedsTask(Led& L1, Led& L2) {
    _L1 = &L1;
    _L2 = &L2;
}

void LedsTask::init(int period) {
    Task::init(period);
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