#include "UserDetectorTask.h"
#include <Arduino.h>
#include "avr/sleep.h"
#include "avr/power.h"

//Il pir viene creato nel main e poi passato al costruttore
UserDetectorTask::UserDetectorTask(PIR* pir) {
    _pir = pir;

    _state = NOT_DETECTED;
    _lastDetectedTime = 0;
    _deltaTime = 5000;
}

void UserDetectorTask::tick() {
    _userDetected = _pir->isDetected();
    
    switch (_state){
    case NOT_DETECTED:
        if(_userDetected){ //se rileva un utente cambia stato
            _state = DETECTED; 
        }else{  //se nessun utente viene rilevato si controlla da quanto tempo siamo nello stato NOT_DETECTED
            if(_lastDetectedTime == 0){ 
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime > _deltaTime){
                _state = SLEEP;
            }
        }

        break;
    
    case DETECTED:
        _lastDetectedTime = 0;
        if(!_userDetected){
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