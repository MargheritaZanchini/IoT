#ifndef __WASTE_DETECTOR_TASK__
#define __WASTE_DETECTOR_TASK__

#include "Task.h"
#include "../components/Sonar.h"

class WasteDetectorTask : Task {
public:
    WasteDetectorTask(Sonar& sonar);
    void init(int period);
    void tick();
    bool full;

private:
    int _pin;
    enum State { NOT_FULL, FULL};
    State _state;
    Sonar* _sonar;
};

#endif