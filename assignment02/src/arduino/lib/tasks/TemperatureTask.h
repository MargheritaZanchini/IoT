#pragma once

#include "arduino/lib/Constants.h"
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"

/**
 * \brief Temperature Task Class
 * \implements{Task}
 */
class TemperatureTask : public Task {
public:
    /**
     * \brief Creates New Temperature Task
     * \param temperatureDetector Reference to Temperature Detector Object
     */
    TemperatureTask(TemperatureDetector* temperatureDetector);

    void tick() override;

private:
    enum State { NORMAL, HIGH_TEMP, PROBLEM_DETECTED }; /** Enumeration for Thermistor States */
    State _state; /** Current State of the Temperature Task */

    TemperatureDetector* _temperatureDetector; /** Reference to Temperature Detector Object */

    unsigned long _lastDetectedTime; /** Timestamp of the Last Detected Event */
};
