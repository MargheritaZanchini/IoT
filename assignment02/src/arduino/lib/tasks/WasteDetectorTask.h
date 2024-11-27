#ifndef __WASTE_DETECTOR_TASK__
#define __WASTE_DETECTOR_TASK__

#include "Task.h"
#include "../components/logical/Display.h"
#include "../components/logical/WasteDetector.h"

class WasteDetectorTask : public Task {
public:
    WasteDetectorTask(WasteDetector& detector, Display& lcd);
    void init(int period);
    void tick();
    bool isFull();

private:
    int _pin;
    WasteDetector* _detector;
    LCD* _lcd;

    bool _state;
};

#endif