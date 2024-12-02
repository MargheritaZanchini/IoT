#ifndef __A02_USER_DISPLAY_TASK__
#define __A02_USER_DISPLAY_TASK__

#include "Task.h"
#include "../components/logical/Display.h"
#include "../components/logical/WasteDetector.h"
#include "../components/logical/TemperatureDetector.h"
#include "../components/logical/Door.h"
#include "../communication/MsgService.h"

class UserDisplayTask : public Task {
public:
    UserDisplayTask(Display* display, WasteDetector* wasteDetector, TemperatureDetector* temperatureDetector, Door* door);
    void tick() override;

private:
    Display* _display;
    WasteDetector* _wasteDetector;
    TemperatureDetector* _temperatureDetector;
    Door* _door;

    unsigned long _lastDetectedTime;

    enum State { OK, DISPLAY_WASTE, DISPLAY_TEMPERATURE, DISPLAY_DOOR_OPEN, DISPLAY_ON_DOOR_CLOSED };
    State _state;
};

#endif