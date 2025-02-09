#include "TemperatureMonitoring.h"

extern MQTT* mqtt;

TemperatureMonitoring::TemperatureMonitoring(Thermistor* thermistor, Led* okLED, Led* errorLED) {
    _thermistor = thermistor;
    _okLED = okLED;
    _errorLED = errorLED;
    _state = OK;
    _okLED->on();
}

void TemperatureMonitoring::tick() {
    switch (_state) {
        case OK:
            if(_thermistor->read() > 25) {
                _state = ERROR;
                _okLED->off();
                _errorLED->on();
            }
            _currentTemperature = _thermistor->read();

            mqtt->sendTemperature(_currentTemperature);
            break;
        case ERROR:
            if(_thermistor->read() <= 25) {
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
