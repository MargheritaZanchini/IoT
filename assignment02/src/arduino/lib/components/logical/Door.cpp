#include "Door.h"

Door::Door(ServoMotor* servoMotor) {
    _servoMotor = servoMotor;
    _angle = Constants::Servo::USER_DOOR_CLOSED;   
}

void Door::setDoorPosition(int angle) {
    _angle = angle;
    _servoMotor->on();
    _servoMotor->setPosition(_angle);
    delay(80);
    _servoMotor->off();
}

int Door::getDoorPosition() {
    return _angle;
}

bool Door::isOpen() {
    return (_angle == Constants::Servo::USER_DOOR_OPENED);
}

bool Door::isOperatorOpen() {
    return (_angle == Constants::Servo::OPERATOR_DOOR_OPENED);
}