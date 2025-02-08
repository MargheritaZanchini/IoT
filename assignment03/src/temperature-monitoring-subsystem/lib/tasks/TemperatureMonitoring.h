#pragma once

#include <Arduino.h>
#include "../lib/tasks/Task.h"
#include "../lib/components/Thermistor.h"

/**
 * \brief Temperature Task Class
 * \implements{Task}
 */
class TemperatureMonitoring : public Task {
public:
    /**
     * \brief Creates New Temperature Task
     * \param thermistor Reference to Temperature Detector Object
     */
    TemperatureMonitoring(Thermistor* thermistor);

    void tick() override;

private:
    enum State { OK, ERROR }; /** Enumeration for Thermistor States */
    State _state; /** Current State of the Temperature Task */

    Thermistor* _thermistor; /** Reference to Temperature Detector Object */
};
