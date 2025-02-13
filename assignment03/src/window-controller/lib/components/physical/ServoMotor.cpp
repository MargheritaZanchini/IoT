#include "ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
    _pin = pin;
    _servo.attach(_pin);
} 

void ServoMotor::on() {
    _servo.attach(_pin);
}

void ServoMotor::setPosition(int angle) {
    _servo.write(angle);
}

void ServoMotor::off() {
    _servo.detach();
}
