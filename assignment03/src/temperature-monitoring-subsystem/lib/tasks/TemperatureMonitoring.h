#pragma once

#include <Arduino.h>
#include "../lib/tasks/Task.h"
#include "../lib/components/Thermistor.h"
#include "../lib/components/Led.h"
#include "MQTT.h"

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
    TemperatureMonitoring(Thermistor* thermistor, Led* okLED, Led* errorLED);

    void tick() override;
    float getCurrentTemperature();

private:
    enum State { OK, ERROR }; /** Enumeration for Thermistor States */
    State _state; /** Current State of the Temperature Task */


    Thermistor* _thermistor; /** Reference to Temperature Detector Object */
    Led* _okLED; /** [Pointer] OK Indicator LED */
    Led* _errorLED; /** [Pointer] Error Indicator LED */

    float _currentTemperature; /** Current Temperature Value */
};
