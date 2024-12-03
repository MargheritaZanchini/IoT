#pragma once

#include <Arduino.h>
#include "arduino/lib/Constants.h"
#include "arduino/lib/components/physical/Sensor.h"

/**
 * \brief Sonar Component Helper Class
 * \implements{Sensor}
 */
class Sonar : public Sensor {
public:
    /**
     * \brief Creates New Sonar Instance
     * \param trig Output Pin for Trigger Signal
     * \param echo Input Pin for Echo Signal
     */
    Sonar(int trig, int echo);

    /**
     * \brief Reads the Distance Measured by the Sonar
     * \return Distance in Meters.
     */
    float read() override;

private:
    int _trig; /** Trigger Signal Pin */
    int _echo; /** Echo Signal Pin */
};
