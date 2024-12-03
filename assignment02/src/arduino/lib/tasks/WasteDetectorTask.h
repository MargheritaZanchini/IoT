#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/logical/WasteDetector.h"
#include "arduino/lib/communication/SerialHandler.h"

class WasteDetectorTask : public Task {
public:
    WasteDetectorTask(WasteDetector* detector);
    void init(int period);
    void tick();
    bool checkFullness();

private:
    int _pin;
    WasteDetector* _detector;

    enum State { NOT_FULL, FULL };
    State _state;
};
