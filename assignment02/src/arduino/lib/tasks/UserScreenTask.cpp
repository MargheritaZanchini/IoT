#include "UserScreenTask.h"

UserScreenTask::UserScreenTask(LCD& lcd) {
    _lcd = &lcd;
}

void UserScreenTask::init(int period) {
    Task::init(period);
    msg = DEFAULT_MSG;
    time = 0;
    clear = false;
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