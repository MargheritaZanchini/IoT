#ifndef __A02_LEDS_TASK__
#define __A02_LEDS_TASK__

#include "Task.h"
#include "../components/physical/Led.h"
#include "../components/logical/TemperatureDetector.h"
#include "../components/logical/WasteDetector.h"

class LedsTask: public Task {
public:
    LedsTask(Led& ok, Led& error, TemperatureDetector& temperatureDetector, WasteDetector& wasteDetector);  
    void init(int period);
    void tick();

private:
    Led* _ok;
    Led* _error;

    TemperatureDetector* _temperatureDetector;
    WasteDetector* _wasteDetector;

    enum State { OK_ON, ERROR_ON};
    State _state;
};

#endif