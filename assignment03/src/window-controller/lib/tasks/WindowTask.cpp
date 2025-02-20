#include "WindowTask.h"

WindowTask::WindowTask(Window* window, Potentiometer* pot) {
    _window = window;
    _pot = pot;
}

void WindowTask::tick() {
    SerialHelperObject::Mode mode = SerialHelper.getMode();

    int aperture = _pot->readValue();

    switch(mode) {
        case SerialHelperObject::Mode::MANUAL:
            _window->setWindowAperture(aperture);
            break;
        case SerialHelperObject::Mode::AUTOMATIC:
            // _window->setWindowAperture(SerialHelper.getAperture());
            break;
        default:
            break;
    }
}