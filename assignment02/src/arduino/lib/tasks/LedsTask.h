#pragma once

#include "arduino/lib/tasks/Task.h"
#include "arduino/lib/components/physical/Led.h"
#include "arduino/lib/components/logical/TemperatureDetector.h"
#include "arduino/lib/components/logical/WasteDetector.h"

class LedsTask: public Task {
public:
    LedsTask(Led* ok, Led* error, TemperatureDetector* temperatureDetector, WasteDetector* wasteDetector);  
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
