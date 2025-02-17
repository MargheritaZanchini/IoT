#include "ModeTask.h"

ModeTask::ModeTask(Button* button, SystemMode* mode) {
    _button = button;
    _mode = mode;
}

void ModeTask::tick() {
    Serial.print("ModeTask tick - Button State: ");
    Serial.println(_button->isPressed() ? "PRESSED" : "RELEASED");

    if(_button->isPressed()) {
        _mode->switchMode();
    }
}