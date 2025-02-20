#include "WindowTask.h"

WindowTask::WindowTask(Window* window, Potentiometer* pot) {
    _window = window;
    _pot = pot;
}

void WindowTask::tick() {
    SerialHelperObject::Mode mode = SerialHelper.getMode();

    switch(mode) {
        case SerialHelperObject::Mode::MANUAL:
            _window->setWindowAperture(_pot->readValue());
            break;
        case SerialHelperObject::Mode::AUTOMATIC:
            _window->setWindowAperture(SerialHelper.getAperture());
            break;
        default:
            break;
    }
}