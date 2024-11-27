#pragma once

#include "Task.h"
#include "../components/logical/Display.h"
#include "../components/logical/WasteDetector.h"
#include "../components/logical/TemperatureDetector.h"
#include "../components/logical/Door.h"

class UserDisplayTask : public Task {
public:
    UserDisplayTask(Display& display, WasteDetector& wasteDetector, TemperatureDetector& temperatureDetector, Door& door);
    void init(int period);
    void tick();

private:
    Display* _display;
    WasteDetector* _wasteDetector;
    TemperatureDetector* _temperatureDetector;
    Door* _door;

    enum State { OK, DISPLAY_WASTE, DISPLAY_TEMPERATURE, DISPLAY_DOOR_STATUS };
    State _state;
};
