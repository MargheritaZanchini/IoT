#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(TemperatureDetector& temperatureDetector) {
    this->_temperatureDetector = &temperatureDetector;
}

void TemperatureTask::init(int period) {
    Task::init(period);
    _temperatureDetector->setTemperatureAlarm(false);
    _state = NORMAL;
    _lastDetectedTime = 0;
}

void TemperatureTask::tick() {
    Serial.print("[Value:Temperature]");
    Serial.println(_temperatureDetector->read());

    switch(_state) {
        case NORMAL:
            if(_temperatureDetector->read() >= Constants::Thermistor::MAX_TEMPERATURE) {
                _state = HIGH_TEMP;
            }
            break;
        case HIGH_TEMP:
            if(_temperatureDetector->read() < Constants::Thermistor::MAX_TEMPERATURE) {
                _lastDetectedTime = 0;
                _state = NORMAL;
            }

            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }
            else if(millis() - _lastDetectedTime > Constants::Thermistor::MAX_TEMPERATURE_TIME){
                _temperatureDetector->setTemperatureAlarm(true);
                _state = PROBLEM_DETECTED;
            }
            break;
        case PROBLEM_DETECTED:
            // while (Serial.available()) {
            //     String content = Serial.readStringUntil('\n');
            //     
            //     if(content == "[Action:Restore]") {
            //         _lastDetectedTime = 0;
            //         _temperatureDetector->setTemperatureAlarm(false);
            //         _state = NORMAL;
            //         break;
            //     }
            // }

            break;
    }
}