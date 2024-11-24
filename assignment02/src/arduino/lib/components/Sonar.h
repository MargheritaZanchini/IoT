#ifndef __SONAR__
#define __SONAR__

#include "Sensor.h"

/*** 
 * Sonar Class 
 * 
 * Sonar used to Measure Distance
 * 
 * @cite https://en.wikipedia.org/wiki/Speed_of_sound
*/
class Sonar : public Sensor {
public:
    Sonar(int trig, int echo) : Sensor() {
        _trig = trig;
        _echo = echo;

        pinMode(_trig, OUTPUT);
        pinMode(_echo, INPUT);
    };

    /*** 
     * Measure the Time in microseconds and Convert to Distance in Meters
     * Dividing by 1000000 to Convert to Seconds and
     * Dividing by 2 because the Sound Travels Back and Forth.
     * 
     * @return [float] Distance in Meters.
     */
    float read() override {
        digitalWrite(_trig, LOW);
        delayMicroseconds(5);
        digitalWrite(_trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(_trig, LOW);

        return (pulseIn(_echo, HIGH) * _vs) / (2.0 * 1000000.0);
    }

private:
    int _trig;
    int _echo;

    const float _temperature = 20;
    const float _vs = (331.45 + (0.62*_temperature));
};

#endif
