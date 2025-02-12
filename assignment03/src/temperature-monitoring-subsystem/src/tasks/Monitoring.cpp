#include "Monitoring.h"

Monitoring::Monitoring() : _ok(CONFIG_LED_OK_PIN), _error(CONFIG_LED_ERROR_PIN), _thermistor(CONFIG_THERMISTOR_PIN) {
    setProblem(); // Starts as problem active
}

void Monitoring::setProblem() {
    _ok.off();
    _error.on();
}

void Monitoring::clearProblem() {
    _ok.on();
    _error.off();
}

bool Monitoring::hasProblem() {
    return _problem;
}

float Monitoring::getTemperature() {
    float currentTemperature = _thermistor.read();
    _problem = bool(currentTemperature >= CONFIG_TEMPERATURE_HOT_ALARM_THRESHOLD); 

    if(hasProblem()) setProblem();
    else clearProblem();

    return currentTemperature;
}
