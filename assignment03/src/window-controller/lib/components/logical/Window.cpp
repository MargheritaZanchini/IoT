#include "Window.h"

Window::Window(ServoMotor* servoMotor) {
    _servoMotor = servoMotor;
    _angle = CONFIG_WINDOW_CLOSED;   
}

void Window::setDoorPosition(int angle) {
    _angle = map(angle, 0, 100, CONFIG_WINDOW_CLOSED, CONFIG_WINDOW_OPEN);
    _servoMotor->on();
    _servoMotor->setPosition(_angle);
    delay(80);
    _servoMotor->off();
}

int Window::getDoorPosition() {
    return _angle;
}

bool Window::isOpen() {
    return (_angle == CONFIG_WINDOW_CLOSED);
}
