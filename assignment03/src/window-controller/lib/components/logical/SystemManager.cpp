#include "SystemManager.h"

SystemManager::SystemManager() {
    _currentMode = MANUAL;
}

void SystemManager::setMode(SystemManager::Mode mode) {
    _currentMode = mode;
}

SystemManager::Mode SystemManager::getMode() const {
    return _currentMode;
}

void SystemManager::switchMode() {
    _currentMode = (_currentMode == MANUAL) ? AUTOMATIC : MANUAL;
}
