#include "ServoMotor.h"
#include "Arduino.h"

ServoMotor::ServoMotor(int pin) {
    this->_pin = pin;
} 

void ServoMotor::on(){
    _servo.attach(_pin);    
}

void ServoMotor::setPosition(int angle){
    _servo.write(angle);              
}

void ServoMotor::off(){
    _servo.detach();    
}
