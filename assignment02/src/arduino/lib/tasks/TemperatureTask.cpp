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
    //MsgService.sendMsg("[Value:Temperature]" + String(_temperatureDetector->read()));

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
            Serial.println("CALDOOOOOOOOOOOOOOOOO");
            if(MsgService.isMsgAvailable()) {
                Msg* msg = MsgService.receiveMsg();    

                if(msg->getContent() == "[Action:Restore]") {
                    _lastDetectedTime = 0;
                    _temperatureDetector->setTemperatureAlarm(false);
                    _state = NORMAL;
                };

                delete msg;
            }
            break;
    }
}