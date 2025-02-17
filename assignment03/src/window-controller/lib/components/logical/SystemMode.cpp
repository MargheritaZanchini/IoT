#include "SystemMode.h"

SystemMode::SystemMode() {
    _currentMode = MANUAL;
}

void SystemMode::setMode(SystemMode::Mode mode) {
    _currentMode = mode;
}

SystemMode::Mode SystemMode::getMode() const {
    return _currentMode;
}

void SystemMode::switchMode() {
    _currentMode = (_currentMode == MANUAL) ? AUTOMATIC : MANUAL;
}
