#ifndef __A02_WASTE_DETECTOR_TASK__
#define __A02_WASTE_DETECTOR_TASK__

#include "Task.h"
#include "../components/logical/WasteDetector.h"
#include "../communication/MsgService.h"

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

#endif