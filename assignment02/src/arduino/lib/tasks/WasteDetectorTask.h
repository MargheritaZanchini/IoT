#ifndef __WASTE_DETECTOR_TASK__
#define __WASTE_DETECTOR_TASK__

#include "Task.h"
#include "../components/logical/WasteDetector.h"

#define MSG_FULL "Container full"

class WasteDetectorTask : public Task {
public:
    WasteDetectorTask(WasteDetector& detector);
    void init(int period);
    void tick();

private:
    int _pin;
    WasteDetector* _detector;
};

#endif