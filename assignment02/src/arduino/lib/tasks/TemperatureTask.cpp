#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(TemperatureDetector* temperatureDetector) {
    _temperatureDetector = temperatureDetector;

    _state = NORMAL;
    _lastDetectedTime = 0;
}

void TemperatureTask::tick() {
    Serial.print(F("[Value:Temperature]"));
    Serial.println(_temperatureDetector->read());

    switch(_state) {
        case NORMAL:
            if(_temperatureDetector->read() >= Constants::Thermistor::MAX_TEMPERATURE) {
                _lastDetectedTime = 0;
                _state = HIGH_TEMP;
            }
            break;
        case HIGH_TEMP:
            if(_temperatureDetector->read() < Constants::Thermistor::MAX_TEMPERATURE) {
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
            if(MsgService.restoreActionAvailable()) {
                Msg* msg = MsgService.receiveMessage();

                Serial.print(F("[TT] "));
                Serial.println(msg->getContent());

                if(msg->getContent() == "[Action:Restore]") {
                    _temperatureDetector->setTemperatureAlarm(false);
                    _state = NORMAL;
                }

                delete msg;
            }
            break;
    }
}