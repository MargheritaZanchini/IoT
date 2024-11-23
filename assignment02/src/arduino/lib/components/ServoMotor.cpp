#include "ServoMotor.h"
#include <Arduino.h>

ServoMotor::ServoMotor(int pin) {
  this->pin = pin;
} 

void ServoMotor::on(){
  servo.attach(pin);    
}

void ServoMotor::setPosition(int angle){
  servo.write(angle);              
}

void ServoMotor::off(){
  servo.detach();    
}
