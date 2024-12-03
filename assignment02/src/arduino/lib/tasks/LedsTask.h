#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/physical/Led.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/WasteDetector.h"

/**
 * \brief Leds Task Class
 * \implements{Task}
 */
class LedsTask: public Task {
public:
    /**
     * \brief Creates New Leds Task
     * \param ok Pointer to OK (Green) LED Object
     * \param error Pointer to Error (Red) LED Object
     * \param temperatureDetector Pointer to Temperature Detector Object
     * \param wasteDetector Pointer to Waste Detector Object
     */
    LedsTask(Led* ok, Led* error, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector);

    void tick() override;

private:
    enum State { OK_ON, ERROR_ON}; /** Enumeration for LED States */
    State _state; /** Current State of the LEDs */

    Led* _ok; /** Pointer to OK (Green) LED Object */
    Led* _error; /** Pointer to Error (Red) LED Object */

    WasteDetector* _wasteDetector; /** Pointer to Waste Detector Object */
    TemperatureDetector* _temperatureDetector; /** Pointer to Temperature Detector Object */
};