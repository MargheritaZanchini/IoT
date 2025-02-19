#include "ModeTask.h"

ModeTask::ModeTask(Button* button, SystemManager* mode) {
    _button = button;
    _mode = mode;
}

void ModeTask::tick() {
    bool pressed = _button->isPressed();

    if(pressed) {
        SerialHelper.switchMode();
    }
}