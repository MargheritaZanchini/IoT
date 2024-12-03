#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/logical/WasteDetector.h"
#include "arduino/lib/communication/SerialHandler.h"

/**
 * \brief Waste Detector Task Class
 * \implements{Task}
 */
class WasteDetectorTask : public Task {
public:
    /**
     * \brief Creates New Waste Detector Task
     * \param detector Pointer to Waste Detector Object
     */
    WasteDetectorTask(WasteDetector* detector);
    void tick() override;

    /**
     * \brief Check if Container is Full
     * \return if Waste Level >= Alarm Threshold \note See Constants::Sonar::ALARM_THRESHOLD
     */
    bool checkFullness();

private:
    enum State { NOT_FULL, FULL }; /** Enumeration for Waste Detector States */
    State _state; /** Current State of the Waste Detector Task */

    WasteDetector* _detector; /** Pointer to Waste Detector Object */
};
