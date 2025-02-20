#include "ModeTask.h"

ModeTask::ModeTask(Button* button) {
    _button = button;
}

void ModeTask::tick() {
    bool pressed = _button->isPressed();

    if(pressed) {
        SerialHelper.switchMode();
        SerialHelper.sendMode();
    }
}