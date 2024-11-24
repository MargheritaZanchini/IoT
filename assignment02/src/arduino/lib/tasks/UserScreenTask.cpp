#include "UserScreenTask.h"

UserScreenTask::UserScreenTask(LCD& lcd) {
    _lcd = &lcd;
}

void UserScreenTask::init(int period) {
    Task::init(period);
    // alarm = true;
    // _state = L1_ON;
}

void UserScreenTask::tick() {
    switch (_state)
    {
        case PRINT_DEFAULT:
            /* code */
            break;
        case PRINT:
            /* code */
            break;
    }
}