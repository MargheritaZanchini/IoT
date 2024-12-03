#pragma once

#include <LiquidCrystal_I2C.h>
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/communication/SerialHandler.h"
#include "arduino/lib/components/logical/WasteDetector.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/Door.h"

/**
 * \brief User Display Task Class
 * \implements{Task}
 */
class UserDisplayTask : public Task {
public:
    /**
     * \brief Creates New User Display Task
     * \param wasteDetector Pointer to Waste Detector Object
     * \param temperatureDetector Pointer to Temperature Detector Object
     * \param door Pointer to Door Object
     */
    UserDisplayTask(WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector, Door* door);

    void tick() override;

private:
    enum State { DISPLAY_DEFAULT, DISPLAY_WASTE, DISPLAY_TEMPERATURE, DISPLAY_DOOR_OPEN, DISPLAY_ON_DOOR_CLOSED }; /** Enumeration for Display States */
    State _state; /** Current State of the Display */

    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4); /** LCD Display Object */
    WasteDetector* _wasteDetector; /** Pointer to Waste Detector Object */
    TemperatureDetector* _temperatureDetector; /** Pointer to Temperature Detector Object */
    Door* _door; /** Pointer to Door Object */

    unsigned long _lastDetectedTime; /** Timestamp of the Last Detected Event */

    const char* _previousMessage; /** Previous Message Displayed on the LCD */

    /**
     * \brief Updates the Display with a New Message
     * \param msg The Message to Display
     */
    void updateDisplay(const char* msg);
};