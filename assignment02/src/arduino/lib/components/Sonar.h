#ifndef __SONAR__
#define __SONAR__

#include "Sensor.h"

/**
 * @brief Sonar Component Helper Class
 * @implements Sensor
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class Sonar : public Sensor {
public:
    /**
     * @brief Creates New Distance Sensor
     * @param trig Output Pin for Trigger Signal
     * @param echo Input Pin for Echo Signal
     */
    Sonar(int trig, int echo) : Sensor() {
        _trig = trig;
        _echo = echo;

        pinMode(_trig, OUTPUT);
        pinMode(_echo, INPUT);
    };

    /*** 
     * @brief Measure the Time in microseconds and Convert to Distance in Meters
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
    int _trig; /** Trigger Signal Pin */
    int _echo; /** Echo Signal Pin */
    static constexpr float _temperature = 20; /** Temperature for Speed Calculation, @note https://en.wikipedia.org/wiki/Speed_of_sound */
    static constexpr float _vs = 331.45 + (0.62 * _temperature); /** Current Sound Velocity */
};

#endif
