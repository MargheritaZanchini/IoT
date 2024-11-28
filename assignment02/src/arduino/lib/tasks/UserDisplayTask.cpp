#include "UserDisplayTask.h"
#include "DoorTask.h"

#include <Arduino.h>

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

/* WasteLevel{"value":<X>,"full":<X>} Temperature{"value":<X>,"overheated":<X>} */
void UserDisplayTask::updateGUI() {
    Serial.print("[WasteLevel] ");
    Serial.println(_wasteDetector->mapValue());

    Serial.print("[Temperature] ");
    Serial.println(_temperatureDetector->read());
    
    //Serial.println("[WasteLevel] " + (String) _wasteDetector->getFullnessAlarm());
    //Serial.println("[Temperature] " + (String) _temperatureDetector->getTemperatureAlarm());
}

void UserDisplayTask::updateLCD() {
    switch (_state) {
        case OK:
            _display->print(Constants::LCD::MSG_DEFAULT);
            if (_wasteDetector->getFullnessAlarm()) {
                _state = DISPLAY_WASTE;
            }
            else if (_temperatureDetector->getTemperatureAlarm()) {
                _state = DISPLAY_TEMPERATURE;
            }
            else if (_door->isOpen()) {
                _state = DISPLAY_DOOR_OPEN;
            }
            break;

        case DISPLAY_WASTE:
            _display->print(Constants::LCD::MSG_CONTAINER_FULL);
            if (!_wasteDetector->getFullnessAlarm()) {
                _state = OK;
            }
            break;

        case DISPLAY_TEMPERATURE:
            _display->print(Constants::LCD::MSG_TEMPERATURE_ALARM);
            if (!_temperatureDetector->getTemperatureAlarm()) {
                _state = OK;
            }
            break;

        case DISPLAY_DOOR_OPEN:
            _display->print(Constants::LCD::MSG_DOOR_OPEN);
            if (!_door->isOpen()) {
                _state = DISPLAY_ON_DOOR_CLOSED;
                _lastDetectedTime = 0;
            }
            break;
        case DISPLAY_ON_DOOR_CLOSED:
            _display->print(Constants::LCD::MSG_DOOR_CLOSE);
            
            if(_lastDetectedTime == 0) _lastDetectedTime = millis();
            else if(millis() - _lastDetectedTime > Constants::Servo::CLOSING_MESSAGE_TIME){
                _state = OK;
            }
            break;
    }
}

void UserDisplayTask::tick() {
    updateGUI();
    updateLCD();
}