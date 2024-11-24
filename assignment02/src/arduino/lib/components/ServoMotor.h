#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Servo.h>

class ServoMotor {
public:
    ServoMotor(int pin);

    void on();
    void setPosition(int angle);
    void off();
    
private:
    int _pin;
    Servo _servo;
};

#endif
