#ifndef __WASTE_DETECTOR_TASK__
#define __WASTE_DETECTOR_TASK__

#include "Task.h"

class WasteDetectorTask : Task {
public:
    WasteDetectorTask(int pin);
    void init(int period);
    void tick();

private:
    int _pin;
    enum State { EMPTY, FULL};
    State _state;
};

#endif