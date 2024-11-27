#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(TemperatureDetector& temperatureDetector) {
    this->_temperatureDetector = &temperatureDetector;
}

void TemperatureTask::init(int period) {
    Task::init(period);
    _temperatureDetector->setAlarm(false);
    _state = NORMAL;
    _lastDetectedTime = 0;
}

void TemperatureTask::tick() {
    switch (_state)
    {
        case NORMAL:
            Serial.println("NORMAL");
            if(_temperatureDetector->read() >= Constants::Thermistor::MAX_TEMPERATURE) {
                _state = HIGH_TEMP;
            }
            break;
        case HIGH_TEMP:
        Serial.println("HIGH");
            if(_temperatureDetector->read() < Constants::Thermistor::MAX_TEMPERATURE) {
                _lastDetectedTime = 0;
                _state = NORMAL;
            }
            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime > Constants::Thermistor::MAX_TEMPERATURE_THRESHOLD){
                _temperatureDetector->setAlarm(true);
                _state = PROBLEM_DETECTED;
            }
            break;
        case PROBLEM_DETECTED:
            /* code */
            break;
    }
}