#include "UserDisplayTask.h"

UserDisplayTask::UserDisplayTask(Display& lcd, WasteDetector& wasteDetector, TemperatureDetector& temperatureDetector, Door& door) {
    _lcd = &lcd;
    _wasteDetector = &wasteDetector;
    _temperatureDetector = &temperatureDetector;
    _door = &door;

    _state = OK;
}

void UserDisplayTask::init(int period) {
    Task::init(period);
}

void UserDisplayTask::tick() {
    switch (_state) {
        case OK:
            _lcd->print("System OK");
            if (_wasteDetector->isFull()) {
                _state = DISPLAY_WASTE;
            } else if (_temperatureDetector->isOverheated()) {
                _state = DISPLAY_TEMPERATURE;
            } else if (_door->isOpen()) {
                _state = DISPLAY_DOOR_STATUS;
            }
            break;

        case DISPLAY_WASTE:
            _lcd->print("Waste Full");
            if (!_wasteDetector->isFull()) {
                _state = OK;
            }
            break;

        case DISPLAY_TEMPERATURE:
            _lcd->print("Overheated");
            if (!_temperatureDetector->isOverheated()) {
                _state = OK;
            }
            break;

        case DISPLAY_DOOR_STATUS:
            _lcd->print("Door Open");
            if (!_door->isOpen()) {
                _state = OK;
            }
            break;
    }
}