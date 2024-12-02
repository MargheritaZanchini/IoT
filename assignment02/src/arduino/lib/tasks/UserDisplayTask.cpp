#include "UserDisplayTask.h"

#include <Arduino.h>

UserDisplayTask::UserDisplayTask(Display* display, WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector, Door* door) {
    _display = display;
    _wasteDetector = wasteDetector;
    _temperatureDetector = temperatureDetector;
    _door = door;

    _state = OK;
    _display->print(Constants::LCD::MSG_DEFAULT);
    Serial.println("UserDisplayTask initialized");
}

void UserDisplayTask::tick() {
    bool isFull = _wasteDetector->getFullnessAlarm();
    bool isInAlarm = _temperatureDetector->getTemperatureAlarm();
    bool isOpen = _door->isOpen();

    switch (_state) {
        case OK:
            if (isFull){
                _state = DISPLAY_WASTE;
                _display->print(Constants::LCD::MSG_CONTAINER_FULL);
            }
            else if (isInAlarm){
                _state = DISPLAY_TEMPERATURE;
                _display->print(Constants::LCD::MSG_TEMPERATURE_ALARM);
            }
            else if (isOpen){
                _state = DISPLAY_DOOR_OPEN;
                _display->print(Constants::LCD::MSG_DOOR_OPEN);
            }
            break;

        case DISPLAY_WASTE:
            if(!isFull){
                _state = OK;
                _display->print(Constants::LCD::MSG_DEFAULT);
            }
            break;

        case DISPLAY_TEMPERATURE:
            if(!isInAlarm){
                _state = OK;
                _display->print(Constants::LCD::MSG_DEFAULT);
            }
            break;

        case DISPLAY_DOOR_OPEN:
            if(!isOpen) {
                _state = DISPLAY_ON_DOOR_CLOSED;
                _display->print(Constants::LCD::MSG_DOOR_CLOSE);
                _lastDetectedTime = 0;
            }
            break;
            
        case DISPLAY_ON_DOOR_CLOSED:
            if(_lastDetectedTime == 0) _lastDetectedTime = millis();
            else if(millis() - _lastDetectedTime > Constants::Servo::CLOSING_MESSAGE_TIME) {
                _state = OK;
                _display->print(Constants::LCD::MSG_DEFAULT);
            }
            break;
    }
}