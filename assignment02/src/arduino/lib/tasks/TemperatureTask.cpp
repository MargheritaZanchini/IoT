#include "TemperatureTask.h"

TemperatureTask::TemperatureTask(TemperatureDetector& temperatureDetector, String& msg, bool& clear) {
    this->_temperatureDetector = &temperatureDetector;
    _msg = &msg;
    _clear = &clear;
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
            if(_temperatureDetector->read() >= MAX_TEMP) {
                _state = HIGH_TEMP;
            }
            break;
        case HIGH_TEMP:
        Serial.println("HITGH");
            if(_temperatureDetector->read() < MAX_TEMP) {
                _lastDetectedTime = 0;
                _state = NORMAL;
            }
            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime > MAX_TEMP_TIME){
                _temperatureDetector->setAlarm(true);
                *_msg = MSG_PROBLEM;
                _state = PROBLEM_DETECTED;
            }
            break;
        case PROBLEM_DETECTED:
            /* code */
            break;
    }
}