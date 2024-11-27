#ifndef __PIR__
#define __PIR__

#include "Sensor.h"

/**
 * @brief PIR Component Helper Class
 * @implements Sensor
 * @authors Marco Marrelli, Margherita Zanchini, Sofia Caberletti
 */
class PIR : public Sensor {
public:
    /**
     * @brief Creates New PIR Instance
     * @param pin Input Pin for the PIR Sensor
     */
    PIR(int pin) : Sensor(pin) { }

    /**
     * @brief Reads Current Motion State
     * @return true if Motion Detected, false Otherwise
     */
    const bool isUserDetected() {
        return digitalRead(_pin) == HIGH;
    }
};

#endif