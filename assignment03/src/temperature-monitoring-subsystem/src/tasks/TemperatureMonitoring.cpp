#include "TemperatureMonitoring.h"

extern MQTT* mqtt;

TemperatureMonitoring::TemperatureMonitoring(Thermistor* thermistor, Led* okLED, Led* errorLED) {
    _thermistor = thermistor;
    _state = OK;

    _okLED = okLED;
    _okLED->on();

    _errorLED = errorLED;
    _errorLED->off();
}

void TemperatureMonitoring::tick() {
    switch(_state) {
        case OK:
            if(!mqtt->isOK()) {
                _state = ERROR;
                _okLED->off();
                _errorLED->on();
            }
            
            _currentTemperature = _thermistor->read();
            mqtt->sendTemperature(_currentTemperature);
            
            break;
        case ERROR:
            if(mqtt->isOK()) {
                _state = OK;
                _okLED->on();
                _errorLED->off();
            }
            break;
    }
}

float TemperatureMonitoring::getCurrentTemperature() {
    return _currentTemperature;
}
