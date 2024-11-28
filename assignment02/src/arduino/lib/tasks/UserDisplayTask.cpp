#include "UserDisplayTask.h"

UserDisplayTask::UserDisplayTask(Display& display, WasteDetector& wasteDetector, TemperatureDetector& temperatureDetector, Door& door) {
    _display = &display;
    _wasteDetector = &wasteDetector;
    _temperatureDetector = &temperatureDetector;
    _door = &door;

    _state = OK;
}

void UserDisplayTask::init(int period) {
    Task::init(period);
}

void UserDisplayTask::tick() {
    Serial.println("[WasteLevel] " + (String) _wasteDetector->mapValue());
    Serial.println("[Temperature] " + (String) _temperatureDetector->read());

    switch (_state) {
        case OK:
            _display->print("System OK");
            // if (_wasteDetector->isFull()) {
            //     _state = DISPLAY_WASTE;
            // } else if (_temperatureDetector->isOverheated()) {
            //     _state = DISPLAY_TEMPERATURE;
            // } else if (_door->isOpen()) {
            //     _state = DISPLAY_DOOR_STATUS;
            // }
            // break;

        case DISPLAY_WASTE:
            _display->print("Waste Full");
            // if (!_wasteDetector->isFull()) {
            //     _state = OK;
            // }
            // break;

        case DISPLAY_TEMPERATURE:
            _display->print("Overheated");
            // if (!_temperatureDetector->isOverheated()) {
            //     _state = OK;
            // }
            // break;

        case DISPLAY_DOOR_STATUS:
            _display->print("Door Open");
            // if (!_door->isOpen()) {
            //     _state = OK;
            // }
            // break;
    }
}