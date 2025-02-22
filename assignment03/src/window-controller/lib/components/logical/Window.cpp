#include "Window.h"

Window::Window(ServoMotor* servoMotor) {
    _servoMotor = servoMotor;
    _aperture = CONFIG_WINDOW_CLOSED;
}

void Window::setWindowAperture(int aperture) {
    _percentage = aperture;
    _aperture = map(_percentage, 0, 100, CONFIG_WINDOW_CLOSED, CONFIG_WINDOW_OPEN); // Map Percentage Value to Aperture

    _servoMotor->on();
    _servoMotor->setPosition(_aperture);
    delay(80);
    _servoMotor->off();
}

int Window::getWindowAperture() {
    return _aperture;
}

int Window::getPercentage() {
    return _percentage;
}

bool Window::isOpen() {
    return (_aperture == CONFIG_WINDOW_CLOSED);
}
