#ifndef __A02_DOOR__
#define __A02_DOOR__

#include "../physical/ServoMotor.h"
#include "arduino/lib/Constants.h"

class Door : public ServoMotor {
public:

    Door(int pin) : ServoMotor(pin) {
        setDoorPosition(Constants::Servo::USER_DOOR_CLOSED);
    }

    void setDoorPosition(int angle) {
        _angle = angle;
        on();
        setPosition(_angle);
        delay(80);
        off();
    }

    int getDoorPosition() {
        return _angle;
    }

    bool isOpen() {
        return (_angle == Constants::Servo::USER_DOOR_OPENED);
    }

    bool isOperatorOpen() {
        return (_angle == Constants::Servo::OPERATOR_DOOR_OPENED);
    }

private:
    int _angle;
};

#endif