#pragma once

#include <LiquidCrystal_I2C.h>
#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/communication/SerialHandler.h"
#include "arduino/lib/components/logical/WasteDetector.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/Door.h"

class UserDisplayTask : public Task {
public:
    UserDisplayTask(WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector, Door* door);
    void tick() override;

private:
    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4);
    WasteDetector* _wasteDetector;
    TemperatureDetector* _temperatureDetector;
    Door* _door;

    unsigned long _lastDetectedTime;

    enum State { DISPLAY_DEFAULT, DISPLAY_WASTE, DISPLAY_TEMPERATURE, DISPLAY_DOOR_OPEN, DISPLAY_ON_DOOR_CLOSED };
    State _state;

    const char* _previousMessage;
    void updateDisplay(const char* msg);
};
