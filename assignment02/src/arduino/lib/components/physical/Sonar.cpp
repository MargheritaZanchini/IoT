#include "Sonar.h"

Sonar::Sonar(int trig, int echo) {
    _trig = trig;
    _echo = echo;

    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
}

float Sonar::read() {
    digitalWrite(_trig, LOW);
    delayMicroseconds(5);
    digitalWrite(_trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(_trig, LOW); 

    return (pulseIn(_echo, HIGH) * Constants::Sonar::SOUND_VELOCITY) / (2.0 * 1000000.0);
}