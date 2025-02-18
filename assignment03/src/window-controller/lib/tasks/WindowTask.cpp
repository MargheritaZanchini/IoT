#include "WindowTask.h"

WindowTask::WindowTask(Window* window, Potentiometer* pot, SystemManager* mode) {
    _window = window;
    _pot = pot;
    _mode = mode;
}

void WindowTask::tick() {
    SerialHelper.getMode();

    switch(_mode->getMode()) {
        case SystemManager::Mode::MANUAL:
            _window->setWindowAperture(_pot->readValue());
            break;
        case SystemManager::Mode::AUTOMATIC:
            _window->setWindowAperture(SerialHelper.getAperture());
            break;
    }
}