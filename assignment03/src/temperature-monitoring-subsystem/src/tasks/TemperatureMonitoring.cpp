#include "TemperatureMonitoring.h"

TemperatureMonitoring::TemperatureMonitoring(Thermistor* thermistor) {
    _thermistor = thermistor;
    _state = OK;
}

void TemperatureMonitoring::tick() {
    switch (_state) {
        case OK:
            if(_thermistor->read() >= 50) {
                _state = ERROR;
            }
            break;
        case ERROR:
            if(false) {
                _state = OK;
            }
            break;
    }
}