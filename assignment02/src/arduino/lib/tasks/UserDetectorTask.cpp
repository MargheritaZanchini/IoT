// #include <Arduino.h>

#include "UserDetectorTask.h"
#include "avr/sleep.h"
#include "avr/power.h"

#define SLEEP_TIME 10000

UserDetectorTask::UserDetectorTask(PIR* pir) {
    _state = NOT_DETECTED;

    _pir = pir;

    _sleep = false;
    _userDetected = false;

    _lastDetectedTime = 0;
}

void UserDetectorTask::tick() {
    _userDetected = _pir->isDetected();
    
    switch (_state){
        case NOT_DETECTED:
            if (_userDetected) {
                _state = DETECTED; 
            }
            else {
                if (_lastDetectedTime == 0) { 
                    _lastDetectedTime = millis();
                }
                else if (millis() - _lastDetectedTime > SLEEP_TIME) {
                    _state = SLEEP;
                }
            }

            break;

        case DETECTED:
            _lastDetectedTime = 0;

            if (!_userDetected) {
                _state = NOT_DETECTED; 
            }

            break;

        case SLEEP:
            set_sleep_mode(SLEEP_MODE_IDLE);
            sleep_enable();
            power_all_disable();
            sleep_mode();
            sleep_disable();
            power_all_enable();

            _lastDetectedTime = 0;
            _state = DETECTED;

            break;
    }
}