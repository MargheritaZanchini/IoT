#include "UserDisplayTask.h"

#include <Arduino.h>

UserDisplayTask::UserDisplayTask(WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector, Door* door) {
    _wasteDetector = wasteDetector;
    _temperatureDetector = temperatureDetector;
    _door = door;

    _lcd.init();
    _lcd.backlight();
    _lcd.setCursor(0, 0);

    _state = OK;
    updateDisplay(Constants::LCD::MSG_DEFAULT);
}

void UserDisplayTask::tick() {
    bool isFull = _wasteDetector->getFullnessAlarm();
    bool isInAlarm = _temperatureDetector->getTemperatureAlarm();
    bool isOpen = _door->isOpen();

    switch (_state) {
        case OK:
            if (isFull){
                _state = DISPLAY_WASTE;
                updateDisplay(Constants::LCD::MSG_CONTAINER_FULL);
            }
            else if (isInAlarm){
                _state = DISPLAY_TEMPERATURE;
                updateDisplay(Constants::LCD::MSG_TEMPERATURE_ALARM);
            }
            else if (isOpen){
                _state = DISPLAY_DOOR_OPEN;
                updateDisplay(Constants::LCD::MSG_DOOR_OPEN);
            }
            break;

        case DISPLAY_WASTE:
            if(!isFull){
                _state = OK;
                updateDisplay(Constants::LCD::MSG_DEFAULT);
            }
            break;

        case DISPLAY_TEMPERATURE:
            if(!isInAlarm){
                _state = OK;
                updateDisplay(Constants::LCD::MSG_DEFAULT);
            }
            break;

        case DISPLAY_DOOR_OPEN:
            if(!isOpen) {
                _state = DISPLAY_ON_DOOR_CLOSED;
                 //_lcd..print(Constants::LCD::MSG_DOOR_CLOSE);
                _lastDetectedTime = 0;
            }
            break;
            
        case DISPLAY_ON_DOOR_CLOSED:
            if(_lastDetectedTime == 0) _lastDetectedTime = millis();
            else if(millis() - _lastDetectedTime > Constants::Servo::CLOSING_MESSAGE_TIME) {
                _state = OK;
                updateDisplay(Constants::LCD::MSG_DEFAULT);
            }
            break;
    }
}

void UserDisplayTask::updateDisplay(const String& msg) {
    if (_previousMessage == msg) {
        return;
    }

    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(msg);
    _previousMessage = msg;
}