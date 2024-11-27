#ifndef __SERVO_MOTOR__
#define __SERVO_MOTOR__

#include <Arduino.h>
#include <ServoTimer2.h>

/**
 * @brief Servo Component Helper Class
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class ServoMotor {
public:
    /**
     * @brief Creates New Servo Controller
     * @param pin PWM Pin for Servo Control
     */
    ServoMotor(int pin) {
        this->_pin = pin;
    } 

    /**
     * @brief Attaches Servo to PWM Pin
     */
    void on() {
        _servo.attach(_pin);
    }

    /**
     * @brief Rotates Servo to Position
     * @param angle Target Angle in Degrees
     */
    void setPosition(int angle) {
        _servo.write(angle);
    }

    /**
     * @brief Detaches Servo from PWM Pin
     */
    void off() {
        _servo.detach();
    }

private:
    int _pin; /** Pin Number for PWM Output */
    ServoTimer2 _servo; /** Hardware Interface Instance */
};

#endif
