#pragma once

#include "arduino/lib/Constants.h"
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/communication/SerialHandler.h"
#include "arduino/lib/components/physical/Button.h"
#include "arduino/lib/components/logical/Door.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/WasteDetector.h"

/**
 * \brief Door Task Class
 * \implements{Task}
 */
class DoorTask : public Task {   
public:
    /**
     * \brief Creates New Door Task
     * \param door Pointer to Door Object
     * \param closeButton Pointer to Close Button Object
     * \param openButton Pointer to Open Button Object
     * \param temperatureDetector Pointer to Temperature Detector Object
     * \param wasteDetector Pointer to Waste Detector Object
     */
    DoorTask(Door* door, Button* closeButton, Button* openButton, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector);

    void tick() override;

private:
    enum State { CLOSED, OPENED, OPERATOR_OPENED }; /** Enumeration for Door States */
    State _state; /** Current State of the Door */

    Door* _door; /** Pointer to Door Object */
    Button* _closeButton; /** Pointer to Close Button Object */
    Button* _openButton; /** Pointer to Open Button Object */
    WasteDetector* _wasteDetector; /** Pointer to Waste Detector Object */
    TemperatureDetector* _temperatureDetector; /** Pointer to Temperature Detector Object */

    unsigned long _lastEmptiedTime; /** Timestamp of the Last Empty Action */
    unsigned long _automaticCloseTime; /** Timestamp for Automatic Door Closure */
};