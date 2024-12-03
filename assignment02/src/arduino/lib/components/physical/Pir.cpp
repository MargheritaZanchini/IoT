#include "PIR.h"

PIR::PIR(int pin) : Sensor(pin) {

}

const bool PIR::isDetected() {
    return digitalRead(_pin) == HIGH;
}