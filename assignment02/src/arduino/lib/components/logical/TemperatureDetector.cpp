#include "TemperatureDetector.h"

TemperatureDetector::TemperatureDetector(Thermistor* thermistor) {
    _thermistor = thermistor;
}

float TemperatureDetector::read() {
    return _thermistor->read();
}

bool TemperatureDetector::getTemperatureAlarm() {
    return _highTemperatureAlarm;
}

void TemperatureDetector::setTemperatureAlarm(bool alarm) {
    _highTemperatureAlarm = alarm;

    Serial.print(F("[Alarm:Temperature]"));
    Serial.println(_highTemperatureAlarm ? F("true") : F("false"));
    Serial.flush();
}
