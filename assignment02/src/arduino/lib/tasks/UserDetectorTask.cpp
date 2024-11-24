#include "UserDetectorTask.h"
#include "Arduino.h"

//Il pir viene creato nel main e poi passato al costruttore
UserDetectorTask::UserDetectorTask(PIR& pir) {
    _pir = &pir;
}

void UserDetectorTask::init(int period){
    Task::init(period);
    _state = NOT_DETECTED; //inizialmente non c'è nessuno user
    _lastDetectedTime = 0; //   
    _deltaTime = 5000;
}

void UserDetectorTask::tick(){
    switch (_state){
    case NOT_DETECTED:
        _userDetected = _pir->read();
        if(_userDetected == HIGH){
            _lastDetectedTime = 0;
            _state = DETECTED; 
        }else{
            if(_lastDetectedTime == 0){
                _lastDetectedTime = millis();
            }else if(millis() - _lastDetectedTime >_deltaTime){
                    _state = SLEEP;
            }
        }

        break;
    
    case DETECTED:
        _userDetected = _pir->read();
        if(_userDetected == LOW){
            _state = NOT_DETECTED; 
        }
        break;
    
    case SLEEP:
        break;
    }
}