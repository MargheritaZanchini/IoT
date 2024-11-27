#ifndef __DOOR_H__
#define __DOOR_H__

#include "../physical/ServoMotor.h"
#include "arduino/lib/Constants.h"

class Door : public ServoMotor {
public:

    Door(int pin) : ServoMotor(pin) {
        setDoorPosition(Constants::Servo::USER_DOOR_OPENED);
    }

    void setDoorPosition(int angle) {
        _angle = angle;
        on();
        setPosition(_angle);
        off();
    }

    int getDoorPosition() {
        return _angle;
    }

private:
    int _angle;
};

#endif