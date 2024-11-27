#include "UserScreenTask.h"
#include <HardwareSerial.h>

UserScreenTask::UserScreenTask(LCD& lcd) {
    _lcd = &lcd;
}

void UserScreenTask::init(int period) {
    Task::init(period);
    _state = PRINT_DEFAULT;
    msg = DEFAULT_MSG;
    time = 0;
    clear = false;
}

void UserScreenTask::tick() {
    _lcd->clear();

    switch (_state)
    {
        case PRINT_DEFAULT:
            time = 0;
            _lcd->print(msg);
            if(!msg.equals(DEFAULT_MSG)) {
                _state = PRINT;
                Serial.println("Default->Print");
            }
            break;
        case PRINT:
            _lcd->print(msg);
            if(clear==true || time == 1) { //TO DO: implementare il cambio di stato con il tempo
                msg = DEFAULT_MSG;
                _state = PRINT_DEFAULT;
                Serial.println("Print->Default");
            }
            break;
    }
}