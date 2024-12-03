#ifndef __A02_USER_DISPLAY_TASK__
#define __A02_USER_DISPLAY_TASK__

#include <LiquidCrystal_I2C.h>
#include "Task.h"
#include "../components/logical/WasteDetector.h"
#include "../components/logical/TemperatureDetector.h"
#include "../components/logical/Door.h"
#include "../communication/MsgService.h"

class UserDisplayTask : public Task {
public:
    UserDisplayTask(WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector/* , Door* door */);
    void tick() override;

private:
    LiquidCrystal_I2C _lcd = LiquidCrystal_I2C(0x27, 20, 4);
    WasteDetector* _wasteDetector;
    TemperatureDetector* _temperatureDetector;
    /* Door* _door; */

    unsigned long _lastDetectedTime;

    enum State { OK, DISPLAY_WASTE, DISPLAY_TEMPERATURE, DISPLAY_DOOR_OPEN, DISPLAY_ON_DOOR_CLOSED };
    State _state;

    String _previousMessage;
    void updateDisplay(const String& msg);
};

#endif