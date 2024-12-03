#pragma once

#include "arduino/lib/components/physical/Sensor.h"

/**
 * \brief PIR Component Helper Class
 * \implements{Sensor}
 */
class PIR : public Sensor {
public:
    /**
     * \brief Creates New PIR Instance
     * \param pin Input Pin for the PIR Sensor
     */
    PIR(int pin);

    /**
     * \brief Reads Current Motion State
     * \return true if Motion Detected, false Otherwise
     */
    const bool isDetected();
};
