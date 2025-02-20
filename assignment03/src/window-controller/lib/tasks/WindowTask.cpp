#include "WindowTask.h"

WindowTask::WindowTask(Window* window, Potentiometer* pot) {
    _window = window;
    _pot = pot;
}

void sendWindowAperture(int aperture) {
    Serial.print("aperture:");
    Serial.println(aperture);
}

void WindowTask::tick() {
    SerialHelperObject::Mode mode = SerialHelper.getMode();

    int newAperture = _pot->readValue();

    switch(mode) {
        case SerialHelperObject::Mode::MANUAL:
            _window->setWindowAperture(newAperture);
            sendWindowAperture(newAperture);
            break;
        case SerialHelperObject::Mode::AUTOMATIC:
            _window->setWindowAperture(SerialHelper.getAperture());
            break;
        default:
            break;
    }
}