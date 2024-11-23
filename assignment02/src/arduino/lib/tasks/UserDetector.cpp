#include "UserDetector.h"
#include "Arduino.h"


UserDetector::UserDetector(Pir pir){
    this->_pir = pir;
}

void UserDetector::init(0){
    _state = NOT_DETECTED;
    _lastDetectedTime = 0;
    _deltaTime = 5000;
}

void UserDetector::tick(){
    switch (_state){
    case NOT_DETECTED:
        _userDetected = _pir.read();
        if(_userDetected == HIGH){
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
        _userDetected = _pir.read();
        if(_userDetected == HIGH){
            _state = DETECTED; 
        }
        break;
    
    case SLEEP:
        break;
    }
}