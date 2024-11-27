#pragma once

#include "Task.h"
#include "../components/logical/Display.h"
#include "../components/logical/WasteDetector.h"

class WasteDetectorTask : public Task {
public:
    WasteDetectorTask(WasteDetector& detector);
    void init(int period);
    void tick();
    bool isFull();

private:
    int _pin;
    WasteDetector* _detector;

    bool _state;
};